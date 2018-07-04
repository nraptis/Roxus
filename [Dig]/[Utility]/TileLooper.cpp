//
//  TileLooper.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 11/2/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "TileLooper.h"
#include "core_includes.h"

TileLooper::TileLooper()
{
    mTile = 0;
    
    mWidth = 0;
    mHeight = 0;
    
    mTileWidth = 256;
    mTileHeight = 256;
    
    mX = 0.0f;
    mY = 0.0f;
    
    
    
    mStartU = 0.0f;
    mStartV = 0.0f;
    
    mEndU = 1.0f;
    mEndV = 1.0f;
    
}

TileLooper::~TileLooper()
{
    Free();
}

void TileLooper::Free()
{
    for(int i=0;i<mWidth;i++)
    {
        for(int n=0;n<mHeight;n++)
        {
            delete mTile[i][n];
        }
        delete [] mTile[i];
    }
    delete [] mTile;
    mTile = 0;
    
    mWidth = 0;
    mHeight = 0;
}

void TileLooper::SetUp(float pX, float pY, int pGridWidth, int pGridHeight, float pTileWidth, float pTileHeight, FTexture *pTexture)
{
    Free();
    
    
    mTileWidth = pTileWidth;
    mTileHeight = pTileHeight;
    
    mX = pX;
    mY = pY;
    
    
    mWidth = pGridWidth;
    mHeight = pGridHeight;
    
    mTile = new TileLooperTile**[mWidth];
    
    for(int i=0;i<mWidth;i++)
    {
        mTile[i] = new TileLooperTile*[mHeight];
        for(int n=0;n<mHeight;n++)
        {
            mTile[i][n] = new (TileLooperTile);
            mTile[i][n]->SetUp(mX + mTileWidth * ((float)i), mY + mTileHeight * ((float)n), mTileWidth, mTileHeight, mStartU, mStartV, mEndU, mEndV, pTexture);
        }
    }
}

void TileLooper::Draw(FRect pBounds)
{
    if((mWidth > 0) && (mHeight > 0))
    {
        int aStartDrawX = (int)((pBounds.mX - mX) / mTileWidth);
        int aStartDrawY = (int)((pBounds.mY - mY) / mTileHeight);
        
        int aEndDrawX = (int)(((pBounds.mX - mX) + pBounds.mWidth) / mTileWidth);
        int aEndDrawY = (int)(((pBounds.mY - mY) + pBounds.mHeight) / mTileHeight);
        
        if(aStartDrawX < 0)aStartDrawX = 0;
        if(aStartDrawY < 0)aStartDrawY = 0;
        
        if(aEndDrawX >= mWidth)aEndDrawX = (mWidth - 1);
        if(aEndDrawY >= mHeight)aEndDrawY = (mHeight - 1);
        
        for(int i=aStartDrawX;i<=aEndDrawX;i++)
        {
            for(int n=aStartDrawY;n<=aEndDrawY;n++)
            {
                TileLooperTile *aTile = mTile[i][n];
                
                if(aTile)
                {
                    aTile->Draw();
                }
            }
        }
    }
}

void TileLooper::SetTexture(int pGridX, int pGridY, FTexture *pTexture)
{
    TileLooperTile *aTile = GetTile(pGridX, pGridY);
    if(aTile)
    {
        aTile->SetTexture(pTexture);
    }
}

TileLooperTile *TileLooper::GetTile(int pGridX, int pGridY)
{
    TileLooperTile *aReturn = 0;
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight))
    {
        aReturn = mTile[pGridX][pGridY];
    }
    return aReturn;
}

TileLooperTile::TileLooperTile()
{
    mBufferVertex[0] = -128;
    mBufferVertex[1] = -128;
    mBufferVertex[2] = 128;
    mBufferVertex[3] = -128;
    mBufferVertex[4] = -128;
    mBufferVertex[5] = 128;
    mBufferVertex[6] = 128;
    mBufferVertex[7] = 128;
    
    mBufferVertex[8 + 0] = 0;
    mBufferVertex[8 + 1] = 0;
    mBufferVertex[8 + 2] = 1;
    mBufferVertex[8 + 3] = 0;
    mBufferVertex[8 + 4] = 0;
    mBufferVertex[8 + 5] = 1;
    mBufferVertex[8 + 6] = 1;
    mBufferVertex[8 + 7] = 1;
    
    mBufferIndex[0] = 0;
    mBufferIndex[1] = 2;
    mBufferIndex[2] = 1;
    mBufferIndex[3] = 1;
    mBufferIndex[4] = 2;
    mBufferIndex[5] = 3;
    
    mBindIndex = -1;
    
    mTexture = 0;
}

