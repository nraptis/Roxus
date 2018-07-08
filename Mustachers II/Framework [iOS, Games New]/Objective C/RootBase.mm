//
//  RootViewController.m
//  Gnome
//
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "RootBase.h"
#import "GLView.h"
#import "AppDelegate.h"
#import "PopoverContainer.h"
#import "Root.h"

RootBase *gRootBase;
GameCenterScreen *gGameCenter;
StoreScreen *gStore;

int gLanguageIndex;

@implementation RootBase


#ifdef ENABLE_FACEBOOK
@synthesize facebookUploadDialog;
#endif

#ifdef ENABLE_TWITTER
@synthesize twitterUploadDialog;
#endif


@synthesize loopMusic;
@synthesize isAnimating;

@synthesize admobTimer,admobInterval;
@synthesize musicPlayer;
@synthesize iAdsVisible,admobVisible;
@synthesize disableAllAds, allAdsDisabled;
@synthesize currentOrientation;

@synthesize popupCurrent;
@synthesize popupPrevious;

@synthesize glViewController;

@synthesize bannerBlackBar;

@synthesize glOverlay;

@synthesize nextViewController;
@synthesize currentViewController;
@synthesize previousViewController;

@synthesize gameCenter;
@synthesize storeScreen;

@synthesize ignoreAnimations;

@synthesize disablePopoverPinchClose;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    
    disablePopoverPinchClose=NO;
    
#ifndef DISABLE_AUDIO
    
    AVAudioSession *session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryPlayback error:nil];
    OSStatus propertySetError = 0;
    UInt32 allowMixing = true;
    propertySetError = AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryMixWithOthers,
    sizeof (allowMixing),&allowMixing);
    
#endif
    
    gRootBase=self;
    loopMusic=YES;
    isAnimating=NO;
    
    ignoreAnimations=NO;
    animationDirection=ROOT_DIR_LEFT;
    animationDirectionDefault=ROOT_DIR_LEFT;
    
#ifndef DISABLE_GC
    self.gameCenter = gGameCenter = [[GameCenterScreen alloc] initWithNibName:nil bundle:nil];    
#endif
    
#ifndef DISABLE_STORE
    self.storeScreen = gStore = [[StoreScreen alloc] initWithNibName:nil bundle:nil];
#endif
    
    [gGLViewController load];
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    allAdsDisabled=NO;
	
#ifdef DISABLE_BULLSHIT
	disableAllAds=YES;
#endif
    
    //TODO: Disable auto-buy..
    disableAllAds=YES;
	
    
    if(GAPP->mPurchased)
    {
        disableAllAds=YES;
        allAdsDisabled=YES;
        
        GAPP->UpdateAdHeight(0);
    }
    
    
    return self;
}

- (void)startAccelerometer
{
    
    [[UIAccelerometer sharedAccelerometer] setUpdateInterval:1/60.0f];
    [[UIAccelerometer sharedAccelerometer] setDelegate:self];
    
}

- (void)startAccelerometerWithInterval:(NSTimeInterval)targetInterval
{
    [[UIAccelerometer sharedAccelerometer] setUpdateInterval:targetInterval];
    [[UIAccelerometer sharedAccelerometer] setDelegate:self];
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	if(GAPP)
	{
#ifdef LANDSCAPE_MODE
        GAPP->Accelerometer(acceleration.x, acceleration.y, acceleration.z, gRoot.currentOrientation == UIInterfaceOrientationLandscapeRight);
#else
        GAPP->Accelerometer(acceleration.x, acceleration.y, acceleration.z, gRoot.currentOrientation != UIInterfaceOrientationPortrait);
#endif
	}
}


- (void)startGlobalUpdate
{
    globalInterval = 1 / 60.0f;
    globalTimer = [NSTimer scheduledTimerWithTimeInterval:globalInterval target:self selector:@selector(globalUpdate) userInfo:nil repeats:YES];
}

