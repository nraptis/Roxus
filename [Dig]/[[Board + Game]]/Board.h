//
//  Board.h
//  Bone
//
//  Created by Nick Raptis on 8/6/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef __Bone__Board__
#define __Bone__Board__

////////////////////

//
//1.) Need to know item tops versus dirt tops for shifting AND for proper combo handling.
//

#define BOARD_TIMER_COMBO_TRIGGER_PATHING 29

#define TOPPLE_COMBO_TRIGGER_TIMER 200

#define BOARD_TIME_MATCH 19
#define BOARD_TIME_MATCH_TRIGGER 18



#define BOARD_TIME_COMBO_SPINNER_HOVER 22

#include "FParticleSource.h"

#include "FView.h"
#include "BoardGeneric.h"
#include "BoardUtilities.h"

#include "TileLooper.h"

#include "GameTile.h"
#include "GameTileMatchable.h"
#include "GameTileRock.h"
#include "GameTileMetal.h"
#include "GameTileStar.h"
#include "GameTilePowerUp.h"
#include "GameTileTreasure.h"
#include "GameTileCoin.h"

#include "BoardMatchDestroyGroup.h"

//class RewardJar;
//class ActionProcItem;
//class ActionProcItem;

class ActionProcItem;
class ActionProcItemFocus;

class LevelStats;
class Board : public BoardGeneric
{
public:
    
    Board();
    virtual ~Board();
    
    void                                    Update();
    void                                    Draw();
    
    void                                    SetUpToFitInterface(int pTileSize, int pTopHeight, int pMinimumBottomHeight);
    
    void                                    StartAnimation();
    void                                    FitGridToDevice();
    
    virtual void                            Notify(void *pSender);
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    
    void                                    AddScore(int pPoints);
    void                                    AddScore(int pPoints, int pGridX, int pGridY, bool pBig);
    
    
    virtual bool                            AllowClick();
    
    LevelStats                              *mStats;
    
    BoardUtilities                          mUtils;
    
    
    
    //So here we probe out to see which tiles take damage, etc.
    BoardGenericActionLayer                 mLayerDamageCheck;
    BoardGenericActionLayer                 mLayerDirtDestroy;
    
    
    virtual void                            ActionExecute(int pActionIndex);
    
    virtual void                            DestroyTile(int pGridX, int pGridY, int pDestroyType);
    virtual void                            DestroyTile(int pGridX, int pGridY, int pDestroyType, int pTimer);
    virtual void                            DestroyTileAnimation(float pCenterX, float pCenterY, int pTileType);
    virtual void                            DestroyTileAnimation(int pGridX, int pGridY);
    void                                    DestroyDirtAnimation(int pGridX, int pGridY);
    virtual void                            DestroyTileRealize(int pGridX, int pGridY);
    bool                                    DestroyDirt(int pGridX);
    void                                    DestroyCoinScan(int pGridX, int pGridY);
    
    
    
    bool                                    AttemptDig(int pGridX, int pGridY);
    
    
    
    void                                    DestroyGroup(BoardMatchDestroyGroup *pGroup, bool pFromItem);
    BoardMatchDestroyGroup                  *DestroyGroupMake(BoardGenericMatch *pMatch, bool pFromItem);
    void                                    DestroyGroupsClear();
    void                                    DestroyGroupsTrigger(bool pFromItem);
    
    
    virtual void                            DamageTile(int pGridX, int pGridY, int pDamageType, int pDestroyType, int pDamageAmount);
    
    GameTile                                *GetTile(int pGridX, int pGridY){return (GameTile *)(GetTileBase(pGridX, pGridY));}
    GameTile                                *GetTile(int pGridX, int pGridY, int pTileType){return (GameTile *)(GetTileBase(pGridX, pGridY, pTileType));}
    
    GameTileMatchable                       *GetTileMatchable(int pGridX, int pGridY){return (GameTileMatchable *)GetTile(pGridX, pGridY, GAME_TILE_TYPE_MATCHABLE);}
    GameTileTreasure                        *GetTileTreasure(int pGridX, int pGridY){return (GameTileTreasure *)GetTile(pGridX, pGridY, GAME_TILE_TYPE_TREASURE);}
    GameTilePowerUp                         *GetTilePowerup(int pGridX, int pGridY){return (GameTilePowerUp *)GetTile(pGridX, pGridY, GAME_TILE_TYPE_POWERUP);}
    GameTileRock                            *GetTileRock(int pGridX, int pGridY){return (GameTileRock *)GetTile(pGridX, pGridY, GAME_TILE_TYPE_ROCK);}
    GameTile                                ***mTile;
    GameTileCoin                            ***mTileCoin;
    
    
    
