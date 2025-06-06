import type { HybridObject } from 'react-native-nitro-modules';

type BufferDescriptor = {
  label?: string;
  mappedAtCreation?: boolean;
  size: number;
  usage: number;
};

export interface NitroWGPUBuffer
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}
export interface NitroWGPUQueue
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {}

export interface NitroWGPUDevice
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  readonly queue: NitroWGPUQueue;

  createBuffer(descriptor: BufferDescriptor): NitroWGPUBuffer;
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
