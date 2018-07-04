//
//  EditorBoard.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "EditorBoard.h"
#include "MainApp.h"
#include "GameTileStar.h"

EditorBoard *gEditor;

EditorBoard::EditorBoard()
{
    gEditor = this;
    
    mMode = ED_M_PAN;
    
    mModeTile = ED_T_M_NORMAL;
    
    mAccessoryType = ACC_NONE;
    
    mRecievesOutsideTouches = true;
    
    mTileType = -1;
    
    mLastSetTileX = -1;
    mLastSetTileY = -1;
    
    mDragScale = 1.0f;
    mDragStartOffset = 0.0f;
    mDragStartMouseY = 0.0f;
    mDragging = false;
    mSideDragging = false;
    
    mGridScreenTop = 0;
    mGridScreenHeight = 10;
    
    mEditorStarDepthIndex = 0;
    
    
    //mCurrentFile;
    //mSavedFileList;
    
    
    //virtual void                        Save(const char *pPath);
    //virtual void                        Load(const char *pPath);
    
    //FString                             mCurrentFile;
    //FList                               mSavedFileList;
    
    FFile aFile;
    aFile.Load("editor_files.dat");
    
    int aCount = aFile.ReadInt();
    
    FString aLastFile = aFile.ReadString();
    
    for(int i=0;i<aCount;i++)
    {
        FString aReadFile = aFile.ReadString();
        mSavedFileList += new FString(aReadFile.c());
    }
    
    if(aLastFile.mLength > 0)
    {
        Load(aLastFile.c());
    }
    
    
    
    mRecievesConsumedTouches = false;
}

EditorBoard::~EditorBoard()
{
    
}

void EditorBoard::Update()
{
    
    mGridScreenTop = 0;
    mGridScreenHeight = mGridHeight;
    
    //mGrid.Update();
}

void EditorBoard::Draw()
{
    Graphics::SetColor();
    
    FMatrix aHold = Graphics::GetMatrixModelView();
    FMatrix aMatrix = aHold;
    aMatrix.Translate(0.0f, -mOffsetY);
    Graphics::SetMatrixModelView(aMatrix);
    
    
    //DrawDirt();
    
    int aStartY = GetTouchGridY(-100);
    if(aStartY < 0)aStartY = 0;
    
    int aEndY = aStartY + 16;
    if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    mUtils.DrawDirt(mDirtTop, mGridWidth, aStartY, aEndY);
    
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=aStartY;n<aEndY;n++)
        {
            GameTile *aTile = mTile[i][n];
            
            if(aTile)
            {
                if(aTile->mTileType != GAME_TILE_TYPE_DIRT)
                {
                    aTile->DrawBottom();
                    aTile->Draw();
                }
            }
        }
    }
    
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=aStartY;n<aEndY;n++)
        {
            GameTile *aTile = mTile[i][n];
            
            if(aTile)
            {
                if(aTile->mTileType != GAME_TILE_TYPE_DIRT)aTile->DrawTop();
            }
        }
    }
    
    //DrawDepth();
    
    
    Graphics::SetMatrixModelView(aHold);
}

void EditorBoard::DrawOver()
{
    FMatrix aHold = Graphics::GetMatrixModelView();
    FMatrix aMatrix = aHold;
    aMatrix.Translate(0.0f, -mOffsetY);
    Graphics::SetMatrixModelView(aMatrix);
    
    Graphics::SetMatrixModelView(aHold);
}

//mBaseStarDepth[0] = 6;
//mBaseStarDepth[1] = 20;
//mBaseStarDepth[2] = 32;



void EditorBoard::TouchDown(float pX, float pY, void *pData)
{
    mLastSetTileX = -1;
    mLastSetTileY = -1;
    
    mDragStartOffset = mOffsetY;
    mDragStartMouseY = pY;
    mDragScale = 1.0f;
    mDragging = true;
    
    if(pX >= (mTileWidth * ((float)(mGridWidth))))
    {
        mDragScale = 4.0f;
    }
    
    
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    if(aGridX == -1)mSideDragging = true;
    
    if(mMode == ED_M_TILES)PlaceTile(aGridX, aGridY);
    
    if(mMode == ED_M_DEPTH)
    {
        if(pX < gAppWidth2)
        {
            if(aGridY >= 0)
            {
                if((mEditorStarDepthIndex >= 0) && (mEditorStarDepthIndex < 3))
                {
                    
                }
            }
        }
    }
}

