#include "WebGPUDevice.hpp"
#include "WGPUTypeConversions.hpp"
#include "WebGPUBindGroup.hpp"
#include "WebGPUBindGroupLayout.hpp"
#include "WebGPUBuffer.hpp"
#include "WebGPUCommandEncoder.hpp"
#include "WebGPUComputePipeline.hpp"
#include "WebGPUPipelineLayout.hpp"
#include "WebGPUSampler.hpp"
#include "WebGPUShaderModule.hpp"
#include "WebGPUTexture.hpp"
#include "WebGPUTextureView.hpp"

namespace margelo::nitro {

WebGPUDevice::WebGPUDevice()
    : HybridObject(TAG), device_(nullptr), queueInstance_(nullptr) {}

WebGPUDevice::WebGPUDevice(WGPUDevice device, const DeviceInfo &info)
    : HybridObject(TAG), device_(device), queueInstance_(nullptr), info_(info) {

}

WebGPUDevice::~WebGPUDevice() {
  if (device_) {
    wgpuDeviceRelease(device_);
  }
}

std::shared_ptr<HybridNitroWGPUQueueSpec> WebGPUDevice::getQueue() {
  if (queueInstance_ == nullptr) {
    WGPUQueue queue = wgpuDeviceGetQueue(device_);
    queueInstance_ = std::make_shared<WebGPUQueue>(queue);
  }

  return queueInstance_;
}

std::shared_ptr<HybridNitroWGPUBufferSpec>
WebGPUDevice::createBuffer(const BufferDescriptor &descriptor) {
  WGPUBufferDescriptor wgpuDescriptor{0};

  wgpuDescriptor.size = uint64_t(descriptor.size);
  wgpuDescriptor.mappedAtCreation = descriptor.mappedAtCreation ? 1 : 0;
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  } else {
    wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  }

  wgpuDescriptor.usage = (WGPUBufferUsage)descriptor.usage;
  wgpuDescriptor.nextInChain = nullptr;

  WGPUBuffer buffer = wgpuDeviceCreateBuffer(device_, &wgpuDescriptor);

  return std::make_shared<WebGPUBuffer>(buffer, device_);
}

std::shared_ptr<HybridNitroWGPUSamplerSpec> WebGPUDevice::createSampler(
    const std::optional<SamplerDescriptor> &descriptorM) {
  WGPUSamplerDescriptor wgpuDescriptor{0};

  bool hasDescriptor = descriptorM.has_value();

  if (hasDescriptor) {
    auto descriptor = descriptorM.value();
    wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
    if (descriptor.label.has_value()) {
      wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
    }

    wgpuDescriptor.addressModeU = toWGPUAddressMode(
        descriptor.addressModeU.value_or(SamplerAddressMode::CLAMP_TO_EDGE));
    wgpuDescriptor.addressModeV = toWGPUAddressMode(
        descriptor.addressModeV.value_or(SamplerAddressMode::CLAMP_TO_EDGE));
    wgpuDescriptor.addressModeW = toWGPUAddressMode(
        descriptor.addressModeW.value_or(SamplerAddressMode::CLAMP_TO_EDGE));

    wgpuDescriptor.lodMaxClamp = descriptor.lodMaxClamp.value_or(32);
    wgpuDescriptor.lodMinClamp = descriptor.lodMinClamp.value_or(0);
    wgpuDescriptor.maxAnisotropy = descriptor.maxAnisotropy.value_or(1);

    wgpuDescriptor.magFilter = toWGPUFilterMode(
        descriptor.magFilter.value_or(SamplerFilterType::NEAREST));
    wgpuDescriptor.minFilter = toWGPUFilterMode(
        descriptor.minFilter.value_or(SamplerFilterType::NEAREST));
    wgpuDescriptor.mipmapFilter = toWGPUMipmapFilterMode(
        descriptor.mipmapFilter.value_or(SamplerFilterType::NEAREST));

    wgpuDescriptor.nextInChain = nullptr;
  }

  WGPUSampler sampler = wgpuDeviceCreateSampler(
      device_, hasDescriptor ? &wgpuDescriptor : nullptr);

  return std::make_shared<WebGPUSampler>(sampler);
}

