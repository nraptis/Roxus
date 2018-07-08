//
//  SwipeListener.m
//  FiatReloaded
//
//  Created by Nick Raptis on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "SwipeListener.h"

@implementation SwipeListener

@synthesize recognizerSwipeRight;
@synthesize recognizerSwipeLeft;
@synthesize recognizerSwipeUp;
@synthesize recognizerSwipeDown;

@synthesize delegateSwipe;

- (void)addTo:(UIView*)targetView
{
    [self addTo:targetView withUpEnabled:YES withDownEnabled:YES withRightEnabled:YES withLeftEnabled:YES];
}

- (void)dealloc
{
    NSLog(@"*** --- Swipe Listener Deallocated!!!!!");
    if(self.delegateSwipe)
    {
        if([[self.delegateSwipe class] isSubclassOfClass:[UIViewController class]])
        {
            UIView *aView = ((UIViewController*)self.delegateSwipe).view;
            [self removeFrom:aView];
        }
        else
        {
            NSLog(@"Out Delegate Is like... doesn't exist... like...");
            
        }
    }
    self.delegateSwipe=nil;
}

- (void)addTo:(UIView*)targetView
withUpEnabled:(BOOL)targetUpEnabled
withDownEnabled:(BOOL)targetDownEnabled
withRightEnabled:(BOOL)targetRightEnabled
withLeftEnabled:(BOOL)targetLeftEnabled
{
    if(targetUpEnabled)
    {
        self.recognizerSwipeUp = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeInternal:)];
        [self.recognizerSwipeUp setDirection:UISwipeGestureRecognizerDirectionUp];
        [targetView addGestureRecognizer:self.recognizerSwipeUp];
    }
    if(targetDownEnabled)
    {
        self.recognizerSwipeDown = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeInternal:)];
        [self.recognizerSwipeDown setDirection:UISwipeGestureRecognizerDirectionDown];
        [targetView addGestureRecognizer:self.recognizerSwipeDown];
    }
    if(targetRightEnabled)
    {
        self.recognizerSwipeRight = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeInternal:)];
        [self.recognizerSwipeRight setDirection:UISwipeGestureRecognizerDirectionRight];
        [targetView addGestureRecognizer:self.recognizerSwipeRight];
    }
    if(targetLeftEnabled)
    {
        self.recognizerSwipeLeft = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeInternal:)];
        self.recognizerSwipeLeft.delegate = self;
        [self.recognizerSwipeLeft setDirection:UISwipeGestureRecognizerDirectionLeft];
        [targetView addGestureRecognizer:self.recognizerSwipeLeft];
    }
}

- (void)didSwipeInternal:(UISwipeGestureRecognizer*)swipeRecognizer
{
    if(self.recognizerSwipeUp == swipeRecognizer)
    {
        [delegateSwipe didSwipe:self withDirection:0];
        return;
    }
    if(self.recognizerSwipeDown == swipeRecognizer)
    {
        [delegateSwipe didSwipe:self withDirection:1];
        return;
    }
    
    if(self.recognizerSwipeLeft == swipeRecognizer)
    {
        [delegateSwipe didSwipe:self withDirection:2];
        return;
    }
    
    if(self.recognizerSwipeRight == swipeRecognizer)
    {
        [delegateSwipe didSwipe:self withDirection:3];
        return;
    }
}

- (void)removeFrom:(UIView *)targetView
{
    if(self.recognizerSwipeUp)[targetView removeGestureRecognizer:self.recognizerSwipeUp];
    if(self.recognizerSwipeDown)[targetView removeGestureRecognizer:self.recognizerSwipeDown];
    if(self.recognizerSwipeRight)[targetView removeGestureRecognizer:self.recognizerSwipeRight];
    if(self.recognizerSwipeLeft)[targetView removeGestureRecognizer:self.recognizerSwipeLeft];
    
    self.recognizerSwipeUp=nil;
    self.recognizerSwipeDown=nil;
    self.recognizerSwipeRight=nil;
    self.recognizerSwipeLeft=nil;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

//- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
//{
//    return YES;
//}

@end





