#pragma once

#include "HybridNitroWGPUComputePipelineSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUComputePipelineSpec;

class WebGPUComputePipeline : public HybridNitroWGPUComputePipelineSpec {
public:
  WebGPUComputePipeline();
  WebGPUComputePipeline(WGPUComputePipeline pipeline_);
  ~WebGPUComputePipeline() override;

  const WGPUComputePipeline &resource() const;

private:
  WGPUComputePipeline pipeline_;
};

} // namespace margelo::nitro
