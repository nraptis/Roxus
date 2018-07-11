//
//  RootBase.m
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Darkswarm LLC. All rights reserved.
//

#import "RootBase.h"
#import "core_app_shell.h"

RootBase *gRootBase;
float gLat = 42.3314f;
float gLon = -83.0458f;
static NSString *kPathBundle = nil;
static NSString *kPathDocuments = nil;
static float kAppWidth = 320.0f;
static float kAppHeight = 480.0f;
static float kMainWidth = 320.0f;
static float kMainHeight = 480.0f;
static float kMainScale = 1.0f;
static BOOL kIsTablet = false;
static float kOSVersion = 6.0f;

@implementation RootBase

@synthesize viewControllerCurrent;
@synthesize viewControllerPrevious;
@synthesize containerView;
@synthesize pushDirection;

@synthesize glViewController;

@synthesize globalUpdateTimer;
@synthesize globalUpdateInterval;
@synthesize imageViewBackground;

@synthesize musicPlayer;
@synthesize musicPlayerFading;

@synthesize flipPopoverStack;
@synthesize popoverContainerView;
@synthesize flipDismissViewController;

- (id)init {
    isActive = true;
    gRootBase = self;
    self.pushDirection = ROOT_PUSH_DIR_LEFT;
    self = [super init];
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    isActive = true;
    gRootBase = self;
    self.pushDirection = ROOT_PUSH_DIR_LEFT;
    self = [super initWithCoder:aDecoder];
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    return self;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    isActive = true;
    gRootBase = self;
    self.pushDirection = ROOT_PUSH_DIR_LEFT;
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    return self;
}

- (void)setupOpenGL {
    if (glViewController == nil) {
        //UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        //self.glViewController = (GLViewController *)[mainStoryboard instantiateViewControllerWithIdentifier:@"gl_view_controller"];
        
        self.glViewController = [[GLViewController alloc] init];
        
        if (isActive == YES) {
            [glViewController startAnimation];
        }
    }
}

- (void)setupPass1:(CGRect)pFrame {
    gRootBase = self;
    kAppWidth = pFrame.size.width;
    kAppHeight = pFrame.size.height;
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, kAppWidth, kAppHeight);
    imageViewBackground.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, kAppWidth, kAppHeight);
    float aFixedWidth = 0.0f;//[self CONFIG_fixedWidth];
    BOOL aFixed = NO;
    if(aFixedWidth < 64.0)
    {
        kMainWidth = kAppWidth;
        kMainScale = 1.0f;
        kMainHeight = kAppHeight;
    }
    else
    {
        kMainWidth = aFixedWidth;
        kMainScale = pFrame.size.width / kMainWidth;
        kMainHeight = kAppHeight / kMainScale;
        
        aFixed = YES;
    }
    
    self.containerView = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, kMainWidth, kMainHeight)];
    [self.view addSubview:containerView];
    containerView.clipsToBounds = YES;
    containerView.layer.anchorPoint = CGPointMake(0.0f, 0.0f);
    
    if(aFixed == YES)
    {
        //CATransform3D aTransform = CATransform3DIdentity;
        //aTransform = CATransform3DScale(aTransform, kMainScale, kMainScale, kMainScale);
        //containerView.layer.transform = aTransform;
        
    }
    containerView.frame = CGRectMake(0.0f, 0.0f, kMainWidth, kMainHeight);
    //containerView.layer.zPosition = 100.0f;
    
    
    /*
     self.popoverContainerView = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, kMainWidth, kMainHeight)];
     //[self.view addSubview:popoverContainerView];
     popoverContainerView.clipsToBounds = YES;
     popoverContainerView.layer.anchorPoint = CGPointMake(0.0f, 0.0f);
     if(aFixed == YES)
     {
     CATransform3D aTransform = CATransform3DIdentity;
     aTransform = CATransform3DScale(aTransform, kMainScale, kMainScale, kMainScale);
     popoverContainerView.layer.transform = aTransform;
     }
     popoverContainerView.frame = CGRectMake(0.0f, 0.0f, kMainWidth, kMainHeight);
     popoverContainerView.hidden = YES;
     popoverContainerView.layer.zPosition = 2048.0f;
     */
    
}

