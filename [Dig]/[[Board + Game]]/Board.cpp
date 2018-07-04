#include "Board.h"
#include "MainApp.h"
#include "Game.h"
#include "FParticle.h"
#include "TextBubble.h"
#include "FInterp.h"
#include "TileChainLink.h"
#include "GameInterfaceTop.h"
#include "ActionProcItem.h"

Board *gBoard = 0;

Board::Board()
{
    gBoard = this;
    mName = "Board";
    mDrawManual = true;
    mRecievesOutsideTouches = true;
    mRecievesConsumedTouches = true;
    
    mActionProcItemFocus = new ActionProcItemFocus();
    
    mTile = 0;
    mTileCoin = 0;
    
    
    mStats = new LevelStats();
    mStats->mMoveCount = 4;
    mStats->mMoveCountTotal = 4;
    
    
    mActionQueue.ActionSetPriority(BOARD_ACTION_INITIALIZING, 500);
    mActionQueue.ActionSetPriority(BOARD_ACTION_TUTORIAL, 201);
    mActionQueue.ActionSetPriority(BOARD_ACTION_DRAGGING, 200);
    mActionQueue.ActionSetPriority(BOARD_ACTION_MATCHING, 190);
    mActionQueue.ActionSetPriority(BOARD_ACTION_MATCHING_COMPLETE_TRIGGER, 189);
    //mActionQueue.ActionSetPriority(BOARD_ACTION_DESTROYING, 180);
    
    mActionQueue.ActionSetPriority(BOARD_ACTION_COMBOING, 150);
    mActionQueue.ActionSetPriority(BOARD_ACTION_TOPPLING, 140);
    mActionQueue.ActionSetPriority(BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER, 139);
    
    
    mActionQueue.ActionSetPriority(BOARD_ACTION_SPECIAL_COMBO, 137);
    mActionQueue.ActionSetPriority(BOARD_ACTION_SPECIAL_COMBO_COMPLETE_TRIGGER, 136);
    
    
    mActionQueue.ActionSetPriority(BOARD_ACTION_INTERFACE_PROC_2, 134);
    mActionQueue.ActionSetPriority(BOARD_ACTION_CHECK_BOARD, 130);
    mActionQueue.ActionSetPriority(BOARD_ACTION_INTERFACE_PROC_2_WAITING, 125);
    mActionQueue.ActionSetPriority(BOARD_ACTION_SHIFTING, 120);
    mActionQueue.ActionSetPriority(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER, 119);
    mActionQueue.ActionSetPriority(BOARD_ACTION_SETTLED, 60);
    mActionQueue.ActionSetPriority(BOARD_ACTION_LEVEL_UP, 1);
    mActionQueue.ActionSetPriority(BOARD_ACTION_GAME_OVER, 0);
    
    mMatchTypeCount = 3;
    
    mDestroying = false;
    mBottomBlockGap = 2;
    
    mSoundTimerScreenPoof = 0;
    mSoundTimerTileLand = 0;
    mSoundTimerMatch = 0;
    mSoundTimerMatchStart = 0;
    mSoundTimerDiscoverGeneric = 0;
    mSoundTimerEssenceCollect = 0;
    
    
    
    mLastClickGridX = -1;
    mLastClickGridY = -1;
    mLastClickTimer = 0;
    
    
    
    mShimmerAnimation = false;
    mShimmerAnimationTimer = 0;
    mShimmerAnimationDiagonalTimer = 0;
    mShimmerAnimationGridY = 0;
    
    
    
    mLayerDamageCheck.mName = "Layer Damage Check";
    AddLayer(&mLayerDamageCheck);
    
    mLayerDirtDestroy.mName = "Layer Dirt Probe";
    AddLayer(&mLayerDirtDestroy);
    
    mUtils.mBoard = this;
    
    mChainCount = 0;
    mChainAutoSelect = false;
    
    //So we start out settled, and then once we make it to a touch down,
    //we aren't settled anymore. Too much struggle.
    mSettled = true;
    
    mFinished = false;
    mFinishedTimer = 0;
    mFinishedLevelUp = false;
    mFinishedGameOver = false;
    
    //KLUDGE
    //mFinished = true;
    //mFinishedLevelUp = true;
    //mFinishedTimer = 100;
    
    mShiftAmount = 0;
    
    mChainDragging = true;
    
    mToppleCompleteCombo = false;
    mToppleCompleteComboTimer = 0;
    
    //mChainComboGridX = -1;
    //mChainComboGridY = -1;
    
    mComboSpinnerHoverTimer = 0;
    mSettlePending = false;
    
    mShiftComplete = false;
    mShiftCompletePhase = 0;
    mShiftCompleteTimer = 0;
    
    mMatching = false;
    mMatchingTimer = 0;
    
    mMatchTrigger = false;
    mMatchTriggerTimer = 0;
    
    
    
    
    mEggBorder.Add(0.000, -29.500);
    mEggBorder.Add(3.126, -29.021);
    mEggBorder.Add(6.156, -27.600);
    mEggBorder.Add(9.000, -25.280);
    mEggBorder.Add(11.570, -22.130);
    mEggBorder.Add(13.789, -18.248);
    mEggBorder.Add(15.588, -13.750);
    mEggBorder.Add(16.914, -8.774);
    mEggBorder.Add(17.727, -3.470);
    mEggBorder.Add(18.000, 2.000);
    mEggBorder.Add(17.727, 5.751);
    mEggBorder.Add(16.914, 9.388);
    mEggBorder.Add(15.588, 12.800);
    mEggBorder.Add(13.789, 15.884);
    mEggBorder.Add(11.570, 18.547);
    mEggBorder.Add(9.000, 20.706);
    mEggBorder.Add(6.156, 22.297);
    mEggBorder.Add(3.126, 23.272);
    mEggBorder.Add(0.000, 23.600);
    mEggBorder.Add(-3.126, 23.272);
    mEggBorder.Add(-6.156, 22.297);
    mEggBorder.Add(-9.000, 20.706);
    mEggBorder.Add(-11.570, 18.547);
    mEggBorder.Add(-13.789, 15.884);
    mEggBorder.Add(-15.588, 12.800);
    mEggBorder.Add(-16.914, 9.388);
    mEggBorder.Add(-17.727, 5.751);
    mEggBorder.Add(-18.000, 2.000);
    mEggBorder.Add(-17.727, -3.470);
    mEggBorder.Add(-16.914, -8.774);
    mEggBorder.Add(-15.588, -13.750);
    mEggBorder.Add(-13.789, -18.248);
    mEggBorder.Add(-11.570, -22.130);
    mEggBorder.Add(-9.000, -25.280);
    mEggBorder.Add(-6.156, -27.600);
    mEggBorder.Add(-3.126, -29.021);
    
    
    
    
    mActionProcItemWaiting = false;
    mActionProcItemTriggering = false;
    
    mActionProcItemID = -1;
    
    mActionProcItemChargeTimer = 0;
    
    for(int i=0;i<3;i++)
    {
        mActionProcItemFocus->mMatch[i] = false;
        mActionProcItemFocus->mMatchGridX[i] = -1;
        mActionProcItemFocus->mMatchGridY[i] = -1;
        
        mActionProcItemFocus->mObstacle[i] = false;
        mActionProcItemFocus->mObstacleGridX[i] = -1;
        mActionProcItemFocus->mObstacleGridY[i] = -1;
        
        
        mActionProcItemMatch[i] = 0;
        
        mActionProcItemMatchGridX[i] = -1;
        mActionProcItemMatchGridY[i] = -1;
        
        mActionProcItemObstacleGridX[i] = -1;
        mActionProcItemObstacleGridY[i] = -1;
    }
    
    
    mActionProcGroupDestroying = false;
    mActionProcGroupDestroyingDelay = 0;
    mActionProcGroupDestroyingTimer = 0;
    
    
    
    for(int i=0;i<128;i++)
    {
        mChainListX[i] = 0;
        mChainListY[i] = 0;
    }
    
    for(int i=0;i<9;i++)mDirtTop[i] = 0;
    
    mTargetOffsetY = 0.0f;
    
    
    
    for(int i=0;i<256;i++)
    {
        mObstacleGridX[i] = -1;
        mObstacleGridY[i] = -1;
        mObstacleStrength[i] = 0;
    }
    
    mObstacleCount = 0;
    
    
    mDragItemGridX = -1;
    mDragItemGridY = -1;
    
    mDragItem = 0;
    
    
    mDragDirtDig = false;
    
    mScreenShakeX = 0.0f;
    mScreenShakeY = 0.0f;
    mScreenShakeAmount = 0.0f;
    
    mDestroyRecoilTimer = 0;
    
    mDidDestroyTile = false;
    mDidDestroyTileFromMatch = false;
    
    mDestroyDidChinkDirt = false;
    mDestroyDidChinkRock = false;
    mDestroyDidChinkMetal = false;
    
    mDestroyDidDestroyDirt = false;
    mDestroyDidDestroyRock = false;
    mDestroyDidDestroyMetal = false;
    
    
    CalculateAdjustedDirtTop();
}

Board::~Board()
{
    FreeList(BoardMatchDestroyGroup, mDestroyGroupsKill);
    FreeList(BoardMatchDestroyGroup, mDestroyGroups);
    FreeList(BoardMatchDestroyGroup, mDestroyGroupsItem);
    
    if(mTileCoin)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            for(int n=0;n<mGridHeight;n++)
            {
                if(mTileCoin[i][n])
                {
                    delete mTileCoin[i][n];
                }
                mTileCoin[i][n] = 0;
            }
            delete [] mTileCoin[i];
        }
        
        delete [] mTileCoin;
        mTileCoin = 0;
    }
}

