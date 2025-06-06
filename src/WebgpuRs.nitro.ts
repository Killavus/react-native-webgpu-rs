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

export interface NitroWGPUBuffer
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUQueue
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUSampler
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUShaderModule
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUDevice
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  readonly queue: NitroWGPUQueue;

  createBuffer(descriptor: BufferDescriptor): NitroWGPUBuffer;
  createSampler(descriptor: SamplerDescriptor): NitroWGPUSampler;
  createShaderModule(descriptor: ShaderModuleDescriptor): NitroWGPUShaderModule;
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
