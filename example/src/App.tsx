import { Text, View, StyleSheet, Pressable } from 'react-native';
import { Instance, GPUBufferUsage } from 'react-native-webgpu-rs';

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
      console.log('buffer', buffer);
      console.log('queue', device.queue);
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
