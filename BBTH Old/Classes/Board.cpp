//
//  Board.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/11/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "Board.h"
#include "GLApp.h"


Board *gBoard = 0;

Board::Board(){
    gBoard = this;
    
    mGridWidth = 0;
    mGridHeight = 0;
    
    mGridScreenTop = 0;
    mGridScreenHeight = 16;
    
    mGridDigZoneTop = 0;
    mGridDigZoneHeight = 3;
    
    mMatchTypeCount = 4;
    
    mTile = 0;
    
    mActionTimer = 0;
    
    mDirtTop = 0;
    mMultiPartBottom = 0;
    
    mTouchGridX = -1;
    mTouchGridY = -1;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mMatching = false;
    mMatchingTimer = 0;
    
    mToppling = false;
    mToppleCheck = false;
    
    mCascadeCheck = false;
    mCascadeComboCount = 0;
    
    SwapTilesCancel();
    
    mUtils = new BoardUtilities(this);
    
    SetFrame(0.0f, 0.0f, 512.0f, 512.0f);
}

Board::~Board(){
    gBoard = 0;
    
    delete mUtils;mUtils=0;
    
    FreeGrid();
}

void Board::Load(){
    
    FreeGrid();
    SizeGrid(9, 42);
    
    
    
    mGridScreenHeight = 14;
    
    mGridDigZoneTop = (mGridScreenTop + mGridScreenHeight - 1) - (mGridDigZoneHeight);
    
    
    for(int i=0;i<mGridWidth;i++){
        
        if(i < 3){
            mDirtTop[i] = mGridDigZoneTop + mGridDigZoneHeight;
        }
        else if(i < 5){
            mDirtTop[i] = mGridDigZoneTop + 1;
        }
        else if(i < 7){
            mDirtTop[i] = mGridDigZoneTop;
        }
        else{
            mDirtTop[i] = mGridDigZoneTop + mGridDigZoneHeight;
        }
        
        
        
    }
    
    
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=0;aGridY<mGridHeight;aGridY++){
            if(aGridY < (mDirtTop[aGridX])){
                //if(gRand.Get(5) > 0){
                    
                    TileEgg *aTileEgg = new TileEgg();
                    aTileEgg->SetUp(aGridX, aGridY, gRand.Get(mMatchTypeCount));
                    mTile[aGridX][aGridY] = aTileEgg;
                
                //}
            }
        }
    }
    
    TileMulti *aMulti1 = new TileMulti();
    aMulti1->AddPart(0, 1);
    aMulti1->AddPart(1, 1);
    PlaceTileOnGrid(aMulti1, 2, 3);
    
    TileMulti *aMulti2 = new TileMulti();
    aMulti2->AddPart(0, 1);
    aMulti2->AddPart(1, 0);
    aMulti2->AddPart(1, 1);
    PlaceTileOnGrid(aMulti2, 5, 5);
    
    TileMulti *aMulti3 = new TileMulti();
    aMulti3->AddPart(1, 0);
    aMulti3->AddPart(2, 0);
    PlaceTileOnGrid(aMulti3, 0, 6);
    
    SetFrame(0.0f, 0.0f, ((float)mGridWidth) * gTileWidth, ((float)mGridHeight) * gTileHeight);
    
}

void Board::Layout(){
    
    
}

