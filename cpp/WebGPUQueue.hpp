#pragma once

#include "HybridNitroWGPUBufferSpec.hpp"
#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include "HybridNitroWGPUQueueSpec.hpp"
#include <memory>

#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBufferSpec;
using webgpurs::HybridNitroWGPUCommandBufferSpec;
using webgpurs::HybridNitroWGPUQueueSpec;

class WebGPUQueue : public HybridNitroWGPUQueueSpec {
public:
  WebGPUQueue();
  WebGPUQueue(WGPUQueue queue);
  ~WebGPUQueue() override;

  void
  submit(const std::vector<std::shared_ptr<HybridNitroWGPUCommandBufferSpec>>
             &commandBuffers) override;
  void writeBuffer(const std::shared_ptr<HybridNitroWGPUBufferSpec> &buffer,
                   double bufferOffset,
                   const std::shared_ptr<ArrayBuffer> &data,
                   std::optional<double> dataOffset,
                   std::optional<double> size) override;
  void writeTexture(const WriteTextureDestination &source,
                    const std::shared_ptr<ArrayBuffer> &data,
                    const WriteTextureDataLayout &dataLayout,
                    const std::variant<WriteTextureExtentObject,
                                       std::vector<double>> &size) override;

private:
  WGPUQueue queue_;
};

} // namespace margelo::nitro