TileLooperTile::~TileLooperTile()
{
    
}

//void TileLooperTile::SetUp(float pX, float pY, float pWidth, float pHeight, FTexture *pTexture)

void TileLooperTile::SetUp(float pX, float pY, float pWidth, float pHeight, float pStartU, float pStartV, float pEndU, float pEndV, FTexture *pTexture)
{
    //mBufferVertex[0] = pX;
    //mBufferVertex[1] = pY;
    //mBufferVertex[2] = pX + pWidth;
    //mBufferVertex[3] = pY;
    //mBufferVertex[4] = pX;
    //mBufferVertex[5] = pY + pHeight;
    //mBufferVertex[6] = pX + pWidth;
    //mBufferVertex[7] = pY + pHeight;
    
    mBufferVertex[0] = pX;
    mBufferVertex[1] = pY;
    mBufferVertex[2] = pX;
    mBufferVertex[3] = pY + pHeight;
    mBufferVertex[4] = pX + pWidth;
    mBufferVertex[5] = pY;
    mBufferVertex[6] = pX + pWidth;
    mBufferVertex[7] = pY + pHeight;
    
    mBufferUV[0] = pStartU;
    mBufferUV[1] = pStartV;
    mBufferUV[2] = pStartU;
    mBufferUV[3] = pEndV;
    mBufferUV[4] = pEndU;
    mBufferUV[5] = pStartV;
    mBufferUV[6] = pEndU;
    mBufferUV[7] = pEndV;
    
    SetTexture(pTexture);
}

void TileLooperTile::SetTexture(FTexture *pTexture)
{
    SET_TEXTURE_BODY;
}

void TileLooperTile::Draw()
{
    //gRenderQueue.EnqueueQuad
    
    //Graphics::RenderQuad(mBufferVertex[0], mBufferVertex[1], mBufferVertex[2], mBufferVertex[3], mBufferVertex[4], mBufferVertex[5], mBufferVertex[6], mBufferVertex[7], mTexture);
    
    Graphics::RenderQuad(mBufferVertex[0], mBufferVertex[1], mBufferVertex[2], mBufferVertex[3], mBufferVertex[4], mBufferVertex[5], mBufferVertex[6], mBufferVertex[7],
                         mBufferUV[0], mBufferUV[1], mBufferUV[2], mBufferUV[3], mBufferUV[4], mBufferUV[5], mBufferUV[6], mBufferUV[7], mTexture);
    
    
    /*
    
    if(mBufferSlotVertex <= 0)
    {
        mBufferSlotVertex = gfx_bufferVertexGenerate(mBufferVertex, 16);
        mBufferSlotIndex = gfx_bufferIndexGenerate(mBufferIndex, 6);
    }
    
    if(mBindIndex != -1)
    {
        gfx_bufferVertexBind(mBufferSlotVertex);
        gfx_bufferIndexBind(mBufferSlotIndex);
    
        gfx_positionSetPointer(2, 0);
        gfx_texCoordSetPointer(2, 8);
    
        gfx_bindTexture(mBindIndex);
        gfx_drawElementsTriangle(6, 0);
    }
    */

    
}








