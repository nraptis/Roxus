//
//  BoardUtilities.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//



#include "BoardUtilities.h"
#include "Board.h"
#include "core_includes.h"
#include "FXML.h"

#ifdef EDITOR_MODE
#include "EditorBoard.h"
#endif

BoardUtilities::BoardUtilities()
{
    mBoard = 0;
}

BoardUtilities::~BoardUtilities()
{
    
}


//void GameBoard::DrawDirt()

void BoardUtilities::DrawDirt(int *pDirtTop, int pColumnCount, int pStartY, int pEndY)
{

    GameTile *aTile = 0;
    
    //int aEndY = mGridScreenStartY + mGridScreenHeight + 1;
    //if(aEndY > mGridHeight)aEndY = mGridHeight;
    
    int aDrawLoopWidth = 9;
    int aDrawLoopHeight = 8;
    
    int aSlotX = 0;
    int aSlotY = 0;
    
    //float aDirtLoopImageWidth = (float)gApp->mImageDirtLoop.mExpandedWidth;
    //float aDirtLoopImageHeight = (float)gApp->mImageDirtLoop.mExpandedHeight;
    
    float aDrawStartU[9];
    float aDrawEndU[9];
    
    float aDrawStartV[8];
    float aDrawEndV[8];
    
    
    
    int aImageWidth = 1024;
    int aImageHeight = 1024;
    
    int aPixelWidth = 576;
    int aPixelHeight = 512;
    
    //int aPixelStartU = 0;
    //int aPixelStartV = 0;
    
    float aBaseUStart = 0.0f;
    float aBaseVStart = 0.0f;
    
    float aUSpan = (((float)aPixelWidth) / ((double)aImageWidth)) / ((float)aDrawLoopWidth);
    float aVSpan = (((float)aPixelHeight) / ((double)aImageHeight)) / ((float)aDrawLoopHeight);
    
    for(int i=0;i<aDrawLoopWidth;i++)
    {
        float aStartU = aBaseUStart + (((float)i) * aUSpan);
        float aEndU = aBaseUStart + (((float)(i + 1)) * aUSpan);
        
        aDrawStartU[i] = aStartU;
        aDrawEndU[i] = aEndU;
    }
    
    for(int i=0;i<aDrawLoopHeight;i++)
    {
        float aStartV = aBaseVStart + (((float)i) * aVSpan);
        float aEndV = aBaseVStart + (((float)(i + 1)) * aVSpan);
        
        aDrawStartV[i] = aStartV;
        aDrawEndV[i] = aEndV;
    }
    
    float aUStart, aVStart, aUEnd, aVEnd;
    
    float aLoopRenderStartX = 0.0f;
    float aLoopRenderStartY = 0.0f;
    float aLoopRenderEndX = 0.0f;
    float aLoopRenderEndY = 0.0f;
    
    float aTileWidth = 80.0f;
    float aTileHeight = 80.0f;
    
    
    for(int i=0;i<pColumnCount;i++)
    {
        aLoopRenderStartX = (float)(i * aTileWidth);
        aLoopRenderEndX = aLoopRenderStartX + aTileWidth;
        
        aLoopRenderStartX -= 1.0f;
        aLoopRenderEndX += 1.0f;
        
        aSlotY = 0;
        
        for(int n=pEndY;n>=pStartY;n--)
        {
            //aTile = gBoard->mTile[i][n];
            //if(aTile)
            //{
                if(TileRendersAsDirt(i, n))
                {
                    aSlotY = (n % aDrawLoopHeight);
                    
                    aLoopRenderStartY = (float)(n * aTileHeight);
                    aLoopRenderEndY = aLoopRenderStartY + aTileHeight;
                    
                    aLoopRenderStartY -= 1.0f;
                    aLoopRenderEndY += 1.0f;
                    
                    aUStart = aDrawStartU[aSlotX];
                    aVStart = aDrawStartV[aSlotY];
                    
                    aUEnd = aDrawEndU[aSlotX];
                    aVEnd = aDrawEndV[aSlotY];
                    
                    //Graphics::RenderQuadScaled(aLoopRenderStartX, aLoopRenderStartY, aLoopRenderEndX, aLoopRenderStartY, aLoopRenderStartX, aLoopRenderEndY, aLoopRenderEndX, aLoopRenderEndY, aUStart , aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureFill.mTexture, (80.0f / 64.0f));
                    
                    Graphics::RenderQuad(aLoopRenderStartX, aLoopRenderStartY, aLoopRenderEndX, aLoopRenderStartY, aLoopRenderStartX, aLoopRenderEndY, aLoopRenderEndX, aLoopRenderEndY, aUStart , aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureFill.mTexture);
                    
                }
            //}
            
            aSlotY++;
            if(aSlotY == aDrawLoopHeight)aSlotY = 0;
        }
        
        aSlotX++;
        if(aSlotX == aDrawLoopWidth)aSlotX = 0;
    }
    
    bool aDirtUp = false;
    bool aDirtLeft = false;
    bool aDirtRight = false;
    bool aDirtLeftUp = false;
    bool aDirtRightUp = false;
    
    bool aDirtLeftDown = false;
    bool aDirtRightDown = false;
    
    Graphics::SetColor();
    

    Graphics::MatrixPush();
    Graphics::Scale(80.0f / 64.0f);
    
    for(int n=pEndY;n>=pStartY;n--)
    {
        for(int i=0;i<pColumnCount;i++)
        {
            aTile = gBoard->mTile[i][n];
            
                if(TileRendersAsDirt(i, n))
                {
                    aDirtUp = false;
                    aDirtLeft = false;
                    aDirtRight = false;
                    
                    if(TileRendersAsDirt(i, n-1))aDirtUp = true;
                    if(TileRendersAsDirt(i-1, n))aDirtLeft = true;
                    if(TileRendersAsDirt(i+1, n))aDirtRight = true;
                    
                    if((aDirtUp == false) || (aDirtRight == false) || (aDirtLeft == false))
                    {
                        aDirtLeftUp = false;
                        aDirtRightUp = false;
                        aDirtLeftDown = false;
                        aDirtRightDown = false;
                        
                        if(TileRendersAsDirt(i-1, n-1))aDirtLeftUp = true;
                        if(TileRendersAsDirt(i+1, n-1))aDirtRightUp = true;
                        if(TileRendersAsDirt(i-1, n+1))aDirtLeftDown = true;
                        if(TileRendersAsDirt(i+1, n+1))aDirtRightDown = true;
                        
                        
                        if(aDirtUp == false)
                        {
                            if(aDirtRight == false)
                            {
                                if(aDirtRightUp)DrawDirtTop(i, n, true, false);
                            }
                            else
                            {
                                if(aDirtRightUp == false)DrawDirtTop(i, n, true, false);
                            }
                            
                            
                            if(aDirtLeft == false)
                            {
                                if(aDirtLeftUp)DrawDirtTop(i, n, false, false);
                            }
                            else
                            {
                                if(aDirtLeftUp == false)DrawDirtTop(i, n, false, false);
                            }
                        }
                        
                        
                        if(aDirtLeft == false)
                        {
                            DrawDirtSide(i, n, false, true);
                            
                            if(aDirtLeftDown)
                            {
                                DrawDirtCorner(i, n, false);
                            }
                            else
                            {
                                DrawDirtSide(i, n, false, false);
                                
                            }
                        }
                        
                        if(aDirtRight == false)
                        {
                            DrawDirtSide(i, n, true, true);
                            
                            if(aDirtRightDown)
                            {
                                DrawDirtCorner(i, n, true);
                            }
                            else
                            {
                                DrawDirtSide(i, n, true, false);
                            }
                        }
                        
                        if(aDirtUp == false)
                        {
                            if(aDirtRight == false)
                            {
                                if(aDirtRightUp == false)DrawDirtTop(i, n, true, true);
                            }
                            else
                            {
                                if(aDirtRightUp)DrawDirtTop(i, n, true, true);
                            }
                            
                            
                            if(aDirtLeft == false)
                            {
                                if(aDirtLeftUp == false)DrawDirtTop(i, n, false, true);
                            }
                            else
                            {
                                if(aDirtLeftUp)DrawDirtTop(i, n, false, true);
                            }
                        }
                    }
                //}
            }
        }
    }
    
    Graphics::MatrixPop();
}

