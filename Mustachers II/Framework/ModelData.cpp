//
//  ModelData.cpp
//  Chrysler300ReLoadDataed
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "stdafx.h"
#include "ModelData.h"
#include "ModelUtilities.h"

ModelData::ModelData()
{
    mBindIndex=-1;
    mXYZ=0;mUVW=0;mNormal=0;
    mXYZCount=0;mXYZSize=0;
    mUVWCount=0;mUVWSize=0;
    mNormalCount=0;mNormalSize=0;
}

ModelData::~ModelData()
{
    Free();
}

void ModelData::Free()
{
    DiscardXYZ();
    DiscardUVW();
    DiscardNormal();
}

void ModelData::DiscardXYZ()
{
    delete[]mXYZ;
    mXYZ=0;
    mXYZCount=0;
    mXYZSize=0;
}

void ModelData::DiscardUVW()
{
    delete[]mUVW;
    mUVW=0;
    mUVWCount=0;
    mUVWSize=0;
}

void ModelData::DiscardNormal()
{
    delete[]mNormal;
    mNormal=0;
    mNormalCount=0;
    mNormalSize=0;
}

float *ModelData::ResizeTriple(float *pData, int pCount, int pSize)
{
    int aDataSize = (pSize * 3);
    int aDataCount = (pCount * 3);
    
    float *aNew = new float[aDataSize+1];
    for(int i=0;i<aDataCount;i++)
    {
        aNew[i] = pData[i];
    }
    for(int i=aDataCount;i<aDataSize;i++)
    {
        aNew[i] = 0;
    }
    delete[]pData;
    
    return aNew;
}

void ModelData::SetTriple(unsigned int pIndex, float *pArray, float pValue1, float pValue2, float pValue3)
{
    unsigned int aIndex = pIndex * 3;
    pArray[aIndex]=pValue1;
    pArray[aIndex+1]=pValue2;
    pArray[aIndex+2]=pValue3;
}

void ModelData::AddXYZ(float pX, float pY, float pZ)
{
    if(mXYZCount >= mXYZSize)SizeXYZ(mXYZCount + mXYZCount / 2 + 1);
    SetTriple(mXYZCount, mXYZ, pX, pY, pZ);
    mXYZCount++;
}

void ModelData::SizeXYZ(int pSize)
{
    if(pSize != 0)mXYZ = ResizeTriple(mXYZ, mXYZCount, pSize);
    mXYZSize = pSize;
}

void ModelData::AddUVW(float pU, float pV, float pW)
{
    if(mUVWCount >= mUVWSize)SizeUVW(mUVWCount + mUVWCount / 2 + 1);
    SetTriple(mUVWCount, mUVW, pU, pV, pW);
    mUVWCount++;
}

void ModelData::SizeUVW(int pSize)
{
    if(pSize != 0)mUVW = ResizeTriple(mUVW, mUVWCount, pSize);
    mUVWSize = pSize;
}

void ModelData::AddNormal(float pNormX, float pNormY, float pNormZ)
{
    if(mNormalCount >= mNormalSize)SizeNormal(mNormalCount + mNormalCount / 2 + 1);
    SetTriple(mNormalCount, mNormal, pNormX, pNormY, pNormZ);
    mNormalCount++;
}

void ModelData::SizeNormal(int pSize)
{
    if(pSize != 0)mNormal = ResizeTriple(mNormal, mNormalCount, pSize);
    mNormalSize = pSize;
}

float ModelData::GetX(int pIndex)
{
    //if(pIndex>=0 && pIndex<mXYZCount)
    return mXYZ[pIndex*3];
    //printf("Error Fetching X [%d / %d]\n", pIndex, mXYZCount);
    //return 0;
}

float ModelData::GetY(int pIndex)
{
    //if(pIndex>=0 && pIndex<mXYZCount)
    return mXYZ[pIndex*3+1];
    //return 0;
}

