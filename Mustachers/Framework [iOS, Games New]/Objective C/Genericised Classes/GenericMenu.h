//
//  GenericMenu.h
//  Chrysler300Reloaded
//
//  Created by Nick Raptis on 1/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GenericMenu;

@protocol GenericMenuDelegate <NSObject>

- (void)menuAction:(int)targetAction fromMenu:(GenericMenu*)targetMenu;

@end

@interface GenericMenu : UIViewController
{
    id                              <GenericMenuDelegate>delegateMenu;
    
    UIImageView                     *imageViewMenuBack;
    
    CGRect                          lastClickedRect;
    
    UIButton                        *buttonMenuAction1;
    UIButton                        *buttonMenuAction2;
    UIButton                        *buttonMenuAction3;
    UIButton                        *buttonMenuAction4;
    UIButton                        *buttonMenuAction5;
    UIButton                        *buttonMenuAction6;
    UIButton                        *buttonMenuAction7;
    UIButton                        *buttonMenuAction8;
    UIButton                        *buttonMenuAction9;
    UIButton                        *buttonMenuAction10;
    UIButton                        *buttonMenuAction11;
    UIButton                        *buttonMenuAction12;
    UIButton                        *buttonMenuAction13;
    UIButton                        *buttonMenuAction14;
    UIButton                        *buttonMenuAction15;
    UIButton                        *buttonMenuAction16;
    UIButton                        *buttonMenuAction17;
    UIButton                        *buttonMenuAction18;
    UIButton                        *buttonMenuAction19;
    UIButton                        *buttonMenuAction20;
    UIButton                        *buttonMenuAction21;
    UIButton                        *buttonMenuAction22;
    UIButton                        *buttonMenuAction23;
    UIButton                        *buttonMenuAction24;
    UIButton                        *buttonMenuAction25;
    
    NSMutableArray                  *arrayMenuButtons;
}

@property (nonatomic, retain) id delegateMenu;

@property (nonatomic) CGRect lastClickedRect;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewMenuBack;

@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction1;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction2;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction3;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction4;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction5;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction6;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction7;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction8;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction9;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction10;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction11;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction12;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction13;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction14;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction15;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction16;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction17;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction18;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction19;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction20;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction21;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction22;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction23;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction24;
@property (nonatomic, retain) IBOutlet UIButton *buttonMenuAction25;

@property (nonatomic, retain) NSMutableArray *arrayMenuButtons;

- (IBAction)click:(UIButton*)sender;
- (void)menuAction:(int)targetAction;
- (void)nuke;

@end
