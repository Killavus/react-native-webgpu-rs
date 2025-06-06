#pragma once

#include <memory>
#include "HybridNitroWGPUQueueSpec.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUQueueSpec;

class WebGPUQueue : public HybridNitroWGPUQueueSpec {
public:
  WebGPUQueue();
  WebGPUQueue(WGPUQueue queue);
  ~WebGPUQueue() override;
private:
  WGPUQueue queue_;
};

} // namespace margelo::nitro
