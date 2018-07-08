//
//  PinchCloseImageView.h
//  Fiat
//
//  Created by Nick Raptis on 6/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define PINCH_CLOSE_START_SCALE (0.01f)
#define PINCH_CLOSE_START_ROTATION (22)

@interface PinchCloseImageView : UIViewController <UIGestureRecognizerDelegate>
{
	UIButton					*buttonClose;
	UIButton					*buttonDownload;
	
	UIImageView					*imageView;
	
	UIPinchGestureRecognizer	*pinchRecognizer;
	
	BOOL						isClosing;
	BOOL						killRectExists;
	CGRect						killRect;
	
	float						animationTranslateX;
	float						animationTranslateY;
	
}

@property (nonatomic, retain) IBOutlet UIButton *buttonClose;
@property (nonatomic, retain) IBOutlet UIButton *buttonDownload;
@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) UIPinchGestureRecognizer *pinchRecognizer;

- (IBAction)click:(id)sender;

- (void)didPinch:(UIPinchGestureRecognizer *)recognizer;
- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context;

//Hey, Yo, Call this AFTER you set the image...
- (void)animateMe:(CGRect)targetRect;
- (void)loadImage:(NSString*)targetImagePath;

- (void)close;

@end
