//
//  GenericTouchController.m
//  Wrangler
//
//  Created by Nick Raptis on 10/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GenericTouchController.h"
#import "Root.h"

@implementation GenericTouchController

@synthesize recognizerPan;
@synthesize recognizerPinch;
@synthesize recognizerRotate;
@synthesize recognizerTap;

@synthesize isPanning;
@synthesize isPinching;
@synthesize isRotating;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    isPanning=false;
    isPinching=false;
    isRotating=false;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    return self;
}

- (void)dealloc
{
    NSLog(@"Dealloc: [/ %@]", [self class]);
    
    recognizerPan.delegate=nil;
    recognizerPinch.delegate=nil;
    recognizerRotate.delegate=nil;
    recognizerTap.delegate=nil;
    
    [self.view removeGestureRecognizer:recognizerPan];
    [self.view removeGestureRecognizer:recognizerPinch];
    [self.view removeGestureRecognizer:recognizerRotate];
    [self.view removeGestureRecognizer:recognizerTap];
    
    recognizerPan=nil;
    recognizerPinch=nil;
    recognizerRotate=nil;
    recognizerTap=nil;
}

- (void)didReceiveMemoryWarning
{
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    recognizerPan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(didPan:)];
    recognizerPinch = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(didPinch:)];
    recognizerRotate = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(didRotate:)];
    recognizerTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTap:)];
    recognizerTap.numberOfTapsRequired=2;
    
    recognizerPan.delegate=self;
    recognizerPinch.delegate=self;
    recognizerRotate.delegate=self;
    recognizerTap.delegate=self;
    
    [recognizerPan setCancelsTouchesInView:NO];
    [recognizerPinch setCancelsTouchesInView:NO];
    [recognizerRotate setCancelsTouchesInView:NO];
    [recognizerTap setCancelsTouchesInView:NO];
    
    [self.view addGestureRecognizer:recognizerPan];
    [self.view addGestureRecognizer:recognizerPinch];
    [self.view addGestureRecognizer:recognizerRotate];
    [self.view addGestureRecognizer:recognizerTap];
    
    [self.view setMultipleTouchEnabled:YES];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}


- (void)didPan:(UIPanGestureRecognizer *)recognizer
{
    CGPoint aTranslation = [recognizerPan translationInView:self.view];
    
    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        isPanning=YES;
        [self startPanWithX:aTranslation.x withY:aTranslation.y];
    }
    
    [self panWithX:aTranslation.x withY:aTranslation.y];
    
    if(recognizer.state == UIGestureRecognizerStateEnded)
    {
        [self finishPanWithX:aTranslation.x withY:aTranslation.y];
        
        CGPoint aVelocity = [recognizer velocityInView:self.view];
        [self finishPanWithX:aTranslation.x withY:aTranslation.y withVelX:aVelocity.x withVelY:aVelocity.y];
        
        isPanning=NO;
    }
}

- (void)didPinch:(UIPinchGestureRecognizer *)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        isPinching=YES;
        [self startScale:recognizer.scale];
    }
    
    [self scale:recognizer.scale];
    
    if(recognizer.state == UIGestureRecognizerStateEnded)
    {
        [self finishScale:recognizer.scale];
        isPinching=NO;
    }
}

- (void)didRotate:(UIRotationGestureRecognizer *)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        isRotating=YES;
        [self startRotate:recognizer.rotation];
    }
    
    [self rotate:recognizer.rotation];
    
    if(recognizer.state == UIGestureRecognizerStateEnded)
    {
        [self finishRotate:recognizer.rotation];
        isRotating=NO;
    }
}

- (void)didTap:(UITapGestureRecognizer *)recognizer
{
    
}

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
	UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    gApp->BaseTouch(location.x, location.y);
    
	for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
		if([aTouch phase] == UITouchPhaseBegan)
		{			
			CGPoint aLocation = [aTouch locationInView:self.view];
			gApp->BaseMultiTouch(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}		
	}
}


- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    gApp->BaseDrag(location.x, location.y);
	for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
        
		if([aTouch phase] == UITouchPhaseMoved)
		{
			CGPoint aLocation = [aTouch locationInView:self.view];			
			gApp->BaseMultiDrag(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}		
	}
}

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    gApp->BaseRelease(location.x, location.y);
	for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
		if([aTouch phase] == UITouchPhaseEnded || [aTouch phase]  == UITouchPhaseCancelled)
		{
			CGPoint aLocation = [aTouch locationInView:self.view];
			gApp->BaseMultiRelease(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}
	}
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
    return YES;
}

- (void)startPanWithX:(float)x withY:(float)y
{
    
}

- (void)panWithX:(float)x withY:(float)y
{
    
}

- (void)finishPanWithX:(float)x withY:(float)y
{
    
}

- (void)finishPanWithX:(float)x withY:(float)y withVelX:(float)velX withVelY:(float)velY
{
    
}

- (void)startScale:(float)scale
{
    
}

- (void)scale:(float)scale
{
    
}

- (void)finishScale:(float)scale
{
    
}

- (void)startRotate:(float)scale
{
    
}

- (void)rotate:(float)scale
{
    
}

- (void)finishRotate:(float)scale
{
    
}

@end







