#pragma once

#include "HybridNitroWGPUShaderModuleSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUShaderModuleSpec;

class WebGPUShaderModule : public HybridNitroWGPUShaderModuleSpec {
public:
  WebGPUShaderModule();
  WebGPUShaderModule(WGPUShaderModule buffer);
  ~WebGPUShaderModule() override;

  const WGPUShaderModule &resource() const;

  void setLabel(const std::string &label) override;
  std::string getLabel() override;
private:
  WGPUShaderModule shaderModule_;
};

} // namespace margelo::nitro
