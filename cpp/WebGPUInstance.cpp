#include "WebGPUInstance.hpp"
#include "WebGPUAdapter.hpp"

namespace margelo::nitro {
WebGPUInstance::WebGPUInstance() : HybridObject(TAG) {
  instance_ = wgpuCreateInstance(nullptr);
}

static void handleRequestAdapter(WGPURequestAdapterStatus status,
                                 WGPUAdapter adapter, WGPUStringView message,
                                 void *userdata1, void *userdata2) {
  printf("Called handleRequestAdapter\n");
  auto promise = reinterpret_cast<
      std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUAdapterSpec>>> *>(
      userdata1);
  auto instance =
      reinterpret_cast<std::shared_ptr<WebGPUInstance> *>(userdata2);

  switch (status) {
  case WGPURequestAdapterStatus_Success:
    printf("Success %ld!\n", promise->use_count());
    {
      WGPUSupportedFeatures features{0};
      wgpuAdapterGetFeatures(adapter, &features);

      printf("%lu\n", features.featureCount);
      for (size_t i = 0; i < features.featureCount; ++i) {
        printf("%#.8x\n", features.features[i]);
      }
    }

    {
      auto instancePtr = std::shared_ptr(*instance);
      delete instance;
      promise->get()->resolve(
          std::make_shared<WebGPUAdapter>(adapter, instancePtr));
      delete promise;
    }
    break;
  case WGPURequestAdapterStatus_Error:
    promise->get()->reject(std::make_exception_ptr(message.data));
    delete promise;
    printf("Error\n");
    break;
  case WGPURequestAdapterStatus_Unknown:
    printf("Unknown\n");
    break;
  case WGPURequestAdapterStatus_Unavailable:
    printf("Unavailable\n");
    promise->get()->reject(
        std::make_exception_ptr("WebGPU Adapter unavailable"));
    delete promise;
    break;
  case WGPURequestAdapterStatus_InstanceDropped:
    printf("Instance dropped\n");
    promise->get()->reject(std::make_exception_ptr(
        "WebGPU Instance dropped while requesting adapter"));
    delete promise;
    break;
  default:
    return;
  }
}

void WebGPUInstance::enumerateAdapters() {
  const size_t adapter_count =
      wgpuInstanceEnumerateAdapters(instance_, NULL, NULL);
  WGPUAdapter *adapters =
      (WGPUAdapter *)malloc(sizeof(WGPUAdapter) * adapter_count);
  assert(adapters);
  wgpuInstanceEnumerateAdapters(instance_, NULL, adapters);

  for (int i = 0; i < adapter_count; i++) {
    WGPUAdapter adapter = adapters[i];
    assert(adapter);

    WGPUAdapterInfo info = {0};
    wgpuAdapterGetInfo(adapter, &info);
    printf("WGPUAdapter: %d\n", i);
    printf("WGPUAdapterInfo {\n"
           "\tvendor: %.*s\n"
           "\tarchitecture: %.*s\n"
           "\tdevice: %.*s\n"
           "\tdescription: %.*s\n"
           "\tbackendType: %#.8x\n"
           "\tadapterType: %#.8x\n"
           "\tvendorID: %u"
           "\n"
           "\tdeviceID: %u"
           "\n"
           "}\n",
           (int)info.vendor.length, info.vendor.data,
           (int)info.architecture.length, info.architecture.data,
           (int)info.device.length, info.device.data,
           (int)info.description.length, info.description.data,
           info.backendType, info.adapterType, info.vendorID, info.deviceID);
    wgpuAdapterInfoFreeMembers(info);
  }
}

std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUAdapterSpec>>>
WebGPUInstance::requestAdapter(
    const std::optional<AdapterDescriptor> &descriptor) {
  auto promise = Promise<std::shared_ptr<HybridNitroWGPUAdapterSpec>>::create();

  WGPURequestAdapterOptions wgpuOpts{0};

  bool hasOpts = descriptor.has_value();

  if (hasOpts) {
    auto opts = descriptor.value();
    wgpuOpts.nextInChain = nullptr;
    if (opts.powerPreference.has_value()) {
      wgpuOpts.powerPreference =
          opts.powerPreference.value() == AdapterPowerPreference::LOW_POWER
              ? WGPUPowerPreference_LowPower
              : WGPUPowerPreference_HighPerformance;
    }
  }

  WGPURequestAdapterCallbackInfo callback{0};
  {
    auto promiseCb = new std::shared_ptr(promise);

    callback.mode = WGPUCallbackMode_WaitAnyOnly;
    callback.userdata1 = (void *)promiseCb;
    callback.userdata2 =
        new std::shared_ptr<WebGPUInstance>(this->shared<WebGPUInstance>());
    callback.nextInChain = nullptr;
    callback.callback = handleRequestAdapter;
  }

  wgpuInstanceRequestAdapter(instance_, hasOpts ? &wgpuOpts : nullptr,
                             callback);

  return promise;
}

void WebGPUInstance::registerErrorHandler(
    const std::function<void(const std::string &)> &handler) {
  errorHandler_ =
      std::make_shared<std::function<void(const std::string &)>>(handler);
};

void WebGPUInstance::callErrorHandler(const std::string &message) {
  if (errorHandler_) {
    (*errorHandler_.get())(message);
  }
}

TextureFormat WebGPUInstance::getPreferredCanvasFormat() {
#if defined(__ANDROID__)
  return TextureFormat::RGBA8UNORM;
#else
  return TextureFormat::BGRA8UNORM;
#endif // defined(__ANDROID__)
}

WebGPUInstance::~WebGPUInstance() {
  if (instance_) {
    wgpuInstanceRelease(instance_);
  }
}

} // namespace margelo::nitro
