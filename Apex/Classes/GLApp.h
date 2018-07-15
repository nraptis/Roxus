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
class WorldContainer;

class GLApp : public FApp {
public:
    GLApp();
    virtual ~GLApp();
    
    //Game                                        *mGame;
    WorldContainer                          *mWorld;

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Load();
    virtual void                            LoadComplete();

    virtual void                            SetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                            SetDeviceSize(float pWidth, float pHeight);

    virtual void                            MouseWheel(int pDirection);
    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    bool                                    mDarkMode;

    FSprite                                 mTileTunnel;
    FSprite                                 mTileFloor;
    FSprite                                 mTileBridge;

    FSprite                                 mBridgeRampU;
    FSprite                                 mBridgeRampD;
    FSprite                                 mBridgeRampL;
    FSprite                                 mBridgeRampR;

    FSprite                                 mFloorRampU;
    FSprite                                 mFloorRampD;
    FSprite                                 mFloorRampL;
    FSprite                                 mFloorRampR;

    FSprite                                 mBlocker;

    FSprite                                 mUnitCircleSoft;
    FSprite                                 mUnitCircleHard;

    FSpriteSequence                         mTowerBasicOff;
    FSpriteSequence                         mTowerBasicOn;


    SpriteSequenceNested                    mRobot;

    FSprite                                 mTowerMenuButtonBack[2];
    FSprite                                 mTowerMenuButtonPrice8;
    FSprite                                 mTowerMenuButtonPrice20;
    FSprite                                 mTowerMenuButtonPrice45;
    FSprite                                 mTowerMenuButtonPrice65;
    FSprite                                 mTowerMenuButtonPrice75;
    FSprite                                 mTowerMenuButtonPrice100;
    FSprite                                 mTowerMenuButtonPrice125;


    FSprite                                 mTowerDetailMenuButtonInfo;
    FSprite                                 mTowerDetailMenuButtonSell;
    FSprite                                 mTowerDetailMenuButtonUpgrade;

    FSprite                                 mGridOverlay[2];

    FSprite                                 mLevelBackTunnel;
    FSprite                                 mLevelBackFloor;
    FSprite                                 mLevelBackBridge;

    FSprite                                 mCheck;

    FSprite                                 m1024x1024;
    FSprite                                 m2048x2048;
};

//float CX(int pGridX);
//float CY(int pGridY);
float CX(int pGridX, int pGridZ);
float CY(int pGridY, int pGridZ);
float SZ(int pGridZ);

//extern Game *gGame;
//extern TilePathFinder *gPathFinder;

extern bool gEditorMode;


extern float gArenaWidth;
extern float gArenaWidth2;
extern float gArenaHeight;
extern float gArenaHeight2;

extern float gArenaActiveWidth;
extern float gArenaActiveWidth2;
extern float gArenaActiveHeight;
extern float gArenaActiveHeight2;
extern float gArenaActiveX;
extern float gArenaActiveY;

extern float gTileSize;
extern float gTileSize2;
extern float gPathBendInset45;
extern float gPathBendInset90;

extern GLApp *gApp;

#endif
