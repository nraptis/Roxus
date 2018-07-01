#include "FTexture.h"
#include "FSprite.h"
#include "FImage.h"

#include "core_includes.h"
#include "core_graphics.h"

/*
FTexture::FTexture(FTexture *pBundleTexture)
{
    
    
}
*/

FTexture::FTexture(const char *pFileName)
{
    Initialize(pFileName);
    
    
}

FTexture::FTexture()
{
	mBindIndex = -1;
	//mBundleTexture = 0;

	mWidth = 0;
	mHeight = 0;

	mExpandedWidth = 0;
	mExpandedHeight = 0;

	mOffsetX = 0;
	mOffsetY = 0;
	//FTexture::FTexture();


	//mFileNameBundle = "";

	mDidFailLoad = false;

    Initialize();
}

FTexture::~FTexture()
{
    
}

bool FTexture::IsValid()
{
    bool aReturn = false;
    
    //(mBindIndex >= 0) && 
    if((mExpandedWidth > 0) && (mExpandedHeight > 0))
    {
        aReturn = true;
    }
    
    return aReturn;
}

void FTexture::Initialize(const char *pFilePath)
{
	mBindIndex = -1;
	//mBundleTexture = 0;

	mWidth = 0;
	mHeight = 0;

	mExpandedWidth = 0;
	mExpandedHeight = 0;

	mOffsetX = 0;
	mOffsetY = 0;
	//FTexture::FTexture();


	//mFileNameBundle = "";

	mDidFailLoad = false;

    Initialize();
    
    mFileName = pFilePath;
    Realize();
}

void FTexture::Initialize()
{
    
}

//Realize.. If we're gonna be
void FTexture::Realize()
{
    
    if((mBindIndex == -1) && (mDidFailLoad == false))
    {
        FImage aImage;
        aImage.Load(mFileName);
        
        //TODO: Resolve texture loading situation.
        if(((gEnvironment != ENV_IPHONE) || (gIsLargeScreen == false)) && false)
        {
            FImage *aResize = aImage.Resize50Percent();
            Load(aResize);
            delete aResize;
        }
        else
        {
            Load(&aImage);
        }
    }
}

void FTexture::Load(FImage *pImage)
{
    
    pImage->MakePowerOf2();
    
    mWidth = pImage->mWidth;
    mHeight = pImage->mHeight;
    
    mExpandedWidth = pImage->mExpandedWidth;
    mExpandedHeight = pImage->mExpandedHeight;
    
    mOffsetX = pImage->mOffsetX;
    mOffsetY = pImage->mOffsetY;
    
    mDidFailLoad = false;
    
    if(pImage->DidLoad())
    {
        mBindIndex = Graphics::TextureGenerate(pImage->mData, mExpandedWidth, mExpandedHeight);
    }
    else
    {
        mDidFailLoad = true;
        mBindIndex = -1;
    }
}

void FTexture::Unload()
{
    if(mBindIndex >= 0)
    {
        Graphics::TextureDelete(mBindIndex);
        mBindIndex = -1;
        mDidFailLoad = false;
    }
}

float FTexture::GetStartU()
{
    float aReturn = 0.0f;
    if(mExpandedWidth > 0)
    {
        aReturn = ((float)mOffsetX) / ((float)mExpandedWidth);
    }
    return aReturn;
}

float FTexture::GetStartV()
{
    float aReturn = 0.0f;
    if(mExpandedHeight > 0)
    {
        aReturn = ((float)(mOffsetY)) / ((float)mExpandedHeight);
    }
    return aReturn;
}

float FTexture::GetEndU()
{
    float aReturn = 1.0f;
    if(mExpandedWidth > 0)
    {
        aReturn = ((float)(mOffsetX + mWidth)) / ((float)mExpandedWidth);
    }
    return aReturn;
}

float FTexture::GetEndV()
{
    float aReturn = 1.0f;
    if(mExpandedHeight > 0)
    {
        aReturn = ((float)(mOffsetY + mHeight)) / ((float)mExpandedHeight);
    }
    return aReturn;
}





