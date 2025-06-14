#include "WebGPUShaderModule.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUShaderModule::WebGPUShaderModule()
    : HybridObject(TAG), shaderModule_(nullptr) {}
WebGPUShaderModule::WebGPUShaderModule(WGPUShaderModule shaderModule)
    : HybridObject(TAG), shaderModule_(shaderModule) {}
WebGPUShaderModule::~WebGPUShaderModule() {
  if (shaderModule_) {
    wgpuShaderModuleRelease(shaderModule_);
  }
}

const WGPUShaderModule &WebGPUShaderModule::resource() const {
  return shaderModule_;
}

void WebGPUShaderModule::setLabel(const std::string &label) {
    WGPUStringView view { label.c_str(), WGPU_STRLEN };
    wgpuShaderModuleSetLabel(shaderModule_, view);
}

std::string WebGPUShaderModule::getLabel() {
    return NOT_IMPLEMENTED_LABEL_TEXT;
}
} // namespace margelo::nitro
