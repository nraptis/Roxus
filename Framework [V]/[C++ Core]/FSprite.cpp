#include "FApp.h"
#include "FSprite.h"
#include "FTexture.h"
#include "FVertexBuffer.h"
#include "FStringBuffer.h"
#include "core_includes.h"

bool gFSpriteIgnoreRetina=false;

bool gSpriteListEnabled = true;
FList gSpriteList;
FList gSpriteSequenceList;


#ifdef SETUP_MODE

int gTestSpriteIndex = 0;
int gTestSpriteSequenceIndex = 0;

#endif

FSprite::FSprite()
{
    //mBindIndex=-1;
    mTexture = 0;
    
    mWidth=0;
    mHeight=0;
    
    mAddToSpriteList = true;
    
    
    mDidLoad = false;
    mDidLoadFromBundle = false;
    mDidLoadFromResource = false;
    mDidLoadSingle = false;
    
    //mOffsetX = 0;
    //mOffsetY = 0;
    
    //mBundlerNode=0;
    
    //for(int i=0;i<16;i++)mColorCoord[i]=1.0f;
    //for(int i=0;i<8;i++)mTextureCoord[i]=0.0f;
    //for(int i=0;i<8;i++)mVertex[i]=0.0f;
    
    //mTextureCoord[2]=1;
    //mTextureCoord[5]=1;
    //mTextureCoord[6]=1;
    //mTextureCoord[7]=1;
    
    //mImage=0;
    //mInlineFImage=0;
}

FSprite::~FSprite()
{
    Kill();
    //delete mInlineFImage;
    //mInlineFImage=0;
}

void FSprite::Kill()
{
    SetTexture(0);
    
    mDidLoad = false;
    mDidLoadFromBundle = false;
    mDidLoadFromResource = false;
    mDidLoadSingle = false;
    
    mWidth = 0;
    mHeight = 0;
}

/*
 
 void FSprite::SetRect(float pWidth, float pHeight)
 {
 float aLeft = -(pWidth / 2.0f);
 float aRight = aLeft + pWidth;
 float aTop = -(pHeight / 2.0f);
 float aBottom = aTop + pHeight;
 
 mTextureRect.SetQuad(aLeft, aTop, aRight, aBottom);
 
 //mVertex[0]=aLeft;
 //mVertex[1]=aTop;
 //mVertex[2]=aRight;
 //mVertex[3]=aTop;
 //mVertex[4]=aLeft;
 //mVertex[5]=aBottom;
 //mVertex[6]=aRight;
 //mVertex[7]=aBottom;
 
 }
 
 void FSprite::SetRect(float pX, float pY, float pWidth, float pHeight)
 {
 float aLeft = pX;
 float aRight = aLeft + pWidth;
 float aTop = pY;
 float aBottom = aTop + pHeight;
 
 mTextureRect.SetQuad(aLeft, aTop, aRight, aBottom);
 
 //mVertex[0]=aLeft;
 //mVertex[1]=aTop;
 //mVertex[2]=aRight;
 //mVertex[3]=aTop;
 //mVertex[4]=aLeft;
 //mVertex[5]=aBottom;
 //mVertex[6]=aRight;
 //mVertex[7]=aBottom;
 
 }
 
 void FSprite::SetUVQuad(float pStartU, float pStartV, float pEndU, float pEndV)
 {
 SetStartU(pStartU);
 SetStartV(pStartV);
 SetEndU(pEndU);
 SetEndV(pEndV);
 }
 
 */

void FSprite::SetTexture(FTexture *pTexture)
{
    if(mTexture)
    {
        if(pTexture != mTexture)
        {
            if(gTextureCache.mAutoMode == true)gTextureCache.TextureBindRemove(mTexture);mTexture = 0;
        }
    }
    if(pTexture)
    {
        mTexture = pTexture;
        if(gTextureCache.mAutoMode == true)gTextureCache.TextureBindAdd(mTexture);
    }
    
    //SET_TEXTURE_BODY;
}

void FSprite::LoadNode(FImageBundler *pImageBundler, FImageBundlerLoadNode *pNode)
{
    if(mDidLoad)
    {
        Log("Preventing Double Load [__NODE__]\n");
        return;
    }
    
    Kill();
    
    if(pImageBundler == 0)return;
    if(pNode == 0)return;
    
    //Log("Gettin Bundle Fer [%s]\n", pImageBundler->mBundleName.c());
    FTexture *aTexture = gTextureCache.GetTexture(pImageBundler->mBundleName.c());
    
    if(aTexture == 0)return;
    
    bool aHoldRetinaResize = gFSpriteIgnoreRetina;
    gFSpriteIgnoreRetina = true;
    
    SetTexture(aTexture);
    
    float aStartU,aStartV,aEndU,aEndV;
    float aLeft, aTop, aRight, aBottom;
    
    //float aOffsetX, aOffsetY;
    //aOffsetX = pNode->mOffsetX;
    //aOffsetY = pNode->mOffsetY;
    
    aStartU = pNode->mSpriteUStart;
    aStartV = pNode->mSpriteVStart;
    
    aEndU = pNode->mSpriteUEnd;
    aEndV = pNode->mSpriteVEnd;
    
    aLeft = pNode->mSpriteLeft * pImageBundler->mBundleScale;
    aRight = pNode->mSpriteRight * pImageBundler->mBundleScale;
    
    aTop = pNode->mSpriteTop * pImageBundler->mBundleScale;
    aBottom = pNode->mSpriteBottom * pImageBundler->mBundleScale;
    
    //mWidth = pNode->mSpriteWidth;
    //mHeight = pNode->mSpriteHeight;
    
    mWidth = pNode->mOriginalWidth * pImageBundler->mBundleScale;
    mHeight = pNode->mOriginalHeight * pImageBundler->mBundleScale;
    
    mTextureRect.SetQuad(aLeft, aTop, aRight, aBottom);
    mTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    
    //Log("Pulled [%s] From Bundle [%f x %f]\n", pImageBundler->mBundleName.c(), mWidth, mHeight);
    
    mDidLoad = true;
    mDidLoadFromBundle = true;
    mDidLoadSingle = false;
    
}

FStringBuffer cSpriteLoadBuffer;

