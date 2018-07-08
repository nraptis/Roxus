//
//  Game.h
//  GoldDigger
//
//  Created by Nick Raptis on 1/23/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#ifndef GoldDigger_Game_h
#define GoldDigger_Game_h


#define TEST_MODE_NONE 0
#define TEST_MODE_UNIT_SPAWN 1

#include "GLApp.h"

#include "GameArena.h"
#include "EditorGameArena.h"
#include "TowerPickerMenu.h"
#include "TowerPickerMenuButton.h"
#include "TowerDetailMenu.h"
#include "GameObjectCollection.h"

extern float gTileWidth;
extern float gTileHeight;

class Game : public Canvas
{
public:
    
    Game();
    virtual ~Game();
    
    GLApp                               *mApp;
    
    virtual void                        Update();
    virtual void                        Draw();
    
    
    virtual void                        GoInactive();
    virtual void                        GoActive();
    
    virtual void                        Notify(void *pData);
    
    virtual void                        MultiTouch(int x, int y, void *pData);
	virtual void                        MultiRelease(int x, int y, void *pData);
    virtual void                        MultiDrag(int x, int y, void *pData);
    virtual void                        FlushMultiTouch();
    
    GameArena                           *mArena;
    TowerPickerMenu                     mTowerPickerMenu;
    TowerDetailMenu                     mTowerDetailMenu;
    
    void                                FitArenaOnScreen();
    
    bool                                mTapMode;
    int                                 mTapStartX;
    int                                 mTapStartY;
    
    ///////////////////////////////////////////////
    //
    //
    
    void                                KillPanning();
    
    float                               TransformX(float pX);
    float                               TransformY(float pY);
    
    float                               UntransformX(float pX);
    float                               UntransformY(float pY);
    
    bool                                mPanning;
    
    float                               mCenterX;
    float                               mCenterY;
    
    float                               mZoomScale;
    float                               mZoomScaleMin;
    float                               mZoomScaleMax;
    
    void                                ComputeTouches();
    
    float                               mTouchCenterAdjustmentDirX;
    float                               mTouchCenterAdjustmentDirY;
    
    float                               mTouchCenterX;
    float                               mTouchCenterY;
    
    float                               mDragCenterX;
    float                               mDragCenterY;
    
    float                               mTouchStartCenterX;
    float                               mTouchStartCenterY;
    
    float                               mTouchStartDistance;
    float                               mTouchStartScale;
    
    //
    //
    ///////////////////////////////////////////////
    
    float                               mTestRotation;
    float                               mTestFrame;
    
    int                                 mTestMode;
    
    int                                 mTestUnitSpawnCount;
    int                                 mTestUnitSpawnRandom;
    
    
    
    
};

#endif