void Board::Update()
{
    if(gApp->IsPaused())
    {
        mLastClickGridX = -1;
        mLastClickGridY = -1;
        mLastClickTimer = 0;
        
        return;
    }
    
    if((mLastClickGridX != -1) && (mLastClickGridX != -1))
    {
        mLastClickTimer++;
    }
    else
    {
        mLastClickTimer = 0;
    }
    
    mDidDestroyTile = false;
    mDidDestroyTileFromMatch = false;
    
    mDestroyDidChinkDirt = false;
    mDestroyDidChinkRock = false;
    mDestroyDidChinkMetal = false;
    
    mDestroyDidDestroyDirt = false;
    mDestroyDidDestroyRock = false;
    mDestroyDidDestroyMetal = false;
    
    if(mSoundTimerScreenPoof > 0)mSoundTimerScreenPoof--;
    if(mSoundTimerTileLand > 0)mSoundTimerTileLand--;
    if(mSoundTimerMatch > 0)mSoundTimerMatch--;
    if(mSoundTimerMatchStart > 0)mSoundTimerMatchStart--;
    if(mSoundTimerDiscoverGeneric > 0)mSoundTimerDiscoverGeneric--;
    if(mSoundTimerEssenceCollect > 0)mSoundTimerEssenceCollect--;
    
    
    if(mShimmerAnimation)
    {
        mShimmerAnimationTimer++;
        
        if(mShimmerAnimationTimer >= 40)
        {
            
            int aGridX = 0;
            int aGridY = mShimmerAnimationGridY;
            
            
            while(aGridX < mGridWidth)
            {
                GameTileMatchable *aMatchTile = GetTileMatchable(aGridX, aGridY);
                
                if(aMatchTile)
                {
                    aMatchTile->Shimmer();
                }
                
                Log("Shimmer At [%d %d]\n", aGridX, aGridY);
                
                aGridX++;
                aGridY--;
            }
            
            
            
            mShimmerAnimationGridY++;
            int aBottom = (mGridScreenTop + mGridScreenHeight + 8);
            
            
            mShimmerAnimationTimer = 0;
            if(mShimmerAnimationGridY >= aBottom)mShimmerAnimation = false;
            
        }
    }
    
    // = 0;
    //mShimmerAnimationDiagonalTimer = 0;
    // = mGridScreenTop - 1;
    
    
    
    
    int aStartY = mGridScreenTop - 6;
    if(aStartY < 0)aStartY = 0;
    
    int aEndY = mGridScreenTop + mGridScreenHeight + 6;
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    GameTile *aTile = 0;
    
    bool aAnyDestroying = false;
    bool aAnyDestroyingComplete = false;
    bool aAnyFalling = false;
    bool aAnyLanded = false;
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            aTile = mTile[i][n];
            if(aTile)
            {
                if(aTile->mFalling == true)
                {
                    aAnyFalling = true;
                }
            }
        }
    }
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            aTile = mTile[i][n];
            
            if(aTile)
            {
                bool aFallingBefore = aTile->mFalling;
                
                aTile->Update();
                
                if(aFallingBefore == true)
                {
                    if(aTile->mFalling == false)
                    {
                        aAnyLanded = true;
                    }
                }
                
                if(aTile->mFalling == true)
                {
                    aAnyFalling = true;
                }
                
                if(aTile->mDestroyed == true)
                {
                    aAnyDestroying = true;
                    
                    if(mTile[i][n]->mDestroyTimer > 0)
                    {
                        mTile[i][n]->mDestroyTimer--;
                    }
                    
                    if(mTile[i][n]->mDestroyTimer <= 0)
                    {
                        aAnyDestroyingComplete = true;
                    }
                }
            }
            
            if(mTileCoin[i][n])
            {
                mTileCoin[i][n]->Update();
                
            }
        }
    }
    
    if(aAnyDestroyingComplete)
    {
        for(int n=aEndY-1;n>=aStartY;n--)
        {
            for(int i=0;i<mGridWidth;i++)
            {
                aTile = mTile[i][n];
                
                if(aTile)
                {
                    if((aTile->mDestroyed == true) && (aTile->mDestroyTimer <= 0))
                    {
                        DestroyTileRealize(i, n);
                    }
                }
            }
        }
    }
    
    if((aAnyDestroying == false) && (aAnyDestroyingComplete == false))
    {
        if(mDestroying)
        {
            if(mDestroyRecoilTimer > 0)
            {
                mDestroyRecoilTimer--;
                
                if(mDestroyRecoilTimer == 20)
                {
                    //printf("Destroy Recoil Timer = [%d]\n", mDestroyRecoilTimer);
                }
                
                if(mDestroyRecoilTimer <= 0)
                {
                    mDestroyRecoilTimer = 0;
                    
                    mDestroying = false;
                    //ActionStop(BOARD_ACTION_DESTROYING);
                    //ActionEnqueue(BOARD_ACTION_TOPPLING);
                    
                    ActionEnqueue(BOARD_ACTION_TOPPLING);
                    
                    //ActionEnqueue(BOARD_ACTION_CHECK_BOARD);
                }
            }
        }
    }
    
    if(aAnyFalling)
    {
        
    }
    else
    {
        if(mActionQueue.IsActive(BOARD_ACTION_TOPPLING))
        {
            SetInactive(BOARD_ACTION_TOPPLING);
        }
    }
    
    //if((mChainBreak == false) && (mChainCombo == false) && (mChainDragging == false))
    if((mMatching == false) && (mChainDragging == false))
    {
        if(mChainCount > 0)
        {
            if((aAnyDestroying == false) && (aAnyDestroyingComplete == false))
            {
                LinkPhaseAll();
                mChainCount = 0;
            }
        }
    }
    
    if(mToppleCompleteCombo)
    {
        if(mToppleCompleteComboTimer > 0)
        {
            mToppleCompleteComboTimer--;
            
            Log("mToppleCompleteComboTimer = %d\n", mToppleCompleteComboTimer);
            
            if(mToppleCompleteComboTimer <= 0)
            {
                mToppleCompleteComboTimer = 0;
                mToppleCompleteCombo = false;
                
                //DestroyGroupsTrigger();
                
                
                SetInactive(BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER);
            }
        }
    }
    
    
    if(mMatching)
    {
        mMatchingTimer--;
        if(mMatchingTimer <= 0)
        {
            mMatchingTimer = 0;
            
            DestroyGroupsTrigger(false);
            mMatching = false;
            
            SetInactive(BOARD_ACTION_MATCHING);
        }
    }
    
    if(mMatchTrigger)
    {
        mMatchTriggerTimer--;
        if(mMatchTriggerTimer <= 0)
        {
            mMatchTrigger = false;
            mMatchTriggerTimer = 0;
            
            SetInactive(BOARD_ACTION_MATCHING_COMPLETE_TRIGGER);
        }
    }
    
    if(mComboSpinnerHoverTimer > 0)
    {
        mComboSpinnerHoverTimer--;
    }
    
    if(mShiftComplete)
    {
        
        if(mShiftCompletePhase == 0)
        {
            mShiftCompleteTimer = 0;
            
            
            if(ComboSpinnerPrepare())
            {
                mShiftCompletePhase = 1;
                mShiftCompleteTimer = BOARD_TIMER_COMBO_TRIGGER_PATHING;
            }
            else
            {
                mShiftCompletePhase = 2;
                mComboSpinnerHoverTimer = 0;
            }
            
        }
        
        if(mShiftCompletePhase == 1)
        {
            if(mShiftCompleteTimer > 0)mShiftCompleteTimer--;
            
            if(mComboSpinnerHoverTimer <= 0)
            {
                mComboSpinnerHoverTimer = 0;
                
                if(mShiftCompleteTimer <= 0)
                {
                    ComboSpinnerTrigger();
                    
                    mShiftCompleteTimer = 4;
                    mShiftCompletePhase = 2;
                }
                
                
                
            }
        }
        
        if(mShiftCompletePhase == 2)
        {
            if(mShiftCompleteTimer > 0)mShiftCompleteTimer--;
            
            if(mShiftCompleteTimer <= 0)
            {
                mShiftCompleteTimer = 0;
                
                mShiftComplete = false;
                SetInactive(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER);
                
            }
        }
    }
    
    if(mOffsetY < mTargetOffsetY)
    {
        mOffsetY += 6.0f;
        
        mScreenShakeAmount = 3.4f;
        
        mScreenShakeX = gRand.GetFloat(-mScreenShakeAmount, mScreenShakeAmount);
        mScreenShakeY = gRand.GetFloat(-mScreenShakeAmount, mScreenShakeAmount);
        
        float aDestroyY = mOffsetY - mTileHeight / 2.0f;
        
        for(int i=0;i<mGridWidth;i++)
        {
            for(int n=0;n<mGridHeight;n++)
            {
                aTile = GetTile(i, n);
                if(aTile)
                {
                    if((aTile->mDestroyed == true) && (aTile->mDestroyTypeIndex == DESTROYED_FROM_SCREEN_POOF) && (aTile->mCenterY <= aDestroyY))
                    {
                        aTile->mDestroyPoints = 0;
                        DestroyTileRealize(i, n);
                    }
                }
            }
        }
        
        if(mOffsetY >= mTargetOffsetY)
        {
            mOffsetY = mTargetOffsetY;
            SetInactive(BOARD_ACTION_SHIFTING);
            
            for(int i=0;i<mGridWidth;i++)
            {
                for(int n=0;n<mGridHeight;n++)
                {
                    aTile = GetTile(i, n);
                    if(aTile)
                    {
                        if((aTile->mDestroyed == true) && (aTile->mDestroyTypeIndex == DESTROYED_FROM_SCREEN_POOF))
                        {
                            aTile->mDestroyPoints = 0;
                            DestroyTileRealize(i, n);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(mScreenShakeAmount > 0)
        {
            mScreenShakeAmount -= 0.10f;
            
            if(mScreenShakeAmount <= 0)
            {
                mScreenShakeAmount = 0;
            }
            else
            {
                mScreenShakeX = gRand.GetFloat(-mScreenShakeAmount, mScreenShakeAmount);
                mScreenShakeY = gRand.GetFloat(-mScreenShakeAmount, mScreenShakeAmount);
            }
        }
        else
        {
            mScreenShakeX = 0.0f;
            mScreenShakeY = 0.0f;
        }
    }
    
    
    
    
    if(aAnyLanded)
    {
        if(mSoundTimerTileLand <= 0)
        {
            gApp->mSoundTileLanded.Play();
            mSoundTimerTileLand = 3;
        }
    }
    
    if(mDestroyDidDestroyDirt)
    {
        gApp->mSoundDirtBreak[gRand.Get(3)].Play();
        mDestroyDidDestroyDirt = false;
        mDestroyDidChinkDirt = true;
    }
    else if(mDestroyDidChinkDirt)
    {
        mDestroyDidChinkDirt = false;
    }
    
    if(mDestroyDidDestroyRock)
    {
        gApp->mSoundRockBreak[gRand.Get(2)].Play();
        mDestroyDidDestroyRock = false;
        mDestroyDidChinkRock = false;
    }
    else if(mDestroyDidChinkRock)
    {
        gApp->mSoundRockChink.Play();
        mDestroyDidChinkRock = false;
    }
    
    if(mDestroyDidDestroyMetal)
    {
        gApp->mSoundMetalBreak[gRand.Get(2)].Play();
        mDestroyDidDestroyMetal = false;
        mDestroyDidChinkMetal = false;
    }
    else if(mDestroyDidChinkMetal)
    {
        gApp->mSoundMetalChink.Play();
        mDestroyDidChinkMetal = false;
    }
    
    if(mDidDestroyTileFromMatch)
    {
        mDidDestroyTileFromMatch = false;
        if(mSoundTimerMatch <= 0)
        {
            mSoundTimerMatch = 4;
            gApp->mSoundMatchChain.Play();
            
        }
    }
    
    
    
    mLinkAnimations.Update();
    mAnimations.Update();
    mAnimationsSmoke.Update();
    mAnimationsAdditive.Update();
    mAnimationsSparkles.Update();
    mAnimationsSubtractive.Update();
    mAnimationsComboSpinners.Update();
    mAnimationsText.Update();
    
    //mDestroyGroups.Update();
    
    
    EnumList(BoardMatchDestroyGroup, aGroup, mDestroyGroups)
    {
        if(aGroup->mKill != 0)
        {
            aGroup->mKill--;
            if(aGroup->mKill <= 0)mDestroyGroupsKill.Add(aGroup);
        }
    }
    
    if(mDestroyGroupsKill.mCount > 0)
    {
        EnumList(BoardMatchDestroyGroup, aGroup, mDestroyGroupsKill)
        {
            mDestroyGroups.Remove(aGroup);
            mDestroyGroupsItem.Remove(aGroup);
            
            delete aGroup;
        }
        
        mDestroyGroupsKill.Clear();
    }
    
    
    BoardGeneric::Update();
    
    if(mActionProcItemTriggering)
    {
        if(mActionProcItemTriggeringComplete)
        {
            if(mActionProcGroupDestroying == true)
            {
                ActionProcItemUpdateDestroy(true);
            }
            else
            {
                ActionProcItemFinish();
            }
            
            
        }
        else
        {
            ActionProcItemUpdateDestroy(false);
            gGame->ActionProcItemUpdateTrigger(mActionProcItemID, mActionProcItemFocus);
            if(mActionProcItemChargeTimer > 0)
            {
                mActionProcItemChargeTimer--;
                if(mActionProcItemChargeTimer <= 0)
                {
                    for(int i=0;i<3;i++)
                    {
                        
                        if(mActionProcItemMatch[i])
                        {
                            BoardMatchDestroyGroup *aGroup = DestroyGroupMake(mActionProcItemMatch[i], true);
                            aGroup->mComboType = 2;
                            aGroup->mComboIndex = mStats->mComboCurrent.mJarCount;
                            
                            
                            delete mActionProcItemMatch[i];
                            mActionProcItemMatch[i] = 0;
                            
                        }
                        
                    }
                }
            }
        }
    }
    else if(mActionProcItemWaiting)
    {
        if(gGame->AnyActionProcItemReady())
        {
            ActionEnqueue(BOARD_ACTION_INTERFACE_PROC_2);
            SetInactive(BOARD_ACTION_INTERFACE_PROC_2_WAITING);
            mActionProcItemWaiting = false;
        }
    }
    
    if(mFinished)
    {
        bool aCanFinish = true;
        
        if(mActionQueue.mActiveCount > 0)
        {
            mFinishedTimer = 30;
            aCanFinish = false;
        }
        else
        {
            //printf("Finished [Ticking.. %d], Refreshing Timer..!\n", mFinishedTimer);
            
        }
        
        if(aCanFinish == true)
        {
            if(mFinishedTimer > 0)
            {
                mFinishedTimer--;
                
                if(mFinishedTimer <= 0)
                {
                    if(mFinishedLevelUp)
                    {
                        gGame->LevelCompleteDialogShow(true);
                    }
                    else
                    {
                        gGame->LevelCompleteDialogShow(false);
                    }
                }
            }
        }
    }
}

void Board::Draw()
{
    //Log("Board::Draw()\n");
    
    Graphics::BlendSetAlpha();
    Graphics::TextureSetModulate();
    Graphics::TextureSetFilterLinear();
    Graphics::TextureSetClamp();
    Graphics::SetColor();
    
    float aTranslateX = mScreenShakeX;
    float aTranslateY = mScreenShakeY - mOffsetY;
    
    Graphics::Translate(aTranslateX, aTranslateY);
    
    mLooperBackground.Draw(FRect(-1000.0f, mOffsetY - 256.0f, 3000, mHeight + 512.0f));
    
    mLooperWallLeft.Draw(FRect(-1000.0f, mOffsetY - 256.0f, 3000, mHeight + 512.0f));
    mLooperWallRight.Draw(FRect(-1000.0f, mOffsetY - 256.0f, 3000, mHeight + 512.0f));
    
    int aStartY = mGridScreenTop - 6;
    if(aStartY < 0)aStartY = 0;
    
    int aEndY = mGridScreenTop + mGridScreenHeight + 3;
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    Graphics::SetColor();
    mUtils.DrawDirt(mDirtTop, mGridWidth, aStartY, aEndY);
    Graphics::SetColor();
    
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            if(mTile[i][n])
            {
                if(mTile[i][n]->mSkipDraw == false)
                {
                    if(n < (mDirtTop[i]))mTile[i][n]->DrawBottom();
                    else mTile[i][n]->DrawBottomBuried();
                }
                
            }
        }
    }
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            if(mTile[i][n])
            {
                if(mTile[i][n]->mSkipDraw == false)
                {
                    if(n < (mDirtTop[i]))mTile[i][n]->Draw();
                    else mTile[i][n]->DrawBuried();
                }
            }
            
            if(mTileCoin[i][n])
            {
                //if(gRand.GetBool())
                //{
                mTileCoin[i][n]->Draw();
                //}
            }
        }
    }
    
    
    Graphics::BlendSetAlpha();
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            if(mTile[i][n])
            {
                if(mTile[i][n]->mSkipDraw == true)
                {
                    mTile[i][n]->DrawSkipAccessoryBottom();
                }
            }
        }
    }
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            if(mTile[i][n])
            {
                if(mTile[i][n]->mSkipDraw == true)
                {
                    mTile[i][n]->DrawSkipAccessory();
                }
            }
        }
    }
    
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            if(mTile[i][n])
            {
                if(mTile[i][n]->mSkipDraw == true)
                {
                    mTile[i][n]->DrawSkipAccessoryTop();
                }
            }
        }
    }
    
    Graphics::BlendSetAlpha();Graphics::SetColor();
    mLinkAnimations.Draw();
    
    Graphics::SetColor();Graphics::BlendSetAlpha();
    
    for(int n=aEndY-1;n>=aStartY;n--)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            if(mTile[i][n])
            {
                if(n < (mDirtTop[i]))mTile[i][n]->DrawTop();
                else mTile[i][n]->DrawTopBuried();
            }
        }
    }
    
    //mDestroyGroups.Draw();
    
    
    Graphics::SetColor();Graphics::BlendSetAlpha();
    
    mAnimationsComboSpinners.Draw();
    
    
    
    mAnimations.Draw();
    mAnimationsSmoke.Draw();
    
    
    Graphics::SetColor();
    Graphics::BlendSetInvert1();
    mAnimationsSubtractive.Draw();
    
    
    
    Graphics::SetColor();
    Graphics::BlendSetAdditive();
    mAnimationsAdditive.Draw();
    mAnimationsSparkles.Draw();
    
    Graphics::SetColor();
    Graphics::BlendSetAlpha();
    mAnimationsText.Draw();
    
    
    Graphics::SetColor();
    Graphics::BlendSetAlpha();
    
    
    /*
     if(mDragItemOn == true)
     {
     if((mDragItemGridX != -1) && (mDragItemGridY != -1))
     {
     Graphics::SetColor(0.2f);
     
     
     float aCenterX = GetTileCenterX(mDragItemGridX);
     float aCenterY = GetTileCenterY(mDragItemGridY);
     
     float aTop = GetTileCenterY(mGridScreenTop);
     float aWidth = ((float)mGridWidth) * mTileWidth;
     float aHeight = ((float)mGridHeight) * mTileHeight;
     
     Graphics::DrawRect(aCenterX - mTileWidth / 2.0f, aTop, mTileWidth, aHeight);
     Graphics::DrawRect(0.0f, aCenterY - (mTileHeight / 2.0f), aWidth, mTileHeight);
     
     Graphics::SetColor();
     }
     }
     */
    
    
    
    if(mDragItem != 0)
    {
        
        for(int n=aEndY-1;n>=aStartY;n--)
        {
            for(int i=0;i<mGridWidth;i++)
            {
                bool aTargetable = false;
                
                if(mDirtTop[i] < n)
                {
                    aTargetable = true;
                }
                
                if(aTargetable)
                {
                    Graphics::SetColor(0.0f, 1.0f, 0.0f, 0.15f);
                }
                else
                {
                    Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.15f);
                }
                
                Graphics::DrawRect((GetTileCenterX(i) - gTileWidth2) + 7, (GetTileCenterY(n) - gTileHeight2) + 7.0f, gTileWidth - 14.0f, gTileHeight - 14.0f);
                
                Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.45f);
                Graphics::OutlineRect((GetTileCenterX(i) - gTileWidth2) + 2, (GetTileCenterY(n) - gTileHeight2) + 2.0f, gTileWidth - 4.0f, gTileHeight - 4.0f, 2.0f);
                
                
            }
            
        }
        
        
        if((mDragItemGridX != -1) && (mDragItemGridY != -1))
        {
            Graphics::SetColor(0.4f);
            
            float aCenterX = GetTileCenterX(mDragItemGridX);
            float aCenterY = GetTileCenterY(mDragItemGridY);
            
            float aTop = GetTileCenterY(mGridScreenTop);
            float aWidth = ((float)mGridWidth) * mTileWidth;
            float aHeight = ((float)mGridHeight) * mTileHeight;
            
            Graphics::DrawRect(aCenterX - mTileWidth / 2.0f, aTop - 180.0f, mTileWidth, aHeight + 280.0f);
            Graphics::DrawRect(-80.0f, aCenterY - (mTileHeight / 2.0f), aWidth + 160.0f, mTileHeight);
            
            
        }
    }
    
    Graphics::SetColor();
}