void FSprite::Load(char *pName, FImageBundler *pBundler)
{
    if(mDidLoad)
    {
        Log("Preventing Double Load [%s]\n", pName);
        return;
    }
    
    Kill();
    
    if(!pBundler)return;
    if(pBundler->mDidLoad == false)return;
    
    FImageBundlerLoadNode *aNode = pBundler->FetchNode(pName);
    //FImage *aImage = &pBundler->mImage;
    FTexture *aTexture = gTextureCache.GetTexture(pBundler->mBundleName.c());
    
    bool aHoldRetinaResize = gFSpriteIgnoreRetina;
    gFSpriteIgnoreRetina = true;
    
    
    if((aNode != 0) && (aTexture != 0))
    {
        LoadNode(pBundler, aNode);
    }
    
    gFSpriteIgnoreRetina = aHoldRetinaResize;
}

void FSprite::Load(char *pFile)
{
    if(mDidLoad)
    {
        Log("Preventing Double Load [%s]\n", pFile);
        return;
    }
    
    Kill();
    
    mFileName = pFile;
    mFileName.RemovePath();
    mFileName.RemoveExtension();
    
    
    if(gImageBundler.mAutoBundle)
    {
        if(gImageBundler.mBundleName.mLength > 0)
        {
            FImage aImage;
            aImage.Load(pFile);
            gImageBundler.AddImage(&aImage);
        }
    }
    
    Load(pFile, &gImageBundler);
    
    if(mWidth > 0 && mHeight > 0)
    {
        mDidLoad = true;
        mDidLoadFromBundle = true;
        mDidLoadSingle = false;
        
        if(gSpriteListEnabled == true)
        {
            gSpriteList.Add(this);
        }
        
        return;
    }
    
    Load(gTextureCache.GetTexture(mFileName.c()));
    
    
    if(mWidth > 0 && mHeight > 0)
    {
        mDidLoad = true;
        mDidLoadFromBundle = false;
        mDidLoadSingle = true;
        
        if(gSpriteListEnabled == true)
        {
            gSpriteList.Add(this);
        }
    }
    
}

/*
 void FSprite::Load(const char *pFileStart, int pIndex, const char *pFileEnd)
 {
 FString aPath = FString(pFileStart) + FString(pIndex) + FString(pFileEnd);
 Load(aPath.c());
 }
 */


void FSprite::LoadN(const char *pFileStart, int pIndex)
{
    //int aWriteIndex = 0;
    
    Load(FString(pFileStart) + FString(pIndex));
    
    //cSpriteLoadBuffer.W
    //cSpriteLoadBuffer.Write(<#const char *pString#>, <#int pIndex#>, <#int pCount#>)
}

void FSprite::LoadN(const char *pFileStart, int pIndex, const char *pFileEnd)
{
    Load(FString(pFileStart) + FString(pIndex) + FString(pFileEnd));
    
    
}

void FSprite::LoadN(const char *pFileStart, int pIndex1, const char *pFileEnd, int pIndex2)
{
    Load(FString(pFileStart) + FString(pIndex1) + FString(pFileEnd) + FString(pIndex2));
    
}

void FSprite::LoadN(const char *pFileStart, int pIndex1, const char *pFileMiddle, int pIndex2, const char *pFileEnd)
{
    Load(FString(pFileStart) + FString(pIndex1) + FString(pFileMiddle) + FString(pIndex2) + FString(pFileEnd));
}


void FSprite::Load(FImage *pImage)
{
    if(pImage)
    {
        Load(pImage, pImage->mOffsetX, pImage->mOffsetY, pImage->mWidth, pImage->mHeight);
        //Load(pImage, 0, 0, pImage->mWidth, pImage->mHeight);
    }
}

//void FSprite::Load(FImage *pImage, int x, int y, int pWidth, int pHeight)
void FSprite::Load(FImage *pImage, int pX, int pY, int pWidth, int pHeight)

{
    //Log("FImage Loading ( %x %d %d %d %d )\n", pImage, x, y, pWidth, pHeight);
    //TODO: Why was this commented before?
    Kill();
    
    if(!pImage)return;
    if((pImage->mWidth <= 0) || (pImage->mHeight <=0 ))return;
    
    Load(pImage->GetTexture(), pX, pY, pWidth, pHeight);
}

void FSprite::Load(FTexture *pTexture)
{
    if(pTexture)
    {
        Load(pTexture, pTexture->mOffsetX, pTexture->mOffsetY, pTexture->mWidth, pTexture->mHeight);
    }
}

void FSprite::Load(FTexture *pTexture, int pX, int pY, int pWidth, int pHeight)
{
    if(mDidLoad)
    {
        Log("Preventing Double Load [_TEXTURE_RECT]\n");
        return;
    }
    
    Kill();
    
    if(pTexture)
    {
        if((pTexture->mExpandedWidth > 0) && (pTexture->mExpandedHeight > 0))
        {
            SetTexture(pTexture);
            
            mWidth = pWidth;
            mHeight = pHeight;
            
            float aStartU = (float)pX / (float)pTexture->mExpandedWidth;
            float aStartV = (float)pY / (float)pTexture->mExpandedHeight;
            float aEndU = (float)(pX + pWidth) / (float)pTexture->mExpandedWidth;
            float aEndV = (float)(pY + pHeight) / (float)pTexture->mExpandedHeight;
            
            
            mTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
            
            float aHeight2 = ((float)mHeight)/2.0f;
            float aWidth2 = ((float)mWidth)/2.0f;
            
            mTextureRect.SetQuad(-aWidth2, -aHeight2, aWidth2, aHeight2);
        }
    }
}

void FSprite::Clone(FSprite *pSprite)
{
    
}

bool FSprite::DidLoad()
{
    bool aResult = true;
    
    if(mTexture == 0)aResult = false;
    if((mWidth <= 0.0f) || (mHeight <= 0.0f))aResult = false;
    
    return aResult;
}

float FSprite::ScaleFitH(float pWidth)
{
    float aResult = 1.0f;
    
    if(mWidth > 0.0f)
    {
        if(pWidth >= 0.25f)
        {
            aResult = pWidth / mWidth;
        }
    }
    
    return aResult;
}

float FSprite::ScaleFitV(float pHeight)
{
    float aResult = 1.0f;
    
    if(mHeight > 0.0f)
    {
        if(pHeight >= 0.25f)
        {
            aResult = pHeight / mHeight;
        }
    }
    
    return aResult;
}

float FSprite::ScaleFitH(float pWidth, float pOffset)
{
    return ScaleFitH(pWidth - pOffset);
}

