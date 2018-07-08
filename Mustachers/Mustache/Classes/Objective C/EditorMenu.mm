//
//  EditorMenu.m
//  Mustache
//
//  Created by Nick Raptis on 6/21/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import "EditorGameArena.h"


#import "EditorMenu.h"
#import "EditorMenuTiles.h"
#import "EditorMenuPath.h"

#import "Root.h"



@implementation EditorMenu

@synthesize buttonHome;
@synthesize buttonCollapse;

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
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self pushTo:[[EditorMenuTiles alloc] initWithNibName:nil bundle:nil]];
    
    [self collapseAnimated:NO];
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
        if((aX + aWidth) > gAppWidth)
        {
            aX = (gAppWidth - aWidth);
        }
        
        if(aY < 0)aY=0;
        if((aY + aHeight) > gAppHeight)
        {
            aY = (gAppHeight - aHeight);
        }
        
        self.view.frame = CGRectMake(aX,aY,aWidth,aHeight);
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
        
        gEditor->Save();
        gEditor->Load();
        
        
        if(isCollapsed)[self expandAnimated:YES];
        
        else [self collapseAnimated:YES];
        
        return;
    }
    
    if(sender == buttonMenu1)
    {
        gEditor->mEditorMode = EDITOR_MODE_PATH;
        [self pushTo:[[EditorMenuPath alloc] initWithNibName:nil bundle:nil]];
    }
    if(sender == buttonMenu2)
    {
        gEditor->mEditorMode = EDITOR_MODE_TILES;
        [self pushTo:[[EditorMenuTiles alloc] initWithNibName:nil bundle:nil]];
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
    self.viewToolBar=nil;
    
    self.buttonHome=nil;
    self.buttonCollapse=nil;
    
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

