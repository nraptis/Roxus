//
//  PopoverContainer.m
//  Wrangler
//
//  Created by Nick Raptis on 8/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PopoverContainer.h"
#import "ImageViewController.h"
#import "Root.h"

@implementation PopoverContainer

@synthesize buttonClose;
@synthesize imageViewPopoverBack;
@synthesize currentViewController;
@synthesize pinchRecognizer;
@synthesize imageViewGestureIcon;
@synthesize disablePinchClose;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    disablePinchClose=NO;
    animationTranslateX=0;
	animationTranslateY=0;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
	
	isClosing=false;
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)setTarget:(UIViewController*)targetViewController
{
    currentViewController = targetViewController;
    [self.view addSubview:currentViewController.view];
    
    pinchRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(didPinch:)];
	[self.view addGestureRecognizer:pinchRecognizer];
    
    [self.view bringSubviewToFront:buttonClose];
    
    [self languageUpdate];
}

- (void)loadImage:(NSString*)targetImagePath
{
    ImageViewController *aView = [[ImageViewController alloc] initWithNibName:nil bundle:nil];
    [aView loadImage:targetImagePath];
    [self setTarget:aView];
}

- (void)didPinch:(UIPinchGestureRecognizer *)recognizer
{
    if(disablePinchClose == NO)
    {
        if(recognizer.scale <= 0.90f)
        {
            [self close];
        }
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    /*
	if(isClosing==false)
	{
		[self close];
	}
    */
    
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonClose)
    {
        [self close];
    }
}

- (void)loadImageGesture:(NSString*)targetImagePath
{
    UIImage *aImage = [gRoot loadImage:targetImagePath];
    if(aImage)
    {
        if(aImage.size.width > 0)
        {
            self.imageViewGestureIcon = [[UIImageView alloc] initWithImage:aImage];
            [self.view addSubview:imageViewGestureIcon];
        }
    }
}

- (void)loadImageBackground:(NSString*)targetImagePath
{
    UIImage *aImage = [gRoot loadImage:targetImagePath];
    if(aImage)
    {
        if(aImage.size.width > 0)
        {
            self.imageViewPopoverBack = [[UIImageView alloc] initWithImage:aImage];
            [self.view addSubview:imageViewPopoverBack];
        }
    }
}


- (void)sweepAway:(BOOL)targetLeft
{
    if(isClosing==false)
	{
        self.pinchRecognizer.delegate = nil;
        self.pinchRecognizer = nil;
        
		CGAffineTransform aTransform = CGAffineTransformIdentity;
		
        if(targetLeft)
        {
            aTransform = CGAffineTransformTranslate(aTransform, -1024.0f, 0.0f);
        }
        else
        {
            aTransform = CGAffineTransformTranslate(aTransform, 1024.0f, 0.0f);
        }
		
        //aTransform = CGAffineTransformScale(aTransform,0.01f,0.01f);
        
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:0.563f];
        
        [UIView setAnimationDelegate:self];
		[UIView setAnimationDidStopSelector:@selector(animationDidStop:finished:context:)];
        
        [self.view setTransform:aTransform];
        
        
        /*
		[currentViewController.view setTransform:aTransform];
		[currentViewController.view setAlpha:0.0f];
        
        imageViewPopoverBack.alpha=0.0f;
        buttonClose.alpha = 0.0f;
        */
        
		[UIView commitAnimations];
        
		isClosing=true;
	}
}

