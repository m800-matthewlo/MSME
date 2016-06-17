//
//  M800Connectivity.h
//  MSME-ios
//
//  Created by Justin Liu on 29/12/14.
//  Copyright (c) 2014 M800. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^ M800ConnectivityFeedbackBlock)(BOOL, double, double, NSUInteger, NSUInteger, NSUInteger, NSString*);

@protocol M800ConnectivityFeedback <NSObject>

//- (void)feedback:(BOOL)result sent:(NSUInteger)sent received:(NSUInteger)received message:(NSString *)message;

- (void)feedback:(BOOL)reachable
       bandwidth:(double)bandwidth
      packetLost:(double)packetLost
            sent:(NSUInteger)sent
        received:(NSUInteger)received
          failed:(NSUInteger)failed
         message:(NSString *)message;
@end

@interface M800Connectivity : NSObject
+ (M800Connectivity*)sharedInstance;

/**
 * Check instant connecitivty for RTP stream
 *
 * @param inf Network interface to be checked. For iOS, normally, "en0" is wifi and 3G/4G is "pdp_ip0"
 * @param host Server's host
 * @param port Server's port
 * @param gap The milliseconds between two out packets
 * @param packets The number of packet to be tried.
 * @param timeout Timeout milliseconds if no response from server.
 * @param feeback The delegate handle result.
 */
- (void)checkRTPConnectivityWithInterface:(NSString*)inf
                                   server:(NSString*)host
                                     port:(NSUInteger)port
                                      gap:(NSUInteger)gap
                                  packets:(NSUInteger)packets
                                  timeout:(NSUInteger)timeout
                                 feedback:(id<M800ConnectivityFeedback>)feedback;
/**
 * Check instant connecitivty for RTP stream and feedback with block
 *
 * @param inf Network interface to be checked. For iOS, normally, "en0" is wifi and 3G/4G is "pdp_ip0"
 * @param host Server's host
 * @param port Server's port
 * @param gap The milliseconds between two out packets
 * @param packets The number of packet to be tried.
 * @param timeout Timeout milliseconds if no response from server.
 * @param feebackBlock The block handles the result.
 */
- (void)checkRTPConnectivityWithInterface:(NSString*)inf
                                   server:(NSString*)host
                                     port:(NSUInteger)port
                                      gap:(NSUInteger)gap
                                  packets:(NSUInteger)packets
                                  timeout:(NSUInteger)timeout
                            feedbackBlock:(M800ConnectivityFeedbackBlock)feedbackBlock;
/**
 * Check bandwidth from local network to UDP Echo Server.
 *
 * @param inf Network interface to be checked. For iOS, normally, "en0" is wifi and 3G/4G is "pdp_ip0"
 * @param host Server's host
 * @param port Server's port
 * @param packets The number of packets to be sent.
 * @param packetSize The size of each packet to be sent.
 * @param gap The milliseconds between two out packets
 * @param timeout Timeout milliseconds if no response from server.
 * @param feebackBlock The block handles the result.
 */
- (void)checkBandwidthWithInterface:(NSString*)inf
                             server:(NSString*)host
                               port:(NSUInteger)port
                            packets:(NSUInteger)packets
                         packetSize:(NSUInteger)packetSize
                                gap:(NSUInteger)gap
                            timeout:(NSUInteger)timeout
                      feedbackBlock:(M800ConnectivityFeedbackBlock)feedbackBlock;
@end
