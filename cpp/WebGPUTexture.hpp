#pragma once

#include "HybridNitroWGPUTextureSpec.hpp"
#include <memory>
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUTextureSpec;

class WebGPUTexture : public HybridNitroWGPUTextureSpec {
public:
  WebGPUTexture();
  WebGPUTexture(WGPUTexture texture);
  ~WebGPUTexture() override;

private:
  WGPUTexture texture_;
};

} // namespace margelo::nitro
