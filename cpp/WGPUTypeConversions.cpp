#include "WGPUTypeConversions.hpp"

namespace margelo::nitro {
WGPUAddressMode toWGPUAddressMode(const SamplerAddressMode &addressMode) {
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

WGPUTextureFormat toWGPUTextureFormat(const TextureFormat &format) {
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

WGPUTextureDimension toWGPUTextureDimension(const TextureDimension &dimension) {
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

WGPUFilterMode toWGPUFilterMode(const SamplerFilterType &filterType) {
  switch (filterType) {
  case SamplerFilterType::LINEAR:
    return WGPUFilterMode_Linear;
  case SamplerFilterType::NEAREST:
    return WGPUFilterMode_Nearest;
  default:
    return WGPUFilterMode_Undefined;
  }
}

WGPUMipmapFilterMode
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

WGPUSamplerBindingType
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

WGPUTextureViewDimension toWGPUTextureViewDimension(
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

WGPUTextureSampleType
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

WGPUBufferBindingType
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

WGPUStorageTextureAccess
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

WGPUTextureAspect toWGPUTextureAspect(const TextureAspect &aspect) {
  switch (aspect) {
  case TextureAspect::ALL:
    return WGPUTextureAspect_All;
  case TextureAspect::DEPTH_ONLY:
    return WGPUTextureAspect_DepthOnly;
  case TextureAspect::STENCIL_ONLY:
    return WGPUTextureAspect_StencilOnly;
  default:
    return WGPUTextureAspect_Undefined;
  }
}

TextureDimension
toNitroTextureDimension(const WGPUTextureDimension &dimension) {
  switch (dimension) {
  case WGPUTextureDimension_1D:
    return TextureDimension::_1D;
  case WGPUTextureDimension_2D:
    return TextureDimension::_2D;
  case WGPUTextureDimension_3D:
    return TextureDimension::_3D;
  default:
    throw std::runtime_error("Wrong conversion in toNitroTextureDimension");
  }
}

TextureFormat toNitroTextureFormat(const WGPUTextureFormat &format) {
  switch (format) {
  case WGPUTextureFormat_R8Unorm:
    return TextureFormat::R8UNORM;
  case WGPUTextureFormat_R8Snorm:
    return TextureFormat::R8SNORM;
  case WGPUTextureFormat_R8Uint:
    return TextureFormat::R8UINT;
  case WGPUTextureFormat_R8Sint:
    return TextureFormat::R8SINT;
  case (WGPUTextureFormat)WGPUNativeTextureFormat_R16Unorm:
    return TextureFormat::R16UNORM;
  case (WGPUTextureFormat)WGPUNativeTextureFormat_R16Snorm:
    return TextureFormat::R16SNORM;
  case WGPUTextureFormat_R16Uint:
    return TextureFormat::R16UINT;
  case WGPUTextureFormat_R16Sint:
    return TextureFormat::R16SINT;
  case WGPUTextureFormat_R16Float:
    return TextureFormat::R16FLOAT;
  case WGPUTextureFormat_RG8Unorm:
    return TextureFormat::RG8UNORM;
  case WGPUTextureFormat_RG8Snorm:
    return TextureFormat::RG8SNORM;
  case WGPUTextureFormat_RG8Uint:
    return TextureFormat::RG8UINT;
  case WGPUTextureFormat_RG8Sint:
    return TextureFormat::RG8SINT;
  case WGPUTextureFormat_R32Uint:
    return TextureFormat::R32UINT;
  case WGPUTextureFormat_R32Sint:
    return TextureFormat::R32SINT;
  case WGPUTextureFormat_R32Float:
    return TextureFormat::R32FLOAT;
  case (WGPUTextureFormat)WGPUNativeTextureFormat_Rg16Unorm:
    return TextureFormat::RG16UNORM;
  case (WGPUTextureFormat)WGPUNativeTextureFormat_Rg16Snorm:
    return TextureFormat::RG16SNORM;
  case WGPUTextureFormat_RG16Uint:
    return TextureFormat::RG16UINT;
  case WGPUTextureFormat_RG16Sint:
    return TextureFormat::RG16SINT;
  case WGPUTextureFormat_RG16Float:
    return TextureFormat::RG16FLOAT;
  case WGPUTextureFormat_RGBA8Unorm:
    return TextureFormat::RGBA8UNORM;
  case WGPUTextureFormat_RGBA8UnormSrgb:
    return TextureFormat::RGBA8UNORM_SRGB;
  case WGPUTextureFormat_RGBA8Snorm:
    return TextureFormat::RGBA8SNORM;
  case WGPUTextureFormat_RGBA8Uint:
    return TextureFormat::RGBA8UINT;
  case WGPUTextureFormat_RGBA8Sint:
    return TextureFormat::RGBA8SINT;
  case WGPUTextureFormat_BGRA8Unorm:
    return TextureFormat::BGRA8UNORM;
  case WGPUTextureFormat_BGRA8UnormSrgb:
    return TextureFormat::BGRA8UNORM_SRGB;
  case WGPUTextureFormat_RGB9E5Ufloat:
    return TextureFormat::RGB9E5UFLOAT;
  case WGPUTextureFormat_RGB10A2Uint:
    return TextureFormat::RGB10A2UINT;
  case WGPUTextureFormat_RGB10A2Unorm:
    return TextureFormat::RGB10A2UNORM;
  case WGPUTextureFormat_RG11B10Ufloat:
    return TextureFormat::RG11B10UFLOAT;
  case WGPUTextureFormat_RG32Uint:
    return TextureFormat::RG32UINT;
  case WGPUTextureFormat_RG32Sint:
    return TextureFormat::RG32SINT;
  case WGPUTextureFormat_RG32Float:
    return TextureFormat::RG32FLOAT;
  case (WGPUTextureFormat)WGPUNativeTextureFormat_Rgba16Unorm:
    return TextureFormat::RGBA16UNORM;
  case (WGPUTextureFormat)WGPUNativeTextureFormat_Rgba16Snorm:
    return TextureFormat::RGBA16SNORM;
  case WGPUTextureFormat_RGBA16Uint:
    return TextureFormat::RGBA16UINT;
  case WGPUTextureFormat_RGBA16Sint:
    return TextureFormat::RGBA16SINT;
  case WGPUTextureFormat_RGBA16Float:
    return TextureFormat::RGBA16FLOAT;
  case WGPUTextureFormat_RGBA32Uint:
    return TextureFormat::RGBA32UINT;
  case WGPUTextureFormat_RGBA32Sint:
    return TextureFormat::RGBA32SINT;
  case WGPUTextureFormat_RGBA32Float:
    return TextureFormat::RGBA32FLOAT;
  case WGPUTextureFormat_Stencil8:
    return TextureFormat::STENCIL8;
  case WGPUTextureFormat_Depth16Unorm:
    return TextureFormat::DEPTH16UNORM;
  case WGPUTextureFormat_Depth24Plus:
    return TextureFormat::DEPTH24PLUS;
  case WGPUTextureFormat_Depth24PlusStencil8:
    return TextureFormat::DEPTH24PLUS_STENCIL8;
  case WGPUTextureFormat_Depth32Float:
    return TextureFormat::DEPTH32FLOAT;
  case WGPUTextureFormat_Depth32FloatStencil8:
    return TextureFormat::DEPTH32FLOAT_STENCIL8;
  case WGPUTextureFormat_BC1RGBAUnorm:
    return TextureFormat::BC1_RGBA_UNORM;
  case WGPUTextureFormat_BC1RGBAUnormSrgb:
    return TextureFormat::BC1_RGBA_UNORM_SRGB;
  case WGPUTextureFormat_BC2RGBAUnorm:
    return TextureFormat::BC2_RGBA_UNORM;
  case WGPUTextureFormat_BC2RGBAUnormSrgb:
    return TextureFormat::BC2_RGBA_UNORM_SRGB;
  case WGPUTextureFormat_BC3RGBAUnorm:
    return TextureFormat::BC3_RGBA_UNORM;
  case WGPUTextureFormat_BC3RGBAUnormSrgb:
    return TextureFormat::BC3_RGBA_UNORM_SRGB;
  case WGPUTextureFormat_BC4RUnorm:
    return TextureFormat::BC4_R_UNORM;
  case WGPUTextureFormat_BC4RSnorm:
    return TextureFormat::BC4_R_SNORM;
  case WGPUTextureFormat_BC5RGUnorm:
    return TextureFormat::BC5_RG_UNORM;
  case WGPUTextureFormat_BC5RGSnorm:
    return TextureFormat::BC5_RG_SNORM;
  case WGPUTextureFormat_BC6HRGBUfloat:
    return TextureFormat::BC6H_RGB_UFLOAT;
  case WGPUTextureFormat_BC6HRGBFloat:
    return TextureFormat::BC6H_RGB_FLOAT;
  case WGPUTextureFormat_BC7RGBAUnorm:
    return TextureFormat::BC7_RGBA_UNORM;
  case WGPUTextureFormat_BC7RGBAUnormSrgb:
    return TextureFormat::BC7_RGBA_UNORM_SRGB;
  case WGPUTextureFormat_ETC2RGB8Unorm:
    return TextureFormat::ETC2_RGB8UNORM;
  case WGPUTextureFormat_ETC2RGB8UnormSrgb:
    return TextureFormat::ETC2_RGB8UNORM_SRGB;
  case WGPUTextureFormat_ETC2RGB8A1Unorm:
    return TextureFormat::ETC2_RGB8A1UNORM;
  case WGPUTextureFormat_ETC2RGB8A1UnormSrgb:
    return TextureFormat::ETC2_RGB8A1UNORM_SRGB;
  case WGPUTextureFormat_ETC2RGBA8Unorm:
    return TextureFormat::ETC2_RGBA8UNORM;
  case WGPUTextureFormat_ETC2RGBA8UnormSrgb:
    return TextureFormat::ETC2_RGBA8UNORM_SRGB;
  case WGPUTextureFormat_EACR11Unorm:
    return TextureFormat::EAC_R11UNORM;
  case WGPUTextureFormat_EACR11Snorm:
    return TextureFormat::EAC_R11SNORM;
  case WGPUTextureFormat_EACRG11Unorm:
    return TextureFormat::EAC_RG11UNORM;
  case WGPUTextureFormat_EACRG11Snorm:
    return TextureFormat::EAC_RG11SNORM;
  case WGPUTextureFormat_ASTC4x4Unorm:
    return TextureFormat::ASTC_4X4_UNORM;
  case WGPUTextureFormat_ASTC4x4UnormSrgb:
    return TextureFormat::ASTC_4X4_UNORM_SRGB;
  case WGPUTextureFormat_ASTC5x4Unorm:
    return TextureFormat::ASTC_5X4_UNORM;
  case WGPUTextureFormat_ASTC5x4UnormSrgb:
    return TextureFormat::ASTC_5X4_UNORM_SRGB;
  case WGPUTextureFormat_ASTC5x5Unorm:
    return TextureFormat::ASTC_5X5_UNORM;
  case WGPUTextureFormat_ASTC5x5UnormSrgb:
    return TextureFormat::ASTC_5X5_UNORM_SRGB;
  case WGPUTextureFormat_ASTC6x5Unorm:
    return TextureFormat::ASTC_6X5_UNORM;
  case WGPUTextureFormat_ASTC6x5UnormSrgb:
    return TextureFormat::ASTC_6X5_UNORM_SRGB;
  case WGPUTextureFormat_ASTC6x6Unorm:
    return TextureFormat::ASTC_6X6_UNORM;
  case WGPUTextureFormat_ASTC6x6UnormSrgb:
    return TextureFormat::ASTC_6X6_UNORM_SRGB;
  case WGPUTextureFormat_ASTC8x5Unorm:
    return TextureFormat::ASTC_8X5_UNORM;
  case WGPUTextureFormat_ASTC8x5UnormSrgb:
    return TextureFormat::ASTC_8X5_UNORM_SRGB;
  case WGPUTextureFormat_ASTC8x6Unorm:
    return TextureFormat::ASTC_8X6_UNORM;
  case WGPUTextureFormat_ASTC8x6UnormSrgb:
    return TextureFormat::ASTC_8X6_UNORM_SRGB;
  case WGPUTextureFormat_ASTC8x8Unorm:
    return TextureFormat::ASTC_8X8_UNORM;
  case WGPUTextureFormat_ASTC8x8UnormSrgb:
    return TextureFormat::ASTC_8X8_UNORM_SRGB;
  case WGPUTextureFormat_ASTC10x5Unorm:
    return TextureFormat::ASTC_10X5_UNORM;
  case WGPUTextureFormat_ASTC10x5UnormSrgb:
    return TextureFormat::ASTC_10X5_UNORM_SRGB;
  case WGPUTextureFormat_ASTC10x6Unorm:
    return TextureFormat::ASTC_10X6_UNORM;
  case WGPUTextureFormat_ASTC10x6UnormSrgb:
    return TextureFormat::ASTC_10X6_UNORM_SRGB;
  case WGPUTextureFormat_ASTC10x8Unorm:
    return TextureFormat::ASTC_10X8_UNORM;
  case WGPUTextureFormat_ASTC10x8UnormSrgb:
    return TextureFormat::ASTC_10X8_UNORM_SRGB;
  case WGPUTextureFormat_ASTC10x10Unorm:
    return TextureFormat::ASTC_10X10_UNORM;
  case WGPUTextureFormat_ASTC10x10UnormSrgb:
    return TextureFormat::ASTC_10X10_UNORM_SRGB;
  case WGPUTextureFormat_ASTC12x10Unorm:
    return TextureFormat::ASTC_12X10_UNORM;
  case WGPUTextureFormat_ASTC12x10UnormSrgb:
    return TextureFormat::ASTC_12X10_UNORM_SRGB;
  case WGPUTextureFormat_ASTC12x12Unorm:
    return TextureFormat::ASTC_12X12_UNORM;
  case WGPUTextureFormat_ASTC12x12UnormSrgb:
    return TextureFormat::ASTC_12X12_UNORM_SRGB;
  default:
    throw std::runtime_error("Wrong conversion in toNitroTextureFormat");
  }
}

WGPUFeatureName toWGPUFeatureName(const DeviceFeature &feature) {
  switch (feature) {
  case DeviceFeature::DEPTH32FLOAT_STENCIL8:
    return WGPUFeatureName_Depth32FloatStencil8;
  case DeviceFeature::BGRA8UNORM_STORAGE:
    return WGPUFeatureName_BGRA8UnormStorage;
  case DeviceFeature::CLIP_DISTANCES:
    return WGPUFeatureName_ClipDistances;
  case DeviceFeature::DEPTH_CLIP_CONTROL:
    return WGPUFeatureName_DepthClipControl;
  case DeviceFeature::DUAL_SOURCE_BLENDING:
    return WGPUFeatureName_DualSourceBlending;
  case DeviceFeature::FLOAT32_BLENDABLE:
    return WGPUFeatureName_Float32Blendable;
  case DeviceFeature::FLOAT32_FILTERABLE:
    return WGPUFeatureName_Float32Filterable;
  case DeviceFeature::INDIRECT_FIRST_INSTANCE:
    return WGPUFeatureName_IndirectFirstInstance;
  case DeviceFeature::RG11B10UFLOAT_RENDERABLE:
    return WGPUFeatureName_RG11B10UfloatRenderable;
  case DeviceFeature::SHADER_F16:
    return WGPUFeatureName_ShaderF16;
  case DeviceFeature::SUBGROUPS:
    return (WGPUFeatureName)WGPUNativeFeature_Subgroup;
  case DeviceFeature::TEXTURE_COMPRESSION_BC:
    return WGPUFeatureName_TextureCompressionBC;
  case DeviceFeature::TEXTURE_COMPRESSION_BC_SLICED_3D:
    return WGPUFeatureName_TextureCompressionBCSliced3D;
  case DeviceFeature::TEXTURE_COMPRESSION_ASTC:
    return WGPUFeatureName_TextureCompressionASTC;
  case DeviceFeature::TEXTURE_COMPRESSION_ASTC_SLICED_3D:
    return WGPUFeatureName_TextureCompressionASTCSliced3D;
  case DeviceFeature::TEXTURE_COMPRESSION_ETC2:
    return WGPUFeatureName_TextureCompressionETC2;
  case DeviceFeature::TIMESTAMP_QUERY:
    return WGPUFeatureName_TimestampQuery;
  case DeviceFeature::EXT_PUSH_CONSTANTS:
    return (WGPUFeatureName)WGPUNativeFeature_PushConstants;
  case DeviceFeature::EXT_TEXTURE_ADAPTER_SPECIFIC_FORMAT_FEATURES:
    return (
        WGPUFeatureName)WGPUNativeFeature_TextureAdapterSpecificFormatFeatures;
  case DeviceFeature::EXT_MULTI_DRAW_INDIRECT:
    return (WGPUFeatureName)WGPUNativeFeature_MultiDrawIndirect;
  case DeviceFeature::EXT_MULTI_DRAW_INDIRECT_COUNT:
    return (WGPUFeatureName)WGPUNativeFeature_MultiDrawIndirectCount;
  case DeviceFeature::EXT_VERTEX_WRITABLE_STORAGE:
    return (WGPUFeatureName)WGPUNativeFeature_VertexWritableStorage;
  case DeviceFeature::EXT_TEXTURE_BINDING_ARRAY:
    return (WGPUFeatureName)WGPUNativeFeature_TextureBindingArray;
  case DeviceFeature::
      EXT_SAMPLED_TEXTURE_AND_STORAGE_BUFFER_ARRAY_NON_UNIFORM_INDEXING:
    return (WGPUFeatureName)
        WGPUNativeFeature_SampledTextureAndStorageBufferArrayNonUniformIndexing;
  case DeviceFeature::EXT_PIPELINE_STATISTICS_QUERY:
    return (WGPUFeatureName)WGPUNativeFeature_PipelineStatisticsQuery;
  case DeviceFeature::EXT_STORAGE_RESOURCE_BINDING_ARRAY:
    return (WGPUFeatureName)WGPUNativeFeature_StorageResourceBindingArray;
  case DeviceFeature::EXT_PARTIALLY_BOUND_BINDING_ARRAY:
    return (WGPUFeatureName)WGPUNativeFeature_PartiallyBoundBindingArray;
  case DeviceFeature::EXT_TEXTURE_FORMAT_16BIT_NORM:
    return (WGPUFeatureName)WGPUNativeFeature_TextureFormat16bitNorm;
  case DeviceFeature::EXT_TEXTURE_COMPRESSION_ASTC_HDR:
    return (WGPUFeatureName)WGPUNativeFeature_TextureCompressionAstcHdr;
  case DeviceFeature::EXT_MAPPABLE_PRIMARY_BUFFERS:
    return (WGPUFeatureName)WGPUNativeFeature_MappablePrimaryBuffers;
  case DeviceFeature::EXT_BUFFER_BINDING_ARRAY:
    return (WGPUFeatureName)WGPUNativeFeature_BufferBindingArray;
  case DeviceFeature::
      EXT_UNIFORM_BUFFER_AND_STORAGE_TEXTURE_NON_UNIFORM_INDEXING:
    return (WGPUFeatureName)
        WGPUNativeFeature_UniformBufferAndStorageTextureArrayNonUniformIndexing;
  case DeviceFeature::EXT_SPIRV_SHADER_PASSTHROUGH:
    return (WGPUFeatureName)WGPUNativeFeature_SpirvShaderPassthrough;
  case DeviceFeature::EXT_VERTEX_ATTRIBUTE_64BIT:
    return (WGPUFeatureName)WGPUNativeFeature_VertexAttribute64bit;
  case DeviceFeature::EXT_TEXTURE_FORMAT_NV12:
    return (WGPUFeatureName)WGPUNativeFeature_TextureFormatNv12;
  case DeviceFeature::EXT_RAY_TRACING_ACCELERATION_STRUCTURE:
    return (WGPUFeatureName)WGPUNativeFeature_RayTracingAccelerationStructure;
  case DeviceFeature::EXT_RAY_QUERY:
    return (WGPUFeatureName)WGPUNativeFeature_RayQuery;
  case DeviceFeature::EXT_SHADER_F64:
    return (WGPUFeatureName)WGPUNativeFeature_ShaderF64;
  case DeviceFeature::EXT_SHADER_I16:
    return (WGPUFeatureName)WGPUNativeFeature_ShaderI16;
  case DeviceFeature::EXT_SHADER_PRIMITIVE_INDEX:
    return (WGPUFeatureName)WGPUNativeFeature_ShaderPrimitiveIndex;
  case DeviceFeature::EXT_SHADER_EARLY_DEPTH_TEST:
    return (WGPUFeatureName)WGPUNativeFeature_ShaderEarlyDepthTest;
  case DeviceFeature::EXT_SUBGROUP_VERTEX:
    return (WGPUFeatureName)WGPUNativeFeature_SubgroupVertex;
  case DeviceFeature::EXT_SUBGROUP_BARRIER:
    return (WGPUFeatureName)WGPUNativeFeature_SubgroupBarrier;
  case DeviceFeature::EXT_TIMESTAMP_QUERY_INSIDE_ENCODERS:
    return (WGPUFeatureName)WGPUNativeFeature_TimestampQueryInsideEncoders;
  case DeviceFeature::EXT_TIMESTAMP_QUERY_INSIDE_PASSES:
    return (WGPUFeatureName)WGPUNativeFeature_TimestampQueryInsidePasses;

  default:
    return WGPUFeatureName_Undefined;
  }
}

DeviceFeature toNitroDeviceFeature(const WGPUFeatureName &featureName) {
  switch (featureName) {
  case WGPUFeatureName_Depth32FloatStencil8:
    return DeviceFeature::DEPTH32FLOAT_STENCIL8;
  case WGPUFeatureName_BGRA8UnormStorage:
    return DeviceFeature::BGRA8UNORM_STORAGE;
  case WGPUFeatureName_ClipDistances:
    return DeviceFeature::CLIP_DISTANCES;
  case WGPUFeatureName_DepthClipControl:
    return DeviceFeature::DEPTH_CLIP_CONTROL;
  case WGPUFeatureName_DualSourceBlending:
    return DeviceFeature::DUAL_SOURCE_BLENDING;
  case WGPUFeatureName_Float32Blendable:
    return DeviceFeature::FLOAT32_BLENDABLE;
  case WGPUFeatureName_Float32Filterable:
    return DeviceFeature::FLOAT32_FILTERABLE;
  case WGPUFeatureName_IndirectFirstInstance:
    return DeviceFeature::INDIRECT_FIRST_INSTANCE;
  case WGPUFeatureName_RG11B10UfloatRenderable:
    return DeviceFeature::RG11B10UFLOAT_RENDERABLE;
  case WGPUFeatureName_ShaderF16:
    return DeviceFeature::SHADER_F16;
  case WGPUFeatureName_TextureCompressionBC:
    return DeviceFeature::TEXTURE_COMPRESSION_BC;
  case WGPUFeatureName_TextureCompressionBCSliced3D:
    return DeviceFeature::TEXTURE_COMPRESSION_BC_SLICED_3D;
  case WGPUFeatureName_TextureCompressionASTC:
    return DeviceFeature::TEXTURE_COMPRESSION_ASTC;
  case WGPUFeatureName_TextureCompressionASTCSliced3D:
    return DeviceFeature::TEXTURE_COMPRESSION_ASTC_SLICED_3D;
  case WGPUFeatureName_TextureCompressionETC2:
    return DeviceFeature::TEXTURE_COMPRESSION_ETC2;
  case WGPUFeatureName_TimestampQuery:
    return DeviceFeature::TIMESTAMP_QUERY;
  case (WGPUFeatureName)WGPUNativeFeature_PushConstants:
    return DeviceFeature::EXT_PUSH_CONSTANTS;
  case (WGPUFeatureName)WGPUNativeFeature_TextureAdapterSpecificFormatFeatures:
    return DeviceFeature::EXT_TEXTURE_ADAPTER_SPECIFIC_FORMAT_FEATURES;
  case (WGPUFeatureName)WGPUNativeFeature_MultiDrawIndirect:
    return DeviceFeature::EXT_MULTI_DRAW_INDIRECT;
  case (WGPUFeatureName)WGPUNativeFeature_MultiDrawIndirectCount:
    return DeviceFeature::EXT_MULTI_DRAW_INDIRECT_COUNT;
  case (WGPUFeatureName)WGPUNativeFeature_VertexWritableStorage:
    return DeviceFeature::EXT_VERTEX_WRITABLE_STORAGE;
  case (WGPUFeatureName)WGPUNativeFeature_TextureBindingArray:
    return DeviceFeature::EXT_TEXTURE_BINDING_ARRAY;
  case (WGPUFeatureName)
      WGPUNativeFeature_SampledTextureAndStorageBufferArrayNonUniformIndexing:
    return DeviceFeature::
        EXT_SAMPLED_TEXTURE_AND_STORAGE_BUFFER_ARRAY_NON_UNIFORM_INDEXING;
  case (WGPUFeatureName)WGPUNativeFeature_PipelineStatisticsQuery:
    return DeviceFeature::EXT_PIPELINE_STATISTICS_QUERY;
  case (WGPUFeatureName)WGPUNativeFeature_StorageResourceBindingArray:
    return DeviceFeature::EXT_STORAGE_RESOURCE_BINDING_ARRAY;
  case (WGPUFeatureName)WGPUNativeFeature_PartiallyBoundBindingArray:
    return DeviceFeature::EXT_PARTIALLY_BOUND_BINDING_ARRAY;
  case (WGPUFeatureName)WGPUNativeFeature_TextureFormat16bitNorm:
    return DeviceFeature::EXT_TEXTURE_FORMAT_16BIT_NORM;
  case (WGPUFeatureName)WGPUNativeFeature_TextureCompressionAstcHdr:
    return DeviceFeature::EXT_TEXTURE_COMPRESSION_ASTC_HDR;
  case (WGPUFeatureName)WGPUNativeFeature_MappablePrimaryBuffers:
    return DeviceFeature::EXT_MAPPABLE_PRIMARY_BUFFERS;
  case (WGPUFeatureName)WGPUNativeFeature_BufferBindingArray:
    return DeviceFeature::EXT_BUFFER_BINDING_ARRAY;
  case (WGPUFeatureName)
      WGPUNativeFeature_UniformBufferAndStorageTextureArrayNonUniformIndexing:
    return DeviceFeature::
        EXT_UNIFORM_BUFFER_AND_STORAGE_TEXTURE_NON_UNIFORM_INDEXING;
  case (WGPUFeatureName)WGPUNativeFeature_SpirvShaderPassthrough:
    return DeviceFeature::EXT_SPIRV_SHADER_PASSTHROUGH;
  case (WGPUFeatureName)WGPUNativeFeature_VertexAttribute64bit:
    return DeviceFeature::EXT_VERTEX_ATTRIBUTE_64BIT;
  case (WGPUFeatureName)WGPUNativeFeature_TextureFormatNv12:
    return DeviceFeature::EXT_TEXTURE_FORMAT_NV12;
  case (WGPUFeatureName)WGPUNativeFeature_RayTracingAccelerationStructure:
    return DeviceFeature::EXT_RAY_TRACING_ACCELERATION_STRUCTURE;
  case (WGPUFeatureName)WGPUNativeFeature_RayQuery:
    return DeviceFeature::EXT_RAY_QUERY;
  case (WGPUFeatureName)WGPUNativeFeature_ShaderF64:
    return DeviceFeature::EXT_SHADER_F64;
  case (WGPUFeatureName)WGPUNativeFeature_ShaderI16:
    return DeviceFeature::EXT_SHADER_I16;
  case (WGPUFeatureName)WGPUNativeFeature_ShaderPrimitiveIndex:
    return DeviceFeature::EXT_SHADER_PRIMITIVE_INDEX;
  case (WGPUFeatureName)WGPUNativeFeature_ShaderEarlyDepthTest:
    return DeviceFeature::EXT_SHADER_EARLY_DEPTH_TEST;
  case (WGPUFeatureName)
      WGPUNativeFeature_Subgroup: // DeviceFeature::SUBGROUPS maps here
    return DeviceFeature::SUBGROUPS;
  case (WGPUFeatureName)WGPUNativeFeature_SubgroupVertex:
    return DeviceFeature::EXT_SUBGROUP_VERTEX;
  case (WGPUFeatureName)WGPUNativeFeature_SubgroupBarrier:
    return DeviceFeature::EXT_SUBGROUP_BARRIER;
  case (WGPUFeatureName)WGPUNativeFeature_TimestampQueryInsideEncoders:
    return DeviceFeature::EXT_TIMESTAMP_QUERY_INSIDE_ENCODERS;
  case (WGPUFeatureName)WGPUNativeFeature_TimestampQueryInsidePasses:
    return DeviceFeature::EXT_TIMESTAMP_QUERY_INSIDE_PASSES;
  case WGPUFeatureName_Undefined:
  default:
    throw std::runtime_error("Wrong conversion in toNitroDeviceFeature");
  }
}

} // namespace margelo::nitro
