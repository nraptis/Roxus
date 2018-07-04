//
//  BoardGeneric.cpp
//  Bone
//
//  Created by Nick Raptis on 8/6/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "BoardGeneric.h"
#include "core_includes.h"

BoardGeneric::BoardGeneric()
{
    //mActionQueue.mBoard = this;
    
    mGridGameTile = 0;
    
    mGridWidth = 0;
    mGridHeight = 0;
    
    mGridScreenTop = 0;
    mGridScreenHeight = 0;
    
    mGridWidth = 0;
    mGridHeight = 0;
    
    mTileWidth = 80.0f;
    mTileHeight = 80.0f;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mMatchTypeCount = 3;
    
    mMatchAllowDiagonal = true;
    
    mMatch = 0;
    
    mMatchCount = 0;
    mMatchSize = 0;
    

    
    mLayerMatchType.mName = "Layer - Match Type";
    mLayerMatchCheck.mName = "Layer - Match Check";
    mLayerMatchFlagged.mName = "Layer - Match Flagged";
    mLayerMatchStackX.mName = "Layer - Match Stack X";
    mLayerMatchStackY.mName = "Layer - Match Stack Y";
    
    
    AddLayer(&mLayerMatchType);
    AddLayer(&mLayerMatchCheck);
    AddLayer(&mLayerMatchFlagged);
    AddLayer(&mLayerMatchCount);
    
    AddLayer(&mLayerMatchStackX);
    AddLayer(&mLayerMatchStackY);
    
    
    GridChanged();
    
}

BoardGeneric::~BoardGeneric()
{
    FreeGrid();
}


void BoardGeneric::Update()
{
    
    /*
    
    EnumList(GameTileOld, aTile, mTileListKilled)
    {
        aTile->mKill--;
        if(aTile->mKill <= 0)
        {
            mTileListDelete.Add(aTile);
        }
    }
    
    EnumList(GameTileOld, aTile, mTileListDelete)
    {
        mTileListKilled.Remove(aTile);
        delete aTile;
    }
    
    mTileListDelete.RemoveAll();
     
    */
    
    
    EnumList(BoardGenericTile, aTileDelete, mTilesDeleted)
    {
        aTileDelete->mTimerDelete--;
        
        if(aTileDelete->mTimerDelete <= 0)
        {
            mTilesDeletedThisUpdate.Add(aTileDelete);
        }
    }
    
    EnumList(BoardGenericTile, aTileDelete, mTilesDeletedThisUpdate)
    {
        mTilesDeleted.Remove(aTileDelete);
        delete aTileDelete;
    }
    
    mTilesDeletedThisUpdate.mCount = 0;
    
    
    
    
    ProcessActionQueue();
}

void BoardGeneric::Draw()
{
    
}

int BoardGeneric::GetTouchGridX(float pX)
{
    int aReturn = -1;
    pX += mOffsetX;
    
    if(pX > 0)
    {
        pX /= mTileWidth;
        if(pX < mGridWidth)
        {
            aReturn = pX;
        }
    }
    return aReturn;
}

int BoardGeneric::GetTouchGridY(float pY)
{
    int aReturn = -1;
    pY += mOffsetY;
    
    if(pY > 0)
    {
        pY /= mTileHeight;
        if(pY < mGridHeight)
        {
            aReturn = pY;
        }
    }
    return aReturn;
}

float BoardGeneric::GetTileCenterX(int pGridX)
{
    return (float)pGridX * mTileWidth + (mTileWidth / 2.0f);
}

float BoardGeneric::GetTileCenterY(int pGridY)
{
    return (float)pGridY * mTileHeight + (mTileHeight / 2.0f);
}


void BoardGeneric::GenerateTiles(int pGridWidth, int pGridHeight)
{
    SizeGrid(pGridWidth, pGridHeight);
    
    /*
    
    int aDirtFloor = 11;
    
    for(int i=0;i<mWidth;i++)
    {
        for(int n=0;n<aDirtFloor;n++)
        {
            mTile[i][n] = new GameTileOldBubble();
            
            if(gBoard)((GameTileOldBubble *)mTile[i][n])->SetUp(gRand.Get(gBoard->mTileTypeCount), i, n);
            else ((GameTileOldBubble *)mTile[i][n])->SetUp(gRand.Get(5), i, n);
        }
    }
    
    for(int i=0;i<mWidth;i++)
    {
        for(int n=aDirtFloor;n<(mHeight - 1);n++)
        {
            mTile[i][n] = new GameTileOldDirt();
            mTile[i][n]->SetUp(i, n);
        }
    }
    
    for(int i=0;i<mWidth;i++)
    {
        mTile[i][mHeight - 1] = new GameTileOldRock();
        mTile[i][mHeight - 1]->SetUp(i, (mHeight - 1));
    }
    
    */
    
}

