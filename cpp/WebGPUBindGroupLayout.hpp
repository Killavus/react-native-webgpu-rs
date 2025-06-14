#pragma once

#include "HybridNitroWGPUBindGroupLayoutSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBindGroupLayoutSpec;

class WebGPUBindGroupLayout : public HybridNitroWGPUBindGroupLayoutSpec {
public:
  WebGPUBindGroupLayout();
  WebGPUBindGroupLayout(WGPUBindGroupLayout layout);
  ~WebGPUBindGroupLayout() override;

  const WGPUBindGroupLayout &resource() const;
  void setLabel(const std::string &label) override;
  std::string getLabel() override;

private:
  WGPUBindGroupLayout layout_;
};

} // namespace margelo::nitro
