#pragma once
extern "C" {
#include <webgpu/wgpu.h>
}


#include "BufferLayoutObjectBindingType.hpp"
#include "DeviceFeature.hpp"
#include "SamplerAddressMode.hpp"
#include "SamplerFilterType.hpp"
#include "SamplerLayoutObjectBindingType.hpp"
#include "StorageTextureLayoutObjectAccess.hpp"
#include "TextureAspect.hpp"
#include "TextureDimension.hpp"
#include "TextureFormat.hpp"
#include "TextureLayoutObjectSampleType.hpp"
#include "TextureLayoutObjectViewDimension.hpp"

namespace margelo::nitro {
WGPUStorageTextureAccess
toWGPUStorageTextureAccess(const StorageTextureLayoutObjectAccess &access);
WGPUBufferBindingType
toWGPUBufferBindingType(const BufferLayoutObjectBindingType &bindingType);
WGPUTextureSampleType
toWGPUTextureSampleType(const TextureLayoutObjectSampleType &sampleType);
WGPUTextureViewDimension toWGPUTextureViewDimension(
    const TextureLayoutObjectViewDimension &viewDimension);
WGPUSamplerBindingType
toWGPUSamplerBindingType(const SamplerLayoutObjectBindingType &bindingType);
WGPUMipmapFilterMode
toWGPUMipmapFilterMode(const SamplerFilterType &filterType);
WGPUFilterMode toWGPUFilterMode(const SamplerFilterType &filterType);
WGPUTextureDimension toWGPUTextureDimension(const TextureDimension &dimension);
WGPUTextureFormat toWGPUTextureFormat(const TextureFormat &format);
WGPUAddressMode toWGPUAddressMode(const SamplerAddressMode &addressMode);
WGPUTextureAspect toWGPUTextureAspect(const TextureAspect &aspect);
TextureDimension toNitroTextureDimension(const WGPUTextureDimension &dimension);
TextureFormat toNitroTextureFormat(const WGPUTextureFormat &dimension);
WGPUFeatureName toWGPUFeatureName(const DeviceFeature &feature);
DeviceFeature toNitroDeviceFeature(const WGPUFeatureName &feature);
} // namespace margelo::nitro