bool BoardGeneric::AllowClick()
{
    bool aReturn = true;
    
    return aReturn;
}

bool BoardGeneric::AllowDestroy()
{
    bool aReturn = true;
    
    return aReturn;
}

bool BoardGeneric::AllowShift()
{
    bool aReturn = true;
    
    return aReturn;
}


/*

bool BoardGeneric::ActionIsActive(int pActionID)
{
    bool aReturn = false;
    
    
    
    return aReturn;
}

bool BoardGeneric::ActionIsEnqueued(int pActionID)
{
    bool aReturn = false;
    
    
    
    return aReturn;
}

void BoardGeneric::ActionStart(int pActionID)
{
    mActionQueue.ActionStop(pActionID);
    //mActionQueue.ActionStart(pActionID);
}

void BoardGeneric::ActionStop(int pActionID)
{
    mActionQueue.ActionStop(pActionID);
    //mActionQueue.ActionStop(pActionID);
}

void BoardGeneric::ActionEnqueue(int pActionID)
{
    mActionQueue.ActionIsEnqueued(pActionID);
    //mActionQueue.ActionEnqueue(pActionID);
}

bool BoardGeneric::ActionIsActive(int pActionID)
{
    return mActionQueue.ActionIsOn(pActionID);
    //return mActionQueue.ActionIsActive(pActionID);
}
 
*/

void BoardGeneric::ActionExecute(int pActionIndex)
{
    printf("BoardGeneric::ActionExecute(%d)\n", pActionIndex);
}

FString BoardGeneric::GetActionName(int pActionID)
{
    FString aReturn;
    
    if(pActionID == BOARD_ACTION_CHECK_BOARD)aReturn = "CHECK";
    else if(pActionID == BOARD_ACTION_DESTROYING)aReturn = "DESTROY";
    else if(pActionID == BOARD_ACTION_MATCHING)aReturn = "MATCHING";
    else if(pActionID == BOARD_ACTION_COMBOING)aReturn = "COMBO";
    else if(pActionID == BOARD_ACTION_DRAGGING)aReturn = "DRAG";
    else if(pActionID == BOARD_ACTION_SHIFTING)aReturn = "SHIFT";
    else if(pActionID == BOARD_ACTION_TOPPLING)aReturn = "TOPPLE";
    else if(pActionID == BOARD_ACTION_SETTLED)aReturn = "SETTLING";
    else if(pActionID == BOARD_ACTION_SETTLE_PENDING)aReturn = "SETTLE_PENDING";
    else if(pActionID == BOARD_ACTION_FILLLING_HOLES)aReturn = "FILL_HOLES";
    else if(pActionID == BOARD_ACTION_SHIFT_COMPLETE_TRIGGER)aReturn = "SHIFT_COMPLETE";
    else if(pActionID == BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER)aReturn = "TOPPLE_COMPLETE";
    else if(pActionID == BOARD_ACTION_MATCHING_COMPLETE_TRIGGER)aReturn = "MATCHING_COMPLETE";
    else if(pActionID == BOARD_ACTION_TUTORIAL)aReturn = "TUTORIAL";
    else if(pActionID == BOARD_ACTION_LEVEL_UP)aReturn = "LEVEL_UP";
    else if(pActionID == BOARD_ACTION_GAME_OVER)aReturn = "GAME_OVER";
    else if(pActionID == BOARD_ACTION_INITIALIZING)aReturn = "INIT";
    else aReturn = "UNKNOWN";
    
    if(aReturn.mLength <= 0)aReturn = "NULL";
    return aReturn;
    
}




void BoardGeneric::AddLayer(BoardGenericLayer *pLayer)
{
    mLayerList += pLayer;
    
}

