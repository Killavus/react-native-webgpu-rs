#pragma once

#include <memory>
#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {

using webgpurs::HybridNitroWGPUCommandBufferSpec;

class WebGPUCommandBuffer : public HybridNitroWGPUCommandBufferSpec {
public:
  WebGPUCommandBuffer();
  WebGPUCommandBuffer(WGPUCommandBuffer cmdBuffer);
  ~WebGPUCommandBuffer() override;
  
  const WGPUCommandBuffer& resource() const;
private:
  WGPUCommandBuffer cmdBuffer_;
};

} // namespace margelo::nitro
