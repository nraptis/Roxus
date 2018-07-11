//
//  AppDelegate.m
//  LeadGenerationApp
//
//  Created by Nicholas Raptis on 8/19/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#import "AppDelegate.h"
#import "core_app_shell.h"

@implementation AppDelegate

@synthesize rootViewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [[UIApplication sharedApplication] setStatusBarHidden:YES];

    float aOSVersion = [[[UIDevice currentDevice] systemVersion] floatValue];
    bool aIsTablet = false;
    
    int aWidth = [UIScreen mainScreen]. bounds.size.width;
    int aHeight = [UIScreen mainScreen].bounds.size.height;
    
    //float aScreenScale = [mainscr scale];
    
    if((aWidth >= 1000)  || (aHeight >= 1000))
    {
        aIsTablet = true;
        gIsLargeScreen=true;
        gIsRetina = false;
    }
    else
    {
        gIsLargeScreen=false;
        gIsRetina = true;
    }
    
    
    
    float aAppWidth = aWidth;
    float aAppHeight = aHeight;
    
#ifdef LANDSCAPE_MODE
    aAppWidth  = aHeight;
    aAppHeight = aWidth;
#else
    
#endif
    
    if(aOSVersion >= 8.0)
    {
#ifdef LANDSCAPE_MODE
        int aHold = aAppWidth;
        aAppWidth = aAppHeight;
        aAppHeight = aHold;
#endif
    }
    

    FString aPathBundle;
    char aCharPath[1024];
    memset(aCharPath, 0, sizeof(aCharPath));
    
    CFURLRef aResourceURL = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef aStringRef = CFURLCopyFileSystemPath(aResourceURL, kCFURLPOSIXPathStyle);
    CFRelease(aResourceURL);
    CFStringGetCString(aStringRef,aCharPath,FILENAME_MAX,kCFStringEncodingASCII);
    CFRelease(aStringRef);
    aPathBundle = aCharPath;
    aPathBundle += "/";
    
    FString aPathDocuments;
    NSArray *aPathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *aDocumentDirectory = [aPathArray objectAtIndex:0];
    aPathDocuments = [aDocumentDirectory UTF8String];
    aPathDocuments += "/";
    
    AppShellInitialize(ENV_IPHONE);
    
    AppShellSetDeviceSize(aAppWidth, aAppHeight);
    AppShellSetVirtualFrame(0, 0, aAppWidth, aAppHeight);
    
    AppShellSetDirectoryBundle(aPathBundle.c());
    AppShellSetDirectoryDocuments(aPathDocuments.c());
    AppShellSetOSVersion(gOSVersion);
    AppShellSetAdBannerHeight(0.0f);
    
    
    //UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    //UIViewController *vc = [mainStoryboard instantiateViewControllerWithIdentifier:@"root"];
    
    //UIViewController *vc = [mainStoryboard instantiateInitialViewController];
    self.rootViewController = [[Root alloc] init];
    
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.rootViewController = rootViewController;
    [self.window makeKeyAndVisible];
    
    [rootViewController setupPass1:CGRectMake(0.0f, 0.0f, aAppWidth, aAppHeight)];
    [NSThread sleepForTimeInterval:0.1];
    
    [rootViewController setupPass2:aIsTablet withOS:aOSVersion];
    [NSThread sleepForTimeInterval:0.1];
    
    
    AppShellLoad();
    AppShellSetVirtualFrame(0, 0, aAppWidth, aAppHeight);
    AppShellSetDeviceSize(aAppWidth, aAppHeight);
    AppShellLoadComplete();
    
    [rootViewController setupPass3];
    
    [NSThread sleepForTimeInterval:0.1];
    [rootViewController setupFinalize];
    
    [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    [rootViewController enterBackground];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    [rootViewController enterBackground];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [rootViewController enterForeground];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [rootViewController enterForeground];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [rootViewController enterBackground];
}

@end
