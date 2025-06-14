#pragma once

#include "DeviceInfo.hpp"
#include "HybridNitroWGPUBindGroupLayoutSpec.hpp"
#include "HybridNitroWGPUBindGroupSpec.hpp"
#include "HybridNitroWGPUBufferSpec.hpp"
#include "HybridNitroWGPUCommandEncoderSpec.hpp"
#include "HybridNitroWGPUComputePipelineSpec.hpp"
#include "HybridNitroWGPUDeviceSpec.hpp"
#include "HybridNitroWGPUPipelineLayoutSpec.hpp"
#include "HybridNitroWGPUQueueSpec.hpp"
#include "HybridNitroWGPUSamplerSpec.hpp"
#include "HybridNitroWGPUShaderModuleSpec.hpp"
#include "HybridNitroWGPUTextureSpec.hpp"

#include <memory>

#include "WebGPUQueue.hpp"
#include <webgpu/wgpu.h>

namespace margelo::nitro {

using webgpurs::HybridNitroWGPUBindGroupLayoutSpec;
using webgpurs::HybridNitroWGPUBindGroupSpec;
using webgpurs::HybridNitroWGPUBufferSpec;
using webgpurs::HybridNitroWGPUCommandEncoderSpec;
using webgpurs::HybridNitroWGPUComputePipelineSpec;
using webgpurs::HybridNitroWGPUDeviceSpec;
using webgpurs::HybridNitroWGPUQueueSpec;
using webgpurs::HybridNitroWGPUSamplerSpec;
using webgpurs::HybridNitroWGPUShaderModuleSpec;
using webgpurs::HybridNitroWGPUTextureSpec;

class WebGPUDevice : public HybridNitroWGPUDeviceSpec {
public:
  WebGPUDevice();
  WebGPUDevice(WGPUDevice device, const DeviceInfo &info);
  ~WebGPUDevice() override;

  std::shared_ptr<HybridNitroWGPUQueueSpec> getQueue() override;
  std::shared_ptr<HybridNitroWGPUBufferSpec>
  createBuffer(const BufferDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUSamplerSpec>
  createSampler(const std::optional<SamplerDescriptor> &descriptor) override;
  std::shared_ptr<HybridNitroWGPUShaderModuleSpec>
  createShaderModule(const ShaderModuleDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUCommandEncoderSpec> createCommandEncoder(
      const std::optional<CommandEncoderDescriptor> &descriptor) override;
  std::shared_ptr<HybridNitroWGPUTextureSpec>
  createTexture(const TextureDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUBindGroupLayoutSpec>
  createBindGroupLayout(const BindGroupLayoutDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUBindGroupSpec>
  createBindGroup(const BindGroupDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUPipelineLayoutSpec>
  createPipelineLayout(const PipelineLayoutDescriptor &descriptor) override;
  std::shared_ptr<HybridNitroWGPUComputePipelineSpec>
  createComputePipeline(const ComputePipelineDescriptor &descriptor) override;

  std::vector<DeviceFeature> getFeatures() override;
  RequiredLimits getLimits() override;
  DeviceInfo getAdapterInfo() override;
  bool getLost() override;
  void setLabel(const std::string &label) override;
  std::string getLabel() override;


private:
  WGPUDevice device_;
  DeviceInfo info_;
  std::shared_ptr<WebGPUQueue> queueInstance_;
};

} // namespace margelo::nitro
