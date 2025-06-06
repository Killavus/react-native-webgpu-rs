#pragma once

#include "HybridNitroWGPUAdapterSpec.hpp"
#include "HybridNitroWGPUInstanceSpec.hpp"
#include <memory>

extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {

using webgpurs::HybridNitroWGPUAdapterSpec;
using webgpurs::HybridNitroWGPUInstanceSpec;

class WebGPUInstance : public HybridNitroWGPUInstanceSpec {
public:
  WebGPUInstance();
  ~WebGPUInstance() override;

  void enumerateAdapters() override;
  std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUAdapterSpec>>>
  requestAdapter(const std::optional<AdapterDescriptor> &descriptor) override;
  void registerErrorHandler(
      const std::function<void(const std::string & /* errorMessage */)>
          &handler) override;

  TextureFormat getPreferredCanvasFormat() override;

  void callErrorHandler(const std::string &message);

private:
  WGPUInstance instance_;

  std::shared_ptr<std::function<void(const std::string &)>> errorHandler_;
};

} // namespace margelo::nitro
