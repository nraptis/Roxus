//
//  AppDelegate.m
//  Gnome
//
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Include.h"
#import "AppDelegate.h"
#import "OCInlets.h"
#import "OCOutlets.h"
#import "GLViewController.h"


AppDelegate *gDel;
GLViewController *gGLViewController;

@implementation AppDelegate

@synthesize window;
@synthesize root;

@synthesize gameCenterScreen;



- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	gDel = self;
    
    UIScreen* mainscr = [UIScreen mainScreen];
    
    int aWidth = mainscr.bounds.size.width;
    int aHeight = mainscr.bounds.size.height;
    
    int aModeWidth = mainscr.currentMode.size.width;
    int aModeHeight = mainscr.currentMode.size.height;
    
    //NSLog(@"Screen Size Original[%d %d] [%d %d]", aWidth, aHeight, aModeWidth, aModeHeight);
    
    if(aModeWidth > aWidth)gDoubleRez = true;
    else gDoubleRez = false;
    
    
    if((aWidth == 1024)  || (aHeight == 1024))
    {
        gGlobalScale=2.0f;
        gIsIpad=true;
    }
    else
    {
        gGlobalScale=1.0f;
        gIsIpad=false;
    }
    
#ifdef LANDSCAPE_MODE
    
    gAppWidth = aHeight;
    gAppHeight = aWidth;
    
#else
    
    gAppWidth = aWidth;
    gAppHeight = aHeight;
    
