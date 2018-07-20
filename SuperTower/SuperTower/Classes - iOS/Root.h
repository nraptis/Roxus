#define TEST_MODE 1
//#undef TEST_MODE

#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <UIKit/UIKit.h>

#import "RootBase.h"

@interface Root : RootBase <UINavigationControllerDelegate>
{
    
}

- (void)setupPass1:(CGRect)pFrame;
- (void)setupPass2:(BOOL)pTablet withOS:(float)pOSVersion;

- (void)setupFinalize;
- (void)globalUpdate;

- (void)pushTo:(UIViewController *)pViewController animated:(BOOL)pAnimated;
- (void)pushReverse:(UIViewController *)pViewController animated:(BOOL)pAnimated;

- (void)appPause;
- (void)appResume;

- (void)enterBackground;
- (void)enterForeground;

@end

extern Root *gRoot;











