#pragma once

#include <memory>
#include "HybridNitroWGPUCommandEncoderSpec.hpp"
#include "HybridNitroWGPUComputePassEncoderSpec.hpp"
#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUCommandEncoderSpec;
using webgpurs::HybridNitroWGPUComputePassEncoderSpec;
using webgpurs::HybridNitroWGPUCommandBufferSpec;

class WebGPUCommandEncoder : public HybridNitroWGPUCommandEncoderSpec {
public:
  WebGPUCommandEncoder();
  WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder);
  ~WebGPUCommandEncoder() override;
  
  std::shared_ptr<HybridNitroWGPUComputePassEncoderSpec> beginComputePass(const ComputePassDescriptor& descriptor) override;
  std::shared_ptr<HybridNitroWGPUCommandBufferSpec> finish(const std::optional<CommandBufferDescriptor>& descriptor) override;
private:
  WGPUCommandEncoder commandEncoder_;
};

} // namespace margelo::nitro
