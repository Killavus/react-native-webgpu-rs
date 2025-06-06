#include "WebGPUDevice.hpp"
#include "WebGPUBindGroupLayout.hpp"
#include "WebGPUBuffer.hpp"
#include "WebGPUCommandEncoder.hpp"
#include "WebGPUSampler.hpp"
#include "WebGPUShaderModule.hpp"
#include "WebGPUTexture.hpp"
#include "WebGPUTextureView.hpp"
#include "WebGPUBindGroup.hpp"
#include "WebGPUPipelineLayout.hpp"
#include "WebGPUComputePipeline.hpp"

namespace margelo::nitro {

static WGPUAddressMode
toWGPUAddressMode(const SamplerAddressMode &addressMode) {
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

static WGPUTextureFormat toWGPUTextureFormat(const TextureFormat &format) {
  switch (format) {
  case TextureFormat::R8UNORM:
    return WGPUTextureFormat_R8Unorm;
  case TextureFormat::R8SNORM:
    return WGPUTextureFormat_R8Snorm;
  case TextureFormat::R8UINT:
    return WGPUTextureFormat_R8Uint;
  case TextureFormat::R8SINT:
    return WGPUTextureFormat_R8Sint;
  case TextureFormat::R16UNORM:
    return (WGPUTextureFormat)WGPUNativeTextureFormat_R16Unorm;
  case TextureFormat::R16SNORM:
    return (WGPUTextureFormat)WGPUNativeTextureFormat_R16Snorm;
  case TextureFormat::R16UINT:
    return WGPUTextureFormat_R16Uint;
  case TextureFormat::R16SINT:
    return WGPUTextureFormat_R16Sint;
  case TextureFormat::R16FLOAT:
    return WGPUTextureFormat_R16Float;
  case TextureFormat::RG8UNORM:
    return WGPUTextureFormat_RG8Unorm;
  case TextureFormat::RG8SNORM:
    return WGPUTextureFormat_RG8Snorm;
  case TextureFormat::RG8UINT:
    return WGPUTextureFormat_RG8Uint;
  case TextureFormat::RG8SINT:
    return WGPUTextureFormat_RG8Sint;
  case TextureFormat::R32UINT:
    return WGPUTextureFormat_R32Uint;
  case TextureFormat::R32SINT:
    return WGPUTextureFormat_R32Sint;
  case TextureFormat::R32FLOAT:
    return WGPUTextureFormat_R32Float;
  case TextureFormat::RG16UNORM:
    return (WGPUTextureFormat)WGPUNativeTextureFormat_Rg16Unorm;
  case TextureFormat::RG16SNORM:
    return (WGPUTextureFormat)WGPUNativeTextureFormat_Rg16Snorm;
  case TextureFormat::RG16UINT:
    return WGPUTextureFormat_RG16Uint;
  case TextureFormat::RG16SINT:
    return WGPUTextureFormat_RG16Sint;
  case TextureFormat::RG16FLOAT:
    return WGPUTextureFormat_RG16Float;
  case TextureFormat::RGBA8UNORM:
    return WGPUTextureFormat_RGBA8Unorm;
  case TextureFormat::RGBA8UNORM_SRGB:
    return WGPUTextureFormat_RGBA8UnormSrgb;
  case TextureFormat::RGBA8SNORM:
    return WGPUTextureFormat_RGBA8Snorm;
  case TextureFormat::RGBA8UINT:
    return WGPUTextureFormat_RGBA8Uint;
  case TextureFormat::RGBA8SINT:
    return WGPUTextureFormat_RGBA8Sint;
  case TextureFormat::BGRA8UNORM:
    return WGPUTextureFormat_BGRA8Unorm;
  case TextureFormat::BGRA8UNORM_SRGB:
    return WGPUTextureFormat_BGRA8UnormSrgb;
  case TextureFormat::RGB9E5UFLOAT:
    return WGPUTextureFormat_RGB9E5Ufloat;
  case TextureFormat::RGB10A2UINT:
    return WGPUTextureFormat_RGB10A2Uint;
  case TextureFormat::RGB10A2UNORM:
    return WGPUTextureFormat_RGB10A2Unorm;
  case TextureFormat::RG11B10UFLOAT:
    return WGPUTextureFormat_RG11B10Ufloat;
  case TextureFormat::RG32UINT:
    return WGPUTextureFormat_RG32Uint;
  case TextureFormat::RG32SINT:
    return WGPUTextureFormat_RG32Sint;
  case TextureFormat::RG32FLOAT:
    return WGPUTextureFormat_RG32Float;
  case TextureFormat::RGBA16UNORM:
    return (WGPUTextureFormat)WGPUNativeTextureFormat_Rgba16Unorm;
  case TextureFormat::RGBA16SNORM:
    return (WGPUTextureFormat)WGPUNativeTextureFormat_Rgba16Snorm;
  case TextureFormat::RGBA16UINT:
    return WGPUTextureFormat_RGBA16Uint;
  case TextureFormat::RGBA16SINT:
    return WGPUTextureFormat_RGBA16Sint;
  case TextureFormat::RGBA16FLOAT:
    return WGPUTextureFormat_RGBA16Float;
  case TextureFormat::RGBA32UINT:
    return WGPUTextureFormat_RGBA32Uint;
  case TextureFormat::RGBA32SINT:
    return WGPUTextureFormat_RGBA32Sint;
  case TextureFormat::RGBA32FLOAT:
    return WGPUTextureFormat_RGBA32Float;
  case TextureFormat::STENCIL8:
    return WGPUTextureFormat_Stencil8;
  case TextureFormat::DEPTH16UNORM:
    return WGPUTextureFormat_Depth16Unorm;
  case TextureFormat::DEPTH24PLUS:
    return WGPUTextureFormat_Depth24Plus;
  case TextureFormat::DEPTH24PLUS_STENCIL8:
    return WGPUTextureFormat_Depth24PlusStencil8;
  case TextureFormat::DEPTH32FLOAT:
    return WGPUTextureFormat_Depth32Float;
  case TextureFormat::DEPTH32FLOAT_STENCIL8:
    return WGPUTextureFormat_Depth32FloatStencil8;
  case TextureFormat::BC1_RGBA_UNORM:
    return WGPUTextureFormat_BC1RGBAUnorm;
  case TextureFormat::BC1_RGBA_UNORM_SRGB:
    return WGPUTextureFormat_BC1RGBAUnormSrgb;
  case TextureFormat::BC2_RGBA_UNORM:
    return WGPUTextureFormat_BC2RGBAUnorm;
  case TextureFormat::BC2_RGBA_UNORM_SRGB:
    return WGPUTextureFormat_BC2RGBAUnormSrgb;
  case TextureFormat::BC3_RGBA_UNORM:
    return WGPUTextureFormat_BC3RGBAUnorm;
  case TextureFormat::BC3_RGBA_UNORM_SRGB:
    return WGPUTextureFormat_BC3RGBAUnormSrgb;
  case TextureFormat::BC4_R_UNORM:
    return WGPUTextureFormat_BC4RUnorm;
  case TextureFormat::BC4_R_SNORM:
    return WGPUTextureFormat_BC4RSnorm;
  case TextureFormat::BC5_RG_UNORM:
    return WGPUTextureFormat_BC5RGUnorm;
  case TextureFormat::BC5_RG_SNORM:
    return WGPUTextureFormat_BC5RGSnorm;
  case TextureFormat::BC6H_RGB_UFLOAT:
    return WGPUTextureFormat_BC6HRGBUfloat;
  case TextureFormat::BC6H_RGB_FLOAT:
    return WGPUTextureFormat_BC6HRGBFloat;
  case TextureFormat::BC7_RGBA_UNORM:
    return WGPUTextureFormat_BC7RGBAUnorm;
  case TextureFormat::BC7_RGBA_UNORM_SRGB:
    return WGPUTextureFormat_BC7RGBAUnormSrgb;
  case TextureFormat::ETC2_RGB8UNORM:
    return WGPUTextureFormat_ETC2RGB8Unorm;
  case TextureFormat::ETC2_RGB8UNORM_SRGB:
    return WGPUTextureFormat_ETC2RGB8UnormSrgb;
  case TextureFormat::ETC2_RGB8A1UNORM:
    return WGPUTextureFormat_ETC2RGB8A1Unorm;
  case TextureFormat::ETC2_RGB8A1UNORM_SRGB:
    return WGPUTextureFormat_ETC2RGB8A1UnormSrgb;
  case TextureFormat::ETC2_RGBA8UNORM:
    return WGPUTextureFormat_ETC2RGBA8Unorm;
  case TextureFormat::ETC2_RGBA8UNORM_SRGB:
    return WGPUTextureFormat_ETC2RGBA8UnormSrgb;
  case TextureFormat::EAC_R11UNORM:
    return WGPUTextureFormat_EACR11Unorm;
  case TextureFormat::EAC_R11SNORM:
    return WGPUTextureFormat_EACR11Snorm;
  case TextureFormat::EAC_RG11UNORM:
    return WGPUTextureFormat_EACRG11Unorm;
  case TextureFormat::EAC_RG11SNORM:
    return WGPUTextureFormat_EACRG11Snorm;
  case TextureFormat::ASTC_4X4_UNORM:
    return WGPUTextureFormat_ASTC4x4Unorm;
  case TextureFormat::ASTC_4X4_UNORM_SRGB:
    return WGPUTextureFormat_ASTC4x4UnormSrgb;
  case TextureFormat::ASTC_5X4_UNORM:
    return WGPUTextureFormat_ASTC5x4Unorm;
  case TextureFormat::ASTC_5X4_UNORM_SRGB:
    return WGPUTextureFormat_ASTC5x4UnormSrgb;
  case TextureFormat::ASTC_5X5_UNORM:
    return WGPUTextureFormat_ASTC5x5Unorm;
  case TextureFormat::ASTC_5X5_UNORM_SRGB:
    return WGPUTextureFormat_ASTC5x5UnormSrgb;
  case TextureFormat::ASTC_6X5_UNORM:
    return WGPUTextureFormat_ASTC6x5Unorm;
  case TextureFormat::ASTC_6X5_UNORM_SRGB:
    return WGPUTextureFormat_ASTC6x5UnormSrgb;
  case TextureFormat::ASTC_6X6_UNORM:
    return WGPUTextureFormat_ASTC6x6Unorm;
  case TextureFormat::ASTC_6X6_UNORM_SRGB:
    return WGPUTextureFormat_ASTC6x6UnormSrgb;
  case TextureFormat::ASTC_8X5_UNORM:
    return WGPUTextureFormat_ASTC8x5Unorm;
  case TextureFormat::ASTC_8X5_UNORM_SRGB:
    return WGPUTextureFormat_ASTC8x5UnormSrgb;
  case TextureFormat::ASTC_8X6_UNORM:
    return WGPUTextureFormat_ASTC8x6Unorm;
  case TextureFormat::ASTC_8X6_UNORM_SRGB:
    return WGPUTextureFormat_ASTC8x6UnormSrgb;
  case TextureFormat::ASTC_8X8_UNORM:
    return WGPUTextureFormat_ASTC8x8Unorm;
  case TextureFormat::ASTC_8X8_UNORM_SRGB:
    return WGPUTextureFormat_ASTC8x8UnormSrgb;
  case TextureFormat::ASTC_10X5_UNORM:
    return WGPUTextureFormat_ASTC10x5Unorm;
  case TextureFormat::ASTC_10X5_UNORM_SRGB:
    return WGPUTextureFormat_ASTC10x5UnormSrgb;
  case TextureFormat::ASTC_10X6_UNORM:
    return WGPUTextureFormat_ASTC10x6Unorm;
  case TextureFormat::ASTC_10X6_UNORM_SRGB:
    return WGPUTextureFormat_ASTC10x6UnormSrgb;
  case TextureFormat::ASTC_10X8_UNORM:
    return WGPUTextureFormat_ASTC10x8Unorm;
  case TextureFormat::ASTC_10X8_UNORM_SRGB:
    return WGPUTextureFormat_ASTC10x8UnormSrgb;
  case TextureFormat::ASTC_10X10_UNORM:
    return WGPUTextureFormat_ASTC10x10Unorm;
  case TextureFormat::ASTC_10X10_UNORM_SRGB:
    return WGPUTextureFormat_ASTC10x10UnormSrgb;
  case TextureFormat::ASTC_12X10_UNORM:
    return WGPUTextureFormat_ASTC12x10Unorm;
  case TextureFormat::ASTC_12X10_UNORM_SRGB:
    return WGPUTextureFormat_ASTC12x10UnormSrgb;
  case TextureFormat::ASTC_12X12_UNORM:
    return WGPUTextureFormat_ASTC12x12Unorm;
  case TextureFormat::ASTC_12X12_UNORM_SRGB:
    return WGPUTextureFormat_ASTC12x12UnormSrgb;
  default:
    return WGPUTextureFormat_Undefined;
  }
}

static WGPUTextureDimension
toWGPUTextureDimension(const TextureDimension &dimension) {
  switch (dimension) {
  case TextureDimension::_1D:
    return WGPUTextureDimension_1D;
  case TextureDimension::_2D:
    return WGPUTextureDimension_2D;
  case TextureDimension::_3D:
    return WGPUTextureDimension_3D;
  default:
    return WGPUTextureDimension_Undefined;
  }
}

static WGPUFilterMode toWGPUFilterMode(const SamplerFilterType &filterType) {
  switch (filterType) {
  case SamplerFilterType::LINEAR:
    return WGPUFilterMode_Linear;
  case SamplerFilterType::NEAREST:
    return WGPUFilterMode_Nearest;
  default:
    return WGPUFilterMode_Undefined;
  }
}

static WGPUMipmapFilterMode
toWGPUMipmapFilterMode(const SamplerFilterType &filterType) {
  switch (filterType) {
  case SamplerFilterType::LINEAR:
    return WGPUMipmapFilterMode_Linear;
  case SamplerFilterType::NEAREST:
    return WGPUMipmapFilterMode_Nearest;
  default:
    return WGPUMipmapFilterMode_Undefined;
  }
}

static WGPUSamplerBindingType
toWGPUSamplerBindingType(const SamplerLayoutObjectBindingType &bindingType) {
  switch (bindingType) {
  case SamplerLayoutObjectBindingType::FILTERING:
    return WGPUSamplerBindingType_Filtering;
  case SamplerLayoutObjectBindingType::NON_FILTERING:
    return WGPUSamplerBindingType_NonFiltering;
  case SamplerLayoutObjectBindingType::COMPARISON:
    return WGPUSamplerBindingType_Comparison;
  default:
    return WGPUSamplerBindingType_Undefined;
  }
}

static WGPUTextureViewDimension toWGPUTextureViewDimension(
    const TextureLayoutObjectViewDimension &viewDimension) {
  switch (viewDimension) {
  case TextureLayoutObjectViewDimension::_1D:
    return WGPUTextureViewDimension_1D;
  case TextureLayoutObjectViewDimension::_2D:
    return WGPUTextureViewDimension_2D;
  case TextureLayoutObjectViewDimension::_2D_ARRAY:
    return WGPUTextureViewDimension_2DArray;
  case TextureLayoutObjectViewDimension::_3D:
    return WGPUTextureViewDimension_3D;
  case TextureLayoutObjectViewDimension::CUBE:
    return WGPUTextureViewDimension_Cube;
  case TextureLayoutObjectViewDimension::CUBE_ARRAY:
    return WGPUTextureViewDimension_CubeArray;
  default:
    return WGPUTextureViewDimension_Undefined;
  }
}

static WGPUTextureSampleType
toWGPUTextureSampleType(const TextureLayoutObjectSampleType &sampleType) {
  switch (sampleType) {
  case TextureLayoutObjectSampleType::FLOAT:
    return WGPUTextureSampleType_Float;
  case TextureLayoutObjectSampleType::UNFILTERABLE_FLOAT:
    return WGPUTextureSampleType_UnfilterableFloat;
  case TextureLayoutObjectSampleType::DEPTH:
    return WGPUTextureSampleType_Depth;
  case TextureLayoutObjectSampleType::SINT:
    return WGPUTextureSampleType_Sint;
  case TextureLayoutObjectSampleType::UINT:
    return WGPUTextureSampleType_Uint;
  default:
    return WGPUTextureSampleType_Undefined;
  }
}

static WGPUBufferBindingType
toWGPUBufferBindingType(const BufferLayoutObjectBindingType &bindingType) {
  switch (bindingType) {
  case BufferLayoutObjectBindingType::UNIFORM:
    return WGPUBufferBindingType_Uniform;
  case BufferLayoutObjectBindingType::READ_ONLY_STORAGE:
    return WGPUBufferBindingType_ReadOnlyStorage;
  case BufferLayoutObjectBindingType::STORAGE:
    return WGPUBufferBindingType_Storage;
  default:
    return WGPUBufferBindingType_Undefined;
  }
}

static WGPUStorageTextureAccess
toWGPUStorageTextureAccess(const StorageTextureLayoutObjectAccess &access) {
  switch (access) {
  case StorageTextureLayoutObjectAccess::READ_ONLY:
    return WGPUStorageTextureAccess_ReadOnly;
  case StorageTextureLayoutObjectAccess::READ_WRITE:
    return WGPUStorageTextureAccess_ReadWrite;
  case StorageTextureLayoutObjectAccess::WRITE_ONLY:
    return WGPUStorageTextureAccess_WriteOnly;
  default:
    return WGPUStorageTextureAccess_Undefined;
  }
}

WebGPUDevice::WebGPUDevice()
    : HybridObject(TAG), device_(nullptr), queueInstance_(nullptr) {}

WebGPUDevice::WebGPUDevice(WGPUDevice device)
    : HybridObject(TAG), device_(device), queueInstance_(nullptr) {}

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

  return std::make_shared<WebGPUBuffer>(buffer);
}

std::shared_ptr<HybridNitroWGPUSamplerSpec>
WebGPUDevice::createSampler(const SamplerDescriptor &descriptor) {
  WGPUSamplerDescriptor wgpuDescriptor{0};

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

  WGPUSampler sampler = wgpuDeviceCreateSampler(device_, &wgpuDescriptor);

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
WebGPUDevice::createCommandEncoder(const CommandEncoderDescriptor &descriptor) {
  WGPUCommandEncoderDescriptor wgpuDescriptor{0};
  wgpuDescriptor.nextInChain = nullptr;
  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  WGPUCommandEncoder encoder{
      wgpuDeviceCreateCommandEncoder(device_, &wgpuDescriptor)};

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
  WGPUBindGroupDescriptor wgpuDescriptor {0};
  
  wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
  }
    
  std::vector<WGPUBindGroupEntry> wgpuEntries;
  wgpuEntries.reserve(descriptor.entries.size());
  for (const auto &entry : descriptor.entries) {
    WGPUBindGroupEntry wgpuEntry {0};
    wgpuEntry.binding = (uint32_t) entry.binding;
    wgpuEntry.nextInChain = nullptr;
    
    if (std::holds_alternative<BindGroupBufferBinding>(entry.resource)) {
      auto bufferResource = std::get<BindGroupBufferBinding>(entry.resource);
      auto wgpuBuffer = dynamic_cast<WebGPUBuffer*>(bufferResource.buffer.get())->resource();
      
      wgpuEntry.offset = (uint64_t) bufferResource.offset.value_or(0);
      wgpuEntry.size = (uint64_t) bufferResource.size.value_or((double) wgpuBufferGetSize(wgpuBuffer));
      wgpuEntry.buffer = wgpuBuffer;
    } else if (std::holds_alternative<std::shared_ptr<HybridNitroWGPUTextureViewSpec>>(entry.resource)) {
      auto textureViewResource = std::get<std::shared_ptr<HybridNitroWGPUTextureViewSpec>>(entry.resource);
      
      wgpuEntry.textureView = dynamic_cast<WebGPUTextureView*>(textureViewResource.get())->resource();
    } else if (std::holds_alternative<std::shared_ptr<HybridNitroWGPUSamplerSpec>>(entry.resource)) {
      auto samplerResource = std::get<std::shared_ptr<HybridNitroWGPUSamplerSpec>>(entry.resource);
      
      wgpuEntry.sampler = dynamic_cast<WebGPUSampler*>(samplerResource.get())->resource();
    } else {
      continue;
    }
    
    wgpuEntries.push_back(wgpuEntry);
  }
  
  wgpuDescriptor.layout = dynamic_cast<WebGPUBindGroupLayout*>(descriptor.layout.get())->resource();
  wgpuDescriptor.entryCount = wgpuEntries.size();
  wgpuDescriptor.entries = wgpuEntries.data();
  
  WGPUBindGroup group { wgpuDeviceCreateBindGroup(device_, &wgpuDescriptor) };
  return std::make_shared<WebGPUBindGroup>(group);
}

std::shared_ptr<HybridNitroWGPUPipelineLayoutSpec> WebGPUDevice::createPipelineLayout(const PipelineLayoutDescriptor &descriptor) {
  WGPUPipelineLayoutDescriptor wgpuDescriptor {0};
  
  wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
  }
  