void Board::SetUpToFitInterface(int pTileSize, int pTopHeight, int pMinimumBottomHeight)
{
    float aTransformScale = ((float)pTileSize) / ((float)mTileWidth);
    SetTransformScale(aTransformScale);
    
    if(mGridWidth <= 0)mGridWidth = DEFAULT_GRID_WIDTH;
    
    float aFrameWidth = ((float)pTileSize) * ((float)mGridWidth);
    
    
    SetPos(gAppWidth2 - (aFrameWidth / 2.0f), pTopHeight + 3.0f);
    
    int aMaximumHeight = (gAppHeight - (pTopHeight + pMinimumBottomHeight));
    
    mGridScreenHeight = 0;
    
    int aCheckHeight = 0;
    
    while(mGridScreenHeight < 20)
    {
        aCheckHeight = (mGridScreenHeight * pTileSize);
        if(aCheckHeight >= aMaximumHeight)break;
        else mGridScreenHeight++;
    }
    
    if((aMaximumHeight - aCheckHeight) >= 8.0f)
    {
        mGridScreenHeight--;
    }
    
    SetSize(mGridWidth * gTileWidth, mGridScreenHeight * gTileHeight);
    
    float aWallWidth = gApp->mWallLoopLeft[0].mWidth;
    float aWallHeight = gApp->mWallLoopLeft[0].mHeight;
    
    int aWallLooperHeight = (int)((mGridScreenHeight * gTileHeight) / aWallHeight) + 2;
    aWallLooperHeight = 90;
    
    mLooperWallLeft.SetUp(-(aWallWidth) + 4.0f, -256.0f, 1, aWallLooperHeight, aWallWidth, aWallHeight, gApp->mWallLoopLeft[0].mTexture);
    mLooperWallRight.SetUp(mWidth - 4.0f, -256.0f, 1, aWallLooperHeight, aWallWidth, aWallHeight, gApp->mWallLoopRight[0].mTexture);
    
    for(int i=0;i<aWallLooperHeight;i++)
    {
        mLooperWallLeft.SetTexture(0, i, gApp->mWallLoopLeft[gRand.Get(3)].mTexture);
        mLooperWallRight.SetTexture(0, i, gApp->mWallLoopRight[gRand.Get(3)].mTexture);
    }
    
    float aBGTileWidth = gApp->mBackgroundFill.mWidth;
    float aBGTileHeight = gApp->mBackgroundFill.mHeight;
    
    aBGTileWidth = 796.0f - 226.0f;
    aBGTileHeight = 416.0f - 96.0f;
    
    int aBGTileLooperWidth = 1;
    int aBGTileLooperHeight = 50;
    
    aBGTileLooperHeight = 50;
    
    mLooperBackground.mStartU = ((float)226) / 1024.0f;
    mLooperBackground.mStartV = ((float)96) / 512.0f;
    
    mLooperBackground.mEndU = ((float)796.0f) / 1024.0f;
    mLooperBackground.mEndV = ((float)416.0f) / 512.0f;
    
    mLooperBackground.SetUp(mWidth2 - ((aBGTileWidth * (float)aBGTileLooperWidth)) / 2.0f, -256.0f, aBGTileLooperWidth, aBGTileLooperHeight, aBGTileWidth, aBGTileHeight, gApp->mBackgroundFill.mTexture);
    
    for(int i=0;i<aBGTileLooperWidth;i++)
    {
        for(int n=0;n<aBGTileLooperHeight;n++)
        {
            mLooperBackground.SetTexture(i, n, gApp->mBackgroundFill.mTexture);
        }
    }
    
    SetFrame(mX, mY, mWidth, mHeight);
}

void Board::StartAnimation()
{
    
}

void Board::FitGridToDevice()
{
    if(mGridWidth <= 0)
    {
        mGridWidth = DEFAULT_GRID_WIDTH;
    }
    
    if(mGridHeight <= 0)
    {
        return;
    }
    
    int aTopDirt = mGridHeight;
    
    for(int i=0;i<mGridWidth;i++)
    {
        if(mDirtTop[i] < aTopDirt)aTopDirt = mDirtTop[i];
    }
    
    BoardGenericTile *aTile = 0;
    
    int aMinY = 0;
    
    int aDesiredBottomKeepTiles = 3;
    int aPadTop = (mGridScreenHeight - (aTopDirt + aDesiredBottomKeepTiles));
    int aPadBottom = 30;
    
    PadGrid(aPadTop, aPadBottom);
    
    int aLegalPlayAreaBottom = (mGridHeight - aPadBottom);
    
    for(int i=0;i<mGridWidth;i++)
    {
        mDirtTop[i] += aPadTop;
    }
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=mDirtTop[i]-1;n>=0;n--)
        {
            if(mTile[i][n] == 0)
            {
                GameTileMatchable *aMatchTile = new GameTileMatchable();
                //aMatchTile->SetUp(i, n, mTileWidth, mTileHeight);
                
                aMatchTile->mMatchType = gRand.Get(mMatchTypeCount);
                
                SetTile(i, n, aMatchTile);
            }
        }
    }
    
    //Pepper in 4 random rows of scattered rocks, 4 random rows of denser rocks, 4 random rows of mixed metal colored rocks regular rocks and whatever, and the rest with
    
    int aRand = 0;
    
    int aDepthIndex = 0;
    int aRandomTypeIndex;
    
    for(int n=aLegalPlayAreaBottom;n<mGridHeight;n++)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            aRand = gRand.Get(50);
            
            
            aRandomTypeIndex = 0;
            
            if(aDepthIndex < 4){}//Do Nothing
            else if(aDepthIndex < 8)
            {
                if(aRand < 10)aRandomTypeIndex = 1;
            }
            else if(aDepthIndex < 12)
            {
                if(aRand < 10)aRandomTypeIndex = 1;
                else if(aRand < 20)aRandomTypeIndex = 2;
            }
            else
            {
                if(aRand < 10)aRandomTypeIndex = 1;
                else if(aRand < 20)aRandomTypeIndex = 2;
                else if(aRand < 30)aRandomTypeIndex = 3;
            }
            
            aTile = 0;
            //if(aRandomTypeIndex == 1)aTile = new GameTileOldRock();
            //if(aRandomTypeIndex == 2)aTile = new GameTileOldColorRock();
            //if(aRandomTypeIndex == 3)aTile = new GameTileOldMetal();
            
            if(aTile)
            {
                //mGrid.mTile[i][n] = aTile;
                //aTile->SetUp(i, n);
            }
        }
        aDepthIndex++;
    }
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=aLegalPlayAreaBottom;n<mGridHeight;n++)
        {
            if(mGridGameTile[i][n] == 0)
            {
                
                //GameTileOldDirt *aDirt = new GameTileOldDirt();
                //mGrid.mTile[i][n] = aDirt;
                //aDirt->SetUp(i, n);
                
            }
        }
    }
    
    CalculateAdjustedDirtTop();
}

void Board::Notify(void *pSender)
{
    
}

void Board::TouchDown(float pX, float pY, void *pData)
{
    //Shimmer();
    
    mChainAutoSelect = false;
    mDragDirtDig = false;
    
    if(pY < 115.0f)
    {
        gApp->mTestIndex++;
        if(gApp->mTestIndex > 11)gApp->mTestIndex = 0;
    }
    
    
    
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    
    if(mDragItem)
    {
        if((aGridX != -1) && (aGridY != -1))
        {
            mDragItemGridX = aGridX;
            mDragItemGridY = aGridY;
        }
        else
        {
            mDragItemGridX = -1;
            mDragItemGridY = -1;
        }
        
        return;
    }
    
    
    
    
    
    float aCenterX = GetTileCenterX(aGridX);
    float aCenterY = GetTileCenterY(aGridY);
    
    GameTile *aTile = GetTile(aGridX, aGridY);
    GameTileMatchable *aMatchTile = GetTileMatchable(aGridX, aGridY);
    
    GameTileTreasure *aTreasureTile = GetTileTreasure(aGridX, aGridY);
    GameTilePowerUp *aPowerupTile = GetTilePowerup(aGridX, aGridY);
    
    if(AllowClick())
    {
        if((mChainCount == 0) && (aMatchTile != 0))
        {
            mChainDragging = true;
            
            mChainAutoSelect = false;
            BoardGenericMatch *aMatch = 0;
            
            //if((mLastClickTimer < 20) && (mLastClickGridX == aGridX) && (mLastClickGridY == aGridY))
            //Kludge:
            if(true)
            {
                
                int aStartY = mGridScreenTop - 6;
                if(aStartY < 0)aStartY = 0;
                
                int aEndY = mGridScreenTop + mGridScreenHeight + 6;
                if(aEndY > mGridHeight)aEndY = mGridHeight;
                
                MatchComputeAll(aStartY, aEndY);
                MatchListSort();
                
                for(int aMatchIndex=0;aMatchIndex<mMatchCount;aMatchIndex++)
                {
                    for(int i=0;i<mMatch[aMatchIndex]->mCount;i++)
                    {
                        if((mMatch[aMatchIndex]->mX[i] == aGridX)
                           && (mMatch[aMatchIndex]->mY[i] == aGridY))
                        {
                            aMatch = mMatch[aMatchIndex];
                        }
                    }
                }
                
                if(aMatch != 0)
                {
                    mChainAutoSelect = true;
                }
            }
            
            if(mChainAutoSelect)
            {
                gApp->mSoundChainSelect.Play();
                
                mChainCount = 0;
                
                FList aSelectList;
                
                for(int i=0;i<aMatch->mCount;i++)
                {
                    int aMatchX = aMatch->mX[i];
                    int aMatchY = aMatch->mY[i];
                    
                    aMatchTile = GetTileMatchable(aMatchX, aMatchY);
                    
                    if(aMatchTile)
                    {
                        aMatchTile->Select();
                        
                        mChainListX[mChainCount] = aMatchX;
                        mChainListY[mChainCount] = aMatchY;
                        
                        mChainCount++;
                    }
                }
            }
            else
            {
                gApp->mSoundChainSelect.Play();
                
                aMatchTile->Select();
                
                mChainListX[mChainCount] = aGridX;
                mChainListY[mChainCount] = aGridY;
                
                mChainCount++;
            }
        }
        else
        {
            
            if(IsBuried(aGridX, aGridY))
            {
                if(AttemptDig(aGridX, aGridY))
                {
                    mDragDirtDig = true;
                }
            }
            else
            {
                
                //mDirtTop[pGridX]
                
                GameTilePowerUp *aPowerUp = GetTilePowerup(aGridX, aGridY);
                GameTileTreasure *aTreasure = GetTileTreasure(aGridX, aGridY);
                //mDigClick
                
                if(aPowerUp)
                {
                    DeleteTile(aGridX, aGridY);
                }
                
                if(aTreasure)
                {
                    
                }
            }
        }
    }
    
    
    if((aGridX != -1) && (aGridY != -1))
    {
        mLastClickGridX = aGridX;
        mLastClickGridY = aGridY;
        mLastClickTimer = 0;
    }
    else
    {
        mLastClickGridX = -1;
        mLastClickGridY = -1;
        mLastClickTimer = 0;
    }
    
}

