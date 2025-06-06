import type { HybridObject } from 'react-native-nitro-modules';

type BufferDescriptor = {
  label?: string;
  mappedAtCreation?: boolean;
  size: number;
  usage: number;
};

type SamplerAddressMode = 'clamp-to-edge' | 'repeat' | 'mirror-repeat';
type SamplerCompare =
  | 'never'
  | 'less'
  | 'equal'
  | 'less-equal'
  | 'greater'
  | 'not-equal'
  | 'greater-equal'
  | 'always';
type SamplerFilterType = 'nearest' | 'linear';

type SamplerDescriptor = {
  label?: string;
  addressModeU?: SamplerAddressMode;
  addressModeV?: SamplerAddressMode;
  addressModeW?: SamplerAddressMode;
  compare?: SamplerCompare;
  lodMinClamp?: number;
  lodMaxClamp?: number;
  maxAnisotropy?: number;
  magFilter?: SamplerFilterType;
  minFilter?: SamplerFilterType;
  mipmapFilter?: SamplerFilterType;
};

type ShaderModuleDescriptor = {
  label?: string;
  code: string;
};

type CommandEncoderDescriptor = {
  label?: string;
};

type TextureDimension = '1d' | '2d' | '3d';
type TextureFormat =
  | 'r8unorm'
  | 'r8snorm'
  | 'r8uint'
  | 'r8sint'
  | 'r16unorm'
  | 'r16snorm'
  | 'r16uint'
  | 'r16sint'
  | 'r16float'
  | 'rg8unorm'
  | 'rg8snorm'
  | 'rg8uint'
  | 'rg8sint'
  | 'r32uint'
  | 'r32sint'
  | 'r32float'
  | 'rg16unorm'
  | 'rg16snorm'
  | 'rg16uint'
  | 'rg16sint'
  | 'rg16float'
  | 'rgba8unorm'
  | 'rgba8unorm-srgb'
  | 'rgba8snorm'
  | 'rgba8uint'
  | 'rgba8sint'
  | 'bgra8unorm'
  | 'bgra8unorm-srgb'
  | 'rgb9e5ufloat'
  | 'rgb10a2uint'
  | 'rgb10a2unorm'
  | 'rg11b10ufloat'
  | 'rg32uint'
  | 'rg32sint'
  | 'rg32float'
  | 'rgba16unorm'
  | 'rgba16snorm'
  | 'rgba16uint'
  | 'rgba16sint'
  | 'rgba16float'
  | 'rgba32uint'
  | 'rgba32sint'
  | 'rgba32float'
  | 'stencil8'
  | 'depth16unorm'
  | 'depth24plus'
  | 'depth24plus-stencil8'
  | 'depth32float'
  | 'depth32float-stencil8'
  | 'bc1-rgba-unorm'
  | 'bc1-rgba-unorm-srgb'
  | 'bc2-rgba-unorm'
  | 'bc2-rgba-unorm-srgb'
  | 'bc3-rgba-unorm'
  | 'bc3-rgba-unorm-srgb'
  | 'bc4-r-unorm'
  | 'bc4-r-snorm'
  | 'bc5-rg-unorm'
  | 'bc5-rg-snorm'
  | 'bc6h-rgb-ufloat'
  | 'bc6h-rgb-float'
  | 'bc7-rgba-unorm'
  | 'bc7-rgba-unorm-srgb'
  | 'etc2-rgb8unorm'
  | 'etc2-rgb8unorm-srgb'
  | 'etc2-rgb8a1unorm'
  | 'etc2-rgb8a1unorm-srgb'
  | 'etc2-rgba8unorm'
  | 'etc2-rgba8unorm-srgb'
  | 'eac-r11unorm'
  | 'eac-r11snorm'
  | 'eac-rg11unorm'
  | 'eac-rg11snorm'
  | 'astc-4x4-unorm'
  | 'astc-4x4-unorm-srgb'
  | 'astc-5x4-unorm'
  | 'astc-5x4-unorm-srgb'
  | 'astc-5x5-unorm'
  | 'astc-5x5-unorm-srgb'
  | 'astc-6x5-unorm'
  | 'astc-6x5-unorm-srgb'
  | 'astc-6x6-unorm'
  | 'astc-6x6-unorm-srgb'
  | 'astc-8x5-unorm'
  | 'astc-8x5-unorm-srgb'
  | 'astc-8x6-unorm'
  | 'astc-8x6-unorm-srgb'
  | 'astc-8x8-unorm'
  | 'astc-8x8-unorm-srgb'
  | 'astc-10x5-unorm'
  | 'astc-10x5-unorm-srgb'
  | 'astc-10x6-unorm'
  | 'astc-10x6-unorm-srgb'
  | 'astc-10x8-unorm'
  | 'astc-10x8-unorm-srgb'
  | 'astc-10x10-unorm'
  | 'astc-10x10-unorm-srgb'
  | 'astc-12x10-unorm'
  | 'astc-12x10-unorm-srgb'
  | 'astc-12x12-unorm'
  | 'astc-12x12-unorm-srgb';

type TextureDescriptorSize = number[] | TextureDescriptorSizeObject;
type TextureDescriptorSizeObject = {
  width: number;
  height?: number;
  depthOrArrayLayers?: number;
};

type TextureDescriptor = {
  label?: string;
  dimension?: TextureDimension;
  format: TextureFormat;
  mipLevelCount?: number;
  sampleCount?: number;
  size: TextureDescriptorSize;
  usage: number;
  viewFormats?: TextureFormat[];
};

type BindGroupLayoutDescriptor = {
  label?: string;
  entries: BindGroupLayoutEntry[];
};

type BindGroupLayoutEntry =
  | BufferLayoutObject
  | TextureLayoutObject
  | SamplerLayoutObject
  | StorageTextureLayoutObject
  | TextureLayoutObject;

