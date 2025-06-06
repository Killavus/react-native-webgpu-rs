import { Text, View, StyleSheet, Pressable } from 'react-native';
import {
  Instance,
  GPUBufferUsage,
  GPUTextureUsage,
  GPUShaderStage,
} from 'react-native-webgpu-rs';

const SHADER_CODE = `
struct VertexOut {
  @builtin(position) position : vec4f,
  @location(0) color : vec4f
}

@vertex
fn vertex_main(@location(0) position: vec4f,
               @location(1) color: vec4f) -> VertexOut
{
  var output : VertexOut;
  output.position = position;
  output.color = color;
  return output;
}

@fragment
fn fragment_main(fragData: VertexOut) -> @location(0) vec4f
{
  return fragData.color;
}
`;

export default function App() {
  Instance.enumerateAdapters();

  const handleClick = async () => {
    try {
      const adapter = await Instance.requestAdapter();
      console.log('adapter', adapter);
      const device = await adapter.requestDevice();
      console.log('device', device);
      const buffer = device.createBuffer({
        size: 1024,
        label: 'TestBuffer',
        mappedAtCreation: true,
        usage:
          GPUBufferUsage.COPY_SRC |
          GPUBufferUsage.COPY_DST |
          GPUBufferUsage.UNIFORM,
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
        size: [512, 512, 1],
        format: 'rgba8unorm',
        usage:
          GPUTextureUsage.TEXTURE_BINDING |
          GPUTextureUsage.COPY_DST |
          GPUTextureUsage.RENDER_ATTACHMENT,
      });

      const bindGroupLayout = device.createBindGroupLayout({
        label: 'TestBindGroupLayout',
        entries: [
          {
            binding: 0,
            visibility: GPUShaderStage.VERTEX,
            buffer: {
              type: 'uniform',
            },
          },
        ],
      });

      const bindGroup = device.createBindGroup({
        label: 'TestBindGroup',
        layout: bindGroupLayout,
        entries: [{ binding: 0, resource: { buffer } }],
      });

      console.log('buffer', buffer);
      console.log('queue', device.queue);
      console.log('sampler', sampler);
      console.log('shaderModule', shaderModule);
      console.log('commandEncoder', commandEncoder);
      console.log('texture', texture);
      console.log('bindGroupLayout', bindGroupLayout);
      console.log('bindGroup', bindGroup);
    } catch (error) {
      console.log(error);
    }
  };

  return (
    <View style={styles.container}>
      <Pressable onPress={handleClick}>
        <Text>Click me</Text>
      </Pressable>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