void BoardUtilities::DrawDirtSide(int pGridX, int pGridY, bool pRight, bool pTop)
{
    //float aTileCenterX = CenterX(pGridX);
    
    //float aTileCenterY = CenterY(pGridY);
    
    float aTileCenterX = (float)pGridX * 64.0f + (64.0f / 2.0f);
    float aTileCenterY = (float)pGridY * 64.0f + (64.0f / 2.0f);
    
    
    float aImageCenterX = 0.0f;
    float aImageCenterY = 0.0f;
    
    float aXStart, aYStart, aXEnd, aYEnd;
    float aUStart, aVStart, aUEnd, aVEnd;
    
    
    float aImageWidth = (float)(gApp->mDirtTextureSides.mWidth);
    float aImageHeight = (float)(gApp->mDirtTextureSides.mHeight);
    
    
    float aTileWidth = 64.0f;
    float aTileHeight = 64.0f;
    
    
    //int aBindIndex = gApp->mImageDirtSidesUVW.mBindIndex;
    
    aImageCenterX = ((float)pGridX) * 96.0f + 64.0f;
    aImageCenterY = ((float)(pGridY % 8)) * 64.0f + 64.0f;
    
    if(pRight)aXStart = aImageCenterX;
    else aXStart = aImageCenterX - 48.0f;
    
    if(pTop)aYStart = aImageCenterY - aTileWidth / 2.0f;
    else aYStart = aImageCenterY;
    
    aXEnd = aXStart + 48.0f;
    aYEnd = aYStart + 32.0f;
    
    aUStart = aXStart / aImageWidth;
    aVStart = aYStart / aImageHeight;
    aUEnd = aXEnd / aImageWidth;
    aVEnd = aYEnd / aImageHeight;
    
    aXStart += (aTileCenterX - aImageCenterX);
    aYStart += (aTileCenterY - aImageCenterY);
    aXEnd += (aTileCenterX - aImageCenterX);
    aYEnd += (aTileCenterY - aImageCenterY);
    
    
    //gRenderQueue.EnqueueQuad
    
    
    
    //Graphics::RenderQuadScaled(aXStart, aYStart, aXEnd, aYStart, aXStart, aYEnd, aXEnd, aYEnd, aUStart, aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureSides.mTexture, (80.0f / 64.0f), aTileCenterX, aTileCenterY);
    
    Graphics::RenderQuad(aXStart, aYStart, aXEnd, aYStart, aXStart, aYEnd, aXEnd, aYEnd, aUStart, aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureSides.mTexture);
    

}