std::shared_ptr<HybridNitroWGPUShaderModuleSpec>
WebGPUDevice::createShaderModule(const ShaderModuleDescriptor &descriptor) {
  WGPUShaderModuleDescriptor wgpuDescriptor = {0};

  const WGPUShaderSourceWGSL shaderCode{
      .code = {descriptor.code.c_str(), WGPU_STRLEN},
      .chain = {.sType = WGPUSType_ShaderSourceWGSL}};

  wgpuDescriptor.nextInChain = (const WGPUChainedStruct *)&shaderCode;

  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  WGPUShaderModule shaderModule{
      wgpuDeviceCreateShaderModule(device_, &wgpuDescriptor)};

  return std::make_shared<WebGPUShaderModule>(shaderModule);
}

std::shared_ptr<HybridNitroWGPUCommandEncoderSpec>
WebGPUDevice::createCommandEncoder(
    const std::optional<CommandEncoderDescriptor> &descriptorM) {

  bool hasDescriptor = descriptorM.has_value();
  WGPUCommandEncoderDescriptor wgpuDescriptor{0};

  if (hasDescriptor) {
    auto descriptor = descriptorM.value();
    wgpuDescriptor.nextInChain = nullptr;
    wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
    if (descriptor.label.has_value()) {
      wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
    }
  }

  WGPUCommandEncoder encoder{wgpuDeviceCreateCommandEncoder(
      device_, hasDescriptor ? &wgpuDescriptor : nullptr)};

  return std::make_shared<WebGPUCommandEncoder>(encoder);
}

std::shared_ptr<HybridNitroWGPUTextureSpec>
WebGPUDevice::createTexture(const TextureDescriptor &descriptor) {
  WGPUTextureDescriptor wgpuDescriptor{0};
  wgpuDescriptor.nextInChain = nullptr;

  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  if (std::holds_alternative<std::vector<double>>(descriptor.size)) {
    auto extentData = std::get<std::vector<double>>(descriptor.size);

    if (extentData.size() == 1) {
      wgpuDescriptor.size = {.width = (uint32_t)extentData[0],
                             .height = 1,
                             .depthOrArrayLayers = 1};
    } else if (extentData.size() == 2) {
      wgpuDescriptor.size = {.width = (uint32_t)extentData[0],
                             .height = (uint32_t)extentData[1],
                             .depthOrArrayLayers = 1};
    } else if (extentData.size() > 2) {
      wgpuDescriptor.size = {.width = (uint32_t)extentData[0],
                             .height = (uint32_t)extentData[1],
                             .depthOrArrayLayers = (uint32_t)extentData[2]};
    } else {
      wgpuDescriptor.size = {.width = 0, .height = 0, .depthOrArrayLayers = 1};
    }
  } else {
    auto extentData = std::get<TextureDescriptorSizeObject>(descriptor.size);

    wgpuDescriptor.size = {
        .width = (uint32_t)extentData.width,
        .height = (uint32_t)extentData.height.value_or(1),
        .depthOrArrayLayers =
            (uint32_t)extentData.depthOrArrayLayers.value_or(1)};
  }

  wgpuDescriptor.format = toWGPUTextureFormat(descriptor.format);
  wgpuDescriptor.mipLevelCount = (uint32_t)descriptor.mipLevelCount.value_or(1);
  wgpuDescriptor.sampleCount = (uint32_t)descriptor.sampleCount.value_or(1);
  wgpuDescriptor.usage = (uint64_t)descriptor.usage;
  wgpuDescriptor.dimension = toWGPUTextureDimension(
      descriptor.dimension.value_or(TextureDimension::_2D));

  wgpuDescriptor.viewFormatCount = 0;
  wgpuDescriptor.viewFormats = nullptr;

  std::vector<WGPUTextureFormat> viewFormats;
  if (descriptor.viewFormats.has_value()) {
    wgpuDescriptor.viewFormatCount = descriptor.viewFormats.value().size();
    viewFormats.reserve(descriptor.viewFormats.value().size());

    for (const auto &formatDesc : descriptor.viewFormats.value()) {
      viewFormats.push_back(toWGPUTextureFormat(formatDesc));
    }

    wgpuDescriptor.viewFormats = viewFormats.data();
  }

  WGPUTexture texture{wgpuDeviceCreateTexture(device_, &wgpuDescriptor)};
  return std::make_shared<WebGPUTexture>(texture);
}

