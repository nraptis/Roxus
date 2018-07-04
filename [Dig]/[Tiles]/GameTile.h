//
//  GameTile.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__GameTile__
#define ___015_Jeep_Arcon__GameTile__

#include "core_includes.h"
#include "MainApp.h"
#include "BoardGenericTile.h"
#include "FXML.h"

#define GAME_TILE_TYPE_NULL -1

#define GAME_TILE_TYPE_MATCHABLE 0
#define GAME_TILE_TYPE_DIRT 1
#define GAME_TILE_TYPE_ROCK 2

#define GAME_TILE_TYPE_ROCK_BIG 12

#define GAME_TILE_TYPE_HARD_ROCK 10
#define GAME_TILE_TYPE_POWERUP 3
#define GAME_TILE_TYPE_TREASURE 4
#define GAME_TILE_TYPE_COIN 13
#define GAME_TILE_TYPE_RELIC 5
#define GAME_TILE_TYPE_RELIC_PIECE 6

#define GAME_TILE_TYPE_COLOR_ROCK 7
#define GAME_TILE_TYPE_METAL 8
#define GAME_TILE_TYPE_ENERGY 9
#define GAME_TILE_TYPE_STAR 20

#define DAMAGE_TYPE_UNKNOWN 0
#define DAMAGE_TYPE_MATCH 1
#define DAMAGE_TYPE_MATCH_ADJACENT 2
#define DAMAGE_TYPE_COMBO 3
#define DAMAGE_TYPE_POWER_UP 4
#define DAMAGE_TYPE_SPECIAL 5

#define DESTROYED_FROM_UNKNOWN 0
#define DESTROYED_FROM_MATCH 1
#define DESTROYED_FROM_CLICK 2
#define DESTROYED_FROM_DAMAGE 3
#define DESTROYED_FROM_DAMAGE_POWERUP 4
#define DESTROYED_FROM_ENHANCEMENT 5
#define DESTROYED_FROM_DIRT_COLLAPSE 6
#define DESTROYED_FROM_DISCOVERY 7
#define DESTROYED_FROM_BLAST_WAVE 8
#define DESTROYED_FROM_SCREEN_POOF 9
#define DESTROYED_FROM_GROUP_MATCH 10

class GameTile : public BoardGenericTile
{
public:
    
    GameTile();
    virtual ~GameTile();
    
    
    virtual void                            Update();
    
    virtual void                            DrawBottom();
    virtual void                            DrawBottomBuried(){DrawBottom();}
    
    virtual void                            Draw();
    virtual void                            DrawBuried(){Draw();}
    
    virtual void                            DrawTop();
    virtual void                            DrawTopBuried(){DrawTop();}
    
    
    virtual void                            DrawSkipAccessoryBottom();
    virtual void                            DrawSkipAccessory();
    virtual void                            DrawSkipAccessoryTop();
    
    
    
    virtual BoardGenericTile                *SpawnPart();
    
    bool                                    mToppleEnabled;
    
    
    
    void                                    FallTo(int pGridY);
    virtual void                            FallingComplete();
    
    
    float                                   mTargetCenterX;
    float                                   mTargetCenterY;
    float                                   mFallSpeed;
    
    bool                                    mFalling;
    
    bool                                    mSkipDraw;
    
    //Hmm, the name for the variable that's a flag for
    bool                                    mWasFalling;
    
    int                                     mDestroyPoints;
    bool                                    mDestroyPointsDisplay;
    //bool                                    mCanBeUnearthed;
    
    
    bool                                    mDestroyHalt;
    bool                                    mRecentlyGenerated;
    
    bool                                    mDirt;
    
    int                                     mSpecialIndex;
    int                                     mBackgroundIndex;
    int                                     mBuriedIndex;
    
    
    virtual void                            Save(FXMLTag *pTag);
    virtual void                            Load(FXMLTag *pTag);
};

class DamageFlashOscillator
{
public:
    DamageFlashOscillator();
    virtual ~DamageFlashOscillator();
    
    void                                    Update();
    void                                    Draw(FSprite *pSprite, float pCenterX, float pCenterY);
    
    void                                    Hit();
    bool                                    mActive;
    
    float                                   mDamageSin;
    float                                   mDamageSinSpeed;
    
    float                                   mDamageFade;
    
    int                                     mSinLoopIndex;
    int                                     mSinLoopCount;
    
    //float
    
};


#endif /* defined(___015_Jeep_Arcon__GameTile__) */
