#include "WebGPUCommandEncoder.hpp"
#include "WGPUTypeConversions.hpp"
#include "WebGPUBuffer.hpp"
#include "WebGPUCommandBuffer.hpp"
#include "WebGPUComputePassEncoder.hpp"
#include "WebGPUTexture.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUCommandEncoder::WebGPUCommandEncoder()
    : HybridObject(TAG), commandEncoder_(nullptr) {}
WebGPUCommandEncoder::WebGPUCommandEncoder(WGPUCommandEncoder commandEncoder)
    : HybridObject(TAG), commandEncoder_(commandEncoder) {}
WebGPUCommandEncoder::~WebGPUCommandEncoder() {
  if (commandEncoder_) {
    wgpuCommandEncoderRelease(commandEncoder_);
  }
}

std::shared_ptr<HybridNitroWGPUComputePassEncoderSpec>
WebGPUCommandEncoder::beginComputePass(
    const ComputePassDescriptor &descriptor) {
  WGPUComputePassDescriptor wgpuDescriptor{0};

  wgpuDescriptor.nextInChain = nullptr;
  // TODO: Support timestamp writes.
  wgpuDescriptor.timestampWrites = nullptr;
  wgpuDescriptor.label = {nullptr, WGPU_STRLEN};
  if (descriptor.label.has_value()) {
    wgpuDescriptor.label = {descriptor.label.value().c_str(), WGPU_STRLEN};
  }

  WGPUComputePassEncoder encoder{
      wgpuCommandEncoderBeginComputePass(commandEncoder_, &wgpuDescriptor)};

  return std::make_shared<WebGPUComputePassEncoder>(encoder);
};

std::shared_ptr<HybridNitroWGPUCommandBufferSpec> WebGPUCommandEncoder::finish(
    const std::optional<CommandBufferDescriptor> &descriptor) {
  if (descriptor.has_value()) {
    WGPUCommandBufferDescriptor wgpuDescriptor{0};
    wgpuDescriptor.nextInChain = nullptr;
    wgpuDescriptor.label = {nullptr, WGPU_STRLEN};

    if (descriptor.value().label.has_value()) {
      wgpuDescriptor.label = {descriptor.value().label.value().c_str(),
                              WGPU_STRLEN};
    }

    WGPUCommandBuffer cmdBuffer{
        wgpuCommandEncoderFinish(commandEncoder_, &wgpuDescriptor)};

    return std::make_shared<WebGPUCommandBuffer>(cmdBuffer);
  } else {
    WGPUCommandBuffer cmdBuffer{
        wgpuCommandEncoderFinish(commandEncoder_, nullptr)};
    return std::make_shared<WebGPUCommandBuffer>(cmdBuffer);
  }
};

void WebGPUCommandEncoder::copyBufferToBuffer(
    const std::shared_ptr<HybridNitroWGPUBufferSpec> &source,
    double sourceOffset,
    const std::shared_ptr<HybridNitroWGPUBufferSpec> &destination,
    double destinationOffset, double size) {
  auto wgpuSource = dynamic_cast<WebGPUBuffer *>(source.get())->resource();
  auto wgpuDestination =
      dynamic_cast<WebGPUBuffer *>(destination.get())->resource();

  wgpuCommandEncoderCopyBufferToBuffer(
      commandEncoder_, wgpuSource, (uint64_t)sourceOffset, wgpuDestination,
      (uint64_t)destinationOffset, (uint64_t)size);
}

void WebGPUCommandEncoder::clearBuffer(
    const std::shared_ptr<HybridNitroWGPUBufferSpec> &buffer,
    std::optional<double> offset, std::optional<double> size) {
  auto webgpuBuffer = dynamic_cast<WebGPUBuffer *>(buffer.get())->resource();

  wgpuCommandEncoderClearBuffer(
      commandEncoder_, webgpuBuffer, (uint64_t)offset.value_or(0),
      size.has_value()
          ? (uint64_t)size.value()
          : wgpuBufferGetSize(webgpuBuffer) - (uint64_t)offset.value_or(0));
}

