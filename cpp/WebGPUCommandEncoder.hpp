#pragma once

#include "HybridNitroWGPUBufferSpec.hpp"
#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include "HybridNitroWGPUCommandEncoderSpec.hpp"
#include "HybridNitroWGPUComputePassEncoderSpec.hpp"
#include <memory>
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBufferSpec;
using webgpurs::HybridNitroWGPUCommandBufferSpec;
using webgpurs::HybridNitroWGPUCommandEncoderSpec;
using webgpurs::HybridNitroWGPUComputePassEncoderSpec;

class WebGPUCommandEncoder : public HybridNitroWGPUCommandEncoderSpec {
public:
  WebGPUCommandEncoder();
  WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder);
  ~WebGPUCommandEncoder() override;

  std::shared_ptr<HybridNitroWGPUComputePassEncoderSpec>
  beginComputePass(const ComputePassDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUCommandBufferSpec>
  finish(const std::optional<CommandBufferDescriptor> &descriptor) override;

  void copyBufferToBuffer(
      const std::shared_ptr<HybridNitroWGPUBufferSpec> &source,
      double sourceOffset,
      const std::shared_ptr<HybridNitroWGPUBufferSpec> &destination,
      double destinationOffset, double size) override;

private:
  WGPUCommandEncoder commandEncoder_;
};

} // namespace margelo::nitro