void BoardGeneric::SizeGrid(int pGridWidth, int pGridHeight)
{
    FreeGrid();
    
    mGridWidth = pGridWidth;
    mGridHeight = pGridHeight;
    
    mGridGameTile = new BoardGenericTile**[mGridWidth];
    
    for(int i=0;i<mGridWidth;i++)
    {
        mGridGameTile[i] = new BoardGenericTile*[mGridHeight];
        for(int n=0;n<mGridHeight;n++)
        {
            mGridGameTile[i][n] = 0;
        }
    }
    
    EnumList(BoardGenericLayer, aLayer, mLayerList)
    {
        aLayer->SetSize(mGridWidth, mGridHeight);
    }
    
    GridChanged();
}





void BoardGeneric::ResizeGrid(int pGridWidth, int pGridHeight)
{
    if(pGridWidth <= 0 || pGridHeight <= 0)
    {
        FreeGrid();
    }
    else
    {
        BoardGenericTile ***aOld = mGridGameTile;
        
        int aWidthOld = mGridWidth;
        int aHeightOld = mGridHeight;
        
        mGridWidth = pGridWidth;
        mGridHeight = pGridHeight;
        
        mGridGameTile = new BoardGenericTile**[mGridWidth];
        
        for(int i=0;i<mGridWidth;i++)
        {
            mGridGameTile[i] = new BoardGenericTile*[mGridHeight];
            for(int n=0;n<mGridHeight;n++)
            {
                mGridGameTile[i][n] = 0;
            }
        }
        
        int aCopyWidth = aWidthOld;
        if(mGridWidth < aCopyWidth)aCopyWidth = mGridWidth;
        
        int aCopyHeight = aHeightOld;
        if(mGridHeight < aCopyHeight)aCopyHeight = mGridHeight;
        
        
        for(int i=0;i<aCopyWidth;i++)
        {
            for(int n=0;n<aCopyHeight;n++)
            {
                mGridGameTile[i][n] = aOld[i][n];
            }
        }
        
        
        for(int i=0;i<aWidthOld;i++)
        {
            for(int n=0;n<aHeightOld;n++)
            {
                
            }
            delete [] aOld[i];
        }
        delete [] aOld;
        
        EnumList(BoardGenericLayer, aLayer, mLayerList)
        {
            aLayer->Resize(mGridWidth, mGridHeight);
        }
    }
    
    GridChanged();
    
}

void BoardGeneric::FreeGrid()
{
    if(mGridGameTile)
    {
        for(int i=0;i<mGridWidth;i++)
        {
            for(int n=0;n<mGridHeight;n++)
            {
                DeleteTile(i, n);
                
                mGridGameTile[i][n] = 0;
            }
            delete [] mGridGameTile[i];
        }
        
        delete [] mGridGameTile;
        mGridGameTile = 0;
    }
    
    mGridWidth = 0;
    mGridHeight = 0;
    
    EnumList(BoardGenericLayer, aLayer, mLayerList)
    {
        aLayer->Free();
    }
    
    GridChanged();
}




void BoardGeneric::PadGrid(int pBlockCountTop, int pBlockCountBottom)
{
    
    int aNewHeight = mGridHeight + (pBlockCountTop + pBlockCountBottom);
    
    if(mGridWidth <= 0)mGridWidth = 7;
    
    if((aNewHeight <= 0) || (mGridHeight <= 0))
    {
        FreeGrid();
    }
    else
    {
        if(pBlockCountTop < 0)
        {
            int aCount = (-pBlockCountTop);
            for(int n=0;n<aCount;n++)
            {
                for(int i=0;i<mGridWidth;i++)
                {
                    DeleteTile(i, n);
                }
            }
        }
        
        if(pBlockCountBottom < 0)
        {
            for(int n=(mGridHeight+pBlockCountBottom);n<mGridHeight;n++)
            {
                for(int i=0;i<mGridWidth;i++)
                {
                    DeleteTile(i, n);
                }
            }
        }
        
        //
        //Step 2 = Populate placeholder grid with filler.
        //
        
        BoardGenericTile ***aNewTile = new BoardGenericTile**[mGridWidth];
        
        for(int i=0;i<mGridWidth;i++)
        {
            aNewTile[i] = new BoardGenericTile*[aNewHeight];
            for(int n=0;n<aNewHeight;n++)
            {
                aNewTile[i][n] = 0;
            }
        }
        
        int aCopyY = (-pBlockCountTop);
        for(int n=0;n<aNewHeight;n++)
        {
            if((aCopyY < mGridHeight) && (aCopyY >= 0))
            {
                for(int i=0;i<mGridWidth;i++)
                {
                    aNewTile[i][n] = mGridGameTile[i][aCopyY];
                    mGridGameTile[i][aCopyY] = 0;
                }
            }
            aCopyY++;
        }
        
        SizeGrid(mGridWidth, aNewHeight);
        
        for(int i=0;i<mGridWidth;i++)
        {
            for(int n=0;n<aNewHeight;n++)
            {
                BoardGenericTile *aTile = aNewTile[i][n];
                if(aTile)
                {
                    mGridGameTile[i][n] = aTile;
                    aTile->SetUp(i, n, mTileWidth, mTileHeight);
                }
                else
                {
                    mGridGameTile[i][n] = 0;
                }
            }
            
            delete [] aNewTile[i];
        }
        
        delete [] aNewTile;
        
#ifdef EDITOR_MODE
        
        //if(gEditor)gEditor->EditorFillWithDirt();
#else
        
#endif
        
    }
    
    GridChanged();
    
}

