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
  void setLabel(const std::string &label) override;
  std::string getLabel() override;

private:
  WGPUComputePipeline pipeline_;
};

} // namespace margelo::nitro
