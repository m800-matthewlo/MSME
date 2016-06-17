//
//  M800StatusCode.h
//  M800
//
//  Created by Justin Liu on 21/5/14.
//  Copyright (c) 2014 Maaii. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This list contains all status codes of SDK.
 */

/**
 *
 * VERY IMPORTANT: Modify this file need to also update MSME/api/include/MSMEStatusCode.h
 *
 **/

typedef NS_ENUM(NSInteger, M800StatusCode) {
    /** OKAY */
    M800OK  = 0,
    
    //////////////////////////////////////////////////////////////////////
    //==
    //== Engine Errors
    //==
    //////////////////////////////////////////////////////////////////////
    M800EngineCodeBase = 10000,
    M800EngineNotReady,
    M800EngineFailToRegister,
    M800EngineFailToConfigurate,
    
    M800EngineCodeLast = 19999,
    //////////////////////////////////////////////////////////////////////
    //==
    //== Call Errors
    //==
    //////////////////////////////////////////////////////////////////////
    M800CallCodeBase                            = 20000,
    
    M800CallEndedCauseRecipientNotValid         = 20001,
    M800CallEndedCauseEngineNotInitialized      = 20002,
    M800CallEndedCauseEngineNotReady            = 20003,
    M800CallEndedCauseEngineNotRegistered       = 20004,
    M800CallEndedCauseConfigurationNotSupport   = 20005,
    M800CallEndedCauseFailedToRegister          = 20006,
    M800CallEndedCauseBusy                      = 20007,
    M800CallEndedCauseMissed                    = 20008,
    M800CallEndedCauseNoNetwork                 = 20009,
    M800CallEndedCausePoorNetwork               = 20010,
    M800CallEndedCauseNetworkChangedToCellular  = 20011,
    M800CallEndedCauseNetworkChangedToWiFi      = 20012,
    M800CallEndedCauseNetworkChangedToUnknown   = 20013,
    
    /** Call is ended because of timeout */
    M800CallEndedCauseTimeout                   = 20014,
    /** Call is ended since not answered by remote user */
    M800CallEndedCauseNotAnswered               = 20015,
    /** Call is ended since local user cancel operation */
    M800CallEndedCauseCancelled                 = 20016,
    /** Call is ended since remote user deny this call */
    M800CallEndedCauseDenied                    = 20017,
    /** Call is ended since hungup by user */
    M800CallEndedCauseHungup                    = 20018,
    /** Call is ended since network changed */
    M800CallEndedCauseNetworkChanged            = 20019,
    /** Call is ended since errors happened */
    M800CallEndedCauseError                     = 20020,
    
    M800CallEndedCauseFailedToReject            = 20021,
    
    /** An incoming call was rejected becuase a call was already in progress*/
    M800CallProgressIncomingCallRejected        = 20022,
    
    M800CallEndedCauseAbortedByUser             = 20023,
    
    M800CallProgressUpdateResumeSessionId       = 20024,
    
    /*
     *  M800CallEndedCauseCallReconnection:
     *
     *  An internal call termination event that the App should never see. It signals that
     *  an existing call session was terminated as local side is trying to resume a call
     */
    M800CallEndedCauseCallReconnection          = 20025,
    
    /*
     *  M800CallBeingReconnectedByPeer:
     *
     *  This code  signals that the peer is resuming the current call and there will
     *  be an interruption in the flow of media.
     */
    M800CallBeingReconnectedByPeer              = 20026,
    
    /*
     *  M800CallEndedCauseCallReconnectionFailed:
     *
     *  If call reconnection enabled and call failed to be resumed then this event is reported
     *  back to the app in a call termination event
     */
    M800CallEndedCauseCallReconnectionFailed    = 20027,
    
    /*
     *  M800CallProvisionalResponseTimeout:
     *
     *  This is an internal event that reports a timeout waiting for the first SIP provisional
     *  repsponse ("100 Trying", "180 Ringing", etc) following the sending of an Invite
     */
    M800CallProvisionalResponseTimeout          = 20028,

    
    /*
     *  M800CallEndedSbcFailoverFailed:
     *
     *  This call ended event is reported when a failover attempt to the fallback SBC failed
     */
    M800CallEndedSbcFailoverFailed              = 20029,

    M800CallCodeLast                            = 29999,
    
    //////////////////////////////////////////////////////////////////////
    //==
    //== M5T Engine Errors
    //==
    //////////////////////////////////////////////////////////////////////
    M800_M5T_ENGINE_BASE = 40000,
    
    M800_M5T_ENGINE_LAST = 49999,
};

