//  RootViewController.m
//  Gnome
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

#import <QuartzCore/QuartzCore.h>

#import "Root.h"

#import "GLView.h"
#import "AppDelegate.h"

Root *gRoot;

@implementation Root

@synthesize testMenu;
@synthesize editorMenu;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    gRoot = self;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    gRoot = self;
    
    return self;
}

- (void)cropImage:(NSString *)targetImageName withImageView:(UIImageView*)targetImageView
{
    
    //NSArray *arrayNames = [NSArray arrayWithObjects:@"Bill", @"Sandra", @"Jim", "Sarah", @"Rex", nil];
    //"Bill, Sandra, Jim, Sarah, Rex"
    
}

- (void)go
{
    [self pushTo:gGLViewController];

    [gGLViewController startAnimation];
    
    //GameCenterConnect();
    
    if(gAppWidth > 640.0f || true)
    {
        self.testMenu = [[TestMenu alloc] initWithNibName:nil bundle:nil];
        [self.view addSubview:testMenu.view];
        [testMenu collapseAnimated:NO];
        
        if(gEditor)
        {
            self.editorMenu = [[EditorMenu alloc] initWithNibName:nil bundle:nil];
            
            [self.view addSubview:editorMenu.view];
            
            editorMenu.view.frame = CGRectMake(gAppWidth - editorMenu.view.frame.size.width, 0.0f, editorMenu.view.frame.size.width, editorMenu.view.frame.size.height);
        }
    }
    
    [self startGlobalUpdate];
    
}

- (void)purchaseSuccessful:(NSString*)targetString
{
    GAPP->mPurchased=true;
    GAPP->SaveStatic();
    
    [self killAllAds];
}

- (void)globalUpdate
{
    [super globalUpdate];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if(interfaceOrientation == UIInterfaceOrientationPortrait)
	{
		gRoot.currentOrientation = interfaceOrientation;
		return YES;
	}
	return NO;
}


@end
