//
//  NodePlayer.h
//  NodeMediaClient
//
//  Created by Mingliang Chen on 16/12/29.
//  Copyright © 2016年 Mingliang Chen. All rights reserved.
//

#import <Foundation/Foundation.h>

#define RTSP_TRANSPORT_UDP @"udp"
#define RTSP_TRANSPORT_TCP @"tcp"
#define RTSP_TRANSPORT_UDP_MULTICAST @"udp_multicast"
#define RTSP_TRANSPORT_HTTP @"http"

@protocol NodePlayerDelegate

-(void) onEventCallback:(id _Nonnull)sender event:(int)event msg:(NSString* _Nonnull)msg;

@end

@class UIView;
@interface NodePlayer : NSObject

@property (nullable,nonatomic, weak) id<NodePlayerDelegate> nodePlayerDelegate;

#pragma mark 参数
///音视频流地址,也可以是本地文件绝对路径
@property (nonnull, nonatomic, strong) NSString *inputUrl;

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

/**
 * @brief RTSP 传输协议
 * RTSP_TRANSPORT_UDP
 * RTSP_TRANSPORT_TCP
 * RTSP_TRANSPORT_UDP_MULTICAST
 * RTSP_TRANSPORT_HTTP
 */
@property (nonnull, nonatomic, strong) NSString *rtspTransport;


@property (nullable, nonatomic, weak) UIView *playerView;

///启动缓冲区时长,单位毫秒.默认值 500
@property (nonatomic) int bufferTime;

/**
 * @brief 最大缓冲区时长,单位毫秒.默认值 1000
 *
 * 当输入地址为直播流时,该值决定了当前缓冲区内与直播时间线的最大延迟,当超过后,丢弃过期数据,完成追帧
 *
 * 当输入地址为本地文件或点播流时,该值决定了最大读取缓冲
 */
@property (nonatomic) int maxBufferTime;


///自动重连超时等待时间,单位毫秒, 默认2000. 当为0时不自动重连
@property (nonatomic) unsigned int autoReconnectWaitTimeout;


///连接或数据为空超时等待时间,单位毫秒, 默认10000. 当为0时永久等待
@property (nonatomic) unsigned int connectWaitTimeout;

/**
 * @brief 视频缩放模式
 *
 * 当前支持三种缩放模式: 填充缩放,等比缩放,等比填充缩放
 *
 * (UIViewContentModeScaleToFill) [缩放填充]模式将整个视频填充到给定的显示区域,当显示区域与视频分辨率不一致时,发生画面被拉长或压扁,但没有黑边
 *
 * (UIViewContentModeScaleAspectFit) [等比缩放]模式将整个视频等比例缩放后显示到给定区域,当显示区域与视频分辨率不一致时,画面仍然保持正常比例,但有黑边
 *
 * (UIViewContentModeScaleAspectFill) [等比填充缩放]模式将整个视频等比例缩放后拉伸填充给定区域,当显示区域与视频分辨率不一致时,裁剪掉多余的视频画面,画面仍然保持正常比例,没有黑边,但视频会显示不完全
 */
@property (nonatomic) int contentMode;

/**
 * @brief 是否开始硬件解码加速,开始播放前设置有效,默认开启.
 *
 * 当视频编码为H.264\MPEG4\H.263,可以使用硬件解码加速来降低cpu占用,降低能耗.
 *
 * 当初始化失败,或者系统版本不支持时,自动转为软解码.
 */
@property (nonatomic) BOOL hwEnable;

///是否开启音频
@property (nonatomic) BOOL audioEnable;

///是否开启视频
@property (nonatomic) BOOL videoEnable;

///是否以subscribe模式播放视频
@property (nonatomic) BOOL subscribe;

///设置视频解密秘钥, 16字节
@property (nonnull, nonatomic, strong) NSString *cryptoKey;

///设置音量 0.0 ~ 1.0
@property (nonatomic) float volume;

///设置日志等级，0-错误，1-信息，2-调试
@property (nonatomic) int logLevel;

#pragma mark 属性

-(instancetype _Nonnull)initWithLicense:(NSString* _Nonnull)key;


///获取当前视频总时长,单位毫秒.直播流为0
-(long) getDuration;

///获取当前播放位置,单位毫秒,
-(long) getCurrentPosition;

///获取缓冲位置,单位毫秒
-(long) getBufferPosition;

///获取当前是否为播放状态
-(BOOL) isPlaying;

///获取当前播放地址是否为直播流
-(BOOL) isLive;

#pragma mark 方法

///开始播放
-(int) start;

///停止播放
-(int) stop;

///停止播放但不清除画面
-(int) stop:(BOOL)clear;

///暂停播放,当前为直播流时无效
-(int) pause;

///快进或快退到给定位置.可以在开始播放前设置.
-(int) seekTo:(long) pos;

@end
