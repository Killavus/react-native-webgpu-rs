import { useState } from 'react';
import { Text, View, StyleSheet, TextInput, Button } from 'react-native';
import {
  Instance,
  GPUBufferUsage,
  GPUTextureUsage,
  GPUShaderStage,
  GPUMapMode,
} from 'react-native-webgpu-rs';

const SHADER_CODE = `
@group(0)
@binding(0)
var<storage, read_write> v_indices: array<u32>; // this is used as both input and output for convenience

// The Collatz Conjecture states that for any integer n:
// If n is even, n = n/2
// If n is odd, n = 3n+1
// And repeat this process for each new n, you will always eventually reach 1.
// Though the conjecture has not been proven, no counterexample has ever been found.
// This function returns how many times this recurrence needs to be applied to reach 1.
fn collatz_iterations(n_base: u32) -> u32{
    var n: u32 = n_base;
    var i: u32 = 0u;
    loop {
        if (n <= 1u) {
            break;
        }
        if (n % 2u == 0u) {
            n = n / 2u;
        }
        else {
            // Overflow? (i.e. 3*n + 1 > 0xffffffffu?)
            if (n >= 1431655765u) {   // 0x55555555u
                return 4294967295u;   // 0xffffffffu
            }

            n = 3u * n + 1u;
        }
        i = i + 1u;
    }
    return i;
}

@compute
@workgroup_size(1)
fn main(@builtin(global_invocation_id) global_id: vec3<u32>) {
    v_indices[global_id.x] = collatz_iterations(v_indices[global_id.x]);
}
`;

export default function App() {
  Instance.enumerateAdapters();

  const handleClick = async () => {
    try {
      const adapter = await Instance.requestAdapter();
      const numbersList = new Uint32Array(
        text.split(',').map((chunk) => parseInt(chunk.trim(), 10))
      );

      console.log('adapter', adapter);
      console.log('adapter.features', adapter.features);
      console.log('adapter.limits', adapter.limits);
      console.log('adapter.isFallbackAdapter', adapter.isFallbackAdapter);
      console.log('adapter.info', adapter.info);

      const device = await adapter.requestDevice({
        label: 'TestDevice',
        defaultQueue: {
          label: 'TestQueue',
        },
        // requiredFeatures: ['ext:texture-format-16bit-norm', 'ext:push-constants'],
      });

      console.log('device', device);

      const stagingBuffer = device.createBuffer({
        size: numbersList.byteLength,
        label: 'StagingBuffer',
        usage: GPUBufferUsage.MAP_READ | GPUBufferUsage.COPY_DST,
      });

      const storageBuffer = device.createBuffer({
        size: numbersList.byteLength,
        label: 'StorageBuffer',
        usage:
          GPUBufferUsage.STORAGE |
          GPUBufferUsage.COPY_DST |
          GPUBufferUsage.COPY_SRC,
      });

      const bindGroupLayout = device.createBindGroupLayout({
        label: 'TestBindGroupLayout',
        entries: [
          {
            binding: 0,
            visibility: GPUShaderStage.COMPUTE,
            buffer: { type: 'storage' },
          },
        ],
      });

      const bindGroup = device.createBindGroup({
        label: 'TestBindGroup',
        layout: bindGroupLayout,
        entries: [{ binding: 0, resource: { buffer: storageBuffer } }],
      });

      const sampler = device.createSampler({
        label: 'TestSampler',
        magFilter: 'linear',
        minFilter: 'linear',
      });

      const shaderModule = device.createShaderModule({
        code: SHADER_CODE,
        label: 'TestShaderModule',
      });

      const commandEncoder = device.createCommandEncoder({
        label: 'TestCommandEncoder',
      });

      const texture = device.createTexture({
        label: 'TestTexture',
        size: [240, 510, 1],
        format: 'rgba8unorm',
        usage:
          GPUTextureUsage.TEXTURE_BINDING |
          GPUTextureUsage.COPY_DST |
          GPUTextureUsage.RENDER_ATTACHMENT,
      });

      console.log('textureFormat', texture.format);

      const pipelineLayout = device.createPipelineLayout({
        label: 'TestPipelineLayout',
        bindGroupLayouts: [bindGroupLayout],
      });

      const computePipeline = device.createComputePipeline({
        label: 'TestComputePipeline',
        layout: pipelineLayout,
        compute: {
          module: shaderModule,
          entryPoint: 'main',
        },
      });

      const passEncoder = commandEncoder.beginComputePass({
        label: 'TestComputePassEncoder',
      });

      passEncoder.setPipeline(computePipeline);
      passEncoder.setBindGroup(0, bindGroup);
      passEncoder.dispatchWorkgroups(numbersList.length, 1, 1);
      passEncoder.end();

      commandEncoder.copyBufferToBuffer(
        storageBuffer,
        0,
        stagingBuffer,
        0,
        numbersList.byteLength
      );

      device.queue.writeBuffer(storageBuffer, 0, numbersList.buffer);
      device.queue.submit([commandEncoder.finish()]);

      console.log('submitted work');

      await stagingBuffer.mapAsync(GPUMapMode.MAP_READ);

      console.log('mapAsyncComplete');

      const mappedRange = new Uint32Array(stagingBuffer.getMappedRange());
      console.log('mappedRange', mappedRange);
      setResult(new Uint32Array(mappedRange));

      console.log('buffer', storageBuffer);
      console.log('queue', device.queue);
      console.log('sampler', sampler);
      console.log('shaderModule', shaderModule);
      console.log('commandEncoder', commandEncoder);
      console.log('texture', texture);
      console.log('bindGroupLayout', bindGroupLayout);
      console.log('bindGroup', bindGroup);
      console.log('pipelineLayout', pipelineLayout);
      console.log('computePipeline', computePipeline);
    } catch (error) {
      console.log(error);
    }
  };

  const [result, setResult] = useState<Uint32Array | null>(null);

  const [text, setText] = useState('1, 2, 3, 4');

  const handleChangeText = (text: string) => {
    setText(text);
  };

  return (
    <View style={styles.container}>
      <Text style={{ fontSize: 20, fontWeight: 'bold' }}>
        Collatz Conjecture
      </Text>
      <TextInput
        style={{
          width: '100%',
          height: 40,
          borderColor: 'gray',
          borderWidth: 1,
          paddingHorizontal: 8,
        }}
        onChangeText={handleChangeText}
        value={text}
      />
      <Button onPress={handleClick} title="Compute" />
      {result ? (
        <Text style={{ fontSize: 20, fontWeight: 'bold' }}>
          {result.join(', ')}
        </Text>
      ) : null}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    gap: 16,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
