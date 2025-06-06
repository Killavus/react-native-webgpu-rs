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
  
  const WGPUBuffer& resource() const;
private:
  WGPUBuffer buffer_;
};

} // namespace margelo::nitro
