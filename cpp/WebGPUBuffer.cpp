#include "WebGPUBuffer.hpp"

namespace margelo::nitro {
WebGPUBuffer::WebGPUBuffer() : HybridObject(TAG), buffer_(nullptr) {}
WebGPUBuffer::WebGPUBuffer(WGPUBuffer buffer) : HybridObject(TAG), buffer_(buffer) {}
WebGPUBuffer::~WebGPUBuffer() {
  if (buffer_) {
    wgpuBufferRelease(buffer_);
  }
}

const WGPUBuffer& WebGPUBuffer::resource() const {
  return buffer_;
}

}
