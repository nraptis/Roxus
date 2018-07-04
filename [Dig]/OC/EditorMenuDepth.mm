//
//  EditorMenuDepth.m
//  BoneDig
//
//  Created by Nick Raptis on 11/26/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#import "EditorBoard.h"
#import "EditorMenuDepth.h"

@implementation EditorMenuDepth

@synthesize segmentStarDepth;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (IBAction)click:(UIButton*)sender
{
    
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    if(!gEditor)return;
    
    if(sender == segmentStarDepth)
    {
        
        int aStarIndex = segmentStarDepth.selectedSegmentIndex;
        
        gEditor->mEditorStarDepthIndex = aStarIndex;
        
        
    }
}

- (IBAction)slide:(UISlider*)sender
{
    
}

- (void)nuke
{
    self.segmentStarDepth = nil;
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
