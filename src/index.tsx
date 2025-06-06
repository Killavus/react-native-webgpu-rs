import { NitroModules } from 'react-native-nitro-modules';
import type { WebgpuRs } from './WebgpuRs.nitro';

const WebgpuRsHybridObject =
  NitroModules.createHybridObject<WebgpuRs>('WebgpuRs');

export function multiply(a: number, b: number): number {
  return WebgpuRsHybridObject.multiply(a, b);
}
