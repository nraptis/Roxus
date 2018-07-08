//
//  EditorMenuPathCell.m
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import "EditorMenuPathCell.h"
#import "EditorMenuPath.h"

@implementation EditorMenuPathCell

@synthesize segmentStartZ;
@synthesize segmentEndZ;

@synthesize path;
@synthesize menu;

@synthesize buttonSelect;

- (id)initWithPath:(GamePath *)pPath
{
    path = pPath;
    
    self = [super initWithNibName:nil bundle:nil];
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    segmentStartZ.selectedSegmentIndex = path->mStartZ;
    segmentEndZ.selectedSegmentIndex = path->mEndZ;
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonSelect)
    {
        gEditor->mCurrentPath = path;
        [menu updateSelectedCell];
    }
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    if(path)
    {
        path->mStartZ = segmentStartZ.selectedSegmentIndex;
        path->mEndZ = segmentEndZ.selectedSegmentIndex;
    }
}

- (void)nuke
{
    self.segmentStartZ = nil;
    self.segmentEndZ = nil;
    
    self.path = nil;
    self.menu = nil;
    
    self.buttonSelect = nil;
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
