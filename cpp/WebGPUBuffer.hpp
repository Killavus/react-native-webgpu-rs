#pragma once

#include "HybridNitroWGPUBufferSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBufferSpec;

class WebGPUBuffer : public HybridNitroWGPUBufferSpec {
public:
  WebGPUBuffer();
  WebGPUBuffer(WGPUBuffer buffer, WGPUDevice device);
  ~WebGPUBuffer() override;

  const WGPUBuffer &resource() const;
  std::shared_ptr<Promise<void>> mapAsync(double mode,
                                          std::optional<double> offset,
                                          std::optional<double> size) override;
  std::shared_ptr<ArrayBuffer>
  getMappedRange(std::optional<double> offset,
                 std::optional<double> size) override;

  BufferMapState getMapState() override;

  double getSize() override;
  double getUsage() override;

  void setLabel(const std::string &label) override;
  std::string getLabel() override;

  void unmap() override;

private:
  WGPUBuffer buffer_;
  WGPUDevice device_;
};

} // namespace margelo::nitro