- (void)go
{
    gGLViewController.updateInterval = 1 / 60.0f;
    
    //self.view.frame = CGRectMake(0.0f, 0.0f, gAppWidth, gAppHeight);
}

- (void)begin
{
    gGLViewController.view.frame = CGRectMake(0.0f, 0.0f, gAppWidth, gAppHeight);
    gGLView.frame = CGRectMake(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    self.view.frame = CGRectMake(0.0f, 0.0f, gAppWidth, gAppHeight);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    
#ifdef LANDSCAPE_MODE
	if(interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight)
	{
		gRoot.currentOrientation = interfaceOrientation;
		return YES;
	}
#else
	if(interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
	{
		gRoot.currentOrientation = interfaceOrientation;
		return YES;
	}
#endif
    
	return NO;
}

- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
	iAdsVisible=YES;
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    
	iAdsVisible = NO;
    

}

- (void)fakeAdClicked
{
    
	[self adClickPause];
    
}

- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    
}

- (void)setMusicVolume:(float)volume
{
	GAPP->mMusicVolume=volume;
	[musicPlayer setVolume:GAPP->mMusicVolume];
}

- (void)playMusic:(NSString*) path withDelegate:(id)del
{
    
#ifndef DISABLE_AUDIO
    
    NSString *aPath = [NSString stringWithFormat:@"%s%@", gSandbox.c(), path];
	
	if(musicPlayer)
	{
		[musicPlayer stop];
		musicPlayer.delegate=nil;
		musicPlayer=nil;
	}
    
	NSURL *aURL = [[NSURL alloc] initFileURLWithPath: aPath];
    NSError *aError;
    
	musicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:aURL error:&aError];
    
	[musicPlayer prepareToPlay];
	[musicPlayer setVolume: 1];
	[musicPlayer setDelegate: del];
	[musicPlayer play];
    
#endif
    
}

/*

- (void)playMusic:(NSString*) path withDelegate:(id)del

{
    
    [[AVAudioSession sharedInstance] setDelegate: self];
	[[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryAmbient error: nil];
	
    NSError *activationError = nil;
    [[AVAudioSession sharedInstance] setActive: YES error: &activationError];
    
    if(activationError)
    {
        NSLog(@"Music: Activation Error");
        NSLog(@"%@", activationError);
    }
    
    NSLog(@"Attempting To Play The Musics [%@]", path);
    
	NSString *aPath = [[NSString alloc] initWithFormat:@"%s%@", gSandbox.c(), path];
	
	if(musicPlayer)
	{
		[self.musicPlayer stop];
		self.musicPlayer.delegate=nil;
		self.musicPlayer=nil;
	}
	
	NSURL *aURL = [[NSURL alloc] initFileURLWithPath: aPath];
    NSError *aError;
	
	musicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:aURL error:&aError];
    
    if(aError)
    {
        NSLog(@"Music Error: %@", aError);
    }
    
	[self.musicPlayer prepareToPlay];
	[self.musicPlayer setVolume: 1];
	[self.musicPlayer setDelegate: del];
	[self.musicPlayer play];

}

 */

- (void)playMusic:(NSString*)path
{
    [self playMusic:path withDelegate:self];
}

- (void)killMusic
{
    [self.musicPlayer stop];
    self.musicPlayer=nil;
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
	if(musicPlayer)
	{
        if(loopMusic)
        {
            [musicPlayer play];
        }
        else
        {
            [musicPlayer stop];
            musicPlayer=nil;
        }
        
	}
}

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error
{
	
}

- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player
{
	
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags
{
	
}

- (void)adClickPause
{
	[self enterBackground];
}

- (void)adCloseResume
{
	[self enterForeground];
}

- (void)enterBackground
{
    if(GAPP)GAPP->GoInactive();
    [gGLViewController stopAnimation];
	[musicPlayer stop];
    if(GAPP)
    {
        GAPP->SaveStatic();
        
    }
}

- (void)enterForeground
{
    
    if(GAPP)GAPP->GoActive();
    
	[musicPlayer play];
    
    if(currentViewController == gGLViewController)[gGLViewController startAnimation];
    
    GAPP->LoadStatic();
    
}

- (void)animationComplete
{
    
}

- (UIViewController *)fetchViewForAction:(NSString*)targetAction
{
	UIViewController *aReturn=nil;
	return aReturn;
}

- (bool)action:(NSString*)targetAction
{
    
    return YES;
}


- (NSMutableArray*)getFileSequence:(NSString*)targetPrefix withExtension:(NSString*)targetExtension
{
    NSMutableArray *aArray = [[NSMutableArray alloc] init];
	int aIndex = 0;
	while(true)
	{
		NSString *aFileName = [[NSString alloc] initWithFormat:@"%@%d", targetPrefix, aIndex];
        
		NSString *aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:targetExtension];
        
        if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath] == false)
		{
            aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:@"jpg"];
            
            if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath] == false)
            {
                aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:@"png"];
            }
        }
        
		if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
		{
			[aArray addObject:aCheckPath];
		}
		else
		{
			aFileName = [[NSString alloc] initWithFormat:@"%@0%d", targetPrefix, aIndex];
			aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:targetExtension];
			
            
            if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath] == false)
            {
                aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:@"jpg"];
                
                if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath] == false)
                {
                    aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:@"png"];
                }
            }
            
			if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
			{
				[aArray addObject:aCheckPath];
			}
			else
			{
                
				aFileName = [[NSString alloc] initWithFormat:@"%@00%d", targetPrefix, aIndex];
				aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:targetExtension];
                
                if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath] == false)
                {
                    aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:@"jpg"];
                    
                    if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath] == false)
                    {
                        aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:@"png"];
                    }
                }
				if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
				{
					[aArray addObject:aCheckPath];
				}
				else
				{
					if(aIndex >= 5)
					{
						break;
					}
				}
			}
		}
		aIndex++;
	}
    return aArray;
}

- (void)purchaseSuccessful:(NSString*)targetString
{
    
}

- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
{
    
    isAnimating = NO;
    
    if(previousViewController == gGLViewController)
    {
        
    }
    else
    {
        
        if([previousViewController respondsToSelector:@selector(nuke)])
        {
            [previousViewController performSelector:@selector(nuke)];
        }
        
        [self.previousViewController.view removeFromSuperview];
        self.previousViewController=nil;
    }
    
}

