#include "WebGPUBindGroupLayout.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUBindGroupLayout::WebGPUBindGroupLayout()
    : HybridObject(TAG), layout_(nullptr) {}
WebGPUBindGroupLayout::WebGPUBindGroupLayout(WGPUBindGroupLayout layout)
    : HybridObject(TAG), layout_(layout) {}
WebGPUBindGroupLayout::~WebGPUBindGroupLayout() {
  if (layout_) {
    wgpuBindGroupLayoutRelease(layout_);
  }
}

const WGPUBindGroupLayout &WebGPUBindGroupLayout::resource() const {
  return layout_;
}

std::string WebGPUBindGroupLayout::getLabel()
{
    return NOT_IMPLEMENTED_LABEL_TEXT;
}

void WebGPUBindGroupLayout::setLabel(const std::string &label)
{
    WGPUStringView view{label.c_str(), WGPU_STRLEN};
    wgpuBindGroupLayoutSetLabel(layout_, view);
}
} // namespace margelo::nitro
