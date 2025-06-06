#include "WebGPUDevice.hpp"
#include "WebGPUBuffer.hpp"
#include "WebGPUSampler.hpp"
#include "WebGPUShaderModule.hpp"

 namespace margelo::nitro {
 
 static WGPUAddressMode toWGPUAddressMode(const SamplerAddressMode& addressMode) {
   switch (addressMode) {
     case SamplerAddressMode::CLAMP_TO_EDGE:
       return WGPUAddressMode_ClampToEdge;
     case SamplerAddressMode::MIRROR_REPEAT:
       return WGPUAddressMode_MirrorRepeat;
     case SamplerAddressMode::REPEAT:
       return WGPUAddressMode_Repeat;
     default:
       return WGPUAddressMode_Undefined;
   }
 }
 
 static WGPUFilterMode toWGPUFilterMode(const SamplerFilterType& filterType) {
   switch (filterType) {
     case SamplerFilterType::LINEAR:
       return WGPUFilterMode_Linear;
     case SamplerFilterType::NEAREST:
       return WGPUFilterMode_Nearest;
     default:
       return WGPUFilterMode_Undefined;
   }
 }
 
 static WGPUMipmapFilterMode toWGPUMipmapFilterMode(const SamplerFilterType& filterType) {
   switch (filterType) {
     case SamplerFilterType::LINEAR:
       return WGPUMipmapFilterMode_Linear;
     case SamplerFilterType::NEAREST:
       return WGPUMipmapFilterMode_Nearest;
     default:
       return WGPUMipmapFilterMode_Undefined;
   }
 }
 
 WebGPUDevice::WebGPUDevice() : HybridObject(TAG), device_(nullptr), queueInstance_(nullptr) {}

 WebGPUDevice::WebGPUDevice(WGPUDevice device) : HybridObject(TAG), device_(device), queueInstance_(nullptr) {}

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
 
 std::shared_ptr<HybridNitroWGPUBufferSpec> WebGPUDevice::createBuffer(const BufferDescriptor& descriptor) {
   WGPUBufferDescriptor wgpuDescriptor {0};
   
   wgpuDescriptor.size = uint64_t(descriptor.size);
   wgpuDescriptor.mappedAtCreation = descriptor.mappedAtCreation ? 1 : 0;
   if (descriptor.label.has_value()) {
     wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
   } else {
     wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
   }
   
   wgpuDescriptor.usage = (WGPUBufferUsage) descriptor.usage;
   wgpuDescriptor.nextInChain = nullptr;
   
   WGPUBuffer buffer = wgpuDeviceCreateBuffer(device_, &wgpuDescriptor);
   
   return std::make_shared<WebGPUBuffer>(buffer);
 }
 
 std::shared_ptr<HybridNitroWGPUSamplerSpec> WebGPUDevice::createSampler(const SamplerDescriptor& descriptor) {
   WGPUSamplerDescriptor wgpuDescriptor {0};
   
   wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
   if (descriptor.label.has_value()) {
     wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
   }
   
   wgpuDescriptor.addressModeU = toWGPUAddressMode(descriptor.addressModeU.value_or(SamplerAddressMode::CLAMP_TO_EDGE));
   wgpuDescriptor.addressModeV = toWGPUAddressMode(descriptor.addressModeV.value_or(SamplerAddressMode::CLAMP_TO_EDGE));
   wgpuDescriptor.addressModeW = toWGPUAddressMode(descriptor.addressModeW.value_or(SamplerAddressMode::CLAMP_TO_EDGE));
   
   wgpuDescriptor.lodMaxClamp = descriptor.lodMaxClamp.value_or(32);
   wgpuDescriptor.lodMinClamp = descriptor.lodMinClamp.value_or(0);
   wgpuDescriptor.maxAnisotropy = descriptor.maxAnisotropy.value_or(1);
   
   wgpuDescriptor.magFilter = toWGPUFilterMode(descriptor.magFilter.value_or(SamplerFilterType::NEAREST));
   wgpuDescriptor.minFilter = toWGPUFilterMode(descriptor.minFilter.value_or(SamplerFilterType::NEAREST));
   wgpuDescriptor.mipmapFilter = toWGPUMipmapFilterMode(descriptor.mipmapFilter.value_or(SamplerFilterType::NEAREST));
   
   wgpuDescriptor.nextInChain = nullptr;
   
   WGPUSampler sampler = wgpuDeviceCreateSampler(device_, &wgpuDescriptor);
   
   return std::make_shared<WebGPUSampler>(sampler);
 }
 
 std::shared_ptr<HybridNitroWGPUShaderModuleSpec> WebGPUDevice::createShaderModule(const ShaderModuleDescriptor& descriptor) {
   WGPUShaderModuleDescriptor wgpuDescriptor = {0};
   
   const WGPUShaderSourceWGSL shaderCode {
     .code = { descriptor.code.c_str(), WGPU_STRLEN },
     .chain = { .sType = WGPUSType_ShaderSourceWGSL }
   };
   
   
   wgpuDescriptor.nextInChain = (const WGPUChainedStruct*) &shaderCode;
   
   wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
   if (descriptor.label.has_value()) {
     wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
   }
   
   WGPUShaderModule shaderModule { wgpuDeviceCreateShaderModule(device_, &wgpuDescriptor) };
   
   return std::make_shared<WebGPUShaderModule>(shaderModule);
 }


 
 } // namespace margelo::nitro
