Pod::Spec.new do |s|

s.name = "MSME"
s.version = "2.0.0"
s.summary = "MSME static library"

s.description = <<-DESC
This iOS Static library is used to explain how to distribute iOS Static library via cocoapods
DESC

s.homepage = "http://www.m800.com"
s.license = { :type => "BSD", :file => "LICENSE" }

s.author = { "M800 Limited" => "support@m800.com" }

s.platform = :ios, "7.0"
s.source = { :git => "https://github.com/m800-matthewlo/MSME.git", :tag => s.version.to_s}
s.source_files = "include/*.h"
s.public_header_files = "include/*.h"
s.frameworks       = 'Foundation'

s.preserve_paths = "libMSME-ios.a"
s.ios.vendored_library = "libMSME-ios.a"
end