std::shared_ptr<HybridNitroWGPUBindGroupLayoutSpec>
WebGPUDevice::createBindGroupLayout(
    const BindGroupLayoutDescriptor &descriptor) {
  WGPUBindGroupLayoutDescriptor wgpuDescriptor{0};

  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  std::vector<WGPUBindGroupLayoutEntry> wgpuEntries;
  wgpuEntries.reserve(descriptor.entries.size());

  for (const auto &entry : descriptor.entries) {
    WGPUBindGroupLayoutEntry wgpuEntry{0};

    if (std::holds_alternative<SamplerLayoutObject>(entry)) {
      auto samplerEntry = std::get<SamplerLayoutObject>(entry);

      wgpuEntry.visibility = (uint64_t)samplerEntry.visibility;
      wgpuEntry.nextInChain = nullptr;
      wgpuEntry.binding = (uint32_t)samplerEntry.binding;
      wgpuEntry.sampler = {
          .type = toWGPUSamplerBindingType(samplerEntry.sampler.type.value_or(
              SamplerLayoutObjectBindingType::FILTERING)),
          .nextInChain = nullptr};
    } else if (std::holds_alternative<TextureLayoutObject>(entry)) {
      auto textureEntry = std::get<TextureLayoutObject>(entry);
      wgpuEntry.visibility = (uint64_t)textureEntry.visibility;
      wgpuEntry.nextInChain = nullptr;
      wgpuEntry.binding = (uint32_t)textureEntry.binding;
      wgpuEntry.texture = {
          .sampleType =
              toWGPUTextureSampleType(textureEntry.texture.sampleType.value_or(
                  TextureLayoutObjectSampleType::FLOAT)),
          .viewDimension = toWGPUTextureViewDimension(
              textureEntry.texture.viewDimension.value_or(
                  TextureLayoutObjectViewDimension::_2D)),
          .multisampled = textureEntry.texture.multisampled.value_or(0),
          .nextInChain = nullptr};
    } else if (std::holds_alternative<BufferLayoutObject>(entry)) {
      auto bufferEntry = std::get<BufferLayoutObject>(entry);
      wgpuEntry.visibility = (uint64_t)bufferEntry.visibility;
      wgpuEntry.nextInChain = nullptr;
      wgpuEntry.binding = (uint32_t)bufferEntry.binding;
      wgpuEntry.buffer = {
          .nextInChain = nullptr,
          .minBindingSize =
              (uint32_t)bufferEntry.buffer.minBindingSize.value_or(0),
          .hasDynamicOffset = bufferEntry.buffer.hasDynamicOffset.value_or(0),
          .type = toWGPUBufferBindingType(bufferEntry.buffer.type.value_or(
              BufferLayoutObjectBindingType::UNIFORM))};
    } else if (std::holds_alternative<StorageTextureLayoutObject>(entry)) {
      auto textureEntry = std::get<StorageTextureLayoutObject>(entry);
      wgpuEntry.visibility = (uint64_t)textureEntry.visibility;
      wgpuEntry.nextInChain = nullptr;
      wgpuEntry.binding = (uint32_t)textureEntry.binding;
      wgpuEntry.storageTexture = {
          .format = toWGPUTextureFormat(textureEntry.storageTexture.format),
          .access = toWGPUStorageTextureAccess(
              textureEntry.storageTexture.access.value_or(
                  StorageTextureLayoutObjectAccess::WRITE_ONLY)),
          .viewDimension = toWGPUTextureViewDimension(
              textureEntry.storageTexture.viewDimension.value_or(
                  TextureLayoutObjectViewDimension::_2D)),
          .nextInChain = nullptr};
    } else {
      continue;
    }

    wgpuEntries.push_back(wgpuEntry);
  }

  wgpuDescriptor.entryCount = wgpuEntries.size();
  wgpuDescriptor.entries = wgpuEntries.data();

  WGPUBindGroupLayout layout{
      wgpuDeviceCreateBindGroupLayout(device_, &wgpuDescriptor)};

  return std::make_shared<WebGPUBindGroupLayout>(layout);
}

