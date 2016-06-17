//
//  M800Call.h
//  M800
//
//  Created by Justin Liu on 21/5/14.
//  Copyright (c) 2014 Maaii. All rights reserved.
//

#import <Foundation/Foundation.h>


FOUNDATION_EXPORT NSString *const M800CallUserInfoIncomingCallerKey;
FOUNDATION_EXPORT NSString *const M800CallUserInfoStatusCodeKey;
FOUNDATION_EXPORT NSString *const M800CallUserInfoIsErrorKey;

typedef NS_ENUM(NSInteger, M800CallState){
    M800CallStateUnknown = -1,
    M800CallStateIdle = 0,
    M800CallStateOutgoing,
    M800CallStateIncoming,
    M800CallStateRinging,
    M800CallStateAnswering,
    M800CallStateTalking,
    M800CallStateLocalHeld,
    M800CallStateRemoteHeld,
    M800CallStateTerminating,
    M800CallStateReconnecting
};


/**
 * This list contains all directions of a call.
 */
typedef NS_ENUM(NSInteger, M800CallDirection) {
    /**
     * Indicates call is incoming one.
     */
    M800CallDirectionIncoming,
    /**
     * Indicates call is outgoing one.
     */
    M800CallDirectionOutgoing
};

/**
 * This enumeration contains all types for a call.
 */
typedef NS_ENUM(NSInteger, M800CallType){
    M800CallTypeOnnet,
    M800CallTypeOffnet
};

typedef NS_ENUM(NSInteger, M800VideoScalingMode){
    // Description:
    // Keeps the complete image by scaling it down and introducing letter boxes.
    M800_VSM_INSIDE_EDGE,
    
    // Description:
    // Crops the image to keep the aspect ratio and filling the renderer
    // surface.
    M800_VSM_OUTSIDE_EDGE,
    
    // Description:
    // If the image and the rendering surface have the same orientation,
    // crops the image to keep the aspect ratio and filling the renderer
    // surface. Else keeps the complete image by scaling it down and
    // introducing letter boxes.
    M800_VSM_AUTOMATIC_EDGE
    
};

typedef NS_ENUM(NSInteger, M800VideoRenderingSurface){
    // Description:
    // Specifes that the configuration of the rendering surface is for the
    // video camera capture feed
    M800_VRS_CAMERA_CAPTURE,
    
    // Description:
    // Specifies that this rendering surface is for the peer video feed
    M800_VRS_PEER_VIDEO_FEED
};

typedef NS_ENUM(NSInteger, M800MediaType){
    M800_MEDIA_AUDIO,    
    M800_MEDIA_VIDEO
};

typedef NS_ENUM(NSInteger,M800MediaRouteType) {
    
    // Description:
    // Media route is unknown
    M800_MEDIA_ROUTE_UNKNOWN,
    
    // Description:
    // Media route is via the SBC relay
    M800_MEDIA_ROUTE_SBC,
    
    // Description:
    // Media route is directly peer-to-peer (i.e., not relayed by TURN server or SBC)
    M800_MEDIA_ROUTE_P2P
};


/**
 * MECallInfo conatins all information of a call.
 */
@protocol M800CallInfo <NSObject>

/**
 * @brief The state of current call.
 * @see MECallState
 */
- (M800CallState)callState;

/**
 * @brief The direction of current call.
 */
- (M800CallDirection)direction;
/**
 * Returns call type.
 */
- (M800CallType)callType;
/**
 * The unique ID of call session.
 * For push calls this ID will be the call identifier that arrived with the push call notification.
 * For non-push calls this ID will be a number that this generated when the call is created.
 */
- (NSString*)callID;



/**
 * My ID (JID e.g. abc123@abc.com or a phone number).
 * @brief The identifier of current call.
 */
- (NSString*)myId;
/**
 * The ID (JID or phone number) for remote party
 * @brief The remote identifier of current call.
 */
- (NSString*)remoteId;

/**
 * The phone number for remote party
 *
 */
- (NSString*)remotePhoneNumber;

/**
 * The display name of remote party.
 * It is passed by SIP header "X-Display-Name" or push notification.
 */
- (NSString*)remoteDisplayName;

/**
 * The status code of current code.
 * @see M800StatusCode
 */
- (NSInteger)statusCode;
/**
 * The error of current code. If statusCode is not error, then this property is nil.
 */
- (NSError*)error;

/**
 * The start time of current call. (i.e, the time when the call was initiated (for outgoing)
 * or the time the incoming call landed)
 */

- (NSDate*)startTime;

/**
 * The established time of current call which represents the time when the remote party answered
 * our outgoing call or when the local side answered an incoming call
 */

