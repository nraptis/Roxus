//
//  EditorMenuTiles.m
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import "EditorMenuTiles.h"
#import "EditorBoard.h"
#import "Root.h"

@implementation EditorMenuTiles

@synthesize buttonTileRandom;

@synthesize buttonTile1;
@synthesize buttonTile2;
@synthesize buttonTile3;
@synthesize buttonTile4;
@synthesize buttonTile5;
@synthesize buttonTile6;

@synthesize buttonRock;
@synthesize buttonDirt;
@synthesize buttonColorRock;
@synthesize buttonHardRock;
@synthesize buttonMetal;
@synthesize buttonEnergy;
@synthesize buttonDelete;

@synthesize buttonAccBlank;
@synthesize buttonAcc1;
@synthesize buttonAcc2;
@synthesize buttonAcc3;
@synthesize buttonAcc4;
@synthesize buttonAcc5;
@synthesize buttonAcc6;
@synthesize buttonAccRandom;

@synthesize buttonPowerup1;
@synthesize buttonPowerup2;
@synthesize buttonPowerup3;
@synthesize buttonPowerup4;
@synthesize buttonPowerup5;
@synthesize buttonPowerup6;
@synthesize buttonPowerup7;
@synthesize buttonPowerupRandomSmall;
@synthesize buttonPowerupRandomBig;

@synthesize buttonTreasure1;
@synthesize buttonTreasure2;
@synthesize buttonTreasure3;
@synthesize buttonTreasure4;
@synthesize buttonTreasure5;
@synthesize buttonTreasure6;
@synthesize buttonTreasureRandomSmall;
@synthesize buttonTreasureRandomBig;

@synthesize buttonRelic1;
@synthesize buttonRelic2;
@synthesize buttonRelic3;

