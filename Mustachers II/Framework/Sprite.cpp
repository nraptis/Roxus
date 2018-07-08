#include "Application.h"
#include "Sprite.h"
#include "VertexBuffer.h"
#include "GLApp.h"

bool gSpriteIgnoreRetina=false;

Sprite::Sprite()
{
	mBindIndex=-1;
	mWidth=0;
	mHeight=0;
    
    mBundlerNode=0;
	
	//for(int i=0;i<16;i++)mColorCoord[i]=1.0f;
	for(int i=0;i<8;i++)mTextureCoord[i]=0.0f;
	for(int i=0;i<8;i++)mTextureVertex[i]=0.0f;
    
	mTextureCoord[2]=1;
	mTextureCoord[5]=1;
	mTextureCoord[6]=1;
	mTextureCoord[7]=1;
    
	mImage=0;
	//mInlineImage=0;
}

Sprite::~Sprite()
{
	Kill();
	//delete mInlineImage;
	//mInlineImage=0;
}

void Sprite::Kill()
{
	//printf("Sprite Kill!\n");
	//if(mImage)printf("Killd Image: %s\n", mImage->mPath.c());
	//if(mBindIndex>0)
	gApp->RemoveBind(mBindIndex);
	mBindIndex=-1;
	mWidth=0;
	mHeight=0;
}



/*
void Sprite::Load(Splat *pSplat, char *pName)
{
	Kill();
	Image *aImage=&pSplat->mImage;
	SplatChunk *aChunk=pSplat->Fetch(pName);
	Load(aChunk, pSplat, pName);
	
	//printf("Sprite LoadExt (%.3f %.3f %.3f %.3f) (%d %d %d %d)\n", aChunk->mLeft,aChunk->mRight,aChunk->mTop,aChunk->mBottom,
	//	   aChunk->mX,aChunk->mY,aChunk->mWidth,aChunk->mHeight);
}

void Sprite::Load(SplatChunk *pChunk, Splat *pSplat, char *pName)
{
	if(!pChunk || !pSplat)
	{
		printf("There was a problem loading [%s]\n", pName);
		return;
	}
	
	Image *aImage = &pSplat->mImage;
	mImage=aImage;
	aImage->Bind();
	mBindIndex=aImage->mBindIndex;
	
	if(gApp)gApp->AddBind(mBindIndex);
	
	float aStartU=(float)(pChunk->mX)/(float)aImage->mExpandedWidth;
	float aStartV=(float)(pChunk->mY)/(float)aImage->mExpandedHeight;
	float aEndU=(float)(pChunk->mX+pChunk->mWidth)/(float)aImage->mExpandedWidth;
	float aEndV=(float)(pChunk->mY+pChunk->mHeight)/(float)aImage->mExpandedHeight;
	
	if(pChunk->mRotated)
	{
		mTextureCoord[2]=aStartU;
		mTextureCoord[3]=aStartV;
		mTextureCoord[6]=aEndU;
		mTextureCoord[7]=aStartV;
		mTextureCoord[0]=aStartU;
		mTextureCoord[1]=aEndV;
		mTextureCoord[4]=aEndU;
		mTextureCoord[5]=aEndV;
	}
	else
	{
		mTextureCoord[0]=aStartU;
		mTextureCoord[1]=aStartV;
		mTextureCoord[2]=aEndU;
		mTextureCoord[3]=aStartV;
		mTextureCoord[4]=aStartU;
		mTextureCoord[5]=aEndV;
		mTextureCoord[6]=aEndU;
		mTextureCoord[7]=aEndV;
	}
	
	mTextureVertex[0]=pChunk->mLeft;
	mTextureVertex[1]=pChunk->mTop;
	mTextureVertex[2]=pChunk->mRight;
	mTextureVertex[3]=pChunk->mTop;
	mTextureVertex[4]=pChunk->mLeft;
	mTextureVertex[5]=pChunk->mBottom;
	mTextureVertex[6]=pChunk->mRight;
	mTextureVertex[7]=pChunk->mBottom;
	
	mWidth=pChunk->mImageWidth;
	mHeight=pChunk->mImageHeight;
	
	if(mWidth <=0 || mHeight <=0)
	{
		printf("There was a problem loading [%s] from chunk!\n", pName);
	}
}
*/

void Sprite::SetRect(float pWidth, float pHeight)
{
    float aLeft = -(pWidth / 2.0f);
    float aRight = aLeft + pWidth;
    float aTop = -(pHeight / 2.0f);
    float aBottom = aTop + pHeight;
    
    mTextureVertex[0]=aLeft;
    mTextureVertex[1]=aTop;
    mTextureVertex[2]=aRight;
    mTextureVertex[3]=aTop;
    mTextureVertex[4]=aLeft;
    mTextureVertex[5]=aBottom;
    mTextureVertex[6]=aRight;
    mTextureVertex[7]=aBottom;
}

void Sprite::SetRect(float pX, float pY, float pWidth, float pHeight)
{
    float aLeft = pX;
    float aRight = aLeft + pWidth;
    float aTop = pY;
    float aBottom = aTop + pHeight;
    
    mTextureVertex[0]=aLeft;
    mTextureVertex[1]=aTop;
    mTextureVertex[2]=aRight;
    mTextureVertex[3]=aTop;
    mTextureVertex[4]=aLeft;
    mTextureVertex[5]=aBottom;
    mTextureVertex[6]=aRight;
    mTextureVertex[7]=aBottom;
    
}

