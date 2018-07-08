//
//  ModelDataSequence.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 1/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ModelUtilities.h"
#include "ModelDataSequence.h"
#include "ModelData.h"
#include "ModelDataOptimizer.h"
#include "FileSequence.h"
#include "Application.h"

ModelDataSequence::ModelDataSequence()
{
    mUVWShifted=0;
    mBindIndex=-1;
    mParent=0;
    
    mSize=0;
    mCount=0;
    mData=0;
    
    mDisableNormal=false;
    mDisableUVW=false;
    mDisableIndeces=false;
    
    mUsesBaseXYZ=false;
    mUsesBaseNormal=false;
    mUsesBaseUVW=true;
}

ModelDataSequence::~ModelDataSequence()
{
    Free();
}




void ModelDataSequence::Add(ModelDataIndexed *pData)
{
    if(pData == 0)return;
    
    if(mCount <= mSize)
    {
        mSize = mCount + mCount / 2 + 1;
        
        ModelDataIndexed **aData = new ModelDataIndexed*[mSize];
        
        for(int i=mCount;i<mSize;i++)aData[i]=0;
        for(int i=0;i<mCount;i++)aData[i]=mData[i];
        
        delete[]mData;
        
        mData=aData;
    }
    
    mData[mCount] = pData;
    mCount++;
    
}


void ModelDataSequence::Load(const char *pFileBase, int pStartIndex, int pEndIndex, const char *pFileReferenceName)
{
    Free();
    
    ModelDataOptimizer *aOptimizer = new ModelDataOptimizer();
    
    ModelData *aBaseModel = LoadOBJ(pFileReferenceName);
    
    bool aDidFindBase = false;
    
    List aFileList;
    FileSequence::LoadSequence(pFileBase, "obj", aFileList, pStartIndex, pEndIndex);
    
    //EnumList(FString, aString, aFileList)
    //{
    //    ModelDataIndexed aTest;
    //    aTest.Load(aString->c());
        
    //    printf("Index Count: %d {%d  %d  %d}\n", aTest.mIndexCount, aTest.mXYZCount, aTest.mUVWCount, aTest.mNormalCount);
    //}
    
    int aIndex=0;
    EnumList(FString, aString, aFileList)
    {
        
        ModelData *aData = LoadOBJ(aString->c());
        
        if((aData != 0) && (aDidFindBase == false))
        {
            
            bool aSharedBase = false;
            
            if(aBaseModel == 0)
            {
                aBaseModel = aData;
                aSharedBase = true;
            }
            else if(aBaseModel->mXYZCount <= 0)
            {
                aBaseModel = aData;
                aSharedBase = true;
            }
            
            aOptimizer->Generate(aBaseModel);
            mParent=aOptimizer->Convert(aBaseModel);
            
            aDidFindBase = true;
            
            if(aSharedBase)
            {
                aBaseModel = 0;
            }
        }
        
        ModelDataIndexed *aNew = new ModelDataIndexed();
        
        //aNew->Load(aString->c());
        
        aOptimizer->SolveXYZ(aData, aNew);
        
        if(aData->mNormalCount > 0)aOptimizer->SolveNormal(aData, aNew);
        
        if(aData->mUVWCount > 0)aOptimizer->SolveUVW(aData, aNew);
        
        Add(aNew);
        
        delete aData;
        aIndex++;
    }
    
    delete aBaseModel;
    FreeList(FString, aFileList);
}

void ModelDataSequence::Free()
{
    delete mParent;mParent=0;
    
    for(int i=0;i<mCount;i++)
    {
        delete mData[i];
    }
    delete [] mData;
    mData=0;
    
    mCount=0;
    mSize=0;
}

void ModelDataSequence::FlipXY()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->FlipXY();
    }
    if(mParent)mParent->FlipXY();
}

void ModelDataSequence:: FlipYZ()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->FlipXY();
    }
    if(mParent)mParent->FlipXY();
}

void ModelDataSequence::FlipZX()
{

    for(int i=0;i<mCount;i++)
    {
        mData[i]->FlipXY();
    }
    if(mParent)mParent->FlipXY();
}

void ModelDataSequence::NegateX()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->NegateX();
    }
    if(mParent)mParent->NegateX();
}

void ModelDataSequence::NegateY()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->NegateY();
    }
    if(mParent)mParent->NegateY();
}

