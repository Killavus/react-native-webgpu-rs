#pragma once

#include <memory>
#include "HybridNitroWGPUQueueSpec.hpp"
#include "HybridNitroWGPUCommandBufferSpec.hpp"

#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUQueueSpec;
using webgpurs::HybridNitroWGPUCommandBufferSpec;

class WebGPUQueue : public HybridNitroWGPUQueueSpec {
public:
  WebGPUQueue();
  WebGPUQueue(WGPUQueue queue);
  ~WebGPUQueue() override;
  
  void submit(const std::vector<std::shared_ptr<HybridNitroWGPUCommandBufferSpec>>& commandBuffers) override;
private:
  WGPUQueue queue_;
};

} // namespace margelo::nitro
