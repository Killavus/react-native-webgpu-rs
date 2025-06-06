#pragma once

#include <memory>
#include "HybridNitroWGPUCommandEncoderSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUCommandEncoderSpec;

class WebGPUCommandEncoder : public HybridNitroWGPUCommandEncoderSpec {
public:
  WebGPUCommandEncoder();
  WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder);
  ~WebGPUCommandEncoder() override;
private:
  WGPUCommandEncoder commandEncoder_;
};

} // namespace margelo::nitro
