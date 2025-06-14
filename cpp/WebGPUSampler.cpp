#include "WebGPUSampler.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUSampler::WebGPUSampler() : HybridObject(TAG), sampler_(nullptr) {}
WebGPUSampler::WebGPUSampler(WGPUSampler sampler)
    : HybridObject(TAG), sampler_(sampler) {}
WebGPUSampler::~WebGPUSampler() {
  if (sampler_) {
    wgpuSamplerRelease(sampler_);
  }
}

const WGPUSampler &WebGPUSampler::resource() const { return sampler_; }

void WebGPUSampler::setLabel(const std::string &label) {
    WGPUStringView view { label.c_str(), WGPU_STRLEN };
    wgpuSamplerSetLabel(sampler_, view);
}

std::string WebGPUSampler::getLabel() {
    return NOT_IMPLEMENTED_LABEL_TEXT;
}

} // namespace margelo::nitro