/*

#include "FSprite.h"
#include "FImage.h"
#include "FApp.h"


FSprite::FSprite()
{
 
}

FSprite::~FSprite()
{
    
}

void FSprite::Kill()
{
    mWidth = 0.0f;
    mHeight = 0.0f;
    
    mWidth2 = 0.0f;
    mHeight2 = 0.0f;
    
    if(mBindIndex != -1)
    {
        if(gAppBase)
        {
            gAppBase->BindRemove(mBindIndex);
        }
        
        mBindIndex = -1;
    }
    
    gfx_bufferDelete(mBufferSlotVertex);
    gfx_bufferDelete(mBufferSlotIndex);
    
    mBufferSlotVertex = 0;
    mBufferSlotIndex = 0;
    
}

void FSprite::Load(const char *pFileName)
{
    FImage aImage;
    aImage.Load(pFileName);
    Load(&aImage);
}

void FSprite::Load(FImage *pImage)
{
    Kill();
    
    if(pImage)
    {
        pImage->Bind();
        
        if(pImage->mBindIndex > 0 && pImage->mWidth > 0 && pImage->mHeight > 0)
        {
            mBindIndex = pImage->mBindIndex;
            if(gAppBase)gAppBase->BindAdd(mBindIndex);
            
            mWidth = (float)pImage->mWidth;
            mHeight = (float)pImage->mHeight;
            
            mWidth2 = mWidth / 2.0f;
            mHeight2 = mHeight / 2.0f;
            
            mBufferVertex[0] = -mWidth2;
            mBufferVertex[1] = -mHeight2;
            mBufferVertex[2] = mWidth2;
            mBufferVertex[3] = -mHeight2;
            mBufferVertex[4] = -mWidth2;
            mBufferVertex[5] = mHeight2;
            mBufferVertex[6] = mWidth2;
            mBufferVertex[7] = mHeight2;
            
            float aStartU=(float)pImage->mOffsetX/(float)pImage->mExpandedWidth;
            float aStartV=(float)pImage->mOffsetY/(float)pImage->mExpandedHeight;
            float aEndU=(float)(pImage->mOffsetX + pImage->mWidth)/(float)pImage->mExpandedWidth;
            float aEndV=(float)(pImage->mOffsetY + pImage->mHeight)/(float)pImage->mExpandedHeight;
            
            mBufferVertex[8 + 0] = aStartU;
            mBufferVertex[8 + 1] = aStartV;
            mBufferVertex[8 + 2] = aEndU;
            mBufferVertex[8 + 3] = aStartV;
            mBufferVertex[8 + 4] = aStartU;
            mBufferVertex[8 + 5] = aEndV;
            mBufferVertex[8 + 6] = aEndU;
            mBufferVertex[8 + 7] = aEndV;
            
            //mTextureCoord[0]=aStartU;
            //mTextureCoord[1]=aStartV;
            //mTextureCoord[2]=aEndU;
            //mTextureCoord[3]=aStartV;
            //mTextureCoord[4]=aStartU;
            //mTextureCoord[5]=aEndV;
            //mTextureCoord[6]=aEndU;
            //mTextureCoord[7]=aEndV;
            
            mBufferSlotVertex = gfx_bufferVertexGenerate(mBufferVertex, 16);
            mBufferSlotIndex = gfx_bufferIndexGenerate(mBufferIndex, 6);
            
        }
    }
}

bool FSprite::DidLoad()
{
    bool aReturn = true;
    
    if(mBindIndex <= 0)aReturn = false;
    if(mWidth <= 0)aReturn = false;
    if(mHeight <= 0)aReturn = false;
    
    return aReturn;
}

void FSprite::Center(float pX, float pY)
{
    FMatrix aHold = Graphics::GetMatrixModelView();
    FMatrix aMatrix = aHold;
    aMatrix.Translate(pX, pY);
    //aMatrix = FMatrixTranslate(aMatrix, pX, pY, 0.0f);
    Graphics::SetMatrixModelView(aMatrix);
    Draw();
    Graphics::SetMatrixModelView(aHold);
}

void FSprite::Draw(float pX, float pY)
{
    Center(pX + mWidth2, pY + mHeight2);
}

void FSprite::DrawScaled(float pX, float pY, float pScale)
{
    FMatrix aHold = Graphics::GetMatrixModelView();
    FMatrix aMatrix = aHold;
    
    aMatrix.Translate(pX, pY);
    if(pScale != 1.0f)aMatrix.Scale(pScale);
    
    Graphics::SetMatrixModelView(aMatrix);
    Draw();
    Graphics::SetMatrixModelView(aHold);
}

void FSprite::DrawRotated(float pX, float pY, float pRotation)
{
    FMatrix aHold = Graphics::GetMatrixModelView();
    FMatrix aMatrix = aHold;
    
    aMatrix.Translate(pX, pY);
    if(pRotation != 0.0f)aMatrix.Rotate(pRotation);
    
    Graphics::SetMatrixModelView(aMatrix);
    Draw();
    Graphics::SetMatrixModelView(aHold);
}

void FSprite::Draw(float pX, float pY, float pRotation, float pScale)
{
    FMatrix aHold = Graphics::GetMatrixModelView();
    FMatrix aMatrix = aHold;
    
    aMatrix.Translate(pX, pY);
    if(pScale != 1.0f)aMatrix.Scale(pScale);
    if(pRotation != 0.0f)aMatrix.Rotate(pRotation);
    Graphics::SetMatrixModelView(aMatrix);
    
    Draw();
    Graphics::SetMatrixModelView(aHold);
}

void FSprite::Draw()
{
    //glUseProgram(gGLProgram);
    //gfx_shaderAttachFragment(gGLShaderFragmentTexture);
    
    gfx_bufferVertexBind(mBufferSlotVertex);
    gfx_bufferIndexBind(mBufferSlotIndex);
    
    gfx_positionSetPointer(2, 0);
    gfx_texCoordSetPointer(2, 8);
    
    gfx_bindTexture(mBindIndex);
    gfx_drawElementsTriangle(6, 0);
}

*/

