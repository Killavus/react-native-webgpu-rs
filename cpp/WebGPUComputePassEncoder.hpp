#pragma once

#include "HybridNitroWGPUBindGroupSpec.hpp"
#include "HybridNitroWGPUComputePassEncoderSpec.hpp"
#include "HybridNitroWGPUComputePipelineSpec.hpp"
#include <memory>

extern "C" {
#include <webgpu/wgpu.h>
}


namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBindGroupSpec;
using webgpurs::HybridNitroWGPUComputePassEncoderSpec;
using webgpurs::HybridNitroWGPUComputePipelineSpec;

class WebGPUComputePassEncoder : public HybridNitroWGPUComputePassEncoderSpec {
public:
  WebGPUComputePassEncoder();
  WebGPUComputePassEncoder(WGPUComputePassEncoder encoder);
  ~WebGPUComputePassEncoder() override;

  const WGPUComputePassEncoder &resource() const;
  void setPipeline(const std::shared_ptr<HybridNitroWGPUComputePipelineSpec>
                       &pipeline) override;
  void setBindGroup(
      double index,
      const std::optional<std::shared_ptr<HybridNitroWGPUBindGroupSpec>>
          &bindGroup) override;
  void dispatchWorkgroups(double workgroupCountX, double workgroupCountY,
                          double workgroupCountZ) override;
  void end() override;

private:
  WGPUComputePassEncoder encoder_;
};

} // namespace margelo::nitro