float FSprite::ScaleFitV(float pHeight, float pOffset)
{
    return ScaleFitV(pHeight - pOffset);
}


void FSprite::Center(float x, float y)
{
    Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::Draw(float x, float y)
{
    Graphics::DrawSprite(x + mWidth/2.0f, y + mHeight/2.0f, 1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawStretchedV(float x, float y, float pHeight)
{
    /*
     
     mVertex[0]=0;
     mVertex[1]=0;
     mVertex[2]=mWidth;
     mVertex[3]=0;
     mVertex[4]=0;
     mVertex[5]=pHeight;
     mVertex[6]=mWidth;
     mVertex[7]=pHeight;
     
     Graphics::MatrixPush();
     Graphics::Translate(x,y);
     Draw();
     Graphics::MatrixPop();
     */
    
}


void FSprite::DrawStretchedH(float x, float y, float pWidth)
{
    /*
     
     mVertex[0]=0;
     mVertex[1]=0;
     mVertex[2]=pWidth;
     mVertex[3]=0;
     mVertex[4]=0;
     mVertex[5]=mHeight;
     mVertex[6]=pWidth;
     mVertex[7]=mHeight;
     
     Graphics::MatrixPush();
     Graphics::Translate(x,y);
     Draw();
     Graphics::MatrixPop();
     */
    
}

void FSprite::DrawExtended(FVec2 pPosition, FVec2 pTranslate, float pScale, float pRotation, int pFlipMode)
{
    Graphics::MatrixPush();
    Graphics::Translate(pPosition);
    
    if(pFlipMode == -1)
    {
        Graphics::Scale(-pScale, pScale, pScale);
    }
    else
    {
        Graphics::Scale(pScale, pScale, pScale);
    }
    
    Graphics::Translate(pTranslate);
    Graphics::Rotate(pRotation);
    
    Draw();
    Graphics::MatrixPop();
}

/*
 void FSprite::DrawExtended(FVec2 pOrigin, FVec2 pTranslate, FVec2 pCenter, float pRotationAboutOrigin, float pRotationAboutCenter, float pScale, bool pFlip)
 {
 Graphics::MatrixPush();
	Graphics::Translate(pOrigin);
	Graphics::Rotate(pRotationAboutOrigin);
	
	if(pFlip)
	{
 Graphics::Scale(-pScale, pScale, pScale);
	}
	else
	{
 Graphics::Scale(pScale, pScale, pScale);
	}
	
	Graphics::Translate(pTranslate);
	Graphics::Rotate(pRotationAboutCenter);
	
	FVec2 aCenter=FVec2(mVertex[6],mVertex[7]);
	FVec2 aShift=aCenter-pCenter;
 
	Graphics::Translate(aShift);
 
	Draw();
 Graphics::MatrixPop();
 }
 */

void FSprite::CenterRotated(float x, float y, float pRotationDegrees)
{
    Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, pRotationDegrees, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::Draw(float x, float y, float pScale, float pRotationDegrees)
{
    Graphics::DrawSprite(x, y, pScale, pScale, 1.0f, pRotationDegrees, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing)
{
    if(pFacing < 1)DrawFlippedH(x, y, pScale, pRotationDegrees);
    else Draw(x, y, pScale, pRotationDegrees);
}

void FSprite::Center(float x, float y, int pFacing)
{
    Graphics::DrawSprite(x, y, pFacing<0 ? (-1.f) : (1.0f) , 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawFlippedH(float x, float y)
{
    Graphics::DrawSprite(x + mWidth/2.0f, y + mHeight/2.0f, -1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawFlippedH(float x, float y, float pScale, float pRotationDegrees)
{
    Graphics::DrawSprite(x, y, -pScale, pScale, 1.0f, pRotationDegrees, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawFlippedV(float x, float y)
{
    
}

void FSprite::DrawFlippedV(float x, float y, float pScale, float pRotationDegrees)
{
    
}

FTextureRect cSliceTextureRect;

void FSprite::DrawQuad(float pX1, float pY1,
                       float pX2, float pY2,
                       float pX3, float pY3,
                       float pX4, float pY4)
{
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    cSliceTextureRect.SetQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4);
    
    Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawQuad(float pLeft, float pTop,
                       float pRight, float pBottom)
{
    DrawQuad(pLeft, pTop, pRight, pTop, pLeft, pBottom, pRight, pBottom);
}

void FSprite::CenterQuad(float pCenterX, float pCenterY, float pLeft, float pTop,
                       float pRight, float pBottom)
{
    float aWidth2 = (pRight - pLeft) * 0.5f;
    float aHeight2 = (pBottom - pTop) * 0.5f;
    
    
    DrawQuad(pCenterX - aWidth2, pCenterY - aHeight2, pCenterX + aWidth2, pCenterY + aHeight2);
}



void FSprite::DrawQuadRect(float pX, float pY, float pWidth, float pHeight)
{
    float aX1 = pX;
    float aX2 = pX + pWidth;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + pHeight;
    float aY4 = aY3;
    
    DrawQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    
}

void FSprite::DrawQuadRectOffset(float pX, float pY, float pWidth, float pHeight, float pOffset)
{
    float aOffset2 = pOffset * 2.0f;
    DrawQuadRect(pX - pOffset, pY - pOffset, pWidth + aOffset2, pHeight + aOffset2);
}

void FSprite::DrawTripletH(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength, bool pDrawLeft, bool pDrawMiddle, bool pDrawRight)
{
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aLengthCenter = (pLength - (pInsetLeft + pInsetRight));
    
    float aTripletLeftX = pX;
    float aTripletCenterX1 = pX + pInsetLeft;
    float aTripletCenterX2 = aTripletCenterX1 + aLengthCenter;
    float aTripletRightX = pX + pLength;
    
    float aTripletCenterU1 = aStartU;
    float aTripletCenterU2 = aEndU;
    //float aTripletRightU = aEndU;
    
    if(mWidth > 0.0f)
    {
        //aTripletLeftU = 0.0f;
        aTripletCenterU1 = pInsetLeft / mWidth;
        aTripletCenterU2 = (mWidth - pInsetRight) / mWidth;
        //aTripletRightU
        
        aTripletCenterU1 = (aStartU + ((aEndU - aStartU) * aTripletCenterU1));
        aTripletCenterU2 = (aStartU + ((aEndU - aStartU) * aTripletCenterU2));
    }
    
    
    float aX1 = aTripletLeftX;
    float aX2 = aTripletCenterX1;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + mHeight;
    float aY4 = aY3;
    
    if(pDrawLeft)
    {
        cSliceTextureRect.SetUVQuad(aStartU, aStartV, aTripletCenterU1, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
    }
    
    aX1 = aTripletCenterX1;
    aX2 = aTripletCenterX2;
    aX3 = aX1;
    aX4 = aX2;
    
    if(pDrawMiddle)
    {
        cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU2, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
    }
    
    aX1 = aTripletCenterX2;
    aX2 = aTripletRightX;
    aX3 = aX1;
    aX4 = aX2;
    
    if(pDrawRight)
    {
        cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aEndU, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
    }
}

void FSprite::Draw9x9(float pX, float pY, float pWidth, float pHeight, float pScale, float pRotation, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft)
{
    if(mWidth < 1.0)return;
    if(mHeight < 1.0)return;
    
    float aX[4];
    float aY[4];
    float aU[4];
    float aV[4];
    
    float aWidth = pWidth * pScale;
    float aHeight = pHeight * pScale;
    
    float aQuadInsetLeft = pInsetLeft * pScale;
    float aQuadInsetRight = pInsetRight * pScale;
    float aQuadInsetTop = pInsetTop * pScale;
    float aQuadInsetBottom = pInsetBottom * pScale;
    
    float aQuadRight = pX + aWidth;
    float aQuadBottom = pY + aHeight;
    
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aSpanU = (aEndU - aStartU);
    float aSpanV = (aEndV - aStartV);
    
    aX[0] = pX;
    aX[1] = pX + aQuadInsetLeft;
    aX[3] = aQuadRight;
    aX[2] = (aQuadRight - aQuadInsetRight);
    
    aY[0] = pY;
    aY[1] = pY + aQuadInsetLeft;
    aY[3] = aQuadBottom;
    aY[2] = (aQuadBottom - aQuadInsetBottom);
    
    aU[0] = aStartU;
    aU[3] = aEndU;
    aV[0] = aStartV;
    aV[3] = aEndV;
    
    aU[1] = (pInsetLeft / mWidth);
    aU[2] = ((mWidth - pInsetRight) / mWidth);
    aV[1] = (pInsetTop / mHeight);
    aV[2] = ((mHeight - pInsetBottom) / mHeight);
    
    
    aU[1] = (aU[1] * aSpanU) + aStartU;
    aU[2] = (aU[2] * aSpanU) + aStartU;
    aV[1] = (aV[1] * aSpanV) + aStartV;
    aV[2] = (aV[2] * aSpanV) + aStartV;
    
    
    for(int i=1;i<4;i++)
    {
        for(int n=1;n<4;n++)
        {
            cSliceTextureRect.SetUVQuad(aU[i - 1], aV[n - 1], aU[i], aV[n]);
            cSliceTextureRect.SetQuad(aX[i - 1], aY[n - 1], aX[i], aY[n]);
            Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
        }
    }
}

void FSprite::DrawShiftedCorners(float x, float y, float pScale, float pRotationDegrees, FVec2 pShiftUL, FVec2 pShiftUR, FVec2 pShiftDL, FVec2 pShiftDR)
{
    
    float aX1 = mTextureRect.GetStartX();
    float aX2 = mTextureRect.GetEndX();
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = mTextureRect.GetStartY();
    float aY2 = aY1;
    float aY3 = mTextureRect.GetEndY();
    float aY4 = aY3;
    
    
    aX1 += pShiftUL.mX;
    aY1 += pShiftUL.mY;
    
    aX2 += pShiftUR.mX;
    aY2 += pShiftUR.mY;
    
    aX3 += pShiftDL.mX;
    aY3 += pShiftDL.mY;
    
    aX4 += pShiftDR.mX;
    aY4 += pShiftDR.mY;
    
    
    
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    //cSliceTextureRect.SetQuad(aX1 + pShiftUL.mX, aY1 + pShiftUL.mY, aX2 + pShiftUR.mX, aY2 + pShiftUR.mY, aX3, aY3, aX4, aY4);
    
    
    
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    
    Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, pRotationDegrees, cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawSliceTo(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY)
{
    if((mWidth > 0.0f) && (mHeight > 0.0f) && (pTextureRect != 0))
    {
        
        float aBaseStartU = mTextureRect.GetStartU();
        float aBaseStartV = mTextureRect.GetStartV();
        
        float aBaseEndU = mTextureRect.GetEndU();
        float aBaseEndV = mTextureRect.GetEndV();
        
        float aBaseRangeU = aBaseEndU - aBaseStartU;
        float aBaseRangeV = aBaseEndV - aBaseStartV;
        
        float aStartU = pStartX / mWidth;
        float aEndU = pEndX / mWidth;
        
        float aStartV = pStartY / mHeight;
        float aEndV = pEndY / mHeight;
        
        aStartU = aBaseStartU + aBaseRangeU * aStartU;
        aEndU = aBaseStartU + aBaseRangeU * aEndU;
        
        aStartV = aBaseStartV + aBaseRangeV * aStartV;
        aEndV = aBaseStartV + aBaseRangeV * aEndV;
        
        
        pTextureRect->SetQuad(pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
        pTextureRect->SetUVQuad(aStartU, aStartV, aEndU, aEndV);
        
        Graphics::DrawSprite(pTextureRect->mVertex, pTextureRect->mTextureCoord, mTexture);
        
        //Graphics::DrawSprite(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, pTextureRect->mVertex, pTextureRect->mTextureCoord, mTexture);
        
    }
}


void FSprite::DrawAngleRange(float pX, float pY, float pScale, float pRotation, float pStartRotation, float pEndRotation)
{
    float aAngleDiff = (pEndRotation - pStartRotation);
    
    if(aAngleDiff <= 0.0f)
    {
        return;
    }
    
    if(aAngleDiff >= 360.0f)
    {
        Draw(pX, pY, pScale, pRotation);
        return;
    }
    
    if(pStartRotation < 0 || pStartRotation >= 360.0f)
    {
        pStartRotation = fmodf(pStartRotation, 360.0f);
        if(pStartRotation < 0)pStartRotation += 360.0f;
    }
    if(pEndRotation < 0 || pEndRotation >= 360.0f)
    {
        pEndRotation = fmodf(pEndRotation, 360.0f);
        if(pEndRotation < 0)pEndRotation += 360.0f;
    }
    
    float aStartU = GetStartU();
    float aStartV = GetStartV();
    
    float aEndU = GetEndU();
    float aEndV = GetEndV();
    
    float aStartX = GetStartX();
    float aStartY = GetStartY();
    
    float aEndX = GetEndX();
    float aEndY = GetEndY();
    
    float aX[4] = {aStartX, aEndX, aEndX, aStartX};
    float aY[4] = {aStartY, aStartY, aEndY, aEndY};
    
    float aURange = (aEndU - aStartU);
    float aVRange = (aEndV - aStartV);
    
    float aXRange = (aEndX - aStartX);
    float aYRange = (aEndY - aStartY);
    
    float aCenterU = aStartU + aURange * 0.5f;
    float aCenterV = aStartV + aVRange * 0.5f;
    
    float aLineStartX, aLineStartY, aLineEndX, aLineEndY;
    
    float aLineDirX, aLineDirY;
    float aLineNormX, aLineNormY;
    
    float aPlaneLength;
    
    float aDirX1 = Sin(pStartRotation);
    float aDirY1 = -Cos(pStartRotation);
    
    float aDirX2 = Sin(pEndRotation);
    float aDirY2 = -Cos(pEndRotation);
    
    float aCheckLength1, aCheckLength2;
    
    int aHitLine1 = -1;
    int aHitLine2 = -1;
    
    float aBestLength1 = 9999000000000.0f;
    float aBestLength2 = 9999000000000.0f;
    
    float aNumer, aDenom;
    
    int aStart = 3;
    int aEnd = 0;
    while(aEnd < 4)
    {
        aLineStartX = aX[aStart];
        aLineStartY = aY[aStart];
        
        aLineEndX = aX[aEnd];
        aLineEndY = aY[aEnd];
        
        aLineDirX = (aLineEndX - aLineStartX);
        aLineDirY = (aLineEndY - aLineStartY);
        
        aLineNormX = (-aLineDirY);
        aLineNormY = aLineDirX;
        
        aPlaneLength = (aLineDirX * aLineDirX) + (aLineDirY * aLineDirY);
        
        if(aPlaneLength > 0.01f)
        {
            aPlaneLength = sqrtf(aPlaneLength);
            
            aLineDirX /= aPlaneLength;
            aLineDirY /= aPlaneLength;
        }
        
        aNumer = (-(aLineNormX * aLineStartX + aLineNormY * aLineStartY));
        aDenom = (aDirX1 * aLineNormX + aDirY1 * aLineNormY);
        aCheckLength1 = -(aNumer / aDenom);
        
        //return
        
        if(aCheckLength1 > 0)
        {
            if(aCheckLength1 < aBestLength1)
            {
                aBestLength1 = aCheckLength1;
                aHitLine1 = aStart;
            }
        }
        
        aDenom = (aDirX2 * aLineNormX + aDirY2 * aLineNormY);
        aCheckLength2 = -(aNumer / aDenom);
        
        if(aCheckLength2 > 0)
        {
            if(aCheckLength2 < aBestLength2)
            {
                aBestLength2 = aCheckLength2;
                aHitLine2 = aStart;
            }
        }
        
        aStart = aEnd;
        aEnd++;
    }
    
    if((aHitLine1 == -1) || (aHitLine2 == -1)) { return; }
    
    float aEdgeX1 = aDirX1 * aBestLength1;
    float aEdgeY1 = aDirY1 * aBestLength1;
    
    float aEdgeX2 = aDirX2 * aBestLength2;
    float aEdgeY2 = aDirY2 * aBestLength2;
    
    float aEdgeU1 = aStartU + ((aEdgeX1 - aStartX) / aXRange) * aURange;
    float aEdgeV1 = aStartV + ((aEdgeY1 - aStartY) / aYRange) * aVRange;
    float aEdgeU2 = aStartU + ((aEdgeX2 - aStartX) / aXRange) * aURange;
    float aEdgeV2 = aStartV + ((aEdgeY2 - aStartY) / aYRange) * aVRange;
    
    float aOctantX[8] = {0.0f, aEndX, aEndX, aEndX, 0.0f, aStartX, aStartX, aStartX};
    float aOctantY[8] = {aStartY, aStartY, 0.0f, aEndY, aEndY, aEndY, 0.0f, aStartY};
    float aOctantU[8] = {aCenterU,aEndU,aEndU,aEndU,aCenterU,aStartU, aStartU, aStartU};
    float aOctantV[8] = {aStartV, aStartV, aCenterV, aEndV, aEndV, aEndV, aCenterV, aStartV};
    bool aOctantDraw[8] = {false, false, false, false, false, false, false, false};
    
    aOctantDraw[0] = false;aOctantDraw[1] = false;aOctantDraw[2] = false;aOctantDraw[3] = false;aOctantDraw[4] = false;aOctantDraw[5] = false;aOctantDraw[6] = false;aOctantDraw[7] = false;
    
    int aOctantStart = 7;
    int aOctantEnd = 7;
    
    if(aHitLine1 == 0)
    {
        if(aEdgeX1 >= 0)aOctantStart = 0;
        else aOctantStart = 7;
    }
    
    if(aHitLine1 == 1)
    {
        if(aEdgeY1 <= 0)aOctantStart = 1;
        else aOctantStart = 2;
    }
    
    if(aHitLine1 == 2)
    {
        if(aEdgeX1 > 0)aOctantStart = 3;
        else aOctantStart = 4;
    }
    
    if(aHitLine1 == 3)
    {
        if(aEdgeY1 < 0)aOctantStart = 6;
        else aOctantStart = 5;
    }
    
    if(aHitLine2 == 0)
    {
        if(aEdgeX2 >= 0)aOctantEnd = 0;
        else aOctantEnd = 7;
    }
    
    if(aHitLine2 == 1)
    {
        if(aEdgeY2 <= 0)aOctantEnd = 1;
        else aOctantEnd = 2;
    }
    
    if(aHitLine2 == 2)
    {
        if(aEdgeX2 > 0)aOctantEnd = 3;
        else aOctantEnd = 4;
    }
    
    if(aHitLine2 == 3)
    {
        if(aEdgeY2 < 0)aOctantEnd = 6;
        else aOctantEnd = 5;
    }
    
    FTextureTriangle aTriangle;
    
    if(aOctantStart == aOctantEnd)
    {
        if(pEndRotation < pStartRotation)
        {
            int aDrawOctant1 = aOctantStart;
            int aDrawOctant2 = aDrawOctant1 + 1;
            if(aDrawOctant2 == 8)aDrawOctant2 = 0;
            
            aTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aOctantX[aDrawOctant2], aOctantY[aDrawOctant2]);
            aTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aOctantU[aDrawOctant2], aOctantV[aDrawOctant2]);
            Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTriangle.mVertex, aTriangle.mTextureCoord, mTexture);
            
            
            aDrawOctant1 = aOctantEnd;
            aTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aDrawOctant1], aOctantY[aDrawOctant1], aEdgeX2, aEdgeY2);
            aTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aDrawOctant1], aOctantV[aDrawOctant1], aEdgeU2, aEdgeV2);
            Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTriangle.mVertex, aTriangle.mTextureCoord, mTexture);
            
            
            for(int i=0;i<8;i++)
            {
                if(i != aOctantStart)
                {
                    aOctantDraw[i] = true;
                }
            }
        } else {
            aTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aEdgeX2, aEdgeY2);
            aTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aEdgeU2, aEdgeV2);
            Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTriangle.mVertex, aTriangle.mTextureCoord, mTexture);
        }
    }
    else
    {
        int aDrawOctant1 = aOctantStart;
        int aDrawOctant2 = aDrawOctant1 + 1;
        if(aDrawOctant2 == 8)aDrawOctant2 = 0;
        
        aTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aOctantX[aDrawOctant2], aOctantY[aDrawOctant2]);
        aTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aOctantU[aDrawOctant2], aOctantV[aDrawOctant2]);
        Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTriangle.mVertex, aTriangle.mTextureCoord, mTexture);
        
        
        aDrawOctant1 = aOctantEnd;
        aTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aDrawOctant1], aOctantY[aDrawOctant1], aEdgeX2, aEdgeY2);
        aTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aDrawOctant1], aOctantV[aDrawOctant1], aEdgeU2, aEdgeV2);
        Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTriangle.mVertex, aTriangle.mTextureCoord, mTexture);
        
        
        int aOctant = aOctantStart;
        
        for(int i=0;i<8;i++)
        {
            aOctant++;
            if(aOctant == 8)aOctant = 0;
            if(aOctant == aOctantEnd)break;
            aOctantDraw[aOctant] = true;
        }
        
    }
    
    
    
    for(int aOctant=0;aOctant<8;aOctant++)
    {
        if(aOctantDraw[aOctant])
        {
            int aOctant2 = aOctant + 1;
            if(aOctant2 == 8)aOctant2 = 0;
            
            aTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aOctant], aOctantY[aOctant], aOctantX[aOctant2], aOctantY[aOctant2]);
            aTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aOctant], aOctantV[aOctant], aOctantU[aOctant2], aOctantV[aOctant2]);
            Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTriangle.mVertex, aTriangle.mTextureCoord, mTexture);
        }
    }
}

