//
//  AppDelegate.h
//
//  Gnome
//
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Include.h"

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import <GameKit/GameKit.h>
#import <AVFoundation/AVFoundation.h>
#import <iAd/iAd.h>
#import <QuartzCore/QuartzCore.h>

#import <MediaPlayer/MediaPlayer.h>

#import "Root.h"
#import "GameCenterScreen.h"
#import "GLApp.h"
#import "OCOutlets.h"
#import "OCInlets.h"

#ifdef ENABLE_FACEBOOK

#import "FacebookSDK.h"
#import "FacebookUploadDialog.h"

#endif

/*
@interface AppDelegate : NSObject <UIApplicationDelegate>
{
    UIWindow								*window;
    Root									*viewController;
    GameCenterScreen                        *gameCenterScreen;
}



#endif

@property (strong) UIWindow	*window;
@property (strong) Root	*viewController;

@end
*/

@interface AppDelegate : UIResponder <UIApplicationDelegate>



@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) GLViewController *glViewController;

@property (strong, nonatomic) Root *root;

@property (strong, nonatomic) GameCenterScreen *gameCenterScreen;

- (NSMutableArray*)fetchOrderedFiles:(NSString*)basePath ofType:(NSString*)fileType;
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url;

- (void)gameCenterShow:(BOOL)targetLeaderboardMode;
- (void)gameCenterHide;

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

- (NSMutableArray*)loadFileSequence:(NSString*)basePath;

- (void)loadFileSequence:(NSString*) basePath ofType:(NSString*)fileType withArray:(NSMutableArray *)targetArray;


@end

extern AppDelegate *gDel;
extern GLViewController *gGLViewController;
