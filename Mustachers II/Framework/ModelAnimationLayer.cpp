//
//  ModelAnimationLayer.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ModelAnimationLayer.h"
#include "ModelDataOptimizer.h"
#include "ModelUtilities.h"
#include "FileSequence.h"
#include "Sprite.h"
#include "XML.h"
#include "Buffer.h"

ModelAnimationLayer::ModelAnimationLayer()
{
    mSprite=0;
    mFrameCount=0;
    mParent=0;
    mType=0;
    mBindIndex=-1;
}

ModelAnimationLayer::~ModelAnimationLayer()
{
    
}

void ModelAnimationLayer::SetParent(ModelDataIndexed *pData)
{
    mParent=pData;
}

void ModelAnimationLayer::Save(Buffer *pBuffer)
{
    if(pBuffer)
    {
        if(mParent)
        {
            pBuffer->WriteChar(1);
            mParent->Save(pBuffer);
        }
        else
        {
            pBuffer->WriteChar(0);
        }
        
        pBuffer->WriteInt(mFrameCount);
        pBuffer->WriteInt(mType);
        
        printf("Writing Frame Count: %d\n\n\n", mFrameCount);
        
    }
}

void ModelAnimationLayer::Load(Buffer *pBuffer)
{
    if(pBuffer->ReadChar())
    {
        ModelDataIndexed *aData=new ModelDataIndexed();
        aData->LoadData(pBuffer);
        aData->InvertV();
        SetParent(aData);
    }
    mFrameCount = pBuffer->ReadInt();
    
    printf("\n\n********\n\nReading Frame Count: %d\n\n\n", mFrameCount);
    
    mType = pBuffer->ReadInt();
}

///////////////////////////////////////////////////
//                                               //
//              Layer Stuff                      //
//                                               //
///////////////////////////////////////////////////

ModelAnimationLayerTransform::ModelAnimationLayerTransform()
{
    mType=1;
    
    mListSize=0;
    mFrameCount=0;

    mData=0;
}

ModelAnimationLayerTransform::~ModelAnimationLayerTransform()
{
    
}

void ModelAnimationLayerTransform::SetParent(ModelDataIndexed *pData)
{
    ModelAnimationLayer::SetParent(pData);
}

void ModelAnimationLayerTransform::Draw(float pFrame, int *pKeyStart, int *pKeyEnd, int pFrameCount)
{
    //Draw(pFrame);
    //return;
    
    if(mBindIndex == -1)
    {
        if(mSprite)
        {
            mBindIndex = mSprite->mBindIndex;
        }
    }
    
    if(mFrameCount > 0)
    {
        float aFrameMax = (float)(mFrameCount-1);
        if(pFrame > aFrameMax)pFrame=aFrameMax;
        if(pFrame < 0)pFrame=0;
        
        int aFrameInt=(int)pFrame;
        if(aFrameInt<0)aFrameInt=0;
        if(aFrameInt>=mFrameCount)aFrameInt=mFrameCount-1;
        
        int aStartFrame=pKeyStart[aFrameInt];
        int aEndFrame=pKeyEnd[aFrameInt];
        
        ModelAnimationLayerTransformNode *aData1 = mData[aStartFrame];
        ModelAnimationLayerTransformNode *aData2 = mData[aEndFrame];
        
        if(aData1 && aData2)
        {
        
            float aStartPercent=1.0f;
            
            if(aEndFrame != aStartFrame)
            {
                aStartPercent = (pFrame - ((float)aStartFrame)) / (float)(aEndFrame - aStartFrame);
                
                if(aStartPercent < 0)aStartPercent=0;
                if(aStartPercent > 1)aStartPercent=1;
            }
            
            float aEndPercent=(1-aStartPercent);
            
            float aX=aData1->mX * aEndPercent + aData2->mX * aStartPercent;
            float aY=aData1->mY * aEndPercent + aData2->mY * aStartPercent;
            float aZ=aData1->mZ * aEndPercent + aData2->mZ * aStartPercent;
            
            float aAxisX=aData1->mAxisX * aEndPercent + aData2->mAxisX * aStartPercent;
            float aAxisY=aData1->mAxisY * aEndPercent + aData2->mAxisY * aStartPercent;
            float aAxisZ=aData1->mAxisZ * aEndPercent + aData2->mAxisZ * aStartPercent;
            
            float aRotation=aData1->mRot * aEndPercent + aData2->mRot * aStartPercent;
            
            Graphics::MatrixPush();
            
            Graphics::Translate(aX,aY,aZ);
            Graphics::Rotate(-aRotation,aAxisX,aAxisY,aAxisZ);
            
            mParent->Draw(mBindIndex);
            
            Graphics::MatrixPop();
            
        }
    }
}