- (void)setupPass2:(BOOL)pTablet withOS:(float)pOSVersion
{
    kIsTablet = pTablet;
    kOSVersion = pOSVersion;
    
}

- (void)setupPass3
{
    
}

- (void)setupFinalize
{
    self.globalUpdateInterval = 1 / 60.0f;
    self.globalUpdateTimer = [NSTimer scheduledTimerWithTimeInterval:globalUpdateInterval target:self selector:@selector(globalUpdate) userInfo:nil repeats:YES];
}

- (BOOL)CONFIG_lockOpenGL
{
    return YES;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)pushViewLockPosition:(UIViewController *)pViewController
{
    if(pViewController == glViewController)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

- (BOOL)pushDestroysViewController:(UIViewController *)pViewController
{
    if(pViewController == glViewController)
    {
        return NO;
    }
    else
    {
        return YES;
    }
}

- (void)internalPushDestroyPreviousViewController
{
    if([self pushDestroysViewController:viewControllerPrevious] == YES)
    {
        if(viewControllerPrevious != nil)
        {
            if([viewControllerPrevious respondsToSelector:@selector(nuke)])[viewControllerPrevious performSelector:@selector(nuke)];
            
            [viewControllerPrevious.view.layer removeAllAnimations];
            [viewControllerPrevious.view removeFromSuperview];
            self.viewControllerPrevious = nil;
        }
    }
    else
    {
        [self.viewControllerPrevious.view removeFromSuperview];
        self.viewControllerPrevious = nil;
    }
}

- (void)pushTo:(UIViewController *)pViewController animated:(BOOL)pAnimated
{
    [self internalPushDestroyPreviousViewController];
    
    self.viewControllerPrevious = viewControllerCurrent;
    self.viewControllerCurrent = pViewController;
    
    [containerView addSubview:viewControllerCurrent.view];
    
    [self sendViewFrom:viewControllerCurrent.view direction:pushDirection];
    
    if(pAnimated)
    {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDuration:0.42f];
        //[UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
        [UIView setAnimationDidStopSelector:@selector(animationInDidComplete:finished:context:)];
    }
    
    if([self pushViewLockPosition:viewControllerPrevious] == false)
    {
        [self sendViewTo:viewControllerPrevious.view direction:pushDirection];
    }
    
    
    
    viewControllerCurrent.view.frame = CGRectMake(0,0,viewControllerCurrent.view.frame.size.width,viewControllerCurrent.view.frame.size.height);
    
    if(pAnimated)
    {
        [UIView commitAnimations];
    }
    else
    {
        [self animationInDidComplete:nil finished:nil context:nil];
    }
}

- (void)pushReverse:(UIViewController *)pViewController animated:(BOOL)pAnimated
{
    [self internalPushDestroyPreviousViewController];
    
    self.viewControllerPrevious = viewControllerCurrent;
    self.viewControllerCurrent = pViewController;
    
    [containerView addSubview:viewControllerCurrent.view];
    
    [self sendViewFrom:viewControllerCurrent.view direction:[self getReversePushDirection:pushDirection]];
    
    if(pAnimated)
    {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDuration:0.42f];
        //[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
        [UIView setAnimationDidStopSelector:@selector(animationInDidComplete:finished:context:)];
    }
    
    if([self pushViewLockPosition:viewControllerPrevious] == false)
    {
        [self sendViewTo:viewControllerPrevious.view direction:[self getReversePushDirection:pushDirection]];
    }
    
    viewControllerCurrent.view.frame = CGRectMake(0.0f,0.0f,viewControllerCurrent.view.frame.size.width,viewControllerCurrent.view.frame.size.height);
    
    if(pAnimated)
    {
        [UIView commitAnimations];
    }
    else
    {
        [self animationInDidComplete:nil finished:nil context:nil];
    }
}

- (void)animationInDidComplete:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
{
    
    if(viewControllerCurrent != nil)
    {
        if([viewControllerCurrent respondsToSelector:@selector(didFinishAnimatingIn)] == YES)
        {
            [viewControllerCurrent performSelector:@selector(didFinishAnimatingIn) withObject:nil afterDelay:0.0];
        }
    }
    
    [self internalPushDestroyPreviousViewController];
}