- (void)pushTo:(UIViewController*)targetViewController
{
    BOOL aForceDisable=NO;
    
    int aFind = mUpdateList.Find((__bridge void*) targetViewController);
    mUpdateList.Clear();
    if(aFind != -1)mUpdateList.Add((__bridge void*) targetViewController);
    
    
    if(isAnimating && (self.ignoreAnimations == NO))
    {
        aForceDisable=YES;
        isAnimating=NO;
        self.ignoreAnimations=YES;
    }
    
    if(loopMusic == FALSE)
    {
        [self killMusic];
    }
    
    if(popupCurrent)
    {
        if([popupCurrent respondsToSelector:@selector(nuke)])
        {
            [popupCurrent performSelector:@selector(nuke)];
        }
        
        [popupCurrent.view removeFromSuperview];
        self.popupCurrent=nil;
    }
    
    
    
    if(previousViewController == gGLViewController)
    {
        
    }
    else
    {
        if([previousViewController respondsToSelector:@selector(nuke)])
        {
            [previousViewController performSelector:@selector(nuke)];
        }
        
        [self.previousViewController.view removeFromSuperview];
        self.previousViewController=nil;
    }
    
	self.previousViewController=self.currentViewController;
	self.currentViewController=targetViewController;
    
	BOOL aPreviousGL = (previousViewController == gGLViewController);
	BOOL aCurrentGL = (currentViewController == gGLViewController);
    
    BOOL aDidAnimate=NO;
    
    isAnimating = NO;
    
    if(previousViewController != nil && previousViewController != currentViewController && ignoreAnimations == false)
    {
        aDidAnimate=YES;
        
        [self sendViewFrom:currentViewController.view direction:animationDirection];
        
        isAnimating=YES;
        
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDuration:0.45f];
        [UIView setAnimationDidStopSelector:@selector(animationDidStop:finished:context:)];
        
        [self sendViewTo:previousViewController.view direction:animationDirection];
        //[self sendViewTo:currentViewController.view direction:animationDirection];
        
        currentViewController.view.frame = CGRectMake(0,0,gAppWidth,gAppHeight);
        
        [UIView  commitAnimations];
    }
    else
    {
        currentViewController.view.frame = CGRectMake(0,0,gAppWidth,gAppHeight);
    }
    
    animationDirection=animationDirectionDefault;
    
	if(currentViewController.view.superview == nil)
	{
		[self.view addSubview:currentViewController.view];
	}
	else
	{
		[self.view bringSubviewToFront:currentViewController.view];
	}
	
	if(currentViewController == gGLViewController)
	{
		[gGLViewController startAnimation];
        
        if(glOverlay)
        {
            [self.view addSubview:glOverlay.view];
        }
	}
    
    if([previousViewController respondsToSelector:@selector(stopAnimation)])
    {
        if(aCurrentGL && aPreviousGL)
        {
            
        }
        else
        {
            [previousViewController performSelector:@selector(stopAnimation)];
        }
    }
    
    if(aDidAnimate == NO)
    {
        if(previousViewController != gGLViewController)[previousViewController.view removeFromSuperview];
        previousViewController=nil;
    }
    
    if(aForceDisable)self.ignoreAnimations=NO;
}

- (void)pushTo:(UIViewController*)targetViewController withDirection:(int)targetDirection
{
    animationDirection = targetDirection;
    [self pushTo:targetViewController];
}

- (void)setDirectionLeft
{
    [self setDirection:ROOT_DIR_LEFT];
}

- (void)setDirectionRight
{
    [self setDirection:ROOT_DIR_RIGHT];
}

- (void)setDirectionUp
{
    [self setDirection:ROOT_DIR_UP];
}

- (void)setDirectionDown
{
    [self setDirection:ROOT_DIR_DOWN];
}

- (void)setDirection:(int)targetDirection
{
    animationDirection=targetDirection;
}

- (void)sendViewTo:(UIView*)targetView direction:(int)targetDirection
{
    float aX=targetView.frame.origin.x;
    float aY=targetView.frame.origin.y;
    float aWidth=targetView.frame.size.width;
    float aHeight=targetView.frame.size.height;
    
    if(targetDirection == ROOT_DIR_LEFT)
    {
        targetView.frame = CGRectMake(aX-gAppWidth, aY, aWidth, aHeight);
    }
    
    if(targetDirection == ROOT_DIR_RIGHT)
    {
        targetView.frame = CGRectMake(aX+gAppWidth, aY, aWidth, aHeight);
    }
    
    if(targetDirection == ROOT_DIR_UP)
    {
        targetView.frame = CGRectMake(aX, aY-gAppHeight, aWidth, aHeight);
    }
    
    if(targetDirection == ROOT_DIR_DOWN)
    {
        targetView.frame = CGRectMake(aX, aY+gAppHeight, aWidth, aHeight);
    }
    
}

- (void)sendViewFrom:(UIView*)targetView direction:(int)targetDirection
{
    float aX=targetView.frame.origin.x;
    float aY=targetView.frame.origin.y;
    float aWidth=targetView.frame.size.width;
    float aHeight=targetView.frame.size.height;
    
    if(targetDirection == ROOT_DIR_LEFT)
    {
        targetView.frame = CGRectMake(aX+gAppWidth, aY, aWidth, aHeight);
    }
    if(targetDirection == ROOT_DIR_RIGHT)
    {
        targetView.frame = CGRectMake(aX-gAppWidth, aY, aWidth, aHeight);
    }
    if(targetDirection == ROOT_DIR_UP)
    {
        targetView.frame = CGRectMake(aX, aY+gAppHeight, aWidth, aHeight);
    }
    if(targetDirection == ROOT_DIR_DOWN)
    {
        targetView.frame = CGRectMake(aX, aY-gAppHeight, aWidth, aHeight);
    }
}