float ModelData::GetZ(int pIndex)
{
    //if(pIndex>=0 && pIndex<mXYZCount)
    return mXYZ[pIndex*3+2];
    //return 0;
}


float ModelData::GetU(int pIndex)
{
    //if(pIndex>=0 && pIndex<mUVWCount)
    return mUVW[pIndex*3];
    //return 0;
}

float ModelData::GetV(int pIndex)
{
    //if(pIndex>=0 && pIndex<mUVWCount)
    return mUVW[pIndex*3+1];
    //return 0;
}

float ModelData::GetW(int pIndex)
{
    //if(pIndex>=0 && pIndex<mUVWCount)
    return mUVW[pIndex*3+2];
    //return 0;
}

float ModelData::GetNormX(int pIndex)
{
    //if(pIndex>=0 && pIndex<mNormalCount)
    return mNormal[pIndex*3];
    //return 0;
}

float ModelData::GetNormY(int pIndex)
{
    //if(pIndex>=0 && pIndex<mNormalCount)
    return mNormal[pIndex*3+1];
    //return 0;
}

float ModelData::GetNormZ(int pIndex)
{
    //if(pIndex>=0 && pIndex<mNormalCount)
    return mNormal[pIndex*3+2];
    //return 0;
}

void ModelData::InvertU()
{
    int aCount = mUVWCount * 3;
    for(int i=0;i<aCount;i+=3)mUVW[i]=(1-mUVW[i]);
}

void ModelData::InvertV()
{
    int aCount = mUVWCount * 3;
    for(int i=1;i<aCount;i+=3)mUVW[i]=(1-mUVW[i]);
}

void ModelData::InvertW()
{
    int aCount = mUVWCount * 3;
    for(int i=2;i<aCount;i+=3)mUVW[i]=(1-mUVW[i]);
}

void ModelData::FlipXY()
{
    
    float aHold=0;
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold=mXYZ[i];
        mXYZ[i]=mXYZ[i+1];
        mXYZ[i+1]=aHold;
    }
    
    aCount = mNormalCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold=mNormal[i];
        mNormal[i]=mNormal[i+1];
        mNormal[i+1]=aHold;
    }
}

void ModelData::FlipYZ()
{
    float aHold=0;
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold=mXYZ[i+1];
        mXYZ[i+1]=mXYZ[i+2];
        mXYZ[i+2]=aHold;
    }
    
    aCount = mNormalCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold=mNormal[i];
        mNormal[i]=-mNormal[i+2];
        mNormal[i+2]=aHold;
    }
}

void ModelData::FlipZX()
{
    float aHold=0;
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold=mXYZ[i];
        mXYZ[i]=mXYZ[i+2];
        mXYZ[i+2]=aHold;
    }
    
    aCount = mNormalCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold= mNormal[i];
        mNormal[i]=mNormal[i+2];
        mNormal[i+2]=aHold;
    }
}


void ModelData::NegateX()
{
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        mXYZ[i] = (-mXYZ[i]);
    }
}

void ModelData::NegateY()
{
    int aCount = mXYZCount * 3;
    for(int i=1;i<aCount;i+=3)
    {
        mXYZ[i] = (-mXYZ[i]);
    }
}

void ModelData::NegateZ()
{
    int aCount = mXYZCount * 3;
    for(int i=2;i<aCount;i+=3)
    {
        mXYZ[i] = (-mXYZ[i]);
    }
}