std::shared_ptr<HybridNitroWGPUBindGroupSpec>
WebGPUDevice::createBindGroup(const BindGroupDescriptor &descriptor) {
  WGPUBindGroupDescriptor wgpuDescriptor{0};

  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  std::vector<WGPUBindGroupEntry> wgpuEntries;
  wgpuEntries.reserve(descriptor.entries.size());
  for (const auto &entry : descriptor.entries) {
    WGPUBindGroupEntry wgpuEntry{0};
    wgpuEntry.binding = (uint32_t)entry.binding;
    wgpuEntry.nextInChain = nullptr;

    if (std::holds_alternative<BindGroupBufferBinding>(entry.resource)) {
      auto bufferResource = std::get<BindGroupBufferBinding>(entry.resource);
      auto wgpuBuffer =
          dynamic_cast<WebGPUBuffer *>(bufferResource.buffer.get())->resource();

      wgpuEntry.offset = (uint64_t)bufferResource.offset.value_or(0);
      wgpuEntry.size = (uint64_t)bufferResource.size.value_or(
          (double)wgpuBufferGetSize(wgpuBuffer));
      wgpuEntry.buffer = wgpuBuffer;
    } else if (std::holds_alternative<
                   std::shared_ptr<HybridNitroWGPUTextureViewSpec>>(
                   entry.resource)) {
      auto textureViewResource =
          std::get<std::shared_ptr<HybridNitroWGPUTextureViewSpec>>(
              entry.resource);

      wgpuEntry.textureView =
          dynamic_cast<WebGPUTextureView *>(textureViewResource.get())
              ->resource();
    } else if (std::holds_alternative<
                   std::shared_ptr<HybridNitroWGPUSamplerSpec>>(
                   entry.resource)) {
      auto samplerResource =
          std::get<std::shared_ptr<HybridNitroWGPUSamplerSpec>>(entry.resource);

      wgpuEntry.sampler =
          dynamic_cast<WebGPUSampler *>(samplerResource.get())->resource();
    } else {
      continue;
    }

    wgpuEntries.push_back(wgpuEntry);
  }

  wgpuDescriptor.layout =
      dynamic_cast<WebGPUBindGroupLayout *>(descriptor.layout.get())
          ->resource();
  wgpuDescriptor.entryCount = wgpuEntries.size();
  wgpuDescriptor.entries = wgpuEntries.data();

  WGPUBindGroup group{wgpuDeviceCreateBindGroup(device_, &wgpuDescriptor)};
  return std::make_shared<WebGPUBindGroup>(group);
}

