#include "WebGPUComputePassEncoder.hpp"
#include "WebGPUBindGroup.hpp"
#include "WebGPUComputePipeline.hpp"

namespace margelo::nitro {
WebGPUComputePassEncoder::WebGPUComputePassEncoder()
    : HybridObject(TAG), encoder_(nullptr) {}
WebGPUComputePassEncoder::WebGPUComputePassEncoder(
    WGPUComputePassEncoder encoder)
    : HybridObject(TAG), encoder_(encoder) {}
WebGPUComputePassEncoder::~WebGPUComputePassEncoder() {
  if (encoder_) {
    wgpuComputePassEncoderRelease(encoder_);
  }
}

const WGPUComputePassEncoder &WebGPUComputePassEncoder::resource() const {
  return encoder_;
}

void WebGPUComputePassEncoder::setPipeline(
    const std::shared_ptr<HybridNitroWGPUComputePipelineSpec> &pipeline) {
  wgpuComputePassEncoderSetPipeline(
      encoder_,
      dynamic_cast<WebGPUComputePipeline *>(pipeline.get())->resource());
};

void WebGPUComputePassEncoder::setBindGroup(
    double index,
    const std::optional<std::shared_ptr<HybridNitroWGPUBindGroupSpec>>
        &bindGroup) {
  // TODO: Support dynamic offsets.
  if (bindGroup.has_value()) {
    wgpuComputePassEncoderSetBindGroup(
        encoder_, (uint32_t)index,
        dynamic_cast<WebGPUBindGroup *>(bindGroup.value().get())->resource(), 0,
        nullptr);
  } else {
    wgpuComputePassEncoderSetBindGroup(encoder_, (uint32_t)index, nullptr, 0,
                                       nullptr);
  }
};

void WebGPUComputePassEncoder::dispatchWorkgroups(double workgroupCountX,
                                                  double workgroupCountY,
                                                  double workgroupCountZ) {
  wgpuComputePassEncoderDispatchWorkgroups(encoder_, (uint32_t)workgroupCountX,
                                           (uint32_t)workgroupCountY,
                                           (uint32_t)workgroupCountZ);
};

void WebGPUComputePassEncoder::end() { wgpuComputePassEncoderEnd(encoder_); };

} // namespace margelo::nitro