type BufferLayoutObjectBindingType =
  | 'uniform'
  | 'storage'
  | 'read-only-storage';

type TextureLayoutObjectSampleType =
  | 'float'
  | 'unfilterable-float'
  | 'depth'
  | 'sint'
  | 'uint';

type TextureLayoutObjectViewDimension =
  | '1d'
  | '2d'
  | '2d-array'
  | 'cube'
  | 'cube-array'
  | '3d';

type SamplerLayoutObjectBindingType =
  | 'filtering'
  | 'non-filtering'
  | 'comparison';

type StorageTextureLayoutObjectAccess =
  | 'write-only'
  | 'read-write'
  | 'read-only';

type BufferLayoutObjectResource = {
  hasDynamicOffset?: boolean;
  minBindingSize?: number;
  type?: BufferLayoutObjectBindingType;
};

type TextureLayoutObjectResource = {
  sampleType?: TextureLayoutObjectSampleType;
  multisampled?: boolean;
  viewDimension?: TextureLayoutObjectViewDimension;
};

type SamplerLayoutObjectResource = {
  type?: SamplerLayoutObjectBindingType;
};

type StorageTextureLayoutObjectResource = {
  access?: StorageTextureLayoutObjectAccess;
  format: TextureFormat;
  viewDimension?: TextureLayoutObjectViewDimension;
};

type BufferLayoutObject = {
  binding: number;
  visibility: number;
  buffer: BufferLayoutObjectResource;
};

type TextureLayoutObject = {
  binding: number;
  visibility: number;
  texture: TextureLayoutObjectResource;
};

type SamplerLayoutObject = {
  binding: number;
  visibility: number;
  sampler: SamplerLayoutObjectResource;
};

type StorageTextureLayoutObject = {
  binding: number;
  visibility: number;
  storageTexture: StorageTextureLayoutObjectResource;
};

type BindGroupDescriptor = {
  label?: string;
  layout: NitroWGPUBindGroupLayout;
  entries: BindGroupEntry[];
};

type BindGroupEntry = { binding: number; resource: BindGroupEntryResource };

type BindGroupEntryResource =
  | BindGroupBufferBinding
  | NitroWGPUSampler
  | NitroWGPUTextureView;

type BindGroupBufferBinding = {
  buffer: NitroWGPUBuffer;
  offset?: number;
  size?: number;
};

type PipelineLayoutDescriptor = {
  label?: string;
  bindGroupLayouts: NitroWGPUBindGroupLayout[];
};

type ComputePipelineComputeDescriptor = {
  entryPoint?: string;
  module: NitroWGPUShaderModule;
  constants?: Record<ConstantId, ConstantValue>;
};

type ConstantId = string;
type ConstantValue = number | boolean;

type ComputePipelineDescriptor = {
  label?: string;
  layout: NitroWGPUPipelineLayout;
  compute: ComputePipelineComputeDescriptor;
};

type ComputePassDescriptor = {
  label?: string;
  // timestampWrites?: ComputePassTimestampWrite[];
};

export interface NitroWGPUBuffer
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUQueue
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  submit(commandBuffers: NitroWGPUCommandBuffer[]): void;
}

type CommandBufferDescriptor = {
  label?: string;
};

export interface NitroWGPUSampler
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUShaderModule
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUCommandBuffer
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUCommandEncoder
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  beginComputePass(
    descriptor: ComputePassDescriptor
  ): NitroWGPUComputePassEncoder;
  finish(descriptor?: CommandBufferDescriptor): NitroWGPUCommandBuffer;
}

export interface NitroWGPUTexture
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUBindGroupLayout
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUBindGroup
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUTextureView
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUPipelineLayout
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUComputePipeline
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

type EncodedBindGroup = NitroWGPUBindGroup | null;

export interface NitroWGPUComputePassEncoder
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  setPipeline(pipeline: NitroWGPUComputePipeline): void;
  setBindGroup(index: number, bindGroup: EncodedBindGroup): void;
  dispatchWorkgroups(
    workgroupCountX: number,
    workgroupCountY: number,
    workgroupCountZ: number
  ): void;
  // dispatchWorkgroupsIndirect(indirectBuffer: NitroWGPUBuffer, indirectOffset: number): void;
  // popDebugGroup(): void;
  // pushDebugGroup(groupLabel: string): void;
  // insertDebugMarker(markerLabel: string): void;
  end(): void;
}

export interface NitroWGPUDevice
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  readonly queue: NitroWGPUQueue;

  createBuffer(descriptor: BufferDescriptor): NitroWGPUBuffer;
  createSampler(descriptor: SamplerDescriptor): NitroWGPUSampler;
  createShaderModule(descriptor: ShaderModuleDescriptor): NitroWGPUShaderModule;
  createCommandEncoder(
    descriptor: CommandEncoderDescriptor
  ): NitroWGPUCommandEncoder;
  createTexture(descriptor: TextureDescriptor): NitroWGPUTexture;
  createBindGroupLayout(
    descriptor: BindGroupLayoutDescriptor
  ): NitroWGPUBindGroupLayout;
  createBindGroup(descriptor: BindGroupDescriptor): NitroWGPUBindGroup;
  createPipelineLayout(
    descriptor: PipelineLayoutDescriptor
  ): NitroWGPUPipelineLayout;
  createComputePipeline(
    descriptor: ComputePipelineDescriptor
  ): NitroWGPUComputePipeline;
}

export interface NitroWGPUAdapter
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  requestDevice(): Promise<NitroWGPUDevice>;
}

export interface NitroWGPUInstance
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  enumerateAdapters(): void;
  requestAdapter(): Promise<NitroWGPUAdapter>;
}
