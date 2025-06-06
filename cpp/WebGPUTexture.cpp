#include "WebGPUTexture.hpp"

namespace margelo::nitro {
WebGPUTexture::WebGPUTexture() : HybridObject(TAG), texture_(nullptr) {}
WebGPUTexture::WebGPUTexture(WGPUTexture texture) : HybridObject(TAG), texture_(texture) {}
WebGPUTexture::~WebGPUTexture() {
  if (texture_) {
    wgpuTextureRelease(texture_);
  }
}
}
