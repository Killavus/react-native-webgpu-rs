#pragma once

#include "HybridNitroWGPUAdapterSpec.hpp"
#include "HybridNitroWGPUDeviceSpec.hpp"
#include "WebGPUInstance.hpp"

#include <memory>
#include <webgpu/wgpu.h>

namespace margelo::nitro {

using webgpurs::HybridNitroWGPUAdapterSpec;
using webgpurs::HybridNitroWGPUDeviceSpec;

class WebGPUAdapter : public HybridNitroWGPUAdapterSpec {
public:
  WebGPUAdapter();
  WebGPUAdapter(WGPUAdapter adapter,
                const std::shared_ptr<WebGPUInstance> &instance);
  ~WebGPUAdapter() override;

  std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUDeviceSpec>>>
  requestDevice(const std::optional<DeviceDescriptor> &descriptor) override;

  RequiredLimits getLimits() override;
  std::vector<DeviceFeature> getFeatures() override;
  bool getIsFallbackAdapter() override;
  DeviceInfo getInfo() override;

protected:
private:
  WGPUAdapter adapter_;
  std::shared_ptr<WebGPUInstance> instance_;
};

} // namespace margelo::nitro
