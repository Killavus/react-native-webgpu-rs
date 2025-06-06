#include "WebGPUAdapter.hpp"
#include "WGPUTypeConversions.hpp"
#include "WebGPUDevice.hpp"

namespace margelo::nitro {

static void handleRequestDevice(WGPURequestDeviceStatus status,
                                WGPUDevice device, WGPUStringView message,
                                void *userdata1, void *userdata2) {

  auto promise = reinterpret_cast<
      std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUDeviceSpec>>> *>(
      userdata1);
  auto gpuAdapter = static_cast<WebGPUAdapter *>(userdata2);

  switch (status) {
  case WGPURequestDeviceStatus_Error:
    promise->get()->reject(std::make_exception_ptr(message.data));
    delete promise;
    break;
  case WGPURequestDeviceStatus_Success:
    promise->get()->resolve(
        std::make_shared<WebGPUDevice>(device, gpuAdapter->getInfo()));
    delete promise;
    break;
  case WGPURequestDeviceStatus_Unknown:
    break;
  case WGPURequestDeviceStatus_InstanceDropped:
    promise->get()->reject(std::make_exception_ptr(message.data));
    delete promise;
    break;
  default:
    return;
  }
}

static const char *stringifyErrorType(const WGPUErrorType &errorType) {
  switch (errorType) {
  case WGPUErrorType_Internal:
    return "WebGPU::InternalError";
  case WGPUErrorType_Unknown:
    return "WebGPU::UnknownError";
  case WGPUErrorType_NoError:
    return "WebGPU::NoError (?)";
  case WGPUErrorType_Validation:
    return "WebGPU::ValidationError";
  case WGPUErrorType_OutOfMemory:
    return "WebGPU::OutOfMemory";
  default:
    return "WebGPU::UnknownErrorType";
  }
}

// FIXME: There must be a better way to do this than passing instance, shared
// pointers between and so on. This is super messy.
static void handleUncapturedError(WGPUDevice const *device, WGPUErrorType type,
                                  WGPUStringView message, void *userdata1,
                                  void *userdata2) {
  std::stringstream ss;
  ss << "[" << stringifyErrorType(type)
     << "]: " << std::string(message.data, message.length);

  auto errMsg = ss.str();

  auto instance = static_cast<WebGPUInstance *>(userdata1);
  instance->callErrorHandler(errMsg);
}

WebGPUAdapter::WebGPUAdapter()
    : HybridObject(TAG), adapter_(nullptr), instance_(nullptr) {}

WebGPUAdapter::~WebGPUAdapter() {
  if (adapter_) {
    wgpuAdapterRelease(adapter_);
  }
}

WebGPUAdapter::WebGPUAdapter(WGPUAdapter adapter,
                             const std::shared_ptr<WebGPUInstance> &instance)
    : HybridObject(TAG), adapter_(adapter), instance_(instance) {}

std::shared_ptr<Promise<std::shared_ptr<HybridNitroWGPUDeviceSpec>>>
WebGPUAdapter::requestDevice(
    const std::optional<DeviceDescriptor> &descriptor) {
  auto promise = Promise<std::shared_ptr<HybridNitroWGPUDeviceSpec>>::create();

  bool hasDescriptor = descriptor.has_value();
  WGPUDeviceDescriptor wgpuDescriptor{0};

  wgpuDescriptor.uncapturedErrorCallbackInfo = {.nextInChain = nullptr,
                                                .callback =
                                                    handleUncapturedError,
                                                .userdata1 = instance_.get()};

  if (hasDescriptor) {
    auto descriptor_ = descriptor.value();
    wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
    if (descriptor_.label.has_value()) {
      wgpuDescriptor.label = {descriptor_.label.value().c_str(), WGPU_STRLEN};
    }

    wgpuDescriptor.defaultQueue.label = {nullptr, WGPU_STRLEN};
    if (descriptor_.defaultQueue.has_value()) {
      if (descriptor_.defaultQueue.value().label.has_value()) {
        wgpuDescriptor.defaultQueue.label = {
            descriptor_.defaultQueue.value().label.value().c_str(),
            WGPU_STRLEN};
      }
    }

    std::vector<WGPUFeatureName> wgpuFeatures;
    if (descriptor_.requiredFeatures.has_value()) {
      auto requiredFeatures = descriptor_.requiredFeatures.value();
      wgpuFeatures.reserve(requiredFeatures.size());

      for (const auto &feature : requiredFeatures) {
        auto wgpuFeature = toWGPUFeatureName(feature);
        if (wgpuFeature != WGPUFeatureName_Undefined) {
          wgpuFeatures.push_back(wgpuFeature);
        }
      }

      wgpuDescriptor.requiredFeatureCount = wgpuFeatures.size();
      wgpuDescriptor.requiredFeatures = wgpuFeatures.data();
    }

    WGPUNativeLimits nativeLimits = {
        .chain =
            {
                .sType = (WGPUSType)WGPUSType_NativeLimits,
            },
    };

    WGPULimits limits{.nextInChain = &nativeLimits.chain};

    wgpuAdapterGetLimits(adapter_, &limits);

    if (descriptor_.requiredLimits.has_value()) {
      auto requiredLimits = descriptor_.requiredLimits.value();
      if (requiredLimits.maxTextureDimension1D.has_value()) {
        limits.maxTextureDimension1D =
            (uint32_t)requiredLimits.maxTextureDimension1D.value();
      }

      if (requiredLimits.maxTextureDimension2D.has_value()) {
        limits.maxTextureDimension2D =
            (uint32_t)requiredLimits.maxTextureDimension2D.value();
      }

      if (requiredLimits.maxTextureDimension3D.has_value()) {
        limits.maxTextureDimension3D =
            (uint32_t)requiredLimits.maxTextureDimension3D.value();
      }

      if (requiredLimits.maxTextureArrayLayers.has_value()) {
        limits.maxTextureArrayLayers =
            (uint32_t)requiredLimits.maxTextureArrayLayers.value();
      }

      if (requiredLimits.maxBindGroups.has_value()) {
        limits.maxBindGroups = (uint32_t)requiredLimits.maxBindGroups.value();
      }

      if (requiredLimits.maxBindingsPerBindGroup.has_value()) {
        limits.maxBindingsPerBindGroup =
            (uint32_t)requiredLimits.maxBindingsPerBindGroup.value();
      }

      if (requiredLimits.maxDynamicUniformBuffersPerPipelineLayout
              .has_value()) {
        limits.maxDynamicUniformBuffersPerPipelineLayout =
            (uint32_t)requiredLimits.maxDynamicUniformBuffersPerPipelineLayout
                .value();
      }

      if (requiredLimits.maxDynamicStorageBuffersPerPipelineLayout
              .has_value()) {
        limits.maxDynamicStorageBuffersPerPipelineLayout =
            (uint32_t)requiredLimits.maxDynamicStorageBuffersPerPipelineLayout
                .value();
      }

      if (requiredLimits.maxSampledTexturesPerShaderStage.has_value()) {
        limits.maxSampledTexturesPerShaderStage =
            (uint32_t)requiredLimits.maxSampledTexturesPerShaderStage.value();
      }

      if (requiredLimits.maxSamplersPerShaderStage.has_value()) {
        limits.maxSamplersPerShaderStage =
            (uint32_t)requiredLimits.maxSamplersPerShaderStage.value();
      }

      if (requiredLimits.maxStorageBuffersPerShaderStage.has_value()) {
        limits.maxStorageBuffersPerShaderStage =
            (uint32_t)requiredLimits.maxStorageBuffersPerShaderStage.value();
      }

      if (requiredLimits.maxStorageTexturesPerShaderStage.has_value()) {
        limits.maxStorageTexturesPerShaderStage =
            (uint32_t)requiredLimits.maxStorageTexturesPerShaderStage.value();
      }

      if (requiredLimits.maxUniformBuffersPerShaderStage.has_value()) {
        limits.maxUniformBuffersPerShaderStage =
            (uint32_t)requiredLimits.maxUniformBuffersPerShaderStage.value();
      }

      if (requiredLimits.maxUniformBufferBindingSize.has_value()) {
        limits.maxUniformBufferBindingSize =
            (uint64_t)requiredLimits.maxUniformBufferBindingSize.value();
      }

      if (requiredLimits.maxStorageBufferBindingSize.has_value()) {
        limits.maxStorageBufferBindingSize =
            (uint64_t)requiredLimits.maxStorageBufferBindingSize.value();
      }

      if (requiredLimits.minUniformBufferOffsetAlignment.has_value()) {
        limits.minUniformBufferOffsetAlignment =
            (uint32_t)requiredLimits.minUniformBufferOffsetAlignment.value();
      }

      if (requiredLimits.minStorageBufferOffsetAlignment.has_value()) {
        limits.minStorageBufferOffsetAlignment =
            (uint32_t)requiredLimits.minStorageBufferOffsetAlignment.value();
      }

      if (requiredLimits.maxVertexBuffers.has_value()) {
        limits.maxVertexBuffers =
            (uint32_t)requiredLimits.maxVertexBuffers.value();
      }

      if (requiredLimits.maxBufferSize.has_value()) {
        limits.maxBufferSize = (uint64_t)requiredLimits.maxBufferSize.value();
      }

      if (requiredLimits.maxVertexAttributes.has_value()) {
        limits.maxVertexAttributes =
            (uint32_t)requiredLimits.maxVertexAttributes.value();
      }

      if (requiredLimits.maxVertexBufferArrayStride.has_value()) {
        limits.maxVertexBufferArrayStride =
            (uint32_t)requiredLimits.maxVertexBufferArrayStride.value();
      }

      if (requiredLimits.maxInterStageShaderVariables.has_value()) {
        limits.maxInterStageShaderVariables =
            (uint32_t)requiredLimits.maxInterStageShaderVariables.value();
      }

      if (requiredLimits.maxColorAttachments.has_value()) {
        limits.maxColorAttachments =
            (uint32_t)requiredLimits.maxColorAttachments.value();
      }

      if (requiredLimits.maxColorAttachmentBytesPerSample.has_value()) {
        limits.maxColorAttachmentBytesPerSample =
            (uint32_t)requiredLimits.maxColorAttachmentBytesPerSample.value();
      }

      if (requiredLimits.maxComputeWorkgroupStorageSize.has_value()) {
        limits.maxComputeWorkgroupStorageSize =
            (uint32_t)requiredLimits.maxComputeWorkgroupStorageSize.value();
      }

      if (requiredLimits.maxComputeInvocationsPerWorkgroup.has_value()) {
        limits.maxComputeInvocationsPerWorkgroup =
            (uint32_t)requiredLimits.maxComputeInvocationsPerWorkgroup.value();
      }

      if (requiredLimits.maxComputeWorkgroupSizeX.has_value()) {
        limits.maxComputeWorkgroupSizeX =
            (uint32_t)requiredLimits.maxComputeWorkgroupSizeX.value();
      }

      if (requiredLimits.maxComputeWorkgroupSizeY.has_value()) {
        limits.maxComputeWorkgroupSizeY =
            (uint32_t)requiredLimits.maxComputeWorkgroupSizeY.value();
      }

      if (requiredLimits.maxComputeWorkgroupSizeZ.has_value()) {
        limits.maxComputeWorkgroupSizeZ =
            (uint32_t)requiredLimits.maxComputeWorkgroupSizeZ.value();
      }

      if (requiredLimits.maxComputeWorkgroupsPerDimension.has_value()) {
        limits.maxComputeWorkgroupsPerDimension =
            (uint32_t)requiredLimits.maxComputeWorkgroupsPerDimension.value();
      }

      if (requiredLimits.ext_maxPushConstantSize.has_value()) {
        nativeLimits.maxPushConstantSize =
            (uint32_t)requiredLimits.ext_maxPushConstantSize.value();
      }

      if (requiredLimits.ext_maxNonSamplerBindings.has_value()) {
        nativeLimits.maxNonSamplerBindings =
            (uint32_t)requiredLimits.ext_maxNonSamplerBindings.value();
      }
    }

    wgpuDescriptor.requiredLimits = &limits;
    wgpuDescriptor.nextInChain = nullptr;
  }

  WGPURequestDeviceCallbackInfo callback{0};
  {
    auto promiseCb = new std::shared_ptr(promise);

    callback.mode = WGPUCallbackMode_WaitAnyOnly;
    callback.userdata1 = (void *)promiseCb;
    callback.userdata2 = this;
    callback.nextInChain = nullptr;
    callback.callback = handleRequestDevice;
  }

  wgpuAdapterRequestDevice(adapter_, &wgpuDescriptor, callback);
  return promise;
}

RequiredLimits WebGPUAdapter::getLimits() {
  RequiredLimits limits;

  WGPUNativeLimits wgpuNativeLimits{
      .chain = {
          .sType = (WGPUSType)WGPUSType_NativeLimits,
      }};

  WGPULimits wgpuLimits{.nextInChain = &wgpuNativeLimits.chain};

  wgpuAdapterGetLimits(adapter_, &wgpuLimits);

  limits.maxTextureDimension1D = wgpuLimits.maxTextureDimension1D;
  limits.maxTextureDimension2D = wgpuLimits.maxTextureDimension2D;
  limits.maxTextureDimension3D = wgpuLimits.maxTextureDimension3D;
  limits.maxTextureArrayLayers = wgpuLimits.maxTextureArrayLayers;
  limits.maxBindGroups = wgpuLimits.maxBindGroups;
  limits.maxBindingsPerBindGroup = wgpuLimits.maxBindingsPerBindGroup;
  limits.maxDynamicUniformBuffersPerPipelineLayout =
      wgpuLimits.maxDynamicUniformBuffersPerPipelineLayout;
  limits.maxDynamicStorageBuffersPerPipelineLayout =
      wgpuLimits.maxDynamicStorageBuffersPerPipelineLayout;
  limits.maxSampledTexturesPerShaderStage =
      wgpuLimits.maxSampledTexturesPerShaderStage;
  limits.maxSamplersPerShaderStage = wgpuLimits.maxSamplersPerShaderStage;
  limits.maxStorageBuffersPerShaderStage =
      wgpuLimits.maxStorageBuffersPerShaderStage;
  limits.maxStorageTexturesPerShaderStage =
      wgpuLimits.maxStorageTexturesPerShaderStage;
  limits.maxUniformBuffersPerShaderStage =
      wgpuLimits.maxUniformBuffersPerShaderStage;
  limits.maxUniformBufferBindingSize = wgpuLimits.maxUniformBufferBindingSize;
  limits.maxStorageBufferBindingSize = wgpuLimits.maxStorageBufferBindingSize;
  limits.minUniformBufferOffsetAlignment =
      wgpuLimits.minUniformBufferOffsetAlignment;
  limits.minStorageBufferOffsetAlignment =
      wgpuLimits.minStorageBufferOffsetAlignment;
  limits.maxVertexBuffers = wgpuLimits.maxVertexBuffers;
  limits.maxBufferSize = wgpuLimits.maxBufferSize;
  limits.maxVertexAttributes = wgpuLimits.maxVertexAttributes;
  limits.maxVertexBufferArrayStride = wgpuLimits.maxVertexBufferArrayStride;
  limits.maxInterStageShaderComponents =
      0; // TODO: Not supported by wgpu-native.
  limits.maxInterStageShaderVariables = wgpuLimits.maxInterStageShaderVariables;
  limits.maxColorAttachments = wgpuLimits.maxColorAttachments;
  limits.maxColorAttachmentBytesPerSample =
      wgpuLimits.maxColorAttachmentBytesPerSample;
  limits.maxComputeWorkgroupStorageSize =
      wgpuLimits.maxComputeWorkgroupStorageSize;
  limits.maxComputeInvocationsPerWorkgroup =
      wgpuLimits.maxComputeInvocationsPerWorkgroup;
  limits.maxComputeWorkgroupSizeX = wgpuLimits.maxComputeWorkgroupSizeX;
  limits.maxComputeWorkgroupSizeY = wgpuLimits.maxComputeWorkgroupSizeY;
  limits.maxComputeWorkgroupSizeZ = wgpuLimits.maxComputeWorkgroupSizeZ;
  limits.maxComputeWorkgroupsPerDimension =
      wgpuLimits.maxComputeWorkgroupsPerDimension;
  limits.ext_maxPushConstantSize = wgpuNativeLimits.maxPushConstantSize;
  limits.ext_maxNonSamplerBindings = wgpuNativeLimits.maxNonSamplerBindings;

  return limits;
}

std::vector<DeviceFeature> WebGPUAdapter::getFeatures() {
  WGPUSupportedFeatures wgpuFeatures;
  wgpuAdapterGetFeatures(adapter_, &wgpuFeatures);
  std::vector<DeviceFeature> features;
  features.reserve(wgpuFeatures.featureCount);

  for (size_t i = 0; i < wgpuFeatures.featureCount; i++) {
    features.push_back(toNitroDeviceFeature(wgpuFeatures.features[i]));
  }

  return features;
}

bool WebGPUAdapter::getIsFallbackAdapter() {
  WGPUAdapterInfo info{0};
  wgpuAdapterGetInfo(adapter_, &info);

  return info.adapterType == WGPUAdapterType_CPU;
}

DeviceInfo WebGPUAdapter::getInfo() {
  DeviceInfo info;
  // TODO: Not supported in wgpu-native.
  info.subgroupMinSize = 0;
  info.subgroupMaxSize = 0;

  WGPUAdapterInfo wgpuInfo{0};
  wgpuAdapterGetInfo(adapter_, &wgpuInfo);

  info.description =
      std::string(wgpuInfo.description.data, wgpuInfo.description.length);
  info.device = std::string(wgpuInfo.device.data, wgpuInfo.device.length);
  info.architecture =
      std::string(wgpuInfo.architecture.data, wgpuInfo.architecture.length);
  info.vendor = std::string(wgpuInfo.vendor.data, wgpuInfo.vendor.length);

  return info;
}

} // namespace margelo::nitro
