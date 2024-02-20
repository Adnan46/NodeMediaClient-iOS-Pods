# NodePlayer API
NodePlayer用于RTMP/RTMPT/RTSP/HTTP/TCP/UDP/FILE格式的音视频播放. 支持直播和点播形式, SDK根据两种不同的形式, 采用不同的缓冲策略.达到秒开视频, 自动消除累积延迟, 自动等待点播进度.
当服务端支持GOP缓存特性, 可以达到视频画面跟手开, 自动快进追进度的极佳效果.

Table of Contents
=================

   * [NodePlayer API](#nodeplayer-api)
      * [属性](#属性)
         * [setInputUrl](#setinputurl)
         * [setPageUrl](#setpageurl)
         * [setSwfUrl](#setswfurl)
         * [setConnArgs](#setconnargs)
         * [setBufferTime](#setbuffertime)
         * [setMaxBufferTime](#setmaxbuffertime)
         * [setHwEnable](#sethwenable)
         * [setAutoReconnectWaitTimeout](#setautoreconnectwaittimeout)
         * [setConnectWaitTimeout](#setconnectwaittimeout)
         * [setAudioEnable](#setaudioenable)
         * [setVideoEnable](#setvideoenable)
         * [setSubscribe](#setsubscribe)
         * [setPlayerView](#setplayerview)
         * [setContentMode](#setcontentmode)
         * [setCryptoKey](#setCryptoKey)
         * [setNodePlayerDelegate](#setnodeplayerdelegate)
      * [方法](#方法)
         * [start](#start)
         * [stop](#stop)
         * [pause](#pause)
         * [seekTo](#seekto)
         * [getDuration](#getduration)
         * [getCurrentPosition](#getcurrentposition)
         * [getBufferPosition](#getbufferposition)
         * [getBufferPercentage](#getbufferpercentage)
         * [isPlaying](#isplaying)
         * [isLive](#islive)
      * [事件回调](#事件回调)
         * [1000](#1000)
         * [1001](#1001)
         * [1002](#1002)
         * [1003](#1003)
         * [1004](#1004)
         * [1005](#1005)
         * [1006](#1006)
         * [1100](#1100)
         * [1101](#1101)
         * [1102](#1102)
         * [1103](#1103)
         * [1104](#1104)

## 属性

### setInputUrl
设置输入流地址,支持RTMP/RTMPT/RTSP/HTTP/TCP/UDP/FILE

### setPageUrl
设置RTMP协议集下pageUrl地址

### setSwfUrl
设置RTMP协议集下swfUrl地址

### setConnArgs
设置RTMP协议集下connect命令发出时附带的参数. RTMPDUMP风格
>Append arbitrary AMF data to the Connect message. The type must be B for Boolean, N for number, S for string, O for object, or Z for null. For Booleans the data must be either 0 or 1 for FALSE or TRUE, respectively. Likewise for Objects the data must be 0 or 1 to end or begin an object, respectively. Data items in subobjects may be named, by prefixing the type with 'N' and specifying the name before the value, e.g. NB:myFlag:1. This option may be used multiple times to construct arbitrary AMF sequences. E.g.  
> **S:info O:1 NS:uid:10012 NB:vip:1 NN:num:209.12 O:0**

### setBufferTime
设置播放启动缓冲,单位毫秒, 默认值500ms .
>当网络读取缓冲区数据达到该值时开始播放,不是等待时长.

### setMaxBufferTime
设置播放最大缓冲, 单位毫秒, 默认值1000ms.
>当为直播时, 该值决定最大延迟, 当网络波动形成延迟并超过该值后, SDK内部进行追帧处理. 音频丢弃, 视频快进.   
>当为点播时, 该值决定网络缓冲区达到多少之后停止读取,节省不必要的流量

### setHwEnable
开启硬件解码, 默认开启, 当初始化失败自动切为软解码.

### setAutoReconnectWaitTimeout
设置自动重连等待时长. 单位毫秒, 默认值2000ms. 当设为-1时不进行自动重连.

### setConnectWaitTimeout
设置连接等待超时时长, 单位毫秒,  默认值为0, 一直等待.

### setAudioEnable
设置音频是否开启

### setVideoEnable
设置视频是否开启

### setReceiveAudio
设置RTMP协议集下, 是否接受音频数据,  需要服务端支持. 开始播放前设置有效.

### setReceiveVideo
设置RTMP协议集下, 是否接受视频数据,  需要服务端支持. 开始播放前设置有效.

### setSubscribe
设置是否发送"FCSubscribe", 很多海外CDN商需要发送该命令.


### setPlayerView
设置播放视图,需要传入UIView的视图对象

### setContentMode
设置视频缩放模式,当前支持三种缩放模式: 填充缩放,等比缩放,等比填充缩放  
- (UIViewContentModeScaleToFill) [缩放填充]模式将整个视频填充到给定的显示区域,当显示区域与视频分辨率不一致时,发生画面被拉长或压扁,但没有黑边
- (UIViewContentModeScaleAspectFit) [等比缩放]模式将整个视频等比例缩放后显示到给定区域,当显示区域与视频分辨率不一致时,画面仍然保持正常比例,但有黑边
- (UIViewContentModeScaleAspectFill) [等比填充缩放]模式将整个视频等比例缩放后拉伸填充给定区域,当显示区域与视频分辨率不一致时,裁剪掉多余的视频画面,画面仍然保持正常比例,没有黑边,但视频会显示不完全

### setCryptoKey
设置视频解密秘钥, 16字节

### setNodePlayerDelegate
设置事件回调代理.

## 方法

### start
开始播放

### stop
停止播放

### pause
暂停播放, 点播时有效

### seekTo
跳转到播放点开始播放, 点播时有效

### getDuration
获取点播视频总时长

### getCurrentPosition
获取点播视频当前播放点

### getBufferPosition
获取点播视频缓冲点

### getBufferPercentage
获取缓冲进度百分比

### isPlaying
获取当前是否正在播放

### isLive
获取当前播放是否为直播视频

## 事件回调

### 1000
正在连接视频

### 1001
视频连接成功

### 1002
视频连接失败, 会进行自动重连.

### 1003
视频开始重连

### 1004
视频播放结束

### 1005
视频播放中网络异常, 会进行自动重连.

### 1006
网络连接超时, 会进行自动重连.

### 1100
播放缓冲区为空

### 1101
播放缓冲区正在缓冲数据

### 1102
播放缓冲区达到bufferTime设定值,开始播放

### 1103
收到RTMP协议Stream EOF,或 NetStream.Play.UnpublishNotify, 会进行自动重连.

### 1104
解码后得到视频高宽, 格式为 width x height