void EditorBoard::TouchMove(float pX, float pY, void *pData)
{
    if((mMode == ED_M_PAN) || (mSideDragging == true))
    {
        if(mDragging)
        {
            
            if(mSideDragging)
            {
                
            }
            
            mOffsetY = (mDragStartOffset + (mDragStartMouseY - pY) * mDragScale);
        }
    }
    
    int aGridX = GetTouchGridX(pX);
    int aGridY = GetTouchGridY(pY);
    
    if(mMode == ED_M_TILES)
    {
        if(mSideDragging == false)
        {
            if(mDragging)
            {
                PlaceTile(aGridX, aGridY);
            }
        }
    }
    
    if(mMode == ED_M_DEPTH)
    {
        if(pX < gAppWidth2)
        {
            if(aGridY >= 0)
            {
                if((mEditorStarDepthIndex >= 0) && (mEditorStarDepthIndex < 3))
                {
                    //mBaseStarDepth[mEditorStarDepthIndex] = aGridY;
                    
                }
            }
        }
    }
}

void EditorBoard::TouchUp(float pX, float pY, void *pData)
{
    mLastSetTileX = -1;
    mLastSetTileY = -1;
    mDragging = false;
    mSideDragging = false;
}

void EditorBoard::EditorClear()
{
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            EditorDeleteTile(i, n);
        }
    }
}

void EditorBoard::EditorClearToDirt()
{
    EditorClear();
    EditorFillWithDirt();
}

void EditorBoard::EditorFillWithDirt()
{
    for(int i=0;i<mGridWidth;i++)
    {
        for(int n=0;n<mGridHeight;n++)
        {
            if(mTile[i][n] == 0)
            {
                
                //GameTileOldDirt *aDirt = new GameTileOldDirt();
                //mGrid.mTile[i][n] = aDirt;
                //mGrid.mTile[i][n]->SetUp(i, n);
            }
        }
    }
    
    for(int i=0;i<9;i++)
    {
        mDirtTop[i] = 0;
    }
    
}

void EditorBoard::GenerateLevel(int pInitialDepth, int pSpacing)
{
    if(pInitialDepth <= 2)pInitialDepth = 2;
    if(pSpacing <= 2)pSpacing = 2;
    
    int aBottomPadding = 8;
    
    EditorClear();
    
    int aNewHeight = (pInitialDepth) + (pSpacing + 1) + (pSpacing + 1) + aBottomPadding;
    
    ResizeGrid(mGridWidth, aNewHeight);
    
    EditorClearToDirt();
    
    int aStarDepth = pInitialDepth;
    for(int i=0;i<3;i++)
    {
        int aStarX = gRand.Get((mGridWidth - 3)) + 1;
        
        GameTileStar *aStar = new GameTileStar();
        
        aStar->mStarIndex = i;
        
        //GameTileOldRelicLevelEgg *aEgg = new GameTileOldRelicLevelEgg();
        
        //if(i == 0)aEgg->SetEggIndex(LEVEL_STAR_1_RELIC_INDEX);
        //else if(i == 1)aEgg->SetEggIndex(LEVEL_STAR_2_RELIC_INDEX);
        //else aEgg->SetEggIndex(LEVEL_STAR_3_RELIC_INDEX);
        
        SetTile(aStarX, aStarDepth, aStar);
        
        aStarDepth += pSpacing;
        
        
    }
    
}

