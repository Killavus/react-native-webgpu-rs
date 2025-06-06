#pragma once

#include "HybridNitroWGPUInstanceSpec.hpp"
#include "HybridNitroWGPUAdapterSpec.hpp"
#include <memory>

extern "C" {
  #include <webgpu/wgpu.h>
}


namespace margelo::nitro {

using webgpurs::HybridNitroWGPUInstanceSpec;
using webgpurs::HybridNitroWGPUAdapterSpec;

class WebGPUInstance : public HybridNitroWGPUInstanceSpec {
public:
    WebGPUInstance();
    ~WebGPUInstance() override;

    void enumerateAdapters() override;
    std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUAdapterSpec>>> requestAdapter() override;
private:
    WGPUInstance instance_;
};

} // namespace margelo::nitro 