/*
 void FSprite::DrawAngleRange(float pX, float pY, float pScale, float pRotation, float pAngleStart, float pAngleEnd)
 {
 
 if(pAngleStart > pAngleEnd)
 {
 float aHold = pAngleStart;
 pAngleStart = pAngleEnd;
 pAngleEnd = aHold;
 }
 
 if(pAngleStart < 0.0f)pAngleStart += 360.0f;
 if(pAngleStart > 360.0f)pAngleStart -= 360.0f;
 
 if(pAngleEnd < 0.0f)pAngleEnd += 360.0f;
 if(pAngleEnd > 360.0f)pAngleEnd -= 360.0f;
 
 if((pAngleStart < 0) || (pAngleStart >= 360.0f))
 {
 pAngleStart = fmodf(pAngleStart, 360.0f);
 if(pAngleStart < 0)pAngleStart += 360.0f;
 }
 
 if((pAngleEnd < 0.0f) || (pAngleEnd > 360.0f))
 {
 pAngleEnd = fmodf(pAngleEnd, 360.0f);
 if(pAngleEnd < 0)pAngleEnd += 360.0f;
 }
 
 if(pAngleStart > pAngleEnd)
 {
 float aHold = pAngleStart;
 pAngleStart = pAngleEnd;
 pAngleEnd = aHold;
 }
 
 
 
 
 float aX[8];
 float aY[8];
 
 float aU[8];
 float aV[8];
 
 float aAngle[8];
 
 float aCheckDirX[8];
 float aCheckDirY[8];
 
 float aStartX = mTextureRect.GetStartX();
 float aStartY = mTextureRect.GetStartY();
 
 float aEndX = mTextureRect.GetEndX();
 float aEndY = mTextureRect.GetEndY();
 
 float aStartU = mTextureRect.GetStartU();
 float aStartV = mTextureRect.GetStartV();
 
 float aEndU = mTextureRect.GetEndU();
 float aEndV = mTextureRect.GetEndV();
 
 float aRangeX = (aEndX - aStartX);
 float aRangeY = (aEndY - aStartY);
 
 float aRangeU = (aEndU - aStartU);
 float aRangeV = (aEndV - aStartV);
 
 //Basically we'll assume 0, 0 is the center?
 //Bah, it's just gonna work with squares for now..
 float aCenterU = aStartU + aRangeU / 2.0f;
 float aCenterV = aStartV + aRangeV / 2.0f;
 
 float aCenterX = aStartX + aRangeX / 2.0f;
 float aCenterY = aStartY + aRangeY / 2.0f;
 
 aX[0] = aCenterX;
 aY[0] = aStartY;
 
 aX[1] = aEndX;
 aY[1] = aStartY;
 aX[2] = aEndX;
 
 aY[2] = aCenterY;
 aX[3] = aEndX;
 aY[3] = aEndY;
 
 aX[4] = aCenterX;
 aY[4] = aEndY;
 
 aX[5] = aStartX;
 aY[5] = aEndY;
 
 aX[6] = aStartX;
 aY[6] = aCenterY;
 
 aX[7] = aStartX;
 aY[7] = aStartY;
 
 aU[0] = aCenterU;
 aV[0] = aStartV;
 
 aU[1] = aEndU;
 aV[1] = aStartV;
 
 aU[2] = aEndU;
 aV[2] = aCenterV;
 
 aU[3] = aEndU;
 aV[3] = aEndV;
 
 aU[4] = aCenterU;
 aV[4] = aEndV;
 
 aU[5] = aStartU;
 aV[5] = aEndV;
 
 aU[6] = aStartU;
 aV[6] = aCenterV;
 
 aU[7] = aStartU;
 aV[7] = aStartV;
 
 
 
 
 Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.25f);
 
 Graphics::DrawLine(pX + Sin(pAngleStart) * 200.0f, pY - Cos(pAngleStart) * 200.0f, pX, pY);
 Graphics::DrawLine(pX + Sin(pAngleEnd) * 200.0f, pY - Cos(pAngleEnd) * 200.0f, pX, pY);
 
 
 
 
 int aStartIndex1 = 7;
 int aStartIndex2 = 7;
 int aEndIndex1 = 0;
 int aEndIndex2 = 0;
 
 float aAngleRangeStart1 = 315.0f;
 float aAngleRangeEnd1 = 360.0f;
 
 float aAngleRangeStart2 = 315.0f;
 float aAngleRangeEnd2 = 360.0f;
 
 aAngle[0] = 0.0f;
 aAngle[1] = 45.0f;
 aAngle[2] = 90.0f;
 aAngle[3] = 135.0f;
 aAngle[4] = 180.0f;
 aAngle[5] = 225.0f;
 aAngle[6] = 270.0f;
 aAngle[7] = 315.0f;
 
 float aCheckRangeStart = 0.0f;
 float aCheckRangeEnd = 0.0f;
 
 int aCheckIndex = 0;
 
 for(int aAngleIndex = 0;aAngleIndex<7;aAngleIndex++)
 {
 aCheckRangeStart = aAngle[aAngleIndex];
 aCheckRangeEnd = aAngle[aAngleIndex + 1];
 
 if((pAngleStart >= aCheckRangeStart) && (pAngleStart < aCheckRangeEnd))
 {
 aStartIndex1 = aCheckIndex;
 
 aAngleRangeStart1 = aCheckRangeStart;
 aAngleRangeEnd1 = aCheckRangeEnd;
 }
 
 if((pAngleEnd >= aCheckRangeStart) && (pAngleEnd < aCheckRangeEnd))
 {
 aStartIndex2 = aCheckIndex;
 
 aAngleRangeStart2 = aCheckRangeStart;
 aAngleRangeEnd2 = aCheckRangeEnd;
 }
 
 aCheckIndex++;
 }
 
 if(aAngleRangeEnd1 < aAngleRangeStart1)aAngleRangeEnd1 += 360.0f;
 if(aAngleRangeEnd2 < aAngleRangeStart2)aAngleRangeEnd2 += 360.0f;
 
 aEndIndex1 = aStartIndex1 + 1;
 if(aEndIndex1 == 8)aEndIndex1 = 0;
 
 aEndIndex2 = aStartIndex2 + 1;
 if(aEndIndex2 == 8)aEndIndex2 = 0;
 
 
 float aIntersectionX[2];
 float aIntersectionY[2];
 float aIntersectionU[2];
 float aIntersectionV[2];
 
 
 aIntersectionX[0] = aStartX;
 aIntersectionY[0] = aStartY;
 aIntersectionX[1] = aStartX;
 aIntersectionY[1] = aStartY;
 
 aIntersectionU[0] = aStartU;
 aIntersectionV[0] = aStartV;
 aIntersectionU[1] = aStartU;
 aIntersectionV[1] = aStartV;
 
 
 
 
 
 for(int k=0;k<2;k++)
 {
 
 float aCheckDirX = 0.0f;
 float aCheckDirY = 0.0f;
 
 int aCheckIndex = aStartIndex1;
 
 float aCheckStartX = aStartX;
 float aCheckStartY = aStartY;
 
 float aCheckEndX = aEndX;
 float aCheckEndY = aStartY;
 
 
 float aCheckStartU = aStartU;
 float aCheckStartV = aStartV;
 
 float aCheckEndU = aEndU;
 float aCheckEndV = aStartV;
 
 
 if(k == 0)
 {
 aCheckDirX = Sin(pAngleStart);
 aCheckDirY = -Cos(pAngleStart);
 }
 else
 {
 aCheckDirX = Sin(pAngleEnd);
 aCheckDirY = -Cos(pAngleEnd);
 aCheckIndex = aStartIndex2;
 }
 
 if((aCheckIndex == 0) || (aCheckIndex == 7))
 {
 
 }
 
 if((aCheckIndex == 1) || (aCheckIndex == 2))
 {
 aCheckStartX = aEndX;
 aCheckStartY = aStartY;
 aCheckEndX = aEndX;
 aCheckEndY = aEndY;
 
 aCheckStartU = aEndU;
 aCheckStartV = aStartV;
 aCheckEndU = aEndU;
 aCheckEndV = aEndV;
 }
 
 if((aCheckIndex == 3) || (aCheckIndex == 4))
 {
 aCheckStartX = aEndX;
 aCheckStartY = aEndY;
 aCheckEndX = aStartX;
 aCheckEndY = aEndY;
 
 aCheckStartU = aEndU;
 aCheckStartV = aEndV;
 aCheckEndU = aStartU;
 aCheckEndV = aEndV;
 }
 
 if((aCheckIndex == 5) || (aCheckIndex == 6))
 {
 aCheckStartX = aStartX;
 aCheckStartY = aEndY;
 aCheckEndX = aStartX;
 aCheckEndY = aStartY;
 
 
 aCheckStartU = aStartU;
 aCheckStartV = aEndV;
 aCheckEndU = aStartU;
 aCheckEndV = aStartV;
 }
 
 
 
 float aLineStartX = aCheckStartX;
 float aLineStartY = aCheckStartY;
 
 float aLineEndX = aCheckEndX;
 float aLineEndY = aCheckEndY;
 
 float aLineDirX = (aLineEndX - aLineStartX);
 float aLineDirY = (aLineEndY - aLineStartY);
 
 float aLineNormX = (-aLineDirY);
 float aLineNormY = aLineDirX;
 
 float aPlaneLength = (aLineDirX * aLineDirX) + (aLineDirY * aLineDirY);
 
 if(aPlaneLength > 0.01f)
 {
 aPlaneLength = sqrtf(aPlaneLength);
 
 aLineDirX /= aPlaneLength;
 aLineDirY /= aPlaneLength;
 }
 
 //float aDiffX = (aLineStartX - aCenterX);
 //float aDiffY = (aLineStartY - aCenterY);
 
 
 float aNumer = (aCenterX * aLineNormX + aCenterY * aLineNormY - (aLineNormX * aLineStartX + aLineNormY * aLineStartY));
 float aDenom = (aCheckDirX * aLineNormX + aCheckDirY * aLineNormY);
 float aCheckLength1 = -(aNumer / aDenom);
 
 
 aIntersectionX[k] = aCenterX + aCheckDirX * aCheckLength1;
 aIntersectionY[k] = aCenterY + aCheckDirY * aCheckLength1;
 
 //aIntersectionX[1] = aStartX;
 //aIntersectionY[1] = aStartY;
 
 float aEdgeX1 = aCenterX + aCheckDirX * aCheckLength1;
 float aEdgeY1 = aCenterY + aCheckDirY * aCheckLength1;
 
 
 Graphics::SetColor(0.0f, 1.0f, 0.0f);
 Graphics::DrawLine(aCheckStartX + pX, aCheckStartY + pY, aCheckEndX + pX, aCheckEndY + pY);
 
 Graphics::DrawPoint(pX + aEdgeX1, pY + aEdgeY1);
 }
 
 
 
 Graphics::SetColor(1.0f, 1.0f, 1.0f);
 Graphics::DrawPoint(pX + aIntersectionX[0], pY + aIntersectionY[0], 16.0f);
 
 
 Graphics::DrawPoint(pX + aIntersectionX[1], pY + aIntersectionY[1], 16.0f);
 
 
 
 //aX[0] = mTextureRect.GetStartX();
 
 float aX1 = mTextureRect.GetStartX();
 float aX2 = mTextureRect.GetEndX();
 float aX3 = aX1;
 float aX4 = aX2;
 
 
 float aY1 = mTextureRect.GetStartY();
 float aY2 = aY1;
 float aY3 = mTextureRect.GetEndY();
 float aY4 = aY3;
 
 
 
 //cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
 //cSliceTextureRect.SetQuad(aX1 + pShiftUL.mX, aY1 + pShiftUL.mY, aX2 + pShiftUR.mX, aY2 + pShiftUR.mY, aX3, aY3, aX4, aY4);
 
 //Graphics::CullFacesEnable();
 //Graphics::CullFacesSetFront();
 
 cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
 
 //Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, pRotationDegrees, cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
 
 
 Graphics::SetColor(0.45f, 1.0f, 0.0f);
 
 int aStartIndex = aStartIndex1;
 int aEndIndex = aStartIndex2;
 
 FTextureTriangle aTestTriangle;
 
 //aEndIndex = 7;
 //aStartIndex = 0;
 
 int aLoops = 0;
 
 //while(aStartIndex<aEndIndex)
 for(int aIndex = aStartIndex1 + 1;aIndex < aStartIndex2;aIndex++)
 {
 aLoops++;
 
 //int aEndIndex = aStartIndex + 1;
 //if(aEndIndex == 8)aEndIndex = 0;
 
 
 Graphics::SetColorSwatch(aStartIndex, 0.75f);
 //Graphics::SetColor(gRand.GetFloat(0.85f, 1.0f));
 
 SetColor();
 
 if(aStartIndex == aStartIndex1)SetColor(1.0f, 0.0f, 0.0f);
 if(aStartIndex == aStartIndex2)SetColor(0.0f, 1.0f, 0.0f);
 
 aTestTriangle.SetXYTriangle(aCenterX, aCenterY, aX[aIndex], aY[aIndex], aX[aIndex + 1], aY[aIndex + 1]);
 aTestTriangle.SetUVTriangle(aCenterU, aCenterV, aU[aIndex], aV[aIndex], aU[aIndex + 1], aV[aIndex + 1]);
 
 Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTestTriangle.mVertex, aTestTriangle.mTextureCoord, mTexture);
 
 Graphics::DrawLine(aStartX, aStartY, aEndX, aEndY, 5.0f);
 
 aEndIndex = aStartIndex;
 aStartIndex++;
 
 }
 
 if(aStartIndex1 == aStartIndex2)
 {
 aTestTriangle.SetXYTriangle(aCenterX, aCenterY, aIntersectionX[0], aIntersectionY[0], aIntersectionX[1], aIntersectionY[1]);
 aTestTriangle.SetUVTriangle(aCenterU, aCenterV, aU[0], aV[0], aU[1], aV[1]);
 
 Graphics::DrawSpriteTriangle(pX, pY, 1.0f, 1.0f, 1.0f, 0.0f, aTestTriangle.mVertex, aTestTriangle.mTextureCoord, mTexture);
 
 }
 
 
 
 }
 */