void Sprite::Load(char *pName, ImageBundler *pBundler)
{
	if(mBindIndex!=-1)Kill();
	if(!pBundler)return;
	if(pBundler->mImage.mWidth==0)return;
    
	ImageBundlerLoadNode *aNode = pBundler->FetchNode(pName);
	Image *aImage = &pBundler->mImage;
    
    
    bool aHoldRetinaResize = gSpriteIgnoreRetina;
    gSpriteIgnoreRetina = true;
    
	if(aNode)
	{
        //mBundlerNode = aNode->Clone();
        
		if(aImage->mBindIndex == -1)aImage->Bind();
		
		mBindIndex=aImage->mBindIndex;
		if(gApp)gApp->AddBind(mBindIndex);
		
		mBindIndex = aImage->mBindIndex;
        
        float aStartU,aStartV,aEndU,aEndV;
        float aLeft, aTop, aRight, aBottom;
        
        
        aStartU=aNode->mSpriteUStart;
        aStartV=aNode->mSpriteVStart;
        
        aEndU=aNode->mSpriteUEnd;
        aEndV=aNode->mSpriteVEnd;
        
        
        
        aLeft=aNode->mSpriteLeft;
        aRight=aNode->mSpriteRight;
        
        aTop=aNode->mSpriteTop;
        aBottom=aNode->mSpriteBottom;
        
        mWidth=aNode->mSpriteWidth;
        mHeight=aNode->mSpriteHeight;
        
        /*
		if(aNode->mRotated)
		{
            aLeft = -aWidth / 2.0f + (float)aNode->mOffsetX;
            aRight = aLeft + (float)aNode->mHeight;
            aTop = -aHeight / 2.0f + (float)aNode->mOffsetY;
            aBottom = aTop + (float)aNode->mWidth;
            
            
            
            mTextureCoord[0]=aStartU;
			mTextureCoord[1]=aEndV;
			mTextureCoord[2]=aStartU;
			mTextureCoord[3]=aStartV;
            mTextureCoord[4]=aEndU;
			mTextureCoord[5]=aEndV;
			mTextureCoord[6]=aEndU;
			mTextureCoord[7]=aStartV;
            
            printf("FAIL -- Loaded Coords[%f %f %f %f]\n", aLeft, aRight, aTop, aBottom);
		}
		else
		{
         
            aLeft = -(aWidth / 2.0f) + (float)aNode->mOffsetX;
            aTop = -(aHeight / 2.0f) + (float)aNode->mOffsetY;
        
        
            aRight = aLeft + (float)aNode->mWidth;
            aBottom = aTop + (float)aNode->mHeight;
            
			
            
            printf("Loaded Coords[%f %f %f %f]\n", aLeft, aRight, aTop, aBottom);
            
		//}
        */
        
        
        mTextureCoord[0]=aStartU;
        mTextureCoord[1]=aStartV;
        mTextureCoord[2]=aEndU;
        mTextureCoord[3]=aStartV;
        mTextureCoord[4]=aStartU;
        mTextureCoord[5]=aEndV;
        mTextureCoord[6]=aEndU;
        mTextureCoord[7]=aEndV;
        
        
		mTextureVertex[0]=aLeft;
		mTextureVertex[1]=aTop;
		mTextureVertex[2]=aRight;
		mTextureVertex[3]=aTop;
		mTextureVertex[4]=aLeft;
		mTextureVertex[5]=aBottom;
		mTextureVertex[6]=aRight;
		mTextureVertex[7]=aBottom;
	}
    
    gSpriteIgnoreRetina = aHoldRetinaResize;
}

void Sprite::Load(char *pFile)
{
	Kill();
    
    mPath = pFile;
	
    if(gApp->mImageBundle)
    {
        Load(pFile, gApp->mImageBundle);
        if(mWidth > 0 && mHeight > 0)
        {
            //printf("Bundle Loaded [%d] [%s]\n", mBindIndex, pFile);
            return;
        }
    }
	/*
	if(gApp->mCurrentSplat)
	{
		SplatChunk *aChunk=gApp->mCurrentSplat->Fetch(pFile);
		if(aChunk)
		{
			Load(aChunk, gApp->mCurrentSplat, pFile);
		}
	}
	*/
	
	Image *aImage=new Image();
	aImage->Load(pFile);
	aImage->Bind();
	mBindIndex=aImage->mBindIndex;
	
	//trace("Post Load: %d [%s]\n", mBindIndex, aImage->mPath.c());
	
	if(mBindIndex==-1)
	{
        if(mWidth > 0)
        {
            printf("Cannot Bind Image: %s\n", pFile);
        }
		//mInlineImage=aImage;
		//mWidth=aImage->mWidth;
		//mHeight=aImage->mHeight;
		delete aImage;
	}
	else
	{
		Load(aImage,0,0,aImage->mWidth,aImage->mHeight);
		delete aImage;
	}
    
    if(mWidth <= 0 || mHeight <= 0)
    {
        //printf("Cannot Load Image: %s\n", pFile);
    }
    

    
    
}

void Sprite::Load(const char *pFileStart, int pIndex, const char *pFileEnd)
{
    FString aPath = FString(pFileStart) + FString(pIndex) + FString(pFileEnd);
    Load(aPath.c());
}

void Sprite::Load(Image *pImage)
{
	if(pImage)
	{
		//Load(pImage, pImage->mOffsetX, pImage->mOffsetY, pImage->mWidth, pImage->mHeight); 
		Load(pImage, 0, 0, pImage->mWidth, pImage->mHeight); 
	}
}

void Sprite::Rotate90()
{
	float aHold;
	for(int i=0;i<8;i+=2)
	{
		aHold=mTextureVertex[i];
		mTextureVertex[i]=-mTextureVertex[i+1];
		mTextureVertex[i+1]=aHold;
	}
	
	int aWidth=mWidth;
	mWidth=mHeight;
	mHeight=aWidth;
}


void Sprite::StretchTo(Image *pImage, int pNewWidth, int pNewHeight)
{
    float aStartX = 0;
    float aStartY = 0;
    float aEndX = pNewWidth;
    float aEndY = pNewHeight;
    
    float aStartU=0;
	float aStartV=0;
	float aEndU=(float)pImage->mWidth/(float)pImage->mExpandedWidth;
	float aEndV=(float)pImage->mHeight/(float)pImage->mExpandedHeight;
    
    mTextureVertex[0]=aStartX;
	mTextureVertex[1]=aStartY;
    
	mTextureVertex[2]=aEndX;
	mTextureVertex[3]=aStartY;
    
	mTextureVertex[4]=aStartX;
	mTextureVertex[5]=aEndY;
    
	mTextureVertex[6]=aEndX;
	mTextureVertex[7]=aEndY;
    
	mTextureCoord[0]=aStartU;
	mTextureCoord[1]=aStartV;
    
	mTextureCoord[2]=aEndU;
	mTextureCoord[3]=aStartV;
    
	mTextureCoord[4]=aStartU;
	mTextureCoord[5]=aEndV;
    
	mTextureCoord[6]=aEndU;
	mTextureCoord[7]=aEndV;
}

void Sprite::CalculateUV(int x, int y, int pWidth, int pHeight, int pImageWidth, int pImageHeight, bool pCentered, bool pRotate)
{
    float aStartX = x;
    float aStartY = y;
    float aEndX = x + pWidth;
    float aEndY = y + pHeight;
    
    float aStartU=aStartX/(float)pImageWidth;
	float aStartV=aStartY/(float)pImageHeight;
	float aEndU=aEndX/(float)pImageWidth;
	float aEndV=aEndY/(float)pImageHeight;
    
    printf("Sprite UVW: [%f %f] [%f %f]\n", aStartU, aStartV, aEndU, aEndV);
    printf("Sprite XYZ: [%f %f] [%f %f]\n", aStartX, aStartY, aEndX, aEndY);
    
    mTextureVertex[0]=aStartX;
	mTextureVertex[1]=aStartY;
    
	mTextureVertex[2]=aEndX;
	mTextureVertex[3]=aStartY;
    
	mTextureVertex[4]=aStartX;
	mTextureVertex[5]=aEndY;
    
	mTextureVertex[6]=aEndX;
	mTextureVertex[7]=aEndY;
    
    if(pRotate)
    {
        
        float aHold;
        for(int i=0;i<8;i+=2)
        {
            aHold=mTextureVertex[i];
            mTextureVertex[i]=mTextureVertex[i+1];
            mTextureVertex[i+1]=aHold;
        }
        
        for(int i=0;i<8;i+=2)
        {
            aHold=mTextureVertex[i];
            mTextureVertex[i]=mTextureVertex[i+1];
            mTextureVertex[i+1]=aHold;
        }
        
        for(int i=0;i<8;i+=2)
        {
            aHold=mTextureVertex[i];
            mTextureVertex[i]=mTextureVertex[i+1];
            mTextureVertex[i+1]=aHold;
        }
    }
    
	mTextureCoord[0]=aStartU;
	mTextureCoord[1]=aStartV;
    
	mTextureCoord[2]=aEndU;
	mTextureCoord[3]=aStartV;
    
	mTextureCoord[4]=aStartU;
	mTextureCoord[5]=aEndV;
    
	mTextureCoord[6]=aEndU;
	mTextureCoord[7]=aEndV;
}

