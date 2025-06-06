#include "WebGPUCommandBuffer.hpp"

namespace margelo::nitro {
WebGPUCommandBuffer::WebGPUCommandBuffer() : HybridObject(TAG), cmdBuffer_(nullptr) {}
WebGPUCommandBuffer::WebGPUCommandBuffer(WGPUCommandBuffer cmdBuffer) : HybridObject(TAG), cmdBuffer_(cmdBuffer) {}
WebGPUCommandBuffer::~WebGPUCommandBuffer() {
  if (cmdBuffer_) {
    wgpuCommandBufferRelease(cmdBuffer_);
  }
}

const WGPUCommandBuffer& WebGPUCommandBuffer::resource() const { return cmdBuffer_; }
}
