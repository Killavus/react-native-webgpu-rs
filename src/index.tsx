import { NitroModules } from 'react-native-nitro-modules';
import type { NitroWGPUInstance } from './WebgpuRs.nitro';

const Instance =
  NitroModules.createHybridObject<NitroWGPUInstance>('NitroWGPUInstance');

export const GPUBufferUsage = {
  MAP_READ: 0x0001,
  MAP_WRITE: 0x0002,
  COPY_SRC: 0x0004,
  COPY_DST: 0x0008,
  INDEX: 0x0010,
  INDIRECT: 0x0100,
  QUERY_RESOLVE: 0x0200,
  STORAGE: 0x0080,
  UNIFORM: 0x0040,
  VERTEX: 0x0020,
};

export const GPUTextureUsage = {
  COPY_SRC: 0x01,
  COPY_DST: 0x02,
  RENDER_ATTACHMENT: 0x10,
  STORAGE_BINDING: 0x08,
  TEXTURE_BINDING: 0x04,
};

export const GPUShaderStage = {
  VERTEX: 0x01,
  FRAGMENT: 0x02,
  COMPUTE: 0x04,
};

export { Instance };
