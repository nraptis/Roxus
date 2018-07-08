/*
 *  Model.cpp
 *  SteakNinja
 *
 *  Created by Nick Raptis on 9/14/10.
 *  Copyright 2010 Raptisoft LLC. All rights reserved.
 *
 */

#include "Model.h"
#include "stdafx.h"
#include "ModelUtilities.h"

Model::Model()
{
    mBindSprite=0;

    mData=0;
    
	mBindIndex=-1;
    
	mRotationX=0.0f;
	mRotationY=0.0f;
	mRotationZ=0.0f;
	
    mRotation=0;
    
    mCentroidIsComputed=false;
    
    mCentroidX=0.0f;
    mCentroidY=0.0f;
    mCentroidZ=0.0f;
    
    mRotateSingleAxis=false;
    
	mX=0;
	mY=0;
	mZ=0;
    
    mScale=1;
}

Model::Model(ModelDataIndexed *pData, Sprite *pSprite) : Model()
{
    Load(pData, pSprite);
}

Model::~Model()
{
	Free();
	//delete[]mSpriteBind;mSpriteBind=0;
	//mSpriteBindCount=0;
}

void Model::Free()
{
    delete mData;
    mData=0;
	mBindIndex=-1;
}

void Model::Load(const char *pFileName)
{
    Free();
    
    mName = pFileName;
    mName.RemovePath(true);
    
    mData = LoadOBJIndexed(pFileName);
}

void Model::Draw()
{
    
    Graphics::MatrixPush();
    Graphics::Translate(mX,mY,mZ);
    Graphics::Scale(mScale);
    
    if(mRotateSingleAxis)
    {
        Graphics::Rotate(mRotation,mRotationX,mRotationY,mRotationZ);
    }
    else
    {
        Graphics::Rotate(mRotationX,mRotationY,mRotationZ);
    }
    
    DrawBase();
    Graphics::MatrixPop();
}

void Model::DrawBase()
{
    if(mData)
    {
        if((mBindIndex == -1) && (mBindSprite != 0))
        {
            mBindIndex = mBindSprite->mBindIndex;
        }
        mData->Draw(mBindIndex);
    }
}


void Model::SetAffine(float pTranslationX, float pTranslationY, float pTranslationZ, float pScale, float pRotationX, float pRotationY, float pRotationZ, float pRotationAmount)
{
    mX=pTranslationX;
    mY=pTranslationY;
    mZ=pTranslationZ;
    
    mScale=pScale;
    
    mRotationX=pRotationX;
    mRotationY=pRotationY;
    mRotationZ=pRotationZ;
    
    mRotation=pRotationAmount;
}


/*
int Model::StringGetFloats(char *pString, int pLength, char *pBuffer, float *pArray, int pFetchCount)
{
    int aReturnCount=0;
    
    char *aEnd=&(pString[pLength]);
    char *aSeek=pString;
    char *aCheck;
    
    int aWriteIndex;
    
    while(aReturnCount < pFetchCount && (aSeek < aEnd))
    {
        //go until we find a number..
        
        while(aSeek < aEnd)
        {
            if((*aSeek >= '0' && *aSeek <= '9') || (*aSeek == '.'))
            {
                //Check for minus sign
                aWriteIndex=0;
                
                if(aSeek > pString)
                {
                    //TODO: Make this skip back past white-space.
                    if(*(aSeek-1)=='-')
                    {
                        pBuffer[aWriteIndex++]='-';
                    }
                }
                while(((*aSeek >= '0' && *aSeek <= '9') || (*aSeek == '.')) && (aSeek < aEnd))
                {
                    pBuffer[aWriteIndex++]=*aSeek;
                    aSeek++;
                }
                pBuffer[aWriteIndex]=0;
                pArray[aReturnCount] = atof(pBuffer);
                aReturnCount++;
                break;
            }
            else
            {
                aSeek++;
            }
        }
    }
    return aReturnCount;
}
*/

void Model::Load(ModelDataIndexed *pData, Sprite *pSprite)
{
    if(pData)
    {
        mData = pData;
    }
    
    if(pSprite)
    {
        mBindSprite = pSprite;
        mBindIndex = pSprite->mBindIndex;
    }
}

void Model::FixUVW(Sprite *pSprite)
{
    /*
    if(pSprite == 0)pSprite=mBindSprite;
    if(mBindSprite == 0)mBindSprite=pSprite;
    
    float aStartU = pSprite->GetStartU();
    float aStartV = pSprite->GetStartV();
    float aEndU = pSprite->GetEndU();
    float aEndV = pSprite->GetEndV();
    
    if(aStartU == 0 && aEndU == 1 && aStartV == 0 && aEndV == 1)
    {
        
    }
    else
    {
        if(mUVW == 0)
        {
            
        }
        else
        {
            int aCount = mNodeCount;
            if(mIndexCount != 0)aCount = mIndexCount;
            
            float aSpanU = aEndU - aStartU;
            float aSpanV = aEndV - aStartV;
            
            int aIndex = 0;
            float aU, aV, aW;
            for(int i=0;i<aCount;i++)
            {
                aIndex = i * 3;
                
                aU = mUVW[aIndex];
                aV = mUVW[aIndex+1];
                
                printf("UVW Was [%f %f]\n", aU, aV);
                
                aU = (aStartU + aSpanU * aU);
                aV = (aStartV + aSpanV * aV);
                
                printf("UVW Now [%f %f]\n", aU, aV);
                
                mUVW[aIndex] = aU;
                mUVW[aIndex] = aV;
                
                
            }
        }
    }
    */
}

