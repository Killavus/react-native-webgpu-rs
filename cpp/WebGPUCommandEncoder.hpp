#pragma once

#include "HybridNitroWGPUBufferSpec.hpp"
#include "HybridNitroWGPUCommandBufferSpec.hpp"
#include "HybridNitroWGPUCommandEncoderSpec.hpp"
#include "HybridNitroWGPUComputePassEncoderSpec.hpp"
#include <memory>

extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUBufferSpec;
using webgpurs::HybridNitroWGPUCommandBufferSpec;
using webgpurs::HybridNitroWGPUCommandEncoderSpec;
using webgpurs::HybridNitroWGPUComputePassEncoderSpec;

class WebGPUCommandEncoder : public HybridNitroWGPUCommandEncoderSpec {
public:
  WebGPUCommandEncoder();
  WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder);
  ~WebGPUCommandEncoder() override;

  std::shared_ptr<HybridNitroWGPUComputePassEncoderSpec>
  beginComputePass(const ComputePassDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUCommandBufferSpec>
  finish(const std::optional<CommandBufferDescriptor> &descriptor) override;

  void copyBufferToBuffer(
      const std::shared_ptr<HybridNitroWGPUBufferSpec> &source,
      double sourceOffset,
      const std::shared_ptr<HybridNitroWGPUBufferSpec> &destination,
      double destinationOffset, double size) override;

  void clearBuffer(const std::shared_ptr<HybridNitroWGPUBufferSpec> &buffer,
                   std::optional<double> offset,
                   std::optional<double> size) override;

  void copyBufferToTexture(
      const BufferCopyDescriptor &source,
      const TextureCopyDescriptor &destination,
      const std::variant<std::vector<double>, TextureCopyExtentObject>
          &copySize) override;

  void copyTextureToBuffer(
      const TextureCopyDescriptor &source,
      const BufferCopyDescriptor &destination,
      const std::variant<std::vector<double>, TextureCopyExtentObject>
          &copySize) override;

  void copyTextureToTexture(
      const TextureCopyDescriptor &source,
      const TextureCopyDescriptor &destination,
      const std::variant<std::vector<double>, TextureCopyExtentObject>
          &copySize) override;
    void setLabel(const std::string &label) override;
    std::string getLabel() override;
private:
  WGPUCommandEncoder commandEncoder_;
};

} // namespace margelo::nitro
