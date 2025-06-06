#pragma once

#include "HybridNitroWGPUSamplerSpec.hpp"
#include <memory>
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUSamplerSpec;

class WebGPUSampler : public HybridNitroWGPUSamplerSpec {
public:
  WebGPUSampler();
  WebGPUSampler(WGPUSampler buffer);
  ~WebGPUSampler() override;

  const WGPUSampler &resource() const;

private:
  WGPUSampler sampler_;
};

} // namespace margelo::nitro
