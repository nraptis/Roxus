//
//  GameCenterScreen.h
//  CrazyDarts
//
//  Created by Nick Raptis on 10/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <GameKit/GameKit.h>

@interface GameCenterScreen : UIViewController<GKAchievementViewControllerDelegate, GKLeaderboardViewControllerDelegate>
{    
    GKAchievementViewController                 *gcViewControllerAchievements;
    GKLeaderboardViewController                 *gcViewControllerLeaderboard;
    
    GKLocalPlayer                               *gcLocalPlayer;
    
    BOOL                                        isConnected;
    BOOL                                        isConnecting;
    
    BOOL                                        didFail;
    
    BOOL                                        gcLeaderboardRequested;
    BOOL                                        gcLeaderboardResponded;
    BOOL                                        gcLeaderboardSuccess;
    
    BOOL                                        isShowingLeaderboard;
    BOOL                                        isShowingAchievements;
    
    BOOL                                        modeLeaderboard;
    BOOL                                        modeAchievements;
    
    NSString                                    *showLeaderboardName;
    
    BOOL                                        shouldShowLeaderboard;
    BOOL                                        shouldShowAchievements;
}

@property (nonatomic, assign) BOOL modeLeaderboard;
@property (nonatomic, assign) BOOL modeAchievements;

@property (nonatomic, assign) BOOL isConnected;
@property (nonatomic, assign) BOOL isConnecting;

@property (nonatomic, assign) BOOL shouldShowLeaderboard;
@property (nonatomic, assign) BOOL shouldShowAchievements;

@property (nonatomic, assign) BOOL isShowingLeaderboard;
@property (nonatomic, assign) BOOL isShowingAchievements;

@property (nonatomic, retain) NSString *showLeaderboardName;

@property (nonatomic, assign) BOOL didFail;

@property (nonatomic, retain) GKAchievementViewController *gcViewControllerAchievements;
@property (nonatomic, retain) GKLeaderboardViewController *gcViewControllerLeaderboard;

@property (nonatomic, retain) GKLocalPlayer *gcLocalPlayer;

- (void)submitAchievement:(NSString*)targetAcievementName withPercent:(float)targetPercent;
- (void)requestAchievements;

- (void)syncAchievements;

- (void)signIn;
- (void)signInSuccess;
- (void)signInFail;

- (void)showLeaderboard:(NSString*)targetLeaderboardName;
- (void)showAchievements;

- (void)submitScore:(NSString*)targetLeaderboard withScore:(int)targetScore;

- (void)achievementViewControllerDidFinish:(GKAchievementViewController*)viewController;
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController*)viewController;

@end
