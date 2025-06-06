#include "WebGPUQueue.hpp"

namespace margelo::nitro {
WebGPUQueue::WebGPUQueue() : HybridObject(TAG), queue_(nullptr) {}
WebGPUQueue::WebGPUQueue(WGPUQueue queue) : HybridObject(TAG), queue_(queue) {}
WebGPUQueue::~WebGPUQueue() {}
}
