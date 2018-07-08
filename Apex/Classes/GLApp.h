//
//  GLApp.h
//  OptimizeRX
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#ifndef GLApp_hpp
#define GLApp_hpp

#define TOWER_FRAMES 24

#define GAPP (gApp)

#include "FApp.h"
#include "FSprite.h"
#include "FFont.h"
#include "FModelData.h"
#include "FCanvas.hpp"
#include "SpriteSequenceNested.h"

class Game;
class TilePathFinder;

class GLApp : public FApp {
public:
    GLApp();
    virtual ~GLApp();
    
    Game                                        *mGame;

    virtual void                                Update();
    virtual void                                Draw();
    virtual void                                Load();
    virtual void                                LoadComplete();

    void                                        UpdateRot(float pX);

    virtual void                                SetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetDeviceSize(float pWidth, float pHeight);

    bool                                        SegmentSegmentIntersection(FPoint l1p1, FPoint l1p2, FPoint l2p1, FPoint l2p2, FPoint *intersection);
    
    virtual void                                MouseWheel(int pDirection);
    virtual void                                KeyDown(int pKey);
    virtual void                                KeyUp(int pKey);
    
    virtual void                                TouchDown(float pX, float pY, void *pData);
    virtual void                                TouchMove(float pX, float pY, void *pData);
    virtual void                                TouchUp(float pX, float pY, void *pData);
    virtual void                                TouchFlush();


    FSprite                         mTileTunnel;
    FSprite                         mTileFloor;
    FSprite                         mTileBridge;

    FSprite                         mBridgeRampU;
    FSprite                         mBridgeRampD;
    FSprite                         mBridgeRampL;
    FSprite                         mBridgeRampR;

    FSprite                         mFloorRampU;
    FSprite                         mFloorRampD;
    FSprite                         mFloorRampL;
    FSprite                         mFloorRampR;

    FSprite                         mBlocker;

    FSprite                         mUnitCircleSoft;
    FSprite                         mUnitCircleHard;

    FSpriteSequence                 mTowerBasicOff;
    FSpriteSequence                 mTowerBasicOn;


    SpriteSequenceNested            mRobot;

    FSprite                         mTowerMenuButtonBack[2];
    FSprite                         mTowerMenuButtonPrice8;
    FSprite                         mTowerMenuButtonPrice20;
    FSprite                         mTowerMenuButtonPrice45;
    FSprite                                  mTowerMenuButtonPrice65;
    FSprite                                  mTowerMenuButtonPrice75;
    FSprite                                  mTowerMenuButtonPrice100;
    FSprite                                  mTowerMenuButtonPrice125;


    FSprite                                  mTowerDetailMenuButtonInfo;
    FSprite                                  mTowerDetailMenuButtonSell;
    FSprite                                  mTowerDetailMenuButtonUpgrade;

    FSprite                                  mGridOverlay[2];

    FSprite                                  mLevelBackTunnel;
    FSprite                                  mLevelBackFloor;
    FSprite                                  mLevelBackBridge;

    FSprite                                  mCheck;

    
    FSprite                                                                    gi_chaos_egg_back_blue_steel;
    FSprite                                                                       gi_chaos_egg_back_chrome;
    FSprite                                                                       gi_chaos_egg_back_grey;
    FSprite                                                                       gi_chaos_egg_back_megabronze;
    FSprite                                                                       gi_chaos_egg_back_red;
    FSprite                                                                       gi_chaos_egg_back_tan;
    FSprite                                                                       gi_chaos_egg_diamond_glow_large;
    FSprite                                                                       gi_chaos_egg_diamond_glow_small;
    FSprite                                                                       gi_chaos_egg_diamond_slot;
    FSprite                                                                       gi_chaos_egg_gem_diamond;
    FSprite                                                                       gi_chaos_egg_mockup_2;
    FSprite                                                                       gi_chaos_egg_mockup;
    FSprite                                                                       gi_chaos_egg_spots_blue_glowing;
    FSprite                                                                       gi_chaos_egg_spots_blue;
    FSprite                                                                       gi_chaos_egg_spots_hot_yellow_glowing;
    FSprite                                                                       gi_chaos_egg_spots_purple_glowing;
    FSprite                                                                       gi_chaos_egg_spots_red_glowing;
    FSprite                                                                       gi_chaos_egg_spots_teal_glowing;
    FSprite                                                                       gi_chaos_egg_spots_white;
    FSprite                                                                       gi_chaos_egg_spots_yellow_glowing;
    FSprite                                                                       gi_chaos_egg_stroke_blue;
    FSprite                                                                       gi_chaos_egg_stroke_glowing;
    FSprite                                                                       gi_chaos_egg_stroke_white;



    FSprite                                                                       gi_item_back_bottom_overlay;
    FSprite                                                                       gi_item_back_inset_active;
    FSprite                                                                       gi_item_back_inset;
    FSprite                                                                       gi_item_back;
    FSprite                                                                       gi_item_charge_count_indicator;
    FSprite                                                                       gi_item_crystal;
    FSprite                                                                       gi_item_lock;
    FSprite                                                                       gi_item_locked_mockup;
    FSprite                                                                       gi_item_locked;
    FSprite                                                                       gi_item_mace;
    FSprite                                                                       gi_item_mockup;
    FSprite                                                                       gi_item_progress_bar_fill;
    FSprite                                                                       gi_item_progress_bar;
    FSprite                                                                       gi_item_stone_back;

    


};


float CX(int pGridX);
float CY(int pGridY);

float CX(int pGridX, int pGridZ);
float CY(int pGridY, int pGridZ);


extern Game *gGame;
extern TilePathFinder *gPathFinder;

extern float gArenaWidth;
extern float gArenaWidth2;

extern float gArenaHeight;
extern float gArenaHeight2;



extern GLApp *gApp;

#endif /* GLApp_hpp */
