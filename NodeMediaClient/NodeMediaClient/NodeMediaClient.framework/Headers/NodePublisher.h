//
//  NodePublisher.h
//  NodeMediaClient
//
//  Created by Mingliang Chen on 17/3/23.
//  Copyright © 2017年 Mingliang Chen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#define AUDIO_PROFILE_LCAAC     0           //LC-AAC
#define AUDIO_PROFILE_HEAAC     1           //HE-AAC
#define AUDIO_PROFILE_SPEEX     2           //SPEEX

#define VIDEO_PROFILE_BASELINE  0           //H.264 Baseline profile
#define VIDEO_PROFILE_MAIN      1           //H.264 Main profile
#define VIDEO_PROFILE_HIGH      2           //H.264 High profile
#define VIDEO_PROFILE_HEVC_MAIN 3           //H.265 Main profile

#define CAMERA_BACK             0           //后置摄像头
#define CAMERA_FRONT            1           //前置摄像头

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

typedef void (^CapturePictureBlock)(UIImage * _Nullable image);

@protocol NodePublisherDelegate

-(void) onEventCallback:(id _Nonnull)sender event:(int)event msg:(NSString* _Nonnull)msg;

@end

@protocol NodePublisherVideoSampleDelegate

- (CVImageBufferRef)didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

@end

@class UIView;
@interface NodePublisher : NSObject

@property (nullable, nonatomic, weak) id<NodePublisherDelegate> nodePublisherDelegate;
@property (nullable, nonatomic, weak) id<NodePublisherVideoSampleDelegate> nodePublisherVideoSampleDelegate;

///音视频直播流地址
@property (nonnull, nonatomic, strong) NSString *outputUrl;

///rtmp协议连接下附加pageurl参数
@property (nonnull, nonatomic, strong) NSString *pageUrl;

///rtmp协议连接下附加swfUrl参数
@property (nonnull, nonatomic, strong) NSString *swfUrl;

/**
 * @brief rtmpdump 风格的connect参数
 * Append arbitrary AMF data to the Connect message. The type must be B for Boolean, N for number, S for string, O for object, or Z for null.
 * For Booleans the data must be either 0 or 1 for FALSE or TRUE, respectively. Likewise for Objects the data must be 0 or 1 to end or begin an object, respectively.
 * Data items in subobjects may be named, by prefixing the type with 'N' and specifying the name before the value, e.g. NB:myFlag:1.
 * This option may be used multiple times to construct arbitrary AMF sequences. E.g.
 */
@property (nonnull, nonatomic, strong) NSString *connArgs;

///自动重连超时等待时间,单位毫秒,默认为0. 当为0时不自动重连
@property (nonatomic) NSUInteger autoReconnectWaitTimeout;

///连接或数据为空超时等待时间,单位毫秒,默认0. 当为0时永久等待
@property (nonatomic) NSUInteger connectWaitTimeout;

///开关闪光灯
@property (nonatomic, assign) BOOL flashEnable;

///设置缩放等级 0 ~ 100
@property (nonatomic, assign) NSUInteger zoomScale;

///设置美颜等级 0 ~ 5
@property (nonatomic, assign) NSUInteger beautyLevel;

///当为YES时,摄像头将全时自动对焦. 当为NO时,每请求一次,对焦一次,之后锁定焦距
@property (nonatomic, assign) BOOL autoFocus;

///硬件加速编码
@property (nonatomic, assign) BOOL hwEnable;

///是否采集音频
@property (nonatomic, assign) BOOL audioEnable;

///是否采集视频
@property (nonatomic, assign) BOOL videoEnable;

///是否开启背景音降噪
@property (nonatomic, assign) BOOL denoiseEnable;

///是否开启动态码率调整
@property (nonatomic, assign) BOOL dynamicRateEnable;

///视频关键帧间隔，单位为秒，默认为1
@property (nonatomic, assign) NSUInteger keyFrameInterval;

///设置视频加密秘钥, 16字节
@property (nonnull, nonatomic, strong) NSString *cryptoKey;

///设置日志等级，0-错误，1-信息，2-调试
@property (nonatomic) int logLevel;

-(instancetype _Nonnull)initWithLicense:(NSString* _Nonnull)key;

///设置摄像头预览视图
-(void) setCameraPreview:(UIView* _Nonnull)preView cameraId:(int)cameraId frontMirror:(BOOL)frontMirror;

///设置音频参数
-(void) setAudioParamBitrate:(int)bitrate profile:(int)profile;

///设置音频参数
-(void) setAudioParamBitrate:(int)bitrate profile:(int)profile sampleRate:(int)sampleRate;

///设置视频参数
-(void) setVideoParamPreset:(VideoPreset)preset fps:(int)fps bitrate:(int)bitrate profile:(int)profile frontMirror:(BOOL)frontMirror;

///摄像头开始预览
-(int) startPreview;

///摄像头停止预览
-(int) stopPreview;

///切换前后摄像头
-(int) switchCamera;

//截图
-(void) capturePicture:(CapturePictureBlock _Nonnull)capturePictureBlock;

///开始推流
-(int) start;

///停止推流
-(int) stop;

@end
