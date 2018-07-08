//
//  GameCenterScreen.m
//  CrazyDarts
//
//  Created by Nick Raptis on 10/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GameCenterScreen.h"
#import "Root.h"
#import "Root.h"
#import "GLApp.h"
#import "Achievement.h"


@implementation GameCenterScreen


@synthesize modeLeaderboard;
@synthesize modeAchievements;

@synthesize isConnected;
@synthesize isConnecting;

@synthesize shouldShowLeaderboard;
@synthesize shouldShowAchievements;

@synthesize showLeaderboardName;

@synthesize didFail;

@synthesize gcLocalPlayer;

@synthesize gcViewControllerAchievements;
@synthesize gcViewControllerLeaderboard;

@synthesize isShowingLeaderboard;
@synthesize isShowingAchievements;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    isConnected=FALSE;
    isConnecting=FALSE;
    
    modeLeaderboard=NO;
    modeAchievements=NO;
    
    shouldShowLeaderboard=NO;
    shouldShowAchievements=NO;
    
    isShowingLeaderboard=NO;
    isShowingAchievements=NO;
    
    didFail=FALSE;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    self.view.frame=CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    return self;
}

- (void)dealloc
{
    
}

- (void)didReceiveMemoryWarning
{
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //[self signIn];
}

- (void)signIn
{
    
    isConnecting=YES;
    
    didFail=FALSE;
    
    if(self.gcLocalPlayer)
    {
        if(self.gcLocalPlayer.authenticated)
        {
            isConnected=YES;
            isConnecting=NO;
            
            [self signInSuccess];
            return;
        }
    }
    
    self.gcLocalPlayer = [GKLocalPlayer localPlayer];
    [self.gcLocalPlayer authenticateWithCompletionHandler:^(NSError *error)
    {
         
         isConnecting=NO;
         
         if(self.gcLocalPlayer.isAuthenticated)
         {
             [self signInSuccess];
         }
         else
         {
             [self signInFail];
         }
     }];
}

- (void)signInSuccess
{
    isConnecting = NO;
    isConnected = YES;
    
    [self submitScore:@"bb_scores" withScore:GAPP->mHSList.GetHighestScore()];
    
    [self syncAchievements];
    
    //NSLog(@"Sign-In Success!");
    //NSLog(@"Leader: %d  Ach: %d", shouldShowLeaderboard, shouldShowAchievements);
    
    if(shouldShowLeaderboard && showLeaderboardName)
    {
        [self showLeaderboard:showLeaderboardName];
    }
    else if(shouldShowAchievements)
    {
        [self showAchievements];
    }
}

- (void)signInFail
{
    isConnected=NO;
    didFail=YES;
    isConnecting=NO;
}

- (void)showLeaderboard:(NSString*)targetLeaderboardName
{
    self.showLeaderboardName = [[NSString alloc] initWithString:targetLeaderboardName];
    
    modeLeaderboard=YES;
    modeAchievements=NO;
    
    BOOL aFail=YES;
    if(self.gcLocalPlayer)
    {
        if(self.gcLocalPlayer.authenticated)
        {
            self.gcViewControllerLeaderboard = [[GKLeaderboardViewController alloc] init];
            if(self.gcViewControllerLeaderboard != nil)
            {
                isShowingLeaderboard=YES;
                isShowingAchievements=NO;
                shouldShowLeaderboard=NO;
                aFail=NO;
                self.gcViewControllerLeaderboard.leaderboardDelegate = self;
                [gRoot presentModalViewController:self.gcViewControllerLeaderboard animated:YES];
            }
        }
    }
    
    if(aFail)
    {
        isConnected=FALSE;
        shouldShowLeaderboard=YES;
        [self signIn];
    }
}

- (void)showAchievements
{
    modeLeaderboard=NO;
    modeAchievements=YES;
    
    
    BOOL aFail=YES;
    if(self.gcLocalPlayer)
    {
        if(self.gcLocalPlayer.authenticated)
        {
            self.gcViewControllerAchievements = [[GKAchievementViewController alloc] init];
            if(self.gcViewControllerAchievements != nil)
            {
                shouldShowAchievements=NO;
                aFail=NO;
                self.gcViewControllerAchievements.achievementDelegate = self;
                isShowingLeaderboard=NO;
                isShowingAchievements=YES;
                [gRoot presentModalViewController:gcViewControllerAchievements animated:YES];
            }
        }
    }
    
    if(aFail)
    {
        isConnected=FALSE;
        shouldShowAchievements=YES;
        [self signIn];
    }
}


- (void)submitScore:(NSString*)targetLeaderboard withScore:(int)targetScore
{
    GKScore *scoreReporter = [[GKScore alloc] initWithCategory:targetLeaderboard];
    scoreReporter.value = targetScore;
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error)
     {
         if(error != nil)
         {
             NSLog(@"Score Submitted Failure [%d Points]!", targetScore);
             NSLog(@"[%@]", error);
             
         }
         else
         {
             NSLog(@"Score Submitted Successfully [%d Points]!", targetScore);
         }
         
     }];
}

