//
//  EditorMenuMain.m
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import "EditorMenuMain.h"
#import "EditorBoard.h"
#import "Root.h"

@implementation EditorMenuMain

@synthesize buttonFill;
@synthesize buttonClear;
@synthesize buttonTrim;

@synthesize textFieldStarDepth1;
@synthesize textFieldStarSpacing;

@synthesize buttonGenerateStars;

@synthesize buttonSave;
@synthesize buttonLoad;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonClear)
    {
        gEditor->EditorClearToDirt();
    }
    
    if(sender == buttonTrim)
    {
        
    }
    
    if(sender == buttonFill)
    {
        gEditor->EditorFillWithDirt();
    }
    
    
    if(sender == buttonGenerateStars)
    {
        int aStarDepth = FString([textFieldStarDepth1.text UTF8String]).ToInt();
        int aStarSpacing = FString([textFieldStarSpacing.text UTF8String]).ToInt();
        
        NSLog(@"Star Depth [%d] StarSpacing = [%d]", aStarDepth, aStarSpacing);
        
        gEditor->GenerateLevel(aStarDepth, aStarSpacing);
    }
    
    
    
    
    if(sender == buttonSave)
    {
        gEditor->Save("editor_level.xml");
    }
    if(sender == buttonLoad)
    {
        gEditor->Load("editor_level.xml");
    }
    
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    
}

- (IBAction)slide:(UISlider*)sender
{
    
}

- (void)nuke
{
    self.textFieldStarDepth1 = nil;
    self.textFieldStarSpacing = nil;
    
    self.buttonGenerateStars = nil;
    
    self.buttonClear = nil;
    self.buttonTrim = nil;
    
    self.buttonSave = nil;
    self.buttonLoad = nil;
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