- (void)sendViewTo:(UIView*)targetView direction:(int)targetDirection
{
    float aX=0.0f;
    float aY=0.0f;
    float aWidth=targetView.frame.size.width;
    float aHeight=targetView.frame.size.height;
    
    if(targetDirection == ROOT_PUSH_DIR_LEFT)targetView.frame = CGRectMake(aX-kMainWidth, aY, aWidth, aHeight);
    if(targetDirection == ROOT_PUSH_DIR_RIGHT)targetView.frame = CGRectMake(aX+kMainWidth, aY, aWidth, aHeight);
    if(targetDirection == ROOT_PUSH_DIR_UP)targetView.frame = CGRectMake(aX, aY-kMainHeight, aWidth, aHeight);
    if(targetDirection == ROOT_PUSH_DIR_DOWN)targetView.frame = CGRectMake(aX, aY+kMainHeight, aWidth, aHeight);
}

- (int)getReversePushDirection:(int)targetDirection
{
    int aReturn = targetDirection;
    if(targetDirection == ROOT_PUSH_DIR_LEFT)aReturn = ROOT_PUSH_DIR_RIGHT;
    else if(targetDirection == ROOT_PUSH_DIR_RIGHT)aReturn = ROOT_PUSH_DIR_LEFT;
    else if(targetDirection == ROOT_PUSH_DIR_UP)aReturn = ROOT_PUSH_DIR_DOWN;
    else if(targetDirection == ROOT_PUSH_DIR_DOWN)aReturn = ROOT_PUSH_DIR_UP;
    return aReturn;
}

- (void)sendViewFrom:(UIView*)targetView direction:(int)targetDirection
{
    float aX=0.0f;
    float aY=0.0f;
    float aWidth=targetView.frame.size.width;
    float aHeight=targetView.frame.size.height;
    
    if(targetDirection == ROOT_PUSH_DIR_LEFT)targetView.frame = CGRectMake(aX+kMainWidth, aY, aWidth, aHeight);
    if(targetDirection == ROOT_PUSH_DIR_RIGHT)targetView.frame = CGRectMake(aX-kMainWidth, aY, aWidth, aHeight);
    if(targetDirection == ROOT_PUSH_DIR_UP)targetView.frame = CGRectMake(aX, aY+kMainHeight, aWidth, aHeight);
    if(targetDirection == ROOT_PUSH_DIR_DOWN)targetView.frame = CGRectMake(aX, aY-kMainHeight, aWidth, aHeight);
}

- (void)globalUpdate
{
    if(musicFadeIn)
    {
        musicFadeInTick--;
        
        if(musicFadeInTick <= 0)
        {
            [musicPlayer setVolume:(musicVolume)];
            musicFadeIn = NO;
        }
        else
        {
            if(musicFadeInTickMax <= 0)musicFadeInTickMax = 1;
            float aPercent = ((float)musicFadeInTick) / ((float)musicFadeInTickMax);
            if(aPercent < 0.0f)aPercent = 0.0f;
            if(aPercent > 1.0f)aPercent = 1.0f;
            aPercent = 1.0f - aPercent;
            [musicPlayer setVolume:(aPercent * musicVolume)];
        }
    }
    
    if(musicFadeOut)
    {
        musicFadeOutTick--;
        
        if(musicFadeOutTick <= 0)
        {
            [musicPlayerFading stop];
            musicPlayerFading.delegate = nil;
            self.musicPlayerFading = nil;
            musicFadeOut = NO;
        }
        else
        {
            if(musicFadeOutTickMax <= 0)musicFadeOutTickMax = 1;
            float aPercent = ((float)musicFadeOutTick) / ((float)musicFadeOutTickMax);
            if(aPercent < 0.0f)aPercent = 0.0f;
            if(aPercent > 1.0f)aPercent = 1.0f;
            [musicPlayerFading setVolume:(aPercent * musicVolume)];
        }
    }
}

- (void)musicPlay:(NSString *)pFilePath withLoop:(BOOL)pLoop
{
    [self musicPlay:pFilePath withVolume:1.0f withLoop:pLoop];
}