void ModelDataSequence::NegateZ()
{
    for(int i=0;i<mCount;i++)
    {
        mData[i]->NegateZ();
    }
    if(mParent)mParent->NegateZ();
}

void ModelDataSequence::DrawShifted(float pFrame, float pUShift, float pVShift)
{
    if((mParent != 0) && (mCount > 0))
    {
        
        int aFrame = (int)pFrame;
        if(aFrame < 0)aFrame=0;
        if(aFrame >= mCount)aFrame = (mCount - 1);
        
        ModelDataIndexed *aData = mData[aFrame]; //(ModelData *)mList.Fetch(aFrame);
        
        float *aUVW = mParent->mUVW;
        
        int aCount = mParent->mUVWCount * 3;
        if(mUVWShifted == 0)
        {
            mUVWShifted = new float[aCount + 1];
            for(int i=2;i<aCount;i+=3)mUVWShifted[i] = (aUVW[i]);
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
        
        
        
        
        for(int i=0;i<aCount;i+=3)mUVWShifted[i] = (aUVW[i] + pUShift);
        for(int i=1;i<aCount;i+=3)mUVWShifted[i] = (aUVW[i] + pVShift);
        
        
        //Graphics::TextureSetWrap();
        
        
        if(gTestIndex1 == 0)
        {
            Graphics::DrawModelIndexed(aData->mXYZ, mUVWShifted, aData->mNormal, mParent->mIndex, mParent->mIndexCount, mBindIndex);
        }
        else
        {
            Graphics::DrawModelIndexed(aData->mXYZ, mUVWShifted, mParent->mNormal, mParent->mIndex, mParent->mIndexCount, mBindIndex);
        }
        
        
        
        //Graphics::TextureSetClamp();
    }
}

void ModelDataSequence::Draw(float pFrame)
{
    if((mParent != 0) && (mCount > 0))
    {
        int aFrame = (int)pFrame;
        if(aFrame < 0)aFrame=0;
        if(aFrame >= mCount)aFrame = (mCount - 1);
        
        
        
        
        ModelDataIndexed *aData = mData[aFrame];
        
        int aCount = mParent->mIndexCount;
        if(aCount <= 0)aCount = aData->mXYZCount;
        
        float *aXYZ = aData->mXYZ;
        if(aXYZ == 0)aXYZ = mParent->mXYZ;
        
        float *aUVW = aData->mUVW;
        if(aUVW == 0)aUVW = mParent->mUVW;
        
        float *aNormal = aData->mNormal;
        if(aNormal == 0)aNormal = mParent->mNormal;
        
        unsigned short *aIndex = aData->mIndex;
        if(aIndex == 0)aIndex = mParent->mIndex;
        
        //Graphics::DrawModelIndexed(aData->mXYZ, mParent->mUVW, mUsesBaseNormal ? mParent->mNormal : aData->mNormal, mParent->mIndex, mParent->mIndexCount, mBindIndex);
        
        Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex, aCount, mBindIndex);
        
    }
    
}





void ModelDataSequence::GetCentroid(int pFrame, float &pCentroidX, float &pCentroidY, float &pCentroidZ)
{
    
    ModelDataIndexed *aCheck = new ModelDataIndexed();
    
    if(mParent)
    {
        //if(mParent->mIndexCount > 0)
        aCheck->CopyIndex(mParent->mIndex, mParent->mIndexCount);
    }
    
    int aFrame = (int)pFrame;
    if(aFrame < 0)aFrame=0;
    if(aFrame >= mCount)aFrame = (mCount - 1);
    
    ModelDataIndexed *aData = mData[aFrame];
    
    if(aData)
    {
        aCheck->CopyXYZ(aData->mXYZ, aData->mXYZCount);
    }
    aCheck->GetCentroid(pCentroidX, pCentroidY, pCentroidZ);
    
}



