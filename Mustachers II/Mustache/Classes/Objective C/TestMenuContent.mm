//
//  TestMenuContent.m
//  GoldDigger
//
//  Created by Nick Raptis on 6/9/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#import "TestMenuContent.h"
#import "Root.h"
#import "Game.h"

@implementation TestMenuContent

@synthesize sliderPanX;
@synthesize sliderPanY;

@synthesize sliderZoom;

@synthesize sliderRotaion;

@synthesize labelPan;
@synthesize labelZoom;

@synthesize buttonResetPan;
@synthesize buttonResetZoom;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [gRoot addGlobalUpdate:self];
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonResetPan)
    {
        gGame->mCenterX = 0.0f;
        gGame->mCenterY = 0.0f;
    }
    if(sender == buttonResetZoom)
    {
        gGame->mZoomScale = 1.0f;
    }
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    
}

- (IBAction)slide:(UISlider*)sender
{
    gGame->mCenterX = sliderPanX.value;
    gGame->mCenterY = sliderPanY.value;
    
    gGame->mZoomScale = sliderZoom.value;
    
    gGame->mTestRotation = sliderRotaion.value;
    
}

- (void)globalUpdate
{
    sliderPanX.value = gGame->mCenterX;
    sliderPanY.value = gGame->mCenterY;
    
    sliderZoom.value = gGame->mZoomScale;
    
    sliderRotaion.value = gGame->mTestRotation;
    
    labelPan.text = [NSString stringWithFormat:@"Center(%.4f, %.3f)", gGame->mCenterX, gGame->mCenterY];
    labelZoom.text = [NSString stringWithFormat:@"Zoon %.3f%%", gGame->mZoomScale * 100.0f];
}

- (void)nuke
{
    [gRoot removeGlobalUpdate:self];
    
    self.sliderPanX = nil;
    self.sliderPanY = nil;
    
    self.sliderZoom = nil;
    
    self.sliderRotaion = nil;
    
    self.labelPan = nil;
    self.labelZoom = nil;
    
    self.buttonResetPan = nil;
    self.buttonResetZoom = nil;
}

- (void)dealloc
{
    
}

@end