void BoardUtilities::DrawDirtCorner(int pGridX, int pGridY, bool pRight)
{
    //float aTileCenterX = CenterX(pGridX);
    //float aTileCenterY = CenterY(pGridY);
    
    float aTileCenterX = (float)pGridX * 64.0f + (64.0f / 2.0f);
    float aTileCenterY = (float)pGridY * 64.0f + (64.0f / 2.0f);

    
    float aImageCenterX = 0.0f;
    float aImageCenterY = 0.0f;
    
    float aXStart, aYStart, aXEnd, aYEnd;
    float aUStart, aVStart, aUEnd, aVEnd;
    
    float aImageWidth = (float)(gApp->mDirtTextureBottoms.mWidth);
    float aImageHeight = (float)(gApp->mDirtTextureBottoms.mHeight);
    
    float aTileWidth = 64.0f;
    float aTileHeight = 64.0f;
    
    //int aBindIndex = gApp->mImageDirtCornersUVW.mBindIndex;
    
    aImageCenterX = ((float)pGridX) * 96.0f + aTileWidth;
    aImageCenterY = ((float)(pGridY % 8)) * aTileHeight + aTileHeight;
    
    if(pRight)aXStart = aImageCenterX;
    else aXStart = aImageCenterX - 48.0f;
    
    aYStart = aImageCenterY;
    
    aXEnd = aXStart + 48.0f;
    aYEnd = aYStart + 48.0f;
    
    aUStart = aXStart / aImageWidth;
    aVStart = aYStart / aImageHeight;
    aUEnd = aXEnd / aImageWidth;
    aVEnd = aYEnd / aImageHeight;
    
    aXStart += (aTileCenterX - aImageCenterX);
    aYStart += (aTileCenterY - aImageCenterY);
    aXEnd += (aTileCenterX - aImageCenterX);
    aYEnd += (aTileCenterY - aImageCenterY);
    
    //gRenderQueue.EnqueueQuad
    
    //Graphics::RenderQuadScaled(aXStart, aYStart, aXEnd, aYStart, aXStart, aYEnd, aXEnd, aYEnd, aUStart, aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureBottoms.mTexture, (80.0f / 64.0f), aTileCenterX, aTileCenterY);
    
    Graphics::RenderQuad(aXStart, aYStart, aXEnd, aYStart, aXStart, aYEnd, aXEnd, aYEnd, aUStart, aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureBottoms.mTexture);
    
}