void WebGPUCommandEncoder::copyBufferToTexture(
    const BufferCopyDescriptor &source,
    const TextureCopyDescriptor &destination,
    const std::variant<std::vector<double>, TextureCopyExtentObject>
        &copySize) {
  WGPUTexelCopyBufferInfo wgpuSource{0};

  wgpuSource.layout.offset = (uint64_t)source.offset.value_or(0);
  wgpuSource.layout.bytesPerRow = source.bytesPerRow.has_value()
                                      ? (uint32_t)source.bytesPerRow.value()
                                      : WGPU_COPY_STRIDE_UNDEFINED;
  wgpuSource.layout.rowsPerImage = source.rowsPerImage.has_value()
                                       ? (uint32_t)source.rowsPerImage.value()
                                       : WGPU_COPY_STRIDE_UNDEFINED;

  wgpuSource.buffer =
      dynamic_cast<WebGPUBuffer *>(source.buffer.get())->resource();

  WGPUTexelCopyTextureInfo wgpuDestination{0};
  wgpuDestination.texture =
      dynamic_cast<WebGPUTexture *>(destination.texture.get())->resource();
  wgpuDestination.aspect = destination.aspect.has_value()
                               ? toWGPUTextureAspect(destination.aspect.value())
                               : WGPUTextureAspect_All;
  wgpuDestination.mipLevel = (uint32_t)destination.mipLevel.value_or(0);
  wgpuDestination.origin = {.x = 0, .y = 0, .z = 0};
  if (destination.origin.has_value()) {
    auto destinationOrigin = destination.origin.value();

    if (std::holds_alternative<TextureCopyOriginObject>(destinationOrigin)) {
      auto destinationOriginObject =
          std::get<TextureCopyOriginObject>(destinationOrigin);

      wgpuDestination.origin = {.x = (uint32_t)destinationOriginObject.x,
                                .y = (uint32_t)destinationOriginObject.y,
                                .z = (uint32_t)destinationOriginObject.z};
    } else {
      auto destinationOriginArray =
          std::get<std::vector<double>>(destinationOrigin);
      if (destinationOriginArray.size() > 2) {
        wgpuDestination.origin = {.x = (uint32_t)destinationOriginArray[0],
                                  .y = (uint32_t)destinationOriginArray[1],
                                  .z = (uint32_t)destinationOriginArray[2]};
      }
    }
  }

  WGPUExtent3D wgpuExtent{0};
  if (std::holds_alternative<TextureCopyExtentObject>(copySize)) {
    auto sizeObject = std::get<TextureCopyExtentObject>(copySize);

    wgpuExtent.width = (uint32_t)sizeObject.width;
    wgpuExtent.height = (uint32_t)sizeObject.height.value_or(1);
    wgpuExtent.depthOrArrayLayers =
        (uint32_t)sizeObject.depthOrArrayLayers.value_or(1);
  } else {
    auto sizeArray = std::get<std::vector<double>>(copySize);

    wgpuExtent.width = sizeArray.size() > 0
                           ? (uint32_t)sizeArray[0]
                           : wgpuTextureGetWidth(dynamic_cast<WebGPUTexture *>(
                                                     destination.texture.get())
                                                     ->resource());
    wgpuExtent.height = sizeArray.size() > 1 ? (uint32_t)sizeArray[1] : 1;
    wgpuExtent.depthOrArrayLayers =
        sizeArray.size() > 2 ? (uint32_t)sizeArray[2] : 1;
  }

  wgpuCommandEncoderCopyBufferToTexture(commandEncoder_, &wgpuSource,
                                        &wgpuDestination, &wgpuExtent);
}