void Board::Update(){
    
    EnumList(Tile, aTile, mKillList){
        aTile->mKill--;
        if(aTile->mKill <= 0)mDeleteList.Add(aTile);
    }
    EnumList(Tile, aTile, mDeleteList){
        mKillList.Remove(aTile);
        delete aTile;
    }
    mDeleteList.RemoveAll();
    
    
    bool aAnyTileFalling = false;
    bool aAnyTileLanded = false;
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=0;aGridY<mGridHeight;aGridY++){
            Tile *aTile = mTile[aGridX][aGridY];
            if(aTile){
                bool aFalling = aTile->mFalling;
                
                aTile->Update();
                
                if(aFalling){
                    aAnyTileFalling = true;
                    if(!aTile->mFalling){
                        aAnyTileLanded = true;
                    }
                }
            }
        }
    }
    
    
    if(mToppling)
    {
        ActionRefresh();
        
        if(aAnyTileFalling == false){
            mToppling = false;
        }
    }
    
    if(mMatching){
        
        ActionRefresh();
        
        mToppleCheck = true;
        
        mMatchingTimer--;
        if(mMatchingTimer <= 0){
            MatchesComplete();
        }
    }
    
    if(mSwap){
        ActionRefresh();
        
        mSwapTimer--;
        
        float aCX1 = GetTileCenterX(mSwapTileGridX[0]);float aCY1 = GetTileCenterY(mSwapTileGridY[0]);
        float aCX2 = GetTileCenterX(mSwapTileGridX[1]);float aCY2 = GetTileCenterY(mSwapTileGridY[1]);
        
        if(mSwapTimer <= 0){
            mSwap = false;
            mSwapTimer = 0;
            mSwapTile[0] = 0;mSwapTile[1] = 0;
            
            TileEgg *aSwap1 = GetEgg(mSwapTileGridX[0], mSwapTileGridY[0]);
            TileEgg *aSwap2 = GetEgg(mSwapTileGridX[1], mSwapTileGridY[1]);
            
            if(aSwap1)aSwap1->Deselect();
            if(aSwap2)aSwap1->Deselect();
            
            RemoveTileFromGrid(mSwapTileGridX[0], mSwapTileGridY[0]);
            RemoveTileFromGrid(mSwapTileGridX[1], mSwapTileGridY[1]);
            
            PlaceTileOnGrid(aSwap2, mSwapTileGridX[0], mSwapTileGridY[0]);
            PlaceTileOnGrid(aSwap1, mSwapTileGridX[1], mSwapTileGridY[1]);
            
            //if(false && mSwapBlock){
            //mSwapBlock = false;
            
            //SwapTiles(mSwapTileGridX[0], mSwapTileGridY[0], mSwapTileGridX[1], mSwapTileGridY[1], true);
            //} else
            if(mSwapReverse == false){
                
                MatchesReset();
                
                MatchesFind(mSwapTileGridX[0], mSwapTileGridY[0]);
                MatchesFind(mSwapTileGridX[1], mSwapTileGridY[1]);
                
                if(mMatchList.mCount > 0){
                    
                    
                    MatchesBegin(true);
                    
                    mMatching = true;
                    mMatchingTimer = MATCH_TIME;
                    
                    //                    EnumList(BoardMatch, aMatch, mMatchList){
                    //                        for(int i=0;i<aMatch->mCount;i++){
                    //                            int aMatchX = aMatch->mX[i], aMatchY = aMatch->mY[i];
                    //                            TileEgg *aEgg = GetEgg(aMatchX, aMatchY);
                    //                            aEgg->Matched();
                    //                        }
                    //                    }
                }
                else{
                    SwapTiles(mSwapTileGridX[0], mSwapTileGridY[0], mSwapTileGridX[1], mSwapTileGridY[1], true);
                }
            }
            
        }
        else{
            float aPercent = ((float)mSwapTimer) / ((float)SWAP_TIME);
            aPercent = FAnimation::EaseInSine(aPercent);
            mSwapTile[0]->mX = aCX2 + (aCX1 - aCX2) * aPercent;mSwapTile[0]->mY = aCY2 + (aCY1 - aCY2) * aPercent;
            mSwapTile[1]->mX = aCX1 + (aCX2 - aCX1) * aPercent;mSwapTile[1]->mY = aCY1 + (aCY2 - aCY1) * aPercent;
        }
    }
    
    
    
    //mCascadeCheck
    
    if(ActionAllowed() && mToppleCheck){
        mToppleCheck = false;
        Topple();
    }
    
    if(ActionAllowed() && mCascadeCheck){
        mCascadeCheck = false;
        if(CascadeAllowed())
        {
            
            //Cascade();
        }
        
        if(mMatching == false)FindMoves();
        
    }
    
    if(mActionTimer > 0){
        mActionTimer--;
        if(mActionTimer < 0)mActionTimer=0;
    }
    
}

void Board::Draw(){
    
    Graphics::SetColor(0.02f, 0.03f, 0.11f, 1.0f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    Graphics::SetColor();
    
    int aStartY = 0;
    int aEndY = mGridHeight - 1 - gRand.Get(5);
    
    mUtils->DrawDirt(mDirtTop, mGridWidth, aStartY, aEndY);
    
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=mDirtTop[aGridX];aGridY<aEndY;aGridY++){
            if(mTile[aGridX][aGridY])mTile[aGridX][aGridY]->DrawBuried();
        }
    }
    
    for(int aDrawDepth=0;aDrawDepth<2;aDrawDepth++){
        
        bool aMatched = false;
        if(aDrawDepth > 0)aMatched = true;
        
        
        
        Graphics::BlendSetAdditive();
        for(int aDepth=0;aDepth<2;aDepth++){
            for(int aGridX=0;aGridX<mGridWidth;aGridX++){
                for(int aGridY=aStartY;aGridY<mDirtTop[aGridX];aGridY++){
                    if(mTile[aGridX][aGridY]){
                        if(mTile[aGridX][aGridY]->mMatched == aMatched)mTile[aGridX][aGridY]->DrawEffectsUnder(aDepth);
                    }
                }
            }
        }
        
        
        Graphics::BlendSetAlpha();
        for(int aGridX=0;aGridX<mGridWidth;aGridX++){
            for(int aGridY=aStartY;aGridY<mDirtTop[aGridX];aGridY++){
                if(mTile[aGridX][aGridY]){
                    if((mTile[aGridX][aGridY] != mSwapTile[0]) && (mTile[aGridX][aGridY] != mSwapTile[1]) && (mTile[aGridX][aGridY]->mMatched == aMatched)){
                        mTile[aGridX][aGridY]->Draw();
                    }
                }
            }
        }
        
    }
    
    Graphics::BlendSetAdditive();
    for(int aDepth=0;aDepth<2;aDepth++){
        for(int aGridX=0;aGridX<mGridWidth;aGridX++){
            for(int aGridY=aStartY;aGridY<mDirtTop[aGridX];aGridY++){
                if(mTile[aGridX][aGridY]){
                    if((mTile[aGridX][aGridY] != mSwapTile[0]) && (mTile[aGridX][aGridY] != mSwapTile[1])){
                        mTile[aGridX][aGridY]->DrawEffectsOver(aDepth);
                        
                        
                    }
                }
            }
        }
    }
    
    Graphics::BlendSetAlpha();
    
    if(mSwapTile[1])mSwapTile[1]->Draw();
    if(mSwapTile[0])mSwapTile[0]->Draw();
    
    Graphics::SetColor();
    
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=aStartY;aGridY<mGridHeight;aGridY++){
            
            Graphics::SetColor(0.5f, 0.65f, 0.5f, 0.5f);
            if(mFalling.Get(aGridX, aGridY)){
                Graphics::DrawRect(GetTileCenterX(aGridX)-5, GetTileCenterY(aGridY)-5, 11, 11);
            }
            
            Graphics::SetColor(1.0f, 1.0f, 0.01f, 1.0f);
            if(mFresh.Get(aGridX, aGridY)){
                Graphics::DrawRect(GetTileCenterX(aGridX)-20, GetTileCenterY(aGridY)-26, 11, 40);
            }
            
            
            Graphics::SetColor(0.33f, gRand.F(0.55, 0.66), 0.66f, 1.0f);
            if(mDestroyDirt.Get(aGridX, aGridY)){
                Graphics::DrawRect(GetTileCenterX(aGridX)-26, GetTileCenterY(aGridY)-26, 42, 42);
            }
            
            
            Graphics::SetColor(1.0f, 0.25f, 0.22f, 1.0f);
            if((aGridY >= mGridDigZoneTop) && (aGridY < (mGridDigZoneTop + mGridDigZoneHeight))){
                Graphics::DrawRect(GetTileCenterX(aGridX) - 9.0f, GetTileCenterY(aGridY) - 9.0f, 19.0f, 19.0f);
            }
        }
    }
}