void Sprite::Recenter(float pX, float pY)
{
    float aWidth2=((float)mWidth)/2.0f;
    float aHeight2=((float)mHeight)/2.0f;
    
	mTextureVertex[0]=-aWidth2 + pX;
	mTextureVertex[1]=-aHeight2 + pY;
    
	mTextureVertex[2]=aWidth2 + pX;
	mTextureVertex[3]=-aHeight2 + pY;
    
	mTextureVertex[4]=-aWidth2 + pX;
	mTextureVertex[5]=aHeight2 + pY;
    
	mTextureVertex[6]=aWidth2 + pX;
	mTextureVertex[7]=aHeight2 + pY;
    
    
    //mTextureVertex[0]=-aWidth2;
	//mTextureVertex[1]=-aHeight2;
	//mTextureVertex[2]=aWidth2;
	//mTextureVertex[3]=-aHeight2;
	//mTextureVertex[4]=-aWidth2;
	//mTextureVertex[5]=aHeight2;
	//mTextureVertex[6]=aWidth2;
	//mTextureVertex[7]=aHeight2;
}

void Sprite::Load(Image *pImage, int x, int y, int pWidth, int pHeight)
{
	//printf("Image Loading ( %x %d %d %d %d )\n", pImage, x, y, pWidth, pHeight);
	//Kill();
	
	if(!pImage)return;
	if(pImage->mWidth<=0||pImage->mHeight<=0)return;
	
	if(pImage->mBindIndex==-1)pImage->Bind();
	mBindIndex=pImage->mBindIndex;
	
	//printf("Sprite Loading BInds: i:%d s:%d\n", pImage->mBindIndex, mBindIndex);
	
	if(gApp)gApp->AddBind(mBindIndex);
	
	x+=pImage->mOffsetX;
	y+=pImage->mOffsetY;
	
	mWidth=pWidth;
	mHeight=pHeight;
    
#ifdef IPAD_RETINA_TEST_MODE
    
    if(gDoubleRez==true && gSpriteIgnoreRetina==false)
    {
        mWidth /= 2;
        mHeight /= 2;
    }
    
#endif
	
	float aHeight2=((float)mHeight)/2.0f;
	float aWidth2=((float)mWidth)/2.0f;
	mTextureVertex[0]=-aWidth2;
	mTextureVertex[1]=-aHeight2;
	mTextureVertex[2]=aWidth2;
	mTextureVertex[3]=-aHeight2;
	mTextureVertex[4]=-aWidth2;
	mTextureVertex[5]=aHeight2;
	mTextureVertex[6]=aWidth2;
	mTextureVertex[7]=aHeight2;
	
	mCenterX=0;
	mCenterY=0;
	
	float aStartU=(float)x/(float)pImage->mExpandedWidth;
	float aStartV=(float)y/(float)pImage->mExpandedHeight;
	float aEndU=(float)(x+pWidth)/(float)pImage->mExpandedWidth;
	float aEndV=(float)(y+pHeight)/(float)pImage->mExpandedHeight;
    
	mTextureCoord[0]=aStartU;
	mTextureCoord[1]=aStartV;
	mTextureCoord[2]=aEndU;
	mTextureCoord[3]=aStartV;
	mTextureCoord[4]=aStartU;
	mTextureCoord[5]=aEndV;
	mTextureCoord[6]=aEndU;
	mTextureCoord[7]=aEndV;
}

void Sprite::SetupBackground(Image *pImage, int pAppWidth, int pAppHeight, int pImageRectX, int pImageRectY, int pImageRectWidth, int pImageRectHeight)
{
    if(!pImage)return;
	if(pImage->mWidth<=0||pImage->mHeight<=0)return;
    
    if(pImage->mBindIndex != -1)
    {
        if(mBindIndex == -1)
        {
            mBindIndex = pImage->mBindIndex;
        }
    }
    
    mWidth = (float)pAppWidth;
    mHeight = (float)pAppWidth;
    
    float aLeft = pImageRectX;
    float aTop = pImageRectY;
    
    if(pImageRectWidth > pAppWidth)
    {
        aLeft += (((float)(pImageRectWidth - pAppWidth))) / 2.0f;
    }
    if(pImageRectHeight > pAppHeight)
    {
        aTop += (((float)(pImageRectHeight - pAppHeight))) / 2.0f;
    }
    
    
    float aWidth2=((float)pAppWidth)/2.0f;
    float aHeight2=((float)pAppHeight)/2.0f;
	
    
	mTextureVertex[0]=-aWidth2;
	mTextureVertex[1]=-aHeight2;
	mTextureVertex[2]=aWidth2;
	mTextureVertex[3]=-aHeight2;
	mTextureVertex[4]=-aWidth2;
	mTextureVertex[5]=aHeight2;
	mTextureVertex[6]=aWidth2;
	mTextureVertex[7]=aHeight2;
	
	mCenterX=0;
	mCenterY=0;
	
	float aStartU = (float)aLeft/(float)pImage->mExpandedWidth;
	float aStartV = (float)aTop/(float)pImage->mExpandedHeight;
	float aEndU = (float)(aLeft+pAppWidth)/(float)pImage->mExpandedWidth;
	float aEndV = (float)(aTop+pAppHeight)/(float)pImage->mExpandedHeight;
    
	mTextureCoord[0] = aStartU;
	mTextureCoord[1] = aStartV;
	mTextureCoord[2] = aEndU;
	mTextureCoord[3] = aStartV;
	mTextureCoord[4] = aStartU;
	mTextureCoord[5] = aEndV;
	mTextureCoord[6] = aEndU;
	mTextureCoord[7] = aEndV;
    
}

void Sprite::Center(float x, float y)
{
    gGraphics.DrawSprite(x, y, 1.0f, 1.0f, 1.0f, 0.0f, mTextureVertex, mTextureCoord, mBindIndex);
}

