# react-native-webgpu-rs

React Native WebGPU implementation (with gfx-rs/wgpu)

## Pre-release warning

Right now due to lack of XCFramework setup library works only on iOS simulator. This should be solved soon since there is a clear path to make it work.

## Building

Download latest `wgpu-native` release from [`wgpu-native` releases page](https://github.com/gfx-rs/wgpu-native/releases). Choose `wgpu-ios-aarch64-simulator-release` build and unzip it into `wgpu-native/` directory of this repository.

### Android:

Create `wgpu-native/android` directory. Download releases:

- `wgpu-android-aarch64-release.zip`
- `wgpu-android-armv7-release.zip`
- `wgpu-android-i686-release.zip`
- `wgpu-android-x86_64-release.zip`

Unpack them and create the following structure:

- `wgpu-native/android/lib/x86_64` - put `libwgpu_native.a` from `wgpu-android-x86_64-release.zip` inside
- `wgpu-native/android/lib/x86` - put `libwgpu_native.a` from `wgpu-android-i686-release.zip` inside
- `wgpu-native/android/lib/armeabi-v7a` - put `libwgpu_native.a` from `wgpu-android-armv7-release.zip` inside
- `wgpu-native/android/lib/arm64-v8a` - put `libwgpu_native.a` from `wgpu-android-aarch64-release.zip` inside

Get `include/` directory from any of the releases and put it into `wgpu-native/android/include` directory.

Your directory tree should look like this:

```
android
├───include
│   └───webgpu
│           webgpu.h
│           wgpu.h
│
└───lib
    ├───arm64-v8a
    │       libwgpu_native.a
    │
    ├───armeabi-v7a
    │       libwgpu_native.a
    │
    ├───x86
    │       libwgpu_native.a
    │
    └───x86_64
            libwgpu_native.a
```

This process will be automated in future releases.

Install dependencies:

```
yarn install
```

Run Nitro codegen:

```
yarn nitrogen && cd example/ios && pod install && cd ../..
```

And run example app on simulator:

```
yarn example ios
```

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
