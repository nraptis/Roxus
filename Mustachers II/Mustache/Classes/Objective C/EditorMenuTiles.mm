//
//  EditorMenuTiles.m
//  Mustache
//
//  Created by Nick Raptis on 6/21/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import "EditorMenuTiles.h"
#import "EditorGameArena.h"

@implementation EditorMenuTiles

@synthesize segmentCurrentLayer;

@synthesize segmentShowTunnel;
@synthesize segmentShowFloor;
@synthesize segmentShowBridge;

@synthesize sliderOpacityTunnel;
@synthesize sliderOpacityFloor;
@synthesize sliderOpacityBridge;

@synthesize buttonTile;
@synthesize buttonBlocker;

@synthesize buttonRampU;
@synthesize buttonRampD;
@synthesize buttonRampL;
@synthesize buttonRampR;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    
    [super viewDidLoad];
    
    [self updateUI];
    
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonTile)gEditor->mTileType = TILE_TYPE_NORMAL;
    if(sender == buttonBlocker)gEditor->mTileType = TILE_TYPE_BLOCKED;
    
    if(sender == buttonRampU)gEditor->mTileType = TILE_TYPE_RAMP_U;
    if(sender == buttonRampD)gEditor->mTileType = TILE_TYPE_RAMP_D;
    if(sender == buttonRampL)gEditor->mTileType = TILE_TYPE_RAMP_L;
    if(sender == buttonRampR)gEditor->mTileType = TILE_TYPE_RAMP_R;
    
    
    [self updateUI];
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    if(sender == segmentCurrentLayer)
    {
        gEditor->mTileDepth = segmentCurrentLayer.selectedSegmentIndex;
        gEditor->mTileVisible[segmentCurrentLayer.selectedSegmentIndex] = true;
    }
    
    gEditor->mTileVisible[0] = segmentShowTunnel.selectedSegmentIndex;
    gEditor->mTileVisible[1] = segmentShowFloor.selectedSegmentIndex;
    gEditor->mTileVisible[2] = segmentShowBridge.selectedSegmentIndex;
    
    [self updateUI];
}

- (IBAction)slide:(UISlider*)sender
{
    gEditor->mTileOpacity[0] = sliderOpacityTunnel.value;
    gEditor->mTileOpacity[1] = sliderOpacityFloor.value;
    gEditor->mTileOpacity[2] = sliderOpacityBridge.value;
}

- (void)updateUI
{
    
    segmentCurrentLayer.selectedSegmentIndex = gEditor->mTileDepth;
    segmentShowTunnel.selectedSegmentIndex = gEditor->mTileVisible[0];
    segmentShowFloor.selectedSegmentIndex = gEditor->mTileVisible[1];
    segmentShowBridge.selectedSegmentIndex = gEditor->mTileVisible[2];
    
    
    
    sliderOpacityTunnel.value = gEditor->mTileOpacity[0];
    sliderOpacityFloor.value = gEditor->mTileOpacity[1];
    sliderOpacityBridge.value = gEditor->mTileOpacity[2];
    
    if(gEditor->mTileDepth == 0)
    {
        buttonRampU.hidden = YES;
        buttonRampD.hidden = YES;
        buttonRampL.hidden = YES;
        buttonRampR.hidden = YES;
    }
    else
    {
        buttonRampU.hidden = NO;
        buttonRampD.hidden = NO;
        buttonRampL.hidden = NO;
        buttonRampR.hidden = NO;
    }
}

- (void)nuke
{
    self.segmentCurrentLayer = nil;
    
    self.segmentShowTunnel = nil;
    self.segmentShowFloor = nil;
    self.segmentShowBridge = nil;
    
    self.sliderOpacityTunnel = nil;
    self.sliderOpacityFloor = nil;
    self.sliderOpacityBridge = nil;
    
    self.buttonTile = nil;
    self.buttonBlocker = nil;
    
    self.buttonRampU = nil;
    self.buttonRampD = nil;
    self.buttonRampL = nil;
    self.buttonRampR = nil;
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
