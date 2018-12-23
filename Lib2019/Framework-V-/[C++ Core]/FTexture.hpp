//
//  FTexture.h
//  RaptisGame
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_TEXTURE_H
#define FRAMEWORK_TEXTURE_H

#define SET_TEXTURE_BODY if(mTexture){if(pTexture != mTexture){if(gTextureCache.mAutoMode == true)gTextureCache.TextureBindRemove(mTexture);mTexture = 0;}}if(pTexture){mTexture = pTexture;if(gTextureCache.mAutoMode == true)gTextureCache.TextureBindAdd(mTexture);}

#include "FString.h"

class FSprite;
class FImage;
class FTexture
{
public:
    FTexture(const char *pFileName);
    FTexture();
    
    virtual ~FTexture();

    void                                    Initialize(const char *pFilePath);
    void                                    Initialize();

    bool                                    IsValid();
    
    FString                                 mFileName;

    void                                    Load(FImage *pImage);
    void                                    Realize();
    void                                    Unload();
    
    int                                     mBindIndex;
    
    bool                                    mDidFailLoad;
    
    int                                     mWidth;
    int                                     mHeight;
    
    int                                     mOffsetX;
    int                                     mOffsetY;
    
    int                                     mExpandedWidth;
    int                                     mExpandedHeight;

    float                                   GetStartU();
    float                                   GetStartV();

    float                                   GetEndU();
    float                                   GetEndV();
};

class FTextureRect
{
public:
    
    FTextureRect();
    virtual ~FTextureRect();
    
    float                                   mTextureCoord[8];
    float                                   mVertex[8];
    
    void                                    Set(FTexture *pTexture, float pX=0, float pY=0);
    
    inline float                            GetStartU(){return mTextureCoord[0];}
    inline float                            GetStartV(){return mTextureCoord[1];}
    inline float                            GetEndU(){return mTextureCoord[6];}
    inline float                            GetEndV(){return mTextureCoord[7];}
    
    inline float                            GetStartX(){return mVertex[0];}
    inline float                            GetStartY(){return mVertex[1];}
    inline float                            GetEndX(){return mVertex[6];}
    inline float                            GetEndY(){return mVertex[7];}

    inline void                             SetStartU(float pU){mTextureCoord[0]=pU;mTextureCoord[4]=pU;}
    inline void                             SetStartV(float pV){mTextureCoord[1]=pV;mTextureCoord[3]=pV;}
    inline void                             SetEndU(float pU){mTextureCoord[6]=pU;mTextureCoord[2]=pU;}
    inline void                             SetEndV(float pV){mTextureCoord[7]=pV;mTextureCoord[5]=pV;}
    
    inline void                             SetStartX(float pX){mVertex[0]=pX;mVertex[4]=pX;}
    inline void                             SetStartY(float pY){mVertex[1]=pY;mVertex[3]=pY;}
    inline void                             SetEndX(float pX){mVertex[6]=pX;mVertex[2]=pX;}
    inline void                             SetEndY(float pY){mVertex[7]=pY;mVertex[5]=pY;}
    
    void                                    SetUVQuad(float pStartU, float pStartV, float pEndU, float pEndV);
    void                                    SetUVRect(float pStartU, float pStartV, float pWidthU, float pHeightV);
    
    void                                    SetQuad(float pStartX, float pStartY, float pEndX, float pEndY);
    void                                    SetRect(float pStartX, float pStartY, float pWidth, float pHeight);
    
    void                                    SetQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
};

class FTextureTriangle
{
public:
    
    FTextureTriangle();
    virtual ~FTextureTriangle();
    
    float                                   mTextureCoord[6];
    float                                   mVertex[6];
    
    void                                    SetXYTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);
    void                                    SetUVTriangle(float pU1, float pV1, float pU2, float pV2, float pU3, float pV3);
};

#endif /* defined(__RaptisGame__FTexture__) */
