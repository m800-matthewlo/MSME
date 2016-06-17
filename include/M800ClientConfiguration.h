//
//  M800ClientConfiguration.h
//  MSME
//
//  Created by Justin Liu on 24/6/14.
//  Copyright (c) 2014 M800 Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, M800ClientPurpose) {
    M800ClientPurposeNormal,
    M800ClientPurposeProcessPush,
};

typedef  NS_ENUM(NSInteger,  M800LogsDestination) {
    /*
     *  M800 log output is completely disabled
     */
    M800LogsDisabled,
    
    /*
     *  M800 log output is sent to the STDOUT
     */
    M800LogsStdout,
    
    /*
     * M800 log output is sent to file.
     */
    M800LogsFile,
    
    /*
     *  M800 log output is sent to both STDOUT and FILE
     *  The FILE path is set via the setLogPath() method otherwise
     *  logs are only output the STDOUT
     */
    M800LogsStdoutAndFile
};

typedef  NS_ENUM(NSInteger,  M800CallReconnectionMode)  {
    
    /* M800CallReconnectionModeNetworkChange:
     *
     *  Call reconnection is only attempted if the network changes.
     *  I.e., A switching from 3G to Wifi will trigger a call reconnection.
     */
    M800CallReconnectionModeNetworkChange,
    
    /* M800CallReconnectionModeRtpLoss:
     *
     *  Call reconnection is only attempted when RTP loss is detected
     *  I.e., If we have not changed networks but the consequetive RTP loss exceeds the
     *  threshold then trigger a call reconnection to try to save the call.
     */
    M800CallReconnectionModeRtpLoss,
    
    /* M800CallReconnectionModeAll:
     *
     *  All modes of call reconnection described above are valid reasons to
     *  attempt a call reconnection
     */
    M800CallReconnectionModeAll
};


/**
 * Defines the resource which provides neccessory information for connecting to server.
 */
@interface M800ClientResource : NSObject

/** Resource's host address, e.g. 192.168.1.1*/
@property (nonatomic, retain) NSString *host;
/** Resource's port, e.g. 5222 */
@property (nonatomic, assign) NSInteger port;
/** Resource's type, e.g. com.maaii.resource.sbc */
@property (nonatomic, retain) NSString *type;
/** Resource's protocol, e.g. sip, sips */
@property (nonatomic, retain) NSString *protocol;
/** Resource's priority */
@property (nonatomic, retain) NSString *priority;

/**
 *
 */
//- (M800ClientResource*)resourceWithDictionary:(NSDictionary*)dict;
@end

@interface M800ClientConfiguration : NSObject

@property (nonatomic, assign) BOOL supportCallingWithoutRegistration;
@property (nonatomic, assign) BOOL supportSessionTimer;
@property (nonatomic, assign) BOOL supportSendDTMFWithSIPInfo;
@property (nonatomic, assign) BOOL supportAutoRejectIncomingPushCallSinceBusy;
@property (nonatomic, assign) BOOL supportAcknowledgePushCall;

// Call reconnection
@property (nonatomic, assign) BOOL supportCallReconnection;
@property (nonatomic, assign) M800CallReconnectionMode callReconnectionMode;
@property (nonatomic, assign) int  callReconnectionPacketLossThresholdInMs;
@property (nonatomic, assign) int  callReconnectionOnRtpLossThresholdInMs;
@property (nonatomic, assign) int  callReconnectionMaxRetries;
@property (nonatomic, assign) int  callReconnectionTimeoutInSec;

// Call SBC Failover
@property (nonatomic, assign) BOOL supportCallFailover;
@property (nonatomic, assign) int  callFailoverTimeoutInMs;

// Call reconciliation
@property (nonatomic, assign) BOOL supportCallReconciliation;

// Call Heartbeat
@property (nonatomic, assign) int callHeartbeatPeriodInMs;

@property (nonatomic, retain) NSString * username;
@property (nonatomic, retain) NSString * carrier;
@property (nonatomic, retain) NSString * password;
@property (nonatomic, retain) NSString * caCertificatePath;
@property (nonatomic, retain) NSString * userAgent;
@property (nonatomic, assign) M800LogsDestination logsDestination;
@property (nonatomic, retain) NSString * logPath;
@property (nonatomic, retain) NSURL    * ringbackURL;
@property (nonatomic, retain) NSURL    * holdToneURL;
@property (nonatomic, retain) NSURL    * stoptoneURL;
@property (nonatomic, retain) NSURL    * rtpLossToneURL;
@property (nonatomic, assign) int  packetLossThreshold;

@property (nonatomic, assign) BOOL isEnabledICE;

@property (nonatomic, retain) NSString * iceSettings;

@property (nonatomic, retain) NSString * audioProcessingFeatures;

@property (nonatomic, assign) M800ClientPurpose purpose;

@property (nonatomic, retain) NSString * ssoToken;
@property (nonatomic, retain) NSString * deviceId;
@property (nonatomic, retain) NSString * applicationId;

@property (nonatomic, assign) BOOL targetServerToMSS;
@property (nonatomic, assign) BOOL supportSSOToken;
@property (nonatomic, assign) int networkQualityReportLevel;

@property (nonatomic, retain) NSString * primaryDns;
@property (nonatomic, retain) NSString * secondaryDns;


typedef NS_ENUM(NSInteger, EM800MediaSecurity){
    
    EM800MediaSecurityInvalid = -1,
    
    /**
     *  EM800MediaSecurityDisabled:
     *      Media security (SRTP) is disabled. All media will be sent and received will be insecure RTP
     */
    EM800MediaSecurityDisabled = 0,
    
    /**
     *  EM800MediaSecurityEnabled:
     *      Media security is enabled and SAVP will be only offered if the peer offers SAVP
     *      Media security is not guaranteed when setting to mediaSecurity to this mode.
     */
    EM800MediaSecurityEnabled,
    
    /**
     *  EM800MediaSecuritySecure:
     *      Media will be always secured via SRTP.
     */
    EM800MediaSecuritySecure,
};
@property (nonatomic, assign) EM800MediaSecurity mediaSecurity;

// Video call config
@property (nonatomic, assign) BOOL supportVideoCall;

/**
 * Sets a resource into configuration, according to type and priority, a unique key
 * will be generated for storing. If resource with same key already exist, new 
 * resource will override the old one.
 * @param resource The new resource to be set.
 */
- (void)addResource:(M800ClientResource*)resource;
/**
 * Returns a resource with given type and priority.
 * @param type The type of resource.
 * @param priority The priority of resource.
 * @return Returns a resource with given type and priority if exists, otherwise nil
 */
- (M800ClientResource*)getResourceWithType:(NSString*)type prority:(NSString*)priority;

@end