void Board::TouchMove(float pX, float pY, void *pData)
{
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    
    
    GameTile *aTile = GetTile(aGridX, aGridY);
    GameTileMatchable *aMatchTile = GetTileMatchable(aGridX, aGridY);
    
    if(mDragDirtDig)
    {
        AttemptDig(aGridX, aGridY);
        
        return;
    }
    
    if(mDragItem != 0)
    {
        if((aGridX != -1) && (aGridY != -1))
        {
            mDragItemGridX = aGridX;
            mDragItemGridY = aGridY;
        }
        else
        {
            mDragItemGridX = -1;
            mDragItemGridY = -1;
        }
        return;
    }
    else
    {
        mDragItemGridX = -1;
        mDragItemGridY = -1;
    }
    
    
    
    
    
    if((mChainCount > 0) && (aMatchTile != 0) && (mChainDragging == true) && (mChainAutoSelect == false))
    {
        GameTileMatchable *aChainLast = GetTileMatchable(mChainListX[mChainCount - 1], mChainListY[mChainCount - 1]);
        
        if(aChainLast)
        {
            int aMatchType = aChainLast->mMatchType;
            
            if((aMatchTile != aChainLast) && (aMatchTile->mMatchType == aMatchType))
            {
                int aFind = -1;
                
                for(int i=0;i<mChainCount;i++)
                {
                    if((mChainListX[i] == aGridX) && (mChainListY[i] == aGridY))
                    {
                        aFind = i;
                    }
                }
                
                if(aFind >= 0)
                {
                    if(aFind == (mChainCount - 2))
                    {
                        gApp->mSoundChainDeselect.Play();
                        
                        aChainLast->Deselect();
                        
                        mChainCount--;
                        
                        LinkPhase(mChainCount);
                    }
                }
                else
                {
                    if(aMatchTile->mGridY < (mGridScreenTop + mGridHeight - (mBottomBlockGap - 1)))
                    {
                        gApp->mSoundChainSelect.Play();
                        
                        int aDiffX = aChainLast->mGridX - aMatchTile->mGridX;
                        int aDiffY = aChainLast->mGridY - aMatchTile->mGridY;
                        
                        aDiffX = 1;
                        aDiffY = 1;
                        
                        if((aDiffX >= -1) && (aDiffX <= 1) && (aDiffY >= -1) && (aDiffY <= 1))
                        {
                            gApp->mSoundChainSelect.Play();
                            
                            aMatchTile->Select();
                            
                            mChainListX[mChainCount] = aMatchTile->mGridX;
                            mChainListY[mChainCount] = aMatchTile->mGridY;
                            
                            mChainCount++;
                            
                            LinkSpawn();
                        }
                    }
                }
            }
        }
    }
}

void Board::TouchUp(float pX, float pY, void *pData)
{
    
    mDragDirtDig = false;
    
    if((mChainCount >= 3) && (mChainDragging == true))
    {
        mStats->ComboEnd();
        //ComboCountReset();
        
        mSettled = false;
        
        mChainDragging = false;
        
        mLayerDamageCheck.Flood(-1);
        mLayerDirtDestroy.Flood(-1);
        
        int aChainX = -1;
        int aChainY = -1;
        
        //int aDestroyTime = mChainBreakTime;
        
        BoardGenericMatch *aMatch = new BoardGenericMatch();
        
        for(int i=0;i<mChainCount;i++)
        {
            aMatch->Add(mChainListX[i], mChainListY[i]);
        }
        
        
        BoardMatchDestroyGroup *aGroup = DestroyGroupMake(aMatch, false);
        aGroup->mComboType = 0;
        aGroup->mComboIndex = 0;
        
        ActionEnqueue(BOARD_ACTION_MATCHING);
        
        delete aMatch;
        
        mStats->mMoveCountUsed++;
        mStats->mMoveCount--;
        
        mStats->mMoveCount--;
        
        if(mStats->mMoveCount <= 0)
        {
            mStats->mMoveCount = 0;
            ActionEnqueue(BOARD_ACTION_GAME_OVER);
        }
        
        gGame->mInterfaceTop->SetDisplayMoves(mStats->mMoveCount, mStats->mMoveCountTotal);
        
        
        
        LinkPhaseAll();
    }
    else
    {
        mChainDragging = false;
        LinkPhaseAll();
    }
}

void Board::TouchFlush()
{
    
}

bool Board::AttemptDig(int pGridX, int pGridY)
{
    
    bool aReturn = false;
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
    {
        if(AllowClick())
        {
            
        
    if(IsBuried(pGridX, pGridY))
    {
        
        if((pGridY) <= mDirtTop[pGridX])
        {
            aReturn = true;
            DestroyDirt(pGridX);
            
        }
        
        //mDirtTop[aGridX] = (aGridY + 1);
        
    }
    }
    }
    return aReturn;
}

void Board::DestroyTile(int pGridX, int pGridY, int pDestroyType)
{
    DestroyTile(pGridX, pGridY, pDestroyType, 0);
}

void Board::DestroyTile(int pGridX, int pGridY, int pDestroyType, int pTimer)
{
    GameTile *aTile = GetTile(pGridX, pGridY);
    
    if(pTimer <= 0)pTimer = 1;
    
    if(aTile)
    {
        
        if(aTile->mTileType == GAME_TILE_TYPE_TREASURE)
        {
            Log("Destroyed a treasure, from regular board..\n");
        }
        
        if(aTile->mDestroyed == false)
        {
            mSettled = false;
            mDestroying = true;
            aTile->Destroy(pDestroyType, pTimer);
        }
    }
}

bool Board::DestroyDirt(int pGridX)
{
    bool aReturn = false;
    
    if((pGridX >= 0) && (pGridX < mGridWidth))
    {
        int aGridY = mDirtTop[pGridX];
        
        
        if((aGridY >= 0) && (aGridY < mGridHeight))
        {
            
        }
        
        GameTile *aTile = GetTile(pGridX, mDirtTop[pGridX]);
        
        
        GameTile *aTileDown = GetTile(pGridX, mDirtTop[pGridX]);
        
        if(aTileDown == 0)
        {
            int aBottomY = mGridScreenTop + (mGridScreenHeight - mBottomBlockGap);
            if(aBottomY >= mGridHeight)aBottomY = (mGridHeight - 1);
            
            if(mDirtTop[pGridX] <= aBottomY)
            {
                mDirtTop[pGridX]++;
                DestroyDirtAnimation(pGridX, mDirtTop[pGridX]);
                DestroyCoinScan(pGridX, mDirtTop[pGridX]);
                
                ActionEnqueue(BOARD_ACTION_TOPPLING);
                ActionEnqueue(BOARD_ACTION_CHECK_BOARD);
                
                //ActionEnqueue(BOARD_ACTION_TOPPLING);
                //ActionEnqueue(BOARD_ACTION_CHECK_BOARD);
                
                mDestroyDidDestroyDirt = true;
            }
        }
        else
        {
            if(TileExposed(pGridX, aGridY))
            {
                DiscoverTile(pGridX, aGridY);
            }
        }
        
    }
    
    return aReturn;
}

void Board::DamageTile(int pGridX, int pGridY, int pDamageType, int pDestroyType, int pDamageAmount)
{
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
    {
        if(mDirtTop[pGridX] <= (pGridY))
        {
            GameTile *aTileDown = GetTile(pGridX, mDirtTop[pGridX]);
            if(aTileDown == 0)
            {
                if(pDamageType == DAMAGE_TYPE_MATCH_ADJACENT)
                {
                    DestroyDirt(pGridX);
                }
            }
            else
            {
                int aExposeY = pGridY;
                if(TileExposed(pGridX, aExposeY))
                {
                    DiscoverTile(pGridX, aExposeY);
                }
            }
        }
    }
    
    GameTile *aTile = GetTile(pGridX, pGridY);
    if(aTile != 0)
    {
        if(aTile->CanReceiveDamage(pDamageType) && (aTile->mDestroyed == false))
        {
            if(aTile->Damage(pDamageAmount))
            {
                aTile->Destroy(pDestroyType, 1);
            }
        }
    }
}

void Board::DestroyCoinScan(int pGridX, int pGridY)
{
    if((pGridX >= 0) && (pGridX < mGridWidth))
    {
        int aGridY = pGridY + 1;
        
        for(int aCount = 0;aCount<=4;aCount++)
        {
            if((aGridY >= 0) && (aGridY < mGridHeight) && (aGridY < mDirtTop[pGridX]))
            {
                GameTileCoin *aCoin = mTileCoin[pGridX][aGridY];
                if(aCoin)
                {
                    FParticle *aBurst = new FParticle(&(gApp->mSequenceGlowBall));
                    aBurst->SetPos(GetTileCenterX(pGridX), GetTileCenterY(aGridY));
                    aBurst->SetFrame(0.0f, 0.65f, false);
                    mAnimations += aBurst;
                    
                    mTileCoin[pGridX][aGridY] = 0;
                }
            }
            aGridY--;
        }
    }
}

bool Board::AllowClick()
{
    bool aReturn = BoardGeneric::AllowClick();
    
    if(gGame->IsPaused())aReturn = false;
    if(mSettled == false)aReturn = false;
    if(mActionQueue.mActiveCount > 0)aReturn = false;
    
    //if(mJarTriggering == true)aReturn = false;
    
    return aReturn;
}

void Board::DestroyDirtAnimation(int pGridX, int pGridY)
{
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
    {
        FParticle *aBurst = new FParticle(&(gApp->mSequenceRockCrumble[0]));
        aBurst->SetPos(GetTileCenterX(pGridX), GetTileCenterY(pGridY) + 80.0f);
        aBurst->SetFrame(0.0f, 0.575f, false);
        aBurst->SetScale(1.30f);
        mAnimations += aBurst;
    }
}

void Board::DestroyTileAnimation(float pCenterX, float pCenterY, int pTileType)
{
    
    
    
    
    if(pTileType == GAME_TILE_TYPE_MATCHABLE)
    {
        FParticle *aBurst = new FParticle(gApp->mSequenceTwinkleSphere);
        aBurst->mTimerDelay = 0;
        aBurst->SetPos(pCenterX, pCenterY);
        aBurst->mFrameSpeed = 0.80f + gRand.GetFloat(0.05f);
        aBurst->mFrameLoop = true;
        aBurst->mFrame = gRand.F(aBurst->mSpriteSequence->GetMaxFrame());
        aBurst->mAlpha = 0.80f;
        aBurst->mAlphaSpeed = 0.04f;
        aBurst->mRed = 0.5f + gRand.F(0.4f);
        aBurst->mGreen = 0.5f + gRand.F(0.4f);
        aBurst->SetRotation();
        aBurst->mScale = 0.40f + gRand.F(0.05f);
        aBurst->mScaleSpeed = 0.062f;
        aBurst->mScaleAccel = 0.86f;
        aBurst->mYSpeed = -2.0f + gRand.F(-0.3f, 0.1f);
        aBurst->mGravityY = 0.26f;
        mAnimationsAdditive += aBurst;
    }
    
    
    
    
    /*
     if(pTileType == GAME_TILE_TYPE_MATCHABLE)
     {
     
     FParticle *aBurst = new FParticle(gApp->mSequenceSparkleSphereStop);
     
     
     aBurst->SetPos(pCenterX, pCenterY);
     aBurst->mFrameSpeed = 1.0f + gRand.GetFloat(0.1f);
     
     aBurst->mAlpha = 0.90f;
     //aBurst->SetRotation();
     
     aBurst->mRed = 0.90f + gRand.GetFloat(0.1f);
     aBurst->mGreen = 0.5f + gRand.GetFloat(0.1f);
     aBurst->mBlue = 0.5f + gRand.GetFloat(0.1f);
     
     aBurst->mGreenSpeed = 0.01f;
     aBurst->mBlueSpeed = 0.01f;
     
     mAnimationsAdditive += aBurst;
     }
     */
    
}




void Board::DestroyTileAnimation(int pGridX, int pGridY)
{
    GameTile *aTile = GetTile(pGridX, pGridY);
    
    if(aTile)
    {
        DestroyTileAnimation(aTile->mCenterX, aTile->mCenterY, aTile->mTileType);
        
        if(aTile->mTileType == GAME_TILE_TYPE_MATCHABLE)
        {
            GameTileMatchable *aMatchTile = (GameTileMatchable *)aTile;
            
            if((aMatchTile->mMatchType >= 0) && (aMatchTile->mMatchType < 8))
            {
                
                int aCount = 1;
                
                if(mAnimationsSparkles.mCount < 100)aCount += gRand.Get(2);
            
            for(int i=0;i<aCount;i++)
            {
                FParticle *aSparkle = new FParticle(&(gApp->mEffectSparkleAdditive[aMatchTile->mMatchType][gRand.Get(8)]));
                aSparkle->SetPos(aMatchTile->mCenterX + gRand.F(-12.0f, 12.0f), aMatchTile->mCenterY + gRand.F(-12.0f, 12.0f));
                aSparkle->mAlpha = 1.20f + gRand.F(0.6f);
                aSparkle->mAlphaSpeed = 0.04f + gRand.F(0.02f);
                aSparkle->mScale = 0.82f + gRand.F(0.04f);
                aSparkle->mYSpeed = gRand.F(-5.0f, 5.0f);
                aSparkle->mXSpeed = gRand.F(-5.0f, 5.0f);
                aSparkle->mSpeedAccel = 0.950f;
                aSparkle->SetRRN(4.0f, 0.98f);
                aSparkle->SetRotation();
                mAnimationsSparkles += aSparkle;
            }
        }
        }

        
    }
}

