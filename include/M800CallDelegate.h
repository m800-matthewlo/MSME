//
//  MECallDelegate.h
//  M800
//
//  Created by Justin Liu on 21/5/14.
//  Copyright (c) 2014 Maaii. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol M800OutgoingCall;
@protocol M800IncomingCall;
@protocol M800Call;

/**
 * The delegate of M800Call object to handle changes of call state.
 */
@protocol M800CallDelegate <NSObject>

@optional
/**
 * Event: call is held by local user.
 * @param call The call.
 */
- (void)callHoldByLocal:(id<M800Call>)call;
/**
 *Event: call is unhold by local user.
 * @param call The call.
 */
- (void)callUnholdByLocal:(id<M800Call>)call;
/**
 * Event: call is held by remote user.
 * @param call The call.
 */
- (void)callHoldByRemote:(id<M800Call>)call;
/**
 * Event: call is unheld by remote user.
 * @param call The call.
 */
- (void)callUnHoldByRemote:(id<M800Call>)call;

/**
 * Event: call is muted.
 * @param call The call.
 */
- (void)callMuted:(id<M800Call>)call;
/**
 * Event: call is unmuted.
 * @param call The call.
 */
- (void)callUnmuted:(id<M800Call>)call;
/**
 * Event: call is starting to play file
 * @param call The call.
 */
- (void)callStartPlayingFilePlayback:(id<M800Call>)call;
/**
 * Event: call is restart to play file
 * @param call The call.
 */
- (void)callRestartPlayingFilePlayback:(id<M800Call>)call;
/**
 * Event: call is failed to play file
 * @param call The call.
 */
- (void)callFailedToPlayFilePlayback:(id<M800Call>)call;

/**
 * Event: call is failed to play file
 * @param call The call.
 */
- (void)callFinishedFilePlayback:(id<M800Call>)call;

/**
 * Event: call is dialing.
 * @param call The call.
 */
- (void)callDial:(id<M800Call>)call;

/**
 * Event: call is talking.
 * @param call The call.
 */
- (void)callBeginTalking:(id<M800Call>)call;
/**
 * Event: call is ended for some reasons.
 * @param call The call.
 * @param code A SIP response code. A zero response code indicates a normal (no errors) call termination.
 */
- (void)callTerminated:(id<M800Call>)call status:(NSNumber *)code userInfo:(NSDictionary*)info;

/**
 * Event: call is establishing
 * @param call The call.
 */
- (void)callProgress:(id<M800Call>)call status:(NSNumber *)code userInfo:(NSDictionary*)info;

/**
 * Event: call will start media channels
 * @param call The call.
 */
- (void)callWillStartMedia:(id<M800OutgoingCall>)call;

/**
 * Event: call will start media channels
 * @param call The call.
 */
- (void)callWillDestroy:(id<M800Call>)call;


/**
 * Event: get network quality report
 * @param call The call.
 * @param quality (1 - is the best and 3 is the worst)
 */
- (void)networkQualityReport:(id<M800Call>)call quality:(NSNumber *) quality;

/**
 * Event: new media, such as video, has been offered by the peer
 * @param call The call.
 * @param media The media being offered 0=audio, 1=video
 */
- (void)callNewMediaOffer:(id<M800Call>)call media:(M800MediaType) media isRemoved:(BOOL) isRemoved;

/**
 * Event: the call is reconnecting because other either network change or loss of RTP
 * @param call The call.
 * @param times The reconnection attempt count
 * @param isPeer a boolean indicatig whether the peer (if true) has initiated the call reconnection
 *              or if the call reconnection was initiated locally (if false)
 */
- (void)callReconnecting:(id<M800Call>)call times:(NSNumber*)times isPeer:(BOOL) isPeer;

/**
 * Event: reports the failure of the call to reconnect
 * @param call The call.
 * @param times The number of reconnecion attempts made before reporting failure
 */
- (void)callFailedToReconnect:(id<M800Call>)call times:(NSNumber*)times;

/**
 * Event: reports that the media route has changed. The default route at the beginning of a call is M800_MEDIA_ROUTE_UNKNOWN
 * @param call The call.
 * @param mediaRoute The new media route
 */
- (void)callMediaRouteChanged:(id<M800Call>)call mediaRoute:(M800MediaRouteType) mediaRoute;
@end
/**
 * The delegate of MEOutgoingCall object to handle changes of call state.
 */
@protocol M800OutgoingCallDelegate <M800CallDelegate>
/**
 * Event: call is establishing
 * @param call The call.
 */
- (void)callEstablishing:(id<M800OutgoingCall>)call;

///**
// * Event: call is sent to remote user.
// * @param call The call.
// */
//- (void)callReceivedOnRemote:(id<M800OutgoingCall>)call;


@optional
/**
 * Event: call is starting to play customized ringback tone.
 * @param call The call.
 */
//- (void)callPlayingCustomizedRingbackTone:(id<M800OutgoingCall>)call;
@end
/**
 * The delegate of MEIncomingCall object to handle changes of call state.
 */
@protocol M800IncomingCallDelegate <M800CallDelegate>
/**
 * Event: call is answering.
 * @param call The call.
 */
- (void)callAnswering:(id<M800IncomingCall>)call;
/**
 * Event: call is answered.
 * @param call The call.
 */
- (void)callAnswered:(id<M800IncomingCall>)call;


@optional
/**
 * Event: call is starting to play customized ring tone.
 * @param call The call.
 */
//- (void)callPlayingCustomizedRingtone:(id<M800IncomingCall>)call;

@end
