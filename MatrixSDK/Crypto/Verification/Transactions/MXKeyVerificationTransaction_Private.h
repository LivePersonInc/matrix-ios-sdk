/*
 Copyright 2019 New Vector Ltd

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import "MXKeyVerificationTransaction.h"

#import "MXKeyVerificationAccept.h"
#import "MXKeyVerificationCancel.h"
#import "MXKeyVerificationKey.h"
#import "MXKeyVerificationMac.h"
#import "MXKeyVerificationStart.h"
#import "MXKeyVerificationDone.h"


@class MXKeyVerificationManager, MXHTTPOperation, MXEvent;


NS_ASSUME_NONNULL_BEGIN

/**
 The `MXKeyVerificationTransaction` extension exposes internal operations.
 */
@interface MXKeyVerificationTransaction ()

@property (nonatomic, readonly, weak) MXKeyVerificationManager *manager;
@property (nonatomic, nullable) MXKeyVerificationStart *startContent;

- (instancetype)initWithOtherDevice:(MXDeviceInfo*)otherDevice andManager:(MXKeyVerificationManager*)manager;

- (nullable instancetype)initWithOtherDevice:(MXDeviceInfo*)otherDevice startEvent:(MXEvent *)event andManager:(MXKeyVerificationManager *)manager;

@property (nonatomic) NSString *transactionId;
- (void)setDirectMessageTransportInRoom:(NSString*)roomId originalEvent:(NSString*)eventId;

- (void)didUpdateState;

- (void)cancelWithCancelCodeFromCryptoQueue:(MXTransactionCancelCode *)code;


#pragma mark - Outgoing to_device events
- (MXHTTPOperation*)sendToOther:(NSString*)eventType content:(NSDictionary*)content
                        success:(void (^)(void))success
                        failure:(void (^)(NSError *error))failure;


#pragma mark - Incoming to_device events

- (void)handleAccept:(MXKeyVerificationAccept*)acceptContent;
- (void)handleCancel:(MXKeyVerificationCancel*)cancelContent;
- (void)handleKey:(MXKeyVerificationKey*)keyContent;
- (void)handleMac:(MXKeyVerificationMac*)macContent;

@end

NS_ASSUME_NONNULL_END
