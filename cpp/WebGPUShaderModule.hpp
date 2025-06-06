#pragma once

#include <memory>
#include "HybridNitroWGPUShaderModuleSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUShaderModuleSpec;

class WebGPUShaderModule : public HybridNitroWGPUShaderModuleSpec {
public:
  WebGPUShaderModule();
  WebGPUShaderModule(WGPUShaderModule buffer);
  ~WebGPUShaderModule() override;
  
  const WGPUShaderModule& resource() const;
private:
  WGPUShaderModule shaderModule_;
};

} // namespace margelo::nitro
