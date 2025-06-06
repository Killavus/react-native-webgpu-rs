#include "WebGPUQueue.hpp"
#include "WebGPUCommandBuffer.hpp"
#include "WebGPUBuffer.hpp"

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

void WebGPUQueue::writeBuffer(const std::shared_ptr<HybridNitroWGPUBufferSpec>& buffer, double bufferOffset, const std::shared_ptr<ArrayBuffer>& data, std::optional<double> dataOffset, std::optional<double> size) {
  auto wgpuBuffer = dynamic_cast<WebGPUBuffer*>(buffer.get())->resource();
  
  wgpuQueueWriteBuffer(queue_,
                       wgpuBuffer,
                       (uint64_t) bufferOffset,
                       data.get()->data() + (uint64_t) dataOffset.value_or(0),
                       size.value_or(wgpuBufferGetSize(wgpuBuffer) - (size_t) dataOffset.value_or(0)));
}


}