- (NSDate*)establishedTime;
/**
 * The end time of current call.
 * Note that if the call was never established then the time reported will be Jan-01-1970
 */
- (NSDate*)endTime;

/**
 * Verify the call is push call
 */
- (BOOL)isPushCall;

/**
 * Verify the call is thru ICE
 */
- (BOOL)isEnableICE;



@end

@protocol M800CallDelegate;

/**
 * M800Call contains all information inherited from MECallInfo and defines 
 * operations for a call object.
 */
@protocol M800Call <M800CallInfo>

/**
 * @brief Ends call only if current state is MECallStateTalking
 * @param reason to hangup, the reason will retunr to CallDelegate onCallTerminated callback thru userInfo (key:M800USERINFOKEY_ENDCALLREASON).  The param can set to nil if no reason.
 */
- (void)hangup:(NSString *)reason;

/**
 * @brief Holds call if current call is unhold.
 */
- (void)hold;
/**
 * @brief Unholds call  if current call is MECallStateLocalHeld.
 */
- (void)unhold;

/**
 * @brief Sends DTMF digits to remote side.
 * @param digits The string contains digits.
 */
- (void)sendDTMF:(NSString *) digits;
/**
 * @brief Starts playing file only if call is MECallStateTalking.
 * @param filepath The file to be played
 * @param toRemote Indicate file is played on local or remote.
 * @param sampleRate
 * @param loop Indicate playback is loop or not.
 * @param opaque A unique opaque handle the caller assigns to this file play back session. All further
 * events or control of the file playback session must include this same opaque value
 */
- (void)startFilePlayback:(NSString*)filepath
                   remote:(BOOL)toRemote
               sampleRate:(int) sampleRate
                     loop:(BOOL)loop
                   opaque:(unsigned)opaque;
/**
 * @brief Stops playing audio file.
 * @param opaque A unique opaque handle the caller assigns to this file play back session. All further
 * events or control of the file playback session must include this same opaque value
 */
- (void)stopFilePlayback:(unsigned)opaque;



- (void)addCallDelegate:(id<M800CallDelegate>)delegate;
- (void)removeCallDelegate:(id<M800CallDelegate>)delegate;

/**
 *@brief set video call configuration. This should be done when the render surface is
 known
 */
-(void) setVideoCallRenderSurface: (void *) renderSurface
                      surfaceType: (M800VideoRenderingSurface) surfaceType
                           zOrder: (unsigned) zOrder
                          leftPos: (unsigned) leftPos
                           topPos: (unsigned) topPos
                         rightPos: (unsigned) rightPos
                        bottomPos: (unsigned) bottomPos
                      scalingMode:  (M800VideoScalingMode) scalingMode;

/**
 *@brief use this to enable or disable audio or video media prior to or during a call.
 For instance if the call starts out as audio only and the
 */
-(void) enableMedia: (M800MediaType) media
            enabled: (BOOL) enabled;

/**
 *@brief Enable the call thru ICE
 *@param enable A flage specific enabled or not
 */
- (void) enableICE:(BOOL) enable;

/**
 *@brief check any other active call other than me
 *@return true if it has another active call.
 */
- (bool) hasOtherActiveCalls;
/**
 * Adds customized header to SIP messages.
 * @param header The header's name
 * @param value The header's value
 */
- (void) addCustomSIPHeader:(NSString*)header value:(NSString*)value;
/**
 * Removes customized header to SIP messages.
 * @param header The header's name
 */
- (void) removeCustomSIPHeader:(NSString*)header;



@end


@protocol M800IncomingCallDelegate;

/**
 * MEIncomingCall represents a call which direction is MECallDirectionIncoming,
 * and defines particular operation for incoming call.
 */
@protocol M800IncomingCall <M800Call>

/**
 * This operation can be executed if current call's state is MECallStateIncoming.
 * @brief Answers an incoming call.
 */
- (void)answer;
/**
 * This operation can be executed if current call's state is MECallStateIncoming.
 * @brief Rejects an incoming call.
 * @param reason The reason for rejecting call.
 */
- (void)reject:(NSString*)reason;

@end

@protocol M800OutgoingCallDelegate;
/**
 * MEOutgoingCall represents a call which direction is MECallDirectionOutgoing,
 * and defines particular operation for outgoing call.
 */
@protocol M800OutgoingCall <M800Call>

/** Starts making call to callee configured before.
 * The call session will make a call with current configuration.
 * @see M800Client::createCall
 */
- (void)dial;

/**
 * @brief Cancels current call if it is not answered.
 */
- (void)cancel;

@end