void Board::DestroyTileRealize(int pGridX, int pGridY)
{
    mDestroyRecoilTimer = 2;
    
    GameTile *aTile = GetTile(pGridX, pGridY);
    GameTileMatchable *aEgg = 0;
    
    
    if(aTile)
    {
        DestroyTileAnimation(pGridX, pGridY);
        
        //DestroyTileAnimation(aTile->mCenterX, aTile->mCenterY, aTile->mTileType);
        
        if(aTile->mDestroyPoints > 0)
        {
            AddScore(aTile->mDestroyPoints, pGridX, pGridY, true);
        }
        
        if(aTile->mTileType == GAME_TILE_TYPE_MATCHABLE)
        {
            aEgg = ((GameTileMatchable *)aTile);
        }
        
        if(aEgg)
        {
            ComboTriggerOrb *aCombo = aEgg->mComboTrigger;
            
            if(aCombo)
            {
                aEgg->mComboTrigger = 0;
                
                aCombo->mAttachedToTile = false;
                
                mAnimationsComboSpinners.Add(aCombo);
                
                aCombo->mListener = this;
                
                bool aActivateCombo = true;
                
                if((aEgg->mDestroyTypeIndex == DESTROYED_FROM_SCREEN_POOF) || (aEgg->mDestroyTypeIndex == DESTROYED_FROM_SCREEN_POOF))
                {
                    aActivateCombo = false;
                }
                
                
                
                
                
                
                
                if(aActivateCombo)
                {
                    mComboSpinnerHoverTimer = BOARD_TIME_COMBO_SPINNER_HOVER;
                    
                    //ActionEnqueue(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER);
                    ActionEnqueue(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER);
                }
                else
                {
                    aCombo->PhaseOut();
                }
            }
            
            
            
            
            
            
            
            //gGame->CollectEgg(aEgg);
            mDidDestroyTile = true;
            
            
            
        }
        
        if(aTile->mDestroyTypeIndex == DESTROYED_FROM_SCREEN_POOF)
        {
            
            //mAnimations.Add(GenerateAnimationScreenPoof(pGridX, pGridY));
            if(mSoundTimerScreenPoof <= 0)
            {
                gApp->mSoundTitleLetterBonk.Play();
                mSoundTimerScreenPoof = 8;
            }
        }
        
        //DAMAGE_TYPE_MATCH_ADJACENT
        if((aTile->mDestroyTypeIndex == DESTROYED_FROM_MATCH) || (aTile->mDestroyTypeIndex == DESTROYED_FROM_GROUP_MATCH))
        {
            mDidDestroyTileFromMatch = true;
            
            DamageTile(pGridX, pGridY + 1, DAMAGE_TYPE_MATCH_ADJACENT, DESTROYED_FROM_MATCH, 1);
            DamageTile(pGridX, pGridY - 1, DAMAGE_TYPE_MATCH_ADJACENT, DESTROYED_FROM_MATCH, 1);
            DamageTile(pGridX - 1, pGridY, DAMAGE_TYPE_MATCH_ADJACENT, DESTROYED_FROM_MATCH, 1);
            DamageTile(pGridX + 1, pGridY, DAMAGE_TYPE_MATCH_ADJACENT, DESTROYED_FROM_MATCH, 1);
        }
    }
    
    DeleteTile(pGridX, pGridY);
    
    if(mChainCount > 0)
    {
        for(int i=0;i<mChainCount;i++)
        {
            int aChainX = mChainListX[i];
            int aChainY = mChainListY[i];
            
            if((aChainX == pGridX) && (aChainY == pGridY))
            {
                LinkPhase(i);
            }
        }
    }
}

void Board::ActionExecute(int pActionIndex)
{
    //printf("{{{ - A[%s] Count[%d] (%d:%d) - }}}\n", GetActionName(pActionIndex).c(), mActionQueue.mQueueLength, mPlayTimeMinutes, mPlayTimeSeconds);
    
    if(pActionIndex == BOARD_ACTION_MATCHING)
    {
        ActionEnqueue(BOARD_ACTION_MATCHING_COMPLETE_TRIGGER);
        Match();
    }
    
    if(pActionIndex == BOARD_ACTION_MATCHING_COMPLETE_TRIGGER)
    {
        ActionEnqueue(BOARD_ACTION_TOPPLING);
        MatchCompleteTrigger();
    }
    
    if(pActionIndex == BOARD_ACTION_TOPPLING)
    {
        if(Topple())
        {
            SetActive(BOARD_ACTION_TOPPLING);
        }
        
        ActionEnqueue(BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER);
    }
    
    if(pActionIndex == BOARD_ACTION_INTERFACE_PROC_2)
    {
        ActionProcItem();
    }
    
    if(pActionIndex == BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER)
    {
        ActionEnqueue(BOARD_ACTION_CHECK_BOARD);
        ToppleCompleteComboTrigger();
    }
    
    if(pActionIndex == BOARD_ACTION_CHECK_BOARD)
    {
        ActionEnqueue(BOARD_ACTION_SHIFTING);
        CheckBoard();
    }
    
    if(pActionIndex == BOARD_ACTION_SHIFTING)
    {
        ActionEnqueue(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER);
        Shift();
    }
    
    if(pActionIndex == BOARD_ACTION_SHIFT_COMPLETE_TRIGGER)
    {
        ActionEnqueue(BOARD_ACTION_INTERFACE_PROC_2_WAITING);
        ShiftCompleteTrigger();
    }
    
    if(pActionIndex == BOARD_ACTION_INTERFACE_PROC_2_WAITING)
    {
        ActionEnqueue(BOARD_ACTION_SETTLED);
        ActionProcItemCheck();
    }
    
    if(pActionIndex == BOARD_ACTION_SETTLED)
    {
        Settled();
    }
    
    if(pActionIndex == BOARD_ACTION_GAME_OVER)
    {
        if(mFinished == false)
        {
            mFinishedGameOver = true;
            mFinished = true;
            mFinishedTimer = 200;
        }
    }
    
    if(pActionIndex == BOARD_ACTION_LEVEL_UP)
    {
        if(mFinished == false)
        {
            mFinishedLevelUp = true;
            
            mFinished = true;
            mFinishedTimer = 40;
        }
    }
}

bool Board::IsBuried(int pGridX, int pGridY)
{
    bool aReturn = false;
    
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
    {
        if(mDirtTop[pGridX] <= (pGridY))
        {
            aReturn = true;
            //aReturn = false;
        }
        else
        {
            
        }
    }
    
    return aReturn;
}

bool Board::Topple()
{
    
    bool aReturn = false;
    
    int aStartY = (mGridScreenTop - 4);
    if(aStartY < 0)aStartY = 0;
    if(aStartY > (mGridHeight - 1))aStartY = (mGridHeight - 1);
    
    int aBottom = 0;
    
    for(int i=0;i<mGridWidth;i++)
    {
        GameTile *aTile = 0;
        
        aBottom = mGridScreenTop + mGridScreenHeight + 6;
        if(aBottom >= mDirtTop[i])aBottom = (mDirtTop[i] - 1);
        if(aBottom >= mGridHeight)aBottom = (mGridHeight - 1);
        
        int aShiftAmount = 0;
        
        for(int n=aBottom;n>=aStartY;n--)
        {
            aTile = mTile[i][n];
            
            if(aTile)
            {
                if(aShiftAmount > 0)
                {
                    mTile[i][n] = 0;
                    mTile[i][n + aShiftAmount] = aTile;
                    aTile->FallTo(n + aShiftAmount);
                }
            }
            else
            {
                aShiftAmount++;
            }
            
            if(aShiftAmount > 0)
            {
                aReturn = true;
            }
        }
    }
    
    if(FillHoles())
    {
        aReturn = true;
        RandomizeNewTiles();
    }
    
    return aReturn;
}

bool Board::Topple(int pCol)
{
    int aBottom = mGridScreenTop + mGridScreenHeight + 6;
    if(aBottom >= mDirtTop[pCol])aBottom = (mDirtTop[pCol] - 1);
    if(aBottom >= mGridHeight)aBottom = (mGridHeight - 1);
    
    return Topple(pCol, aBottom);
}

bool Board::Topple(int pCol, int pRow)
{
    bool aReturn = false;
    
    int aShiftAmount = 0;
    int aFallTo;
    
    int aStartY = (mGridScreenTop - 4);
    if(aStartY < 0)aStartY = 0;
    if(aStartY > (mGridHeight - 1))aStartY = (mGridHeight - 1);
    
    int aBottom = mGridScreenTop + mGridScreenHeight + 6;
    if(aBottom >= mDirtTop[pCol])aBottom = (mDirtTop[pCol] - 1);
    if(aBottom >= mGridHeight)aBottom = (mGridHeight - 1);
    
    aShiftAmount = 0;
    
    for(int n=aBottom;n>=aStartY;n--)
    {
        if(mTile[pCol][n])
        {
            
            if(aShiftAmount > 0)
            {
                aReturn = true;
                
                aFallTo = n + aShiftAmount;
                
                mTile[pCol][n]->FallTo(aFallTo);
                mTile[pCol][aFallTo] = mTile[pCol][n];
                mTile[pCol][n] = 0;
            }
        }
        else
        {
            aShiftAmount++;
        }
    }
    
    
    
    return aReturn;
}

bool Board::FillHoles()
{
    bool aReturn = false;
    
    GameTileMatchable *aMatchTile = 0;
    
    for(int i=0;i<mGridWidth;i++)
    {
        int aShiftAmount = 0;
        
        int aStartY = (mGridScreenTop);
        if(aStartY >= mGridHeight)aStartY = (mGridHeight - 1);
        
        int aBottom = mGridScreenTop + mGridScreenHeight + 6;
        if(aBottom >= mDirtTop[i])aBottom = (mDirtTop[i] - 1);
        if(aBottom >= mGridHeight)aBottom = (mGridHeight - 1);
        
        aShiftAmount = 0;
        
        int aFillCount = 0;
        
        for(int n=aStartY;n<=aBottom;n++)
        {
            if(mTile[i][n] == 0)
            {
                aFillCount++;
            }
            else
            {
                break;
            }
        }
        
        int aSpawnStart = (mGridScreenTop - 1);
        int aSpawnTarget = (aStartY + (aFillCount - 1));
        
        if(aFillCount > 0)
        {
            aReturn = true;
            for(int k=0;k<aFillCount;k++)
            {
                aMatchTile = new GameTileMatchable();
                aMatchTile->mMatchType = gRand.Get(mMatchTypeCount);
                
                aMatchTile->mRecentlyGenerated = true;
                
                SetTile(i, aSpawnTarget, aMatchTile);
                
                aMatchTile->mCenterY = GetTileCenterY(aSpawnStart) - 140.0f;
                aMatchTile->FallTo(aSpawnTarget);
                
                aSpawnTarget--;
                aSpawnStart--;
            }
        }
    }
    
    return aReturn;
}


void Board::Shimmer()
{
    mShimmerAnimation = true;
    mShimmerAnimationTimer = 0;
    mShimmerAnimationDiagonalTimer = 0;
    mShimmerAnimationGridY = mGridScreenTop - 1;
}





void Board::ToppleCompleteComboTrigger()
{
    if(mFinished == false)
    {
        MatchComputeAll();
        
        //FList aMatchList;
        
        for(int i=0;i<mMatchCount;i++)
        {
            mMatch[i]->mProcScore = 0;
            
            //mProcScore = 0;
            //mProcProbability = 0.0f;
            
            bool aTouchesDirt = false;
            
            for(int k=0;k<mMatch[i]->mCount;k++)
            {
                int aX = mMatch[i]->mX[k];
                int aY = mMatch[i]->mY[k];
                
                if((mDirtTop[aX] -1) <= aY)
                {
                    GameTile *aTile = GetTileMatchable(aX, aY);
                    
                    if(aTile)
                    {
                        if(aTile->mWasFalling)
                        {
                            aTouchesDirt = true;
                            
                        }
                    }
                }
            }
            
            if(mMatch[i]->mCount >= 3)
            {
                
                mMatch[i]->mProcScore = 8;
                
                //aMatchList.Add(mMatch[i]);
            }
            else
            {
                mMatch[i]->mProcScore = 0;
            }
            
            
            if(aTouchesDirt)
            {
                mMatch[i]->mProcScore *= 3;
            }
            
            
            if(mStats->mComboCurrent.mToppleCount > 3)
            {
                mMatch[i]->mProcScore /= 2;
            }
            
        }
        
        
        bool aDidProcCombo = false;
        
        for(int i=0;i<mMatchCount;i++)
        {
            
            //Log("Match[%d]  ProcScore = %d  Count = %d\n", i, mMatch[i]->mProcScore, mMatch[i]->mCount);
            
            if(mMatch[i]->mProcScore > 0)
            {
                
                int aRand = gRand.Get(mMatch[i]->mProcScore) + gRand.Get(mMatch[i]->mProcScore);
                
                //if(aRand > 14)
                if(aRand > 400)
                {
                    //Log("Match Proccing.. [R=%d]\n", aRand);
                    
                    aDidProcCombo = true;
                    
                    
                    
                    
                    mStats->ComboAddTopple(mMatch[i]->mCount);
                    
                    //mLevelStats.mComboCount++;
                    //mLevelStats.mComboCountToppleTrigger++;
                    //mLevelStats.mComboCountToppleTriggerCurrentWave++;
                    
                    mToppleCompleteCombo = true;
                    mToppleCompleteComboTimer = TOPPLE_COMBO_TRIGGER_TIMER;
                    
                    //BoardGenericMatch *aMatch = (BoardGenericMatch *)(aMatchList.First());
                    
                    BoardMatchDestroyGroup *aGroup = DestroyGroupMake(mMatch[i], false);
                    aGroup->mComboType = 1;
                    aGroup->mComboIndex = mStats->mComboCurrent.mToppleCount;
                }
            }
        }
        
        if(aDidProcCombo)//aMatchList.mCount > 0)
        {
            
            
        }
        else
        {
            mToppleCompleteCombo = false;
            mToppleCompleteComboTimer = 0;
        }
    }
    
    GameTile *aTile = 0;
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            aTile = mTile[i][n];
            
            if(aTile)
            {
                aTile->mWasFalling = false;
            }
        }
    }
}