void Sprite::Draw(float x, float y)
{
    gGraphics.DrawSprite(x + mWidth/2.0f, y + mHeight/2.0f, 1.0f, 1.0f, 1.0f, 0.0f, mTextureVertex, mTextureCoord, mBindIndex);
}

//void Sprite::DrawRadial(float pStartRotation, float pEndRotation, float pCenterOffsetX, float pCenterOffsetY)

/*
void Sprite::DrawRadial(float pCenterX, float pCenterY, float pStartRotation, float pEndRotation, float pCenterOffsetX, float pCenterOffsetY)
{
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
    
    float aStartU = mTextureCoord[0];
	float aStartV = mTextureCoord[1];
    
    float aEndU = mTextureCoord[6];
	float aEndV = mTextureCoord[7];
    
    float aCenterX = pCenterX + pCenterOffsetX;
    float aCenterY = pCenterY + pCenterOffsetY;
    
    float aWidth2  = ((float)mWidth) / 2.0f;
    float aHeight2 = ((float)mHeight) / 2.0f;
    
    //aWidth2  = ((float)mWidth )/4.0f;
    //aHeight2 = ((float)mHeight)/4.0f;
    
    float aX[4];
    float aY[4];
    
    float aURange = (aEndU - aStartU);
    float aVRange = (aEndV - aStartV);
    
    float aLeft = pCenterX - aWidth2;
    float aRight = pCenterX + aWidth2;
    
    float aTop = pCenterY - aHeight2;
    float aBottom = pCenterY + aHeight2;
    
    aX[0] = pCenterX - aWidth2;
    aY[0] = pCenterY - aHeight2;
    
    aX[1] = pCenterX + aWidth2;
    aY[1] = pCenterY - aHeight2;
    
    aX[2] = pCenterX + aWidth2;
    aY[2] = pCenterY + aHeight2;
    
    aX[3] = pCenterX - aWidth2;
    aY[3] = pCenterY + aHeight2;
    
    for(int i=0;i<4;i++)
    {
        SetColorSwatch(i);
        DrawRect(aX[i]-9, aY[i]-9, 19.0f, 19.0f);
    }
    
    float aLineStartX, aLineStartY, aLineEndX, aLineEndY;
    
    float aLineDirX, aLineDirY;
    float aLineNormX, aLineNormY;
    float aDiffX, aDiffY;
    
    float aPlaneLength, aDiffLength;
    
    //Graphics::Translate(gAppWidth2, gAppHeight2, 0.0f);
    
    float aDirX1 = Sin(pStartRotation);
    float aDirY1 = Cos(pStartRotation);
    
    float aDirX2 = Sin(pEndRotation);
    float aDirY2 = Cos(pEndRotation);
    
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
        //printf("X[%d] = %f Y[%d] = %f\n", aStart, aX[aStart], aEnd, aY[aStart]);
        
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
        
        aDiffX = (aLineStartX - aCenterX);
        aDiffY = (aLineStartY - aCenterY);
        
        //aDiffLength
        
        //float d = -(aLineNormX * aLineStartX + aLineNormY * aLineStartY);
		//float numer = (aCenterX * aLineNormX + aCenterY * aLineNormY - (aLineNormX * aLineStartX + aLineNormY * aLineStartY));
		//float denom = (aDirX1 * aLineNormX + aDirY1 * aLineNormY);
        //float aLength = -(numer / denom);
        
        aNumer = (aCenterX * aLineNormX + aCenterY * aLineNormY - (aLineNormX * aLineStartX + aLineNormY * aLineStartY));
        aDenom = (aDirX1 * aLineNormX + aDirY1 * aLineNormY);
        aCheckLength1 = -(aNumer / aDenom);
        
        //return 
        
        if(aCheckLength1 > 0)
        {
            if(aCheckLength1 < aBestLength1)
            {
                aBestLength1 = aCheckLength1;
                aHitLine1 = aEnd;
            }
        }
        
        aDenom = (aDirX2 * aLineNormX + aDirY2 * aLineNormY);
        aCheckLength2 = -(aNumer / aDenom);
        
        //return
        
        if(aCheckLength2 > 0)
        {
            if(aCheckLength2 < aBestLength2)
            {
                aBestLength2 = aCheckLength2;
                aHitLine2 = aEnd;
            }
        }
        
        
        //inline float Dot(FPoint &pVector){return mX*pVector.mX+mY*pVector.mY;}
        
        SetColor(0.0f,1.0f,0.0f);
        DrawLine(aLineStartX, aLineStartY, aLineEndX, aLineEndY, 2.0f);
        
        aStart = aEnd;
        aEnd++;
    }
    

    float aEdgeX1 = aCenterX + aDirX1 * aBestLength1;
    float aEdgeY1 = aCenterY + aDirY1 * aBestLength1;
    
    float aEdgeX2 = aCenterX + aDirX2 * aBestLength2;
    float aEdgeY2 = aCenterY + aDirY2 * aBestLength2;
    
    if((aHitLine1 != -1) && (aHitLine2 != -1))
    {
        SetColor(0.88f, 0.45f, 0.33f);
        DrawRect(aEdgeX1 - 9.0f, aEdgeY1 - 9.0f, 19.0f, 19.0f);
        
        SetColor(0.22f, 0.44, 0.67f);
        DrawRect(aEdgeX2 - 9.0f, aEdgeY2 - 9.0f, 19.0f, 19.0f);
    }
    
    SetColor(1.0f, 1.0f, 1.0f, 0.45f);
    
    //DrawRect( - 11,  - 11, 23.0f, 23.0f);
    //DrawRect( - 11, aCenterY + aDirY2 * aBestLength2 - 11, 23.0f, 23.0f);
    
    VertexBuffer aBuffer;
    
    float aPercentU = (aCenterX - aLeft) / mWidth;
    float aPercentV = (aCenterY - aTop) / mHeight;
    
    float aCenterU = aStartU + aPercentU * aURange;
    float aCenterV = aStartV + aPercentV * aVRange;
    
    //float aStartU = mTextureCoord[0];
	//float aStartV = mTextureCoord[1];
    
    //float aEndU = mTextureCoord[6];
	//float aEndV = mTextureCoord[7];
    
	//mTextureCoord[2]=aEndU;
	//mTextureCoord[3]=aStartV;
    
	//mTextureCoord[4]=aStartU;
	//mTextureCoord[5]=aEndV;
    
    float aZ = 0.0f;
    float aW = 0.0f;
    
    float aEdgeU, aEdgeV;
    
    bool aPeelRight = (pStartRotation > pEndRotation);
    
    float aEdgeU1 = aStartU + ((aEdgeX1 - aLeft) / mWidth) * aURange;
    float aEdgeV1 = aStartV + ((aEdgeY1 - aTop) / mHeight) * aVRange;
    float aEdgeU2 = aStartU + ((aEdgeX2 - aLeft) / mWidth) * aURange;
    float aEdgeV2 = aStartV + ((aEdgeY2 - aTop) / mHeight) * aVRange;
    
    bool aDrawCorner[4];
    
    aDrawCorner[0] = false;
    aDrawCorner[1] = false;
    aDrawCorner[2] = false;
    aDrawCorner[3] = false;
    
    if(aHitLine1 == aHitLine2)
    {
        if(aPeelRight == false)
        {
            
            if(aHitLine1 == 0)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aStartU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aStartU, aEdgeV2, aW);
            }
            else if(aHitLine1 == 1)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aStartV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aStartV, aW);
            }
            else if(aHitLine1 == 2)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEndU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEndU, aEdgeV2, aW);
            }
            else
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aEndV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aEndV, aW);
            }
        }
        else
        {
            //"LEFT"
            if(aHitLine1 == 0)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aStartU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aStartU, aEdgeV2, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                
                aDrawCorner[1] = true;
                aDrawCorner[2] = true;
                aDrawCorner[3] = true;
            }
            
            //"TOP"
            if(aHitLine1 == 1)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aStartV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aStartV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                //aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                
                aDrawCorner[0] = true;
                aDrawCorner[2] = true;
                aDrawCorner[3] = true;
            }
            
            //RIGHT
            if(aHitLine1 == 2)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEndU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEndU, aEdgeV2, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                
                aDrawCorner[0] = true;
                aDrawCorner[1] = true;
                aDrawCorner[3] = true;
            }
            
            //Bottom
            if(aHitLine1 == 3)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aEndV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aEndV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                
                aDrawCorner[0] = true;
                aDrawCorner[1] = true;
                aDrawCorner[2] = true;
            }   
        }
    }
    else
    {
        aPeelRight = false;
        
        //Left
        if(aHitLine1 == 0)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aStartU, aEdgeV1, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
            else aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
        }
        
        //"TOP"
        if(aHitLine1 == 1)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aStartV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
            else aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
        }
        
        //RIGHT
        if(aHitLine1 == 2)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEndU, aEdgeV1, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
            else aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
        }
        
        //Bottom
        if(aHitLine1 == 3)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aEndV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
            else aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
        }
        
        //Left
        if(aHitLine2 == 0)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aStartU, aEdgeV2, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
            else aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
        }
        
        //"TOP"
        if(aHitLine2 == 1)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aStartV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
            else aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
        }
        
        //RIGHT
        if(aHitLine2 == 2)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEndU, aEdgeV2, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
            else aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
        }
        
        //Bottom
        if(aHitLine2 == 3)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aEndV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            if(aPeelRight)aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
            else aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
        }
        
        
        
        
        
        
        if(aHitLine1 == 0)
        {
            if(aHitLine2 == 2)aDrawCorner[3]=true;
            if(aHitLine2 == 1)
            {
                aDrawCorner[2]=true;
                aDrawCorner[3]=true;
            }
        }
        if(aHitLine1 == 1)
        {
            if(aHitLine2 == 3)aDrawCorner[0]=true;
            if(aHitLine2 == 2)
            {
                aDrawCorner[0]=true;
                aDrawCorner[3]=true;
            }
        }
        if(aHitLine1 == 2)
        {
            if(aHitLine2 == 0)
            {
                aDrawCorner[1]=true;
            }
            if(aHitLine2 == 3)
            {
                aDrawCorner[0]=true;
                aDrawCorner[1]=true;
            }
        }
        if(aHitLine1 == 3)
        {
            if(aHitLine2 == 1)aDrawCorner[2]=true;
            if(aHitLine2 == 0)
            {
                aDrawCorner[1]=true;
                aDrawCorner[2]=true;
            }
        }
        
        
        
        //for(int k=aHitLine1;k<aHitLine2
        

//        if(pStartRotation < 90)
//        {
//            aDraw[0] = true;
//        }
//        else if(pStartRotation < 180.0f)
//        {
//            aDraw[1] = true;
//        }
//        else if(pStartRotation < 270.0f)
//        {
//            aDraw[2] = true;
//        }
//        else
//        {
//            aDraw[3] = true;
//        }
        
        
        //aBuffer.mVertexCount = 0;
        //aBuffer.mCoordCount = 0;
        
        
        
    }
    
    if(aDrawCorner[0])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[3], aY[3], 0.0f, aStartU, aEndV, 1.0f);
        aBuffer.Add(aX[0], aY[0], 0.0f, aStartU, aStartV, 1.0f);
    }
    
    if(aDrawCorner[1])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[0], aY[0], 0.0f, aStartU, aStartV, 1.0f);
        aBuffer.Add(aX[1], aY[1], 0.0f, aEndU, aStartV, 1.0f);
    }
    
    if(aDrawCorner[2])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[1], aY[1], 0.0f, aEndU, aStartV, 1.0f);
        aBuffer.Add(aX[2], aY[2], 0.0f, aEndU, aEndV, 1.0f);
        
        
    }
    
    if(aDrawCorner[3])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[2], aY[2], 0.0f, aEndU, aEndV, 1.0f);
        aBuffer.Add(aX[3], aY[3], 0.0f, aStartU, aEndV, 1.0f);
    }
    
    aBuffer.mBindIndex = mBindIndex;
    aBuffer.DrawTriangles();
    
    
    SetColor(1.0f, 0.66f, 0.66f);
    
    DrawRect(aCenterX - 9, aCenterY - 9, 19, 19);
    
//    float aCenterX = pCenterOffsetX;
//    float aCenterY = pCenterOffsetY;
//    
//    
//    float aWidth2  = ((float)mWidth )/2.0f;
//    float aHeight2 = ((float)mHeight)/2.0f;
//    
//    aWidth2  = ((float)mWidth )/4.0f;
//    aHeight2 = ((float)mHeight)/4.0f;
    
    //float aStartU = mTextureCoord[0];
	//float aStartV = mTextureCoord[1];
    
    //float aEndU = mTextureCoord[6];
	//float aEndV = mTextureCoord[7];
    
    aStart = 3;
    aEnd = 0;
    
    while(aEnd < 4)
    {
        
        aLineStartX = aX[aStart];
        aLineStartY = aY[aStart];
        
        aLineEndX = aX[aEnd];
        aLineEndY = aY[aEnd];
        
        float aRed = 0.0f;
        if(aStart == aHitLine1)aRed = 1.0f;
        
        float aGreen = 0.0f;
        if(aStart == aHitLine2)aGreen = 1.0f;
        
        float aBlue = 0.5f;
        
        //aBuffer.Add(  )
        
        SetColor(aRed, aGreen, aBlue);
        DrawLine(aLineStartX, aLineStartY, aLineEndX, aLineEndY, 2.0f);
        
        aStart = aEnd;
        aEnd++;
        
    }
    
    
    SetColor(0.0f,0.0f,1.0f);
    DrawRect(aCenterX + aDirX1 * 100.0f - 3.0f, aCenterY +  aDirY1 * 100.0f - 3.0f, 7.0f, 7.0f);
    
    SetColor(0.66f,0.15f,0.0f);
    DrawRect(aCenterX + aDirX2 * 100.0f - 3.0f, aCenterY + aDirY2 * 100.0f - 3.0f, 7.0f, 7.0f);
}
 
*/

