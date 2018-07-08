//
//  EditorMenuPath.m
//  Mustache
//
//  Created by Nick Raptis on 6/22/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import "EditorMenuPath.h"
#import "EditorGameArena.h"

@implementation EditorMenuPath

@synthesize segmentPathMode;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    if(gEditor->mPathStartMode)segmentPathMode.selectedSegmentIndex = 0;
    else segmentPathMode.selectedSegmentIndex = 1;
}

- (IBAction)click:(UIButton*)sender
{
    
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    if(sender == segmentPathMode)
    {
        gEditor->mPathStartMode = !(segmentPathMode.selectedSegmentIndex);
    }
}

- (IBAction)slide:(UISlider*)sender
{
    
}

- (void)nuke
{
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
