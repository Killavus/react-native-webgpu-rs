#include "WebGPUCommandBuffer.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUCommandBuffer::WebGPUCommandBuffer()
    : HybridObject(TAG), cmdBuffer_(nullptr) {}
WebGPUCommandBuffer::WebGPUCommandBuffer(WGPUCommandBuffer cmdBuffer)
    : HybridObject(TAG), cmdBuffer_(cmdBuffer) {}
WebGPUCommandBuffer::~WebGPUCommandBuffer() {
  if (cmdBuffer_) {
    wgpuCommandBufferRelease(cmdBuffer_);
  }
}

const WGPUCommandBuffer &WebGPUCommandBuffer::resource() const {
  return cmdBuffer_;
}
    void WebGPUCommandBuffer::setLabel(const std::string &label) {
        WGPUStringView view { label.c_str(), WGPU_STRLEN };
        wgpuCommandBufferSetLabel(cmdBuffer_, view);
    }

    std::string WebGPUCommandBuffer::getLabel() {
        return NOT_IMPLEMENTED_LABEL_TEXT;
    }
} // namespace margelo::nitro