- (void)close
{
	if(isClosing==false)
	{
        self.pinchRecognizer.delegate = nil;
        self.pinchRecognizer = nil;
        
		CGAffineTransform aTransform = CGAffineTransformIdentity;
		
		aTransform = CGAffineTransformTranslate(aTransform, animationTranslateX, animationTranslateY);
		aTransform = CGAffineTransformScale(aTransform,0.01f,0.01f);
        
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:0.563f];
        
        [UIView setAnimationDelegate:self];
		[UIView setAnimationDidStopSelector:@selector(animationDidStop:finished:context:)];
        
		[currentViewController.view setTransform:aTransform];
		[currentViewController.view setAlpha:0.0f];
        
        imageViewPopoverBack.alpha=0.0f;
        
        float aGestureWidth = imageViewGestureIcon.frame.size.width;
        float aGestureHeight = imageViewGestureIcon.frame.size.height;
        
        imageViewGestureIcon.frame = CGRectMake(gAppWidth + 100, imageViewGestureIcon.frame.origin.y, aGestureWidth, aGestureHeight);
        
        [self.view setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:0.0f]];
        imageViewGestureIcon.alpha = 0.0f;
        
        buttonClose.alpha = 0.0f;
        
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
    
    [self.view bringSubviewToFront:imageViewGestureIcon];
    
    [self.view bringSubviewToFront:currentViewController.view];
    
    [self.view bringSubviewToFront:buttonClose];
    
	float centerX = targetRect.origin.x+targetRect.size.width/2;
	float centerY = targetRect.origin.y+targetRect.size.height/2;
    
    float aViewWidth = currentViewController.view.frame.size.width;
    float aViewHeight = currentViewController.view.frame.size.height;
    
    float aGestureWidth = imageViewGestureIcon.frame.size.width;
    float aGestureHeight = imageViewGestureIcon.frame.size.height;
    
    currentViewController.view.frame = CGRectMake(gAppWidth2 - currentViewController.view.frame.size.width / 2.0f,
                                                  gAppHeight2 - currentViewController.view.frame.size.height / 2.0f,
                                                  currentViewController.view.frame.size.width,
                                                  currentViewController.view.frame.size.height);
    
	animationTranslateX = centerX - (gAppWidth/2);
	animationTranslateY = centerY - (gAppHeight/2);
    
    CGRect aCloseFrame = buttonClose.frame;
    
    buttonClose.alpha = 0.0f;
    imageViewPopoverBack.alpha=0.0f;
    
	CGAffineTransform aTransform = CGAffineTransformIdentity;
    
	aTransform = CGAffineTransformTranslate(aTransform, animationTranslateX, animationTranslateY);
	aTransform = CGAffineTransformScale(aTransform,0.01f,0.01f);
    
	currentViewController.view.transform = aTransform;
	currentViewController.view.alpha=0.0f;
    
    float aRightCenter = gAppWidth2 + (aViewWidth / 2.0f);
    float aRightDiff = gAppWidth - aRightCenter;
    
    //aRightCenter = aRightCenter + aRightDiff - (imageViewGestureIcon.frame.size.width / 2.0f);
    //float aVerticalCenter = currentViewController.view.frame.origin.y + (currentViewController.view.frame.size.width / 2.0f);
    
    imageViewGestureIcon.frame = CGRectMake(gAppWidth + 100, gAppHeight2 - (aGestureHeight / 2.0f), aGestureWidth, aGestureHeight);
    
    imageViewGestureIcon.alpha = 0.0f;
    
    [self.view setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:0.0f]];
    
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.563f];
    
    imageViewPopoverBack.alpha=1.0f;
    
	currentViewController.view.transform=CGAffineTransformIdentity;
    currentViewController.view.alpha=1.0f;
    
    if(imageViewGestureIcon)
    {
        imageViewGestureIcon.frame = CGRectMake(aRightCenter + 8.0f, gAppHeight2 - (aGestureHeight / 2.0f), aGestureWidth, aGestureHeight);
        imageViewGestureIcon.alpha = 1.0f;
    }
    
    buttonClose.frame = aCloseFrame;
    buttonClose.alpha = 1.0f;
    
    [self.view setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:0.75f]];
	
	[UIView commitAnimations];
    
}

- (void)languageUpdate
{
    if(currentViewController)
    {
        if([currentViewController respondsToSelector:@selector(languageUpdate)])
        {
            [currentViewController performSelector:@selector(languageUpdate)];
        }
    }
    
    //[super languageUpdate];
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}




- (void)dealloc
{
    NSLog(@"[/Deallocate - %@]", [self class]);
    
    if(self.currentViewController)
    {
        NSLog(@"Popover Item: [%@]", [currentViewController class]);
    }
    
    self.pinchRecognizer.delegate=nil;
    self.pinchRecognizer=nil;
    
    [self.currentViewController.view removeFromSuperview];
    self.currentViewController = nil;
    
    self.buttonClose = nil;
    self.imageViewPopoverBack = nil;
    
    self.imageViewGestureIcon = nil;
    
    [self.view removeFromSuperview];
}


@end