void Board::TouchDown(float pX, float pY, void *pData){
    
    int aGridX = GetTouchGridX(pX);int aGridY = GetTouchGridY(pY);
    mTouchGridX = aGridX;mTouchGridY = aGridY;
    
    if(aGridX == -1 || aGridY == -1){
        printf("--- ALT ACTION ---\n\n");
        
        DestroyDirtAdjustUndershoot();
    }
    
    
    if(ActionAllowed())
    {
        if(Selectable(aGridX, aGridY)){
            TileEgg *aSwap = GetEgg(aGridX, aGridY);
            if(aSwap != 0){
                if(mSwapTile[0] == 0){
                    mSwapTile[0] = aSwap;
                    mSwapTileGridX[0] = aGridX;mSwapTileGridY[0] = aGridY;
                    mSwapDragStartX = pX;mSwapDragStartY = pY;
                    mSwapDragData = pData;
                    aSwap->Select();
                }
                else{
                    if(aSwap == mSwapTile[0]){
                        SwapTilesCancel();
                    }
                    else{
                        if(SwapTilesAllowed(mSwapTileGridX[0], mSwapTileGridY[0], aGridX, aGridY)){
                            //mSwapBlock = (SwapTilesAllowed(mSwapTileGridX[0], mSwapTileGridY[0], aGridX, aGridY) == false);
                            SwapTiles(mSwapTileGridX[0], mSwapTileGridY[0], aGridX, aGridY, false);
                        }
                        else{
                            SwapTilesCancel();
                        }
                    }
                }
            }
        } else {
            SwapTilesCancel();
        }
    }
}

void Board::TouchMove(float pX, float pY, void *pData){
    if((mSwapTile[0] != 0) && (mSwapTile[1] == 0))
    {
        if(ActionAllowed() && (pData == mSwapDragData))
        {
            float aThreshold = 40.0f;
            bool aTrySwap = false;
            int aTrySwapDirX = 0;int aTrySwapDirY = 0;
            float aDiffX = pX - mSwapDragStartX;float aDiffY = pY - mSwapDragStartY;
            float aAbsDiffX = aDiffX;if(aAbsDiffX < 0)aAbsDiffX = -aDiffX;
            float aAbsDiffY = aDiffY;if(aAbsDiffY < 0)aAbsDiffY = -aDiffY;
            if(aAbsDiffX > aAbsDiffY){
                if(aAbsDiffX >= aThreshold){
                    aTrySwap = true;
                    if(aDiffX < 0)aTrySwapDirX = -1;
                    else aTrySwapDirX = 1;
                }
            }
            else{
                if(aAbsDiffY >= aThreshold){
                    aTrySwap = true;
                    if(aDiffY < 0)aTrySwapDirY = -1;
                    else aTrySwapDirY = 1;
                }
            }
            
            if(aTrySwap == true){
                if(SwapTilesAllowed(mSwapTileGridX[0], mSwapTileGridY[0], mSwapTileGridX[0] + aTrySwapDirX, mSwapTileGridY[0] + aTrySwapDirY)){
                    //mSwapBlock = (SwapTilesAllowed(mSwapTileGridX[0], mSwapTileGridY[0], mSwapTileGridX[0] + aTrySwapDirX, mSwapTileGridY[0] + aTrySwapDirY) == false);
                    SwapTiles(mSwapTileGridX[0], mSwapTileGridY[0], mSwapTileGridX[0] + aTrySwapDirX, mSwapTileGridY[0] + aTrySwapDirY, false);
                }
            }
        }
    }
}

void Board::TouchUp(float pX, float pY, void *pData){
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    if((mSwapTile[0] != 0) && (mSwapTile[1] == 0)){
        if(ActionAllowed() && (pData == mSwapDragData)){
            if(Selectable(aGridX, aGridY)){
                TileEgg *aSwap = GetEgg(aGridX, aGridY);
                if((aSwap != 0) && (aSwap != mSwapTile[0])){
                    if(SwapTilesAllowed(mSwapTileGridX[0], mSwapTileGridY[0], aGridX, aGridY)){
                        //mSwapBlock = (SwapTilesAllowed(mSwapTileGridX[0], mSwapTileGridY[0], aGridX, aGridY) == false);
                        SwapTiles(mSwapTileGridX[0], mSwapTileGridY[0], aGridX, aGridY, false);
                    }
                    else{
                        SwapTilesCancel();
                    }
                }
            } else {
                SwapTilesCancel();
            }
        }
    }
}

