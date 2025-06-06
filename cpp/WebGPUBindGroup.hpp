#pragma once

#include "HybridNitroWGPUBindGroupSpec.hpp"
#include <memory>
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBindGroupSpec;

class WebGPUBindGroup : public HybridNitroWGPUBindGroupSpec {
public:
  WebGPUBindGroup();
  WebGPUBindGroup(WGPUBindGroup group);
  ~WebGPUBindGroup() override;

  const WGPUBindGroup &resource() const;

private:
  WGPUBindGroup group_;
};

} // namespace margelo::nitro