std::shared_ptr<HybridNitroWGPUPipelineLayoutSpec>
WebGPUDevice::createPipelineLayout(const PipelineLayoutDescriptor &descriptor) {
  WGPUPipelineLayoutDescriptor wgpuDescriptor{0};

  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  wgpuDescriptor.nextInChain = nullptr;

  std::vector<WGPUBindGroupLayout> wgpuLayouts;
  wgpuLayouts.reserve(descriptor.bindGroupLayouts.size());

  for (const auto &layout : descriptor.bindGroupLayouts) {
    auto wgpuLayout = dynamic_cast<WebGPUBindGroupLayout *>(layout.get());
    wgpuLayouts.push_back(wgpuLayout->resource());
  }

  wgpuDescriptor.bindGroupLayoutCount = wgpuLayouts.size();
  wgpuDescriptor.bindGroupLayouts = wgpuLayouts.data();

  WGPUPipelineLayout layout{
      wgpuDeviceCreatePipelineLayout(device_, &wgpuDescriptor)};

  return std::make_shared<WebGPUPipelineLayout>(layout);
}

std::shared_ptr<HybridNitroWGPUComputePipelineSpec>
WebGPUDevice::createComputePipeline(
    const ComputePipelineDescriptor &descriptor) {
  WGPUComputePipelineDescriptor wgpuDescriptor{0};

  wgpuDescriptor.nextInChain = nullptr;
  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }
  wgpuDescriptor.layout =
      dynamic_cast<WebGPUPipelineLayout *>(descriptor.layout.get())->resource();
  wgpuDescriptor.compute.entryPoint = {nullptr, WGPU_STRLEN};
  if (descriptor.compute.entryPoint.has_value()) {
    wgpuDescriptor.compute.entryPoint = {
        descriptor.compute.entryPoint.value().c_str(), WGPU_STRLEN};
  }

  wgpuDescriptor.compute.nextInChain = nullptr;
  wgpuDescriptor.compute.module =
      dynamic_cast<WebGPUShaderModule *>(descriptor.compute.module.get())
          ->resource();

  wgpuDescriptor.compute.constantCount = 0;
  wgpuDescriptor.compute.constants = nullptr;

  std::vector<WGPUConstantEntry> wgpuEntries;
  if (descriptor.compute.constants.has_value()) {
    auto constantsMap = descriptor.compute.constants.value();

    wgpuEntries.reserve(constantsMap.size());

    for (const auto &entry : constantsMap) {
      WGPUConstantEntry wgpuEntry{0};
      auto key = entry.first;
      auto value = entry.second;

      wgpuEntry.nextInChain = nullptr;
      wgpuEntry.key = {key.c_str(), WGPU_STRLEN};

      if (std::holds_alternative<bool>(value)) {
        auto boolValue = std::get<bool>(value);
        wgpuEntry.value = boolValue ? 1.0 : 0.0;
      } else {
        auto doubleValue = std::get<double>(value);
        wgpuEntry.value = doubleValue;
      }

      wgpuEntries.push_back(wgpuEntry);
    }

    wgpuDescriptor.compute.constantCount = wgpuEntries.size();
    wgpuDescriptor.compute.constants = wgpuEntries.data();
  }

  WGPUComputePipeline pipeline{
      wgpuDeviceCreateComputePipeline(device_, &wgpuDescriptor)};

  return std::make_shared<WebGPUComputePipeline>(pipeline);
}

std::vector<DeviceFeature> WebGPUDevice::getFeatures() {
  WGPUSupportedFeatures wgpuFeatures;
  wgpuDeviceGetFeatures(device_, &wgpuFeatures);
  std::vector<DeviceFeature> features;
  features.reserve(wgpuFeatures.featureCount);

  for (size_t i = 0; i < wgpuFeatures.featureCount; i++) {
    features.push_back(toNitroDeviceFeature(wgpuFeatures.features[i]));
  }

  return features;
};