void Board::TouchFlush(){
    
}

void Board::Notify(void *pSender){
    
}

void Board::SizeGrid(int pGridWidth, int pGridHeight){
    if(pGridWidth <= 0 || pGridHeight <= 0){
        FreeGrid();
    }
    else {
        Tile ***aPrev = mTile;
        
        int aWidthPrev = mGridWidth;
        int aHeightPrev = mGridHeight;
        
        mGridWidth = pGridWidth;
        mGridHeight = pGridHeight;
        
        mTile = new Tile**[mGridWidth];
        
        for(int aGridX=0;aGridX<mGridWidth;aGridX++){
            mTile[aGridX] = new Tile*[mGridHeight];
            for(int aGridY=0;aGridY<mGridHeight;aGridY++)mTile[aGridX][aGridY] = 0;
        }
        
        int aCopyWidth = aWidthPrev;
        if(mGridWidth < aCopyWidth)aCopyWidth = mGridWidth;
        
        int aCopyHeight = aHeightPrev;
        if(mGridHeight < aCopyHeight)aCopyHeight = mGridHeight;
        
        for(int aGridX=0;aGridX<aCopyWidth;aGridX++){
            for(int aGridY=0;aGridY<aCopyHeight;aGridY++)mTile[aGridX][aGridY] = aPrev[aGridX][aGridY];
        }
        
        for(int aGridX=0;aGridX<aWidthPrev;aGridX++){
            for(int aGridY=0;aGridY<aHeightPrev;aGridY++){
                if(((aGridX > aCopyWidth) || (aGridY > aCopyHeight)) && (aPrev[aGridX][aGridY] != 0)){
                    DeleteTile(aGridX, aGridY);
                }
            }
        }
        
        for(int i=0;i<aWidthPrev;i++)delete [] aPrev[i];
        delete [] aPrev;
        
        
        int *aPrevTop = mDirtTop;
        mDirtTop = new int[mGridWidth];
        
        for(int aGridX=aCopyWidth;aGridX<mGridWidth;aGridX++){
            mDirtTop[aGridX] = (aGridX >= (mGridWidth / 2)) ? ((aGridX % 3) + 6) : (((mGridWidth - aGridX) - 1) % 3) + 6;
        }
        
        
        for(int aGridX=0;aGridX<aCopyWidth;aGridX++){
            mDirtTop[aGridX] = aPrevTop[aGridX];
        }
        delete aPrevTop;
        
        delete [] mMultiPartBottom;
        mMultiPartBottom = new int[mGridWidth];
        
        mMatchCheckH.Resize(mGridWidth, mGridHeight);
        mMatchCheckV.Resize(mGridWidth, mGridHeight);
        
        mMatchType.Resize(mGridWidth, mGridHeight);
        
        mFalling.Resize(mGridWidth, mGridHeight);
        
        mFresh.Resize(mGridWidth, mGridHeight);
        
        mDestroyDirtAdjacent.Resize(mGridWidth, mGridHeight);
        mDestroyDirt.Resize(mGridWidth, mGridHeight);
        
        mGridScreenTop = 0;
        mGridScreenHeight = mGridHeight;
    }
}

void Board::FreeGrid(){
    
    SwapTilesCancel();
    
    if(mTile){
        for(int aGridX=0;aGridX<mGridWidth;aGridX++){
            for(int aGridY=0;aGridY<mGridHeight;aGridY++){
                DeleteTile(aGridX, aGridY);
            }
            delete [] mTile[aGridX];
        }
        delete [] mTile;
        mTile = 0;
        
        delete [] mDirtTop;
        mDirtTop = 0;
        
        delete [] mMultiPartBottom;
        mMultiPartBottom = 0;
    }
    
    mMatchCheckH.Free();
    mMatchCheckV.Free();
    
    mGridWidth = 0;
    mGridHeight = 0;
}


Tile *Board::RemoveTileFromGrid(int pGridX, int pGridY)
{
    Tile *aTile = 0;
    if(OnGrid(pGridX, pGridY)){
        aTile = GetTile(pGridX, pGridY);
        if(aTile){
            TileMulti *aMulti = 0;
            if(aTile->mMultiTilePart){
                aMulti = ((TileMultiPart *)aTile)->mMultiParent;
            } else if(aTile->mMultiTile){
                aMulti = ((TileMulti *)aTile);
            }
            
            if(aMulti){
                mTile[aMulti->mGridX][aMulti->mGridY] = 0;
                EnumList(TileMultiPart, aPart, aMulti->mPartList) {
                    mTile[aMulti->mGridX + aPart->mGridOffsetX][aMulti->mGridY + aPart->mGridOffsetY] = 0;
                }
                aTile = aMulti;
            } else {
                mTile[pGridX][pGridY] = 0;
            }
        }
    }
    return aTile;
}

void Board::DeleteTile(int pGridX, int pGridY){
    Tile *aTile = RemoveTileFromGrid(pGridX, pGridY);
    if(aTile){
        aTile->Kill();
        mKillList.Add(aTile);
    }
}

