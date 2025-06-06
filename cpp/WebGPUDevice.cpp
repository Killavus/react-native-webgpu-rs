 #include "WebGPUDevice.hpp"
#include "WebGPUBuffer.hpp"

 namespace margelo::nitro {
 
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
 
 } // namespace margelo::nitro