void WebGPUCommandEncoder::copyTextureToTexture(
    const TextureCopyDescriptor &source,
    const TextureCopyDescriptor &destination,
    const std::variant<std::vector<double>, TextureCopyExtentObject>
        &copySize) {
  WGPUTexelCopyTextureInfo wgpuSource{0};
  wgpuSource.texture =
      dynamic_cast<WebGPUTexture *>(source.texture.get())->resource();
  wgpuSource.aspect = source.aspect.has_value()
                          ? toWGPUTextureAspect(source.aspect.value())
                          : WGPUTextureAspect_All;
  wgpuSource.mipLevel = (uint32_t)source.mipLevel.value_or(0);
  wgpuSource.origin = {.x = 0, .y = 0, .z = 0};
  if (source.origin.has_value()) {
    auto sourceOrigin = source.origin.value();

    if (std::holds_alternative<TextureCopyOriginObject>(sourceOrigin)) {
      auto sourceOriginObject = std::get<TextureCopyOriginObject>(sourceOrigin);

      wgpuSource.origin = {.x = (uint32_t)sourceOriginObject.x,
                           .y = (uint32_t)sourceOriginObject.y,
                           .z = (uint32_t)sourceOriginObject.z};
    } else {
      auto sourceOriginObjectArray =
          std::get<std::vector<double>>(sourceOrigin);
      if (sourceOriginObjectArray.size() > 2) {
        wgpuSource.origin = {.x = (uint32_t)sourceOriginObjectArray[0],
                             .y = (uint32_t)sourceOriginObjectArray[1],
                             .z = (uint32_t)sourceOriginObjectArray[2]};
      }
    }
  }

  WGPUTexelCopyTextureInfo wgpuDestination{0};
  wgpuDestination.texture =
      dynamic_cast<WebGPUTexture *>(destination.texture.get())->resource();
  wgpuDestination.aspect = destination.aspect.has_value()
                               ? toWGPUTextureAspect(destination.aspect.value())
                               : WGPUTextureAspect_All;
  wgpuDestination.mipLevel = (uint32_t)destination.mipLevel.value_or(0);
  wgpuDestination.origin = {.x = 0, .y = 0, .z = 0};
  if (destination.origin.has_value()) {
    auto destinationOrigin = destination.origin.value();

    if (std::holds_alternative<TextureCopyOriginObject>(destinationOrigin)) {
      auto destinationOriginObject =
          std::get<TextureCopyOriginObject>(destinationOrigin);

      wgpuDestination.origin = {.x = (uint32_t)destinationOriginObject.x,
                                .y = (uint32_t)destinationOriginObject.y,
                                .z = (uint32_t)destinationOriginObject.z};
    } else {
      auto destinationOriginArray =
          std::get<std::vector<double>>(destinationOrigin);
      if (destinationOriginArray.size() > 2) {
        wgpuDestination.origin = {.x = (uint32_t)destinationOriginArray[0],
                                  .y = (uint32_t)destinationOriginArray[1],
                                  .z = (uint32_t)destinationOriginArray[2]};
      }
    }
  }

  WGPUExtent3D wgpuExtent{0};
  if (std::holds_alternative<TextureCopyExtentObject>(copySize)) {
    auto sizeObject = std::get<TextureCopyExtentObject>(copySize);

    wgpuExtent.width = (uint32_t)sizeObject.width;
    wgpuExtent.height = (uint32_t)sizeObject.height.value_or(1);
    wgpuExtent.depthOrArrayLayers =
        (uint32_t)sizeObject.depthOrArrayLayers.value_or(1);
  } else {
    auto sizeArray = std::get<std::vector<double>>(copySize);

    wgpuExtent.width = sizeArray.size() > 0
                           ? (uint32_t)sizeArray[0]
                           : wgpuTextureGetWidth(dynamic_cast<WebGPUTexture *>(
                                                     destination.texture.get())
                                                     ->resource());
    wgpuExtent.height = sizeArray.size() > 1 ? (uint32_t)sizeArray[1] : 1;
    wgpuExtent.depthOrArrayLayers =
        sizeArray.size() > 2 ? (uint32_t)sizeArray[2] : 1;
  }

  wgpuCommandEncoderCopyTextureToTexture(commandEncoder_, &wgpuSource,
                                         &wgpuDestination, &wgpuExtent);
}