    void                                    CreateTextBubble(int pGridX, int pGridY, FString pText, bool pBig);
    
    //So, actually, this one function can start up the entire state machine for
    //shift being complete..
    void                                    ShiftCompleteTrigger();
    
    void                                    ToppleCompleteComboTrigger();
    void                                    SpecialCompleteComboTrigger();
    
    
    
    virtual bool                            TileExposed(int pGridX, int pGridY);
    virtual void                            DiscoverTile(int pGridX, int pGridY);
    
    
    virtual bool                            Topple();
    virtual bool                            Topple(int pCol);
    virtual bool                            Topple(int pCol, int pRow);
    
    
    
    
    bool                                    DragItemCanStart();
    void                                    DragItemStart(ActionProcItem *pItem);
    void                                    DragItemEnd(ActionProcItem *pItem);
    int                                     mDragItemGridX;
    int                                     mDragItemGridY;
    ActionProcItem                          *mDragItem;
    
    
    bool                                    IsBuried(int pGridX, int pGridY);
    
    void                                    Match();
    void                                    MatchCompleteTrigger();
    
    
    bool                                    mMatching;
    int                                     mMatchingTimer;
    
    
    bool                                    mMatchTrigger;
    int                                     mMatchTriggerTimer;
    
    bool                                    mDestroying;
    
    
    
    virtual bool                            FillHoles();
    
    
    void                                    RandomizeBoard();
    void                                    RandomizeNewTiles();
    
    void                                    CheckBoard();
    
    void                                    Shift();
    int                                     mShiftAmount;
    
    int                                     mBottomBlockGap;
    
    int                                     mDirtTop[9];
    
    int                                     mDirtTopAdjsuted[9];
    void                                    CalculateAdjustedDirtTop();
    
    
    
    void                                    ObstacleFindAll();
    void                                    ObstacleSort();
    
    int                                     mObstacleGridX[256];
    int                                     mObstacleGridY[256];
    int                                     mObstacleStrength[256];
    int                                     mObstacleCount;
    
    
    
    void                                    Shimmer();
    bool                                    mShimmerAnimation;
    
    int                                     mShimmerAnimationTimer;
    int                                     mShimmerAnimationGridY;
    int                                     mShimmerAnimationDiagonalTimer;
    
    
    
    int                                     mLastClickGridX;
    int                                     mLastClickGridY;
    int                                     mLastClickTimer;
    
    
    bool                                    ComboSpinnerPrepare();
    bool                                    ComboSpinnerTrigger();
    
    
    
    
    
    void                                    Settled();
    bool                                    mSettled;
    
    
    void                                    SettlePending();
    int                                     mComboSpinnerHoverTimer;
    
    bool                                    mSettlePending;
    
    
    
    int                                     mChainCount;
    bool                                    mChainAutoSelect;
    int                                     mChainListX[128];
    int                                     mChainListY[128];
    
    bool                                    mChainDragging;
    
    bool                                    mDragDirtDig;
    
    bool                                    mShiftComplete;
    int                                     mShiftCompletePhase;
    int                                     mShiftCompleteTimer;
    
    bool                                    mToppleCompleteCombo;
    int                                     mToppleCompleteComboTimer;
    
    void                                    ActionProcItemCheck();
    void                                    ActionProcItemTriggerStop();
    
    void                                    ActionProcItem(int pItemID);
    void                                    ActionProcItem();
    
    void                                    ActionProcItemUpdateDestroy(bool pComplete);
    void                                    ActionProcItemFinish();
    
    
    //Basically, so we don't break a chain while a fill-up animation finishes...
    bool                                    mActionProcItemWaiting;
    bool                                    mActionProcItemTriggering;
    bool                                    mActionProcItemTriggeringComplete;
    int                                     mActionProcItemID;
    int                                     mActionProcItemChargeTimer;
    
    
    bool                                    mActionProcGroupDestroying;
    int                                     mActionProcGroupDestroyingDelay;
    int                                     mActionProcGroupDestroyingTimer;
    
    
    ActionProcItemFocus                     *mActionProcItemFocus;
    BoardGenericMatch                       *mActionProcItemMatch[3];
    
