project(webgpurs)
cmake_minimum_required(VERSION 3.9.0)

set(PACKAGE_NAME webgpurs)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

add_library(wgpu_native STATIC IMPORTED)

set_target_properties(wgpu_native PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../wgpu-native/android/lib/${CMAKE_ANDROID_ARCH_ABI}/libwgpu_native.a"
)

target_include_directories(wgpu_native INTERFACE "../wgpu-native/android/include")

# Define C++ library and add all sources
add_library(${PACKAGE_NAME} SHARED src/main/cpp/cpp-adapter.cpp
  "../cpp/WebGPUAdapter.cpp"
  "../cpp/WebGPUBindGroup.cpp"
  "../cpp/WebGPUBindGroupLayout.cpp"
  "../cpp/WebGPUBuffer.cpp"
  "../cpp/WebGPUCommandBuffer.cpp"
  "../cpp/WebGPUCommandEncoder.cpp"
  "../cpp/WebGPUComputePassEncoder.cpp"
  "../cpp/WebGPUComputePipeline.cpp"
  "../cpp/WebGPUDevice.cpp"
  "../cpp/WebGPUInstance.cpp"
  "../cpp/WebGPUPipelineLayout.cpp"
  "../cpp/WebGPUQueue.cpp"
  "../cpp/WebGPUSampler.cpp"
  "../cpp/WebGPUShaderModule.cpp"
  "../cpp/WebGPUTexture.cpp"
  "../cpp/WebGPUTextureView.cpp"
  "../cpp/WGPUTypeConversions.cpp"
)

# Add Nitrogen specs :)
include(${CMAKE_SOURCE_DIR}/../nitrogen/generated/android/webgpurs+autolinking.cmake)

# Set up local includes
target_include_directories(${PACKAGE_NAME} PRIVATE "../cpp")
target_include_directories(${PACKAGE_NAME} PRIVATE "src/main/cpp" "../cpp")

find_library(LOG_LIB log)

# Link all libraries together
target_link_libraries(
        ${PACKAGE_NAME}
        ${LOG_LIB}
        wgpu_native
        android # <-- Android core
)