void EditorBoard::PlaceTile(int pGridX, int pGridY)
{
    if(mLastSetTileX == pGridX && mLastSetTileY == pGridY)
    {
        
    }
    else
    {
        mLastSetTileX = pGridX;
        mLastSetTileY = pGridY;
        
        if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGridWidth) && (pGridY < mGridHeight))
        {
            
            if(mModeTile == ED_T_M_ERASER)
            {
                DeleteTile(pGridX, pGridY);
            }
            
            if(mModeTile == ED_T_M_NORMAL)
            {
                GameTileMatchable *aTile = new GameTileMatchable();
                
                //GameTileOldBubble *aTile = new GameTileOldBubble();
                if(mTileType < 0)aTile->mMatchType = gRand.Get(3);
                else aTile->mMatchType = mTileType;
                
                if(SetTile(pGridX, pGridY, aTile) == false)
                {
                    
                    printf("Can't Place Editor Tile! [%d, %d]\n", pGridX, pGridY);
                    
                    delete aTile;
                    aTile = 0;
                }
            }
            
            if(mModeTile == ED_T_M_ACCESSORY)
            {
                GameTileMatchable *aMatchTile = GetTileMatchable(pGridX, pGridY);
                
                if(aMatchTile == 0)
                {
                    GameTileMatchable *aTile = new GameTileMatchable();
                    if(mTileType < 0)aTile->mMatchType = gRand.Get(3);
                    else aTile->mMatchType = mTileType;
                    
                    if(SetTile(pGridX, pGridY, aTile) == false)
                    {
                        printf("Can't Place Editor Tile! [%d, %d]\n", pGridX, pGridY);
                        delete aTile;
                        aTile = 0;
                    }
                }
                
                aMatchTile = GetTileMatchable(pGridX, pGridY);
                
                
                if(aMatchTile)
                {
                    //Accessory...??
                    //aBubble->mAccessoryType = mAccessoryType;
                }
            }
            
            if(mModeTile == ED_T_M_COLORED_ROCK)
            {
                //GameTileOldColorRock *aTile = new GameTileOldColorRock();
                //SetTile(pGridX, pGridY, aTile);
            }
            
            
            if(mModeTile == ED_T_M_METAL)
            {
                GameTileMetal *aTile = new GameTileMetal();
                
                if(SetTile(pGridX, pGridY, aTile) == false)
                {
                    printf("Can't Place Editor Tile! [%d, %d]\n", pGridX, pGridY);
                    
                    delete aTile;
                    aTile = 0;
                }
            }
            
            if(mModeTile == ED_T_M_ENERGY)
            {
                //GameTileOldEnergy *aTile = new GameTileOldEnergy();
                //SetTile(pGridX, pGridY, aTile);
            }
            
            if(mModeTile == ED_T_M_POWERUP)
            {
                GameTilePowerUp *aTile = new GameTilePowerUp();
                aTile->mSpecialIndex = mTileType;
                
                if(SetTile(pGridX, pGridY, aTile) == false)
                {
                    printf("Can't Place Editor Tile! [%d, %d]\n", pGridX, pGridY);
                    delete aTile;
                    aTile = 0;
                }
                
                
                
                //GameTileOldPowerup *aTile = new GameTileOldPowerup();
                //aTile->mPowerupIndex = mTileType;
                //SetTile(pGridX, pGridY, aTile);
            }
            
            if(mModeTile == ED_T_M_TREASURE)
            {
                GameTileTreasure *aTile = new GameTileTreasure();
                if(SetTile(pGridX, pGridY, aTile) == false)
                {
                    printf("Can't Place Editor Tile! [%d, %d]\n", pGridX, pGridY);
                    
                    delete aTile;
                    aTile = 0;
                }
            }
            
            if(mModeTile == ED_T_M_DIRT)
            {
                mDirtTop[pGridX] = pGridY;
                
                //GameTileOldDirt *aTile = new GameTileOldDirt();
                //SetTile(pGridX, pGridY, aTile);
            }
            
            if(mModeTile == ED_T_M_ROCK)
            {
                GameTileRock *aTile = new GameTileRock();
                SetTile(pGridX, pGridY, aTile);
                
                //GameTileOldRock *aTile = new GameTileOldRock();
                //SetTile(pGridX, pGridY, aTile);
            }
            
            if(mModeTile == ED_T_M_HARD_ROCK)
            {
                //GameTileOldHardRock *aTile = new GameTileOldHardRock();
                //SetTile(pGridX, pGridY, aTile);
            }
            
            if(mModeTile == ED_T_M_RELIC)
            {
                
                //BoardGenericMultiTile *aTile = 0;
                
                //if(mTileType == 0)aTile = new GameTileOldRelicSword();
                //if(mTileType == 1)aTile = new GameTileOldRelicAxe();
                
                if(mTileType == LEVEL_STAR_1_RELIC_INDEX || mTileType == LEVEL_STAR_2_RELIC_INDEX || mTileType == LEVEL_STAR_3_RELIC_INDEX)
                {
                    
                    GameTileStar *aStar = new GameTileStar();
                    
                    //aTile = aStar;
                    //aStar->mTileType = mTileType;
                    
                    //aEgg->SetEggIndex(mTileType);
                    
                    if(SetTile(pGridX, pGridY, aStar) == false)
                    {
                        printf("Can't Place Editor Star! [%d, %d]\n", pGridX, pGridY);
                        delete aStar;
                        aStar = 0;
                    }
                    
                    //SetTile(pGridX, pGridY, aStar);
                    
                }
                
                
                //SetTile(pGridX, pGridY, aTile);
                
                
            }
            
        }
    }
}