  wgpuDescriptor.nextInChain = nullptr;
  
  std::vector<WGPUBindGroupLayout> wgpuLayouts;
  wgpuLayouts.reserve(descriptor.bindGroupLayouts.size());
  
  for (const auto& layout : descriptor.bindGroupLayouts) {
    auto wgpuLayout = dynamic_cast<WebGPUBindGroupLayout*>(layout.get());
    wgpuLayouts.push_back(wgpuLayout->resource());
  }
  
  wgpuDescriptor.bindGroupLayoutCount = wgpuLayouts.size();
  wgpuDescriptor.bindGroupLayouts = wgpuLayouts.data();
  
  WGPUPipelineLayout layout { wgpuDeviceCreatePipelineLayout(device_, &wgpuDescriptor) };
  
  return std::make_shared<WebGPUPipelineLayout>(layout);
}

std::shared_ptr<HybridNitroWGPUComputePipelineSpec>
WebGPUDevice::createComputePipeline(const ComputePipelineDescriptor &descriptor) {
  WGPUComputePipelineDescriptor wgpuDescriptor {0};
  
  wgpuDescriptor.nextInChain = nullptr;
  wgpuDescriptor.label = { nullptr, WGPU_STRLEN };
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = { descriptor.label.value().c_str(), WGPU_STRLEN };
  }
  wgpuDescriptor.layout = dynamic_cast<WebGPUPipelineLayout*>(descriptor.layout.get())->resource();
  wgpuDescriptor.compute.entryPoint = { nullptr, WGPU_STRLEN };
  if (descriptor.compute.entryPoint.has_value()) {
    wgpuDescriptor.compute.entryPoint = { descriptor.compute.entryPoint.value().c_str(), WGPU_STRLEN };
  }
  
  wgpuDescriptor.compute.nextInChain = nullptr;
  wgpuDescriptor.compute.module = dynamic_cast<WebGPUShaderModule*>(descriptor.compute.module.get())->resource();
  
  wgpuDescriptor.compute.constantCount = 0;
  wgpuDescriptor.compute.constants = nullptr;
  
  std::vector<WGPUConstantEntry> wgpuEntries;
  if (descriptor.compute.constants.has_value()) {
    auto constantsMap = descriptor.compute.constants.value();
    
    wgpuEntries.reserve(constantsMap.size());
    
    for (const auto &entry : constantsMap) {
      WGPUConstantEntry wgpuEntry {0};
      auto key = entry.first;
      auto value = entry.second;
      
      wgpuEntry.nextInChain = nullptr;
      wgpuEntry.key = { key.c_str(), WGPU_STRLEN };
      
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
  
  WGPUComputePipeline pipeline { wgpuDeviceCreateComputePipeline(device_, &wgpuDescriptor) };
  
  return std::make_shared<WebGPUComputePipeline>(pipeline);
}



} // namespace margelo::nitro
