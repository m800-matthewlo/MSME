//
//  M800AudioDelegate.h
//  MSME-ios
//
//  Created by Cyrus Lo on 28/7/14.
//  Copyright (c) 2014 M800. All rights reserved.
//

#ifndef MSME_ios_M800AudioDelegate_h
#define MSME_ios_M800AudioDelegate_h
#include "M800Audio.h"

/**
 * The delegate of M800Client to handle events.
 */
@protocol M800AudioDelegate <NSObject>
@optional
/**
 * Audio is being interrupted by other apps
 * @param client The existing client.
 */
- (void)audioInterrupted;

/**
 * Audio is resume from interruption
 * @param client The existing client.
 */
- (void)audioResumed;

/**
 * Client is started.
 * @param client The existing client.
 */
- (void)audioRouteChanged:(M800AudioChangeReason) reason oldDevice:(M800AudioRoutes)oldDevice newDevice:(M800AudioRoutes)newDevice;
@end

#endif
