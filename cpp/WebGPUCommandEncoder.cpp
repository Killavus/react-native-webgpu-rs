#include "WebGPUCommandEncoder.hpp"
#include "WebGPUComputePassEncoder.hpp"
#include "WebGPUCommandBuffer.hpp"

namespace margelo::nitro {
WebGPUCommandEncoder::WebGPUCommandEncoder() : HybridObject(TAG), commandEncoder_(nullptr) {}
WebGPUCommandEncoder::WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder) : HybridObject(TAG), commandEncoder_(commandEncoder) {}
WebGPUCommandEncoder::~WebGPUCommandEncoder() {
  if (commandEncoder_) {
    wgpuCommandEncoderRelease(commandEncoder_);
  }
}

std::shared_ptr<HybridNitroWGPUComputePassEncoderSpec> WebGPUCommandEncoder::beginComputePass(const ComputePassDescriptor& descriptor) {
  WGPUComputePassDescriptor wgpuDescriptor {0};
  
  wgpuDescriptor.nextInChain = nullptr;
  // TODO: Support timestamp writes.
  wgpuDescriptor.timestampWrites = nullptr;
  wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
  }
  
  WGPUComputePassEncoder encoder { wgpuCommandEncoderBeginComputePass(commandEncoder_, &wgpuDescriptor) };
  
  return std::make_shared<WebGPUComputePassEncoder>(encoder);
};

std::shared_ptr<HybridNitroWGPUCommandBufferSpec> WebGPUCommandEncoder::finish(const std::optional<CommandBufferDescriptor>& descriptor) {
  if (descriptor.has_value()) {
    WGPUCommandBufferDescriptor wgpuDescriptor {0};
    wgpuDescriptor.nextInChain = nullptr;
    wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
    
    if (descriptor.value().label.has_value()) {
      wgpuDescriptor.label = { descriptor.value().label.value().c_str(), WGPU_STRLEN };
    }
    
    WGPUCommandBuffer cmdBuffer {
      wgpuCommandEncoderFinish(commandEncoder_, &wgpuDescriptor)
    };
    
    return std::make_shared<WebGPUCommandBuffer>(cmdBuffer);
  } else {
    WGPUCommandBuffer cmdBuffer { wgpuCommandEncoderFinish(commandEncoder_, nullptr) };
    return std::make_shared<WebGPUCommandBuffer>(cmdBuffer);
  }
  
};


}
