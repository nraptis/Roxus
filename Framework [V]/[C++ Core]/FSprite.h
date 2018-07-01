#ifndef FSprite_H
#define FSprite_H

#include "FImage.h"
#include "FImageBundler.h"
#include "FTexture.h"
#include "FString.h"
#include "FVec2.h"

class FTexture;

class FSprite
{
public:
    
	FSprite();
	~FSprite();
    
	void                            Load(char *pName, FImageBundler *pBundler);
	inline void                     Load(const char *pFile, FImageBundler *pBundler){Load((char*)pFile,pBundler);}
    inline void                     Load(FString pFile, FImageBundler *pBundler){Load(pFile.c(),pBundler);}
    
	inline void                     Load(FString pFile){Load(pFile.c());}
	inline void                     Load(const char *pFile){Load((char*)pFile);}
	void                            Load(char *pFile);
    
    void                            LoadN(const char *pFileStart, int pIndex);
    void                            LoadN(const char *pFileStart, int pIndex, const char *pFileEnd);
    void                            LoadN(const char *pFileStart, int pIndex1, const char *pFileEnd, int pIndex2);
    void                            LoadN(const char *pFileStart, int pIndex1, const char *pFileMiddle, int pIndex2, const char *pFileEnd);
    
    void                            LoadNode(FImageBundler *pImageBundler, FImageBundlerLoadNode *pNode);
    
    void                            Load(FImage *pImage);
    void                            Load(FImage *pImage, int pX, int pY, int pWidth, int pHeight);
    
    void                            Load(FTexture *pTexture);
    void                            Load(FTexture *pTexture, int pX, int pY, int pWidth, int pHeight);

    bool                            DidLoad();
    
    void                            Clone(FSprite *pSprite);
    
    void                            SetTexture(FTexture *pTexture);
    FTexture                        *mTexture;
    
    
    bool                            mDidLoad;
    bool                            mDidLoadFromBundle;
    bool                            mDidLoadFromResource;
    bool                            mDidLoadSingle;
    
    
    
    //void                            SetupBackground(FImage *pImage, int pAppWidth, int pAppHeight, int pImageRectX, int pImageRectY, int pImageRectWidth, int pImageRectHeight);
    
    
    //void                            CalculateUV(int x, int y, int pWidth, int pHeight, int pImageWidth, int pImageHeight, bool pCentered=true, bool pRotate=false);
    
    //void                            StretchTo(FImage *pImage, int pNewWidth, int pNewHeight);
	
	//void                            Rotate90();
    