void ModelData::SetSprite(Sprite *pSprite, bool pFixUVW)
{
    
    if(pSprite)
    {
        
        mBindIndex = pSprite->mBindIndex;
        
        if(pFixUVW)
        {
            
            
             float aStartU = pSprite->GetStartU();
             float aStartV = pSprite->GetStartV();
             
             float aEndU = pSprite->GetEndU();
             float aEndV = pSprite->GetEndV();
            
            
            /*
            float aStartU = 0.0f;
            float aStartV = 0.0f;
            
            float aEndU = 1.0f;
            float aEndV = 1.0f;
            
            if(pSprite->mBundlerNode)
            {
                printf("BUNDLE NODE!!!");
                
                float aBundleWidth = pSprite->mBundlerNode->mBundleWidth;
                float aBundleHeight = pSprite->mBundlerNode->mBundleHeight;
                
                float aBundleStartX = pSprite->mBundlerNode->mX - pSprite->mBundlerNode->mOffsetX;
                float aBundleStartY = pSprite->mBundlerNode->mY - pSprite->mBundlerNode->mOffsetY;
                
                
                float aBundleEndX = aBundleStartX + pSprite->mBundlerNode->mOriginalWidth;
                float aBundleEndY = aBundleStartY + pSprite->mBundlerNode->mOriginalHeight;
                
                aStartU = aBundleStartX / aBundleWidth;
                aStartV = aBundleStartY / aBundleHeight;
                
                aEndU = aBundleEndX / aBundleWidth;
                aEndV = aBundleEndY / aBundleHeight;
                
                
            }
            
            float aStartU = 0.0f;
            float aStartV = 0.0f;
            
            float aEndU = 1.0f;
            float aEndV = 1.0f;
             
            */
            
            FitUVW(aStartU, aEndU, aStartV, aEndV);
            
            //printf("\n\nUVW Fitting TO: [%f %f %f %f]\n\n", aStartU, aEndU, aStartV, aEndV);
            //printf("\n...\n");
        }
    }
    
}

void ModelData::FitUVW(float pStartU, float pEndU, float pStartV, float pEndV)
{
    //float aRangeU = pMaxU - pMinU;
    
    if((pStartU == 0) && (pStartV == 0) && (pEndU == 1) && (pEndV == 1))
    {
        return;
    }
    
    if(mUVWCount <= 0)return;
    
    float aSpanU = pEndU - pStartU;
    float aSpanV = pEndV - pStartV;
    
    int aIndex = 0;
    float aU, aV;
    for(int i=0;i<mUVWCount;i++)
    {
        aIndex = i * 3;
        
        aU = mUVW[aIndex];
        aV = mUVW[aIndex+1];
        
        //printf("UVW Was [%f %f]\n", aU, aV);
        
        aU = (pStartU + aSpanU * aU);
        aV = (pStartV + aSpanV * aV);
        
        //printf("UVW Now [%f %f]\n", aU, aV);
        
        mUVW[aIndex] = aU;
        mUVW[aIndex+1] = aV;
        
        
    }    
    
    /*
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
            
            
        }
    }
     
    */
}


void ModelData::CopyXYZ(float *pXYZ, int pCount)
{
    delete[]mXYZ;
    mXYZCount=0;
    mXYZSize=0;
    if((pXYZ!=0) && (pCount>0))
    {
        SizeXYZ(pCount);
        int aCount3 = (pCount * 3);
        mXYZ = new float[aCount3];
        for(int i=0;i<aCount3;i++)mXYZ[i] = pXYZ[i];
        mXYZCount = pCount;
    }
}

void ModelData::CopyUVW(float *pUVW, int pCount)
{
    delete[]mUVW;
    mUVWCount=0;
    mUVWSize=0;
    if((pUVW!=0) && (pCount>0))
    {
        SizeUVW(pCount);
        int aCount3 = (pCount * 3);
        mUVW = new float[aCount3];
        for(int i=0;i<aCount3;i++)mUVW[i] = pUVW[i];
        mUVWCount = pCount;
    }
}

void ModelData::CopyNorm(float *pNorm, int pCount)
{
    delete[]mNormal;
    mNormalCount=0;
    mNormalSize=0;
    if((pNorm!=0) && (pCount>0))
    {
        SizeNormal(pCount);
        int aCount3 = (pCount * 3);
        mNormal = new float[aCount3];
        for(int i=0;i<aCount3;i++)mNormal[i] = pNorm[i];
        mNormalCount = pCount;
    }
}

