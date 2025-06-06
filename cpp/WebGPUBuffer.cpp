#include "WebGPUBuffer.hpp"

namespace margelo::nitro {
WebGPUBuffer::WebGPUBuffer()
    : HybridObject(TAG), buffer_(nullptr), device_(nullptr) {}
WebGPUBuffer::WebGPUBuffer(WGPUBuffer buffer, WGPUDevice device)
    : HybridObject(TAG), buffer_(buffer), device_(device) {}
WebGPUBuffer::~WebGPUBuffer() {
  if (buffer_) {
    wgpuBufferRelease(buffer_);
  }
}

const WGPUBuffer &WebGPUBuffer::resource() const { return buffer_; }

static void handleMapAsync(WGPUMapAsyncStatus status, WGPUStringView message,
                           void *userdata1, void *userdata2) {
  printf("handleMapAsync\n");
  auto promise = static_cast<std::shared_ptr<Promise<void>> *>(userdata1);

  switch (status) {
  case WGPUMapAsyncStatus_Aborted:
    printf("handleMapAsync ABORTED\n");
    promise->get()->reject(std::make_exception_ptr(message));
    delete promise;
    return;
  case WGPUMapAsyncStatus_InstanceDropped:
    printf("handleMapAsync INSTANCE DROPPED\n");
    promise->get()->reject(std::make_exception_ptr(message));
    delete promise;
    return;
  case WGPUMapAsyncStatus_Success:
    printf("handleMapAsync SUCCESS\n");
    promise->get()->resolve();
    delete promise;
    return;
  case WGPUMapAsyncStatus_Error:
    printf("handleMapAsync ERROR\n");
    promise->get()->reject(std::make_exception_ptr(message));
    delete promise;
    return;
  case WGPUMapAsyncStatus_Unknown:
    printf("Unknown WGPUMapAsyncStatus\n");
    return;
  default:
    return;
  }
}

std::shared_ptr<Promise<void>>
WebGPUBuffer::mapAsync(double mode, std::optional<double> offset,
                       std::optional<double> size) {
  printf("WebGPUBuffer::mapAsync\n");
  auto wgpuOffset = (size_t)offset.value_or(0);
  auto wgpuSize = wgpuBufferGetSize(buffer_) - (size_t)offset.value_or(0);

  auto promise = Promise<void>::create();

  auto promiseCb = new std::shared_ptr<Promise<void>>(promise);

  ThreadPool::shared().run([=, this] {
    WGPUBufferMapCallbackInfo callbackInfo{0};
    callbackInfo.nextInChain = nullptr;
    callbackInfo.userdata1 = promiseCb;
    callbackInfo.userdata2 = nullptr;
    callbackInfo.callback = handleMapAsync;

    wgpuBufferMapAsync(buffer_, (uint64_t)mode, wgpuOffset, wgpuSize,
                       callbackInfo);
    wgpuDevicePoll(device_, 1, nullptr);
  });

  return promise;
}

std::shared_ptr<ArrayBuffer>
WebGPUBuffer::getMappedRange(std::optional<double> offset,
                             std::optional<double> size) {
  auto wgpuOffset = (size_t)offset.value_or(0);
  auto wgpuSize = wgpuBufferGetSize(buffer_) - (size_t)offset.value_or(0);

  uint8_t *mappedData =
      (uint8_t *)wgpuBufferGetMappedRange(buffer_, wgpuOffset, wgpuSize);

  auto mappedArrayBuffer = ArrayBuffer::wrap(mappedData, wgpuSize, [=]() {});

  return mappedArrayBuffer;
}

void WebGPUBuffer::unmap() { wgpuBufferUnmap(buffer_); };

} // namespace margelo::nitro