// - (void)showPopupImage:(NSString *)targetImage withBackgroundImage:(NSString*)targetBackgroundImagePath;

- (void)showPopoverImage:(NSString*)targetPath withRect:(CGRect)targetRectangle
{
    PopoverContainer *aContainer = [[PopoverContainer alloc] initWithNibName:nil bundle:nil];
    
    if(disablePopoverPinchClose)aContainer.disablePinchClose=YES;
    else aContainer.disablePinchClose=NO;
    
    [aContainer loadImage:targetPath];
    [self showPopup:aContainer];
    [aContainer animateMe:targetRectangle];
}

- (void)showPopupAnimated:(UIViewController*)targetViewController withRect:(CGRect)targetRectangle
{
    PopoverContainer *aContainer = [[PopoverContainer alloc] initWithNibName:nil bundle:nil];
    
    if(disablePopoverPinchClose)aContainer.disablePinchClose=YES;
    else aContainer.disablePinchClose=NO;
    
    [aContainer setTarget:targetViewController];
    [self showPopup:aContainer];
    [aContainer animateMe:targetRectangle];
}

- (void)showPopup:(UIViewController*)targetViewController
{
    if(popupPrevious)
    {
        if([popupPrevious respondsToSelector:@selector(nuke)])
        {
            [popupPrevious performSelector:@selector(nuke)];
        }
        [popupPrevious.view removeFromSuperview];
        self.popupPrevious=popupCurrent;
        self.popupCurrent=nil;
    }
    else if(popupCurrent)
    {
        if([popupCurrent respondsToSelector:@selector(nuke)])
        {
            [popupCurrent performSelector:@selector(nuke)];
        }
        
        [popupCurrent.view removeFromSuperview];
        self.popupCurrent=nil;
    }
	self.popupCurrent=targetViewController;
	[self.view addSubview:popupCurrent.view];
    
    if(targetViewController)
    {
        if([targetViewController respondsToSelector:@selector(languageUpdate)])
        {
            [targetViewController performSelector:@selector(languageUpdate)];
        }
    }
}

- (void)killPopup
{
    [self killMusic];
    if(popupPrevious)
    {
        if([popupPrevious respondsToSelector:@selector(nuke)])
        {
            [popupPrevious performSelector:@selector(nuke)];
        }
        [popupPrevious.view removeFromSuperview];
    }
    if(popupCurrent)
    {
        if([popupCurrent respondsToSelector:@selector(nuke)])
        {
            [popupCurrent performSelector:@selector(nuke)];
        }
        [popupCurrent.view removeFromSuperview];
    }
    
    self.popupPrevious=nil;
    self.popupCurrent=nil;
    
}

- (UIImage*)loadImage:(NSString*)targetImagePath
{
    int aCheck=0;
    UIImage *aImage=nil;
    
    if(targetImagePath != nil)
    {
        aImage=[UIImage imageNamed:targetImagePath];
    }
    
    FString aPath=NS_S(targetImagePath);
    aPath.RemoveExtension();
    
    if(aImage == nil)
    {
        aImage=[UIImage imageNamed:[NSString stringWithFormat:@"%s.png", aPath.c()]];
        if(aImage)aCheck = aImage.size.width;
    }
    
    if(aImage == nil)
    {
        aImage=[UIImage imageNamed:[NSString stringWithFormat:@"%s.jpg", aPath.c()]];
        if(aImage)aCheck = aImage.size.width;
    }
    
    if(aImage == nil)
    {
        aImage=[UIImage imageNamed:[NSString stringWithFormat:@"%s0.png", aPath.c()]];
        if(aImage)aCheck = aImage.size.width;
    }
    
    return aImage;
}