void Sprite::DrawRadial(float pCenterX, float pCenterY, float pStartRotation, float pEndRotation, float pCenterOffsetX, float pCenterOffsetY)
{
    
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
    
    
    float aStartU = mTextureCoord[0];
	float aStartV = mTextureCoord[1];
    float aEndU = mTextureCoord[6];
	float aEndV = mTextureCoord[7];
    
    float aCenterX = pCenterX + pCenterOffsetX;
    float aCenterY = pCenterY + pCenterOffsetY;
    
    float aWidth2  = ((float)mWidth) / 2.0f;
    float aHeight2 = ((float)mHeight) / 2.0f;
    
    float aX[4];
    float aY[4];
    
    float aURange = (aEndU - aStartU);
    float aVRange = (aEndV - aStartV);
    
    float aLeft = pCenterX - aWidth2;
    float aRight = pCenterX + aWidth2;
    
    float aTop = pCenterY - aHeight2;
    float aBottom = pCenterY + aHeight2;
    
    aX[0] = aLeft;
    aY[0] = aTop;
    
    aX[1] = aRight;
    aY[1] = aTop;
    
    aX[2] = aRight;
    aY[2] = aBottom;
    
    aX[3] = aLeft;
    aY[3] = aBottom;
    
    float aLineStartX, aLineStartY, aLineEndX, aLineEndY;
    
    float aLineDirX, aLineDirY;
    float aLineNormX, aLineNormY;
    float aDiffX, aDiffY;
    
    float aPlaneLength;
    
    float aDirX1 = Sin(pStartRotation);
    float aDirY1 = Cos(pStartRotation);
    
    float aDirX2 = Sin(pEndRotation);
    float aDirY2 = Cos(pEndRotation);
    
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
        
        aDiffX = (aLineStartX - aCenterX);
        aDiffY = (aLineStartY - aCenterY);
        
        aNumer = (aCenterX * aLineNormX + aCenterY * aLineNormY - (aLineNormX * aLineStartX + aLineNormY * aLineStartY));
        aDenom = (aDirX1 * aLineNormX + aDirY1 * aLineNormY);
        aCheckLength1 = -(aNumer / aDenom);
        
        if(aCheckLength1 > 0)
        {
            if(aCheckLength1 < aBestLength1)
            {
                aBestLength1 = aCheckLength1;
                aHitLine1 = aEnd;
            }
        }
        
        aDenom = (aDirX2 * aLineNormX + aDirY2 * aLineNormY);
        aCheckLength2 = -(aNumer / aDenom);
        
        if(aCheckLength2 > 0)
        {
            if(aCheckLength2 < aBestLength2)
            {
                aBestLength2 = aCheckLength2;
                aHitLine2 = aEnd;
            }
        }
        
        aStart = aEnd;
        aEnd++;
    }
    
    float aEdgeX1 = aCenterX + aDirX1 * aBestLength1;
    float aEdgeY1 = aCenterY + aDirY1 * aBestLength1;
    
    float aEdgeX2 = aCenterX + aDirX2 * aBestLength2;
    float aEdgeY2 = aCenterY + aDirY2 * aBestLength2;
    
    VertexBuffer aBuffer;
    
    float aPercentU = (aCenterX - aLeft) / mWidth;
    float aPercentV = (aCenterY - aTop) / mHeight;
    
    float aCenterU = aStartU + aPercentU * aURange;
    float aCenterV = aStartV + aPercentV * aVRange;
    
    float aZ = 0.0f;
    float aW = 0.0f;
    
    float aEdgeU, aEdgeV;
    
    bool aPeelRight = (pStartRotation > pEndRotation);
    
    float aEdgeU1 = aStartU + ((aEdgeX1 - aLeft) / mWidth) * aURange;
    float aEdgeV1 = aStartV + ((aEdgeY1 - aTop) / mHeight) * aVRange;
    float aEdgeU2 = aStartU + ((aEdgeX2 - aLeft) / mWidth) * aURange;
    float aEdgeV2 = aStartV + ((aEdgeY2 - aTop) / mHeight) * aVRange;
    
    bool aDrawCorner[4];
    
    aDrawCorner[0] = false;
    aDrawCorner[1] = false;
    aDrawCorner[2] = false;
    aDrawCorner[3] = false;
    
    if(aHitLine1 == aHitLine2)
    {
        if(aPeelRight == false)
        {
            
            if(aHitLine1 == 0)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aStartU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aStartU, aEdgeV2, aW);
            }
            else if(aHitLine1 == 1)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aStartV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aStartV, aW);
            }
            else if(aHitLine1 == 2)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEndU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEndU, aEdgeV2, aW);
            }
            else
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aEndV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aEndV, aW);
            }
        }
        else
        {
            //"LEFT"
            if(aHitLine1 == 0)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aStartU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aStartU, aEdgeV2, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                
                aDrawCorner[1] = true;
                aDrawCorner[2] = true;
                aDrawCorner[3] = true;
            }
            
            //"TOP"
            if(aHitLine1 == 1)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aStartV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aStartV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                //aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
                
                aDrawCorner[0] = true;
                aDrawCorner[2] = true;
                aDrawCorner[3] = true;
            }
            
            //RIGHT
            if(aHitLine1 == 2)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEndU, aEdgeV1, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEndU, aEdgeV2, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
                aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                
                aDrawCorner[0] = true;
                aDrawCorner[1] = true;
                aDrawCorner[3] = true;
            }
            
            //Bottom
            if(aHitLine1 == 3)
            {
                aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aEndV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                
                aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aEndV, aW);
                aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
                //aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
                aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
                
                aDrawCorner[0] = true;
                aDrawCorner[1] = true;
                aDrawCorner[2] = true;
            }   
        }
    }
    else
    {
        //Left
        if(aHitLine1 == 0)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aStartU, aEdgeV1, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
        }
        
        //"TOP"
        if(aHitLine1 == 1)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aStartV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
        }
        
        //RIGHT
        if(aHitLine1 == 2)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEndU, aEdgeV1, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
        }
        
        //Bottom
        if(aHitLine1 == 3)
        {
            aBuffer.Add(aEdgeX1, aEdgeY1, aZ, aEdgeU1, aEndV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
        }
        
        //Left
        if(aHitLine2 == 0)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aStartU, aEdgeV2, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[0], aY[0], aZ, aStartU, aStartV, aW);
        }
        //"TOP"
        if(aHitLine2 == 1)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aStartV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[1], aY[1], aZ, aEndU, aStartV, aW);
        }
        //RIGHT
        if(aHitLine2 == 2)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEndU, aEdgeV2, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[2], aY[2], aZ, aEndU, aEndV, aW);
        }
        //Bottom
        if(aHitLine2 == 3)
        {
            aBuffer.Add(aEdgeX2, aEdgeY2, aZ, aEdgeU2, aEndV, aW);
            aBuffer.Add(aCenterX, aCenterY, aZ, aCenterU, aCenterV, aW);
            aBuffer.Add(aX[3], aY[3], aZ, aStartU, aEndV, aW);
        }
        if(aHitLine1 == 0)
        {
            if(aHitLine2 == 2)aDrawCorner[3]=true;
            if(aHitLine2 == 1)
            {
                aDrawCorner[2]=true;
                aDrawCorner[3]=true;
            }
        }
        if(aHitLine1 == 1)
        {
            if(aHitLine2 == 3)aDrawCorner[0]=true;
            if(aHitLine2 == 2)
            {
                aDrawCorner[0]=true;
                aDrawCorner[3]=true;
            }
        }
        if(aHitLine1 == 2)
        {
            if(aHitLine2 == 0)
            {
                aDrawCorner[1]=true;
            }
            if(aHitLine2 == 3)
            {
                aDrawCorner[0]=true;
                aDrawCorner[1]=true;
            }
        }
        if(aHitLine1 == 3)
        {
            if(aHitLine2 == 1)aDrawCorner[2]=true;
            if(aHitLine2 == 0)
            {
                aDrawCorner[1]=true;
                aDrawCorner[2]=true;
            }
        } 
    }
    if(aDrawCorner[0])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[3], aY[3], 0.0f, aStartU, aEndV, 1.0f);
        aBuffer.Add(aX[0], aY[0], 0.0f, aStartU, aStartV, 1.0f);
    }
    if(aDrawCorner[1])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[0], aY[0], 0.0f, aStartU, aStartV, 1.0f);
        aBuffer.Add(aX[1], aY[1], 0.0f, aEndU, aStartV, 1.0f);
    }
    if(aDrawCorner[2])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[1], aY[1], 0.0f, aEndU, aStartV, 1.0f);
        aBuffer.Add(aX[2], aY[2], 0.0f, aEndU, aEndV, 1.0f);
    }
    if(aDrawCorner[3])
    {
        aBuffer.Add(aCenterX, aCenterY, 0.0f, aCenterU, aCenterV, 1.0f);
        aBuffer.Add(aX[2], aY[2], 0.0f, aEndU, aEndV, 1.0f);
        aBuffer.Add(aX[3], aY[3], 0.0f, aStartU, aEndV, 1.0f);
    }
    
    aBuffer.mBindIndex = mBindIndex;
    aBuffer.DrawTriangles();
}