void ModelDataSequence::Save(const char *pFile)
{
    if(!mParent)return;
    
    //printf("Saving Data Sequence [%d Nodes] [Index: %d  UVW: %d]\n", mList.mCount, mParent->mIndexCount, mParent->mUVWCount);
    
    Buffer aBuffer;
    
    if(mDisableUVW)
    {
        mParent->DiscardUVW();
        for(int i=0;i<mCount;i++)mData[i]->DiscardUVW();
    }
    
    if(mDisableNormal)
    {
        mParent->DiscardNormal();
        for(int i=0;i<mCount;i++)mData[i]->DiscardNormal();
    }
    
    
    if(mDisableIndeces)
    {
        if(mParent->mIndexCount > 0)
        {
            for(int i=0;i<mCount;i++)
            {
                if(mData[i]->mIndexCount <= 0)
                {
                    int aPreIndCount = mParent->mIndexCount;
                    int aPreXYZCount = mData[i]->mXYZCount;
                    
                    mData[i]->CopyIndex(mParent->mIndex, mParent->mIndexCount);
                    mData[i]->DiscardIndeces();
                    
                    printf("Data[%d] Stripped[%d Index %d XYZ] to [%d XYZ]\n", i, aPreIndCount, aPreXYZCount, mData[i]->mXYZCount);
                }
            }
        }
        else
        {
            for(int i=0;i<mCount;i++)
            {
                mData[i]->DiscardIndeces();
            }
        }
        
        
        mParent->DiscardIndeces();
    }
    
    
    
    if(mUsesBaseNormal)
    {
        for(int i=0;i<mCount;i++)
        {
            mData[i]->DiscardNormal();
        }
    }
    else
    {
        mParent->DiscardNormal();
    }
    
    if(mUsesBaseUVW)
    {
        for(int i=0;i<mCount;i++)
        {
            mData[i]->DiscardUVW();
        }
    }
    else
    {
        mParent->DiscardUVW();
    }

    
    mParent->Save(&aBuffer);
    aBuffer.WriteInt(mCount);
    
    int aXYZCount = 0;
    int aUVWCount = 0;
    int aNormalCount = 0;
    
    for(int i=0;i<mCount;i++)
    {
        mData[i]->Save(&aBuffer);
        
        if(mData[i]->mXYZCount > 0)aXYZCount++;
        if(mData[i]->mUVWCount > 0)aUVWCount++;
        if(mData[i]->mNormalCount > 0)aNormalCount++;
    }
    
    printf("[----- Saving %s ------]\n", pFile);
    
    printf("Model Count: %d\n", mCount);
    
    printf("XYZ on %d nodex (parent = %s)\n", aXYZCount, (mParent->mXYZ ? "yes" : "no"));
    if(aXYZCount > 0 && mParent->mXYZ != 0)printf("***Duplicates for XYZ\n");
    
    printf("UVW on %d nodex (parent = %s)\n", aUVWCount, (mParent->mUVW ? "yes" : "no"));
    if(aUVWCount > 0 && mParent->mUVW != 0)printf("***Duplicates for UVW\n");
    
    printf("Normal on %d nodex (parent = %s)\n", aNormalCount, (mParent->mNormal ? "yes" : "no"));
    if(aNormalCount > 0 && mParent->mNormal != 0)printf("***Duplicates for Normal\n");
    
    printf("[---------------------]\n\n");
    
    
    aBuffer.Save(pFile);
    
    //printf("Data Sequenced Saved [%s]\n\nData Sequence Size [%d] (%d)\n\n", pFile, aBuffer.mLength, aBuffer.mLength / (1000000));
}

void ModelDataSequence::Load(const char *pFile)
{
    Free();
    
    Buffer aBuffer;
    aBuffer.Load(pFile);
    
    if(aBuffer.mLength <= 0)
    {
        FString aAltPath = FString(pFile) + FString(".seq");
        aBuffer.Load(aAltPath);
    }
    
    mParent = new ModelDataIndexed();
    mParent->LoadData(&aBuffer);
    //mParent->InvertV();
    
    int aListCount = aBuffer.ReadInt();
    //printf("**** OBJ Sequence List Count: %d\n", aListCount);
    for(int i=0;i<aListCount;i++)
    {
        ModelDataIndexed *aData = new ModelDataIndexed();
        aData->LoadData(&aBuffer);
        Add(aData);
    }
    
    mUsesBaseNormal = (mParent->mNormalCount > 0);
}

void ModelDataSequence::SetSprite(Sprite *pSprite, bool pFixUVW)
{
    for(int i=0;i<mCount;i++)
    {
        //if(mData[i])
        //{
        //    mData[i]->SetSprite(pSprite, pFixUVW);
        //}
    }
    if(mParent)
    {
        mParent->SetSprite(pSprite, pFixUVW);
    }
    
    mBindIndex = pSprite->mBindIndex;
}
