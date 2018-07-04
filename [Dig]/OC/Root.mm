//
//  Root.m
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import "Root.h"
#import "MainApp.h"
#import "core_includes.h"


Root *gRoot = nil;

@implementation Root


#ifdef ANIMATION_MODE
@synthesize buildMenu;
#endif


#ifdef EDITOR_MODE
@synthesize editorMenu;
#endif


//@synthesize caBuilder;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    gRoot = self;
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    gRoot = self;
    
    
    
    return self;
}

- (void)viewDidLoad
{
    
    [super viewDidLoad];
    
    //[self pushTo:glViewController animated:NO];
    
}

- (void)go
{
    gRoot = self;
    
    
    gApp = new MainApp();
    
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, gAppWidth, gAppHeight);
    
    
    
    
    if(glViewController == nil)
    {
        self.glViewController = [[GLViewController alloc] initWithNibName:nil bundle:nil];
        [glViewController load];
    }
    
    
    
    
}

- (void)begin
{
    [self startGlobalUpdate];
    self.ignoreAnimations = YES;
    [self pushTo:glViewController];
    self.ignoreAnimations = NO;
    
    
#ifdef EDITOR_MODE
    self.editorMenu = [[EditorMenu alloc] initWithNibName:nil bundle:nil];
    [self.view addSubview:editorMenu.view];
    editorMenu.view.frame = CGRectMake(gDeviceWidth - (editorMenu.view.frame.size.width + 20), gDeviceHeight - (editorMenu.view.frame.size.height + 20), editorMenu.view.frame.size.width, editorMenu.view.frame.size.height);
#endif
    
    
#ifdef ANIMATION_MODE
    
    self.buildMenu = [[SABuildMenu alloc] initWithNibName:nil bundle:nil];
    [self.view addSubview:buildMenu.view];
    
#endif
    
    //self.caBuilder = [[CABuilderMenu alloc] initWithNibName:nil bundle:nil];
    //[self.view addSubview:caBuilder.view];
    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown);
}

- (void)didReceiveMemoryWarning
{
    
}

@end
