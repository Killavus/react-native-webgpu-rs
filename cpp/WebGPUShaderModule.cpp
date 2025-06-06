#include "WebGPUShaderModule.hpp"

namespace margelo::nitro {
WebGPUShaderModule::WebGPUShaderModule() : HybridObject(TAG), shaderModule_(nullptr) {}
WebGPUShaderModule::WebGPUShaderModule(WGPUShaderModule shaderModule) : HybridObject(TAG), shaderModule_(shaderModule) {}
WebGPUShaderModule::~WebGPUShaderModule() {
  if (shaderModule_) {
    wgpuShaderModuleRelease(shaderModule_);
  }
}
}
