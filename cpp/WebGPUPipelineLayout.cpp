#include "WebGPUPipelineLayout.hpp"

namespace margelo::nitro {
WebGPUPipelineLayout::WebGPUPipelineLayout() : HybridObject(TAG), layout_(nullptr) {}
WebGPUPipelineLayout::WebGPUPipelineLayout(WGPUPipelineLayout layout) : HybridObject(TAG), layout_(layout) {}
WebGPUPipelineLayout::~WebGPUPipelineLayout() {
  if (layout_) {
    wgpuPipelineLayoutRelease(layout_);
  }
}

const WGPUPipelineLayout& WebGPUPipelineLayout::resource() const {
  return layout_;
}
}
