#include "WebGPUComputePipeline.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUComputePipeline::WebGPUComputePipeline()
    : HybridObject(TAG), pipeline_(nullptr) {}
WebGPUComputePipeline::WebGPUComputePipeline(WGPUComputePipeline pipeline)
    : HybridObject(TAG), pipeline_(pipeline) {}
WebGPUComputePipeline::~WebGPUComputePipeline() {
  if (pipeline_) {
    wgpuComputePipelineRelease(pipeline_);
  }
}

const WGPUComputePipeline &WebGPUComputePipeline::resource() const {
  return pipeline_;
}

    void WebGPUComputePipeline::setLabel(const std::string &label) {
        WGPUStringView view { label.c_str(), WGPU_STRLEN };
        wgpuComputePipelineSetLabel(pipeline_, view);
    }

    std::string WebGPUComputePipeline::getLabel() {
        return NOT_IMPLEMENTED_LABEL_TEXT;
    }

} // namespace margelo::nitro
