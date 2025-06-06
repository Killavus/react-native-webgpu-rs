package com.margelo.nitro.webgpurs
  
import com.facebook.proguard.annotations.DoNotStrip

@DoNotStrip
class WebgpuRs : HybridWebgpuRsSpec() {
  override fun multiply(a: Double, b: Double): Double {
    return a * b
  }
}
