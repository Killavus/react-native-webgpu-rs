 #pragma once

 #include <memory>
 #include "HybridNitroWGPUDeviceSpec.hpp"
 #include "HybridNitroWGPUBufferSpec.hpp"
 #include "HybridNitroWGPUQueueSpec.hpp"
 #include "HybridNitroWGPUSamplerSpec.hpp"
 #include "HybridNitroWGPUShaderModuleSpec.hpp"


 #include "WebGPUQueue.hpp"
 #include <webgpu/wgpu.h>

 namespace margelo::nitro {

 using webgpurs::HybridNitroWGPUDeviceSpec;
 using webgpurs::HybridNitroWGPUQueueSpec;
 using webgpurs::HybridNitroWGPUBufferSpec;
 using webgpurs::HybridNitroWGPUSamplerSpec;
 using webgpurs::HybridNitroWGPUShaderModuleSpec;


 class WebGPUDevice : public HybridNitroWGPUDeviceSpec {
 public:
   WebGPUDevice();
   WebGPUDevice(WGPUDevice device);
   ~WebGPUDevice() override;
   
   std::shared_ptr<HybridNitroWGPUQueueSpec> getQueue() override;
   std::shared_ptr<HybridNitroWGPUBufferSpec> createBuffer(const BufferDescriptor& descriptor) override;
   std::shared_ptr<HybridNitroWGPUSamplerSpec> createSampler(const SamplerDescriptor& descriptor) override;
   std::shared_ptr<HybridNitroWGPUShaderModuleSpec> createShaderModule(const ShaderModuleDescriptor& descriptor) override;
   
 private:
   WGPUDevice device_;
   std::shared_ptr<WebGPUQueue> queueInstance_;
 };

 } // namespace margelo::nitro 