@synthesize buttonLevelStar1;
@synthesize buttonLevelStar2;
@synthesize buttonLevelStar3;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (IBAction)click:(UIButton*)sender
{
    if(sender == buttonTileRandom || sender == buttonTile1 || sender == buttonTile2 || sender == buttonTile3
    || sender == buttonTile4 || sender == buttonTile5 || sender == buttonTile6)
    {
        gEditor->mModeTile = ED_T_M_NORMAL;
        
        if(sender == buttonTileRandom) gEditor->mTileType = -1;
        if(sender == buttonTile1) gEditor->mTileType = 0;
        if(sender == buttonTile2) gEditor->mTileType = 1;
        if(sender == buttonTile3) gEditor->mTileType = 2;
        if(sender == buttonTile4) gEditor->mTileType = 3;
        if(sender == buttonTile5) gEditor->mTileType = 4;
        if(sender == buttonTile6) gEditor->mTileType = 5;
    }
    
    
    if(sender == buttonAccBlank || sender == buttonAccRandom || sender == buttonAcc1 || sender == buttonAcc2
       || sender == buttonAcc3 || sender == buttonAcc4 || sender == buttonAcc5 || sender == buttonAcc6)
    {
        gEditor->mModeTile = ED_T_M_ACCESSORY;
        
        if(sender == buttonAccBlank)gEditor->mAccessoryType = ACC_NONE;
        
        if(sender == buttonAccRandom)gEditor->mAccessoryType = ACC_RANDOM;
        
        if(sender == buttonAcc1)gEditor->mAccessoryType = 1;
        if(sender == buttonAcc2)gEditor->mAccessoryType = 2;
        if(sender == buttonAcc3)gEditor->mAccessoryType = 3;
        if(sender == buttonAcc4)gEditor->mAccessoryType = 4;
        if(sender == buttonAcc5)gEditor->mAccessoryType = 5;
        if(sender == buttonAcc6)gEditor->mAccessoryType = 6;
    }
    
    
    if(sender == buttonRock)
    {
        gEditor->mModeTile = ED_T_M_ROCK;
        
    }
    
    if(sender == buttonDirt)
    {
        gEditor->mModeTile = ED_T_M_DIRT;
        
    }
    
    if(sender == buttonColorRock)
    {
        gEditor->mModeTile = ED_T_M_COLORED_ROCK;
    }
    
    if(sender == buttonHardRock)
    {
        gEditor->mModeTile = ED_T_M_HARD_ROCK;
        
        //buttonHardRock
        
    }
    
    if(sender == buttonMetal)
    {
        gEditor->mModeTile = ED_T_M_METAL;
        
    }
    
    if(sender == buttonEnergy)
    {
        gEditor->mModeTile = ED_T_M_ENERGY;
        
    }
    
    if(sender == buttonDelete)
    {
        gEditor->mModeTile = ED_T_M_ERASER;
    }
    
    
    if(sender == buttonPowerup1 || sender == buttonPowerup2 || sender == buttonPowerup3 || sender == buttonPowerup4
       || sender == buttonPowerup5 || sender == buttonPowerup6 || sender == buttonPowerup7 || sender == buttonPowerupRandomSmall || sender == buttonPowerupRandomBig)
    {
        gEditor->mModeTile = ED_T_M_POWERUP;
        
        if(sender == buttonPowerup1) gEditor->mTileType = 0;
        if(sender == buttonPowerup2) gEditor->mTileType = 1;
        if(sender == buttonPowerup3) gEditor->mTileType = 2;
        if(sender == buttonPowerup4) gEditor->mTileType = 3;
        if(sender == buttonPowerup5) gEditor->mTileType = 4;
        if(sender == buttonPowerup6) gEditor->mTileType = 5;
        if(sender == buttonPowerup7) gEditor->mTileType = 6;
        
        if(sender == buttonPowerupRandomSmall)gEditor->mTileType = POWERUP_RANDOM_SMALL;
        if(sender == buttonPowerupRandomBig)gEditor->mTileType = POWERUP_RANDOM_BIG;
        
        Log("Type = [%d]\n", gEditor->mTileType);
        
    }
    
    if(sender == buttonTreasure1 || sender == buttonTreasure2 || sender == buttonTreasure3 || sender == buttonTreasure4
       || sender == buttonTreasure5 || sender == buttonTreasure6 || sender == buttonTreasureRandomSmall || sender == buttonTreasureRandomBig)
    {
        gEditor->mModeTile = ED_T_M_TREASURE;
        
        if(sender == buttonTreasure1)gEditor->mTileType = 0;
        if(sender == buttonTreasure2)gEditor->mTileType = 1;
        if(sender == buttonTreasure3)gEditor->mTileType = 2;
        if(sender == buttonTreasure4)gEditor->mTileType = 3;
        if(sender == buttonTreasure5)gEditor->mTileType = 4;
        if(sender == buttonTreasure6)gEditor->mTileType = 5;
        
        if(sender == buttonTreasureRandomSmall)
        {
            gEditor->mTileType = TREASURE_RANDOM;
        }
    }
    
    if(sender == buttonLevelStar1 || sender == buttonLevelStar2 || sender == buttonLevelStar3)
    {
        gEditor->mModeTile = ED_T_M_RELIC;
        
        if(sender == buttonLevelStar1)gEditor->mTileType = LEVEL_STAR_1_RELIC_INDEX;
        if(sender == buttonLevelStar2)gEditor->mTileType = LEVEL_STAR_2_RELIC_INDEX;
        if(sender == buttonLevelStar3)gEditor->mTileType = LEVEL_STAR_3_RELIC_INDEX;
    }

    
    
    if(sender == buttonRelic1 || sender == buttonRelic2 || sender == buttonRelic3)
    {
        gEditor->mModeTile = ED_T_M_RELIC;
        
        if(sender == buttonRelic1)gEditor->mTileType = 0;
        if(sender == buttonRelic2)gEditor->mTileType = 1;
        if(sender == buttonRelic3)gEditor->mTileType = 2;
    }
}

- (IBAction)toggle:(UISegmentedControl*)sender
{
    
}

- (IBAction)slide:(UISlider*)sender
{
    
}

- (void)nuke
{
    
    self.buttonTileRandom = nil;
    
    self.buttonTile1 = nil;
    self.buttonTile2 = nil;
    self.buttonTile3 = nil;
    self.buttonTile4 = nil;
    self.buttonTile5 = nil;
    self.buttonTile6 = nil;
    
    self.buttonRock = nil;
    self.buttonDirt = nil;
    self.buttonColorRock = nil;
    self.buttonMetal = nil;
    self.buttonHardRock = nil;
    self.buttonEnergy = nil;
    
    self.buttonPowerup1 = nil;
    self.buttonPowerup2 = nil;
    self.buttonPowerup3 = nil;
    self.buttonPowerup4 = nil;
    self.buttonPowerup5 = nil;
    self.buttonPowerupRandomSmall = nil;
    self.buttonPowerupRandomBig = nil;
    
    self.buttonTreasure1 = nil;
    self.buttonTreasure2 = nil;
    self.buttonTreasure3 = nil;
    self.buttonTreasure4 = nil;
    self.buttonTreasure5 = nil;
    self.buttonTreasure6 = nil;
    self.buttonTreasureRandomSmall = nil;
    self.buttonTreasureRandomBig = nil;
    
    self.buttonRelic1 = nil;
    self.buttonRelic2 = nil;
    self.buttonRelic3 = nil;
    
    self.buttonLevelStar1 = nil;
    self.buttonLevelStar2 = nil;
    self.buttonLevelStar3 = nil;
    
    [self.view removeFromSuperview];
    
}

- (void)dealloc
{
    [self nuke];
}

@end