void ModelAnimationLayerTransform::Draw(float pFrame)
{
    if(mBindIndex == -1)
    {
        if(mSprite)
        {
            mBindIndex = mSprite->mBindIndex;
        }
    }
    
    int aFrame = pFrame;
    if(aFrame < 0)aFrame = 0;
    if(aFrame >= mFrameCount)aFrame = mFrameCount - 1;
    
    if((aFrame >= 0) && (mParent != 0))
    {
        ModelAnimationLayerTransformNode *aNode=mData[aFrame];
        if(aNode)
        {
            float aX=aNode->mX;
            float aY=aNode->mY;
            float aZ=aNode->mZ;
            
            float aAxisX=aNode->mAxisX;
            float aAxisY=aNode->mAxisY;
            float aAxisZ=aNode->mAxisZ;
            
            float aRotation=aNode->mRot;
            
            Graphics::MatrixPush();
            Graphics::Translate(aX,aY,aZ);
            Graphics::Rotate(-aRotation,aAxisX,aAxisY,aAxisZ);
            
            mParent->Draw(mBindIndex);
            
            Graphics::MatrixPop();
        }
    }
}

void ModelAnimationLayerTransform::SizeTransforms(int pSize)
{
    int aNewSize=pSize;
    
    ModelAnimationLayerTransformNode **aNewData=new ModelAnimationLayerTransformNode*[aNewSize+1];
    
    int aCap=aNewSize+1;
    for(int i=mListSize;i<aCap;i++)
    {
        aNewData[i]=0;
    }
    
    for(int i=0;i<mListSize;i++)
    {
        aNewData[i]=mData[i];
    }
    
    mListSize = aNewSize;
    
    
    delete [] mData;
    mData = aNewData;
}

void ModelAnimationLayerTransform::AddTransform(float pX, float pY, float pZ, float pAxisX, float pAxisY, float pAxisZ, float pRot)
{
    if(mFrameCount >= mListSize)
    {
        SizeTransforms(mFrameCount + mFrameCount / 2 + 16);
    }
    
    ModelAnimationLayerTransformNode *aNode=new ModelAnimationLayerTransformNode();
    
    aNode->mX=pX;
    aNode->mY=pY;
    aNode->mZ=pZ;
    
    aNode->mAxisX=pAxisX;
    aNode->mAxisY=pAxisY;
    aNode->mAxisZ=pAxisZ;
    
    aNode->mRot=pRot;
    
    mData[mFrameCount]=aNode;
    //printf("mData[%d] = [%f %f %f]\n", mFrameCount, aNode->mX, aNode->mY, aNode->mZ);
    mFrameCount++;
}

