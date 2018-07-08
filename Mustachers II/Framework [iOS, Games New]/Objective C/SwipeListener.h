//
//  SwipeListener.h
//  FiatReloaded
//
//  Created by Nick Raptis on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#define SWIPE_UP 0
#define SWIPE_DOWN 1
#define SWIPE_LEFT 2
#define SWIPE_RIGHT 3

@class SwipeListener;

@protocol SwipeListenerDelegate <NSObject>

//Uses this: Up = 0, Down = 1, Left = 2, Right = 3
- (void) didSwipe:(SwipeListener *)targetSwipeListener withDirection:(int)targetDirection;

@end

@interface SwipeListener : NSObject
{
    UISwipeGestureRecognizer        *recognizerSwipeRight;
    UISwipeGestureRecognizer        *recognizerSwipeLeft;
    UISwipeGestureRecognizer        *recognizerSwipeUp;
    UISwipeGestureRecognizer        *recognizerSwipeDown;
    
    id <SwipeListenerDelegate>      delegateSwipe;
}

@property (nonatomic, retain) id delegateSwipe;

@property (nonatomic, retain) UISwipeGestureRecognizer *recognizerSwipeRight;
@property (nonatomic, retain) UISwipeGestureRecognizer *recognizerSwipeLeft;
@property (nonatomic, retain) UISwipeGestureRecognizer *recognizerSwipeUp;
@property (nonatomic, retain) UISwipeGestureRecognizer *recognizerSwipeDown;

- (void)didSwipeInternal:(UISwipeGestureRecognizer*)swipeRecognizer;

- (void)initWithView:(UIView*)targetView;
- (void)initWithView:(UIView*)targetView
withUpEnabled:(BOOL)targetUpEnabled
withDownEnabled:(BOOL)targetDownEnabled
withRightEnabled:(BOOL)targetRightEnabled
withLeftEnabled:(BOOL)targetLeftEnabled;

- (void)addTo:(UIView*)targetView;
- (void)addTo:(UIView*)targetView
withUpEnabled:(BOOL)targetUpEnabled
withDownEnabled:(BOOL)targetDownEnabled
withRightEnabled:(BOOL)targetRightEnabled
withLeftEnabled:(BOOL)targetLeftEnabled;

- (void)removeFrom:(UIView *)targetView;

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer;
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;
//- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch;

@end