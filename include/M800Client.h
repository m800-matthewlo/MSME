//
//  M800Client.h
//  M800
//
//  Created by Justin Liu on 21/5/14.
//  Copyright (c) 2014 Maaii. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "M800Call.h"
#import "M800ClientDelegate.h"
#import "M800ClientConfiguration.h"

/**
 * This enum mirror all states of MSME client engine.
 * @discussion When enabled M800ClientConfiguration.supportCallingWithoutRegistration, M800ClientStateRegistered would be NOT applicable.
 */
typedef NS_ENUM(NSInteger, M800ClientState) {
    /// Client is stopped
    M800ClientStateStopped,
    /// Client is initializing
    M800ClientStateInitializing,
    /// Client is configurating
    M800ClientStateConfigurating,
    /// Client is initialized
    M800ClientStateInitialized,
    /// Client is Ready to use.
    M800ClientStateReady,
    /// Client is registered to server.
    M800ClientStateRegistered
    
};

/**
 * This enum specifies the video cameras that can be selected when streaming video. Selection affects all video
 * sessions that may be in progress on this client/device
 */
typedef NS_ENUM(NSInteger, M800ClientVideoCameraSelection){
    // Description:
    // Selects the back facing camera for to capture the video feed from
    M800_VC_BACK,
    
    // Description:
    // Selects the front facing vide camera to capture video from
    M800_VC_FRONT,
};




/**
 * The M800Client protocol mirror methods that are defined in MSMEClient implemented by C++.
 * M800Client provides a centralized entry point of control and coordination for MSME engine running in apps.
 * If app want to use calling module, M800Client must have correct configuration.
 * Every app only have one instance of MSMEClient, access it by invoking the 'client' class method in class M800ClientAccessor.
 */
@protocol M800Client <NSObject>

#pragma mark - Properties

/** The state of client */
@property (nonatomic, readonly) M800ClientState state;

#pragma mark - Control Operations
/**
 * @method
 *
 * @abstract
 * Starts client with a new configuration.
 * @param configuration
 * A new configuration conatins username, password, resources and so on.
 */
- (void)start:(M800ClientConfiguration*)configuration;

/**
 * @method
 * @abstract
 * Stops clilent and release resources.
 */
- (void)stop;

/**
 *@abstract
 * Connect(Register) to server with configurated resource. 
 */
- (void)connect;


/**
 *@abstract
 * Reset the m800 engine purpose
 *@param purpose
 * either M800ClientPurposeNormal or M800ClientPurposeProcessPush
 */
- (BOOL)resetPurpose:(M800ClientPurpose)purpose;


/**
 * @method
 *
 * @abstract
 * get current configuration
 *
 * @return configuration
 * The current configuration.
 *
 */
- (M800ClientConfiguration*) getCurrentConfiguration;

#pragma mark - Delegate
/**
 * @method
 * @abstract
 * Adds new delegate into client.
 * @param delegate
 * A new client will be added to client. If already exist, ignored.
 */
- (void)addClientDelegate:(id<M800ClientDelegate>)delegate;
/**
 * @method
 * @abstract
 * Removes a delegate from client.
 * @param delegate
 * A delegate will be removed from client. If not exists, ignored.
 */
- (void)removeClientDelegate:(id<M800ClientDelegate>)delegate;

#pragma mark - Call
/** Makes a call to given receiver which maybe phone number or user id.
 * If receiver is a phone number, it is an offnet call.
 * If receiver is user id (JID), it is an onnet call.
 *@param username
 * username is the phonenumber
 *@param carrier
 * carrier specific the domain name in OnNet call, set to empty for OffNetCall
 *@param userInfo 
 * More extra info for creating call.
 *@param callID
 * Application define call id
 *@param enableICE
 * Specific ICE enable or not, default is false
 * @return An object comfirms to M800OutgoingCall, nil if failed.
 */
- (id<M800OutgoingCall>)createCall:(NSString*)username
                           display:(NSString*)displayName
                           carrier:(NSString*)carrier
                          userInfo:(NSDictionary*)userInfo
                            callID:(NSString*)callID
                         enableICE:(BOOL)enableICE;
/** Makes a call to given receiver which maybe phone number or user id.
 * If receiver is a phone number, it is an offnet call.
 * If receiver is user id (JID), it is an onnet call.
 *@param username
 * username is the phonenumber
 *@param carrier
 * carrier specific the domain name in OnNet call, set to empty for OffNetCall
 *@param userInfo
 * More extra info for creating call.
 *@param callID
 * Application define call id
 *@param enableICE
 * Specific ICE enable or not, default is false
 *
 * @param result Return the result for creating call in engine.
 *
 * @return An object comfirms to M800OutgoingCall, nil if failed.
 */
- (id<M800OutgoingCall>)createCall:(NSString *)username
                           display:(NSString *)displayName
                           carrier:(NSString*)carrier
                          userInfo:(NSDictionary *)userInfo
                            callID:(NSString *)callID
                         enableICE:(BOOL)enableICE
                            result:(NSNumber**)result;

/* TODO: TWH_MCS : multiple call sessions -> change this to return a list of calls */
/** Returns the current call session object from engine
 *
 * @return An object confirms to M800Call protocol, nil if none.
 */
- (id<M800Call>)getCurrentCall;
/**
 * @method
 *
 * @abstract
 * get number of the  calls
 *
 * @return
 * number of  calls
 *
 */
- (int) numOfCalls;

/**
 * @method
 *
 * @abstract
 * get number of the active calls
 *
 * @return
 * number of active calls
 *
 */
- (int) numOfActiveCalls:(NSString *)callID;

/**
 * @method
 *
 * @abstract
 * check the any call active
 *
 * @return bool
 * true if it has active call
 *
 */
- (bool) hasCallActive:(NSString *)callID;

/**
 * Catches remote notification from system.
 * If notification is incoming call, then create a new call session and return it.
 * 
 * If notification is an missed call one, then MSME would post event
 * M800CallDelegate::callTerminated: from delegate and return nil;
 *
 * @param userInfo
 * A dictionary contains all information from push.
 * @return An object conforms to M800IncomingCall protocol represents incoming call. Otherwise return nil.
 */
- (id<M800IncomingCall>)catchRemoteNotification:(NSDictionary*)userInfo;

/**
 *  Rejects an incoming push call since we are busy that cannot answer it.
 *
 *  @param userInfo The user infor of remote notification.
 */
- (void) rejectCallSinceBusyWithRemoteNotification:(NSDictionary*)userInfo;

/**
 *  Selects the video camera to be used by the client for video call sessions
 *
 *  @param videoCamera The video camera to use. Its either the front or back facing camera
 */
- (void) selectVideoCamera:(M800ClientVideoCameraSelection)videoCamera;
/**
 * send OOD(out of dialog) message to a sip address
 * @param destination is an sip addresss like "sip:abc.com"
 * @param timeout is timeout value defined for this request, if timeout, response will return
 * @return transactionId Uniquely identifies this SendOod request in the responses that will be returned
 */
- (unsigned) SendOod:(NSString*) pOodReqDestination
                     timeout: (unsigned int) timeout;

@end


@interface M800ClientAccessor : NSObject
/** Create M800 client which be responsed for communicating with M800 lower side.
 * @return The object implements M800Client
 * @see M800Client
 */
+ (id<M800Client>)client;
@end



