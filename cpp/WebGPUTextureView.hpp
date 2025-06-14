#pragma once

#include "HybridNitroWGPUTextureViewSpec.hpp"
#include <memory>
extern "C" {
#include <webgpu/wgpu.h>
}

namespace margelo::nitro {
using webgpurs::HybridNitroWGPUTextureViewSpec;

class WebGPUTextureView : public HybridNitroWGPUTextureViewSpec {
public:
  WebGPUTextureView();
  WebGPUTextureView(WGPUTextureView textureView);
  ~WebGPUTextureView() override;

  const WGPUTextureView &resource() const;
  void setLabel(const std::string &label) override;
  std::string getLabel() override;


private:
  WGPUTextureView textureView_;
};

} // namespace margelo::nitro
