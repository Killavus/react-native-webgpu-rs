#pragma once

#include "HybridNitroWGPUSamplerSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUSamplerSpec;

class WebGPUSampler : public HybridNitroWGPUSamplerSpec {
public:
  WebGPUSampler();
  WebGPUSampler(WGPUSampler buffer);
  ~WebGPUSampler() override;

  const WGPUSampler &resource() const;

  void setLabel(const std::string &label) override;
  std::string getLabel() override;

private:
  WGPUSampler sampler_;
};

} // namespace margelo::nitro
