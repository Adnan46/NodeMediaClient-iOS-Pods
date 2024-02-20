# NodePublisher API
NodePublisher 用于RTMP直播推流, 支持H.264+AAC/SPEEX编码, 16:9 / 4:3 / 1:1画面, 内置GPU加速的美颜滤镜. 

Table of Contents
=================

   * [NodePublisher API](#nodepublisher-api)
      * [属性](#属性)
         * [setOutputUrl](#setoutputurl)
         * [setPageUrl](#setpageurl)
         * [setSwfUrl](#setswfurl)
         * [setConnArgs](#setconnargs)
         * [setCameraPreview:(nonnull UIView*)preView cameraId:(int)cameraId frontMirror:(BOOL)frontMirror](#setcamerapreviewnonnull-uiviewpreview-cameraidintcameraid-frontmirrorboolfrontmirror)
         * [setZoomScale](#setzoomscale)
         * [setFlashEnable](#setflashenable)
         * [setAudioParamBitrate:(int)bitrate profile:(int)profile](#setaudioparambitrateintbitrate-profileintprofile)
         * [setVideoParamPreset:(VideoPreset)preset fps:(int)fps bitrate:(int)bitrate profile:(int)profile frontMirror:(BOOL)frontMirror](#setvideoparampresetvideopresetpreset-fpsintfps-bitrateintbitrate-profileintprofile-frontmirrorboolfrontmirror)
         * [setHwEnable](#sethwenable)
         * [setAutoFocus](#setautofocus)
         * [setBeautyLevel](#setbeautylevel)
         * [setAudioEnable](#setaudioenable)
         * [setVideoEnable](#setvideoenable)
         * [setDenoiseEnable](#setdenoiseenable)
         * [setDynamicRateEnable](#setdynamicrateenable)
         * [setKeyFrameInterval](#setkeyframeinterval)
         * [setCryptoKey](#setCryptoKey)
         * [setNodePublisherDelegate](#setnodepublisherdelegate)
      * [方法](#方法)
         * [switchCamera](#switchcamera)
         * [startPreview](#startpreview)
         * [stopPreview](#stoppreview)
         * [start](#start)
         * [stop](#stop)
         * [release](#release)
      * [事件回调](#事件回调)
         * [2000](#2000)
         * [2001](#2001)
         * [2002](#2002)
         * [2004](#2004)
         * [2005](#2005)
         * [2100](#2100)
         * [2101](#2101) 
      * [VideoPreset](#videopreset) 

## 属性
### setOutputUrl
设置视频输出地址, 支持RTMP/RTMPT/HTTP形式,FLV封装

### setPageUrl
设置RTMP协议下pageUrl地址.

### setSwfUrl
设置RTMP协议集下swfUrl地址

### setConnArgs
设置RTMP协议集下connect命令发出时附带的参数. RTMPDUMP风格
>Append arbitrary AMF data to the Connect message. The type must be B for Boolean, N for number, S for string, O for object, or Z for null. For Booleans the data must be either 0 or 1 for FALSE or TRUE, respectively. Likewise for Objects the data must be 0 or 1 to end or begin an object, respectively. Data items in subobjects may be named, by prefixing the type with 'N' and specifying the name before the value, e.g. NB:myFlag:1. This option may be used multiple times to construct arbitrary AMF sequences. E.g.  
**S:info O:1 NS:uid:10012 NB:vip:1 NN:num:209.12 O:0**

### setCameraPreview:(nonnull UIView*)preView cameraId:(int)cameraId frontMirror:(BOOL)frontMirror
设置摄像头预览视图
- 参数1 : 需要传入UIView对象
- 参数2 : 摄像头ID,使用CAMERA_BACK或CAMERA_FRONT
- 参数3 : 预览时画面是否镜像显示

### setZoomScale
设置摄像头缩放等级, 0-100
>GPU算法, 非系统API, 所有机型上缩放效果比例一致

### setFlashEnable
设置是否一直开启闪光灯

### setAudioParamBitrate:(int)bitrate profile:(int)profile
设置音频编码参数
- 参数1 : 音频比特率
- 参数2 : 音频编码格式,支持
	- AUDIO_PROFILE_LCAAC 
	- AUDIO_PROFILE_HEAAC 
	- AUDIO_PROFILE_SPEEX 
	
### setVideoParamPreset:(VideoPreset)preset fps:(int)fps bitrate:(int)bitrate profile:(int)profile frontMirror:(BOOL)frontMirror
设置视频编码参数
- 参数1 : [视频分辨率预设](VideoPreset)
- 参数2 : 视频帧率
- 参数3 : 视频比特率
- 参数4 : 视频编码规格
	- VIDEO_PROFILE_BASELINE
	- VIDEO_PROFILE_MAIN
	- VIDEO_PROFILE_HIGH
- 参数5 : 视频输出画面是否进行镜像翻转

### setHwEnable
设置是否开启硬件编码加速, 默认自动开启,当初始化失败时自动转为软件编码

### setAutoFocus
当为YES时,摄像头将全时自动对焦. 当为NO时,每请求一次,对焦一次,之后锁定焦距

### setBeautyLevel
设置美颜等级,0-5 , 0关闭, 1-5级别

### setAudioEnable
设置音频是否开启传输

### setVideoEnable
设置视频是否开始传输

### setDenoiseEnable
设置是否开启噪音抑制

### setDynamicRateEnable
设置是否开启动态码率调整

### setKeyFrameInterval
设置视频关键帧间隔的帧数

### setCryptoKey
设置视频加密秘钥, 16字节

### setNodePublisherDelegate
设置[事件回调](事件回调)代理

## 方法

### switchCamera
切换前后摄像头

### startPreview
摄像头开始预览

### stopPreview
摄像头停止预览

###capturePicture:(_Nonnull CapturePictureBlock)capturePictureBlock
截图, 传入监听器, 当截图完成后回调UIImage. 需要自行处理UIImage,如另存为jpeg.

### start
开始推流

### stop
停止推流

### release
释放资源

## 事件回调
### 2000
正在发布视频

### 2001 
视频发布成功

### 2002
视频发布失败

### 2004
视频发布结束

### 2005
视频发布中途,网络异常,发布中断

### 2100
网络阻塞, 发布卡顿

### 2101
网络恢复, 发布流畅

## VideoPreset
``` objectivec
typedef enum {
    VIDEO_PPRESET_16X9_270,
    VIDEO_PPRESET_16X9_360,
    VIDEO_PPRESET_16X9_480,
    VIDEO_PPRESET_16X9_540,
    VIDEO_PPRESET_16X9_720,
    VIDEO_PPRESET_16X9_1080,
    
    VIDEO_PPRESET_4X3_270=10,
    VIDEO_PPRESET_4X3_360,
    VIDEO_PPRESET_4X3_480,
    VIDEO_PPRESET_4X3_540,
    VIDEO_PPRESET_4X3_720,
    VIDEO_PPRESET_4X3_1080,
    
    VIDEO_PPRESET_1X1_270=20,
    VIDEO_PPRESET_1X1_360,
    VIDEO_PPRESET_1X1_480,
    VIDEO_PPRESET_1X1_540,
    VIDEO_PPRESET_1X1_720,
    VIDEO_PPRESET_1X1_1080,
    
}VideoPreset;
```