void EditorBoard::EditorDeleteTile(int pGridX, int pGridY)
{
    DeleteTile(pGridX, pGridY);
    
    /*
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGrid.mWidth) && (pGridY < mGrid.mHeight))
    {
        GameTileOld *aTile = mGrid.mTile[pGridX][pGridY];
        
        if(aTile)
        {
            if((aTile->mTileType == GAME_TILE_TYPE_RELIC) || (aTile->mTileType == GAME_TILE_TYPE_RELIC_PIECE))
            {
                GameTileOldRelic *aRelic = 0;
                
                if(aTile->mTileType == GAME_TILE_TYPE_RELIC)
                {
                    aRelic = (GameTileOldRelic *)aTile;
                }
                else
                {
                    aRelic = ((GameTileOldRelicPiece *)aTile)->mRelic;
                }
                
                if(aRelic)
                {
                    EnumList(GameTileOldRelicPiece, aPiece, aRelic->mRelicPieceList)
                    {
                        int aGridX = aRelic->mGridX + aPiece->mRelicGridX;
                        int aGridY = aRelic->mGridY + aPiece->mRelicGridY;
                        
                        if((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGrid.mWidth) && (aGridY < mGrid.mHeight))
                        {
                            mGrid.mTile[aGridX][aGridY] = 0;
                        }
                    }
                    
                    mGrid.mTile[aRelic->mGridX][aRelic->mGridY] = 0;
                    mEditorDeletedTileList += aRelic;
                }
            }
            else
            {
                mGrid.mTile[pGridX][pGridY] = 0;
                mEditorDeletedTileList += aTile;
            }
        }
    }
    ComputeReachability();
     
    */
}

/*
void EditorBoard::SetTile(int pGridX, int pGridY, GameTile *pTile)
{
    if(pTile == 0)return;
    
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mGrid.mWidth) && (pGridY < mGrid.mHeight))
    {
        
        if(pTile->mTileType == GAME_TILE_TYPE_RELIC)
        {
            GameTileOldRelic *aRelic = (GameTileOldRelic *)pTile;
            
            aRelic->mGridX = pGridX;
            aRelic->mGridY = pGridY;
            
            EnumList(GameTileOldRelicPiece, aPiece, aRelic->mRelicPieceList)
            {
                int aGridX = pGridX + aPiece->mRelicGridX;
                int aGridY = pGridY + aPiece->mRelicGridY;
                
                if((aGridX >= 0) && (aGridY >= 0) && (aGridX < mGrid.mWidth) && (aGridY < mGrid.mHeight))
                {
                    
                }
                else
                {
                    return;
                }
                
            }
            
            EnumList(GameTileOldRelicPiece, aPiece, aRelic->mRelicPieceList)
            {
                int aGridX = pGridX + aPiece->mRelicGridX;
                int aGridY = pGridY + aPiece->mRelicGridY;
                EditorDeleteTile(aGridX, aGridY);
            }
            
            EditorDeleteTile(pGridX, pGridY);
            
            mGrid.mTile[pGridX][pGridY] = pTile;
            if(pTile)pTile->SetUp(pGridX, pGridY);
            
            EnumList(GameTileOldRelicPiece, aPiece, aRelic->mRelicPieceList)
            {
                int aGridX = pGridX + aPiece->mRelicGridX;
                int aGridY = pGridY + aPiece->mRelicGridY;
                mGrid.mTile[aGridX][aGridY] = aPiece;
                aPiece->SetUp(aGridX, aGridY);
            }
        }
        else
        {
            EditorDeleteTile(pGridX, pGridY);
            
            mGrid.mTile[pGridX][pGridY] = pTile;
            if(pTile)
            {
                pTile->SetUp(pGridX, pGridY);
            }
        }
    }
    
    ComputeReachability();
}
*/


void EditorBoard::Save(const char *pPath)
{
    mCurrentFile = pPath;
    
    Board::Save(pPath);
    
    FString aName = pPath;
    
    bool aExists = false;
    
    EnumList(FString, aFileName, mSavedFileList)
    {
        
        if(aName == aFileName->c())
        {
            aExists = true;
        }
    }
    
    if(aExists == false)
    {
        mSavedFileList += new FString(pPath);
    }
    
    
    FFile aFile;
    
    aFile.WriteInt(mSavedFileList.mCount);
    aFile.WriteString(mCurrentFile.c());

    EnumList(FString, aFileName, mSavedFileList)
    {
        aFile.WriteString(aFileName->c());
    }
    
    aFile.Save(gDirDocuments + "editor_files.dat");
    
}

void EditorBoard::Load(const char *pPath)
{
    mCurrentFile = pPath;
    
    Board::Load(pPath);
    
    Save(pPath);
}