bool BoardGeneric::OnGrid(int pGridX, int pGridY)
{
    bool aReturn = ((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight));
    
    return aReturn;
}

bool BoardGeneric::CanSetTile(int pGridX, int pGridY, BoardGenericTile *pTile)
{
    bool aReturn = false;
    
    
    
    return aReturn;
}

bool BoardGeneric::SetTile(int pGridX, int pGridY, BoardGenericTile *pTile)
{
    if(OnGrid(pGridX, pGridY))
    {
        if(pTile->mMulti)
        {
            BoardGenericTile *aPart = 0;
            
            bool aIllegal = false;
            
            for(int i=0;i<pTile->mMultiPartCount;i++)
            {
                aPart = pTile->mMultiPartList[i];
                
                if(OnGrid(aPart->mMultiPartGridOffsetX + pGridX, aPart->mMultiPartGridOffsetY + pGridY) == false)
                {
                    aIllegal = true;
                }
            }
            
            if(aIllegal == true)
            {
                return false;
            }
            
            aPart = 0;
            
            for(int i=0;i<pTile->mMultiPartCount;i++)
            {
                aPart = pTile->mMultiPartList[i];
                
                DeleteTile(aPart->mMultiPartGridOffsetX + pGridX, aPart->mMultiPartGridOffsetY + pGridY);
            }
        }
        
        DeleteTile(pGridX, pGridY);
        
        if(pTile->mMulti)
        {
            BoardGenericTile *aPart = 0;
            
            for(int i=0;i<pTile->mMultiPartCount;i++)
            {
                aPart = pTile->mMultiPartList[i];
                
                aPart->mGridX = pGridX + aPart->mMultiPartGridOffsetX;
                aPart->mGridY = pGridY + aPart->mMultiPartGridOffsetY;
                
                mGridGameTile[aPart->mGridX][aPart->mGridY] = aPart;
            }
            
            mGridGameTile[pGridX][pGridY] = pTile;
            pTile->SetUp(pGridX, pGridY, mTileWidth, mTileHeight);
        }
        else
        {
            mGridGameTile[pGridX][pGridY] = pTile;
            pTile->SetUp(pGridX, pGridY, mTileWidth, mTileHeight);
        }
    }
    else
    {
        return false;
    }
    
    return true;
}

BoardGenericTile *BoardGeneric::GetTileBase(int pGridX, int pGridY)
{
    BoardGenericTile *aReturn = 0;
    
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
    {
        aReturn = mGridGameTile[pGridX][pGridY];
        
        if(aReturn)
        {
            if((aReturn->mMultiPart == true) && (aReturn->mMultiPartParent != 0))
            {
                aReturn = aReturn->mMultiPartParent;
            }
        }
    }
    
    return aReturn;
}

BoardGenericTile *BoardGeneric::GetTileBase(int pGridX, int pGridY, int pTileType)
{
    BoardGenericTile *aReturn = GetTileBase(pGridX, pGridY);
    
    if(aReturn != 0)
    {
        if(aReturn->mTileType != pTileType)
        {
            aReturn = 0;
        }
    }
    
    return aReturn;
}

