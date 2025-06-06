#include "WebGPUSampler.hpp"

namespace margelo::nitro {
WebGPUSampler::WebGPUSampler() : HybridObject(TAG), sampler_(nullptr) {}
WebGPUSampler::WebGPUSampler(WGPUSampler sampler) : HybridObject(TAG), sampler_(sampler) {}
WebGPUSampler::~WebGPUSampler() {
  if (sampler_) {
    wgpuSamplerRelease(sampler_);
  }
}
}