void BoardUtilities::DrawDirtTop(int pGridX, int pGridY, bool pRight, bool pEdge)
{
    float aTileCenterX = (float)pGridX * 64.0f + (64.0f / 2.0f);
    float aTileCenterY = (float)pGridY * 64.0f + (64.0f / 2.0f);

    //float aTileCenterX = CenterX(pGridX);
    //float aTileCenterY = CenterY(pGridY);
    
    float aImageCenterX = 0.0f;
    float aImageCenterY = 0.0f;
    
    float aXStart, aYStart, aXEnd, aYEnd;
    float aUStart, aVStart, aUEnd, aVEnd;
    
    float aImageWidth = (float)(gApp->mDirtTextureSides.mWidth);
    float aImageHeight = (float)(gApp->mDirtTextureSides.mHeight);
    
    //aTileCenterX = pTile->mCenterX;
    //aTileCenterY = pTile->mCenterY;
    
    int aXIndex = pGridX % 4;
    
    //aXIndex = pTile->mGridX % 2;
    
    aImageCenterX = ((float)(aXIndex)) * 64.0f + 64.0f;
    aImageCenterY = 128.0f + 512.0f;
    
    if(pEdge)
    {
        if((aXIndex & 1) == 0)
        {
            aImageCenterY += 48.0f;
        }
        else
        {
            aImageCenterY += 96.0f;
        }
    }
    
    float aWidth = 32.0f;
    if(pEdge)aWidth = 48.0f;
    
    aYStart = aImageCenterY - 16.0f;
    
    if(pRight)
    {
        aXStart = aImageCenterX;
    }
    else
    {
        aXStart = aImageCenterX - aWidth;
    }
    
    aXEnd = aXStart + aWidth;
    aYEnd = aYStart + 32.0f;
    
    
    aUStart = aXStart / aImageWidth;
    aVStart = aYStart / aImageHeight;
    aUEnd = aXEnd / aImageWidth;
    aVEnd = aYEnd / aImageHeight;
    
    aImageCenterY += 32.0f;
    
    aXStart += (aTileCenterX - aImageCenterX);
    aYStart += (aTileCenterY - aImageCenterY);
    aXEnd += (aTileCenterX - aImageCenterX);
    aYEnd += (aTileCenterY - aImageCenterY);
    
    
    aYStart -= 6.0f;
    aYEnd -= 6.0f;
    
    //gRenderQueue.EnqueueQuad
    
    //Graphics::RenderQuadScaled(aXStart, aYStart, aXEnd, aYStart, aXStart, aYEnd, aXEnd, aYEnd, aUStart, aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureSides.mTexture, (84.0f / 64.0f));
    
    Graphics::RenderQuad(aXStart, aYStart, aXEnd, aYStart, aXStart, aYEnd, aXEnd, aYEnd, aUStart, aVStart, aUEnd, aVStart, aUStart, aVEnd, aUEnd, aVEnd, gApp->mDirtTextureSides.mTexture);
    
    
}