void Board::PlaceTileOnGrid(Tile *pTile, int pGridX, int pGridY){
    
    if(OnGrid(pGridX, pGridY)){
        DeleteTile(pGridX, pGridY);
        if(pTile->mMultiTile){
            TileMulti *aMulti = (TileMulti *)pTile;
            EnumList(TileMultiPart, aPart, aMulti->mPartList){
                DeleteTile(pGridX + aPart->mGridOffsetX,
                           pGridY + aPart->mGridOffsetY);
                
                mTile[pGridX + aPart->mGridOffsetX][pGridY + aPart->mGridOffsetY] = aPart;
            }
        }
        
        if(pTile){
            mTile[pGridX][pGridY] = pTile;
            pTile->SetUp(pGridX, pGridY);
        }
    }
}

bool Board::ActionAllowed()
{
    bool aReturn = true;
    
    //if(mSwap)aReturn = false;
    if(mActionTimer > 0)aReturn = false;
    
    return aReturn;
}

void Board::ActionRefresh()
{
    mActionTimer = 4;
}


int Board::GetTouchGridX(float pX){
    int aReturn = -1;
    pX += mOffsetX;
    if(pX > 0){
        pX /= gTileWidth;
        if(pX < mGridWidth)aReturn = pX;
    }
    return aReturn;
}

int Board::GetTouchGridY(float pY){
    int aReturn = -1;
    pY += mOffsetY;
    if(pY > 0){
        pY /= gTileHeight;
        if(pY < mGridHeight)aReturn = pY;
    }
    return aReturn;
}

