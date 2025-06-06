#pragma once

#include <memory>
#include "HybridNitroWGPUBindGroupSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBindGroupSpec;

class WebGPUBindGroup : public HybridNitroWGPUBindGroupSpec {
public:
  WebGPUBindGroup();
  WebGPUBindGroup(WGPUBindGroup group);
  ~WebGPUBindGroup() override;
private:
  WGPUBindGroup group_;
};

} // namespace margelo::nitro
