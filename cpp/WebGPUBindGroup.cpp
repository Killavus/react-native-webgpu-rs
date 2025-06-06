#include "WebGPUBindGroup.hpp"

namespace margelo::nitro {
WebGPUBindGroup::WebGPUBindGroup() : HybridObject(TAG), group_(nullptr) {}
WebGPUBindGroup::WebGPUBindGroup(WGPUBindGroup group) : HybridObject(TAG), group_(group) {}
WebGPUBindGroup::~WebGPUBindGroup() {
  if (group_) {
    wgpuBindGroupRelease(group_);
  }
}
}
