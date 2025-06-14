#include "WebGPUTextureView.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUTextureView::WebGPUTextureView()
    : HybridObject(TAG), textureView_(nullptr) {}
WebGPUTextureView::WebGPUTextureView(WGPUTextureView textureView)
    : HybridObject(TAG), textureView_(textureView) {}
WebGPUTextureView::~WebGPUTextureView() {
  if (textureView_) {
    wgpuTextureViewRelease(textureView_);
  }
}

const WGPUTextureView &WebGPUTextureView::resource() const {
  return textureView_;
}

std::string WebGPUTextureView::getLabel() {
    return NOT_IMPLEMENTED_LABEL_TEXT;
}

void WebGPUTextureView::setLabel(const std::string &label) {
    WGPUStringView view { label.c_str(), WGPU_STRLEN };
    wgpuTextureViewSetLabel(textureView_, view);
}


} // namespace margelo::nitro
