#pragma once

#include "HybridNitroWGPUPipelineLayoutSpec.hpp"
#include <memory>

extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUPipelineLayoutSpec;

class WebGPUPipelineLayout : public HybridNitroWGPUPipelineLayoutSpec {
public:
  WebGPUPipelineLayout();
  WebGPUPipelineLayout(WGPUPipelineLayout layout_);
  ~WebGPUPipelineLayout() override;

  const WGPUPipelineLayout &resource() const;
  void setLabel(const std::string &label) override;
  std::string getLabel() override;

private:
  WGPUPipelineLayout layout_;
};

} // namespace margelo::nitro