bool Board::ComboSpinnerPrepare()
{
    bool aReturn = false;
    
    int aStartY = mGridScreenTop - 6;
    if(aStartY < 0)aStartY = 0;
    
    int aEndY = mGridScreenTop + mGridScreenHeight + 6;
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    
    int aTriggerCount = 0;
    EnumList(ComboTriggerOrb, aComboTrigger, mAnimationsComboSpinners)
    {
        aComboTrigger->mReadyToTrigger = false;
        
        if(aComboTrigger->IsActive())
        {
            if(aComboTrigger->mMode <= 1)
            {
                aTriggerCount++;
                aComboTrigger->mReadyToTrigger = true;
            }
        }
    }
    
    BoardGenericMatch *aMatch = 0;
    
    MatchComputeAll(aStartY, aEndY);
    MatchListSort();
    
    FList aMatches;
    
    for(int aMatchCountTier=0;aMatchCountTier<3;aMatchCountTier++)
    {
        int aMax = 9999;
        int aMin = 3;
        
        if(aMatchCountTier == 1)
        {
            aMin = 2;
            aMax = 2;
        }
        
        if(aMatchCountTier == 2)
        {
            aMin = 1;
            aMax = 1;
        }
        
        int aAddedCount = 0;
        
        if(aMatches.mCount < aTriggerCount)
        {
            for(int i=0;(i<mMatchCount);i++)
            {
                aMatch = mMatch[i];
                
                if((aMatch->mCount >= aMin) && (aMatch->mCount <= aMax))
                {
                    
                    BoardGenericMatch *aClone = aMatch->Clone();
                    aClone->mTagged = false;
                    aMatches.Add(aClone);
                    
                    aAddedCount++;
                }
            }
        }
    }
    
    int aTriggerMatchIndex = 0;
    
    EnumList(ComboTriggerOrb, aComboTrigger, mAnimationsComboSpinners)
    {
        if(aComboTrigger->mReadyToTrigger)
        {
            
            aMatch = 0;
            
            if(mFinished == false)
            {
                aMatch = ((BoardGenericMatch *)(aMatches.Fetch(aTriggerMatchIndex)));
            }
            
            if(aMatch != 0)
            {
                aMatch->mTagged = true;
                aComboTrigger->Trigger(aMatch);
                aReturn = true;
            }
            else
            {
                aComboTrigger->TriggerFizzle();
            }
            
            aTriggerMatchIndex++;
        }
    }
    
    EnumList(BoardGenericMatch, aCheckMatch, aMatches)
    {
        if(aCheckMatch->mTagged == false)
        {
            delete aCheckMatch;
        }
    }
    
    aMatches.Clear();
    
    return aReturn;
}

bool Board::ComboSpinnerTrigger()
{
    bool aReturn = false;
    
    BoardGenericMatch *aMatch = 0;
    
    if(mFinished)
    {
        EnumList(ComboTriggerOrb, aComboTrigger, mAnimationsComboSpinners)
        {
            aComboTrigger->TriggerFizzle();
        }
    }
    else
    {
        EnumList(ComboTriggerOrb, aComboTrigger, mAnimationsComboSpinners)
        {
            if(aComboTrigger->IsActive())
            {
                aMatch = aComboTrigger->mMatch;
                
                if(aMatch != 0)
                {
                    BoardMatchDestroyGroup *aGroup = DestroyGroupMake(aMatch, false);
                    
                    mStats->ComboAddOrb(aGroup->mCount);
                    aGroup->mComboIndex = mStats->mComboCurrent.mOrbCount;
                    aGroup->mComboType = 0;
                    
                }
                
                aComboTrigger->PhaseOut();
            }
        }
    }
    
    bool aAnyDestroyGroups = false;
    
    EnumList(BoardMatchDestroyGroup, aDestroyGroup, mDestroyGroups)
    {
        if(aDestroyGroup->mKill == 0)
        {
            aAnyDestroyGroups = true;
        }
    }
    
    if(aAnyDestroyGroups)
    {
        ActionEnqueue(BOARD_ACTION_MATCHING);
    }
    
    
    return aReturn;
}

void Board::ObstacleFindAll()
{
    mObstacleCount = 0;
    
    int aEndY = ((mGridScreenTop + mGridScreenHeight) - 1);
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    
    GameTile *aTile = 0;
    for(int i=0;i<mGridWidth;i++)
    {
        //for(int n=mGridScreenTop;n<mDirtTop[i];n++)
        
        for(int n=mGridScreenTop;n<mDirtTop[i];n++)
        {
            aTile = mTile[i][n];
            if(aTile)
            {
                if(aTile->mMultiPart == false)
                {
                    if((aTile->mTileType == GAME_TILE_TYPE_ROCK) || (aTile->mTileType == GAME_TILE_TYPE_METAL) || (aTile->mTileType == GAME_TILE_TYPE_ROCK_BIG))
                    {
                        if(mObstacleCount < 256)
                        {
                            mObstacleGridX[mObstacleCount] = i;
                            mObstacleGridY[mObstacleCount] = n;
                            mObstacleStrength[mObstacleCount] = 8;
                            mObstacleCount++;
                        }
                    }
                }
            }
        }
        
        if(mDirtTop[i] < aEndY)
        {
            aTile = mTile[i][mDirtTop[i]];
            
            if(aTile)
            {
                if((aTile->mTileType == GAME_TILE_TYPE_ROCK) || (aTile->mTileType == GAME_TILE_TYPE_METAL) || (aTile->mTileType == GAME_TILE_TYPE_ROCK_BIG))
                {
                    if(mObstacleCount < 256)
                    {
                        mObstacleGridX[mObstacleCount] = i;
                        mObstacleGridY[mObstacleCount] = mDirtTop[i];
                        mObstacleStrength[mObstacleCount] = 6;
                        mObstacleCount++;
                    }
                }
                else
                {
                    if(mObstacleCount < 256)
                    {
                        mObstacleGridX[mObstacleCount] = i;
                        mObstacleGridY[mObstacleCount] = mDirtTop[i];
                        mObstacleStrength[mObstacleCount] = 1;
                        mObstacleCount++;
                    }
                }
            }
            else
            {
                if(mObstacleCount < 256)
                {
                    mObstacleGridX[mObstacleCount] = i;
                    mObstacleGridY[mObstacleCount] = mDirtTop[i];
                    mObstacleStrength[mObstacleCount] = 3;
                    mObstacleCount++;
                }
            }
        }
    }
}

void Board::ObstacleSort()
{
    
    
    //BoardGenericMatch *aMatchSortKey = 0;
    //BoardGenericMatch *aMatchHold = 0;
    
    int aObstacleKeyX = 0;
    int aObstacleKeyY = 0;
    int aObstacleKeyStrength = 0;
    
    
    int aCheck = 0;
    
    for(int aStart = 1;aStart<mObstacleCount;aStart++)
    {
        aObstacleKeyX = mObstacleGridX[aStart];
        aObstacleKeyY = mObstacleGridY[aStart];
        aObstacleKeyStrength = mObstacleStrength[aStart];
        
        //aMatchSortKey = mMatch[aStart];
        
        
        
        aCheck=aStart-1;
        while(aCheck >= 0 && (mObstacleStrength[aCheck]) < aObstacleKeyStrength)
        {
            mObstacleGridX[aCheck + 1] = mObstacleGridX[aCheck];
            mObstacleGridY[aCheck + 1] = mObstacleGridY[aCheck];
            mObstacleStrength[aCheck + 1] = mObstacleStrength[aCheck];
            
            
            //mMatch[aCheck+1] = mMatch[aCheck];
            
            aCheck--;
        }
        //mMatch[aCheck+1]=aMatchSortKey;
        mObstacleGridX[aCheck + 1] = aObstacleKeyX;
        mObstacleGridY[aCheck + 1] = aObstacleKeyY;
        mObstacleStrength[aCheck + 1] = aObstacleKeyStrength;
        
    }
    
    
    
    
    int aIndex = 0;
    int aSeek = 0;
    int aRand = 0;
    int aTies = 0;
    bool aContinue = true;
    
    while(aIndex < mObstacleCount)
    {
        aTies = 1;
        aSeek = aIndex + 1;
        aContinue = true;
        
        while((aSeek < mObstacleCount) && (aContinue == true))
        {
            if(mObstacleStrength[aSeek] != mObstacleStrength[aIndex])
            {
                aContinue = false;
            }
            else
            {
                aTies++;
            }
            aSeek++;
        }
        
        if(aTies > 1)
        {
            for(int i=0;i<aTies;i++)
            {
                aRand = gRand.Get(aTies);
                
                if(aRand != i)
                {
                    aObstacleKeyX = mObstacleGridX[aIndex + i];
                    aObstacleKeyY = mObstacleGridY[aIndex + i];
                    aObstacleKeyStrength = mObstacleStrength[aIndex + i];
                    
                    //aMatchHold = mMatch[aIndex + i];
                    
                    mObstacleGridX[aIndex + i] = mObstacleGridX[aIndex + aRand];
                    mObstacleGridY[aIndex + i] = mObstacleGridY[aIndex + aRand];
                    mObstacleStrength[aIndex + i] = mObstacleStrength[aIndex + aRand];
                    
                    
                    //mMatch[aIndex + aRand] = aMatchHold;
                    mObstacleGridX[aIndex + aRand] = aObstacleKeyX;
                    mObstacleGridY[aIndex + aRand] = aObstacleKeyY;
                    mObstacleStrength[aIndex + aRand] = aObstacleKeyStrength;
                }
            }
        }
        
        aIndex += aTies;
    }
    
    
}

/*
 
 void Board::JarReady()
 {
 //printf("Board::JarReady(R = %d  T = %d)\n", mActionQueue.IsActive(BOARD_ACTION_INTERFACE_PROC_1), mJarTriggering);
 
 ActionEnqueue(BOARD_ACTION_INTERFACE_PROC_1);
 
 //mJarReady = true;
 //mJarReadyTimer = 3;
 }
 
 //Okay, so this is actually quite hairy logic, there will be 3 branches from which we
 //can get here (maybe eventually more..)
 
 bool Board::JarTrigger()
 {
 //printf("Board::JarTrigger(R = %d  T = %d)\n", mActionQueue.IsActive(BOARD_ACTION_INTERFACE_PROC_1), mJarTriggering);
 
 bool aReturn = false;
 
 if(mActionQueue.IsActive(BOARD_ACTION_INTERFACE_PROC_1) == false)
 {
 
 if(mJarTriggering == false)
 {
 SetActive(BOARD_ACTION_INTERFACE_PROC_1);
 
 if(mJarTargetMatch)
 {
 delete mJarTargetMatch;
 mJarTargetMatch = 0;
 }
 
 mJarTargetMatch = 0;
 
 mJarTargetGridX = -1;
 mJarTargetGridY = -1;
 
 MatchComputeAll();
 MatchListSort();
 
 mJarTargetGridX = gRand.Get(mGridWidth);
 
 if(gRand.GetBool())
 {
 mJarTargetGridX = (mGridWidth - 1);
 }
 
 mJarTargetGridY = mDirtTop[mJarTargetGridX];
 
 BoardGenericMatch *aMatch = 0;
 mJarTargetMatch = 0;
 
 if(mMatchCount > 0)aMatch = mMatch[0];
 
 if(aMatch)
 {
 mJarTargetMatch = aMatch->Clone();
 }
 
 if(mJarTargetMatch)
 {
 mJarTargetGridX = mJarTargetMatch->mCenterX;
 mJarTargetGridY = mJarTargetMatch->mCenterY;
 }
 
 gGame->JarTrigger(mJarTargetGridX, mJarTargetGridY);
 
 mJarTriggering = true;
 
 mJarTriggerTimer = 0;
 mJarTriggerMode = 0;
 }
 }
 return aReturn;
 }
 */



void Board::ActionProcItemCheck()
{
    if((mActionProcItemWaiting == false) && (mActionProcItemTriggering == false))
    {
        if(gGame->AnyActionProcItemReady())mActionProcItemWaiting = true;
        if(gGame->AnyActionProcItemWillBeReady())mActionProcItemWaiting = true;
        
        if(mActionProcItemWaiting)
        {
            SetActive(BOARD_ACTION_INTERFACE_PROC_2_WAITING);
        }
    }
}

void Board::ActionProcItemTriggerStop()
{
    mActionProcItemTriggeringComplete = true;
    
}

void Board::ActionProcItem(int pItemID)
{
    
}

void Board::ActionProcItem()
{
    mActionProcItemID = gGame->ActionProcItemSelect();
    
    if(mActionProcItemID != -1)
    {
        mActionProcItemWaiting = false;
        mActionProcItemTriggering = true;
        mActionProcItemTriggeringComplete = false;
        
        SetActive(BOARD_ACTION_INTERFACE_PROC_2);
        SetInactive(BOARD_ACTION_INTERFACE_PROC_2_WAITING);
        
        
        
        for(int i=0;i<3;i++)
        {
            mActionProcItemFocus->mMatch[i] = false;
            mActionProcItemFocus->mObstacle[i] = false;
            
            
            mActionProcItemMatchGridX[i] = -1;
            mActionProcItemMatchGridY[i] = -1;
            
            mActionProcItemObstacleGridX[i] = -1;
            mActionProcItemObstacleGridY[i] = -1;
            
            if(mActionProcItemMatch[i])
            {
                delete mActionProcItemMatch[i];
                mActionProcItemMatch[i] = 0;
            }
        }
        
        mMatchAllowDiagonal = false;
        
        MatchComputeAll();
        MatchListSort();
        
        mMatchAllowDiagonal = true;
        
        
        
        for(int i=0;((i<3) && (i < mMatchCount));i++)
        {
            mActionProcItemMatch[i] = mMatch[i]->Clone();
            
            mActionProcItemFocus->mMatch[i] = true;
            mActionProcItemFocus->mMatchGridX[i] = mActionProcItemMatch[i]->mCenterX;
            mActionProcItemFocus->mMatchGridY[i] = mActionProcItemMatch[i]->mCenterY;
        }
        
        
        ObstacleFindAll();
        ObstacleSort();
        
        
        for(int i=0;((i<3) && (i < mObstacleCount));i++)
        {
            mActionProcItemFocus->mObstacle[i] = true;
            
            mActionProcItemFocus->mObstacleGridX[i] = mObstacleGridX[i];
            mActionProcItemFocus->mObstacleGridY[i] = mObstacleGridY[i];
        }
        
        gGame->ActionProcItemStartTrigger(mActionProcItemID, mActionProcItemFocus);
        
        mActionProcItemChargeTimer = gGame->ActionProcItemTriggerChargeTime(mActionProcItemID);
        
        
        
        mActionProcGroupDestroying = true;
        mActionProcGroupDestroyingDelay = 30;
        mActionProcGroupDestroyingTimer = 24;
        
        
    }
}