/*

void FTexture::Add(FSprite *pSprite)
{
    for(int i=0;i<mSpriteListCount;i++)
    {
        if(mSprite[i] == pSprite)
        {
            return;
        }
    }
    
    if(mSpriteListCount >= mSpriteListSize)
    {
        mSpriteListSize = (mSpriteListCount + mSpriteListCount / 2 + 1);
        
        FSprite **aSpriteNew = new FSprite*[mSpriteListSize];
        
        for(int i=0;i<mSpriteListCount;i++)
        {
            aSpriteNew[i] = mSprite[i];
        }
        
        delete [] mSprite;
        
        mSprite = aSpriteNew;
    }
    
    mSprite[mSpriteListCount] = pSprite;
    mSpriteListCount++;
}

void FTexture::Remove(FSprite *pSprite)
{
    
}
 
*/




FTextureRect::FTextureRect()
{
    mVertex[0] = -128.0f;
    mVertex[1] = -128.0f;
    mVertex[2] = 128.0f;
    mVertex[3] = -128.0f;
    mVertex[4] = -128.0f;
    mVertex[5] = 128.0f;
    mVertex[6] = 128.0f;
    mVertex[7] = 128.0f;
    
    mTextureCoord[0] = 0.0f;
    mTextureCoord[1] = 0.0f;
    mTextureCoord[2] = 1.0f;
    mTextureCoord[3] = 0.0f;
    mTextureCoord[4] = 0.0f;
    mTextureCoord[5] = 1.0f;
    mTextureCoord[6] = 1.0f;
    mTextureCoord[7] = 1.0f;
}

FTextureRect::~FTextureRect()
{
    
}

void FTextureRect::Set(FTexture *pTexture, float pX, float pY)
{
    if(pTexture)
    {
        SetRect(pX, pY, pX + pTexture->mWidth, pY + pTexture->mHeight);
        SetUVQuad(pTexture->GetStartU(), pTexture->GetStartV(), pTexture->GetEndU(), pTexture->GetEndV());
    }
}

void FTextureRect::SetUVQuad(float pStartU, float pStartV, float pEndU, float pEndV)
{
    SetStartU(pStartU);
    SetStartV(pStartV);
    SetEndU(pEndU);
    SetEndV(pEndV);
}

void FTextureRect::SetUVRect(float pStartU, float pStartV, float pWidthU, float pHeightV)
{
    SetStartU(pStartU);
    SetStartV(pStartV);
    SetEndU(pStartU + pWidthU);
    SetEndV(pStartV + pHeightV);
}

void FTextureRect::SetQuad(float pStartX, float pStartY, float pEndX, float pEndY)
{
    SetStartX(pStartX);
    SetStartY(pStartY);
    SetEndX(pEndX);
    SetEndY(pEndY);
}

void FTextureRect::SetRect(float pStartX, float pStartY, float pWidth, float pHeight)
{
    SetStartX(pStartX);
    SetStartY(pStartY);
    SetEndX(pStartX + pWidth);
    SetEndY(pStartY + pHeight);
    
}

void FTextureRect::SetQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4)
{
    mVertex[0] = pX1;
    mVertex[1] = pY1;
    mVertex[2] = pX2;
    mVertex[3] = pY2;
    mVertex[4] = pX3;
    mVertex[5] = pY3;
    mVertex[6] = pX4;
    mVertex[7] = pY4;
}



FTextureTriangle::FTextureTriangle()
{
    mVertex[0] = -128.0f;
    mVertex[1] = -128.0f;
    mVertex[2] = 128.0f;
    mVertex[3] = -128.0f;
    mVertex[4] = -128.0f;
    mVertex[5] = 128.0f;
    
    mTextureCoord[0] = 0.0f;
    mTextureCoord[1] = 0.0f;
    mTextureCoord[2] = 1.0f;
    mTextureCoord[3] = 0.0f;
    mTextureCoord[4] = 0.0f;
    mTextureCoord[5] = 1.0f;
}

FTextureTriangle::~FTextureTriangle()
{
    
}

void FTextureTriangle::SetXYTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
{
    mVertex[0] = pX1;
    mVertex[1] = pY1;
    mVertex[2] = pX2;
    mVertex[3] = pY2;
    mVertex[4] = pX3;
    mVertex[5] = pY3;
}

//void FTextureTriangle::SetUVTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
void FTextureTriangle::SetUVTriangle(float pU1, float pV1, float pU2, float pV2, float pU3, float pV3)
{
    mTextureCoord[0] = pU1;
    mTextureCoord[1] = pV1;
    
    mTextureCoord[2] = pU2;
    mTextureCoord[3] = pV2;
    
    mTextureCoord[4] = pU3;
    mTextureCoord[5] = pV3;
}