RequiredLimits WebGPUDevice::getLimits() {
  RequiredLimits limits;

  WGPUNativeLimits wgpuNativeLimits{
      .chain = {
          .sType = (WGPUSType)WGPUSType_NativeLimits,
      }};

  WGPULimits wgpuLimits{.nextInChain = &wgpuNativeLimits.chain};

  wgpuDeviceGetLimits(device_, &wgpuLimits);

  limits.maxTextureDimension1D = wgpuLimits.maxTextureDimension1D;
  limits.maxTextureDimension2D = wgpuLimits.maxTextureDimension2D;
  limits.maxTextureDimension3D = wgpuLimits.maxTextureDimension3D;
  limits.maxTextureArrayLayers = wgpuLimits.maxTextureArrayLayers;
  limits.maxBindGroups = wgpuLimits.maxBindGroups;
  limits.maxBindingsPerBindGroup = wgpuLimits.maxBindingsPerBindGroup;
  limits.maxDynamicUniformBuffersPerPipelineLayout =
      wgpuLimits.maxDynamicUniformBuffersPerPipelineLayout;
  limits.maxDynamicStorageBuffersPerPipelineLayout =
      wgpuLimits.maxDynamicStorageBuffersPerPipelineLayout;
  limits.maxSampledTexturesPerShaderStage =
      wgpuLimits.maxSampledTexturesPerShaderStage;
  limits.maxSamplersPerShaderStage = wgpuLimits.maxSamplersPerShaderStage;
  limits.maxStorageBuffersPerShaderStage =
      wgpuLimits.maxStorageBuffersPerShaderStage;
  limits.maxStorageTexturesPerShaderStage =
      wgpuLimits.maxStorageTexturesPerShaderStage;
  limits.maxUniformBuffersPerShaderStage =
      wgpuLimits.maxUniformBuffersPerShaderStage;
  limits.maxUniformBufferBindingSize = wgpuLimits.maxUniformBufferBindingSize;
  limits.maxStorageBufferBindingSize = wgpuLimits.maxStorageBufferBindingSize;
  limits.minUniformBufferOffsetAlignment =
      wgpuLimits.minUniformBufferOffsetAlignment;
  limits.minStorageBufferOffsetAlignment =
      wgpuLimits.minStorageBufferOffsetAlignment;
  limits.maxVertexBuffers = wgpuLimits.maxVertexBuffers;
  limits.maxBufferSize = wgpuLimits.maxBufferSize;
  limits.maxVertexAttributes = wgpuLimits.maxVertexAttributes;
  limits.maxVertexBufferArrayStride = wgpuLimits.maxVertexBufferArrayStride;
  limits.maxInterStageShaderComponents =
      0; // TODO: Not supported by wgpu-native.
  limits.maxInterStageShaderVariables = wgpuLimits.maxInterStageShaderVariables;
  limits.maxColorAttachments = wgpuLimits.maxColorAttachments;
  limits.maxColorAttachmentBytesPerSample =
      wgpuLimits.maxColorAttachmentBytesPerSample;
  limits.maxComputeWorkgroupStorageSize =
      wgpuLimits.maxComputeWorkgroupStorageSize;
  limits.maxComputeInvocationsPerWorkgroup =
      wgpuLimits.maxComputeInvocationsPerWorkgroup;
  limits.maxComputeWorkgroupSizeX = wgpuLimits.maxComputeWorkgroupSizeX;
  limits.maxComputeWorkgroupSizeY = wgpuLimits.maxComputeWorkgroupSizeY;
  limits.maxComputeWorkgroupSizeZ = wgpuLimits.maxComputeWorkgroupSizeZ;
  limits.maxComputeWorkgroupsPerDimension =
      wgpuLimits.maxComputeWorkgroupsPerDimension;
  limits.ext_maxPushConstantSize = wgpuNativeLimits.maxPushConstantSize;
  limits.ext_maxNonSamplerBindings = wgpuNativeLimits.maxNonSamplerBindings;

  return limits;
};

DeviceInfo WebGPUDevice::getAdapterInfo() { return info_; };

bool WebGPUDevice::getLost() { return false; };

} // namespace margelo::nitro
