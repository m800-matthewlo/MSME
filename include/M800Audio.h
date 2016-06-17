//
//  M800Audio.h
//  MSME-ios
//
//  Created by Cyrus Lo on 30/7/14.
//  Copyright (c) 2014 M800. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This list contains audio category
 */
typedef NS_ENUM(NSInteger, M800AudioCategory) {
    M800AmbientSound,
    M800SoloAmbientSound,
    M800MediaPlayback,
    M800RecordAudio,
    M800PlayAndRecord,
    M800AudioProcessing,
    M800UnknownCategory
};

/**
 * This list contains all audio routes
 */
typedef NS_ENUM(NSInteger, M800AudioRoutes) {
    M800Earpiece,
    M800Speaker,
    M800Bluetooth,
    M800Others
};

/**
 * This list contains all audio route change reason
 */
typedef NS_ENUM(NSInteger, M800AudioChangeReason) {
    M800NewDeviceAvailable,
    M800OldDeviceUnavailable,
    M800CategoryChange,
    M800ApplicationOverride,
    M800WakeFromSleep,
    M800NoSuitableRoute,
    M800UnknownReason
};

@protocol M800AudioDelegate;

@protocol M800Audio <NSObject>
#pragma mark
#pragma mark telephony tones play

+ (id<M800Audio>) getRef;

/**
 * @method
 * @abstract
 * Play ringback
 */
- (void)playRingbackTone;
/**
 * @method
 * @abstract
 * Play stop tone
 */
- (void)playStopTone;

/**
 * @method
 * @abstract
 * stop play
 */
- (void)stop;

/**
 * @method
 * @abstract
 * pause play
 */
- (void)pause;

/**
 * @method
 * @abstract
 * isPlaying
 */
- (bool)isPlaying;



#pragma mark
#pragma mark iOS high level audio control

/**
 * @method
 * @abstract
 * check audio is mute
 */
- (bool) isMute;


/**
 * @method
 * @abstract
 * set audio mute/unmute
 */
- (void) setMute:(bool) mute;


/**
 * @method
 * @abstract
 * set audio to speaker
 */
- (void) setSpeaker:(bool)enable;


/**
 * @method
 * @abstract
 * get current audio output
 * @discussion
 * A known issue that this method always return Speaker on IOS6.
 */
- (M800AudioRoutes) getOutputDevice;

/**
 * @method
 * @abstract
 * set audio session active/deactive
 */
- (void)setActive:(bool)active;




#pragma mark
#pragma mark iOS low level audio control
/**
 * @method
 * @abstract
 * set audio cateogy
 */
//- (void)setAudioCategory:(M800AudioCategory) category;

/**
 * @method
 * @abstract
 * get audio cateogy
 */
//- (M800AudioCategory)getActiveAudioCategory;

/**
 * @method
 * @abstract
 * Gets the current interruption state of the iOS Core Audio session.
 */
- (bool)isAudioSessionInterrupted;

#pragma mark
#pragma mark iOS audio delegate
/**
 * @method
 * @abstract
 * Adds new audio delegate into client.
 * @param delegate
 * A new client will be added to client. If already exist, ignored.
 */
- (void)addAudioDelegate:(id<M800AudioDelegate>)delegate;
/**
 * @method
 * @abstract
 * Removes a audio delegate from client.
 * @param delegate
 * A delegate will be removed from client. If not exists, ignored.
 */
- (void)removeAudioDelegate:(id<M800AudioDelegate>)delegate;
@end


@interface M800AudioAccessor : NSObject

/** Create M800 audio which be responsed for communicating with M800 lower side.
 * @return The object implements M800Client
 * @see M800Client
 */
+ (id<M800Audio>)getM800Audio;

@end

