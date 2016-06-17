//
//  MEClientDelegate.h
//  M800
//
//  Created by Justin Liu on 21/5/14.
//  Copyright (c) 2014 Maaii. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol M800Client;

/**
 * The delegate of M800Client to handle events.
 */
@protocol M800ClientDelegate <NSObject>
@optional
/**
 * Client has passed through its basic initialization and is awaiting configuration.
 * @param client The existing client.
 */
- (void)clientInitialized:(id<M800Client>)client userInfo:(NSDictionary*)userInfo;
/**
 * oodReseponse from lower layer, it can be either a real respeonse or timeout of the request
 * @param client. The existing client
 * @param opaque is the session Id of the request
 * @param responseTime, is the difference between sending and reeiving time
 * @param responseCode is the respoense code from response, it is invalid when this is a timeout event
 * @param isTimeout indicate if this is a timeout event or actual sip response, true means it is a timeout event.
 */
- (void)onOodResponse:(id<M800Client>)client opaque:(unsigned int)opaque responseTime: (long long)responseTime responseCode:(short) responseCode isTimeout: (BOOL) isTimeout;

/**
 * report the reconciliation result when incoming call received and an outgoing call with same remote user is outstanding
 * @param client. The exiting client
 * @param incomingCall. The incoming call object
 * @param outgoingCall. The outgoing call object
 * @param reconcileResult. A flag indicate whether local user win in the reconciliation
 * @param callerInfo.
 */
- (void)client:(id<M800Client>)client incomingCall:(id<M800IncomingCall>)incoming outgoingCall:(id<M800OutgoingCall>)outgoing reconcileResult:(BOOL)isWin callerInfo:(NSDictionary*)callerInfo;

@required
/**
 * Client is ready to be used. It has accepted the supplied configuration.
 * At this point the client has not registered with the SIP server but will do
 * so either in response to registerClient message and when making a call where it
 * automatically register.
 * @param client The existing client.
 */
- (void)clientReady:(id<M800Client>)client userInfo:(NSDictionary*)userInfo;
/**
 * Client is not ready. Likey reason is the configuration was not accepted by the SIP Client Engine.
 * A new configuration should be supplied in order to make the client Ready
 * @param client The existing client.
 */
- (void)clientNotReady:(id<M800Client>)client reason:(NSError*)reason userInfo:(NSDictionary*)userInfo;
/**
 * Client is ready and registered with the SIP server.
 * @param client The existing client.
 */
- (void)clientRegistered:(id<M800Client>)client userInfo:(NSDictionary*)userInfo;
/**
 * Client is ready but is now unregistred from the SIP server.
 * @param client The existing client.
 */
- (void)clientUnRegistered:(id<M800Client>)client userInfo:(NSDictionary*)userInfo;
/**
 * Client received incoming call from server.
 * @param client The existing client.
 * @param call The incoming call object.
 */
- (void)client:(id<M800Client>)client didReceiveIncomingCall:(id<M800IncomingCall>)call callerInfo:(NSDictionary*)callerInfo;
@end
