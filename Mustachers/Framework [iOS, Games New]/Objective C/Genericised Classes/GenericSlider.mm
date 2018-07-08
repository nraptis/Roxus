//
//  GenericSlider.m
//  JiggleARC
//
//  Created by Nick Raptis on 1/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GenericSlider.h"

@implementation GenericSlider

@synthesize delegateSlider;
@synthesize imageViewThumb;

@synthesize imageViewBackground;

@synthesize viewBounds;

@synthesize isVertical;

@synthesize percent;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    selectedImage = nil;
    
    percent = 0.0f;
    
    selectedImageStartX = 0.0f;
    selectedImageStartY = 0.0f;
    
    touchStartX = 0.0f;
    touchStartY = 0.0f;
    
    internalPercent = 0;
    
    isDragging = NO;
    isVertical = NO;
    
    self.view.multipleTouchEnabled = NO;
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
    NSLog(@"Dealloc[%@]", [self class]);
    [self nuke];
}

- (void)nuke
{
    self.delegateSlider=nil;
    self.imageViewThumb=nil;
    self.viewBounds=nil;
    self.imageViewBackground=nil;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    viewBounds.backgroundColor = [UIColor clearColor];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	return YES;
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* touch = [touches anyObject];
    
    UIView *aBounds = viewBounds;
    if(aBounds == 0)aBounds = self.view;
    
	CGPoint location = [touch locationInView:aBounds];
    
	float aTouchX = location.x + aBounds.frame.origin.x;
	float aTouchY = location.y + aBounds.frame.origin.y;
    
    [self touchImage:imageViewThumb withX:aTouchX withY:aTouchY];
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(selectedImage)
    {
        UITouch* touch = [touches anyObject];
        
        UIView *aBounds = aBounds;
        if(aBounds == 0)aBounds = self.view;
        
        CGPoint location = [touch locationInView:aBounds];
        
        float aTouchX = location.x;// + aBounds.frame.origin.x;
        float aTouchY = location.y;// + aBounds.frame.origin.y;
        
        float aDiffX = (aTouchX - touchStartX);
        float aDiffY = (aTouchY - touchStartY);
        
        if(isVertical)
        {
            selectedImage.frame = CGRectMake(selectedImage.frame.origin.x, selectedImageStartY + aDiffY, selectedImage.frame.size.width, selectedImage.frame.size.height);
        }
        else
        {
            selectedImage.frame = CGRectMake(selectedImageStartX + aDiffX, selectedImage.frame.origin.y, selectedImage.frame.size.width, selectedImage.frame.size.height);
        }
        
        [self correctOverlap];
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    selectedImage=nil;
    
    selectedImageStartX=0.0f;
    selectedImageStartY=0.0f;
    
    touchStartX=0.0f;
    touchStartY=0.0f;
}

- (void)touchImage:(UIImageView *)targetImageView withX:(float)targetX withY:(float)targetY;
{
    if(!targetImageView)
    {
        selectedImage = nil;
        
        selectedImageStartX = 0.0f;
        selectedImageStartY = 0.0f;
        
        touchStartX = 0.0f;
        touchStartY = 0.0f;
        
        return;
    }
    
    float aLeft=targetImageView.frame.origin.x + viewBounds.frame.origin.x;
    float aTop=targetImageView.frame.origin.y + viewBounds.frame.origin.y;
    
    float aRight=aLeft+targetImageView.frame.size.width;
    float aBottom=aTop+targetImageView.frame.size.height;
    
    if(isVertical)
    {
        if((targetY >= aTop) && (targetY <= aBottom))// && (targetY >= aTop) && (targetY <= aBottom))
        {
            selectedImage = targetImageView;
            selectedImageStartY = aTop - viewBounds.frame.origin.y;
            touchStartY=targetY;
        }
    }
    else
    {
        if((targetX >= aLeft) && (targetX <= aRight))// && (targetY >= aTop) && (targetY <= aBottom))
        {
            selectedImage = targetImageView;
            selectedImageStartX = aLeft - viewBounds.frame.origin.x;
            touchStartX=targetX;
        }
    }
    
    
    
    //if(
    
    
}

- (void)correctOverlap
{
    
    UIView *aBounds = viewBounds;
    if(aBounds == 0)aBounds = self.view;
    
    float aPercent=0.0f;
    
    float aThumbWidth=imageViewThumb.frame.size.width;
    float aThumbHeight=imageViewThumb.frame.size.height;
    
    
    float aLeft = 0;
    float aRight = (aBounds.frame.size.width - aThumbWidth);
    
    
    float aTop = 0;
    float aBottom = (aBounds.frame.size.height - aThumbHeight);
    
    float aThumbX = imageViewThumb.frame.origin.x;
    float aThumbY = imageViewThumb.frame.origin.y;
    
    if(isVertical)
    {
        if(aThumbY > aBottom)aThumbY = aBottom;
        if(aThumbY < 0)aThumbY=0;
        imageViewThumb.frame = CGRectMake(aThumbX,aThumbY,aThumbWidth,aThumbHeight);
        float aRange = (aBottom - aTop);
        if(aRange > 0)
        {
            aPercent = (aThumbY) / aRange;
        }
    }
    else
    {
        if(aThumbX > aRight)aThumbX = aRight;
        if(aThumbX < 0)aThumbX=0;
        imageViewThumb.frame = CGRectMake(aThumbX,aThumbY,aThumbWidth,aThumbHeight);
        float aRange = (aRight - aLeft);
        if(aRange > 0)
        {
            aPercent = (aThumbX) / aRange;
        }
    }
    
    
    
    if(aPercent < 0)aPercent=0.0f;
    if(aPercent > 1)aPercent=1.0f;
    
    [self setPercent:aPercent];
    
    //percent = aPercent;
    
    [delegateSlider didSlide:aPercent withSlider:self];
}

//- (void)setPercent:(float)targetPercent
- (void)setPercent:(float)targetPercent withNotification:(BOOL)targetNotify
{
    internalPercent=targetPercent;
    
    percent=internalPercent;
    if(percent < 0)percent=0.0f;
    if(percent > 1)percent=1.0f;
    
    internalPercent = percent;
    
    [self performSelectorOnMainThread:@selector(internalUpdate:) withObject:self waitUntilDone:YES];
    
    if(targetNotify)
    {
        [delegateSlider didSlide:internalPercent withSlider:self];
    }
    
    /*
    
    float aThumbWidth=imageViewThumb.frame.size.width;
    float aThumbHeight=imageViewThumb.frame.size.height;
    
    float aLeft = 0;
    float aRight = (aBounds.frame.size.width - aThumbWidth);
    
    float aThumbX = imageViewThumb.frame.origin.x;
    float aThumbY = imageViewThumb.frame.origin.y;
    
     
    
    float aPercent=0.0f;
    
    float aRange = (aRight - aLeft);
    
    if(aRange > 0)
    {
        [imageViewThumb performSelectorInBackground:@selector(setFrame:) withObject:CGRectMake(aLeft + aRange * targetPercent,aThumbY,aThumbWidth,aThumbHeight)];
        //imageViewThumb.frame = ;
    }
    
    */
}

- (void)internalUpdate:(id)sender
{
    UIView *aBounds = viewBounds;
    if(aBounds == 0)aBounds = self.view;
    
    float aThumbWidth=imageViewThumb.frame.size.width;
    float aThumbHeight=imageViewThumb.frame.size.height;
    
    float aLeft = 0;
    float aRight = (aBounds.frame.size.width - aThumbWidth);
    
    float aThumbX = imageViewThumb.frame.origin.x;
    float aThumbY = imageViewThumb.frame.origin.y;
    
    float aPercent=internalPercent;
    if(aPercent < 0.0f)aPercent=0.0f;
    if(aPercent > 1.0f)aPercent=1.0f;
    
    float aRange = (aRight - aLeft);
    
    if(aRange > 0)
    {
        imageViewThumb.frame = CGRectMake(aLeft + aRange * aPercent,aThumbY,aThumbWidth,aThumbHeight);
    }
    
}

@end