    //void                            Recenter(float pX, float pY);
    
	
	void                            Kill();
	
    
    /*
	void                            DrawPercentH(float pStartPercent, float pEndPercent);
	void                            DrawPercentH(float pEndPercent){DrawPercentH(0,pEndPercent);}
	
	void                            DrawPercentH(float x, float y, float pStartPercent, float pEndPercent);
	void                            DrawPercentH(float x, float y, float pEndPercent){DrawPercentH(x,y,0,pEndPercent);}
	
	void                            DrawPercentH(FVec2 pPos, float pStartPercent, float pEndPercent){DrawPercentH(pPos.mX,pPos.mY,pStartPercent,pEndPercent);}
	void                            DrawPercentH(FVec2 pPos, float pEndPercent){DrawPercentH(pPos.mX,pPos.mY,0,pEndPercent);}
	
	
	void                            DrawPercentV(float pStartPercent, float pEndPercent);
	void                            DrawPercentV(float pEndPercent){DrawPercentV(0,pEndPercent);}
	
	void                            DrawPercentV(float x, float y, float pStartPercent, float pEndPercent);
	void                            DrawPercentV(float x, float y, float pEndPercent){DrawPercentV(x,y,0,pEndPercent);}
	
	void                            DrawPercentV(FVec2 pPos, float pStartPercent, float pEndPercent){DrawPercentV(pPos.mX,pPos.mY,pStartPercent,pEndPercent);}
	void                            DrawPercentV(FVec2 pPos, float pEndPercent){DrawPercentV(pPos.mX,pPos.mY,0,pEndPercent);}
	*/
    
	
	void                            Draw();
	void                            Draw(float x, float y);
	void                            Draw(float pX, float pY, float pScale, float pRotation=0);
    void                            Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing);
	inline void                     Draw(FVec2 pPosition){Draw(pPosition.mX,pPosition.mY);}
	inline void                     Draw(FVec2 pPosition, float pScale, float pRotationDegrees=0){Draw(pPosition.mX,pPosition.mY,pScale,pRotationDegrees);}

    void                            DrawScaled(float pX, float pY, float pScale);
    void                            DrawScaled(float pX, float pY, float pScaleX, float pScaleY);
    
    void                            DrawScaled(float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    
    
    inline void                     DrawScaled(FVec2 pPosition, float pScale){DrawScaled(pPosition.mX,pPosition.mY, pScale);}
    inline void                     DrawScaled(FVec2 pPosition, float pScaleX, float pScaleY){DrawScaled(pPosition.mX,pPosition.mY, pScaleX, pScaleY);}
    
    void                            DrawRotated(float pX, float pY, float pRotation);
    inline void                     DrawRotated(FVec2 pPosition, float pRotation){DrawRotated(pPosition.mX,pPosition.mY, pRotation);}
    

    void                            DrawExtended(FVec2 pOrigin, FVec2 pTranslate, FVec2 pCenter, float pRotationAboutOrigin, float pRotationAboutCenter, float pScale, bool pFlip=false);
    void                            DrawExtended(FVec2 pPosition, FVec2 pTranslate, float pScale, float pRotation, int pFlipMode);

    void                            DrawAngleRange(float pX, float pY, float pScale, float pRotation, float pAngleStart, float pAngleEnd);

    void                            DrawTripletH(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength, bool pDrawLeft=true, bool pDrawMiddle=true, bool pDrawRight=true);
    
    void                            Draw9x9(float pX, float pY, float pWidth, float pHeight, float pScale, float pRotation, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft);

	void                            DrawStretchedH(float x, float y, float pWidth);
	void                            DrawStretchedV(float x, float y, float pHeight);
	
	void                            DrawFlippedH(float x, float y);
	void                            DrawFlippedH(float x, float y, float pScale, float pRotationDegrees=0);
	inline void                     DrawFlippedH(FVec2 pPos){DrawFlippedH(pPos.mX,pPos.mY);}
	inline void                     DrawFlippedH(FVec2 pPos, float pScale, float pRotationDegrees=0){DrawFlippedH(pPos.mX,pPos.mY,pScale,pRotationDegrees);}
	
	void                            DrawFlippedV(float x, float y);
	void                            DrawFlippedV(float x, float y, float pScale, float pRotationDegrees=0);
	inline void                     DrawFlippedV(FVec2 pPos){DrawFlippedV(pPos.mX,pPos.mY);}
	inline void                     DrawFlippedV(FVec2 pPos, float pScale, float pRotationDegrees=0){DrawFlippedV(pPos.mX,pPos.mY,pScale,pRotationDegrees);}
	
	
	void                            Center(float x, float y);
	void                            Center(FVec2 pPosition){Center(pPosition.mX,pPosition.mY);}
	
	void                            Center(float x, float y, int pFacing);
	void                            Center(FVec2 pPosition, int pFacing){Center(pPosition.mX,pPosition.mY,pFacing);}
    
    
    
    void                            DrawShiftedCorners(float x, float y, float pScale, float pRotationDegrees, FVec2 pShiftUL, FVec2 pShiftUR, FVec2 pShiftDL, FVec2 pShiftDR);
    
    
    void                            DrawSliceTo(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY);
    void                            DrawSlice(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY);
    
    void                            DrawSliceTo(float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY);
    void                            DrawSlice(float pStartX, float pStartY, float pEndX, float pEndY);

    void                            DrawQuad(float pX1, float pY1,
                                             float pX2, float pY2,
                                             float pX3, float pY3,
                                             float pX4, float pY4);
    
    void                            DrawQuad(float pLeft, float pTop,
                                             float pRight, float pBottom);
    
    void                            CenterQuad(float pCenterX, float pCenterY, float pLeft, float pTop,
                                             float pRight, float pBottom);

    void                            DrawQuadRect(float pX, float pY, float pWidth, float pHeight);
    void                            DrawQuadRectOffset(float pX, float pY, float pWidth, float pHeight, float pOffset);
    
    
	
	void                            CenterRotated(float x, float y, float pRotationDegrees);
	inline void                     CenterRotated(FVec2 pPos, float pRotationDegrees){CenterRotated(pPos.mX,pPos.mY,pRotationDegrees);}
    
    //void                            SetRect(float pWidth, float pHeight);
    //void                            SetRect(float pX, float pY, float pWidth, float pHeight);
    
    //void                            SetUVQuad(float pStartU, float pStartV, float pEndU, float pEndV);
    
    
    float                                   mWidth;
    float                                   mHeight;
	
	//float                           mCenterX, mCenterY;
    
    //int                             mOffsetX;
    //int                             mOffsetY;
	
	//float                           mTextureCoord[8];
	//float                           mVertex[8];
    FTextureRect                            mTextureRect;
    
    
    FString                                 mFileName;
    
    
    void                                    PrintQuadData();
    
    
    float                                   ScaleFitH(float pWidth);
    float                                   ScaleFitH(float pWidth, float pOffset);
    
    float                                   ScaleFitV(float pHeight);
    float                                   ScaleFitV(float pHeight, float pOffset);
    
    
    inline float                            GetStartU(){return mTextureRect.GetStartU();}
    inline float                            GetStartV(){return mTextureRect.GetStartV();}
    inline float                            GetEndU(){return mTextureRect.GetEndU();}
    inline float                            GetEndV(){return mTextureRect.GetEndV();}
    
    inline float                            GetStartX(){return mTextureRect.GetStartX();}
    inline float                            GetStartY(){return mTextureRect.GetStartY();}
    inline float                            GetEndX(){return mTextureRect.GetEndX();}
    inline float                            GetEndY(){return mTextureRect.GetEndY();}
    
	//inline float                    GetStartU(){return mTextureCoord[0];}
	//inline float                    GetStartV(){return mTextureCoord[1];}
	//inline float                    GetEndU(){return mTextureCoord[6];}
	//inline float                    GetEndV(){return mTextureCoord[7];}
    
    //inline float                    GetStartX(){return mVertex[0];}
	//inline float                    GetStartY(){return mVertex[1];}
	//inline float                    GetEndX(){return mVertex[6];}
	//inline float                    GetEndY(){return mVertex[7];}
    
    
    //void                            SetStartU(float pU){mTextureCoord[0]=pU;mTextureCoord[4]=pU;}
	//void                            SetStartV(float pV){mTextureCoord[1]=pV;mTextureCoord[3]=pV;}
	//void                            SetEndU(float pU){mTextureCoord[6]=pU;mTextureCoord[2]=pU;}
	//void                            SetEndV(float pV){mTextureCoord[7]=pV;mTextureCoord[5]=pV;}
    
    //void                            SetStartX(float pX){mVertex[0]=pX;mVertex[4]=pX;}
	//void                            SetStartY(float pY){mVertex[1]=pY;mVertex[3]=pY;}
	//void                            SetEndX(float pX){mVertex[6]=pX;mVertex[2]=pX;}
	//void                            SetEndY(float pY){mVertex[7]=pY;mVertex[5]=pY;}

    bool                            mAddToSpriteList;
};


extern bool gSpriteListEnabled;
extern FList gSpriteList;
extern FList gSpriteSequenceList;

#ifdef SETUP_MODE

extern int gTestSpriteIndex;
extern int gTestSpriteSequenceIndex;

#endif


#endif
