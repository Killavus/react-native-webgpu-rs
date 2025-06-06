#include "WebGPUTextureView.hpp"

namespace margelo::nitro {
WebGPUTextureView::WebGPUTextureView() : HybridObject(TAG), textureView_(nullptr) {}
WebGPUTextureView::WebGPUTextureView(WGPUTextureView textureView) : HybridObject(TAG), textureView_(textureView) {}
WebGPUTextureView::~WebGPUTextureView() {
  if (textureView_) {
    wgpuTextureViewRelease(textureView_);
  }
}

const WGPUTextureView& WebGPUTextureView::resource() const {
  return textureView_;
}

}