BoardGenericTile *BoardGeneric::RemoveTile(int pGridX, int pGridY)
{
    BoardGenericTile *aReturn = GetTileBase(pGridX, pGridY);
    
    if(aReturn)
    {
        if(aReturn->mMulti)
        {
            BoardGenericTile *aPart = 0;
            int aGridX = 0;
            int aGridY = 0;
            
            for(int i=0;i<aReturn->mMultiPartCount;i++)
            {
                aPart = aReturn->mMultiPartList[i];
                
                aGridX = aPart->mGridX;
                aGridY = aPart->mGridY;
                
                mGridGameTile[aGridX][aGridY] = 0;
            }
            
            mGridGameTile[aReturn->mGridX][aReturn->mGridY] = 0;
        }
        else
        {
            mGridGameTile[pGridX][pGridY] = 0;
        }
    }
    
    return aReturn;
}

void BoardGeneric::DeleteTile(int pGridX, int pGridY)
{
    
    BoardGenericTile *aTile = RemoveTile(pGridX, pGridY);
    
    if(aTile != 0)
    {
        aTile->mTimerDelete = 20;
        mTilesDeleted.Add(aTile);
        
        /*
        
        if((aTile->mTileType == GAME_TILE_TYPE_RELIC) || (aTile->mTileType == GAME_TILE_TYPE_RELIC_PIECE))
        {
            GameTileOldRelic *aRelic = 0;
            if(aTile->mTileType == GAME_TILE_TYPE_RELIC)
            {
                aRelic = (GameTileOldRelic *)aTile;
            }
            else
            {
                GameTileOldRelicPiece *aPiece = (GameTileOldRelicPiece *)aTile;
                aRelic = aPiece->mRelic;
            }
            
            if(aRelic)
            {
                EnumList(GameTileOldRelicPiece, aPiece, aRelic->mRelicPieceList)
                {
                    if((aPiece->mGridX >= 0) && (aPiece->mGridY >= 0) && (aPiece->mGridX < mWidth) && (aPiece->mGridY < mHeight))
                    {
                        mTile[aPiece->mGridX][aPiece->mGridY] = 0;
                    }
                }
                
                mTile[aRelic->mGridX][aRelic->mGridY] = 0;
                
                aRelic->mKill = 24;
                mTileListKilled.Add(aRelic);
            }
        }
        else
        {
            mTile[pGridX][pGridY] = 0;
            
            aTile->mKill = 24;
            mTileListKilled.Add(aTile);
        }
        
        */
        
        //mGridGameTile[pGridX][pGridY] = 0;
        
        //delete aTile;
    }
}


