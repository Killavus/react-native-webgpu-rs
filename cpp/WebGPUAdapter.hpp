#pragma once

#include <memory>
#include "HybridNitroWGPUAdapterSpec.hpp"
#include "HybridNitroWGPUDeviceSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {

using webgpurs::HybridNitroWGPUAdapterSpec;
using webgpurs::HybridNitroWGPUDeviceSpec;

class WebGPUAdapter : public HybridNitroWGPUAdapterSpec {
public:
  WebGPUAdapter();
  WebGPUAdapter(WGPUAdapter adapter);
  ~WebGPUAdapter() override;
  
  std::shared_ptr<Promise<std::shared_ptr<margelo::nitro::webgpurs::HybridNitroWGPUDeviceSpec>>> requestDevice() override;
private:
  WGPUAdapter adapter_;
};

} // namespace margelo::nitro 
