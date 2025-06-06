#include "WebGPUAdapter.hpp"
#include "WebGPUDevice.hpp"

namespace margelo::nitro {

static void handleRequestDevice(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message, void* userdata1, void* userdata2) {
  printf("Called handleRequestDevice\n");
  auto promise = reinterpret_cast<std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUDeviceSpec>>>*>(userdata1);
  
  switch (status) {
    case WGPURequestDeviceStatus_Error:
      promise->get()->reject(std::make_exception_ptr(message.data));
      delete promise;
      break;
    case WGPURequestDeviceStatus_Success:
      promise->get()->resolve(std::make_shared<WebGPUDevice>(device));
      delete promise;
      break;
    case WGPURequestDeviceStatus_Unknown:
      printf("Unknown\n");
      break;
    case WGPURequestDeviceStatus_InstanceDropped:
      printf("Instance dropped\n");
      promise->get()->reject(std::make_exception_ptr(message.data));
      delete promise;
      break;
    default:
      return;
  }

}

WebGPUAdapter::WebGPUAdapter() : HybridObject(TAG), adapter_(nullptr) {}

WebGPUAdapter::~WebGPUAdapter() {
  if (adapter_) {
    wgpuAdapterRelease(adapter_);
  }
}

WebGPUAdapter::WebGPUAdapter(WGPUAdapter adapter): HybridObject(TAG), adapter_(adapter) {}

std::shared_ptr<Promise<std::shared_ptr<margelo::nitro::webgpurs::HybridNitroWGPUDeviceSpec>>> WebGPUAdapter::requestDevice() {
  auto promise = Promise<std::shared_ptr<margelo::nitro::webgpurs::HybridNitroWGPUDeviceSpec>>::create();
  
  WGPURequestDeviceCallbackInfo callback {0};
  {
    auto promiseCb = new std::shared_ptr(promise);

    callback.mode = WGPUCallbackMode_WaitAnyOnly;
    callback.userdata1 = (void*) promiseCb;
    callback.userdata2 = nullptr;
    callback.nextInChain = nullptr;
    callback.callback = handleRequestDevice;
  }
  
  wgpuAdapterRequestDevice(adapter_, nullptr, callback);
  return promise;
}

} // namespace margelo::nitro