#endif
    
    
    
    gAppWidth2 = ((float)gAppWidth/2.0f);
    gAppHeight2 = ((float)gAppHeight/2.0f);
    
    //NSLog(@"App Size  [%d %d] [%f %f]", gAppWidth, gAppHeight, gAppWidth2, gAppHeight2);
    
    gApp = new GLApp();
    
	gApp->Initialize();
    gApp->LoadStatic();
    
    /*
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    
    Root *aRoot = [[Root alloc] initWithNibName:nil bundle:nil];
    self.window.rootViewController = aRoot;
    
    //[self.window addSubview:aRoot.view];
    //self.window.frame = CGRectMake(0,0,gAppWidth,gAppHeight);
    
    [self.window makeKeyAndVisible];
    */
    
    
    //CGRect aBounds = [[UIScreen mainScreen] bounds];
    //float aScreenWidth=aBounds.size.width;
    //float aScreenHeight=aBounds.size.height;
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    gGLViewController = [[GLViewController alloc] initWithNibName:nil bundle:nil];
    gGLViewController.updateInterval = 1 / 60.0f;
    [gGLViewController stopAnimation];
    
    self.root = [[Root alloc] initWithNibName:nil bundle:nil];
    
    self.window.rootViewController = root;
    
    [root go];
    
    [self.window makeKeyAndVisible];
    
    [root begin];
    
    root.view.frame = CGRectMake(0.0f, 0.0f, aWidth, aHeight);
    gGLViewController.view.frame = CGRectMake(0.0f, 0.0f, gAppWidth, gAppHeight);
    gGLView.frame = CGRectMake(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    //self.window.clipsToBounds = YES;
    //self.window.frame = CGRectMake(0,0,480,320);
    //self.window.backgroundColor = [UIColor colorWithRed:0.25f green:0.88f blue:0.55f alpha:1.0f];
    //root.view.frame = CGRectMake(0,0, gAppWidth, gAppHeight);
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{    
    [gRoot enterBackground];
	//[self stopAnimation];
}

- (void)enterForeground
{
    [gRoot enterForeground];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    
	[gRoot enterForeground];
    
    //GAPP->
    
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[gRoot enterBackground];
}



- (NSMutableArray*)fetchOrderedFiles:(NSString*)basePath ofType:(NSString*)fileType
{
	NSMutableArray *aArray = [[NSMutableArray alloc] init];
	int aIndex = 0;
	while(true)
	{
		NSString *aFileName = [[NSString alloc] initWithFormat:@"%@%d", basePath, aIndex];
		NSString *aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
        
		if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
		{
			[aArray addObject:aCheckPath];
		}
		else
		{
			aFileName = [[NSString alloc] initWithFormat:@"%@0%d", basePath, aIndex];
			aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
			
			if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
			{
				[aArray addObject:aCheckPath];
			}
			else
			{
                
				aFileName = [[NSString alloc] initWithFormat:@"%@00%d", basePath, aIndex];
				aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
                
				if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
				{
					[aArray addObject:aCheckPath];
				}
				else
				{
					if(aIndex!=0)
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

- (void)dealloc
{
    
}


- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
#ifdef ENABLE_FACEBOOK
    // attempt to extract a token from the url
    return [FBSession.activeSession handleOpenURL:url];
#endif
    return NO;
}



- (void)gameCenterShow:(BOOL)targetLeaderboardMode
{
    if(gameCenterScreen==nil)
    {
        gameCenterScreen=[[GameCenterScreen alloc] initWithNibName:nil bundle:nil];
    }
    
    if(gameCenterScreen.view.superview == nil)
    {
        [gRoot.view addSubview:gameCenterScreen.view];
    }
    
    [gRoot.view bringSubviewToFront:gameCenterScreen.view];
    
}

- (void)gameCenterHide
{
    if(gameCenterScreen)
    {
        if(gameCenterScreen.view.superview)
        {
            [gameCenterScreen.view removeFromSuperview];
        }
    }
}



- (NSMutableArray*)loadFileSequence:(NSString*)basePath
{
    NSMutableArray *aReturn = [[NSMutableArray alloc] init];
    if([aReturn count] <= 0)[self loadFileSequence:basePath ofType:@"jpg" withArray:aReturn];
    if([aReturn count] <= 0)[self loadFileSequence:basePath ofType:@"png" withArray:aReturn];
    if([aReturn count] <= 0)[self loadFileSequence:basePath ofType:@"jpeg" withArray:aReturn];
    if([aReturn count] <= 0)[self loadFileSequence:basePath ofType:@"JPG" withArray:aReturn];
    if([aReturn count] <= 0)[self loadFileSequence:basePath ofType:@"PNG" withArray:aReturn];
    if([aReturn count] <= 0)[self loadFileSequence:basePath ofType:@"JPEG" withArray:aReturn];
    return aReturn;
}

- (void)loadFileSequence:(NSString*) basePath ofType:(NSString*)fileType withArray:(NSMutableArray *)targetArray
{
	int aIndex = 0;
    
	while(true)
	{
		NSString *aFileName = [[NSString alloc] initWithFormat:@"%@%d", basePath, aIndex];
		NSString *aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
        
		if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
		{
			[targetArray addObject:aCheckPath];
		}
		else
		{
			aFileName = [[NSString alloc] initWithFormat:@"%@0%d", basePath, aIndex];
			aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
			if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
			{
				[targetArray addObject:aCheckPath];
			}
			else
			{
				aFileName = [[NSString alloc] initWithFormat:@"%@00%d", basePath, aIndex];
				aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
				
				if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
				{
					[targetArray addObject:aCheckPath];
				}
				else
				{
                    if(aIndex > 4)
                    {
                        if(aIndex!=0)
                        {
                            break;
                        }
                    }
				}
			}
		}
		aIndex++;
	}
    
    NSMutableArray *aNewArray = [[NSMutableArray alloc] init];
    
    for(NSString *aTempPath in targetArray)
    {
        FString aChopString = [aTempPath UTF8String];
        aChopString.RemovePath(false);
        NSString *aNewString = [NSString stringWithUTF8String:aChopString.c()];
        [aNewArray addObject:aNewString];
    }
    
    [targetArray removeAllObjects];
    
    for(NSString *aTempPath in aNewArray)
    {
        [targetArray addObject:aTempPath];
    }
}

@end