ModelData *ModelData::Clone()
{
    ModelData *aClone=new ModelData();
    aClone->CopyXYZ(mXYZ, mXYZCount);
    aClone->CopyUVW(mUVW, mUVWCount);
    aClone->CopyNorm(mNormal, mNormalCount);
    return aClone;
}

void ModelData::Print()
{
    
}

void ModelData::Save(const char *pFile)
{
    Buffer aBuffer;
    Save(&aBuffer);
    aBuffer.Save(pFile);
}

void ModelData::Save(Buffer *pBuffer)
{
    if(!pBuffer)return;
    
    pBuffer->WriteInt(mXYZCount);
    pBuffer->WriteInt(mUVWCount);
    pBuffer->WriteInt(mNormalCount);
    
    int aXYZCount = mXYZCount * 3;
    int aUVWCount = mUVWCount * 3;
    int aNormalCount = mNormalCount * 3;
    
    for(int i=0;i<aXYZCount;i++)pBuffer->WriteFloat(mXYZ[i]);
    for(int i=0;i<aUVWCount;i++)pBuffer->WriteFloat(mUVW[i]);
    for(int i=0;i<aNormalCount;i++)pBuffer->WriteFloat(mNormal[i]);
}

void ModelData::LoadData(Buffer *pBuffer)
{
    if(!pBuffer)return;
    
    int aXYZCount=pBuffer->ReadInt();
    int aUVWCount=pBuffer->ReadInt();
    int aNormalCount=pBuffer->ReadInt();
    
    DiscardXYZ();
    DiscardUVW();
    DiscardNormal();
    
    //mXYZCount=0;
    //mUVWCount=0;
    //mNormalCount=0;
    
    SizeXYZ(aXYZCount);
    SizeUVW(aUVWCount);
    SizeNormal(aNormalCount);
    
    mXYZCount=aXYZCount;
    mUVWCount=aUVWCount;
    mNormalCount=aNormalCount;
    
    aXYZCount *= 3;
    aUVWCount *= 3;
    aNormalCount *= 3;
    
    for(int i=0;i<aXYZCount;i++)mXYZ[i] = pBuffer->ReadFloat();
    for(int i=0;i<aUVWCount;i++)mUVW[i] = pBuffer->ReadFloat();
    for(int i=0;i<aNormalCount;i++)mNormal[i] = pBuffer->ReadFloat();
}

void ModelData::LoadData(const char *pFile)
{
    printf("LoadDataingModelData[%s]\n", pFile);
    Buffer aBuffer;
    aBuffer.Load(pFile);
    LoadData(&aBuffer);
}

void ModelData::GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ)
{
    pCentroidX=0.0f;
    pCentroidY=0.0f;
    pCentroidZ=0.0f;
    
    int aCap = mXYZCount * 3;
    
    for(int i=0;i<aCap;)
    {
        pCentroidX += mXYZ[i++];
        pCentroidY += mXYZ[i++];
        pCentroidZ += mXYZ[i++];
    }
    
    if(mXYZCount > 1)
    {
        pCentroidX /= (float)mXYZCount;
        pCentroidY /= (float)mXYZCount;
        pCentroidZ /= (float)mXYZCount;
    }
}

void ModelData::PrintOverview()
{
    printf("ModelDataOverview: XYZ(%d/%d) UVW(%d/%d) NORM(%d/%d)\n", mXYZCount, mXYZSize, mUVWCount, mUVWSize, mNormalCount, mNormalSize);
}

void ModelData::DrawEfficientSetup()
{
    Graphics::DrawModelEfficientSetup(mXYZ, mUVW, mNormal, mBindIndex);
}

void ModelData::DrawEfficient()
{
    Graphics::DrawTriangles(mXYZCount);
}

void ModelData::Draw()
{
    Graphics::DrawModel(mXYZ,mUVW,mNormal,mXYZCount,mBindIndex);
}

void ModelData::Draw(int pBindIndex)
{
    Graphics::DrawModel(mXYZ,mUVW,mNormal,mXYZCount,pBindIndex);
}

