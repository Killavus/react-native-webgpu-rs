#include "WebGPUQueue.hpp"
#include "WebGPUCommandBuffer.hpp"

namespace margelo::nitro {
WebGPUQueue::WebGPUQueue() : HybridObject(TAG), queue_(nullptr) {}
WebGPUQueue::WebGPUQueue(WGPUQueue queue) : HybridObject(TAG), queue_(queue) {}
WebGPUQueue::~WebGPUQueue() {}

void WebGPUQueue::submit(const std::vector<std::shared_ptr<HybridNitroWGPUCommandBufferSpec>>& commandBuffers) {
  std::vector<WGPUCommandBuffer> wgpuBuffers;
  wgpuBuffers.reserve(commandBuffers.size());
  
  for (const auto& commandBuffer : commandBuffers) {
    auto wgpuBuffer = dynamic_cast<WebGPUCommandBuffer*>(commandBuffer.get())->resource();
    
    wgpuBuffers.push_back(wgpuBuffer);
  }
  
  wgpuQueueSubmit(queue_, wgpuBuffers.size(), wgpuBuffers.data());
}

}