void WebGPUCommandEncoder::copyTextureToBuffer(
    const TextureCopyDescriptor &source,
    const BufferCopyDescriptor &destination,
    const std::variant<std::vector<double>, TextureCopyExtentObject>
        &copySize) {

  WGPUTexelCopyTextureInfo wgpuSource{0};
  wgpuSource.texture =
      dynamic_cast<WebGPUTexture *>(source.texture.get())->resource();
  wgpuSource.aspect = source.aspect.has_value()
                          ? toWGPUTextureAspect(source.aspect.value())
                          : WGPUTextureAspect_All;
  wgpuSource.mipLevel = (uint32_t)source.mipLevel.value_or(0);
  wgpuSource.origin = {.x = 0, .y = 0, .z = 0};
  if (source.origin.has_value()) {
    auto sourceOrigin = source.origin.value();

    if (std::holds_alternative<TextureCopyOriginObject>(sourceOrigin)) {
      auto sourceOriginObject = std::get<TextureCopyOriginObject>(sourceOrigin);

      wgpuSource.origin = {.x = (uint32_t)sourceOriginObject.x,
                           .y = (uint32_t)sourceOriginObject.y,
                           .z = (uint32_t)sourceOriginObject.z};
    } else {
      auto sourceOriginObjectArray =
          std::get<std::vector<double>>(sourceOrigin);
      if (sourceOriginObjectArray.size() > 2) {
        wgpuSource.origin = {.x = (uint32_t)sourceOriginObjectArray[0],
                             .y = (uint32_t)sourceOriginObjectArray[1],
                             .z = (uint32_t)sourceOriginObjectArray[2]};
      }
    }
  }

  WGPUTexelCopyBufferInfo wgpuDestination{0};
  wgpuDestination.layout.offset = (uint64_t)destination.offset.value_or(0);
  wgpuDestination.layout.bytesPerRow =
      destination.bytesPerRow.has_value()
          ? (uint32_t)destination.bytesPerRow.value()
          : WGPU_COPY_STRIDE_UNDEFINED;
  wgpuDestination.layout.rowsPerImage =
      destination.rowsPerImage.has_value()
          ? (uint32_t)destination.rowsPerImage.value()
          : WGPU_COPY_STRIDE_UNDEFINED;

  wgpuDestination.buffer =
      dynamic_cast<WebGPUBuffer *>(destination.buffer.get())->resource();

  WGPUExtent3D wgpuExtent{0};
  if (std::holds_alternative<TextureCopyExtentObject>(copySize)) {
    auto sizeObject = std::get<TextureCopyExtentObject>(copySize);

    wgpuExtent.width = (uint32_t)sizeObject.width;
    wgpuExtent.height = (uint32_t)sizeObject.height.value_or(1);
    wgpuExtent.depthOrArrayLayers =
        (uint32_t)sizeObject.depthOrArrayLayers.value_or(1);
  } else {
    auto sizeArray = std::get<std::vector<double>>(copySize);

    wgpuExtent.width = sizeArray.size() > 0
                           ? (uint32_t)sizeArray[0]
                           : wgpuTextureGetWidth(dynamic_cast<WebGPUTexture *>(
                                                     source.texture.get())
                                                     ->resource());
    wgpuExtent.height = sizeArray.size() > 1 ? (uint32_t)sizeArray[1] : 1;
    wgpuExtent.depthOrArrayLayers =
        sizeArray.size() > 2 ? (uint32_t)sizeArray[2] : 1;
  }
}

    void WebGPUCommandEncoder::setLabel(const std::string &label) {
        WGPUStringView view { label.c_str(), WGPU_STRLEN };
        wgpuCommandEncoderSetLabel(commandEncoder_, view);
    }

    std::string WebGPUCommandEncoder::getLabel() {
        return NOT_IMPLEMENTED_LABEL_TEXT;
    }

} // namespace margelo::nitro
