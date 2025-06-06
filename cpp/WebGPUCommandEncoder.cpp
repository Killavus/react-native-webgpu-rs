#include "WebGPUCommandEncoder.hpp"

namespace margelo::nitro {
WebGPUCommandEncoder::WebGPUCommandEncoder() : HybridObject(TAG), commandEncoder_(nullptr) {}
WebGPUCommandEncoder::WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder) : HybridObject(TAG), commandEncoder_(commandEncoder) {}
WebGPUCommandEncoder::~WebGPUCommandEncoder() {
  if (commandEncoder_) {
    wgpuCommandEncoderRelease(commandEncoder_);
  }
}

}
