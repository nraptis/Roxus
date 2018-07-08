#ifndef SPRITE_H
#define SPRITE_H

#include "Image.h"
#include "FPoint.h"
#include "stdafx.h"
#include "ImageBundler.h"
#include "FString.h"

class Sprite
{
public:
    
	Sprite();
	~Sprite();
	
	//void				Load(Splat *pSplat, char *pName);
	//void				Load(SplatChunk *pChunk, Splat *pSplat, char *pName);
    
	void				Load(char *pName, ImageBundler *pBundler);
	inline void			Load(const char *pFile, ImageBundler *pBundler){Load((char*)pFile,pBundler);}
	inline void			Load(FString pFile, ImageBundler *pBundler){Load(pFile.c(),pBundler);}
    
	inline void			Load(FString pFile){Load(pFile.c());}
	inline void			Load(const char *pFile){Load((char*)pFile);}
	void				Load(char *pFile);
    void				Load(const char *pFileStart, int pIndex, const char *pFileEnd=0);
	void				Load(Image *pImage);
	void				Load(Image *pImage, int x, int y, int pWidth, int pHeight);
    
    void                SetupBackground(Image *pImage, int pAppWidth, int pAppHeight, int pImageRectX, int pImageRectY, int pImageRectWidth, int pImageRectHeight);
    
    
    void                CalculateUV(int x, int y, int pWidth, int pHeight, int pImageWidth, int pImageHeight, bool pCentered=true, bool pRotate=false);
    void                StretchTo(Image *pImage, int pNewWidth, int pNewHeight); 
	
	void				Rotate90();
    
    void				Recenter(float pX, float pY);
    
	
	void				Kill();
	
	void				DrawPercentH(float pStartPercent, float pEndPercent);
	void				DrawPercentH(float pEndPercent){DrawPercentH(0,pEndPercent);}
	
	void				DrawPercentH(float x, float y, float pStartPercent, float pEndPercent);
	void				DrawPercentH(float x, float y, float pEndPercent){DrawPercentH(x,y,0,pEndPercent);}
	
	void				DrawPercentH(FPoint pPos, float pStartPercent, float pEndPercent){DrawPercentH(pPos.mX,pPos.mY,pStartPercent,pEndPercent);}
	void				DrawPercentH(FPoint pPos, float pEndPercent){DrawPercentH(pPos.mX,pPos.mY,0,pEndPercent);}
	
	
	void				DrawPercentV(float pStartPercent, float pEndPercent);
	void				DrawPercentV(float pEndPercent){DrawPercentV(0,pEndPercent);}
	
	void				DrawPercentV(float x, float y, float pStartPercent, float pEndPercent);
	void				DrawPercentV(float x, float y, float pEndPercent){DrawPercentV(x,y,0,pEndPercent);}
	