Vector3 Model::GetCentroidRotated()//bool pPrint)
{	
	Vector3 aCentroid=GetCentroid();
	Vector3 aDir=Vector3(mRotationX,mRotationY,mRotationZ);
	
	float aLength = aDir.Length();
	
	if(aLength > 0.015f)
	{
		aDir /= aLength;
	}
	else
	{
		aDir.mX=1;
		aDir.mY=0;
		aDir.mZ=0;
	}
	
	float aDirX=aDir.mX;
	float aDirY=aDir.mY;
	float aDirZ=aDir.mZ;
	
	float aX=aCentroid.mX;
	float aY=aCentroid.mY;
	float aZ=aCentroid.mZ;
	
	float aCos = Cos(mRotation);
	float aSin = Sin(mRotation);
	float aCosInv=1-aCos;
	
	float xy = aDirX*aDirY*aCosInv;
	float xz = aDirX*aDirZ*aCosInv;
	float yz = aDirY*aDirZ*aCosInv;
	
	float xs = aDirX*aSin;
	float ys = aDirY*aSin;
	float zs = aDirZ*aSin;
	
	aCentroid.mX = (aDirX*aDirX*aCosInv+aCos) * aX + (xy-zs) * aY + (xz+ys) * aZ;
	aCentroid.mY = (xy+zs) * aX + (aDirY*aDirY*aCosInv+aCos) * aY + (yz-xs) * aZ;
	aCentroid.mZ = (xz+ys) * aX + (yz-xs) * aY + (aDirZ*aDirZ*aCosInv+aCos) * aZ;
	
	return aCentroid;
}

Vector3 Model::GetCentroid()
{
    if(mCentroidIsComputed)
    {
        return Vector3(mCentroidX, mCentroidY, mCentroidZ);
    }
    
    if(mData)
    {
        mData->GetCentroid(mCentroidX, mCentroidY, mCentroidZ);
        mCentroidIsComputed=true;
    }
    
	return Vector3(mCentroidX,mCentroidY,mCentroidZ);
}

/*




void Model::PrintSetupCode()
{
    
    
    printf("Free();\nmNodeCount=%d;\nmIndexCount=%d;\n\n", mNodeCount, mIndexCount);
    
    printf("int aNodeSize=mNodeCount*3;\n");
    
    printf("float *aNew = new float[aNodeSize * 3 + 3];\n");
    
    printf("mXYZ = &(aNew[aNodeSize*0]);\nmUVW = &(aNew[aNodeSize*1]);\nmNormal = &(aNew[aNodeSize*2]);\n\n");
    
    int aNodeCount=mNodeCount*3;
    
    for(int i=0;i<aNodeCount;i++)
    {
        printf("mXYZ[%d]=%f;", i, mXYZ[i]);
        if(i % 10 == 9)printf("\n");
    }
    
    for(int i=0;i<aNodeCount;i++)
    {
        printf("mUVW[%d]=%f;", i, mUVW[i]);
        if(i % 10 == 9)printf("\n");
    }
    
    for(int i=0;i<aNodeCount;i++)
    {
        printf("mNormal[%d]=%f;", i, mNormal[i]);
        if(i % 10 == 9)printf("\n");
    }
    
    printf("\n\n");
    
    if((mIndexCount > 0) && (mIndex != 0))
    {
        printf("mIndex = new unsigned int[%d];\n", mIndexCount);
        
        
        for(int i=0;i<mIndexCount;i++)
        {
            if(i % 10 == 0)printf("\n");
            printf("mIndex[%d]=%d;", i, mIndex[i]);
        }
    }
    
    printf("\n");
}

void Model::Print()
{
	printf("___ BEGIN 3D MODEL ___\n");
	
	printf("VERTEX COUNT: %d\n", mNodeCount);
	
	printf("Vertices:\n");
	
    if(mXYZ)
    {
	for(int i=0;i<mNodeCount;i++)
	{
		printf("V %d \t\t = (%3.2f, %3.2f, %3.2f)\n", i, mXYZ[i*3], mXYZ[i*3+1], mXYZ[i*3+2]);
	}
    }
	printf("\n\n~~~\n\n");
	
    if(mUVW)
    {
	for(int i=0;i<mNodeCount;i++)
	{
		printf("T %d \t\t = (%3.2f, %3.2f, %3.2f)\n", i, mUVW[i*3], mUVW[i*3+1], mUVW[i*3+2]);
	}
    }
    
    printf("\n\n~~~\n\n");
    
    if(mNormal)
    {
        for(int i=0;i<mNodeCount;i++)
        {
            printf("N %d \t\t = (%3.2f, %3.2f, %3.2f)\n", i, mNormal[i*3], mNormal[i*3+1], mNormal[i*3+2]);
        }
    }
    
	printf("___ END 3D MODEL ___\n");
}
*/




