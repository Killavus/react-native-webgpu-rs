#pragma once

#include <memory>
#include "HybridNitroWGPUBufferSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBufferSpec;

class WebGPUBuffer : public HybridNitroWGPUBufferSpec {
public:
  WebGPUBuffer();
  WebGPUBuffer(WGPUBuffer buffer);
  ~WebGPUBuffer() override;
private:
  WGPUBuffer buffer_;
};

} // namespace margelo::nitro
