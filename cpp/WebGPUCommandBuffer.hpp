#pragma once

#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {

using webgpurs::HybridNitroWGPUCommandBufferSpec;

class WebGPUCommandBuffer : public HybridNitroWGPUCommandBufferSpec {
public:
  WebGPUCommandBuffer();
  WebGPUCommandBuffer(WGPUCommandBuffer cmdBuffer);
  ~WebGPUCommandBuffer() override;

  const WGPUCommandBuffer &resource() const;
  void setLabel(const std::string &label) override;
  std::string getLabel() override;

private:
  WGPUCommandBuffer cmdBuffer_;
};

} // namespace margelo::nitro
