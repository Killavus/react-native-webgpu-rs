#include "WebGPUBindGroup.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUBindGroup::WebGPUBindGroup() : HybridObject(TAG), group_(nullptr) {}
WebGPUBindGroup::WebGPUBindGroup(WGPUBindGroup group)
    : HybridObject(TAG), group_(group) {}
WebGPUBindGroup::~WebGPUBindGroup() {
  if (group_) {
    wgpuBindGroupRelease(group_);
  }
}

const WGPUBindGroup &WebGPUBindGroup::resource() const { return group_; }
    std::string WebGPUBindGroup::getLabel()
    {
        return NOT_IMPLEMENTED_LABEL_TEXT;
    }

    void WebGPUBindGroup::setLabel(const std::string &label)
    {
        WGPUStringView view{label.c_str(), WGPU_STRLEN};
        wgpuBindGroupSetLabel(group_, view);
    }
} // namespace margelo::nitro
