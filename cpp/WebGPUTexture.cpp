#include "WebGPUTexture.hpp"
#include "WGPUTypeConversions.hpp"
#include "WebGPUTextureView.hpp"

namespace margelo::nitro {
WebGPUTexture::WebGPUTexture() : HybridObject(TAG), texture_(nullptr) {}
WebGPUTexture::WebGPUTexture(WGPUTexture texture)
    : HybridObject(TAG), texture_(texture) {}
WebGPUTexture::~WebGPUTexture() {
  if (texture_) {
    wgpuTextureRelease(texture_);
  }
}

std::shared_ptr<HybridNitroWGPUTextureViewSpec>
WebGPUTexture::createView(const TextureViewDescriptor &descriptor) {
  WGPUTextureViewDescriptor wgpuDescriptor{0};

  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }
  wgpuDescriptor.nextInChain = nullptr;

  wgpuDescriptor.usage = (WGPUFlags)descriptor.usage.value_or(0);
  wgpuDescriptor.format = descriptor.format.has_value()
                              ? toWGPUTextureFormat(descriptor.format.value())
                              : WGPUTextureFormat_Undefined;

  wgpuDescriptor.dimension =
      descriptor.dimension.has_value()
          ? toWGPUTextureViewDimension(descriptor.dimension.value())
          : WGPUTextureViewDimension_Undefined;

  wgpuDescriptor.aspect =
      toWGPUTextureAspect(descriptor.aspect.value_or(TextureAspect::ALL));
  wgpuDescriptor.baseArrayLayer =
      (uint32_t)descriptor.baseArrayLayer.value_or(0);
  wgpuDescriptor.baseMipLevel = (uint32_t)descriptor.baseMipLevel.value_or(0);

  wgpuDescriptor.arrayLayerCount =
      descriptor.arrayLayerCount.has_value()
          ? (uint32_t)descriptor.arrayLayerCount.value()
          : deduceTextureViewArrayCount(wgpuDescriptor.dimension,
                                        wgpuDescriptor.baseArrayLayer);

  wgpuDescriptor.mipLevelCount =
      descriptor.mipLevelCount.has_value()
          ? (uint32_t)descriptor.mipLevelCount.value()
          : wgpuTextureGetMipLevelCount(texture_) - wgpuDescriptor.baseMipLevel;

  WGPUTextureView textureView{wgpuTextureCreateView(texture_, &wgpuDescriptor)};

  return std::make_shared<WebGPUTextureView>(textureView);
}

uint32_t WebGPUTexture::deduceTextureViewArrayCount(
    const WGPUTextureViewDimension &dimension, uint32_t baseArrayLayer) {
  WGPUTextureViewDimension targetDimension = dimension;

  if (targetDimension == WGPUTextureViewDimension_Undefined) {
    WGPUTextureDimension textureDimension{wgpuTextureGetDimension(texture_)};
    uint32_t depthArrayLayers = wgpuTextureGetDepthOrArrayLayers(texture_);

    if (textureDimension == WGPUTextureDimension_1D) {
      targetDimension = WGPUTextureViewDimension_1D;
    } else if (textureDimension == WGPUTextureDimension_2D) {
      targetDimension = depthArrayLayers > 1 ? WGPUTextureViewDimension_2DArray
                                             : WGPUTextureViewDimension_2D;
    } else if (textureDimension == WGPUTextureDimension_3D) {
      targetDimension = WGPUTextureViewDimension_3D;
    }
  }

  switch (targetDimension) {
  case WGPUTextureViewDimension_1D:
  case WGPUTextureViewDimension_2D:
  case WGPUTextureViewDimension_3D:
    return 1;
  case WGPUTextureViewDimension_Cube:
    return 6;
  default:
    return wgpuTextureGetDepthOrArrayLayers(texture_) - baseArrayLayer;
  }
}

double WebGPUTexture::getWidth() {
  return (double)wgpuTextureGetWidth(texture_);
};
double WebGPUTexture::getHeight() {
  return (double)wgpuTextureGetHeight(texture_);
};
double WebGPUTexture::getDepthOrArrayLayers() {
  return (double)wgpuTextureGetDepthOrArrayLayers(texture_);
};
double WebGPUTexture::getMipLevelCount() {
  return (double)wgpuTextureGetMipLevelCount(texture_);
};
double WebGPUTexture::getSampleCount() {
  return (double)wgpuTextureGetSampleCount(texture_);
};
TextureDimension WebGPUTexture::getDimension() {
  return toNitroTextureDimension(wgpuTextureGetDimension(texture_));
};
TextureFormat WebGPUTexture::getFormat() {
  return toNitroTextureFormat(wgpuTextureGetFormat(texture_));
};
double WebGPUTexture::getUsage() {
  return (double)wgpuTextureGetUsage(texture_);
};

const WGPUTexture &WebGPUTexture::resource() const { return texture_; }

} // namespace margelo::nitro
