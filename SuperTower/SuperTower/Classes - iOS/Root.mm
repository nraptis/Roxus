//
//  Root.m
//  LeadGenerationApp
//
//  Created by Nicholas Raptis on 8/19/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#import "Root.h"
#import "GLApp.h"

Root *gRoot;


@implementation Root

- (id)init {
    gRoot = self;
    self = [super init];
    return self;
}

- (id) initWithCoder:(NSCoder *)aDecoder {
    gRoot = self;
    self = [super initWithCoder:aDecoder];
    return self;
}
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    gRoot = self;
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)setupPass1:(CGRect)pFrame {
    [super setupPass1:pFrame];
    gAppBase = new GLApp();
    [self setupOpenGL];
}

- (void)setupPass2:(BOOL)pTablet withOS:(float)pOSVersion {
    [super setupPass2:pTablet withOS:pOSVersion];
}

- (void)setupFinalize {
    [super setupFinalize];
    [self pushTo:glViewController animated:NO];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)globalUpdate
{
    
}

+ (BOOL)isSubstringI:(NSString *)pString withSearchWord:(NSString *)pSearchString
{
    BOOL aReturn = NO;
    if((pString != nil) && (pSearchString != nil))
    {
        NSRange aRange = [pString rangeOfString:pSearchString options:NSCaseInsensitiveSearch];
        if(aRange.length > 0)aReturn = YES;
    }
    return aReturn;
}

- (BOOL)pushDestroysViewController:(UIViewController *)pViewController {
    if(pViewController == self)return NO;
    return [super pushDestroysViewController:pViewController];
}


- (void)pushTo:(UIViewController *)pViewController animated:(BOOL)pAnimated {
    [super pushTo:pViewController animated:pAnimated];
}

- (void)pushReverse:(UIViewController *)pViewController animated:(BOOL)pAnimated {
    [super pushReverse:pViewController animated:pAnimated];
}

- (void)appPause
{
    [gGLViewController stopAnimation];
}

- (void)appResume
{
    [gGLViewController startAnimation];
}

- (void)enterBackground
{
    [super enterBackground];
}

- (void)enterForeground
{
    [super enterForeground];
}

@end
