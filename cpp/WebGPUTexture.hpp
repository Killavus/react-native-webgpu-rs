#pragma once

#include "HybridNitroWGPUTextureSpec.hpp"
#include "HybridNitroWGPUTextureViewSpec.hpp"

#include <memory>
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUTextureSpec;
using webgpurs::HybridNitroWGPUTextureViewSpec;

class WebGPUTexture : public HybridNitroWGPUTextureSpec {
public:
  WebGPUTexture();
  WebGPUTexture(WGPUTexture texture);
  ~WebGPUTexture() override;

  std::shared_ptr<HybridNitroWGPUTextureViewSpec>
  createView(const TextureViewDescriptor &descriptor) override;
  double getWidth() override;
  double getHeight() override;
  double getDepthOrArrayLayers() override;
  double getMipLevelCount() override;
  double getSampleCount() override;
  TextureDimension getDimension() override;
  TextureFormat getFormat() override;
  double getUsage() override;

  const WGPUTexture &resource() const;

private:
  uint32_t
  deduceTextureViewArrayCount(const WGPUTextureViewDimension &dimension,
                              uint32_t baseArrayLayer);

  WGPUTexture texture_;
};

} // namespace margelo::nitro