void FSprite::DrawSlice(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY)
{
    DrawSliceTo(pTextureRect, pStartX, pStartY, pEndX, pEndY, 0.0f, 0.0f, pEndX - pStartX, pEndY - pStartY);
}

void FSprite::DrawSliceTo(float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY)
{
    DrawSliceTo(&cSliceTextureRect, pStartX, pStartY, pEndX, pEndY, pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
}

void FSprite::DrawSlice(float pStartX, float pStartY, float pEndX, float pEndY)
{
    DrawSlice(&cSliceTextureRect, pStartX, pStartY, pEndX, pEndY);
}

void FSprite::Draw()
{
    Graphics::DrawSprite(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawScaled(float pX, float pY, float pScale)
{
    Draw(pX, pY, pScale, 0.0f);
}

void FSprite::DrawScaled(float pX, float pY, float pScaleX, float pScaleY)
{
    Graphics::DrawSprite(pX, pY, pScaleX, pScaleY, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawScaled(float pX, float pY, float pScaleX, float pScaleY, float pRotation)
{
    Graphics::DrawSprite(pX, pY, pScaleX, pScaleY, 1.0f, pRotation, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawRotated(float pX, float pY, float pRotation)
{
    Draw(pX, pY, 1.0f, pRotation);
}

void FSprite::PrintQuadData()
{
    FString aName = mFileName.c();
    aName.RemoveExtension();
    aName.RemovePath();
    
    Log("Sprite [ %s ] Sz(%.1fx%.1f) Tex[%.3f, %.3f, %.3f, %.3f], Rec[%.1f, %.1f, %.1f, %.1f]\n", aName.c(), mWidth, mHeight, mTextureRect.GetStartU(), mTextureRect.GetStartV(), mTextureRect.GetEndU(), mTextureRect.GetEndV(), mTextureRect.GetStartX(), mTextureRect.GetStartY(), mTextureRect.GetEndX(), mTextureRect.GetEndY());
    
    
}