	void				DrawPercentV(FPoint pPos, float pStartPercent, float pEndPercent){DrawPercentV(pPos.mX,pPos.mY,pStartPercent,pEndPercent);}
	void				DrawPercentV(FPoint pPos, float pEndPercent){DrawPercentV(pPos.mX,pPos.mY,0,pEndPercent);}
	
	
	void				Draw();
	void				Draw(float x, float y);
	void				Draw(float x, float y, float pScale, float pRotationDegrees=0);
    void				Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing);
	inline void			Draw(FPoint pPosition){Draw(pPosition.mX,pPosition.mY);}
	inline void			Draw(FPoint pPosition, float pScale, float pRotationDegrees=0){Draw(pPosition.mX,pPosition.mY,pScale,pRotationDegrees);}
    
    
    void                DrawRadial(float pCenterX, float pCenterY, float pStartRotation, float pEndRotation, float pCenterOffsetX=0, float pCenterOffsetY=0);
	
	
    //Used so far for fly swat rotating parts...
	void				DrawExtended(FPoint pOrigin, FPoint pTranslate, FPoint pCenter, float pRotationAboutOrigin, float pRotationAboutCenter, float pScale, bool pFlip=false);
    
    //For ninja game..
    void                DrawExtended(FPoint pPosition, FPoint pTranslate, float pScale, float pRotation, int pFlipMode);
    
    
	void				DrawStretchedH(float x, float y, float pWidth);
	void				DrawStretchedV(float x, float y, float pHeight);
	
	void				DrawFlippedH(float x, float y);
	void				DrawFlippedH(float x, float y, float pScale, float pRotationDegrees=0);
	inline void			DrawFlippedH(FPoint pPos){DrawFlippedH(pPos.mX,pPos.mY);}
	inline void			DrawFlippedH(FPoint pPos, float pScale, float pRotationDegrees=0){DrawFlippedH(pPos.mX,pPos.mY,pScale,pRotationDegrees);}
	
	void				DrawFlippedV(float x, float y);
	void				DrawFlippedV(float x, float y, float pScale, float pRotationDegrees=0);
	inline void			DrawFlippedV(FPoint pPos){DrawFlippedV(pPos.mX,pPos.mY);}
	inline void			DrawFlippedV(FPoint pPos, float pScale, float pRotationDegrees=0){DrawFlippedV(pPos.mX,pPos.mY,pScale,pRotationDegrees);}
	
	
	void				Center(float x, float y);
	void				Center(FPoint pPosition){Center(pPosition.mX,pPosition.mY);}
	
	void				Center(float x, float y, int pFacing);
	void				Center(FPoint pPosition, int pFacing){Center(pPosition.mX,pPosition.mY,pFacing);}
	
	
	void				CenterRotated(float x, float y, float pRotationDegrees);
	inline void			CenterRotated(FPoint pPos, float pRotationDegrees){CenterRotated(pPos.mX,pPos.mY,pRotationDegrees);}
    
    
    void                SetRect(float pWidth, float pHeight);
    void                SetRect(float pX, float pY, float pWidth, float pHeight);
	
	float                           mWidth, mHeight;
	
	float                           mCenterX, mCenterY;
	
	float                           mTextureCoord[8];
	float                           mTextureVertex[8];
	
	
	//float				mColorCoord[16];
	
	int                             mBindIndex;
	
    
    ImageBundlerLoadNode            *mBundlerNode;
	Image                           *mImage;
    
    FString                         mPath;
    
    
	inline float                    GetStartU(){return mTextureCoord[0];}
	inline float                    GetStartV(){return mTextureCoord[1];}
	inline float                    GetEndU(){return mTextureCoord[6];}
	inline float                    GetEndV(){return mTextureCoord[7];}
    
    inline float                    GetStartX(){return mTextureVertex[0];}
	inline float                    GetStartY(){return mTextureVertex[1];}
	inline float                    GetEndX(){return mTextureVertex[6];}
	inline float                    GetEndY(){return mTextureVertex[7];}
    
    
    void                            SetStartU(float pU){mTextureCoord[0]=pU;mTextureCoord[4]=pU;}
	void                            SetStartV(float pV){mTextureCoord[1]=pV;mTextureCoord[3]=pV;}
	void                            SetEndU(float pU){mTextureCoord[6]=pU;mTextureCoord[2]=pU;}
	void                            SetEndV(float pV){mTextureCoord[7]=pV;mTextureCoord[5]=pV;}
    
    void                            SetStartX(float pX){mTextureVertex[0]=pX;mTextureVertex[4]=pX;}
	void                            SetStartY(float pY){mTextureVertex[1]=pY;mTextureVertex[3]=pY;}
	void                            SetEndX(float pX){mTextureVertex[6]=pX;mTextureVertex[2]=pX;}
	void                            SetEndY(float pY){mTextureVertex[7]=pY;mTextureVertex[5]=pY;}
    
};


class SpriteStrip
{
	public:
	
	SpriteStrip();
	~SpriteStrip();
	
	void				Kill();
	void				Load(char *pFile, int pCount, bool pVertical=false);
	
	inline Sprite		&Fetch(int pIndex)
	{
		if(pIndex<0)pIndex=0;
		if(pIndex>=mSpriteCount)pIndex=mSpriteCount-1;
		//printf("Index: %d Cnt: %d Spr(%d,%d)\n",pIndex,mSpriteCount,mSprite[pIndex]->mWidth,mSprite[pIndex]->mHeight);
		return *mSprite[pIndex];
	
	}
	inline Sprite		&operator[](int pIndex){return Fetch(pIndex);}
	inline Sprite		&operator[](float pIndex){return Fetch((int)pIndex);}
	
	Sprite				**mSprite;
	int					mSpriteCount;
};

extern bool gSpriteIgnoreRetina;

#endif