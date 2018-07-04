#ifndef GAME_H
#define GAME_H

#include "MainApp.h"
#include "GameMenu.h"

#include "LevelCompleteOverlay.h"

#include "GameTileMatchable.h"
#include "GameTileStar.h"
#include "GameTileTreasure.h"



#ifdef EDITOR_MODE
#include "EditorBoard.h"
#include "EditorUCanvas.h"
#endif



#define COLLECTION_TYPE_STAR 0
#define COLLECTION_TYPE_TILE 1
#define COLLECTION_TYPE_TREASURE 2
#define COLLECTION_TYPE_DEPTH 3

class GameBoard;
class Board;
class CollectedEssence;

class GameInterfaceTop;
class GameInterfaceBottom;

class ActionProcItem;
class ActionProcItemFocus;

class Game : public FView
{
public:
    
    Game(int pLevelIndex);
    virtual ~Game();
    
    virtual void                            PositionContent();
    void                                    SetUpForLevel(int pLevelIndex);
    
    virtual void                            Update();
	virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    bool                                    IsPaused();
    
    
    float                                   UntransformScale();
    float                                   UntransformScale(float pScale);
    float                                   UntransformX(float pX);
    float                                   UntransformY(float pY);
    
    Board                                   *mBoard;
    
#ifdef EDITOR_MODE
    EditorUCanvas                           *mEditorCanvas;
#endif
    
    
    GameInterfaceTop                        *mInterfaceTop;
    GameInterfaceBottom                     *mInterfaceBottom;
    GameMenu                                *mGameMenu;
    
    //AnimationHeatBeam
    ActionProcItem                          *mMainItem;
    
    
    int                                     mInterfaceTileSize;
    int                                     mInterfaceTopHeight;
    int                                     mInterfaceBottomHeight;
    
    
    
    int                                     mCollectionType[8];
    int                                     mCollectionTypeIndex[8];
    int                                     mCollectionCount[8];
    int                                     mCollectionCountTotal[8];
    bool                                    mCollectionComplete[8];
    
    float                                   mCollectionTypeAnimationTargetX[8];
    float                                   mCollectionTypeAnimationTargetY[8];
    
    void                                    CollectionTypeSetUp();
    void                                    CollectionTypeAddTile(int pTileType, int pCount);
    void                                    CollectionTypeAddStar(int pNumber=3);
    
    void                                    SetDisplayScore(int pScore);
    
    void                                    CollectionTypeUpdateTile(int pTileType, int pCount);
    
    void                                    CollectionTypeCheckCompletion();
    
    int                                     mCollectionTypeCount;
    
    FString                                 mLoadLevel;
    int                                     mLoadLevelIndex;
    
    
    
    
    
    
    
    bool                                    mDidSetupBoard;
    
    
    //void                                    TimeExtend();
    
    void                                    Flash(FColor pColor);
    FColor                                  mFlashColor;
    
    
    float                                   mDarkenFade;
    
    
    
    void                                    CircleBurst(float pX, float pY, FSprite *pSprite, int pCount, float pSpeed);
    void                                    CircleBurst(float pX, float pY);
    
    //GameTileOldRelic                        *mDiscoveredRelic;
    //void                                    DiscoverRelic(GameTileOldRelic *pRelic);
    //void                                    DiscoverTreasure(GameTileOldTreasure *pTreasure);
    //void                                    CollectBubble(GameTileOldBubble *pBubble);
    
    
    
    
    
    void                                    DiscoverStar(GameTileStar *pStar, float pCenterX, float pCenterY);
    void                                    DiscoverTreasure(GameTileTreasure *pTreasure, float pCenterX, float pCenterY);
    
    void                                    CollectEssence(float pCenterX, float pCenterY, int pEssenceCount, int pFlag=0);
    bool                                    CollectedEssenceReachedInterface(CollectedEssence *pEssence);
    
    int                                     CollectedEssencesCount(void *pTarget);
    
    //mCollectedEssences
    
    int                                     ActionProcItemSelect();
    void                                    ActionProcItemWillBeReady();
    void                                    ComputeFocus(ActionProcItemFocus *pFocus);
    void                                    ActionProcItemStartTrigger(int pItemID, ActionProcItemFocus *pFocus);
    void                                    ActionProcItemUpdateTrigger(int pItemID, ActionProcItemFocus *pFocus);
    int                                     ActionProcItemTriggerChargeTime(int pItemID);
    
    
    bool                                    AnyActionProcItemReady();
    bool                                    AnyActionProcItemWillBeReady();
    
    void                                    ActionProcItemTriggerStop();
    
    //int                                     ActionProcItemTriggerState();
    
    
    
    
    FList                                   mActionProcItems;
    
    
    
    
    //bool                                    mJarTriggering;
    //int                                     mJarTriggerTimer;
    
    //int                                     mJarTriggerGridX;
    //int                                     mJarTriggerGridY;
    
    
    float                                   mEssenceTargetX;
    float                                   mEssenceTargetY;
    
    int                                     mDiscoverStarCount;
    int                                     mDiscoverStarTotal;
    
    
    //AnimationDiscoveredStar
    
    //void                                    CollectEgg(GameTileMatchable *pTile);
    //void                                    CollectStar(GameTileStar *pStar);
    
    
    //AnimationDiscoveredLevelEgg             *mLevelEggAnimation;
    
    //float                                   mDiscoveredRelicX;
    //float                                   mDiscoveredRelicY;
    //float                                   mDiscoveredRelicScale;
    //float                                   mDiscoveredRelicFade;
    
    //int                                     mDiscoveredRelicMode;
    //int                                     mDiscoveredRelicTimer;
    
    //float                                   mDiscoveredRelicRotationSin;
    //float                                   mDiscoveredRelicScaleSin;
    //float                                   mDiscoveredRelicLightRotation;
    //float                                   mDiscoveredRelicLightFade;
    
    //int                                     mDiscoveredRelicSparkleTimer;
    
    void                                    LevelCompleteDialogShow(bool pDidWin);
    bool                                    mLevelComplete;
    LevelCompleteOverlay                    *mLevelCompleteOverlay;
    
    //bool                                    mTimeOver;
    //TimesUpDialog                           *mTimesUpDialog;
    
    
    
    bool                                    mWarning;
    int                                     mWarningAlertTimer;
    
    int                                     mWarningSoundTickTockTimer;
    bool                                    mWarningSoundTick;
    
    
    
    bool                                    mStartAnimation;
    
    int                                     mStartAnimationTimer;
    int                                     mStartAnimationIndex;
    
    float                                   mStartAnimationNumbarScale;
    float                                   mStartAnimationNumbarScaleSpeed;
    int                                     mStartAnimationNumberScalePauseTimer;
    
    float                                   mStartAnimationGoFade;
    float                                   mStartAnimationGoRotationSin;
    float                                   mStartAnimationGoScaleSin;
    float                                   mStartAnimationGoScale;
    float                                   mStartAnimationGoScaleSpeed;
    
    
    float                                   mAnimationScreenFade;
    
    FObjectList                             mListBurstParticles;
    
    FObjectList                             mAnimations;
    FObjectList                             mAnimationsAdditive;
    
    FObjectList                             mAnimationsTop;
    FObjectList                             mAnimationsTopAdditive;
    
    FObjectList                             mCollectedEssences;
    
    //FObjectList                             mListDiscoveredTreasures;
    //FObjectList                             mListDiscoveredLevelEggs;
    //FObjectList                             mListCollectedTiles;
    
    float                                   mScoreAnimationNodeX[4];
    float                                   mScoreAnimationNodeY[4];
};

extern Game *gGame;

#endif