void Sprite::DrawStretchedV(float x, float y, float pHeight)
{
	mTextureVertex[0]=0;
	mTextureVertex[1]=0;
	mTextureVertex[2]=mWidth;
	mTextureVertex[3]=0;
	mTextureVertex[4]=0;
	mTextureVertex[5]=pHeight;
	mTextureVertex[6]=mWidth;
	mTextureVertex[7]=pHeight;
	
	glPushMatrix();
	Translate(x,y);
	Draw();
	glPopMatrix();
}


void Sprite::DrawStretchedH(float x, float y, float pWidth)
{
	mTextureVertex[0]=0;
	mTextureVertex[1]=0;
	mTextureVertex[2]=pWidth;
	mTextureVertex[3]=0;
	mTextureVertex[4]=0;
	mTextureVertex[5]=mHeight;
	mTextureVertex[6]=pWidth;
	mTextureVertex[7]=mHeight;
	
	glPushMatrix();
	Translate(x,y);
	Draw();
	glPopMatrix();
}

void Sprite::DrawExtended(FPoint pPosition, FPoint pTranslate, float pScale, float pRotation, int pFlipMode)
{
    glPushMatrix();
	
	Translate(pPosition);
    
	if(pFlipMode == -1)
	{
		glScalef(-pScale, pScale, pScale);
		
	}
	else
	{
		glScalef(pScale, pScale, pScale);
	}
    
	Translate(pTranslate);
	Rotate(pRotation);
    
	Draw();
	glPopMatrix();
}

