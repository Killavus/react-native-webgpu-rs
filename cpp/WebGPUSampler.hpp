#pragma once

#include <memory>
#include "HybridNitroWGPUSamplerSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUSamplerSpec;

class WebGPUSampler : public HybridNitroWGPUSamplerSpec {
public:
  WebGPUSampler();
  WebGPUSampler(WGPUSampler buffer);
  ~WebGPUSampler() override;
private:
  WGPUSampler sampler_;
};

} // namespace margelo::nitro
