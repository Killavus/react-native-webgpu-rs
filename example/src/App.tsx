import { Text, View, StyleSheet, Pressable } from 'react-native';
import { Instance, GPUBufferUsage } from 'react-native-webgpu-rs';

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
        usage: GPUBufferUsage.COPY_SRC | GPUBufferUsage.COPY_DST,
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

      console.log('buffer', buffer);
      console.log('queue', device.queue);
      console.log('sampler', sampler);
      console.log('shaderModule', shaderModule);
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
