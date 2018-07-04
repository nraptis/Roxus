//
//  EditorMenu.m
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import "EditorMenu.h"
#import "Root.h"

@implementation EditorMenu

@synthesize buttonHome;
@synthesize buttonCollapse;

@synthesize buttonTopAdd1;
@synthesize buttonTopSub1;

@synthesize buttonBottomAdd1;
@synthesize buttonBottomSub1;

@synthesize buttonTopBotAddTest;

@synthesize buttonSaveImage;

@synthesize buttonMenu1;
@synthesize buttonMenu2;
@synthesize buttonMenu3;
@synthesize buttonMenu4;
@synthesize buttonMenu5;

@synthesize viewToolBar;

@synthesize currentMenu;
@synthesize previousMenu;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    isDragging=NO;
    isCollapsed=NO;
    
    touchStartX=0.0f;
    touchStartY=0.0f;
    
    touchViewX=0.0f;
    touchViewY=0.0f;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self pushTo:[[EditorMenuMain alloc] initWithNibName:nil bundle:nil]];
    
    [self expandAnimated:NO];
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
    isDragging=NO;
    
    UITouch* touch = [touches anyObject];
    
    CGPoint location = [touch locationInView:gRoot.view];
    float aTouchX = location.x;
    float aTouchY = location.y;
    
    
    
    isDragging=YES;
    
    touchViewX=self.view.frame.origin.x;
    touchViewY=self.view.frame.origin.y;
    
    touchStartX=aTouchX;
    touchStartY=aTouchY;
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(isDragging)
    {
        UITouch* touch = [touches anyObject];
        CGPoint location = [touch locationInView:gRoot.view];
        
        float aTouchX = location.x;
        float aTouchY = location.y;
        
        float aWidth=self.view.frame.size.width;
        float aHeight=self.view.frame.size.height;
        
        float aX = touchViewX + (aTouchX - touchStartX);
        float aY = touchViewY + (aTouchY - touchStartY);
        
        if(aX < 0)aX=0;
        if((aX + aWidth) > gDeviceWidth)
        {
            aX = (gDeviceWidth - aWidth);
        }
        
        if(aY < 0)aY=0;
        if((aY + aHeight) > gDeviceHeight)
        {
            aY = (gDeviceHeight - aHeight);
        }
        
        self.view.frame = CGRectMake(aX, aY, aWidth, aHeight);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    isDragging=NO;
}

- (void)pushTo:(UIViewController*)targetViewController
{
    if([currentMenu respondsToSelector:@selector(nuke)])
    {
        [currentMenu performSelector:@selector(nuke)];
    }
    [currentMenu.view removeFromSuperview];
    self.currentMenu=nil;
    
    self.currentMenu = targetViewController;
    [self.view addSubview:currentMenu.view];
    
    [self collapseAnimated:YES];
    [self expandAnimated:YES];
}

- (void)collapseAnimated:(BOOL)targetAnimated
{
    float aWidth = self.view.frame.size.width;
    float aHeight = self.currentMenu.view.frame.size.height;
    
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, aWidth, GTM_TOOL_HEIGHT);
    
    currentMenu.view.frame = CGRectMake(GTM_TOOL_HEIGHT, 0, aWidth, aHeight);
    
    currentMenu.view.hidden = YES;
    
    isCollapsed = YES;
    
    viewToolBar.frame = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, GTM_TOOL_HEIGHT);
}

- (void)expandAnimated:(BOOL)targetAnimated
{
    float aWidth = self.view.frame.size.width;
    float aHeight = self.currentMenu.view.frame.size.height;
    
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, aWidth, GTM_TOOL_HEIGHT + aHeight);
    
    currentMenu.view.frame = CGRectMake(0, GTM_TOOL_HEIGHT, aWidth, aHeight);
    
    currentMenu.view.alpha = 1.0f;
    
    currentMenu.view.hidden = NO;
    
    isCollapsed = NO;
    
    viewToolBar.frame = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, GTM_TOOL_HEIGHT);
}

- (IBAction)click:(UIButton*)sender
{
    
    if(sender == buttonCollapse)
    {
        if(isCollapsed)[self expandAnimated:YES];
        else [self collapseAnimated:YES];
        
        return;
    }
    
    if(sender == buttonMenu1)
    {
        gEditor->mMode = ED_M_PAN;
        EditorMenuMain *aMenu = [[EditorMenuMain alloc] initWithNibName:nil bundle:nil];
        [self pushTo:aMenu];
    }
    
    if(sender == buttonMenu2)
    {
        gEditor->mMode = ED_M_TILES;
        EditorMenuTiles *aMenu = [[EditorMenuTiles alloc] initWithNibName:nil bundle:nil];
        [self pushTo:aMenu];
    }
    
    if(sender == buttonTopAdd1)
    {
        gEditor->PadGrid(1, 0);
    }
    
    if(sender == buttonTopSub1)
    {
        gEditor->PadGrid(-1, 0);
    }
    
    if(sender == buttonBottomAdd1)
    {
        gEditor->PadGrid(0, 1);
    }
    
    if(sender == buttonBottomSub1)
    {
        gEditor->PadGrid(0, -1);
    }
    
    if(sender == buttonTopBotAddTest)
    {
        gEditor->PadGrid(2, 2);
    }
    
    
    [self expandAnimated:YES];
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    
}

- (IBAction)slide:(UISlider*)sender
{
    
}

- (void)nuke
{
    self.viewToolBar = nil;
    
    self.buttonTopAdd1 = nil;
    self.buttonTopSub1 = nil;
    
    self.buttonBottomAdd1 = nil;
    self.buttonBottomSub1 = nil;
    
    self.buttonTopBotAddTest = nil;
    
    
    self.buttonHome=nil;
    self.buttonCollapse=nil;
    self.buttonSaveImage=nil;
    
    self.buttonMenu1=nil;
    self.buttonMenu2=nil;
    self.buttonMenu3=nil;
    self.buttonMenu4=nil;
    self.buttonMenu5=nil;
    
    if([currentMenu respondsToSelector:@selector(nuke)])
    {
        [currentMenu performSelector:@selector(nuke)];
    }
    
    [currentMenu.view removeFromSuperview];
    
    self.currentMenu=nil;
    
    if([previousMenu respondsToSelector:@selector(nuke)])
    {
        [previousMenu performSelector:@selector(nuke)];
    }
    
    [previousMenu.view removeFromSuperview];
    self.previousMenu=nil;
}

- (void)dealloc
{
    [self nuke];
}

@end


