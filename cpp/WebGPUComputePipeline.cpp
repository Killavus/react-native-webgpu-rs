#include "WebGPUComputePipeline.hpp"

namespace margelo::nitro {
WebGPUComputePipeline::WebGPUComputePipeline() : HybridObject(TAG), pipeline_(nullptr) {}
WebGPUComputePipeline::WebGPUComputePipeline(WGPUComputePipeline pipeline) : HybridObject(TAG), pipeline_(pipeline) {}
WebGPUComputePipeline::~WebGPUComputePipeline() {
  if (pipeline_) {
    wgpuComputePipelineRelease(pipeline_);
  }
}

const WGPUComputePipeline& WebGPUComputePipeline::resource() const { return pipeline_; }
}
