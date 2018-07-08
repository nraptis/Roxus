//
//  RootViewController.h
//  Gnome
//
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define VIEWHAX(v) (v).frame=CGRectMake((v).frame.origin.x,(v).frame.origin.y,(v).frame.size.width,(v).frame.size.height)
#define VCHAX(v) (v).view.frame=CGRectMake((v).view.frame.origin.x,(v).view.frame.origin.y,(v).view.frame.size.width,(v).view.frame.size.height)

#import <UIKit/UIKit.h>

#import "RootBase.h"
#import <OpenGLES/ES2/glext.h>
#import <AVFoundation/AVFoundation.h>
#import "GLApp.h"
#import "Game.h"
#import "GLViewController.h"
#import "TestMenu.h"
#import "EditorMenu.h"

@interface Root : RootBase
{
    TestMenu                                    *testMenu;
    EditorMenu                                  *editorMenu;
}

@property (nonatomic, retain) TestMenu *testMenu;
@property (nonatomic, retain) EditorMenu *editorMenu;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;

- (void)enterBackground;
- (void)enterForeground;

- (void)cropImage:(NSString *)targetImageName withImageView:(UIImageView*)targetImageView;
- (void)go;

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)purchaseSuccessful:(NSString*)targetString;
- (void)globalUpdate;

@end

extern Root *gRoot;