/*
bool GameBoardGrid::IsMatch(int pGridX, int pGridY)
{
    
    bool aReturn = false;
    
    GameTile *aTile = GetTile(pGridX, pGridY);
    GameTile *aCheckTile = 0;
    
    if(aTile)
    {
        ClearDidCheck();
        ClearDidMatch();
        
        if(aTile->mTileType == GAME_TILE_TYPE_BUBBLE)
        {
            int aType = ((GameTileBubble *)aTile)->mMatchType;
            int aStackCount = 1;
            
            mTileStack[0] = aTile;
            
            int aLoops = 0;
            
            while(aStackCount > 0)
            {
                aLoops++;
                aStackCount--;
                
                GameTile *aPop = mTileStack[aStackCount];
                
                aPop->mDidMatch = true;
                
                int aGridX = aPop->mGridX;
                int aGridY = aPop->mGridY;
                
                int aCheckX, aCheckY;
                if(aGridX > 0)
                {
                    aCheckX = aGridX - 1;
                    aCheckY = aGridY;
                    
                    if(mDidCheck[aCheckX][aCheckY] == false)
                    {
                        mDidCheck[aCheckX][aCheckY] = true;
                        aCheckTile = mTile[aCheckX][aCheckY];
                        if(aCheckTile)
                        {
                            if((aCheckTile->mTileType == GAME_TILE_TYPE_BUBBLE) && (aCheckTile->mDestroy == false))
                            {
                                if(((GameTileBubble *)aCheckTile)->mMatchType == aType)
                                {
                                    mTileStack[aStackCount] = aCheckTile;
                                    aStackCount++;
                                }
                            }
                        }
                    }
                }
                if(aGridX < (mWidth - 1))
                {
                    aCheckX = aGridX + 1;
                    aCheckY = aGridY;
                    if(mDidCheck[aCheckX][aCheckY] == false)
                    {
                        mDidCheck[aCheckX][aCheckY] = true;
                        aCheckTile = mTile[aCheckX][aCheckY];
                        if(aCheckTile)
                        {
                            if((aCheckTile->mTileType == GAME_TILE_TYPE_BUBBLE) && (aCheckTile->mDestroy == false))
                            {
                                if(((GameTileBubble *)aCheckTile)->mMatchType == aType)
                                {
                                    mTileStack[aStackCount] = aCheckTile;
                                    aStackCount++;
                                }
                            }
                        }
                    }
                }
                
                if(aGridY > 0)
                {
                    aCheckX = aGridX;
                    aCheckY = aGridY - 1;
                    
                    if(mDidCheck[aCheckX][aCheckY] == false)
                    {
                        mDidCheck[aCheckX][aCheckY] = true;
                        aCheckTile = mTile[aCheckX][aCheckY];
                        if(aCheckTile)
                        {
                            if((aCheckTile->mTileType == GAME_TILE_TYPE_BUBBLE) && (aCheckTile->mDestroy == false))
                                //if(aCheckTile->mTileType == GAME_TILE_TYPE_BUBBLE)
                            {
                                if(((GameTileBubble *)aCheckTile)->mMatchType == aType)
                                {
                                    mTileStack[aStackCount] = aCheckTile;
                                    aStackCount++;
                                }
                            }
                        }
                    }
                }
                
                if(aGridY < (mHeight - 1))
                {
                    aCheckX = aGridX;
                    aCheckY = aGridY + 1;
                    if(mDidCheck[aCheckX][aCheckY] == false)
                    {
                        mDidCheck[aCheckX][aCheckY] = true;
                        aCheckTile = mTile[aCheckX][aCheckY];
                        if(aCheckTile)
                        {
                            if((aCheckTile->mTileType == GAME_TILE_TYPE_BUBBLE) && (aCheckTile->mDestroy == false))
                            {
                                if(((GameTileBubble *)aCheckTile)->mMatchType == aType)
                                {
                                    mTileStack[aStackCount] = aCheckTile;
                                    aStackCount++;
                                }
                            }
                        }
                    }
                }
            }
            aReturn = GetMatchCount() >= 3;
        }
    }
    return aReturn;
}
*/

void BoardGeneric::MatchComputeAll()
{
    MatchComputeAll(0, mGridHeight - 1);
}

void BoardGeneric::MatchComputeAll(int pGridStartY, int pGridEndY)
{
    MatchComputeAll(0, pGridStartY, mGridWidth - 1, pGridEndY);
}