float Board::GetTileCenterX(int pGridX){
    return (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
}

float Board::GetTileCenterY(int pGridY){
    return (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
}

Tile *Board::GetTile(int pGridX, int pGridY){
    Tile *aReturn = 0;
    if(OnGrid(pGridX, pGridY)){
        aReturn = mTile[pGridX][pGridY];
        if(aReturn){
            if(aReturn->mMultiTilePart){
                aReturn = ((TileMultiPart *)aReturn)->mMultiParent;
            }
        }
    }
    return aReturn;
}

Tile *Board::GetTile(int pGridX, int pGridY, int pTileType){
    Tile *aReturn = GetTile(pGridX, pGridY);
    if(aReturn != 0){
        if(aReturn->mType != pTileType)aReturn = 0;
    }
    return aReturn;
}

bool Board::SwapTiles(int pGridX1, int pGridY1, int pGridX2, int pGridY2, bool pReverse)
{
    bool aSuccess = false;
    
    TileEgg *aSwap1 = GetEgg(pGridX1, pGridY1);
    TileEgg *aSwap2 = GetEgg(pGridX2, pGridY2);
    
    mSwapTile[0] = aSwap1;
    mSwapTileGridX[0] = pGridX1;mSwapTileGridY[0] = pGridY1;
    
    mSwapTile[1] = aSwap2;
    mSwapTileGridX[1] = pGridX2;mSwapTileGridY[1] = pGridY2;
    
    //if((aSwap1 != 0) && (aSwap2 != 0) && (aSwap1 != aSwap2) && (SwapTilesAttemptAllowed(pGridX1, pGridY1, pGridX2, pGridY2) == true))
    if((aSwap1 != 0) && (aSwap2 != 0) && (aSwap1 != aSwap2) && (SwapTilesAllowed(pGridX1, pGridY1, pGridX2, pGridY2) == true))
    {
        ActionRefresh();
        mSwap = true;
        mSwapReverse = pReverse;
        mSwapTimer = SWAP_TIME;
        aSuccess = true;
    }
    
    return aSuccess;
}

bool Board::SwapTilesAllowed(int pGridX1, int pGridY1, int pGridX2, int pGridY2)
{
    bool aSuccess = false;
    
    TileEgg *aSwap1 = GetEgg(pGridX1, pGridY1);
    TileEgg *aSwap2 = GetEgg(pGridX2, pGridY2);
    
    //Naughty pyramids of non-beautiful Swift-ness.
    //Somebody should be extremely ashamed.
    if((aSwap1 != 0) && (aSwap2 != 0) && (aSwap1 != aSwap2)){
        //if(aSwap1->mMatchType != aSwap2->mMatchType){
        if(Selectable(pGridX1, pGridY1) && Selectable(pGridX2, pGridY2)){
            int aDiffX = pGridX1 - pGridX2;
            int aDiffY = pGridY1 - pGridY2;
            if(((aDiffX == 1) || (aDiffX == -1)) && (aDiffY == 0))aSuccess = true;
            if(((aDiffY == 1) || (aDiffY == -1)) && (aDiffX == 0))aSuccess = true;
        }
        //}
    }
    
    return aSuccess;
}

/*
 bool Board::SwapTilesAttemptAllowed(int pGridX1, int pGridY1, int pGridX2, int pGridY2)
 {
 bool aSuccess = false;
 
 TileEgg *aSwap1 = GetEgg(pGridX1, pGridY1);
 TileEgg *aSwap2 = GetEgg(pGridX2, pGridY2);
 
 if((aSwap1 != 0) && (aSwap2 != 0) && (aSwap1 != aSwap2)){
 if(Selectable(pGridX1, pGridY1) && Selectable(pGridX2, pGridY2)){
 int aDiffX = pGridX1 - pGridX2;
 int aDiffY = pGridY1 - pGridY2;
 if(((aDiffX == 1) || (aDiffX == -1)) && (aDiffY == 0))aSuccess = true;
 if(((aDiffY == 1) || (aDiffY == -1)) && (aDiffX == 0))aSuccess = true;
 }
 }
 
 return aSuccess;
 }
 
 bool Board::SwapTilesAllowed(int pGridX1, int pGridY1, int pGridX2, int pGridY2)
 {
 bool aSuccess = false;
 
 TileEgg *aSwap1 = GetEgg(pGridX1, pGridY1);
 TileEgg *aSwap2 = GetEgg(pGridX2, pGridY2);
 
 if((aSwap1 != 0) && (aSwap2 != 0) && (aSwap1 != aSwap2)){
 if(aSwap1->mMatchType != aSwap2->mMatchType){
 int aDiffX = pGridX1 - pGridX2;
 int aDiffY = pGridY1 - pGridY2;
 if(((aDiffX == 1) || (aDiffX == -1)) && (aDiffY == 0))aSuccess = true;
 if(((aDiffY == 1) || (aDiffY == -1)) && (aDiffX == 0))aSuccess = true;
 }
 }
 
 return aSuccess;
 }
 */

void Board::SwapTilesCancel()
{
    TileEgg *aSwap1 = 0;TileEgg *aSwap2 = 0;
    
    if(mSwapTile[0])aSwap1 = GetEgg(mSwapTileGridX[0], mSwapTileGridY[0]);
    if(mSwapTile[1])aSwap2 = GetEgg(mSwapTileGridX[1], mSwapTileGridY[1]);
    
    if(aSwap1)aSwap1->Deselect();
    if(aSwap2)aSwap1->Deselect();
    
    mSwapDragStartX = 0.0f;mSwapDragStartY = 0.0f;
    mSwapDragData = 0;
    
    mSwapTile[0] = 0;
    mSwapTileGridX[0] = -1;mSwapTileGridY[0] = -1;
    
    mSwapTile[1] = 0;
    mSwapTileGridX[1] = -1;mSwapTileGridY[1] = -1;
    
    mSwap = false;
    mSwapReverse = false;
    mSwapTimer = 0;
}

bool Board::Selectable(int pGridX, int pGridY)
{
    if(OnGrid(pGridX, pGridY)){
        if(pGridY < mDirtTop[pGridX])return true;
    }
    return false;
}

void Board::DestroyDirtReset(){
    mDestroyDirt.Flood(0);
    mDestroyDirtAdjacent.Flood(0);
}

void Board::DestroyDirt(int pGridX, int pGridY)
{
    if(OnGrid(pGridX, pGridY)){
        if(pGridY >= mDirtTop[pGridX]){
            mDestroyDirt.Set(pGridX, pGridY, 1);
        }
    }
}

//This will also need to factor in multi-tile pieces.
void Board::DestroyDirtAdjustUndershoot(){
    
    bool aRepeat = true;
    
    while(aRepeat) {
        aRepeat = false;
        
        
        
        for(int aGridX=0;aGridX<mGridWidth;aGridX++){
            
        }
    }
    
    
    
    
}

void Board::MatchesBegin(bool pFromSwap)
{
    mMatching = true;
    mMatchingTimer = MATCH_TIME;
    
    EnumList(BoardMatch, aMatch, mMatchList){
        for(int i=0;i<aMatch->mCount;i++){
            int aMatchX = aMatch->mX[i], aMatchY = aMatch->mY[i];
            TileEgg *aEgg = GetEgg(aMatchX, aMatchY);
            aEgg->Matched();
        }
    }
}

void Board::MatchesComplete()
{
    //mDirtDestroy.Flood(0);
    
    DestroyDirtReset();
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=0;aGridY<mDirtTop[aGridX];aGridY++){
            
            TileEgg *aEgg = GetEgg(aGridX, aGridY);
            if(aEgg){
                if(aEgg->mMatched){
                    DestroyDirt(aGridX-1, aGridY  );
                    DestroyDirt(aGridX+1, aGridY  );
                    DestroyDirt(aGridX  , aGridY+1);
                }
            }
        }
    }
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=0;aGridY<mDirtTop[aGridX];aGridY++){
            
            TileEgg *aEgg = GetEgg(aGridX, aGridY);
            
            if(aEgg){
                if(aEgg->mMatched){
                    DeleteTile(aGridX, aGridY);
                }
            }
        }
    }
    
    mMatching = false;
    mMatchingTimer = 0;
}

void Board::MatchesReset(){
    mMatchCheckH.Flood(0);mMatchCheckV.Flood(0);
    mMatchType.Flood(0);
    
    mMatchQueue.Add(mMatchList);
    mMatchList.RemoveAll();
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=0;aGridY<mDirtTop[aGridX];aGridY++){
            //if(aGridY < ()){
            
            TileEgg *aEgg = GetEgg(aGridX, aGridY);
            if(aEgg)mMatchType.Set(aGridX, aGridY, aEgg->mMatchType + 1);
            //}
        }
    }
    //mMatchType
    
}

