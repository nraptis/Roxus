//
//  TileLooper.h
//  CoreDemo
//
//  Created by Nick Raptis on 11/2/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__TileLooper__
#define __CoreDemo__TileLooper__

#include "FSprite.h"
#include "FString.h"
#include "FRect.h"
#include "FApp.h"
#include "core_graphics.h"

class TileLooperTile;

class TileLooper
{
public:
  
    TileLooper();
    ~TileLooper();
    
    void                            SetUp(float pX, float pY, int pGridWidth, int pGridHeight, float pTileWidth, float pTileHeight, FTexture *pTexture);
    
    void                            Free();
    
    void                            SetTexture(int pGridX, int pGridY, FTexture *pTexture);
    
    TileLooperTile                  *GetTile(int pGridX, int pGridY);
    
    void                            Draw(FRect pBounds);
    
    TileLooperTile                  ***mTile;
    
    int                             mWidth;
    int                             mHeight;
    
    float                           mTileWidth;
    float                           mTileHeight;
    
    float                           mX;
    float                           mY;
    
    float                           mStartU;
    float                           mStartV;
    
    float                           mEndU;
    float                           mEndV;
    
};


class TileLooperTile
{
public:
    
    TileLooperTile();
    ~TileLooperTile();
    
    void                            SetUp(float pX, float pY, float pWidth, float pHeight, float pStartU, float pStartV, float pEndU, float pEndV, FTexture *pTexture);
    
    //void                            SetUp(float pX, float pY, float pWidth, float pHeight, FTexture *pTexture);
    
    void                            SetTexture(FTexture *pTexture);
    FTexture                        *mTexture;
    
    void                            Draw();
    
    float                           mBufferVertex[16];
    float                           mBufferUV[16];
    
    //The background one would probably look neater with color shifts happening as we dive down..
    //float                           mBufferColor[16];
    
    GFX_MODEL_INDEX_TYPE            mBufferIndex[6];
    
    //float                           mBufferColor[16];
    
    int                             mBindIndex;
    
};


#endif /* defined(__CoreDemo__TileLooper__) */
