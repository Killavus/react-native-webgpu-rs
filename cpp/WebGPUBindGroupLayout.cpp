#include "WebGPUBindGroupLayout.hpp"

namespace margelo::nitro {
WebGPUBindGroupLayout::WebGPUBindGroupLayout() : HybridObject(TAG), layout_(nullptr) {}
WebGPUBindGroupLayout::WebGPUBindGroupLayout(WGPUBindGroupLayout layout) : HybridObject(TAG), layout_(layout) {}
WebGPUBindGroupLayout::~WebGPUBindGroupLayout() {
  if (layout_) {
    wgpuBindGroupLayoutRelease(layout_);
  }
}

const WGPUBindGroupLayout& WebGPUBindGroupLayout::resource() const { return layout_; }
}