bool BoardUtilities::TileRendersAsDirt(int pGridX, int pGridY)
{
    bool aReturn = false;
    
    if((pGridX >= 0) && (pGridX < gBoard->mGridWidth) && (pGridY >= 0) && (pGridY < gBoard->mGridHeight))
    {
        if(gBoard->mDirtTop[pGridX] <= pGridY)
        {
            aReturn = true;
        }
    }
    
    return aReturn;
}

void BoardUtilities::Save(const char *pPath)
{
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    
    aPath = (gDirDocuments + aPath);
    
    FXML aXML;
    
    FXMLTag *aLevelTag = new FXMLTag("level");
    aXML.mRoot = aLevelTag;
    
    aLevelTag->AddParamInt("grid_width", mBoard->mGridWidth);
    aLevelTag->AddParamInt("grid_height", mBoard->mGridHeight);
    
    
    FXMLTag *aDirtTopTag = new FXMLTag("dirt_info");
    *aLevelTag += aDirtTopTag;
    
    for(int i=0;i<mBoard->mGridWidth;i++)
    {
        FString aParam = FString("top_") + FString(i);
        aDirtTopTag->AddParamInt(aParam.c(), mBoard->mDirtTop[i]);
    }
    
    
    
    FXMLTag *aTileListTag = new FXMLTag("tile_list");
    *aLevelTag += aTileListTag;
    
    for(int i=0;i<mBoard->mGridWidth;i++)
    {
        for(int n=0;n<mBoard->mGridHeight;n++)
        {
            GameTile *aTile = mBoard->mTile[i][n];
            if(aTile)
            {
                if(aTile->mMultiPart == false)
                {
                    FXMLTag *aTileTag = new FXMLTag("tile");
                    *aTileListTag += aTileTag;
                    
                    int aTileType = aTile->mTileType;
                    
                    aTileTag->AddParamInt("tile_type", aTileType);
                    
                    aTile->Save(aTileTag);
                }
            }
        }
    }
    
    aXML.Print();
    aXML.Save(aPath);
    
}

float BoardUtilities::CenterX(int pGridX)
{
    
    return mBoard->GetTileCenterX(pGridX);
}

float BoardUtilities::CenterY(int pGridY)
{
    
    return mBoard->GetTileCenterY(pGridY);
}

