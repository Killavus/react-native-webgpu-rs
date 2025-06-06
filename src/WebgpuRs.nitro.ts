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
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  mapAsync(mode: number, offset?: number, size?: number): Promise<void>;
  getMappedRange(offset?: number, size?: number): ArrayBuffer;
  unmap(): void;
}

type WriteTextureOrigin = WriteTextureOriginObject | number[];
type WriteTextureOriginObject = {
  x: number;
  y: number;
  z: number;
};

type WriteTextureDestination = {
  aspect?: TextureAspect;
  mipLevel?: number;
  origin?: WriteTextureOrigin;
  texture: NitroWGPUTexture;
};

type WriteTextureDataLayout = {
  offset?: number;
  bytesPerRow?: number;
  rowsPerImage?: number;
};

export interface NitroWGPUQueue
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  submit(commandBuffers: NitroWGPUCommandBuffer[]): void;
  writeBuffer(
    buffer: NitroWGPUBuffer,
    bufferOffset: number,
    data: ArrayBuffer,
    dataOffset?: number,
    size?: number
  ): void;

  writeTexture(
    source: WriteTextureDestination,
    data: ArrayBuffer,
    dataLayout: WriteTextureDataLayout,
    size: WriteTextureExtent
  ): void;
}

type WriteTextureExtent = WriteTextureExtentObject | number[];
type WriteTextureExtentObject = {
  width: number;
  height?: number;
  depthOrArrayLayers?: number;
};

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
  copyBufferToBuffer(
    source: NitroWGPUBuffer,
    sourceOffset: number,
    destination: NitroWGPUBuffer,
    destinationOffset: number,
    size: number
  ): void;
  finish(descriptor?: CommandBufferDescriptor): NitroWGPUCommandBuffer;
}

type TextureAspect = 'all' | 'stencil-only' | 'depth-only';

type TextureViewDescriptor = {
  label?: string;
  aspect?: TextureAspect;
  arrayLayerCount?: number;
  baseArrayLayer?: number;
  baseMipLevel?: number;
  dimension?: TextureLayoutObjectViewDimension;
  format?: TextureFormat;
  mipLevelCount?: number;
  usage?: number;
};

export interface NitroWGPUTexture
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  createView(descriptor: TextureViewDescriptor): NitroWGPUTextureView;

  readonly width: number;
  readonly height: number;
  readonly depthOrArrayLayers: number;
  readonly mipLevelCount: number;
  readonly sampleCount: number;
  readonly dimension: TextureDimension;
  readonly format: TextureFormat;
  readonly usage: number;
}

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

type DeviceFeature =
  // WebGPU Features:
  | 'bgra8unorm-storage'
  | 'clip-distances'
  | 'depth-clip-control'
  | 'depth32float-stencil8'
  | 'dual-source-blending'
  | 'float32-blendable'
  | 'float32-filterable'
  | 'indirect-first-instance'
  | 'rg11b10ufloat-renderable'
  | 'shader-f16'
  | 'subgroups'
  | 'texture-compression-bc'
  | 'texture-compression-bc-sliced-3d'
  | 'texture-compression-astc'
  | 'texture-compression-astc-sliced-3d'
  | 'texture-compression-etc2'
  | 'timestamp-query'
  // Native Extensions:
  /*
  Requires wgpu.h api change:
  "ext:address-mode-clamp-to-zero" |
  "ext:address-mode-clamp-to-border" |
  "ext:polygon-mode-line" |
  "ext:polygon-mode-point" |
  "ext:conservative-rasterization" |
  "ext:clear-texture" |
  "ext:multiview" |
  */
  | 'ext:push-constants'
  | 'ext:texture-adapter-specific-format-features'
  | 'ext:multi-draw-indirect'
  | 'ext:multi-draw-indirect-count'
  | 'ext:vertex-writable-storage'
  | 'ext:texture-binding-array'
  | 'ext:sampled-texture-and-storage-buffer-array-non-uniform-indexing'
  | 'ext:pipeline-statistics-query'
  | 'ext:storage-resource-binding-array'
  | 'ext:partially-bound-binding-array'
  | 'ext:texture-format-16bit-norm'
  | 'ext:texture-compression-astc-hdr'
  | 'ext:mappable-primary-buffers'
  | 'ext:buffer-binding-array'
  | 'ext:uniform-buffer-and-storage-texture-non-uniform-indexing'
  | 'ext:spirv-shader-passthrough'
  | 'ext:vertex-attribute-64bit'
  | 'ext:texture-format-nv12'
  | 'ext:ray-tracing-acceleration-structure'
  | 'ext:ray-query'
  | 'ext:shader-f64'
  | 'ext:shader-i16'
  | 'ext:shader-primitive-index'
  | 'ext:shader-early-depth-test'
  | 'ext:subgroup-vertex'
  | 'ext:subgroup-barrier'
  | 'ext:timestamp-query-inside-encoders'
  | 'ext:timestamp-query-inside-passes';

