//  PopoverContainer.h
//  Wrangler
//  Created by Nick Raptis on 8/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

#import <UIKit/UIKit.h>

@interface PopoverContainer : UIViewController <UIGestureRecognizerDelegate>
{
	BOOL						isClosing;
	BOOL						killRectExists;
	
    CGRect						killRect;
	
	float						animationTranslateX;
	float						animationTranslateY;
    
    BOOL                        disablePinchClose;
}

@property (nonatomic, retain) IBOutlet UIButton *buttonClose;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewPopoverBack;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewGestureIcon;

@property (nonatomic, retain) IBOutlet UIViewController *currentViewController;


@property (nonatomic, retain) UIPinchGestureRecognizer *pinchRecognizer;


@property (nonatomic, assign) BOOL disablePinchClose;

- (IBAction)click:(UIButton*)sender;

- (void)didPinch:(UIPinchGestureRecognizer *)recognizer;
- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context;
- (void)setGestureImage:(NSString *)targetPath;
//- (void)

//Hey, Yo, Call this AFTER you set the image...

- (void)animateMe:(CGRect)targetRect;

- (void)languageUpdate;

- (void)loadImage:(NSString*)targetImagePath;
- (void)loadImageBackground:(NSString*)targetImagePath;
- (void)loadImageGesture:(NSString*)targetImagePath;

- (void)setTarget:(UIViewController*)targetViewController;

- (void)close;
- (void)sweepAway:(BOOL)targetLeft;

@end
