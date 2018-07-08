//  GenericTouchController.h
//  Wrangler
//  Created by Nick Raptis on 10/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

#import <UIKit/UIKit.h>

@interface GenericTouchController : UIViewController <UIGestureRecognizerDelegate>
{
    UIPanGestureRecognizer              *recognizerPan;
    UIPinchGestureRecognizer            *recognizerPinch;
    UIRotationGestureRecognizer         *recognizerRotate;
    UITapGestureRecognizer              *recognizerTap;
    
    CGPoint                             panStartPosition;
    float                               pinchStartScale;
    
    CGPoint                             cyclerCenter;
    float                               cyclerScale;
    float                               cyclerRotation;
    
    float                               rotationStart;
    
    BOOL                                isPanning;
    BOOL                                isPinching;
    BOOL                                isRotating;
}

@property (nonatomic, assign) BOOL isPanning;
@property (nonatomic, assign) BOOL isPinching;
@property (nonatomic, assign) BOOL isRotating;

@property (nonatomic, retain) UIPanGestureRecognizer *recognizerPan;
@property (nonatomic, retain) UIPinchGestureRecognizer *recognizerPinch;
@property (nonatomic, retain) UIRotationGestureRecognizer *recognizerRotate;
@property (nonatomic, retain) UITapGestureRecognizer *recognizerTap;

- (void)didPan:(UIPanGestureRecognizer *)recognizer;
- (void)didPinch:(UIPinchGestureRecognizer *)recognizer;
- (void)didRotate:(UIRotationGestureRecognizer *)recognizer;
- (void)didTap:(UITapGestureRecognizer *)recognizer;

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer;
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

- (void)startPanWithX:(float)x withY:(float)y;
- (void)panWithX:(float)x withY:(float)y;
- (void)finishPanWithX:(float)x withY:(float)y;
- (void)finishPanWithX:(float)x withY:(float)y withVelX:(float)velX withVelY:(float)velY;

- (void)startScale:(float)scale;
- (void)scale:(float)scale;
- (void)finishScale:(float)scale;

- (void)startRotate:(float)scale;
- (void)rotate:(float)scale;
- (void)finishRotate:(float)scale;

@end