//////////////////////////////////////////
//////////////////////////////////////////
////                                  ////
////                                  ////
////         Indexed Version          ////
////                                  ////
////                                  ////
//////////////////////////////////////////
//////////////////////////////////////////

ModelDataIndexed::ModelDataIndexed() : ModelData()
{
    
    mUVWShifted=0;
    
    mIndex=0;
    mIndexCount=0;
    mIndexSize=0;
}

ModelDataIndexed::~ModelDataIndexed()
{
    Free();
}

void ModelDataIndexed::Free()
{
    ModelData::Free();
    
    delete[]mIndex;
    mIndex=0;
    mIndexCount=0;
    mIndexSize=0;
}

void ModelDataIndexed::AddIndex(GRAPHICS_MODEL_TYPE pIndex)
{
    if(mIndexCount >= mIndexSize)SizeIndex(mIndexCount + (mIndexCount / 2) + 1);
    mIndex[mIndexCount]=pIndex;
    mIndexCount++;
}

void ModelDataIndexed::SizeIndex(int pSize)
{
    mIndexSize = pSize;
    
    GRAPHICS_MODEL_TYPE *aNew = new GRAPHICS_MODEL_TYPE[mIndexSize + 1];
    
    for(int i=0;i<mIndexCount;i++)aNew[i] = mIndex[i];
    for(int i=mIndexCount;i<mIndexSize;i++)aNew[i] = 0;
    
    delete [] mIndex;
    mIndex = aNew;
}

void ModelDataIndexed::CopyIndex(GRAPHICS_MODEL_TYPE *pIndex, int pCount)
{
    delete[]mIndex;
    mIndex=0;
    mIndexCount=0;
    mIndexSize=0;
    
    if((pIndex == 0) || (pCount <= 0))
    {
        return;
    }
    
    SizeIndex(pCount);
    for(int i=0;i<pCount;i++)
    {
        mIndex[i]=pIndex[i];
    }
    mIndexCount=pCount;
}

void ModelDataIndexed::GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ)
{
    pCentroidX=0.0f;
    pCentroidY=0.0f;
    pCentroidZ=0.0f;
    
    int aIndex;
    
    for(int i=0;i<mIndexCount;i++)
    {            
        aIndex = mIndex[i] * 3;
        pCentroidX += mXYZ[aIndex + 0];
        pCentroidY += mXYZ[aIndex + 1];
        pCentroidZ += mXYZ[aIndex + 2];
    }
    
    if(mIndexCount > 1)
    {
        pCentroidX /= (float)mIndexCount;
        pCentroidY /= (float)mIndexCount;
        pCentroidZ /= (float)mIndexCount;
    }
}



ModelData *ModelDataIndexed::GetData()
{
    ModelData *aReturn = new ModelData();
    
    if(mIndexCount > 0)
    {
        int aIndex;
        
        if(mXYZCount)
        {
            for(int i=0;i<mIndexCount;i++)
            {            
                aIndex = mIndex[i] * 3;
                float aX = mXYZ[aIndex + 0];
                float aY = mXYZ[aIndex + 1];
                float aZ = mXYZ[aIndex + 2];
                aReturn->AddXYZ(aX, aY, aZ);
            }
        }
        
        if(mUVWCount)
        {
            for(int i=0;i<mIndexCount;i++)
            {            
                aIndex = mIndex[i] * 3;
                float aU = mUVW[aIndex + 0];
                float aV = mUVW[aIndex + 1];
                float aW = mUVW[aIndex + 2];
                aReturn->AddUVW(aU, aV, aW);
            }
        }
        
        if(mNormalCount)
        {
            for(int i=0;i<mIndexCount;i++)
            {            
                aIndex = mIndex[i] * 3;
                float aNormX = mNormal[aIndex + 0];
                float aNormY = mNormal[aIndex + 1];
                float aNormZ = mNormal[aIndex + 2];
                aReturn->AddNormal(aNormX, aNormY, aNormZ);
            }
        }
        
    }
    else
    {
        aReturn->CopyXYZ(mXYZ, mXYZCount);
        aReturn->CopyXYZ(mUVW, mUVWCount);
        aReturn->CopyXYZ(mNormal, mNormalCount);
        
        
    }
    
    return aReturn;
}

