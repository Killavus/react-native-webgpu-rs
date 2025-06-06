require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "WebgpuRs"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => min_ios_version_supported }
  s.source       = { :git => "https://github.com/Killavus/react-native-webgpu-rs.git", :tag => "#{s.version}" }

  s.source_files = ["ios/**/*.{h,m,mm,swift}", "cpp/*.{h,hpp,cpp}"]
  
  # Add wgpu-native headers
  s.pod_target_xcconfig = {
    # 'LIBRARY_SEARCH_PATHS[sdk=iphoneos*]' => '$(PODS_TARGET_SRCROOT)/wgpu-native/wgpu-ios-aarch64-release/lib',
    'LIBRARY_SEARCH_PATHS' => '$(PODS_TARGET_SRCROOT)/wgpu-native/wgpu-ios-aarch64-simulator-release/lib',
    # 'LIBRARY_SEARCH_PATHS[sdk=iphonesimulator*][arch=x86_64]' => '$(PODS_TARGET_SRCROOT)/wgpu-native/wgpu-ios-x86_64-simulator-release/lib',
    'HEADER_SEARCH_PATHS' => '$(PODS_TARGET_SRCROOT)/cpp $(PODS_TARGET_SRCROOT)/wgpu-native/wgpu-ios-aarch64-simulator-release/include',
    'OTHER_LDFLAGS' => '-lwgpu_native',
    'CLANG_CXX_LANGUAGE_STANDARD' => 'c++20',
  }
  
  s.vendored_libraries = ['wgpu-native/wgpu-ios-aarch64-simulator-release/lib/libwgpu_native.a']
  
  s.preserve_paths = [
    'wgpu-native/wgpu-ios-aarch64-simulator-release/**/*'
  ]

  s.frameworks = 'CoreFoundation', 'QuartzCore', 'Metal'

  load 'nitrogen/generated/ios/WebgpuRs+autolinking.rb'
  add_nitrogen_files(s)

  install_modules_dependencies(s)
end