void ModelAnimationLayerTransform::SetUp(const char *pModelFile, const char *pXMLFile, int pStartFrame, int pEndFrame)
{
    SetParent(LoadOBJIndexed(pModelFile));
    
    if(mParent == 0)
    {
        printf("Animation Layer Transform::SetUp Error - Reference model not found (%s)\n", pModelFile);
    }
    
    XML aXML;
    aXML.Load(pXMLFile);
    
    if(pEndFrame < 0)
    {
        pEndFrame=10000000;
    }
    
    XMLTag *aRoot = aXML.GetRoot();
    
    if(aRoot == 0)
    {
        printf("Animation Layer Transform::SetUp Error - XML not found (%s)\n", pXMLFile);
    }
    
    printf("Start: %d  End: %d\n", pStartFrame, pEndFrame);
    
    if(aRoot)
    {
        
        int aFrame;
        
        float aTranslateX, aTranslateY, aTranslateZ;
        float aRotationAxisX, aRotationAxisY, aRotationAxisZ;
        float aRotation;
        
        EnumTagsMatching(aRoot, aTag, "animation_node")
        {
            aFrame = FString(aTag->GetParamValue("frame")).ToInt();
            if((aFrame >= pStartFrame) && (aFrame <= pEndFrame))
            {
                aTranslateX = FString(aTag->GetParamValue("tx")).ToFloat();
                aTranslateY = FString(aTag->GetParamValue("ty")).ToFloat();
                aTranslateZ = FString(aTag->GetParamValue("tz")).ToFloat();
                
                aRotationAxisX = FString(aTag->GetParamValue("ax")).ToFloat();
                aRotationAxisY = FString(aTag->GetParamValue("ay")).ToFloat();
                aRotationAxisZ = FString(aTag->GetParamValue("az")).ToFloat();
                
                aRotation = FString(aTag->GetParamValue("rot")).ToFloat();
                
                AddTransform(aTranslateX,aTranslateY,aTranslateZ,
                             aRotationAxisX,aRotationAxisY,aRotationAxisZ,
                             aRotation);
            }
        }
    }
    
    float aLastRotation = 0;
    bool aFound=false;
    
    
    for(int i=0;i<mFrameCount;i++)
    {
        if(mData[i])
        {
            if(aFound)
            {
                float aRot=mData[i]->mRot;
                
                float aDiff = DistanceBetweenAngles(aLastRotation, aRot);
                
                aLastRotation = (aLastRotation + aDiff);
                
                mData[i]->mRot = aLastRotation;
                
                //printf("Rotations: %f\n", aLastRotation);
                
                
            }
            else
            {
                aLastRotation = mData[i]->mRot;
                aFound=true;
            }
        }
    }
}

void ModelAnimationLayerTransform::Free()
{
    printf("ModelAnimationLayerTransform::~ModelAnimationLayerTransform::Free() \n");
    
    ModelAnimationLayer::Free();
    
    for(int i=0;i<mFrameCount;i++)
    {
        delete mData[i];
    }
    
    delete []mData;
    mData=0;
    
    mListSize=0;
    mFrameCount=0;
}

void ModelAnimationLayerTransform::Save(Buffer *pBuffer)
{
    ModelAnimationLayer::Save(pBuffer);
    
    printf("ModelAnimationLayerTransform::Count(%d);\n", mFrameCount);
    
    for(int i=0;i<mFrameCount;i++)
    {
        if(mData[i])
        {
            pBuffer->WriteChar(1);
            
            pBuffer->WriteFloat(mData[i]->mX);
            pBuffer->WriteFloat(mData[i]->mY);
            pBuffer->WriteFloat(mData[i]->mZ);
            
            pBuffer->WriteFloat(mData[i]->mAxisX);
            pBuffer->WriteFloat(mData[i]->mAxisY);
            pBuffer->WriteFloat(mData[i]->mAxisZ);
            
            pBuffer->WriteFloat(mData[i]->mRot);
            
        }
        else
        {
            pBuffer->WriteChar(0);
        }
    }
}

void ModelAnimationLayerTransform::Load(Buffer *pBuffer)
{
    Free();
    
    ModelAnimationLayer::Load(pBuffer);
    
    int aHoldCount=mFrameCount;
    mFrameCount=0;
    SizeTransforms(aHoldCount);
    mFrameCount=aHoldCount;
    
    for(int i=0;i<mFrameCount;i++)
    {
        if(pBuffer->ReadChar())
        {
            mData[i]=new ModelAnimationLayerTransformNode();
            
            mData[i]->mX=pBuffer->ReadFloat();
            mData[i]->mY=pBuffer->ReadFloat();
            mData[i]->mZ=pBuffer->ReadFloat();
            
            mData[i]->mAxisX=pBuffer->ReadFloat();
            mData[i]->mAxisY=pBuffer->ReadFloat();
            mData[i]->mAxisZ=pBuffer->ReadFloat();
            
            mData[i]->mRot=pBuffer->ReadFloat();
        }
        else
        {
            mData[i]=0;
        }
    }
}