void Board::ActionProcItemUpdateDestroy(bool pComplete)
{
    
    bool aDone = true;
    
    
    if(mActionProcGroupDestroying)
    {
        aDone = false;
        
        if(mActionProcGroupDestroyingDelay > 0)
        {
            mActionProcGroupDestroyingDelay--;
            if(mActionProcGroupDestroyingDelay <= 0)
            {
                bool aAnyGroups = false;
                
                
                EnumList(BoardMatchDestroyGroup, aGroup, mDestroyGroupsItem)
                {
                    if(aGroup->mKill == 0)
                    {
                        aAnyGroups = true;
                        
                        for(int i=0;i<aGroup->mCount;i++)
                        {
                            int aGridX = aGroup->mX[i];
                            int aGridY = aGroup->mY[i];
                            
                            GameTile *aTile = GetTile(aGridX, aGridY);
                            GameTileMatchable *aTileMatchable = 0;
                            
                            if(aTile->mTileType == GAME_TILE_TYPE_MATCHABLE)
                            {
                                aTileMatchable = (GameTileMatchable *)aTile;
                                
                            }
                            
                            if(aTileMatchable)
                            {
                                aTileMatchable->mSkipDraw = true;
                            }
                            
                        }
                        
                    }
                    
                }
            }
        }
        else if(mActionProcGroupDestroyingTimer > 0)
        {
            mActionProcGroupDestroyingTimer--;
            if(mActionProcGroupDestroyingTimer <= 0)
            {
                mActionProcGroupDestroyingTimer = 0;
                DestroyGroupsTrigger(true);
                
                
                aDone = true;
            }
        }
        else
        {
            aDone = true;
        }
        
        
        if(aDone)
        {
            
            mActionProcGroupDestroying = false;
            mActionProcGroupDestroyingDelay = 0;
            mActionProcGroupDestroyingTimer = 0;
            
            if(pComplete)
            {
                ActionProcItemFinish();
            }
            else
            {
                
            }
            
            //pComplete
            
            
        }
        
    }
    
}

void Board::ActionProcItemFinish()
{
    mActionProcGroupDestroying = false;
    mActionProcGroupDestroyingDelay = 0;
    mActionProcGroupDestroyingTimer = 0;
    
    ActionEnqueue(BOARD_ACTION_MATCHING_COMPLETE_TRIGGER);
    SetInactive(BOARD_ACTION_INTERFACE_PROC_2);
    
    mActionProcItemWaiting = false;
    
    mActionProcItemTriggering = false;
    mActionProcItemTriggeringComplete = false;
    mActionProcItemID = -1;
    
    mActionProcItemChargeTimer = 0;
}

void Board::ShiftCompleteTrigger()
{
    mShiftComplete = true;
    mShiftCompletePhase = 0;
    mShiftCompleteTimer = 20;
    
    SetActive(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER);
    //ActionStart(BOARD_ACTION_SHIFT_COMPLETE_TRIGGER);
}

void Board::SettlePending()
{
    ActionEnqueue(BOARD_ACTION_SETTLE_PENDING);
    //ActionStart(BOARD_ACTION_SETTLE_PENDING);
    mSettlePending = true;
}


void Board::Settled()
{
    mStats->ComboEnd();
    mSettled = true;
}

void Board::CheckBoard()
{
    int aRiseHeight = 0;
    
    int aEndY = mGridScreenTop + mGridScreenHeight;
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    int aTop = mDirtTop[0];
    int aBottom = mDirtTop[0];
    
    for(int i=0;i<mGridWidth;i++)
    {
        if(mDirtTop[i] < aTop)aTop = mDirtTop[i];
        if(mDirtTop[i] > aBottom)aBottom = mDirtTop[i];
    }
    
    int aTotalHeight = 0;
    for(int i=0;i<mGridWidth;i++)
    {
        int aColHeight = aEndY - mDirtTop[i];
        aTotalHeight += aColHeight;
    }
    
    if(aTotalHeight <= 14)
    {
        aRiseHeight = 2;
    }
    
    if(aRiseHeight > 0)
    {
        int aTopDirtOffset = (aTop - mGridScreenTop);
        
        aTopDirtOffset -= (aRiseHeight);
        
        if(aTopDirtOffset < 2)
        {
            aRiseHeight = 0;
        }
    }
    
    if(aRiseHeight > 0)
    {
        mShiftAmount = aRiseHeight;
        ActionEnqueue(BOARD_ACTION_SHIFTING);
    }
}

void Board::DestroyGroup(BoardMatchDestroyGroup *pGroup, bool pFromItem)//, bool pFromMatch, int pDelayTime, int pMatchTime)
{
    if(pGroup)
    {
        GameTileMatchable *aTileMatchable = 0;
        GameTile *aTile = 0;
        int aGridX = 0;
        int aGridY = 0;
        
        
        for(int i=0;i<pGroup->mCount;i++)
        {
            aGridX = pGroup->mX[i];
            aGridY = pGroup->mY[i];
            
            aTile = GetTile(aGridX, aGridY);
            
            if(aTile)
            {
                pGroup->mList.Add(aTile);
                pGroup->mScoreValue += aTile->mDestroyPoints;
                aTile->mDestroyPoints = 0;
                
                if(pFromItem == false)
                {
                    if(aTile->mTileType == GAME_TILE_TYPE_MATCHABLE)
                    {
                        aTileMatchable = (GameTileMatchable *)aTile;
                        
                        if(aTileMatchable)
                        {
                            aTileMatchable->mSkipDraw = true;
                        }
                    }
                }
            }
            
            DestroyTile(aGridX, aGridY, DESTROYED_FROM_GROUP_MATCH, 900);
            
            if(mSoundTimerMatchStart == 0)
            {
                mSoundTimerMatchStart = 6;
                gApp->mSoundMatchStarting.Play();
            }
        }
        
        pGroup->Compute(0, mGridScreenTop, mGridWidth - 1, mGridScreenTop + (mGridScreenHeight - 1));
        
        if(pFromItem)mDestroyGroupsItem.Add(pGroup);
        else mDestroyGroups.Add(pGroup);
    }
    
}

BoardMatchDestroyGroup *Board::DestroyGroupMake(BoardGenericMatch *pMatch, bool pFromItem)//, bool pFromMatch, int pDelayTime, int pMatchTime)
{
    BoardMatchDestroyGroup *aGroup = new BoardMatchDestroyGroup();
    
    if(pMatch)pMatch->Clone(aGroup);
    
    DestroyGroup(aGroup, pFromItem);
    
    return aGroup;
}

void Board::DestroyGroupsClear()
{
    EnumList(BoardMatchDestroyGroup, aGroup, mDestroyGroups)
    {
        aGroup->Kill();
    }
}

void Board::DestroyGroupsTrigger(bool pFromItem)
{
    
    FList *aList = &(mDestroyGroups);
    if(pFromItem)
    {
        aList = &(mDestroyGroupsItem);
    }
    
    EnumList(BoardMatchDestroyGroup, aGroup, *aList)
    {
        if(aGroup->mKill == 0)
        {
            for(int i=0;i<aGroup->mCount;i++)
            {
                int aGridX = aGroup->mX[i];
                int aGridY = aGroup->mY[i];
                
                DestroyTileRealize(aGridX, aGridY);
            }
            
            AddScore(aGroup->mScoreValue, aGroup->mCenterX, aGroup->mCenterY, true);
            
            
            
            //If we collect the essense...
            //which for now is always..
            
            //if(pFromItem == false)
            //{
            gGame->CollectEssence(GetTileCenterX(aGroup->mCenterX), GetTileCenterY(aGroup->mCenterY), aGroup->mCount, 0);
            //}
            
            if(mSoundTimerEssenceCollect == 0)
            {
                mSoundTimerEssenceCollect = 12;
                gApp->mSoundJarCollect.Play();
            }
            
            aGroup->Kill();
        }
    }
}


void Board::CalculateAdjustedDirtTop()
{
    for(int i=0;i<mGridWidth;i++)
    {
        mDirtTopAdjsuted[i] = mDirtTop[i];
    }
    
    
}

int Board::GetRandomTreasure(bool pLarge)
{
    return 0;
}


void Board::AddScore(int pPoints)
{
    gApp->mMeta.mScore += pPoints;
    
    //mLevelStats.mScore += pPoints;
    
    if(gGame)
    {
        gGame->SetDisplayScore(gApp->mMeta.mScore);
    }
}

void Board::AddScore(int pPoints, int pGridX, int pGridY, bool pBig)
{
    AddScore(pPoints);
    
    FString aTest = FString(pPoints * 33);
    CreateTextBubble(pGridX, pGridY, FString(pPoints, true).c(), pBig);
    
}

void Board::Match()
{
    mMatching = true;
    mMatchingTimer = BOARD_TIME_MATCH;
    //mMatchingTimer = mMatchTriggerTime;
    
    SetActive(BOARD_ACTION_MATCHING);
    //ActionStart(BOARD_ACTION_MATCHING);
}

void Board::MatchCompleteTrigger()
{
    mMatchTrigger = true;
    //mMatchTriggerTimer = mMatchTriggerTime;
    mMatchTriggerTimer = 1;
    
    
    
    
    //ActionStart(BOARD_ACTION_MATCHING_COMPLETE_TRIGGER);
    SetActive(BOARD_ACTION_MATCHING_COMPLETE_TRIGGER);
}


void Board::Shift()
{
    if(mShiftAmount > 0)
    {
        int aCheckTop = (mGridScreenTop - 4);
        if(aCheckTop < 0)aCheckTop = 0;
        
        mGridScreenTop += mShiftAmount;
        
        int aCheckBottom = mGridScreenTop;
        if(aCheckBottom > mGridHeight)
        {
            aCheckBottom = mGridHeight;
        }
        
        int aDestroyTime = 8;
        for(int n=aCheckTop;n<aCheckBottom;n++)
        {
            for(int i=0;i<mGridWidth;i++)
            {
                DestroyTile(i, n, DESTROYED_FROM_SCREEN_POOF, 5000);
            }
            aDestroyTime += 12;
        }
        
        EnumList(ComboTriggerOrb, aCombo, mAnimationsComboSpinners)
        {
            aCombo->mOrbitTargetCenterX = aCombo->mOrbitCenterX;
            aCombo->mOrbitTargetCenterY = aCombo->mOrbitCenterY - gTileHeight * ((float)mShiftAmount);
        }
        
        SetActive(BOARD_ACTION_SHIFTING);
        
        mTargetOffsetY = ((float)mGridScreenTop) * mTileHeight;
        
        mShiftAmount = 0;
        
        gApp->mSoundRise[gRand.Get(2)].Play();
        
    }
}

void Board::RandomizeBoard()
{
    Log("RandomizeBoard()\n");
    
    int aOrbCounts[8];
    
    for(int i=0;i<8;i++)
    {
        aOrbCounts[i] = 0;
    }
    
    int aIndex1 = gRand.Get(3);
    int aIndex2 = gRand.Get(3);
    
    FList aList;
    
    GameTile *aTile = 0;
    GameTileMatchable *aTileMatchable = 0;
    
    int aEmptyCount = 0;
    int aEmptyCountBuried = 0;
    
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            aTile = GetTile(i, n);
            aTileMatchable = GetTileMatchable(i, n);
            
            if(aTileMatchable)
            {
                aList.Add(aTileMatchable);
                
                //if((aTileMatchable->mRecentlyGenerated == true) && (aTileMatchable->mKill == 0))
                //{
                
                //}
            }
            
            if(aTile)
            {
                //aTile->mRecentlyGenerated = false;
                
            }
            else
            {
                aEmptyCount++;
                
                if(n >= mDirtTop[i])
                {
                    aEmptyCountBuried++;
                    
                }
                
            }
        }
    }
    
    int aCount = 2 + gRand.Get(3);
    
    for(int i=0;i<aCount;i++)
    {
        GameTileMatchable *aRandomTile = (GameTileMatchable *)(aList.FetchRandom());
        if(aRandomTile)
        {
            aRandomTile->GenerateComboTrigger();
        }
    }
    
    
    //mGridHeight
    
    
    mTileCoin = new GameTileCoin**[mGridWidth];
    for(int i=0;i<mGridWidth;i++)
    {
        mTileCoin[i] = new GameTileCoin*[mGridHeight];
        for(int n=0;n<mGridHeight;n++)
        {
            mTileCoin[i][n] = 0;
        }
    }
    
    
    
    int aCoinCount = (aEmptyCountBuried / 3);
    //aCoinCount += gRand.Get(aCoinCount + (aCoinCount / 4));
    
    GameTileCoin *aCoin = 0;
    GameTileCoin *aCoinCheck = 0;
    
    
    while (aCoinCount > 0)
    {
        
        int aTryLoops = 600;
        bool aSuccess = false;
        
        int aGridX = 0;
        int aGridY = 0;
        int aAdjCount = 0;
        
        while ((aSuccess == false) && (aTryLoops > 0))
        {
            
            aGridX = gRand.Get(mGridWidth);
            aGridY = gRand.Get(mGridHeight);
            aAdjCount = 0;
            
            if(IsBuried(aGridX, aGridY))
            {
                aTile = GetTile(aGridX, aGridY);
                
                if(aTile == 0)
                {
                    aCoin = new GameTileCoin();
                    
                    SetTile(aGridX, aGridY, aCoin);
                    
                    mTileCoin[aGridX][aGridY] = aCoin;
                    
                    aSuccess = true;
                }
            }
            aTryLoops--;
        }
        aCoinCount--;
    }
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            if(mTileCoin[i][n] != 0)
            {
                mTile[i][n] = 0;
            }
        }
    }
    
}

