#pragma once

#include "HybridNitroWGPUBindGroupSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}


namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBindGroupSpec;

class WebGPUBindGroup : public HybridNitroWGPUBindGroupSpec {
public:
  WebGPUBindGroup();
  WebGPUBindGroup(WGPUBindGroup group);
  ~WebGPUBindGroup() override;

  const WGPUBindGroup &resource() const;
void setLabel(const std::string &label) override;
std::string getLabel() override;
private:
  WGPUBindGroup group_;
};

} // namespace margelo::nitro
