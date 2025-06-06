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

  switch (status) {
  case WGPURequestAdapterStatus_Success:
    printf("Success %ld!\n", promise->use_count());
    promise->get()->resolve(std::make_shared<WebGPUAdapter>(adapter));
    delete promise;
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
WebGPUInstance::requestAdapter() {
  auto promise = Promise<std::shared_ptr<HybridNitroWGPUAdapterSpec>>::create();

  WGPURequestAdapterCallbackInfo callback{0};
  {
    auto promiseCb = new std::shared_ptr(promise);

    callback.mode = WGPUCallbackMode_WaitAnyOnly;
    callback.userdata1 = (void *)promiseCb;
    callback.userdata2 = nullptr;
    callback.nextInChain = nullptr;
    callback.callback = handleRequestAdapter;
  }

  wgpuInstanceRequestAdapter(instance_, nullptr, callback);

  return promise;
}

WebGPUInstance::~WebGPUInstance() {
  if (instance_) {
    wgpuInstanceRelease(instance_);
  }
}

} // namespace margelo::nitro
