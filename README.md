# react-native-webgpu-rs

React Native WebGPU implementation (with gfx-rs/wgpu)

## Pre-release warning

Right now due to lack of XCFramework setup library works only on iOS simulator. This should be solved soon since there is a clear path to make it work.

## Building 

Download latest `wgpu-native` release from [`wgpu-native` releases page](https://github.com/gfx-rs/wgpu-native/releases). Choose `wgpu-ios-aarch64-simulator-release` build and unzip it into `wgpu-native/` directory of this repository.


## Installation

Package is not published yet.

## Usage


```js
import { Instance } from 'react-native-webgpu-rs';

const adapter = await Instance.requestAdapter();

// The rest follows WebGPU spec.
```


## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
