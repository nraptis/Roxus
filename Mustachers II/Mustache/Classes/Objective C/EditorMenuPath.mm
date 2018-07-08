//
//  EditorMenuPath.m
//  Mustache
//
//  Created by Nick Raptis on 6/22/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import "EditorMenuPath.h"
#import "EditorGameArena.h"
#import "EditorMenuPathCell.h"

@implementation EditorMenuPath

@synthesize buttonAdd;
@synthesize buttonRemove;

@synthesize segmentPoint;

@synthesize arrayCells;
@synthesize scrollViewCells;

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
    if(sender == buttonAdd)
    {
        gEditor->AddPath();
    }
    
    if(sender == buttonRemove)
    {
        gEditor->RemovePath(gEditor->mCurrentPath);
    }
    
    [self updateUI];
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    gEditor->mPathStartMode = segmentPoint.selectedSegmentIndex;
}

- (void)updateSelectedCell
{
    for(EditorMenuPathCell *aCell in arrayCells)
    {
        if(aCell.path == gEditor->mCurrentPath)
        {
            [aCell.view setBackgroundColor:[UIColor colorWithRed:0.25f green:0.25f blue:0.65f alpha:1.0f]];
        }
        else
        {
            [aCell.view setBackgroundColor:[UIColor colorWithRed:0.25f green:0.25f blue:0.25f alpha:1.0f]];
        }
    }
}

- (void)updateUI
{
    segmentPoint.selectedSegmentIndex = gEditor->mPathStartMode;
    
    for(EditorMenuPathCell *aCell in arrayCells)
    {
        [aCell nuke];
    }
    [arrayCells removeAllObjects];
    
    [scrollViewCells removeFromSuperview];
    self.scrollViewCells = nil;
    
    
    self.arrayCells = [[NSMutableArray alloc] init];
    
    
    float aTop = buttonAdd.frame.origin.y + buttonAdd.frame.size.height + 12.0f;
    
    self.scrollViewCells = [[UIScrollView alloc] initWithFrame:CGRectMake(0.0f, aTop, self.view.frame.size.width, self.view.frame.size.height - aTop)];
    [self.view addSubview:scrollViewCells];
    
    float aHeight = 4.0f;
    
    EnumList(GamePath, aPath, gEditor->mPathList)
    {
        EditorMenuPathCell *aCell = [[EditorMenuPathCell alloc] initWithPath:aPath];
        [arrayCells addObject:aCell];
        [scrollViewCells addSubview:aCell.view];
        
        aCell.view.frame = CGRectMake(0.0f, aHeight, aCell.view.frame.size.width, aCell.view.frame.size.height);
        aCell.menu = self;
        
        aHeight += (aCell.view.frame.size.height + 4);
    }
    
    scrollViewCells.contentSize = CGSizeMake(self.view.frame.size.width, aHeight);
    
    [self updateSelectedCell];
}

- (void)nuke
{
    for(EditorMenuPathCell *aCell in arrayCells)
    {
        [aCell nuke];
    }
    [arrayCells removeAllObjects];
    
    [scrollViewCells removeFromSuperview];
    self.scrollViewCells = nil;
    
    [self.view removeFromSuperview];
}

- (void)dealloc
{
    [self nuke];
}

@end