void BoardUtilities::Load(const char *pPath)
{
    FString aPath = FString(pPath);
    if(aPath.mLength <= 0)aPath = "test_level.xml";
    
    FXML aXML;
    aXML.Load(aPath);
    //aXML.Print();
    
    if(aXML.mRoot == 0)aXML.Load(FString(aPath + ".xml"));
    if(aXML.mRoot == 0)aXML.Load(FString(aPath + ".XML"));
    if(aXML.mRoot == 0)aXML.Load(FString(gDirBundle + aPath));
    if(aXML.mRoot == 0)aXML.Load(FString(gDirBundle + aPath + ".xml"));
    if(aXML.mRoot == 0)aXML.Load(FString(gDirBundle + aPath + ".XML"));
    
    FXMLTag *aLevelTag = aXML.mRoot;
    
    if(aLevelTag)
    {
        int aGridWidth = aLevelTag->GetParamInt("grid_width");
        int aGridHeight = aLevelTag->GetParamInt("grid_height");
        
        mBoard->SizeGrid(aGridWidth, aGridHeight);
        
        
        EnumTagsMatching(aLevelTag, aDirtTopTag, "dirt_info")
        {
            for(int i=0;i<mBoard->mGridWidth;i++)
            {
                FString aParam = FString("top_") + FString(i);
                //aDirtTopTag->AddParamInt(aParam.c(), );
                
                mBoard->mDirtTop[i] = aDirtTopTag->GetParamInt(aParam.c());
            }
        }
        
        EnumTagsMatching(aLevelTag, aTileListTag, "tile_list")
        {
            EnumTagsMatching(aTileListTag, aTileTag, "tile")
            {
                int aTileType = aTileTag->GetParamInt("tile_type");
                
                GameTile *aTile = 0;
                
                if(aTileType == GAME_TILE_TYPE_MATCHABLE)aTile = new GameTileMatchable();
                if(aTileType == GAME_TILE_TYPE_ROCK)aTile = new GameTileRock();
                
                if(aTileType == GAME_TILE_TYPE_POWERUP)aTile = new GameTilePowerUp();
                if(aTileType == GAME_TILE_TYPE_TREASURE)aTile = new GameTileTreasure();
                
                if(aTileType == GAME_TILE_TYPE_STAR)aTile = new GameTileStar();
                
                if(aTileType == GAME_TILE_TYPE_METAL)aTile = new GameTileMetal();
                
                
                if(aTile)
                {
                    aTile->Load(aTileTag);
                    
                    if(mBoard->SetTile(aTile->mGridX, aTile->mGridY, aTile))
                    {
                        
                    }
                    else
                    {
                        delete aTile;
                        aTile = 0;
                    }
                    
                    if((aTile->mGridX >= 0) && (aTile->mGridY >= 0) && (aTile->mGridX < mBoard->mGridWidth) && (aTile->mGridY < mBoard->mGridHeight))
                    {
                        
                    }
                }
            }
        }
        
        
    }
    else
    {
        
        mBoard->SizeGrid(DEFAULT_GRID_WIDTH, 9);
        
#ifdef EDITOR_MODE
        if(gEditor)gEditor->EditorFillWithDirt();
#else
        mBoard->GenerateTiles(DEFAULT_GRID_WIDTH, 9);
#endif
        
    }
    
    
    //mGrid.FillWithDirt();
    
#ifdef EDITOR_MODE
    
#else
    
    mBoard->FitGridToDevice();
    
#endif
    
    for(int i=0;i<mBoard->mGridWidth;i++)
    {
        for(int n=0;n<mBoard->mGridHeight;n++)
        {
            GameTile *aTile = mBoard->mTile[i][n];
            if(aTile)
            {
                
                if(aTile->mTileType == GAME_TILE_TYPE_MATCHABLE)
                {
                    ((GameTileMatchable *)aTile)->mMatchType = gRand.Get(mBoard->mMatchTypeCount);
                    
                    //((GameTileOldBubble *)aTile)->mMatchType = 2;
                    
                }
                else if(aTile->mTileType == GAME_TILE_TYPE_TREASURE)
                {
                    ((GameTileTreasure *)aTile)->mSpecialIndex = gRand.Get(3);
                    ((GameTileTreasure *)aTile)->mBackgroundIndex = gRand.Get(4);
                    
                    
                    //((GameTileOldBubble *)aTile)->mMatchType = 2;
                    
                }
                else
                {
                    //aTile->mBuried = true;
                }
            }
        }
    }
    
    //mGrid.ReachabilityCheck(-1);
    
    //ReachabilityCheck(-1);
    
    for(int i=0;i<mBoard->mGridWidth;i++)
    {
        for(int n=0;n<mBoard->mGridHeight;n++)
        {
            GameTile *aTile = mBoard->mTile[i][n];
            if(aTile)
            {
                //aTile->mDiscoveredRecently = true;
                //aTile->mReachableNewly = false;
            }
        }
    }
    
    //mDidLoad = true;
}
