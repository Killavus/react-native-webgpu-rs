#include "WebGPUQueue.hpp"
#include "WGPUTypeConversions.hpp"
#include "WebGPUBuffer.hpp"
#include "WebGPUCommandBuffer.hpp"
#include "WebGPUTexture.hpp"
#include "WGPUInternalConstants.hpp"

namespace margelo::nitro {
WebGPUQueue::WebGPUQueue() : HybridObject(TAG), queue_(nullptr) {}
WebGPUQueue::WebGPUQueue(WGPUQueue queue) : HybridObject(TAG), queue_(queue) {}
WebGPUQueue::~WebGPUQueue() {}

void WebGPUQueue::submit(
    const std::vector<std::shared_ptr<HybridNitroWGPUCommandBufferSpec>>
        &commandBuffers) {
  std::vector<WGPUCommandBuffer> wgpuBuffers;
  wgpuBuffers.reserve(commandBuffers.size());

  for (const auto &commandBuffer : commandBuffers) {
    auto wgpuBuffer =
        dynamic_cast<WebGPUCommandBuffer *>(commandBuffer.get())->resource();

    wgpuBuffers.push_back(wgpuBuffer);
  }

  wgpuQueueSubmit(queue_, wgpuBuffers.size(), wgpuBuffers.data());
}

void WebGPUQueue::writeBuffer(
    const std::shared_ptr<HybridNitroWGPUBufferSpec> &buffer,
    double bufferOffset, const std::shared_ptr<ArrayBuffer> &data,
    std::optional<double> dataOffset, std::optional<double> size) {
  auto wgpuBuffer = dynamic_cast<WebGPUBuffer *>(buffer.get())->resource();

  wgpuQueueWriteBuffer(queue_, wgpuBuffer, (uint64_t)bufferOffset,
                       data.get()->data() + (uint64_t)dataOffset.value_or(0),
                       size.value_or(wgpuBufferGetSize(wgpuBuffer) -
                                     (size_t)dataOffset.value_or(0)));
}

void WebGPUQueue::writeTexture(
    const TextureCopyDescriptor &source,
    const std::shared_ptr<ArrayBuffer> &data,
    const TextureCopyDataLayout &dataLayout,
    const std::variant<std::vector<double>, TextureCopyExtentObject> &size) {
  WGPUTexelCopyTextureInfo wgpuDestination{0};
  WGPUTexelCopyBufferLayout wgpuDataLayout{0};
  WGPUExtent3D wgpuExtent{0};

  wgpuDestination.texture =
      dynamic_cast<WebGPUTexture *>(source.texture.get())->resource();
  wgpuDestination.aspect = source.aspect.has_value()
                               ? toWGPUTextureAspect(source.aspect.value())
                               : WGPUTextureAspect_All;
  wgpuDestination.mipLevel = (uint32_t)source.mipLevel.value_or(0);

  wgpuDestination.origin = {.x = 0, .y = 0, .z = 0};
  if (source.origin.has_value()) {
    auto sourceOrigin = source.origin.value();

    if (std::holds_alternative<TextureCopyOriginObject>(sourceOrigin)) {
      auto sourceOriginObject = std::get<TextureCopyOriginObject>(sourceOrigin);

      wgpuDestination.origin = {.x = (uint32_t)sourceOriginObject.x,
                                .y = (uint32_t)sourceOriginObject.y,
                                .z = (uint32_t)sourceOriginObject.z};
    } else {
      auto sourceOriginArray = std::get<std::vector<double>>(sourceOrigin);
      if (sourceOriginArray.size() > 2) {
        wgpuDestination.origin = {.x = (uint32_t)sourceOriginArray[0],
                                  .y = (uint32_t)sourceOriginArray[1],
                                  .z = (uint32_t)sourceOriginArray[2]};
      }
    }
  }

  if (std::holds_alternative<TextureCopyExtentObject>(size)) {
    auto sizeObject = std::get<TextureCopyExtentObject>(size);

    wgpuExtent.width = (uint32_t)sizeObject.width;
    wgpuExtent.height = (uint32_t)sizeObject.height.value_or(1);
    wgpuExtent.depthOrArrayLayers =
        (uint32_t)sizeObject.depthOrArrayLayers.value_or(1);
  } else {
    auto sizeArray = std::get<std::vector<double>>(size);

    wgpuExtent.width = sizeArray.size() > 0
                           ? (uint32_t)sizeArray[0]
                           : wgpuTextureGetWidth(dynamic_cast<WebGPUTexture *>(
                                                     source.texture.get())
                                                     ->resource());
    wgpuExtent.height = sizeArray.size() > 1 ? (uint32_t)sizeArray[1] : 1;
    wgpuExtent.depthOrArrayLayers =
        sizeArray.size() > 2 ? (uint32_t)sizeArray[2] : 1;
  }

  wgpuDataLayout.offset = (uint64_t)dataLayout.offset.value_or(0);
  wgpuDataLayout.bytesPerRow = dataLayout.bytesPerRow.has_value()
                                   ? (uint32_t)dataLayout.bytesPerRow.value()
                                   : WGPU_COPY_STRIDE_UNDEFINED;
  wgpuDataLayout.rowsPerImage = dataLayout.rowsPerImage.has_value()
                                    ? (uint32_t)dataLayout.rowsPerImage.value()
                                    : WGPU_COPY_STRIDE_UNDEFINED;

  wgpuQueueWriteTexture(queue_, &wgpuDestination, (void *)data->data(),
                        data->size(), &wgpuDataLayout, &wgpuExtent);
}

    void WebGPUQueue::setLabel(const std::string &label) {
        WGPUStringView view { label.c_str(), WGPU_STRLEN };
        wgpuQueueSetLabel(queue_, view);
    }

    std::string WebGPUQueue::getLabel() {
        return NOT_IMPLEMENTED_LABEL_TEXT;
    }


} // namespace margelo::nitro
