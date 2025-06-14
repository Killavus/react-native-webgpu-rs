#include "WebGPUPipelineLayout.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUPipelineLayout::WebGPUPipelineLayout()
    : HybridObject(TAG), layout_(nullptr) {}
WebGPUPipelineLayout::WebGPUPipelineLayout(WGPUPipelineLayout layout)
    : HybridObject(TAG), layout_(layout) {}
WebGPUPipelineLayout::~WebGPUPipelineLayout() {
  if (layout_) {
    wgpuPipelineLayoutRelease(layout_);
  }
}

const WGPUPipelineLayout &WebGPUPipelineLayout::resource() const {
  return layout_;
}

void WebGPUPipelineLayout::setLabel(const std::string &label) {
    WGPUStringView view { label.c_str(), WGPU_STRLEN };
    wgpuPipelineLayoutSetLabel(layout_, view);
}

std::string WebGPUPipelineLayout::getLabel() {
    return NOT_IMPLEMENTED_LABEL_TEXT;
}

} // namespace margelo::nitro
