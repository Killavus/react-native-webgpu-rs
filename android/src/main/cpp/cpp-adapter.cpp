#include <jni.h>
#include "webgpursOnLoad.hpp"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
  return margelo::nitro::webgpurs::initialize(vm);
}