bool Board::MatchesFind(int pGridX, int pGridY){
    bool aMatchFound = false;
    
    int aType = mMatchType.Get(pGridX, pGridY);
    
    if(aType > 0){
        int aCheckType = -1;
        if(!mMatchCheckH.Get(pGridX, pGridY)){
            mMatchCheckH.Set(pGridX, pGridY, 1);
            int aLeft = pGridX, aRight = pGridX;
            for(int aCheckX=pGridX-1;aCheckX>=0;aCheckX--){
                aCheckType = mMatchType.Get(aCheckX, pGridY);
                if(aCheckType == aType){
                    aLeft = aCheckX;
                    mMatchCheckH.Set(aCheckX, pGridY, 1);
                }
                else break;
            }
            
            for(int aCheckX=pGridX+1;aCheckX<mGridWidth;aCheckX++){
                aCheckType = mMatchType.Get(aCheckX, pGridY);
                if(aCheckType == aType){
                    aRight = aCheckX;
                    mMatchCheckH.Set(aCheckX, pGridY, 1);
                }
                else break;
            }
            int aCount = (aRight - aLeft) + 1;
            if(aCount >= 3){
                BoardMatch *aMatch = DequeueMatch();
                aMatch->mHorizontal = true;
                mMatchList.Add(aMatch);
                for(int aGridX=aLeft;aGridX<=aRight;aGridX++){
                    aMatch->Add(aGridX, pGridY);
                }
            }
        }
        
        if(!mMatchCheckV.Get(pGridX, pGridY)){
            
            mMatchCheckV.Set(pGridX, pGridY, 1);
            int aTop = pGridY, aBottom = pGridY;
            for(int aCheckY=pGridY-1;aCheckY>=0;aCheckY--){
                aCheckType = mMatchType.Get(pGridX, aCheckY);
                if(aCheckType == aType){
                    aTop = aCheckY;
                    mMatchCheckV.Set(pGridX, aCheckY, 1);
                }
                else break;
            }
            
            for(int aCheckY=pGridY+1;aCheckY<mGridHeight;aCheckY++){
                aCheckType = mMatchType.Get(pGridX, aCheckY);
                if(aCheckType == aType){
                    aBottom = aCheckY;
                    mMatchCheckV.Set(pGridX, aCheckY, 1);
                }
                else break;
            }
            
            int aCount = (aBottom - aTop) + 1;
            if(aCount >= 3){
                BoardMatch *aMatch = DequeueMatch();
                aMatch->mVertical = true;
                mMatchList.Add(aMatch);
                for(int aGridY=aTop;aGridY<=aBottom;aGridY++){
                    aMatch->Add(pGridX, aGridY);
                }
            }
        }
    }
    return aMatchFound;
}

BoardMatch *Board::DequeueMatch()
{
    BoardMatch *aMatch = (BoardMatch *)(mMatchQueue.Pop());
    if(aMatch){
        aMatch->Reset();
    } else {
        aMatch = new BoardMatch();
    }
    return aMatch;
}

int Board::FindMoves(){
    
    int aCount = 0;
    
    MatchesReset();
    
    for(int aGridX=0;aGridX<(mGridWidth);aGridX++){
        for(int aGridY=0;aGridY<mGridHeight;aGridY++){
            TileEgg *aFlag = GetEgg(aGridX, aGridY);
            if(aFlag){
                aFlag->FlagReset();
            }
        }
    }
    
    for(int aGridX=0;aGridX<(mGridWidth);aGridX++){
        for(int aGridY=0;aGridY<mDirtTop[aGridX];aGridY++){
            
            if(mMatchType.SwapAllowed(aGridX, aGridY, aGridX + 1, aGridY)){
                mMatchType.Swap(aGridX, aGridY, aGridX + 1, aGridY);
                
                if(mMatchType.MatchExists(aGridX, aGridY)){
                    aCount++;
                    
                    TileEgg *aEgg = GetEgg(aGridX, aGridY);
                    aEgg->mFlagR = true;
                    
                    
                }
                
                if(mMatchType.MatchExists(aGridX + 1, aGridY)){
                    aCount++;
                    
                    TileEgg *aEgg = GetEgg(aGridX + 1, aGridY);
                    aEgg->mFlagL = true;
                }
                
                mMatchType.Swap(aGridX + 1, aGridY, aGridX, aGridY);
            }
            
            if(mMatchType.SwapAllowed(aGridX, aGridY, aGridX, aGridY + 1)){
                mMatchType.Swap(aGridX, aGridY, aGridX, aGridY + 1);
                if(mMatchType.MatchExists(aGridX, aGridY)){
                    aCount++;
                    
                    TileEgg *aEgg = GetEgg(aGridX, aGridY);
                    aEgg->mFlagD = true;
                    
                }
                if(mMatchType.MatchExists(aGridX, aGridY + 1)){
                    aCount++;
                    
                    TileEgg *aEgg = GetEgg(aGridX, aGridY + 1);
                    aEgg->mFlagU = true;
                }
                mMatchType.Swap(aGridX, aGridY + 1, aGridX, aGridY);
            }
        }
    }
    
    return aCount;
}