- (void)killPopupAnimated
{
    if([popupCurrent class] == [PopoverContainer class])
    {
        [((PopoverContainer*)popupCurrent) close];
    }
    else
    {
        [self killPopup];
    }
}

- (void)sendAdsToFront
{
    
}

- (void)facebookGo:(UIImage*)targetImage withCaption:(NSString*)targetCaption
{
#ifdef ENABLE_FACEBOOK
    if(facebookUploadDialog == nil)
	{
		self.facebookUploadDialog = [[FacebookUploadDialog alloc] initWithNibName:nil bundle:nil];
	}
    [self.view addSubview:facebookUploadDialog.view];
    [facebookUploadDialog uploadImage:targetImage withMessage:targetCaption];
#endif
    [self sendAdsToFront];
}

- (void)facebookGoVideo:(NSString*)targetPath withCaption:(NSString*)targetCaption
{
#ifdef ENABLE_FACEBOOK
    if(facebookUploadDialog == nil)
	{
		self.facebookUploadDialog = [[FacebookUploadDialog alloc] initWithNibName:nil bundle:nil];
	}
    [self.view addSubview:facebookUploadDialog.view];
    NSLog(@"About To Upload[%@]", targetPath);
    NSLog(@"Facebook Class Is: [%@]", facebookUploadDialog);
    [facebookUploadDialog uploadVideo:targetPath withMessage:targetCaption];
#endif
    [self sendAdsToFront];
}

- (void)facebookKill
{
#ifdef ENABLE_FACEBOOK
    [facebookUploadDialog.view removeFromSuperview];
#endif
}

- (void)twitterGo:(UIImage*)targetImage withCaption:(NSString*)targetCaption
{
#ifdef ENABLE_TWITTER
    if(twitterUploadDialog == nil)
	{
		self.twitterUploadDialog = [[TwitterUploadDialog alloc] initWithNibName:nil bundle:nil];
	}
    [self.view addSubview:twitterUploadDialog.view];
    [twitterUploadDialog uploadImage:targetImage withMessage:targetCaption];
#endif
    [self sendAdsToFront];
}

- (void)twitterGoData:(NSString*)targetPath withCaption:(NSString*)targetCaption
{
#ifdef ENABLE_TWITTER
    if(twitterUploadDialog == nil)
	{
		self.twitterUploadDialog = [[TwitterUploadDialog alloc] initWithNibName:nil bundle:nil];
	}
    [self.view addSubview:twitterUploadDialog.view];
    [twitterUploadDialog uploadJPEG:targetPath withMessage:targetCaption];
#endif
    [self sendAdsToFront];
}

- (void)twitterGoVideo:(NSString*)targetPath withCaption:(NSString*)targetCaption
{
#ifdef ENABLE_TWITTER
    if(twitterUploadDialog == nil)
	{
		self.twitterUploadDialog = [[TwitterUploadDialog alloc] initWithNibName:nil bundle:nil];
	}
    [self.view addSubview:twitterUploadDialog.view];
    [twitterUploadDialog uploadVideo:targetPath withMessage:targetCaption];
#endif
    [self sendAdsToFront];
}

- (void)twitterKill
{
#ifdef ENABLE_TWITTER
    [twitterUploadDialog.view removeFromSuperview];
#endif
}




- (void)globalUpdate
{
    EnumList(void, aObject, mUpdateList)
    {
        [((__bridge NSObject*)aObject) performSelector:@selector(globalUpdate)];
    }
}

- (void)addGlobalUpdate:(NSObject*)targetObject
{
    if(mUpdateList.Exists((__bridge void*)targetObject) == false)
    {
        mUpdateList += (__bridge void*)targetObject;
    }
}

- (void)removeGlobalUpdate:(NSObject*)targetObject
{
    mUpdateList -= (__bridge void*)targetObject;
}

- (void)dealloc
{
    NSLog(@"\n\n\n___ ROOT DEALLOC ___\n\n\n");
}

@end