void ModelDataIndexed::DiscardIndeces()
{
    if(mIndexCount > 0)
    {
        ModelData *aData = GetData();
        
        Free();
        
        CopyXYZ(aData->mXYZ, aData->mXYZCount);
        CopyUVW(aData->mUVW, aData->mUVWCount);
        CopyNorm(aData->mNormal, aData->mNormalCount);
        
        delete aData;
    }
    mIndex=0;
}

ModelDataIndexed *ModelDataIndexed::Clone()
{
    ModelDataIndexed *aClone=new ModelDataIndexed();
    aClone->CopyXYZ(mXYZ, mXYZCount);
    aClone->CopyUVW(mUVW, mUVWCount);
    aClone->CopyNorm(mNormal, mNormalCount);
    aClone->CopyIndex(mIndex, mIndexCount);
    return aClone;
}

void ModelDataIndexed::Clone(ModelDataIndexed *pTarget)
{
    Free();
    if(pTarget)
    {
        CopyXYZ(pTarget->mXYZ, pTarget->mXYZCount);
        CopyUVW(pTarget->mUVW, pTarget->mUVWCount);
        CopyNorm(pTarget->mNormal, pTarget->mNormalCount);
        CopyIndex(pTarget->mIndex, pTarget->mIndexCount);
    }
}



void ModelDataIndexed::Save(const char *pFile)
{
    Buffer aBuffer;
    Save(&aBuffer);
    aBuffer.Save(pFile);
}

void ModelDataIndexed::Save(Buffer *pBuffer)
{
    if(!pBuffer)return;
    
    ModelData::Save(pBuffer);
    
    pBuffer->WriteInt(mIndexCount);
    
    for(int i=0;i<mIndexCount;i++)
    {
        pBuffer->WriteShort(mIndex[i]);
    }
}

void ModelDataIndexed::LoadData(Buffer *pBuffer)
{
    if(!pBuffer)return;
    
    ModelData::LoadData(pBuffer);
    
    int aIndexCount = pBuffer->ReadInt();

    DiscardIndeces();
    
    if(aIndexCount > 0)
    {
        SizeIndex(aIndexCount);
        
        mIndexCount = aIndexCount;
        
        for(int i=0;i<mIndexCount;i++)
        {
            mIndex[i] = pBuffer->ReadShort();
        }
    }
}

void ModelDataIndexed::LoadData(const char *pFile)
{
    Buffer aBuffer;
    aBuffer.Load(pFile);
    LoadData(&aBuffer);
}

void ModelDataIndexed::Draw()
{
    Graphics::DrawModelIndexed(mXYZ, mUVW, mNormal, mIndex, mIndexCount, mBindIndex);
}

void ModelDataIndexed::Draw(int pBindIndex)
{
    Graphics::DrawModelIndexed(mXYZ, mUVW, mNormal, mIndex, mIndexCount, pBindIndex);
}

void ModelDataIndexed::DrawEfficientSetup()
{
    Graphics::DrawModelIndexedEfficientSetup(mXYZ, mUVW, mNormal, mBindIndex);
}

void ModelDataIndexed::DrawEfficient()
{
    Graphics::DrawTriangles(mIndex, mIndexCount);
    
    //Graphics::DrawModelEfficientSetup(mXYZ, mUVW, mNormal, mBindIndex);
}

//mUVWShifted

