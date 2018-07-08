//
//  EditorMenuTiles.m
//  Mustache
//
//  Created by Nick Raptis on 6/21/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import "EditorMenuTiles.h"
#import "EditorGameArena.h"

@implementation EditorMenuTiles\

@synthesize segmentTileType;

@synthesize buttonTileCross;

@synthesize buttonTileH;
@synthesize buttonTileV;

@synthesize buttonTileT_U;
@synthesize buttonTileT_R;
@synthesize buttonTileT_D;
@synthesize buttonTileT_L;

@synthesize buttonTileCorner_UR;
@synthesize buttonTileCorner_BR;
@synthesize buttonTileCorner_BL;
@synthesize buttonTileCorner_UL;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    segmentTileType.selectedSegmentIndex = gEditor->mTileType;
    // Do any additional setup after loading the view from its nib.
}

- (IBAction)click:(UIButton*)sender
{
    
    bool aLeft = false;
    bool aRight = false;
    bool aTop = false;
    bool aBottom = false;
    
    //
    if(sender == buttonTileCross)
    {
        aLeft = true;
        aRight = true;
        aTop = true;
        aBottom = true;
    }
    
    if(sender == buttonTileH)
    {
        aLeft = true;
        aRight = true;
    }
    if(sender == buttonTileV)
    {
        aTop = true;
        aBottom = true;
    }
    
    if(sender == buttonTileT_U)
    {
        aLeft = true;
        aRight = true;
        aTop = true;
    }
    
    if(sender == buttonTileT_R)
    {
        aRight = true;
        aTop = true;
        aBottom = true;
    }

    if(sender == buttonTileT_D)
    {
        aLeft = true;
        aRight = true;
        aBottom = true;
    }
    if(sender == buttonTileT_L)
    {
        aLeft = true;
        aTop = true;
        aBottom = true;
    }
    
    if(sender == buttonTileCorner_UR)
    {
        aRight = true;
        aTop = true;
    }
    
    if(sender == buttonTileCorner_BR)
    {
        aRight = true;
        aBottom = true;
    }
    
    if(sender == buttonTileCorner_BL)
    {
        aLeft = true;
        aBottom = true;
    }
    
    if(sender == buttonTileCorner_UL)
    {
        aLeft = true;
        aTop = true;
    }
    
    gEditor->mTileDown = aBottom;
    gEditor->mTileUp = aTop;
    gEditor->mTileLeft = aLeft;
    gEditor->mTileRight = aRight;
    
    NSLog(@"U[%d] D[%d] R[%d] L[%d]", aTop, aBottom, aRight, aLeft);
    
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    gEditor->mTileType = segmentTileType.selectedSegmentIndex;
}

- (IBAction)slide:(UISlider*)sender
{
    
}

- (void)nuke
{
    self.segmentTileType = nil;
    
    self.buttonTileCross = nil;
    
    self.buttonTileH = nil;
    self.buttonTileV = nil;
    
    self.buttonTileT_U = nil;
    self.buttonTileT_R = nil;
    self.buttonTileT_D = nil;
    self.buttonTileT_L = nil;
    
    self.buttonTileCorner_UR = nil;
    self.buttonTileCorner_BR = nil;
    self.buttonTileCorner_BL = nil;
    self.buttonTileCorner_UL = nil;
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
