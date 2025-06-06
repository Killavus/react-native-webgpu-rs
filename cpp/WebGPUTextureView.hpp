#pragma once

#include <memory>
#include "HybridNitroWGPUTextureViewSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUTextureViewSpec;

class WebGPUTextureView : public HybridNitroWGPUTextureViewSpec {
public:
  WebGPUTextureView();
  WebGPUTextureView(WGPUTextureView textureView);
  ~WebGPUTextureView() override;
  
  const WGPUTextureView& resource() const;
private:
  WGPUTextureView textureView_;
};

} // namespace margelo::nitro