void ModelDataIndexed::DrawShifted(float pUShift, float pVShift)
{
    
    if((pUShift == 0) && (pVShift == 0))
    {
        Draw();
    }
    
    int aCount = mUVWCount * 3;
    if(mUVWShifted == 0)
    {
        mUVWShifted = new float[aCount + 1];
    }
    
    if((pUShift < 0) || (pUShift > 1))
    {
        pUShift = fmodf(pUShift, 1.0f);
        if(pUShift < 0)pUShift += 1.0f;
    }
    
    if((pVShift < 0) || (pVShift > 1))
    {
        pVShift = fmodf(pVShift, 1.0f);
        if(pVShift < 0)pVShift += 1.0f;
    }
    
    for(int i=0;i<aCount;i+=3)mUVWShifted[i] = (mUVW[i] + pUShift);
    for(int i=1;i<aCount;i+=3)mUVWShifted[i] = (mUVW[i] + pVShift);
    for(int i=2;i<aCount;i+=3)mUVWShifted[i] = 0;//(mUVW[i]);
    
    float *aHold = mUVW;
    
    mUVW = mUVWShifted;
    
    /*
    
    if(pUShift > 0.5f || pVShift > 0.5f)
    {
        for(int i=0;i<aCount;i+=3)
        {
            float aU = mUVW[i];
            float aV = mUVW[i+1];
            float aW = mUVW[i+2];
            
            printf("UVW[%d] = (%.2f %.2f %.2f)\n", aCount / 3, aU, aV, aW);
     
        }
        int aTime = 0;
    }
    
    */
    
    
    //Graphics::TextureSetWrap();
    Draw();
    //Graphics::TextureSetClamp();
    
    mUVW = aHold;
}

void ModelDataIndexed::DrawShifted(ModelDataIndexed *pReference, float pUShift, float pVShift)
{
    int aCount = mUVWCount * 3;
    
    float *aUVW = pReference->mUVW;
    
    if(pUShift != 0)
    {
        
    }
    
    if(pVShift != 0)
    {
        
    }
    
    //Graphics::TextureSetWrap();
    Draw();
    //Graphics::TextureSetClamp();
}

void ModelDataIndexed::PrintCode()
{
    //float aXYZ[5] = {5.0f, 1.25f, 0.5f, 0.5f, 1.0f};
    
    int aCount;
    
    aCount = mXYZCount * 3;
    printf("static float aXYZ[%d]={", aCount);
    for(int i=0;i<aCount;i++)
    {
        printf("%.1f", mXYZ[i]);
        if(i != (aCount - 1))
        {
            printf(",");
        }
        else
        {
            printf("};\n");
        }
    }
    
    aCount = mUVWCount * 3;
    printf("static float aUVW[%d]={", aCount);
    for(int i=0;i<aCount;i++)
    {
        printf("%.2f", mUVW[i]);
        if(i != (aCount - 1))
        {
            printf(",");
        }
        else
        {
            printf("};\n");
        }
    }
    
    aCount = mNormalCount * 3;
    printf("static float aNormal[%d]={", aCount);
    for(int i=0;i<aCount;i++)
    {
        printf("%f", mNormal[i]);
        if(i != (aCount - 1))
        {
            printf(",");
        }
        else
        {
            printf("};\n");
        }
    }
    
    printf("static unsigned short aIndex[%d]={", mIndexCount);
    for(int i=0;i<mIndexCount;i++)
    {
        printf("%d", mIndex[i]);
        if(i != (mIndexCount - 1))
        {
            printf(",");
        }
        else
        {
            printf("};\n");
        }
    }
}

void ModelDataIndexed::Load(const char *pFile)
{
    Load3D(*this, pFile);
}

void ModelDataIndexed::Load(const char *pFileStart, int pIndex, const char *pFileEnd)
{
    FString aPath = FString(pFileStart) + FString(pIndex) + FString(pFileEnd);
    Load(aPath.c());
}

void ModelDataIndexed::Load(const char *pFile, Sprite &pSprite)
{
    Load(pFile);
    mBindIndex = pSprite.mBindIndex;
}

void ModelDataIndexed::Load(const char *pFileStart, int pIndex, const char *pFileEnd, Sprite &pSprite)
{
    Load(pFileEnd, pIndex, pFileEnd);
    mBindIndex = pSprite.mBindIndex;
}