void Board::RandomizeNewTiles()
{
    //TODO: Add check for making sure there is an existing match.
    
    int aStartY = mGridScreenTop - 4;
    if(aStartY < 0)aStartY = 0;
    
    int aEndY = mGridScreenTop + mGridScreenHeight + 2;
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    GameTile *aTile = 0;
    GameTileMatchable *aTileMatchable = 0;
    
    FList aList;
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=aStartY;n<aEndY;n++)
        {
            aTile = GetTile(i, n);
            aTileMatchable = GetTileMatchable(i, n);
            
            if(aTileMatchable)
            {
                if((aTileMatchable->mRecentlyGenerated == true) && (aTileMatchable->mKill == 0))
                {
                    aList.Add(aTileMatchable);
                }
            }
            
            if(aTile)
            {
                aTile->mRecentlyGenerated = false;
            }
        }
    }
    
    GameTileMatchable *aRandomTile = (GameTileMatchable *)(aList.FetchRandom());
    
    if(gRand.Get(4) == 0)
    {
        if(aRandomTile)
        {
            aRandomTile->GenerateComboTrigger();
        }
    }
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=aStartY;n<aEndY;n++)
        {
            aTile = GetTile(i, n);
            
            if(aTile != 0)
            {
                aTile->mRecentlyGenerated = false;
            }
        }
    }
    
}

void Board::LinkSpawn()
{
    int aIndexStart = mChainCount - 2;
    int aIndexEnd = mChainCount - 1;
    
    GameTileMatchable *aGameTileStart = GetTileMatchable(mChainListX[aIndexStart], mChainListY[aIndexStart]);
    GameTileMatchable *aTileEnd = GetTileMatchable(mChainListX[aIndexEnd], mChainListY[aIndexEnd]);
    
    if((aGameTileStart != 0) && (aTileEnd != 0))
    {
        TileChainLink *aLink = new TileChainLink(aIndexStart, aIndexEnd);
        
        aLink->SetUp(aGameTileStart->mCenterX, aGameTileStart->mCenterY, aTileEnd->mCenterX, aTileEnd->mCenterY);
        
        mLinkAnimations.Add(aLink);
    }
}

void Board::LinkPhase(int pIndex)
{
    EnumList(TileChainLink, aLink, mLinkAnimations)
    {
        if((aLink->mEndIndex == pIndex) || (aLink->mStartIndex == pIndex))
        {
            aLink->PhaseOut();
        }
    }
}

void Board::LinkPhaseAll()
{
    EnumList(TileChainLink, aLink, mLinkAnimations)
    {
        aLink->PhaseOut();
    }
    
    for(int i=0;i<mChainCount;i++)
    {
        GameTileMatchable *aMatchTile = GetTileMatchable(mChainListX[i], mChainListY[i]);
        if(aMatchTile)aMatchTile->Deselect();
    }
    
    mChainCount = 0;
}


bool Board::DragItemCanStart()
{
    bool aReturn = true;
    
    
    //if( mDragItemOn == true)
    //{
    //    aReturn = false;
    //}
    
    return aReturn;
}

void Board::DragItemStart(class ActionProcItem *pItem)
{
    mDragItem = pItem;
    
    mDragItemGridX = -1;
    mDragItemGridY = -1;
}

void Board::DragItemEnd(class ActionProcItem *pItem)
{
    if(mDragItem)
    {
        
    }
    
    mDragItem = 0;
}

void Board::CreateTextBubble(int pGridX, int pGridY, FString pText, bool pBig)
{
    TextBubble *aBubble = new TextBubble();
    
    if(pBig)
    {
        aBubble->SetUp(&(gApp->mFontMainDisplayFront), pText, GetTileCenterX(pGridX), GetTileCenterY(pGridY) - 40.0f);
    }
    else
    {
        aBubble->SetUp(&(gApp->mFontMainDisplayFront), pText, GetTileCenterX(pGridX), GetTileCenterY(pGridY) - 40.0f);
    }
    
    mAnimationsText.Add(aBubble);
}

bool Board::TileExposed(int pGridX, int pGridY)
{
    bool aReturn = true;
    bool aScreenClipped = false;
    
    GameTile *aTile = GetTile(pGridX, pGridY);
    
    int aBottomY = mGridScreenTop + mGridScreenHeight;
    if(aBottomY > mGridHeight)aBottomY = mGridHeight;
    
    if(pGridY >= aBottomY)
    {
        aScreenClipped = true;
    }
    
    if(aTile)
    {
        if(aTile->mMulti)
        {
            GameTile *aPart = 0;
            
            int aTileTop[6];
            
            int aTileColumnX[6];
            int aTileColumnCount = 1;
            
            aTileColumnX[0] = aTile->mGridX;
            aTileTop[0] = aTile->mGridY;
            
            for(int i=0;i<aTile->mMultiPartCount;i++)
            {
                aPart = ((GameTile *)(aTile->mMultiPartList[i]));
                
                int aGridX = aPart->mGridX;
                int aGridY = aPart->mGridY;
                
                if(aGridY >= aBottomY)aScreenClipped = true;
                
                int aGridIndex = -1;
                
                for(int k=0;k<aTileColumnCount;k++)
                {
                    if(aTileColumnX[k] == aGridX)
                    {
                        aGridIndex = k;
                    }
                }
                
                if(aGridIndex == -1)
                {
                    aGridIndex = aTileColumnCount;
                    
                    aTileColumnX[aTileColumnCount] = aGridX;
                    aTileColumnCount++;
                    
                    aTileTop[aGridIndex] = aGridY;
                }
                else
                {
                    if(aGridY < aTileTop[aGridIndex])
                    {
                        aTileTop[aGridIndex] = aGridY;
                    }
                }
            }
            
            bool aAllTopsDiscovered = true;
            
            for(int i=0;i<aTileColumnCount;i++)
            {
                if(mDirtTop[aTileColumnX[i]] < aTileTop[i])
                {
                    aAllTopsDiscovered = false;
                }
            }
            
            if(aAllTopsDiscovered == false)
            {
                aReturn = false;
            }
        }
        else
        {
            
        }
    }
    
    if(aScreenClipped)
    {
        aReturn = false;
    }
    
    return aReturn;
}

void Board::DiscoverTile(int pGridX, int pGridY)
{
    GameTile *aTile = GetTile(pGridX, pGridY);
    
    if(aTile)
    {
        bool aDeleteTile = false;
        
        int aGridX = aTile->mGridX;
        int aGridY = aTile->mGridY;
        
        float aCenterX = aTile->mCenterX;
        float aCenterY = aTile->mCenterY;
        
        if(aTile->mMultiPart)
        {
            Log("WHAT THE HELL???\n");
            
        }
        
        if(aTile->mMulti)
        {
            aCenterX += aTile->mOffsetX;
            aCenterY += aTile->mOffsetY;
        }
        
        while(mDirtTop[aGridX] <= aGridY)
        {
            
            
            //mAnimations.Add(GenerateAnimationDirtDestroy(aGridX, mDirtTop[aGridX]));
            mDirtTop[aGridX]++;
            DestroyDirtAnimation(aGridX, mDirtTop[aGridX]);
            DestroyCoinScan(aGridX, mDirtTop[aGridX]);
            
        }
        
        
        if(aTile->mMulti)
        {
            GameTile *aPart = 0;
            
            for(int i=0;i<aTile->mMultiPartCount;i++)
            {
                aPart = ((GameTile *)(aTile->mMultiPartList[i]));
                
                int aGridX = aPart->mGridX;
                int aGridY = aPart->mGridY;
                
                while(mDirtTop[aGridX] <= aGridY)
                {
                    mDirtTop[aGridX]++;
                    DestroyDirtAnimation(aGridX, mDirtTop[aGridX]);
                    DestroyCoinScan(aGridX, mDirtTop[aGridX]);
                }
            }
        }
        
        if(aTile->mTileType == GAME_TILE_TYPE_TREASURE)
        {
            gApp->mSoundDiscoverTreasure.Play();
            
            GameTileTreasure *aTreasure = (GameTileTreasure *)aTile;
            
            if(aTreasure != 0)
            {
                AddScore(300, pGridX, pGridY, true);
                
                gGame->DiscoverTreasure(aTreasure, aCenterX, aCenterY);
            }
            
            aDeleteTile = true;
            //aDeleteTile = false;
        }
        
        /*else if(aTile->mTileType == GAME_TILE_TYPE_POWERUP)
         {
         GameTilePowerUp *aTilePowerup = ((GameTilePowerUp *)aTile);
         
         if(aTilePowerup != 0)
         {
         
         }
         }*/
        
        if(aTile->mTileType == GAME_TILE_TYPE_STAR)
        {
            GameTileStar *aTileStar = ((GameTileStar *)aTile);
            
            if(aTileStar != 0)
            {
                gApp->mSoundDiscoverStar.Play();
                
                if(gGame)
                {
                    gGame->DiscoverStar(aTileStar, aCenterX, aCenterY);
                    
                    if(gGame->mDiscoverStarCount >= 3)
                    {
                        ActionEnqueue(BOARD_ACTION_LEVEL_UP);
                    }
                }
            }
            
            aDeleteTile = true;
        }
        
        
        
        if((aTile->mTileType == GAME_TILE_TYPE_ROCK) || (aTile->mTileType == GAME_TILE_TYPE_COLOR_ROCK) || (aTile->mTileType == GAME_TILE_TYPE_METAL))
        {
            if(mSoundTimerDiscoverGeneric <= 0)
            {
                mSoundTimerDiscoverGeneric = 9;
                gApp->mSoundDiscoverGeneric.Play();
            }
        }
        
        
        if(aDeleteTile == true)
        {
            DeleteTile(pGridX, pGridY);
        }
        
        CalculateAdjustedDirtTop();
        
        ActionEnqueue(BOARD_ACTION_TOPPLING);
    }
}

void Board::Save(const char *pPath)
{
    mUtils.Save(pPath);
}

void Board::Load(const char *pPath)
{
    mUtils.Load(pPath);
    CalculateAdjustedDirtTop();
    RandomizeBoard();
}

void Board::LevelUp()
{
    SetInactive(BOARD_ACTION_LEVEL_UP);
    SetInactive(BOARD_ACTION_GAME_OVER);
    
    if(gGame->mLevelCompleteOverlay)
    {
        gGame->mLevelCompleteOverlay->Kill();
        gGame->mLevelCompleteOverlay = 0;
    }
    
    gGame->mLevelComplete = false;
    
    mFinished = false;
    mFinishedTimer = 0;
    mFinishedLevelUp = false;
    mFinishedGameOver = false;
    
    ActionEnqueue(BOARD_ACTION_LEVEL_UP);
}

void Board::SetStartMoveCount(int pMoves)
{
    mStats->mMoveCount = pMoves;
    mStats->mMoveCountTotal = pMoves;
}

ComboStats::ComboStats()
{
    Reset();
    
}

void ComboStats::Reset()
{
    mLength = 0;
    mTileCount = 0;
    mToppleCount = 0;
    mOrbCount = 0;
    mJarCount = 0;
    mMatchCount = 0;
}

LevelStats::LevelStats()
{
    mDepth = 0;
    mDepthStart = 0;
    mDepthMax = 0;
    
    mMoveCount = 5;
    mMoveCountTotal = mMoveCount;
    mMoveCountUsed = 0;
    
    mDestroyedCountTotal = 0;
    mDestroyedCountDirt = 0;
    mDestroyedCountRock = 0;
    mDestroyedCountMatchable = 0;
    
    mComboActive = false;
    mComboCurrent.Reset();
    mComboRecent.Reset();
    mComboBest.Reset();
    
    mPlayTime = 0;
    mPlayTimeSeconds = 0;
    mPlayTimeMinutes = 0;
}

void LevelStats::Update()
{
    mPlayTime++;
    mPlayTimeSeconds++;
    
    if(mPlayTimeSeconds >= 60)
    {
        mPlayTimeSeconds = 0;
        mPlayTimeMinutes++;
    }
}

void LevelStats::ComboAddMatch(int pTileCount)
{
    mComboActive = true;
    mComboCurrent.mMatchCount++;
    mComboCurrent.mLength++;
    mComboCurrent.mTileCount += pTileCount;
    ComboRefresh();
}

void LevelStats::ComboAddTopple(int pTileCount)
{
    mComboActive = true;
    mComboCurrent.mToppleCount++;
    mComboCurrent.mLength++;
    mComboCurrent.mTileCount += pTileCount;
    ComboRefresh();
}

void LevelStats::ComboAddOrb(int pTileCount)
{
    mComboActive = true;
    mComboCurrent.mOrbCount++;
    mComboCurrent.mLength++;
    mComboCurrent.mTileCount += pTileCount;
    ComboRefresh();
}

void LevelStats::ComboAddJar(int pTileCount)
{
    mComboActive = true;
    mComboCurrent.mJarCount++;
    mComboCurrent.mLength++;
    mComboCurrent.mTileCount += pTileCount;
    ComboRefresh();
}

void LevelStats::ComboEnd()
{
    if(mComboActive)
    {
        ComboRefresh();
        mComboActive = false;
        mComboCurrent.Reset();
    }
}

void LevelStats::ComboRefresh()
{
    if(mComboActive)
    {
        mComboRecent.mLength = mComboCurrent.mLength;
        mComboRecent.mTileCount = mComboCurrent.mTileCount;
        mComboRecent.mToppleCount = mComboCurrent.mToppleCount;
        mComboRecent.mOrbCount = mComboCurrent.mOrbCount;
        mComboRecent.mJarCount = mComboCurrent.mJarCount;
        mComboRecent.mMatchCount = mComboCurrent.mMatchCount;
        
        //if(mComboCurrent.mLength > mComboBest.mLength)mComboBest.mLength = mComboCurrent.mLength;
        
    }
}
