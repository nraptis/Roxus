//
//  RootBase.h
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Darkswarm LLC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

#import "GLViewController.h"
#import "GLView.h"

#define ROOT_PUSH_DIR_LEFT 0
#define ROOT_PUSH_DIR_RIGHT 1
#define ROOT_PUSH_DIR_UP 2
#define ROOT_PUSH_DIR_DOWN 3

#define MAIN_W [gRootBase mainWidth]
#define MAIN_H [gRootBase mainHeight]

@interface RootBase : UIViewController <AVAudioPlayerDelegate>
{
    UIViewController                            *viewControllerCurrent;
    UIViewController                            *viewControllerPrevious;
    UIView                                      *containerView;
    int                                         pushDirection;
    
    
    GLViewController                            *glViewController;
    
    BOOL                                        isActive;
    
    NSTimer                                     *globalTimer;
    NSTimeInterval                              globalUpdateInterval;
    
    UIImageView                                 *imageViewBackground;
    
    
    NSMutableArray                              *flipPopoverStack;
    UIView                                      *popoverContainerView;
    UIViewController                            *flipDismissViewController;
    
    AVAudioPlayer                               *musicPlayer;
    AVAudioPlayer                               *musicPlayerFading;
    int                                         musicFadeOutTick;
    int                                         musicFadeOutTickMax;
    bool                                        musicFadeOut;
    int                                         musicFadeInTick;
    int                                         musicFadeInTickMax;
    bool                                        musicFadeIn;
    float                                       musicVolume;
    bool                                        musicLoop;
    bool                                        musicFadeLoop;
}

@property (nonatomic, strong) IBOutlet UIViewController *viewControllerCurrent;
@property (nonatomic, strong) IBOutlet UIViewController *viewControllerPrevious;
@property (nonatomic, strong) UIView *containerView;
@property (nonatomic, assign) int pushDirection;

@property (nonatomic, strong) GLViewController *glViewController;

@property (nonatomic, strong) IBOutlet UIImageView *imageViewBackground;
@property (nonatomic, strong) NSTimer *globalUpdateTimer;
@property (nonatomic, assign) NSTimeInterval globalUpdateInterval;


@property (nonatomic, strong) AVAudioPlayer *musicPlayer;
@property (nonatomic, strong) AVAudioPlayer *musicPlayerFading;

@property (nonatomic, strong) NSMutableArray *flipPopoverStack;
@property (nonatomic, strong) UIView *popoverContainerView;
@property (nonatomic, strong) UIViewController *flipDismissViewController;

- (void)setupOpenGL;

- (void)setupPass1:(CGRect)pFrame;
- (void)setupPass2:(BOOL)pTablet withOS:(float)pOSVersion;
- (void)setupPass3;
- (void)setupFinalize;

- (BOOL)CONFIG_lockOpenGL;

- (void)globalUpdate;

+ (float)appWidth;
+ (float)appHeight;

- (float)mainWidth;
- (float)mainHeightBase;
- (float)mainHeight;
+ (float)mainScale;

+ (BOOL)isTablet;


- (BOOL)pushDestroysViewController:(UIViewController *)pViewController;
- (BOOL)pushViewLockPosition:(UIViewController *)pViewController;


- (void)pushTo:(UIViewController *)pViewController animated:(BOOL)pAnimated;
- (void)pushReverse:(UIViewController *)pViewController animated:(BOOL)pAnimated;
- (void)animationInDidComplete:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context;
- (void)sendViewTo:(UIView*)targetView direction:(int)targetDirection;
- (void)sendViewFrom:(UIView*)targetView direction:(int)targetDirection;
- (int)getReversePushDirection:(int)targetDirection;


- (void)musicPlay:(NSString *)pFilePath withLoop:(BOOL)pLoop;
- (void)musicPlay:(NSString *)pFilePath withVolume:(float)pVolume withLoop:(BOOL)pLoop;
- (void)musicCrossFadeWithPath:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks withLoop:(BOOL)pLoop;
- (void)musicFadeOutWithDurationTicks:(int)pDurationTicks;
- (void)musicFadeInWith:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks;
- (float)musicGetVolume;
- (void)musicSetVolume:(float)pVolume;
- (void)musicStop;
- (BOOL)musicIsPlaying;
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;

- (void)enterBackground;
- (void)enterForeground;

- (void)didFinishAnimatingIn;

- (void)nuke;
- (void)dealloc;

@end

extern RootBase *gRootBase;