- (void)musicPlay:(NSString *)pFilePath withVolume:(float)pVolume withLoop:(BOOL)pLoop
{
    NSLog(@"Music Play [%@]", pFilePath);
    musicLoop = NO;
    if(musicPlayer)
    {
        [musicPlayer stop];
        musicPlayer.delegate = nil;
        self.musicPlayer = nil;
    }
    bool aFail = true;
    NSURL *aURL = [[NSURL alloc] initFileURLWithPath: pFilePath];
    if(aURL)
    {
        NSError *aError;
        musicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:aURL error:&aError];
        if(aError)
        {
            NSLog(@"Music Error!");
            NSLog(@"[%@]", pFilePath);
            NSLog(@"(%@)", aError);
        }
        else
        {
            [musicPlayer prepareToPlay];
            [musicPlayer setVolume:(musicVolume * pVolume)];
            [musicPlayer setDelegate:self];
            [musicPlayer play];
            musicLoop = pLoop;
            aFail = NO;
        }
    }
}

- (void)musicCrossFadeWithPath:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks withLoop:(BOOL)pLoop
{
    if(pDurationTicks < 1)pDurationTicks = 1;
    
    [self musicFadeOutWithDurationTicks:pDurationTicks];
    
    if(musicPlayer)
    {
        [musicPlayer stop];
        musicPlayer.delegate = nil;
        self.musicPlayer = nil;
    }
    
    
    [self musicPlay:pFilePath withVolume:0.0f withLoop:pLoop];
    
    
    musicFadeInTick = pDurationTicks;
    musicFadeInTickMax = pDurationTicks;
    musicFadeIn = YES;
}

- (void)musicFadeOutWithDurationTicks:(int)pDurationTicks
{
    if(pDurationTicks < 1)pDurationTicks = 1;
    
    if(musicPlayerFading)
    {
        [musicPlayerFading stop];
        musicPlayerFading.delegate = nil;
        self.musicPlayerFading = nil;
    }
    
    
    if(musicPlayer)
    {
        self.musicPlayerFading = musicPlayer;
        self.musicPlayer = nil;
        
        musicFadeLoop = musicLoop;
        musicFadeOutTick = pDurationTicks;
        musicFadeOutTickMax = pDurationTicks;
        musicFadeOut = true;
    }
    else
    {
        musicFadeLoop = false;
        musicFadeOutTick = 0;
        musicFadeOutTickMax = 0;
        musicFadeOut = false;
    }
    
}

- (float)musicGetVolume
{
    return musicVolume;
}

- (void)musicSetVolume:(float)pVolume
{
    if(pVolume < 0.0f)pVolume = 0.0f;
    if(pVolume > 1.0f)pVolume = 1.0f;
    
    musicVolume = pVolume;
    
    [musicPlayer setVolume:(musicVolume)];
}


- (void)musicFadeInWith:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks
{
    
}

- (void)musicStop
{
    
}

- (BOOL)musicIsPlaying
{
    BOOL aReturn = NO;
    
    return aReturn;
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    NSLog(@"AudioPlayerFinished! Successful(%d) Loop(main: %d, fade: %d)", flag, musicLoop, musicFadeLoop);
    
    if(player == musicPlayer)
    {
        if(musicLoop)
        {
            [musicPlayer play];
        }
        else
        {
            [musicPlayer stop];
            musicPlayer.delegate = nil;
            self.musicPlayer = nil;
        }
    }
    else if(player == musicPlayerFading)
    {
        if(musicFadeLoop)
        {
            [musicPlayerFading play];
        }
        else
        {
            [musicPlayerFading stop];
            musicPlayerFading.delegate = nil;
            self.musicPlayerFading = nil;
        }
    }
}

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error{}

+ (float)appWidth
{
    return kAppWidth;
}

+ (float)appHeight
{
    return kAppHeight;
}



- (float)mainWidth
{
    return kMainWidth;
}

- (float)mainHeightBase
{
    return kMainHeight;
}

- (float)mainHeight
{
    return kMainHeight;
}

+ (float)mainScale
{
    return kMainScale;
}

+ (BOOL)isTablet
{
    return kIsTablet;
}

- (void)enterBackground
{
    isActive = false;
    
    AppShellPause();
    [glViewController stopAnimation];
}

- (void)enterForeground
{
    isActive = true;
    
    AppShellResume();
    if((viewControllerCurrent == gGLViewController) && (viewControllerCurrent != nil))
    {
        [glViewController startAnimation];
    }
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didFinishAnimatingIn
{
    
}

- (void)nuke
{
    
}

- (void)dealloc
{
    [self nuke];
}

@end