- (void)submitAchievement:(NSString*)targetAcievementName withPercent:(float)targetPercent
{
    GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier:targetAcievementName];
    if(achievement)
    {
		achievement.percentComplete = targetPercent;
		[achievement reportAchievementWithCompletionHandler:^(NSError *error)
		 {
			 if(error != nil)
			 {
                 //NSLog(@"Achievement Couldn't Save [ %@ ]", targetAcievementName);
			 }
			 else
			 {
                 //NSLog(@"Achievement Saved[ %@ ]", targetAcievementName);
			 }
		 }];
    }
}

- (void)syncAchievements
{
    
    EnumList(AchievementGroup, aGroup, GAPP->mAchievementManager.mAchievementGroupList)
    {
        EnumList(Achievement, aAchievement, aGroup->mAchievementList)
        {
            float aPercent = 0.0f;
            
            if(aAchievement->mComplete)
            {
                aPercent = 1.0f;
            }
            else
            {
                if(aAchievement->mProgressMax > 0)
                {
                    aPercent = (float)aAchievement->mProgress / (float)aAchievement->mProgressMax;
                }
            }
            if(aPercent > 1.0f)aPercent = 1.0f;
            if(aPercent < 0.0f)aPercent = 0.0f;
            
            aPercent *= 100.0f;
            
            NSString *aName = [NSString stringWithUTF8String:aAchievement->mName.c()];
            
            //NSLog(@"Synchronizing Achievement: [%@] (%f Percent)", aName, (aPercent * 100.0f));
            
            [self submitAchievement:aName withPercent:aPercent];
        }
    }
    
    /*
    Achievement *aAchievement;
    if(GAPP)
    {
        for(int i=0;i<GAPP->mAchievementManager.mCount;i++)
        {
            aAchievement = GAPP->mAchievementManager.mAchievement[i];
            if(aAchievement)
            {
                NSLog(@"Looking At Achievement: %s [%d / %d]", aAchievement->mName.c(), aAchievement->mProgress, aAchievement->mProgressMax);
            }
        }
    }
    */
    
    /*
    EnumList(Achievement, aAchievement, GAPP->mAchievementManager.mList)
    {
        float aPercent = 0;
        if(aAchievement->mComplete)
        {
            //aPercent = 
        }
        
        [self submitAchievement:[NSString stringWithUTF8String:aAchievement->mName.c()] withPercent:aPercent];
    }
    */
    
    [self requestAchievements];
}

- (void)requestAchievements
{
    [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray *achievements, NSError *error)
     {
         //NSLog(@"loadAchievementsWithCompletionHandler Done...");
         //NSLog(@"Error[%@]", error);
         if(error == nil)
         {
             Achievement *aAch=0;
             if(achievements != nil)
             {
                 for(GKAchievement *aGKAch in achievements)
                 {
                     NSString *aAchievementName = nil;
                     if(aGKAch.identifier != nil)
                     {
                         FString aString = [aGKAch.identifier UTF8String];
                         aAch = gApp->mAchievementManager.GetAchievement(aString.c());
                         
                         if(aAch)
                         {
                             
                             NSLog(@"[%@] = %f%%", aGKAch.identifier, aGKAch.percentComplete);
                             int aProgress = (aGKAch.percentComplete / 99.99f) * (float)aAch->mProgressMax;
                             if(aProgress > aAch->mProgress && aAch->mComplete == false)
                             {
                                 aAch->mProgress=aProgress;
                                 if(aAch->mProgress<0)aAch->mProgress=0;
                                 if(aAch->mProgress>aAch->mProgressMax)aAch->mProgress=aAch->mProgressMax;
                                 aAch->mProgressSaved=aAch->mProgress;
                                 
                                 if(aAch->mProgress>=aAch->mProgressMax)
                                 {
                                     //NSLog(@"Adding New Completer [%s]", aAch->mName.c());
                                     GAPP->mRecentAchievements += aAch;
                                 }
                             }
                         }
                     }
                 }
             }
             GAPP->SaveStatic();
             
             
             if(GAPP)
             {
                 
                 /*
                 for(int i=0;i<GAPP->mAchievementManager.mListSize;i++)
                 {
                     aAch = GAPP->mAchievementManager.mList[i];
                     if(aAch)
                     {
                         float aPercent = (float)aAch->mProgress / (float)aAch->mProgressMax;
                         if(aPercent < 0)aPercent = 0;
                         if(aPercent > 1)aPercent = 1;
                         
                         aPercent *= 100.0f;
                         
                         [self submitAchievement:[NSString stringWithUTF8String:aAch->mName.c()] withPercent:aPercent];
                         
                         //NSLog(@"Looking At Achievement: %s [%d / %d]", aAch->mName.c(), aAch->mProgress, aAch->mProgressMax);
                         
                     }
                 }
                */
                 
             }             
         }
     }];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

- (void)achievementViewControllerDidFinish:(GKAchievementViewController*)viewController
{
    [gRoot dismissModalViewControllerAnimated:YES];
    isShowingLeaderboard=NO;
    isShowingAchievements=NO;
    //viewControllerAchievements=nil;
    self.gcViewControllerAchievements = nil;
    if(GAPP)GAPP->Message("gc_complete",0);
}

- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController*)viewController
{
    [gRoot dismissModalViewControllerAnimated:YES];
    isShowingLeaderboard=NO;
    isShowingAchievements=NO;
    self.gcViewControllerLeaderboard = nil;
    if(GAPP)GAPP->Message("gc_complete",0);
}

@end