void BoardGeneric::MatchComputeAll(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY)
{
    mMatchCount = 0;
    
    if(pGridStartX >= mGridWidth)pGridStartX = (mGridWidth - 1);
    if(pGridEndX >= mGridWidth)pGridEndX = (mGridWidth - 1);
    if(pGridStartY >= mGridHeight)pGridStartY = (mGridHeight - 1);
    if(pGridEndY >= mGridHeight)pGridEndY = (mGridHeight - 1);
    
    if(pGridStartX < 0)pGridStartX = 0;
    if(pGridStartY < 0)pGridStartY = 0;
    
    if((pGridEndX < pGridStartX) || (pGridEndY < pGridStartY))
    {
        return;
    }
    
    BoardGenericMatch *aMatch = 0;
    
    int aStackCount = 0;
    
    int *aStackX = mLayerMatchStackX.mDataBase;
    int *aStackY = mLayerMatchStackY.mDataBase;
    
    int **aMatchType = mLayerMatchType.mData;
    int **aMatchCheck = mLayerMatchCheck.mData;
    int **aMatchFlagged = mLayerMatchFlagged.mData;
    
    int aGridX = 0;
    int aGridY = 0;
    
    int aCheckX = 0;
    int aCheckY = 0;
    
    int aType = 0;
    int aFlagged = 0;
    
    int aCheckIndex = 1;
    
    BoardGenericTile *aTile = 0;
    
    for(int i=pGridStartX;i<=pGridEndX;i++)
    {
        for(int n=pGridStartY;n<=pGridEndY;n++)
        {
            aTile = mGridGameTile[i][n];
            
            aType = -1;
            
            if(aTile)
            {
                if((aTile->mDestroyed == false) && (aTile->mDestroyed == false))
                {
                    aType = aTile->mMatchType;
                    
                }
            }
            
            mLayerMatchType.Set(i, n, aType);
            mLayerMatchCheck.Set(i, n, 0);
            mLayerMatchFlagged.Set(i, n, 0);
            
        }
    }
    
    
    for(int i=pGridStartX;i<=pGridEndX;i++)
    {
        for(int n=pGridStartY;n<=pGridEndY;n++)
        {
            aType = aMatchType[i][n];
            aFlagged = aMatchFlagged[i][n];
            
            if((aType >= 0) && (aFlagged == 0))
            {
                if(mMatchCount >= mMatchSize)
                {
                    int aMatchSize = mMatchCount + (mMatchCount / 2) + 1;
                    
                    BoardGenericMatch **aMatchNew = new BoardGenericMatch*[aMatchSize];
                    
                    for(int k=0;k<mMatchSize;k++)
                    {
                        aMatchNew[k] = mMatch[k];
                    }
                    
                    delete [] mMatch;
                    
                    mMatch = aMatchNew;
                    
                    for(int k=mMatchSize;k<aMatchSize;k++)
                    {
                        mMatch[k] = new BoardGenericMatch();
                    }
                    
                    mMatchSize = aMatchSize;
                }
                
                aMatch = mMatch[mMatchCount];
                mMatchCount++;
                
                aMatch->Reset();
                
                aStackX[0] = i;
                aStackY[0] = n;
                
                aCheckIndex++;
                aMatchCheck[i][n] = aCheckIndex;

                aStackCount = 1;

                while(aStackCount > 0)
                {
                    aStackCount--;
                    
                    aGridX = aStackX[aStackCount];
                    aGridY = aStackY[aStackCount];
                    
                    aMatchFlagged[aGridX][aGridY] = true;

                    aMatch->Add(aGridX, aGridY);
                    
                    if(aGridX > pGridStartX)
                    {
                        aCheckX = aGridX - 1;
                        aCheckY = aGridY;
                        
                        if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                        {
                            aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                            
                            if(aType == aMatchType[aCheckX][aCheckY])
                            {
                                aStackX[aStackCount] = aCheckX;
                                aStackY[aStackCount] = aCheckY;
                                aStackCount++;
                            }
                        }
                        
                        if(mMatchAllowDiagonal)
                        {
                            if(aGridY < pGridEndY)
                            {
                                aCheckY = aGridY + 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                            }
                            
                            if(aGridY > pGridStartY)
                            {
                                aCheckY = aGridY - 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                            }
                            
                        }
                        
                    }
                    if(aGridX < (pGridEndX))
                    {
                        aCheckX = aGridX + 1;
                        aCheckY = aGridY;
                        
                        if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                        {
                            aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                            
                            if(aType == aMatchType[aCheckX][aCheckY])
                            {
                                aStackX[aStackCount] = aCheckX;
                                aStackY[aStackCount] = aCheckY;
                                aStackCount++;
                            }
                        }
                        
                        
                        if(mMatchAllowDiagonal)
                        {
                            if(aGridY < pGridEndY)
                            {
                                aCheckY = aGridY + 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                            }
                            
                            if(aGridY > pGridStartY)
                            {
                                aCheckY = aGridY - 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                            }
                            
                        }
                        
                        
                    }
                    
                    if(aGridY > pGridStartY)
                    {
                        aCheckX = aGridX;
                        aCheckY = aGridY - 1;
                        
                        if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                        {
                            aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                            
                            if(aType == aMatchType[aCheckX][aCheckY])
                            {
                                aStackX[aStackCount] = aCheckX;
                                aStackY[aStackCount] = aCheckY;
                                aStackCount++;
                            }
                        }
                        
                        if(mMatchAllowDiagonal)
                        {
                            if(aGridX < (pGridEndX))
                            {
                                aCheckX = aGridX + 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                            }
                            if(aGridX > pGridStartX)
                            {
                                aCheckX = aGridX - 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                                
                            }
                        }
                        
                    }
                    
                    if(aGridY < pGridEndY)
                    {
                        aCheckX = aGridX;
                        aCheckY = aGridY + 1;
                        
                        if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                        {
                            aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                            
                            if(aType == aMatchType[aCheckX][aCheckY])
                            {
                                aStackX[aStackCount] = aCheckX;
                                aStackY[aStackCount] = aCheckY;
                                aStackCount++;
                            }
                        }
                        
                        if(mMatchAllowDiagonal)
                        {
                            if(aGridX < (pGridEndX))
                            {
                                aCheckX = aGridX + 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                            }
                            if(aGridX > pGridStartX)
                            {
                                aCheckX = aGridX - 1;
                                
                                if(aMatchCheck[aCheckX][aCheckY] != aCheckIndex)
                                {
                                    aMatchCheck[aCheckX][aCheckY] = aCheckIndex;
                                    
                                    if(aType == aMatchType[aCheckX][aCheckY])
                                    {
                                        aStackX[aStackCount] = aCheckX;
                                        aStackY[aStackCount] = aCheckY;
                                        aStackCount++;
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    for(int i=0;i<mMatchCount;i++)
    {
        aMatch = mMatch[i];
        aMatch->Compute(0, 0, mGridWidth - 1, mGridHeight - 1);
    }
}

void BoardGeneric::MatchListSort()
{
    BoardGenericMatch *aMatchSortKey = 0;
    BoardGenericMatch *aMatchHold = 0;
    
    int aCheck = 0;
    
    for(int aStart = 1;aStart<mMatchCount;aStart++)
    {
        aMatchSortKey = mMatch[aStart];
        aCheck=aStart-1;
        while(aCheck >= 0 && (mMatch[aCheck]->mCount) < aMatchSortKey->mCount)
        {
            mMatch[aCheck+1] = mMatch[aCheck];
            aCheck--;
        }
        mMatch[aCheck+1]=aMatchSortKey;
    }
    
    int aMatchCountTies = 1;
    
    int aIndex = 0;
    int aSeek = 0;
    bool aContinue = true;
    
    int aRand = 0;
    
    while(aIndex < mMatchCount)
    {
        aMatchCountTies = 1;
        
        aSeek = aIndex + 1;
        
        aContinue = true;
        
        
        while((aSeek < mMatchCount) && (aContinue == true))
        {
            if(mMatch[aSeek]->mCount != mMatch[aIndex]->mCount)
            {
                aContinue = false;
            }
            else
            {
                aMatchCountTies++;
            }
            aSeek++;
        }
        
        if(aMatchCountTies > 1)
        {
            for(int i=0;i<aMatchCountTies;i++)
            {
                aRand = gRand.Get(aMatchCountTies);
                
                if(aRand != i)
                {
                    aMatchHold = mMatch[aIndex + i];
                    
                    mMatch[aIndex + i] = mMatch[aIndex + aRand];
                    
                    mMatch[aIndex + aRand] = aMatchHold;
                }
            }
        }
        
        aIndex += aMatchCountTies;
    }
}

void BoardGeneric::PrintMatchContent(BoardGenericMatch *pMatch)
{
    FString aMatchContent = "Match[";
    
    for(int i=0;i<pMatch->mCount;i++)
    {
        BoardGenericTile *aTile = GetTileBase(pMatch->mX[i], pMatch->mY[i]);
        
        if(aTile)
        {
            aMatchContent += FString("(") + FString(aTile->mTileType) + FString(")");
        }
    }
    
    aMatchContent += "]";
    
    Log(aMatchContent.c());
    
}

FParticle *BoardGeneric::SpawnParticleSequenceGrid(FSpriteSequence *pSequence, int pGridX, int pGridY)
{
    return SpawnParticleSequence(pSequence, GetTileCenterX(pGridX), GetTileCenterY(pGridY));
}

FParticle *BoardGeneric::SpawnParticleSequence(FSpriteSequence *pSequence, float pX, float pY)
{
    FParticle *aParticle = new FParticle();
    
    aParticle->SetSpriteSequence(pSequence);
    
    aParticle->SetPos(pX, pY);
    
    aParticle->mFrameLoop = false;
    aParticle->mFrameSpeed = 0.72f;
    
    return aParticle;
}


void BoardGeneric::ProcessActionQueue()
{
    int aAction = mActionQueue.DequeueAction();
    while(aAction != -1)
    {
        ActionExecute(aAction);
        aAction = mActionQueue.DequeueAction();
    }
}

void BoardGeneric::ActionEnqueue(int pActionID)
{
    mActionQueue.ActionEnqueue(pActionID);
}

void BoardGeneric::SetActive(int pStateID)
{
    mActionQueue.SetActive(pStateID);
}

void BoardGeneric::SetInactive(int pStateID)
{
    mActionQueue.SetInactive(pStateID);
}


void BoardGeneric::Save(const char *pPath)
{
    
}

void BoardGeneric::Load(const char *pPath)
{
    
}