type QueueDescriptor = {
  label?: string;
};

type RequiredLimits = {
  maxTextureDimension1D?: number;
  maxTextureDimension2D?: number;
  maxTextureDimension3D?: number;
  maxTextureArrayLayers?: number;
  maxBindGroups?: number;
  maxBindingsPerBindGroup?: number;
  maxDynamicUniformBuffersPerPipelineLayout?: number;
  maxDynamicStorageBuffersPerPipelineLayout?: number;
  maxSampledTexturesPerShaderStage?: number;
  maxSamplersPerShaderStage?: number;
  maxStorageBuffersPerShaderStage?: number;
  maxStorageTexturesPerShaderStage?: number;
  maxUniformBuffersPerShaderStage?: number;
  maxUniformBufferBindingSize?: number;
  maxStorageBufferBindingSize?: number;
  minUniformBufferOffsetAlignment?: number;
  minStorageBufferOffsetAlignment?: number;
  maxVertexBuffers?: number;
  maxBufferSize?: number;
  maxVertexAttributes?: number;
  maxVertexBufferArrayStride?: number;
  maxInterStageShaderComponents?: number;
  maxInterStageShaderVariables?: number;
  maxColorAttachments?: number;
  maxColorAttachmentBytesPerSample?: number;
  maxComputeWorkgroupStorageSize?: number;
  maxComputeInvocationsPerWorkgroup?: number;
  maxComputeWorkgroupSizeX?: number;
  maxComputeWorkgroupSizeY?: number;
  maxComputeWorkgroupSizeZ?: number;
  maxComputeWorkgroupsPerDimension?: number;
  ext_maxPushConstantSize?: number;
  ext_maxNonSamplerBindings?: number;
};

type DeviceDescriptor = {
  label?: string;
  requiredFeatures?: DeviceFeature[];
  requiredLimits?: RequiredLimits;
  defaultQueue?: QueueDescriptor;
};

export interface NitroWGPUDevice
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  readonly queue: NitroWGPUQueue;

  readonly features: DeviceFeature[];
  readonly limits: RequiredLimits;
  readonly adapterInfo: DeviceInfo;
  readonly lost: boolean;

  createBuffer(descriptor: BufferDescriptor): NitroWGPUBuffer;
  createSampler(descriptor?: SamplerDescriptor): NitroWGPUSampler;
  createShaderModule(descriptor: ShaderModuleDescriptor): NitroWGPUShaderModule;
  createCommandEncoder(
    descriptor?: CommandEncoderDescriptor
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

type DeviceInfo = {
  architecture: string;
  description: string;
  device: string;
  vendor: string;
  subgroupMaxSize: number;
  subgroupMinSize: number;
};

type FeatureSet = DeviceFeature[];

export interface NitroWGPUAdapter
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  requestDevice(descriptor?: DeviceDescriptor): Promise<NitroWGPUDevice>;

  readonly limits: RequiredLimits;
  readonly features: FeatureSet;
  readonly isFallbackAdapter: boolean;
  readonly info: DeviceInfo;
}

type AdapterPowerPreference = 'low-power' | 'high-performance';

type AdapterDescriptor = {
  powerPreference?: AdapterPowerPreference;
};

export interface NitroWGPUInstance
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  enumerateAdapters(): void;
  requestAdapter(descriptor?: AdapterDescriptor): Promise<NitroWGPUAdapter>;
  getPreferredCanvasFormat(): TextureFormat;

  registerErrorHandler(handler: (errorMessage: string) => void): void;
}
