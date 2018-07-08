//
//  ImagePopover.h
//  JeepWranglerPhone
//
//  Created by Nick Raptis on 7/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ImagePopover : UIViewController
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

- (IBAction)click:(UIButton*)sender;

- (void)didPinch:(UIPinchGestureRecognizer *)recognizer;
- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context;

//- (void)

//Hey, Yo, Call this AFTER you set the image...
- (void)animateMe:(CGRect)targetRect;
- (void)loadImage:(NSString*)targetImagePath;

- (void)close;

@end
