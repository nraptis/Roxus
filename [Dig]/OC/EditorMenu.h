//
//  EditorMenu.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "EditorBoard.h"
#import "EditorMenuMain.h"
#import "EditorMenuTiles.h"
#import "EditorMenuDepth.h"

#define GTM_TOOL_HEIGHT 64.0f

@interface EditorMenu : UIViewController
{
    UIButton                    *buttonHome;
    UIButton                    *buttonCollapse;
    
    UIButton                    *buttonTopAdd1;
    UIButton                    *buttonTopSub1;
    
    UIButton                    *buttonBottomAdd1;
    UIButton                    *buttonBottomSub1;
    
    UIButton                    *buttonTopBotAddTest;
    
    UIButton                    *buttonSaveImage;
    
    UIButton                    *buttonMenu1;
    UIButton                    *buttonMenu2;
    UIButton                    *buttonMenu3;
    UIButton                    *buttonMenu4;
    UIButton                    *buttonMenu5;
    
    UIView                      *viewToolBar;
    
    UIViewController            *currentMenu;
    UIViewController            *previousMenu;
    
    BOOL                        isCollapsed;
    BOOL                        isDragging;
    
    float                       touchStartX;
    float                       touchStartY;
    
    float                       touchViewX;
    float                       touchViewY;
}


@property (nonatomic, retain) IBOutlet UIButton *buttonHome;
@property (nonatomic, retain) IBOutlet UIButton *buttonCollapse;



@property (nonatomic, retain) IBOutlet UIButton *buttonTopAdd1;
@property (nonatomic, retain) IBOutlet UIButton *buttonTopSub1;

@property (nonatomic, retain) IBOutlet UIButton *buttonBottomAdd1;
@property (nonatomic, retain) IBOutlet UIButton *buttonBottomSub1;

@property (nonatomic, retain) IBOutlet UIButton *buttonTopBotAddTest;





@property (nonatomic, retain) IBOutlet UIButton *buttonSaveImage;

@property (nonatomic, retain) IBOutlet UIButton *buttonMenu1;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenu2;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenu3;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenu4;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenu5;

@property (nonatomic, retain) IBOutlet UIView *viewToolBar;

@property (nonatomic, retain) IBOutlet UIViewController *currentMenu;
@property (nonatomic, retain) IBOutlet UIViewController *previousMenu;

- (void)pushTo:(UIViewController*)targetViewController;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)collapseAnimated:(BOOL)targetAnimated;
- (void)expandAnimated:(BOOL)targetAnimated;

- (void)nuke;
- (void)dealloc;

@end