    int                                     mActionProcItemMatchGridX[3];
    int                                     mActionProcItemMatchGridY[3];
    
    int                                     mActionProcItemObstacleGridX[3];
    int                                     mActionProcItemObstacleGridY[3];
    
    
    
    
    FList                                   mDestroyGroups;
    FList                                   mDestroyGroupsItem;
    FList                                   mDestroyGroupsKill;
    
    
    FObjectList                             mAnimations;
    
    FObjectList                             mAnimationsSparkles;
    FObjectList                             mAnimationsSmoke;
    FObjectList                             mAnimationsSubtractive;
    FObjectList                             mAnimationsAdditive;
    FObjectList                             mAnimationsText;
    FObjectList                             mAnimationsComboSpinners;
    
    void                                    LinkSpawn();
    void                                    LinkPhase(int pIndex);
    void                                    LinkPhaseAll();
    
    FObjectList                             mLinkAnimations;
    
    
    TileLooper                              mLooperWallLeft;
    TileLooper                              mLooperWallRight;
    TileLooper                              mLooperBackground;
    
    
    FPointPath                              mEggBorder;
    
    
    int                                     mDestroyRecoilTimer;
    
    
    bool                                    mDidDestroyTile;
    bool                                    mDidDestroyTileFromMatch;
    
    bool                                    mDestroyDidChinkDirt;
    bool                                    mDestroyDidChinkRock;
    bool                                    mDestroyDidChinkMetal;
    
    bool                                    mDestroyDidDestroyDirt;
    bool                                    mDestroyDidDestroyRock;
    bool                                    mDestroyDidDestroyMetal;
    
    int                                     mSoundTimerScreenPoof;
    int                                     mSoundTimerTileLand;
    int                                     mSoundTimerMatch;
    int                                     mSoundTimerMatchStart;
    int                                     mSoundTimerDiscoverGeneric;
    int                                     mSoundTimerEssenceCollect;
    
    
    float                                   mTargetOffsetY;
        
        
    float                                   mScreenShakeX;
    float                                   mScreenShakeY;
    float                                   mScreenShakeAmount;
    
    int                                     GetRandomTreasure(bool pLarge=true);
    
    virtual void                            GridChanged(){mTile = (GameTile ***)mGridGameTile;}
    
    virtual void                            Save(const char *pPath);
    virtual void                            Load(const char *pPath);
    
    
    void                                    SetStartMoveCount(int pMoves);
    
    
    
    
    
    bool                                    mFinished;
    int                                     mFinishedTimer;
    bool                                    mFinishedLevelUp;
    bool                                    mFinishedGameOver;
    bool                                    mFinishedTriggered;
    
    
    void                                    LevelUp();
    
    
};


class ComboStats
{
public:
    ComboStats();
    
    void                                    Reset();
    
    int                                     mLength;
    int                                     mTileCount;
    int                                     mToppleCount;
    int                                     mOrbCount;
    int                                     mJarCount;
    int                                     mMatchCount;
    
};

class LevelStats
{
public:
    LevelStats();
    
    void                                    Update();
    
    int                                     mPlayTime;
    int                                     mPlayTimeSeconds;
    int                                     mPlayTimeMinutes;
    
    
    int                                     mDepth;
    int                                     mDepthStart;
    int                                     mDepthMax;
    
    
    int                                     mMoveCount;
    int                                     mMoveCountTotal;
    int                                     mMoveCountUsed;
    
    
    int                                     mDestroyedCountTotal;
    int                                     mDestroyedCountDirt;
    int                                     mDestroyedCountRock;
    int                                     mDestroyedCountMatchable;
    
    int                                     mCollectedCountTotal;
    
    
    
    
    bool                                    mComboActive;
    
    ComboStats                              mComboCurrent;
    ComboStats                              mComboRecent;
    ComboStats                              mComboBest;
    
    void                                    ComboAddMatch(int pTileCount);
    void                                    ComboAddTopple(int pTileCount);
    void                                    ComboAddOrb(int pTileCount);
    void                                    ComboAddJar(int pTileCount);
    
    void                                    ComboEnd();
    void                                    ComboRefresh();
};



extern Board *gBoard;


#endif /* defined(__Bone__Board__) */