bool Board::Topple(){
    
    bool aReturn = false;
    
    mFalling.Flood(0);
    mFresh.Flood(0);
    
    bool aReloop = true;
    
    while (aReloop) {
        aReloop = false;
        
        Tile *aTile = 0;
        
        for(int aGridX=mGridWidth-1;aGridX>=0;aGridX--){
            for(int aGridY=mDirtTop[aGridX]-1;aGridY>=0;aGridY--){
                
                aTile = mTile[aGridX][aGridY];
                
                if(aTile){
                    if(aTile->mMultiTilePart){
                        //Ignore MT parts..
                    } else if(aTile->mMultiTile){
                        
                        /*
                        TileMulti *aMulti = (TileMulti *)aTile;
                        
                        for(int i=0;i<mGridWidth;i++){
                            mMultiPartBottom[i] = -1;
                        }
                        
                        mMultiPartBottom[aGridX] = aGridY;
                        
                        EnumList(TileMultiPart, aPart, aMulti->mPartList) {
                            
                            if(aPart->mGridY > mMultiPartBottom[aPart->mGridX]){
                                mMultiPartBottom[aPart->mGridX] = aPart->mGridY;
                            }
                        }
                        
                        bool aFall = true;
                        
                        for(int i=0;i<mGridWidth;i++){
                            
                            if(mMultiPartBottom[i] != -1){
                                
                                if((mMultiPartBottom[i] < (mDirtTop[i] - 1)) && (mMultiPartBottom[i] < (mGridHeight - 1))){
                                    
                                    if(mTile[aGridX][mMultiPartBottom[i] + 1]){
                                        aFall = false;
                                    }
                                }
                            }
                        }
                        
                        if(aFall){
                            
                        }
                        */
                        
                        
                    } else {
                        
                        if((aGridY < (mDirtTop[aGridX] - 1)) && (aGridY < (mGridHeight - 1))){
                            
                            if(mTile[aGridX][aGridY + 1] == 0){
                                
                                aTile->FallTo(aGridY + 1);
                                mTile[aGridX][aGridY + 1] = aTile;
                                mTile[aGridX][aGridY] = 0;
                                
                                aReloop = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    
    /*
    int aStartY = (mGridScreenTop - 4);
    if(aStartY < 0)aStartY = 0;
    if(aStartY > (mGridHeight - 1))aStartY = (mGridHeight - 1);
    
    int aBottom = 0;
    
    for(int i=0;i<mGridWidth;i++){
        Tile *aTile = 0;
        aBottom = mGridScreenTop + mGridScreenHeight + 6;
        if(aBottom >= mDirtTop[i])aBottom = (mDirtTop[i] - 1);
        if(aBottom >= mGridHeight)aBottom = (mGridHeight - 1);
        
        int aShiftAmount = 0;
        
        for(int n=aBottom;n>=aStartY;n--){
            aTile = mTile[i][n];
            if(aTile){
                if(aShiftAmount > 0){
                    mTile[i][n] = 0;
                    mTile[i][n + aShiftAmount] = aTile;
                    aTile->FallTo(n + aShiftAmount);
                }
            }
            else{
                aShiftAmount++;
            }
            
            if(aShiftAmount > 0){
                mFalling.Set(i, n, 1);
                aReturn = true;
            }
        }
    }
    */
    
    if(FillHoles()){
        aReturn = true;
    }
    
    if(aReturn){
        mToppling = true;
        mCascadeCheck = true;
        ActionRefresh();
    }
    
    return aReturn;
}

bool Board::FillHoles()
{
    bool aReturn = false;
    
    TileEgg *aEgg = 0;
    
    for(int i=0;i<mGridWidth;i++){
        int aShiftAmount = 0;
        
        int aStartY = (mGridScreenTop);
        if(aStartY >= mGridHeight)aStartY = (mGridHeight - 1);
        
        int aBottom = mGridScreenTop + mGridScreenHeight + 6;
        if(aBottom >= mDirtTop[i])aBottom = (mDirtTop[i] - 1);
        if(aBottom >= mGridHeight)aBottom = (mGridHeight - 1);
        
        aShiftAmount = 0;
        
        int aFillCount = 0;
        
        for(int n=aStartY;n<=aBottom;n++){
            if(mTile[i][n] == 0)aFillCount++;
            else break;
        }
        
        int aSpawnStart = (mGridScreenTop - 1);
        int aSpawnTarget = (aStartY + (aFillCount - 1));
        
        if(aFillCount > 0){
            aReturn = true;
            while(aFillCount > 0){
                aEgg = new TileEgg();
                aEgg->mMatchType = gRand.Get(mMatchTypeCount);
                mFresh.Set(i, aSpawnTarget, 1);
                PlaceTileOnGrid(aEgg, i, aSpawnTarget);
                aEgg->mY = GetTileCenterY(aSpawnStart) - 140.0f;
                aEgg->FallTo(aSpawnTarget);
                aSpawnTarget--;
                aSpawnStart--;
                aFillCount--;
            }
        }
    }
    return aReturn;
}

bool Board::CascadeAllowed()
{
    if(mCascadeComboCount > 1)return false;
    return true;
}

bool Board::Cascade(){
    bool aResult = false;
    
    MatchesReset();
    
    
    for(int aGridX=0;aGridX<mGridWidth;aGridX++){
        for(int aGridY=0;aGridY<mGridHeight;aGridY++){
            if(mFalling.Get(aGridX, aGridY)){
                MatchesFind(aGridX, aGridY);
            }
        }
    }
    
    if(mMatchList.mCount > 0){
        
        mCascadeComboCount++;
        
        
        MatchesBegin(false);
    }
    
    
    /*
     MatchesReset();
     
     MatchesFind(mSwapTileGridX[0], mSwapTileGridY[0]);
     MatchesFind(mSwapTileGridX[1], mSwapTileGridY[1]);
     
     if(mMatchList.mCount > 0){
     
     mMatching = true;
     mMatchingTimer = 60;
     
     EnumList(BoardMatch, aMatch, mMatchList){
     for(int i=0;i<aMatch->mCount;i++){
     int aMatchX = aMatch->mX[i], aMatchY = aMatch->mY[i];
     TileEgg *aEgg = GetEgg(aMatchX, aMatchY);
     aEgg->Matched();
     }
     }
     }
     else{
     SwapTiles(mSwapTileGridX[0], mSwapTileGridY[0], mSwapTileGridX[1], mSwapTileGridY[1], true);
     }
     */
    
    
    return aResult;
}