void ModelAnimationLayerTransform::StripToKeyframes(bool *pKeyFrames)
{
    for(int i=0;i<mListSize;i++)
    {
        if(pKeyFrames[i])
        {
            printf("Data[%d] = %x\n", i, mData[i]);
        }
        else
        {
            //printf("Deleting Frame: %d\n", i);
            delete mData[i];
            mData[i]=0;
        }
    }
}



////////////////////////////////////////////////////
//////
//////       Layer Stuff
//////


ModelAnimationLayerMesh::ModelAnimationLayerMesh()
{
    mType=2;
    mListSize=0;
    mData=0;
    mXYZInterp=0;
    mNormalInterp=0;
}

ModelAnimationLayerMesh::~ModelAnimationLayerMesh()
{
    Free();
}

void ModelAnimationLayerMesh::SetUp(ModelDataSequence *pSequence)
{
    
    SetParent(pSequence->mParent->Clone());
    
    int aIndex=0;
    
    //EnumList(ModelData, aData, pSequence->mList)
    //{
    //    AddNode(aData->Clone(), aIndex);
    //    aIndex++;
    //}
    
    //mFrameCount = pSequence->mList.mCount;
    
}

void ModelAnimationLayerMesh::SetParent(ModelDataIndexed *pData)
{
    ModelAnimationLayer::SetParent(pData);
    
    delete[]mXYZInterp;
    
    mNormalInterp=0;
    mXYZInterp=0;
    
    if(pData)
    {
        int aSize=pData->mXYZCount;
        if(pData->mUVWCount>aSize)aSize=pData->mUVWCount;
        if(pData->mNormalCount>aSize)aSize=pData->mNormalCount;
        
        if(aSize <= 0)aSize=1;
        aSize *= 3;
        
        mXYZInterp=new float[aSize * 2];
        mNormalInterp=(mXYZInterp + aSize);
    }
}

void ModelAnimationLayerMesh::Draw(float pFrame)
{
    int aFrame = pFrame;
    if(aFrame < 0)aFrame = 0;
    
    if(mFrameCount > 0)
    {
        if(aFrame >= mFrameCount)aFrame = (mFrameCount-1);
        
        ModelData *aData = mData[aFrame]; //((ModelData *)mList.FetchBest(((int)pFrame)));
    
        if((aData != 0) && (mParent != 0))
        {
            Graphics::DrawModelIndexed(aData->mXYZ, mParent->mUVW, aData->mNormal, mParent->mIndex, mParent->mIndexCount, mBindIndex);
        }
    }
}

void ModelAnimationLayerMesh::Draw(float pFrame, int *pKeyStart, int *pKeyEnd, int pFrameCount)
{
    if(mBindIndex == -1)
    {
        if(mSprite)
        {
            mBindIndex = mSprite->mBindIndex;
        }
    }
    
    if(mFrameCount > 0)
    {
        float aFrameMax = (float)(mFrameCount-1);
        if(pFrame > aFrameMax)pFrame=aFrameMax;
        if(pFrame < 0)pFrame=0;
        
        int aFrameInt=(int)pFrame;
        if(aFrameInt<0)aFrameInt=0;
        if(aFrameInt>=mFrameCount)aFrameInt=mFrameCount-1;
        
        int aStartFrame=pKeyStart[aFrameInt];
        int aEndFrame=pKeyEnd[aFrameInt];
        
        //printf("%f = [%d - %d]\n", aHole, aStartFrame, aEndFrame);
        
        ModelData *aData1 = mData[aStartFrame];
        ModelData *aData2 = mData[aEndFrame];
        
        if(aData1 && aData2)
        {
            
            float *aXYZ1 = aData1->mXYZ;
            float *aXYZ2 = aData2->mXYZ;
            
            float *aNormal1 = aData1->mNormal;
            float *aNormal2 = aData2->mNormal;
            
            float aStartPercent=1.0f;
            
            
            if(aEndFrame != aStartFrame)
            {
                aStartPercent = (pFrame - ((float)aStartFrame)) / (float)(aEndFrame - aStartFrame);
                
                if(aStartPercent < 0)aStartPercent=0;
                if(aStartPercent > 1)aStartPercent=1;
            }
            
            float aEndPercent=(1-aStartPercent);
            
            //printf("Percents[%f  -  %f]\n", aStartPercent * 100.0f, aEndPercent * 100.0f);
            
            int aDataCount = mParent->mNormalCount * 3;
            
            for(int i=0;i<aDataCount;i++)
            {
                mXYZInterp[i] = (aXYZ1[i] * aEndPercent) + (aXYZ2[i] * aStartPercent);
            }
            for(int i=0;i<aDataCount;i++)
            {
                mNormalInterp[i] = (aNormal1[i] * aEndPercent) + (aNormal2[i] * aStartPercent);
            }
            
            Graphics::DrawModelIndexed(mXYZInterp, mParent->mUVW, mNormalInterp, mParent->mIndex, mParent->mIndexCount, mBindIndex);
        }
    }
}

