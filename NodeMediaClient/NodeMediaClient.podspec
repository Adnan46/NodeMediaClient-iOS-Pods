Pod::Spec.new do |s|

  s.name          = 'NodeMediaClient'
  s.version       = '2.9.6'
  s.summary       = 'A live streaming SDK.'
  s.license       = { :type => 'Copyright', :text => 'Copyright 2020 NodeMedia Ltd. All rights reserved.' }
  s.homepage      = 'http://www.nodemedia.cn'
  s.author        = { 'Mingliang Chen' => 'illuspas@gmail.com' }
  s.source        = { :git => 'https://github.com/NodeMedia/NodeMediaClient-iOS.git', :tag => s.version }
  s.platform      = :ios, '8.0'
  s.source_files  = 'NodeMediaClient/NodeMediaClient.framework/Headers/*.{h}'
  s.vendored_frameworks = 'NodeMediaClient/NodeMediaClient.framework'
  s.public_header_files = 'NodeMediaClient/NodeMediaClient.framework/Headers/NodeMediaClient.h'
  s.libraries     = 'z'
  s.frameworks    = 'CoreMedia','AudioToolbox','VideoToolbox','AVFoundation'
end
