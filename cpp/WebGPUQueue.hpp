#pragma once

#include <memory>
#include "HybridNitroWGPUQueueSpec.hpp"
#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include "HybridNitroWGPUBufferSpec.hpp"

#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUQueueSpec;
using webgpurs::HybridNitroWGPUCommandBufferSpec;
using webgpurs::HybridNitroWGPUBufferSpec;

class WebGPUQueue : public HybridNitroWGPUQueueSpec {
public:
  WebGPUQueue();
  WebGPUQueue(WGPUQueue queue);
  ~WebGPUQueue() override;
  
  void submit(const std::vector<std::shared_ptr<HybridNitroWGPUCommandBufferSpec>>& commandBuffers) override;
  void writeBuffer(const std::shared_ptr<HybridNitroWGPUBufferSpec>& buffer, double bufferOffset, const std::shared_ptr<ArrayBuffer>& data, std::optional<double> dataOffset, std::optional<double> size) override;
private:
  WGPUQueue queue_;
};

} // namespace margelo::nitro