void ModelAnimationLayerMesh::Free()
{
    for(int i=0;i<mListSize;i++)
    {
        delete mData[i];
    }
    delete[]mData;
    
    mData=0;
    mListSize=0;
    
    delete [] mXYZInterp;
    mXYZInterp=0;
    mNormalInterp=0;
}

void ModelAnimationLayerMesh::SizeData(int pSize)
{
    int aNewSize = pSize;
    int aCap=aNewSize+1;
    
    
    
    ModelData **aNewData=new ModelData*[aCap];
    
    
    for(int i=0;i<mListSize;i++)
    {
        aNewData[i]=mData[i];
    }
    
    for(int i=mListSize;i<aCap;i++)
    {
        aNewData[i]=0;
    }
    
    
    
    delete[]mData;
    
    mData=aNewData;
    mListSize=aNewSize;
    
}

void ModelAnimationLayerMesh::AddNode(ModelData *pData, int pIndex)
{
    if(pIndex >= mListSize)
    {
        SizeData(pIndex + (pIndex / 2) + 16);
    }
    
    mData[pIndex]=pData;
    
}

void ModelAnimationLayerMesh::StripToKeyframes(bool *pKeyFrames)
{
    for(int i=0;i<mListSize;i++)
    {
        if(pKeyFrames[i])
        {
            
        }
        else
        {
            delete mData[i];
            mData[i]=0;
        }
    }
}

void ModelAnimationLayerMesh::SetUp(ModelDataOptimizer *pOptimizer, const char *pBasePath, int pStartIndex, int pEndIndex)
{
    List aFileList;
    FileSequence::LoadSequence(pBasePath, "obj", aFileList, pStartIndex, pEndIndex);
    SizeData(aFileList.mCount);
    
    int aIndex=0;
    EnumList(FString, aString, aFileList)
    {
        ModelData *aData = LoadOBJ(aString->c());
        
        ModelData *aNew=new ModelData();
        
        pOptimizer->SolveXYZ(aData, aNew);
        pOptimizer->SolveNormal(aData, aNew);
        
        AddNode(aNew, aIndex);
        
        delete aData;
        aIndex++;
    }
    
    mFrameCount = aFileList.mCount;
    FreeList(FString, aFileList);
}

void ModelAnimationLayerMesh::Save(Buffer *pBuffer)
{
    ModelAnimationLayer::Save(pBuffer);
    for(int i=0;i<mFrameCount;i++)
    {
        ModelData *aData=mData[i];//((ModelData*)mList.mData[i]);
        if(aData)
        {
            pBuffer->WriteChar(1);
            aData->Save(pBuffer);
        }
        else
        {
            pBuffer->WriteChar(0);
        }
    }
}

void ModelAnimationLayerMesh::Load(Buffer *pBuffer)
{
    ModelAnimationLayer::Load(pBuffer);
    
    
    
    
    int aHoldCount=mFrameCount;
    mFrameCount=0;
    SizeData(aHoldCount);
    mFrameCount=aHoldCount;
    
    
    for(int i=0;i<mFrameCount;i++)
    {
        if(pBuffer->ReadChar())
        {
            ModelData *aData = new ModelData();
            aData->LoadData(pBuffer);
            mData[i]=aData;
        }
        else
        {
            mData[i]=0;
        }
        
        
    }
}

//////
//////       Layer Stuff
//////
////////////////////////////////////////////////////


