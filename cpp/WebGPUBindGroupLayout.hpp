#pragma once

#include <memory>
#include "HybridNitroWGPUBindGroupLayoutSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBindGroupLayoutSpec;

class WebGPUBindGroupLayout : public HybridNitroWGPUBindGroupLayoutSpec {
public:
  WebGPUBindGroupLayout();
  WebGPUBindGroupLayout(WGPUBindGroupLayout layout);
  ~WebGPUBindGroupLayout() override;
private:
  WGPUBindGroupLayout layout_;
};

} // namespace margelo::nitro
