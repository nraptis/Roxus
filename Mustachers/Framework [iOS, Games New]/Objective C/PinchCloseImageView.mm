    //
//  PinchCloseImageView.m
//  Fiat
//
//  Created by Nick Raptis on 6/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PinchCloseImageView.h"
#import "Root.h"

@implementation PinchCloseImageView

@synthesize buttonClose;
@synthesize buttonDownload;

@synthesize imageView;

@synthesize pinchRecognizer;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
	animationTranslateX=0;
	animationTranslateY=0;
	isClosing=false;
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	
	pinchRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(didPinch:)];
	[self.view addGestureRecognizer:pinchRecognizer];
}

- (void)loadImage:(NSString*)targetImagePath
{
	imageView.image=[UIImage imageNamed:targetImagePath];
}

- (void)didPinch:(UIPinchGestureRecognizer *)recognizer
{
	if(recognizer.scale <= 0.75f)
	{
		[self close];
	}
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	if(isClosing==false)
	{
		[self close];
	}
}

- (void)close
{

	if(isClosing==false)
	{
        self.pinchRecognizer.delegate = nil;
        self.pinchRecognizer = nil;
        
		CGAffineTransform aTransform = CGAffineTransformIdentity;//CGAffineTransformMakeScale(transformScale, transformScale);
		
		aTransform = CGAffineTransformTranslate(aTransform, animationTranslateX, animationTranslateY);
		aTransform = CGAffineTransformScale(aTransform,PINCH_CLOSE_START_SCALE,PINCH_CLOSE_START_SCALE);
		aTransform = CGAffineTransformRotate(aTransform, PINCH_CLOSE_START_ROTATION);
		
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDelegate:self];
		[UIView setAnimationDuration:0.563f];
		[UIView setAnimationDidStopSelector:@selector(animationDidStop:finished:context:)];
		
		
		
		[imageView setTransform:aTransform];
		[imageView setAlpha:0.0f];
		
		[UIView commitAnimations];
		isClosing=true;
	}
}

- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
{
	[gRoot killPopup];
}

- (void)animateMe:(CGRect)targetRect
{
	float aCenterX = targetRect.origin.x+targetRect.size.width/2;
	float aCenterY = targetRect.origin.y+targetRect.size.height/2;
	
	//Let's Figure out the difference vector between where we are and where we are goin...................
	
	animationTranslateX = aCenterX - (gAppWidth /2);
	animationTranslateY = aCenterY - (gAppHeight/2);
	
	CGAffineTransform aTransform = CGAffineTransformIdentity;//CGAffineTransformMakeScale(transformScale, transformScale);
	
	
	aTransform = CGAffineTransformTranslate(aTransform, animationTranslateX, animationTranslateY);
	aTransform = CGAffineTransformScale(aTransform,PINCH_CLOSE_START_SCALE,PINCH_CLOSE_START_SCALE);
	aTransform = CGAffineTransformRotate(aTransform, PINCH_CLOSE_START_ROTATION);
	
	
	self.imageView.transform = aTransform;
	imageView.alpha=0.0f;
	
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.563f];
	//[UIView setAnimationDidStopSelector:@selector(animationDidStop:finished:context:)];
	
	
	imageView.transform=CGAffineTransformIdentity;
	imageView.alpha=1.0f;
	
	[UIView commitAnimations];
	
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}

- (void)dealloc
{
    NSLog(@"PinchCloseImageView is deallocating.");
    
    self.pinchRecognizer.delegate = nil;
    self.buttonClose=nil;
	self.buttonDownload=nil;
	self.imageView=nil;
	self.pinchRecognizer=nil;
}


@end
