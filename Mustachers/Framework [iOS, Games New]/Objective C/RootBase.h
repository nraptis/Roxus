
#define VIEWHAX(v) (v).frame=CGRectMake((v).frame.origin.x,(v).frame.origin.y,(v).frame.size.width,(v).frame.size.height)

#define VCHAX(v) (v).view.frame=CGRectMake((v).view.frame.origin.x,(v).view.frame.origin.y,(v).view.frame.size.width,(v).view.frame.size.height)

#import <UIKit/UIKit.h>
#import <OpenGLES/ES2/glext.h>
#import <AVFoundation/AVFoundation.h>
#import "GLApp.h"
#include "Include.h"
#import "GLViewController.h"

#ifdef ENABLE_FACEBOOK
#import "FacebookUploadDialog.h"
#endif

#ifdef ENABLE_TWITTER
#import "TwitterUploadDialog.h"
#endif

#import "GameCenterScreen.h"
#import "StoreScreen.h"

#import "OCInlets.h"
#import "OCOutlets.h"
#import "XML.h"

enum
{
    ROOT_DIR_LEFT,
    ROOT_DIR_RIGHT,
    ROOT_DIR_UP,
    ROOT_DIR_DOWN
};

@interface RootBase : UIViewController

<AVAudioPlayerDelegate,
UIAccelerometerDelegate> {
	AVAudioPlayer							*musicPlayer;
	
	GLViewController						*glViewController;
    UIViewController						*glOverlay;
	
	UIViewController						*currentViewController;
    UIViewController						*previousViewController;
    UIViewController                        *nextViewController;
    
    UIView                                  *bannerBlackBar;
    
    NSTimer                                 *globalTimer;
    NSTimeInterval                          globalInterval;
    List                                    mUpdateList;
    
	UIInterfaceOrientation					currentOrientation;
    
	BOOL									iAdsVisible;
    
	BOOL									admobVisible;
	
	BOOL									disableAllAds;
	BOOL									allAdsDisabled;
    
    BOOL                                    ignoreAnimations;
    
    int                                     animationDirection;
    int                                     animationDirectionDefault;
    
    BOOL                                    isAnimating;
    BOOL                                    loopMusic;
    
    BOOL                                    disablePopoverPinchClose;
    
    GameCenterScreen                        *gameCenter;
    
    StoreScreen                             *storeScreen;
    
#ifdef ENABLE_FACEBOOK
    FacebookUploadDialog                    *facebookUploadDialog;
#endif
    
#ifdef ENABLE_TWITTER
    TwitterUploadDialog                     *twitterUploadDialog;
#endif
    
}

@property (nonatomic, assign) BOOL loopMusic;
@property (nonatomic, assign) BOOL isAnimating;

@property (nonatomic, assign) UIInterfaceOrientation currentOrientation;

@property (nonatomic, retain) UIViewController *nextViewController;
@property (nonatomic, retain) UIViewController *currentViewController;
@property (nonatomic, retain) UIViewController *previousViewController;

@property (nonatomic, retain) UIViewController *popupCurrent;
@property (nonatomic, retain) UIViewController *popupPrevious;

@property (nonatomic, retain) UIView *bannerBlackBar;

@property (nonatomic, retain) GameCenterScreen *gameCenter;
@property (nonatomic, retain) StoreScreen *storeScreen;

@property (nonatomic, retain) GLViewController *glViewController;

@property (nonatomic, retain) UIViewController *glOverlay;


@property (nonatomic, retain) NSTimer *admobTimer;
@property (nonatomic, assign) NSTimeInterval admobInterval;

@property (nonatomic, retain) AVAudioPlayer *musicPlayer;

@property (nonatomic, assign) BOOL iAdsVisible;
@property (nonatomic, assign) BOOL admobVisible;

@property (nonatomic, assign) BOOL disableAllAds;
@property (nonatomic, assign) BOOL allAdsDisabled;

@property (nonatomic, assign) BOOL ignoreAnimations;

@property (nonatomic, assign) BOOL disablePopoverPinchClose;

- (void)purchaseSuccessful:(NSString*)targetString;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;

- (void)startAnimation;
- (void)stopAnimation;

- (void)killPopupAnimated;

#ifdef ENABLE_FACEBOOK
@property (nonatomic, retain) FacebookUploadDialog *facebookUploadDialog;

#endif

#ifdef ENABLE_TWITTER
@property (nonatomic, retain) TwitterUploadDialog *twitterUploadDialog;
#endif

- (void)adWasRefreshed;

- (void)fakeAdClicked;
- (void)refreshAllAds;
- (void)killAllAds;

- (void)playMusic:(NSString*)path withDelegate:(id)del;
- (void)playMusic:(NSString*)path;
- (void)killMusic;
- (void)setMusicVolume:(float)volume;

- (void)enterBackground;
- (void)enterForeground;

- (void)animationComplete;

- (UIViewController*)fetchViewForAction:(NSString*)targetAction;
- (void)action:(NSString*)targetAction;

- (UIImage*)loadImage:(NSString*)targetImagePath;

- (void)pushTo:(UIViewController*)targetViewController;
- (void)pushTo:(UIViewController*)targetViewController withDirection:(int)targetDirection;
- (void)setDirection:(int)targetDirection;
- (void)setDirectionLeft;
- (void)setDirectionRight;
- (void)setDirectionUp;
- (void)setDirectionDown;

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)sendViewTo:(UIView*)targetView direction:(int)targetDirection;
- (void)sendViewFrom:(UIView*)targetView direction:(int)targetDirection;

- (void)showPopupAnimated:(UIViewController*)targetViewController withRect:(CGRect)targetRectangle;
- (void)showPopup:(UIViewController*)targetViewController;
- (void)showPopoverImage:(NSString*)targetPath withRect:(CGRect)targetRectangle;
- (void)killPopup;

- (NSMutableArray*)getFileSequence:(NSString*)targetPrefix withExtension:(NSString*)targetExtension;

- (void)globalUpdate;
- (void)addGlobalUpdate:(NSObject*)targetObject;
- (void)removeGlobalUpdate:(NSObject*)targetObject;

- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context;

- (NSMutableArray*)getFileSequence:(NSString*)targetPrefix withExtension:(NSString*)targetExtension;

- (void)startAccelerometer;
- (void)startAccelerometerWithInterval:(NSTimeInterval)targetInterval;
- (void)startGlobalUpdate;

- (void)go;
- (void)begin;

- (void)facebookGo:(UIImage*)targetImage withCaption:(NSString*)targetCaption;
- (void)facebookGoVideo:(NSString*)targetPath withCaption:(NSString*)targetCaption;
- (void)facebookKill;

- (void)twitterGo:(UIImage*)targetImage withCaption:(NSString*)targetCaption;
- (void)twitterGoData:(NSString*)targetPath withCaption:(NSString*)targetCaption;
- (void)twitterGoVideo:(NSString*)targetPath withCaption:(NSString*)targetCaption;
- (void)twitterKill;

@end

extern RootBase *gRootBase;
extern GameCenterScreen *gGameCenter;
extern StoreScreen *gStore;




