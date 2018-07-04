//
//  EditorMenuTiles.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EditorMenuTiles : UIViewController
{
    UIButton                        *buttonTileRandom;
    
    UIButton                        *buttonTile1;
    UIButton                        *buttonTile2;
    UIButton                        *buttonTile3;
    UIButton                        *buttonTile4;
    UIButton                        *buttonTile5;
    UIButton                        *buttonTile6;
    
    UIButton                        *buttonAccBlank;
    UIButton                        *buttonAcc1;
    UIButton                        *buttonAcc2;
    UIButton                        *buttonAcc3;
    UIButton                        *buttonAcc4;
    UIButton                        *buttonAcc5;
    UIButton                        *buttonAcc6;
    UIButton                        *buttonAccRandom;
    
    UIButton                        *buttonRock;
    UIButton                        *buttonDirt;
    UIButton                        *buttonColorRock;
    UIButton                        *buttonHardRock;
    UIButton                        *buttonMetal;
    UIButton                        *buttonEnergy;
    UIButton                        *buttonDelete;
    
    UIButton                        *buttonPowerup1;
    UIButton                        *buttonPowerup2;
    UIButton                        *buttonPowerup3;
    UIButton                        *buttonPowerup4;
    UIButton                        *buttonPowerup5;
    UIButton                        *buttonPowerup6;
    UIButton                        *buttonPowerup7;
    UIButton                        *buttonPowerupRandomSmall;
    UIButton                        *buttonPowerupRandomBig;
    
    UIButton                        *buttonTreasure1;
    UIButton                        *buttonTreasure2;
    UIButton                        *buttonTreasure3;
    UIButton                        *buttonTreasure4;
    UIButton                        *buttonTreasure5;
    UIButton                        *buttonTreasure6;
    UIButton                        *buttonTreasureRandomSmall;
    UIButton                        *buttonTreasureRandomBig;
    
    UIButton                        *buttonRelic1;
    UIButton                        *buttonRelic2;
    UIButton                        *buttonRelic3;
    
    UIButton                        *buttonLevelStar1;
    UIButton                        *buttonLevelStar2;
    UIButton                        *buttonLevelStar3;
    
}

@property (nonatomic, strong) IBOutlet UIButton *buttonTileRandom;

@property (nonatomic, strong) IBOutlet UIButton *buttonTile1;
@property (nonatomic, strong) IBOutlet UIButton *buttonTile2;
@property (nonatomic, strong) IBOutlet UIButton *buttonTile3;
@property (nonatomic, strong) IBOutlet UIButton *buttonTile4;
@property (nonatomic, strong) IBOutlet UIButton *buttonTile5;
@property (nonatomic, strong) IBOutlet UIButton *buttonTile6;

@property (nonatomic, strong) IBOutlet UIButton *buttonRock;
@property (nonatomic, strong) IBOutlet UIButton *buttonDirt;
@property (nonatomic, strong) IBOutlet UIButton *buttonColorRock;
@property (nonatomic, strong) IBOutlet UIButton *buttonHardRock;
@property (nonatomic, strong) IBOutlet UIButton *buttonMetal;
@property (nonatomic, strong) IBOutlet UIButton *buttonEnergy;
@property (nonatomic, strong) IBOutlet UIButton *buttonDelete;

@property (nonatomic, strong) IBOutlet UIButton *buttonAccBlank;
@property (nonatomic, strong) IBOutlet UIButton *buttonAcc1;
@property (nonatomic, strong) IBOutlet UIButton *buttonAcc2;
@property (nonatomic, strong) IBOutlet UIButton *buttonAcc3;
@property (nonatomic, strong) IBOutlet UIButton *buttonAcc4;
@property (nonatomic, strong) IBOutlet UIButton *buttonAcc5;
@property (nonatomic, strong) IBOutlet UIButton *buttonAcc6;
@property (nonatomic, strong) IBOutlet UIButton *buttonAccRandom;



@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup1;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup2;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup3;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup4;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup5;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup6;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerup7;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerupRandomSmall;
@property (nonatomic, strong) IBOutlet UIButton *buttonPowerupRandomBig;

@property (nonatomic, strong) IBOutlet UIButton *buttonTreasure1;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasure2;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasure3;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasure4;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasure5;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasure6;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasureRandomSmall;
@property (nonatomic, strong) IBOutlet UIButton *buttonTreasureRandomBig;

@property (nonatomic, strong) IBOutlet UIButton *buttonRelic1;
@property (nonatomic, strong) IBOutlet UIButton *buttonRelic2;
@property (nonatomic, strong) IBOutlet UIButton *buttonRelic3;

@property (nonatomic, strong) IBOutlet UIButton *buttonLevelStar1;
@property (nonatomic, strong) IBOutlet UIButton *buttonLevelStar2;
@property (nonatomic, strong) IBOutlet UIButton *buttonLevelStar3;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)nuke;
- (void)dealloc;

@end
