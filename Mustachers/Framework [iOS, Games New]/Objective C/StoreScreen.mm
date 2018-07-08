//
//  StoreScreen.m
//  BakeSlap
//
//  Created by Nick Raptis on 8/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "StoreScreen.h"
#import "Root.h"

@implementation StoreScreen

@synthesize arrayProducts;

@synthesize targetPurchase;
@synthesize imageViewBack;

@synthesize isConnecting;
@synthesize isRequesting;
@synthesize isPaying;

@synthesize didSucceed;
@synthesize didFail;
@synthesize didCancel;

@synthesize buttonBuy;
@synthesize buttonClose;

@synthesize imageViewText;

@synthesize imageViewTextConnecting;
@synthesize imageViewTextError;
@synthesize imageViewTextSuccess;

@synthesize activityIndicator;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    isConnecting=NO;
    isRequesting=NO;
    isPaying=NO;
    
    didSucceed=NO;
    didFail=NO;
    didCancel=NO;
    
    tryPurchase=NO;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    self.view.frame = CGRectMake(self.view.frame.origin.x,self.view.frame.origin.y,self.view.frame.size.width,self.view.frame.size.height);
    return self;
}

- (void)dealloc
{
    self.buttonBuy=nil;
    self.buttonClose=nil;
    self.imageViewText=nil;
    self.activityIndicator=nil;
    self.arrayProducts=nil;
}

- (void)didReceiveMemoryWarning
{
    
}

- (void)viewDidLoad
{
    [self setUp];
    [super viewDidLoad];
    
    if(gAppHeight > imageViewBack.frame.size.height)
    {
        float aHeightRatio = ((float)gAppHeight) / imageViewBack.frame.size.height;
        
        float aNewWidth = imageViewBack.frame.size.width * aHeightRatio;
        float aNewHeight = imageViewBack.frame.size.height * aHeightRatio;
        
        float aCenterX = self.view.frame.size.width / 2.0f;
        float aCenterY = self.view.frame.size.height / 2.0f;
        
        //TODO: Kludge, to shift background image slightly more.. lol
        imageViewBack.frame = CGRectMake(aCenterX - (aNewWidth / 2.0f + 18.0f), aCenterY - aNewHeight / 2.0f, aNewWidth, aNewHeight);
    }
    else
    {
        //NSLog(@"Height is FINE... LOL!!");
    }
    
}

- (BOOL)hasProducts
{
    if(arrayProducts)
    {
        if([arrayProducts count] > 0)return YES;
    }
    return NO;
}

- (void)setUp
{
    imageViewTextSuccess.hidden = YES;
    if([SKPaymentQueue canMakePayments])
    {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        [self requestProductData];
    }
    else
    {
        [activityIndicator stopAnimating];
        activityIndicator.hidden = YES;
        
        buttonBuy.hidden = NO;
        
        imageViewText.image = [UIImage imageNamed:@"store_text_disabled.png"];
		if(didSucceed == false)
        {
            didFail = true;
        }
        
        imageViewTextError.hidden = buttonBuy.hidden;
        imageViewTextConnecting.hidden = !(buttonBuy.hidden);
    }
    
    //store_text_canceled.png
    //store_text_error.png
    //store_text_successful.png
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	return YES;
}

- (void)buy:(NSString*)targetItem
{
    NSLog(@"Purchasing[%@]", targetItem);
    
    tryPurchase = NO;
    
    self.targetPurchase=nil;
    self.targetPurchase=[[NSString alloc] initWithString:targetItem];
    
    //if(isConnecting == false)
    //{
    
    if([self hasProducts] == NO)
    {
        [activityIndicator stopAnimating];
        activityIndicator.hidden = YES;
        buttonBuy.hidden = NO;
       
        isConnecting = NO;
        isPaying = NO;
        isRequesting = NO;
        if(didSucceed == NO)
        {
            imageViewText.image = [UIImage imageNamed:@"store_text_error.png"];
            didFail = YES;
        }
        
        tryPurchase=YES;
        
        [self requestProductData];
        
        imageViewTextError.hidden = buttonBuy.hidden;
        imageViewTextConnecting.hidden = !(buttonBuy.hidden);
        
        return;
    }
    
    //paymentWithProductIdentifier
    
    [activityIndicator startAnimating];
    activityIndicator.hidden = NO;
    
    buttonBuy.hidden = YES;
    imageViewTextError.hidden = buttonBuy.hidden;
    imageViewTextConnecting.hidden = !(buttonBuy.hidden);
    imageViewTextSuccess.hidden = YES;
    
    imageViewText.image = [UIImage imageNamed:@"store_text_connecting.png"];
    
    isConnecting = YES;
    isPaying = YES;
    isRequesting = NO;
    
    SKMutablePayment *payment = [SKMutablePayment paymentWithProductIdentifier:targetItem];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    
}