void Sprite::DrawExtended(FPoint pOrigin, FPoint pTranslate, FPoint pCenter, float pRotationAboutOrigin, float pRotationAboutCenter, float pScale, bool pFlip)
{
	glPushMatrix();
	
	Translate(pOrigin);
	Rotate(pRotationAboutOrigin);
	
	if(pFlip)
	{
		glScalef(-pScale, pScale, pScale);
		
	}
	else
	{
		glScalef(pScale, pScale, pScale);
	}
	
	Translate(pTranslate);
	Rotate(pRotationAboutCenter);
	
	FPoint aCenter=FPoint(mTextureVertex[6],mTextureVertex[7]);
	FPoint aShift=aCenter-pCenter;
	Translate(aShift);

	Draw();
	glPopMatrix();
}

void Sprite::CenterRotated(float x, float y, float pRotationDegrees)
{
    gGraphics.DrawSprite(x, y, 1.0f, 1.0f, 1.0f, pRotationDegrees, mTextureVertex, mTextureCoord, mBindIndex);
}

void Sprite::Draw(float x, float y, float pScale, float pRotationDegrees)
{
    gGraphics.DrawSprite(x, y, pScale, pScale, 1.0f, pRotationDegrees, mTextureVertex, mTextureCoord, mBindIndex);
}

void Sprite::Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing)
{
    if(pFacing < 1)DrawFlippedH(x, y, pScale, pRotationDegrees);
    else Draw(x, y, pScale, pRotationDegrees);
}

void Sprite::Center(float x, float y, int pFacing)
{
    gGraphics.DrawSprite(x, y, pFacing<0 ? (-1.f) : (1.0f) , 1.0f, 1.0f, 0.0f, mTextureVertex, mTextureCoord, mBindIndex);
}

void Sprite::DrawFlippedH(float x, float y)
{
    gGraphics.DrawSprite(x + mWidth/2.0f, y + mHeight/2.0f, -1.0f, 1.0f, 1.0f, 0.0f, mTextureVertex, mTextureCoord, mBindIndex);
}

void Sprite::DrawFlippedH(float x, float y, float pScale, float pRotationDegrees)
{
    gGraphics.DrawSprite(x, y, -pScale, pScale, 1.0f, pRotationDegrees, mTextureVertex, mTextureCoord, mBindIndex);
}

void Sprite::DrawFlippedV(float x, float y)
{
    
}

void Sprite::DrawFlippedV(float x, float y, float pScale, float pRotationDegrees)
{
    
}


