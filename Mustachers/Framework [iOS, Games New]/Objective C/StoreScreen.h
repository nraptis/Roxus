//
//  StoreScreen.h
//  BakeSlap
//
//  Created by Nick Raptis on 8/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>

@interface StoreScreen : UIViewController <SKRequestDelegate, SKProductsRequestDelegate, SKPaymentTransactionObserver>
{
    BOOL                        tryPurchase;
    
    NSMutableArray              *arrayProducts;
    
    UIImageView                 *imageViewBack;
    
    UIImageView                 *imageViewText;
    
    UIImageView                 *imageViewTextConnecting;
    UIImageView                 *imageViewTextError;
    UIImageView                 *imageViewTextSuccess;
    
    BOOL                        isConnecting;
    BOOL                        isRequesting;
    BOOL                        isPaying;
    
    BOOL                        didSucceed;
    BOOL                        didFail;
    BOOL                        didCancel;
    
    NSString                    *targetPurchase;
}

@property (nonatomic, retain) IBOutlet UIButton *buttonBuy;
@property (nonatomic, retain) IBOutlet UIButton *buttonClose;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewBack;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewText;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewTextConnecting;
@property (nonatomic, retain) IBOutlet UIImageView *imageViewTextError;
@property (nonatomic, retain) IBOutlet UIImageView *imageViewTextSuccess;

@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityIndicator;

@property (nonatomic, retain) NSString *targetPurchase;
@property (nonatomic, retain) NSMutableArray *arrayProducts;

@property (nonatomic, assign) BOOL isConnecting;
@property (nonatomic, assign) BOOL isRequesting;
@property (nonatomic, assign) BOOL isPaying;

@property (nonatomic, assign) BOOL didSucceed;
@property (nonatomic, assign) BOOL didFail;
@property (nonatomic, assign) BOOL didCancel;

- (IBAction)click:(UIButton*)sender;

- (BOOL)hasProducts;

- (IBAction)click:(UIButton*)sender;

- (void)setUp;

- (void)restorePurchases;

- (void)buy:(NSString*)targetItem;
- (void)requestProductData;

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
- (void)completeTransaction:(SKPaymentTransaction *)transaction;
- (void)restoreTransaction:(SKPaymentTransaction *)transaction;
- (void)failedTransaction:(SKPaymentTransaction *)transaction;

- (void)resetAll;

@end