- (void)requestProductData
{
    NSLog(@"Request Product Data!");
    
    imageViewText.image = [UIImage imageNamed:@"store_text_connecting.png"];
    
    [activityIndicator startAnimating];
    activityIndicator.hidden = NO;
    
    isConnecting=YES;
    
    buttonBuy.hidden = YES;
    imageViewTextError.hidden = buttonBuy.hidden;
    imageViewTextConnecting.hidden = !(buttonBuy.hidden);
    
    //SKProductsRequest *request= [[SKProductsRequest alloc] initWithProductIdentifiers: [NSSet setWithObjects:@"crazy_lizard_upgrade", nil]];
    SKProductsRequest *request= [[SKProductsRequest alloc] initWithProductIdentifiers: [NSSet setWithObjects:@"jiggle_upgrade", nil]];
    
    request.delegate = self;
    
    [request start];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSLog(@"Product Request Response: [%@]", response);
    
    isRequesting=NO;
    isConnecting=NO;
    
    [activityIndicator stopAnimating];
    activityIndicator.hidden = YES;
    
    buttonBuy.hidden = NO;
    
    imageViewTextError.hidden = buttonBuy.hidden;
    imageViewTextConnecting.hidden = !(buttonBuy.hidden);
    
    NSArray *myProduct = response.products;
    
    NSLog(@"[[%@]]", response.products);
    
    if(arrayProducts==nil)arrayProducts=[[NSMutableArray alloc] init];
    
    for(SKProduct *aProduct in myProduct)
    {
        NSString *aTemp = [aProduct productIdentifier];
        FString aString = FString([aTemp UTF8String]);
        
        if([arrayProducts containsObject:aProduct])
        {
            
        }
        else
        {
            [arrayProducts addObject:aProduct];
        }
    }
    
    
    if((self.targetPurchase != nil) && tryPurchase && [self hasProducts])
    {
        [self buy:self.targetPurchase];
        tryPurchase = NO;
    }
    else
    {
        imageViewText.image = [UIImage imageNamed:@"store_text_error.png"];
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for(SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                NSLog(@"SKPaymentTransactionStatePurchased");
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStatePurchasing:
                NSLog(@"SKPaymentTransactionStatePurchasing");
                break;
            case SKPaymentTransactionStateFailed:
                NSLog(@"SKPaymentTransactionStateFailed");
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                NSLog(@"SKPaymentTransactionStateRestored");
                [self restoreTransaction:transaction];
            default:
                NSLog(@"default:");
                break;
        }
    }
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"completeTransaction");
    
    [activityIndicator stopAnimating];
    activityIndicator.hidden = YES;
    
    buttonBuy.hidden = YES;
    
    imageViewTextError.hidden = YES;
    imageViewTextConnecting.hidden = YES;
    imageViewTextSuccess.hidden = NO;
    
    isConnecting=NO;
    isPaying=NO;
    
    didSucceed=YES;
    didFail=NO;
    didCancel=NO;
    
    self.targetPurchase=nil;
    
    imageViewText.image = [UIImage imageNamed:@"store_text_successful.png"];
    
    [gRoot purchaseSuccessful:transaction.payment.productIdentifier];
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void)restorePurchases
{
    [activityIndicator startAnimating];
    activityIndicator.hidden = NO;
    
    buttonBuy.hidden = YES;
    imageViewTextError.hidden = buttonBuy.hidden;
    imageViewTextConnecting.hidden = !(buttonBuy.hidden);
    imageViewTextSuccess.hidden = YES;
    
    imageViewText.image = [UIImage imageNamed:@"store_text_restoring.png"];
    
    isConnecting = YES;
    isPaying = NO;
    isRequesting = NO;
    
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
    [self completeTransaction:transaction];
}

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
    NSLog(@"Restore Failed!");
    
    isConnecting=NO;
    isPaying=NO;
    
    didSucceed=NO;
    didFail=YES;
    didCancel=NO;
}

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
    isConnecting=NO;
    isPaying=NO;
    
    didSucceed=YES;
    didFail=NO;
    didCancel=NO;
    
    NSLog(@"Restore Succeeded!");
    
    ShowAlert("Restored", "Purchases have been restored.");
    
    //[gRoot purchaseSuccessful:@"lizard"];
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
    self.targetPurchase=nil;
    
    activityIndicator.hidden = YES;
    buttonBuy.hidden = NO;
    
    imageViewTextError.hidden = buttonBuy.hidden;
    imageViewTextConnecting.hidden = !(buttonBuy.hidden);
    
    NSLog(@"Fail Reason [%@]", transaction.error);
    
	if(didSucceed == NO)
	{
        [activityIndicator stopAnimating];
        
        isConnecting=NO;
        isPaying=NO;
        
        didSucceed=NO;
        didFail=YES;
        didCancel=NO;
        
		if(transaction.error.code == SKErrorPaymentCancelled)
		{
            imageViewText.image = [UIImage imageNamed:@"store_text_canceled.png"];
            didCancel=YES;
		}
        else
        {
            imageViewText.image = [UIImage imageNamed:@"store_text_error.png"];
        }
	}
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonBuy)
    {
        [self buy:@"jiggle_upgrade"];
    }
    if(sender == buttonClose)
    {
        //[self.view removeFromSuperview];
        
        [gRoot killPopup];
        
        if([gRoot respondsToSelector:@selector(hideStore)])
        {
            [gRoot performSelector:@selector(hideStore)];
        }
        
        //[gRoot hideStore];
        
        //[gRoot enterForeground];
    }
}

- (void)resetAll
{
    [activityIndicator stopAnimating];
    isConnecting=NO;
    isRequesting=NO;
    isPaying=NO;
    didSucceed=NO;
    didFail=NO;
    didCancel=NO;
    tryPurchase=NO;
}

@end