void Sprite::Draw()
{
    
    gGraphics.DrawSprite(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, mTextureVertex, mTextureCoord, mBindIndex);
    
	/*
	if(mBindIndex==-1)
	{
		
		if(mInlineImage)
		{
			//printf("Inline Image! %s\n", mInlineImage->mPath.c());
			Load(mInlineImage);
		}
		
		//printf("Bind Index = %d Delete: %d Imag: %d\n", mBindIndex, mDeleteImage, mImage);
		if(mImage)
		{
			//printf("Regimage: %s\n", mImage->mPath.c());
			if(mImage->mBindIndex==-1)mImage->Bind();
			if(mImage->mBindIndex!=-1)
			{
				mBindIndex=mImage->mBindIndex;
				gApp->AddBind(mBindIndex);
				//if(mDeleteImage)
				//{
				//	mDeleteImage=false;
				//	delete mImage;
				//	mImage=0;
				//}
			}
		}
	}
	*/
	
	//glEnable( GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, mBindIndex);
	//glVertexPointer(2,GL_FLOAT,0,mTextureVertex);
	//glTexCoordPointer(2,GL_FLOAT,0,mTextureCoord);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glDisable( GL_TEXTURE_2D);
    
    
    /*
    mTextureCoord[0]=aStartU;
    mTextureCoord[1]=aStartV;
    mTextureCoord[2]=aEndU;
    mTextureCoord[3]=aStartV;
    mTextureCoord[4]=aStartU;
    mTextureCoord[5]=aEndV;
    mTextureCoord[6]=aEndU;
    mTextureCoord[7]=aEndV;
    
    
    mTextureVertex[0]=aLeft;
    mTextureVertex[1]=aTop;
    mTextureVertex[2]=aRight;
    mTextureVertex[3]=aTop;
    mTextureVertex[4]=aLeft;
    mTextureVertex[5]=aBottom;
    mTextureVertex[6]=aRight;
    mTextureVertex[7]=aBottom;
    */
    
    
    //DrawRect(mTextureVertex[0],mTextureVertex[1],3,3);
    //DrawRect(mTextureVertex[2],mTextureVertex[3],3,3);
    //DrawRect(mTextureVertex[4],mTextureVertex[5],3,3);
    //DrawRect(mTextureVertex[6],mTextureVertex[7],3,3);
    
}

void Sprite::DrawPercentH(float x, float y, float pStartPercent, float pEndPercent)
{
	glPushMatrix();
	Translate(x+mWidth/2,y+mHeight/2);
	DrawPercentH(pStartPercent, pEndPercent);
	glPopMatrix();
}

void Sprite::DrawPercentV(float x, float y, float pStartPercent, float pEndPercent)
{
	glPushMatrix();
	Translate(x+mWidth/2,y+mHeight/2);
	DrawPercentV(pStartPercent, pEndPercent);
	glPopMatrix();
}

void Sprite::DrawPercentH(float pStartPercent, float pEndPercent)
{
	float aTex[8];
	float aVer[8];
	
	float aWidth=mTextureVertex[2] - mTextureVertex[0];
	float aTexWidth=mTextureCoord[2] - mTextureCoord[0];
	
	aTex[0] = mTextureCoord[0] + aTexWidth * pStartPercent;
	aTex[1] = mTextureCoord[1];
	aTex[2] = mTextureCoord[0] + aTexWidth * pEndPercent;
	aTex[3] = mTextureCoord[3];
	aTex[4] = mTextureCoord[0] + aTexWidth * pStartPercent;
	aTex[5] = mTextureCoord[5];
	aTex[6] = mTextureCoord[0] + aTexWidth * pEndPercent;
	aTex[7] = mTextureCoord[7];
	
	aVer[0] = mTextureVertex[0] + aWidth * pStartPercent;
	aVer[1] = mTextureVertex[1];
	aVer[2] = mTextureVertex[0] + aWidth * pEndPercent;
	aVer[3] = mTextureVertex[3];
	aVer[4] = mTextureVertex[0] + aWidth * pStartPercent;
	aVer[5] = mTextureVertex[5];
	aVer[6] = mTextureVertex[0] + aWidth * pEndPercent;
	aVer[7] = mTextureVertex[7];
	
	
	

	glEnable( GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mBindIndex);
	glVertexPointer(2,GL_FLOAT,0,aVer);
	glTexCoordPointer(2,GL_FLOAT,0,aTex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable( GL_TEXTURE_2D);
}


void Sprite::DrawPercentV(float pStartPercent, float pEndPercent)
{
	float aTex[8];
	float aVer[8];
	
	float aHeight=mTextureVertex[5] - mTextureVertex[1];
	float aTexHeight=mTextureCoord[5] - mTextureCoord[1];
	
	//
	
	aTex[0] = mTextureCoord[0];
	aTex[1] = mTextureCoord[5]-aTexHeight*pEndPercent;
	aTex[2] = mTextureCoord[2];
	aTex[3] = mTextureCoord[5]-aTexHeight*pEndPercent;
	aTex[4] = mTextureCoord[4];
	aTex[5] = mTextureCoord[5]-aTexHeight*pStartPercent;
	aTex[6] = mTextureCoord[6];
	aTex[7] = mTextureCoord[5]-aTexHeight*pStartPercent;
	
	aVer[0] = mTextureVertex[0];
	aVer[1] = mTextureVertex[5]-aHeight*pEndPercent;
	aVer[2] = mTextureVertex[2];
	aVer[3] = mTextureVertex[5]-aHeight*pEndPercent;
	aVer[4] = mTextureVertex[4];
	aVer[5] = mTextureVertex[5]-aHeight*pStartPercent;
	aVer[6] = mTextureVertex[6];
	aVer[7] = mTextureVertex[5]-aHeight*pStartPercent;
	
	glEnable( GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mBindIndex);
	glVertexPointer(2,GL_FLOAT,0,aVer);
	glTexCoordPointer(2,GL_FLOAT,0,aTex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable( GL_TEXTURE_2D);
}



SpriteStrip::SpriteStrip()
{
	mSprite=0;
	mSpriteCount=0;
}

SpriteStrip::~SpriteStrip()
{
	Kill();
}

void SpriteStrip::Kill()
{
	if(mSpriteCount)
	{
		for(int i=0;i<mSpriteCount;i++)
		{
			delete mSprite[i];
		}
		delete[]mSprite;
		mSprite=0;
		mSpriteCount=0;
	}
}



void SpriteStrip::Load(char *pFile, int pCount, bool pVertical)
{
	Kill();
	Image aImage;
	aImage.Load(pFile);
	if(aImage.mWidth<=0||aImage.mHeight<=0)return;
	if(!pVertical)
	{
		if(aImage.mWidth>=pCount&&pCount>0)
		{
			int aX=0;
			int aCellWidth=aImage.mWidth/pCount;
			mSprite=new Sprite*[pCount];
			for(int i=0;i<pCount;i++)
			{
				mSprite[i]=new Sprite();
				mSprite[i]->Load(&aImage,aX,0,aCellWidth,aImage.mHeight);
				aX+=aCellWidth;
			}
			mSpriteCount=pCount;
		}
	}
	else
	{
		
	}
}


