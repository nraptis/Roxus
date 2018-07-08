//
//  ModelAnimation.cpp
//  BerryChopper
//
//  Created by Nick Raptis on 1/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ModelAnimation.h"
#include "Graphics.h"
#include "XML.h"

ModelAnimation::ModelAnimation()
{
    //mData=0;
    mFrameCount=0;
    mFrameSize=0;
    
    mInterpolated=false;
    
    mIsKey=0;
    
    mKeyMix1=0;
    mKeyMix2=0;
    
    
    mPlayID=0;
    
    mPlay=true;
    mPlayLoop=true;
    mPlayComplete=false;
    
    
    mPlayFrame=0.0f;
    mPlayFrameSpeed=0.33f;
    
    mPlayFrameEnd=0.0f;;
    mPlayFrameStart=1.0f;
}

ModelAnimation::ModelAnimation(const char *pFile)
{
    mFrameCount=0;
    Load(pFile);
}

ModelAnimation::ModelAnimation(FString pFile)
{
    mFrameCount=0;
    Load(pFile);
}

ModelAnimation::~ModelAnimation()
{
    Free();
}

void ModelAnimation::SetTexture(Sprite *pSprite, int pIndex)
{
    if(pSprite == 0)return;
    
    if(pIndex == -1)
    {
        EnumList(ModelAnimationLayer, aLayer, mLayerList)
        {
            aLayer->mBindIndex = pSprite->mBindIndex;
        }
    }
    else
    {
        ModelAnimationLayer *aLayer = (ModelAnimationLayer *)(mLayerList.Fetch(pIndex));
        if(aLayer)
        {
            aLayer->mBindIndex = pSprite->mBindIndex;
        }
    }
}

void ModelAnimation::Free()
{
    delete[]mIsKey;
    delete[]mKeyMix1;
    
    mKeyMix1 = 0;
    mKeyMix2 = 0;
    mIsKey = 0;
    
    //mFrameXYZ=0;//new float[mFrameCount * 3 + 1];
    //mFrameUVW=0;//&(mFrameXYZ[aSize]);
    //mFrameNormal=0;//=&(mFrameUVW[aSize]);
    
    mFrameCount=0;
    mFrameSize=0;
    
}

void ModelAnimation::Draw()
{
    Draw(mPlayFrame);
}

void ModelAnimation::Draw(float pFrame)
{
    if(mInterpolated)
    {
        
    EnumList(ModelAnimationLayer, aLayer, mLayerList)
    {
        aLayer->Draw(pFrame, mKeyMix1, mKeyMix2, mFrameCount);
    }
    }
    else
    {
        EnumList(ModelAnimationLayer, aLayer, mLayerList)
        {
            aLayer->Draw(pFrame);
        }
    }
}

void ModelAnimation::Update()
{
    
    if(mPlay)
    {
        
        mPlayFrame += mPlayFrameSpeed;
        
        float aEndFrame = (float)mPlayFrameEnd;
        float aStartFrame = (float)mPlayFrameStart;
        
        if(mPlayFrame >= aEndFrame)
        {
            float aFrameDiff = aEndFrame - aStartFrame;
            mPlayFrame -= aFrameDiff;
        }
    }
    
    
    /*
    if(aCurrent)
    {
        mPlayID=pId;
        mPlayLoop=false;
        mPlay=true;
        
        mPlayFrameStart = aCurrent->mStartFrame;
        mPlayFrameEnd = aCurrent->mEndFrame;
        
        mPlayFrame = (float)mPlayFrameStart;
    }
    else
    {
        mPlayID=-1;
        mPlayLoop=pLoop;
        mPlay=false;
    }
    */
}

void ModelAnimation::Generate()
{
    int aMaxFrame=0;
    
    //if(m
    
    EnumList(ModelAnimationSegment, aSegment, mSegmentList)
    {
        
        printf("Segment1[%d] (%d - %d)\n", aSegment->mID, aSegment->mStartFrame, aSegment->mEndFrame);
        
        if(aSegment->mEndFrame > aMaxFrame)
        {
            aMaxFrame = aSegment->mEndFrame;
        }
    }
    
    EnumList(ModelAnimationSegment, aSegment, mSegmentList)
    {
        printf("Segment2[%d] (%d - %d) [%d]\n", aSegment->mID, aSegment->mStartFrame, aSegment->mEndFrame);
        
        
        bool aHasAnyInbetweeners = false;
        
        MakeKey(aSegment->mStartFrame);
        MakeKey(aSegment->mEndFrame);
        
        for(int i=aSegment->mStartFrame;i<aSegment->mEndFrame;i+=10)
        {
            //MakeKey(i);
        }
        
        ComputeKeyIndeces(aSegment->mStartFrame, aSegment->mEndFrame);
    }
    
    
    
    EnumList(ModelAnimationLayer, aLayer, mLayerList)
    {
        aLayer->StripToKeyframes(mIsKey);
    }
    
    //bool *aCanNuke = new bool[mFrameCount + 1];
}

void ModelAnimation::MakeSegment(int pStartFrame, int pEndFrame, int pIdentifier)
{
    
    ModelAnimationSegment *aSegment = new ModelAnimationSegment();
    aSegment->mStartFrame = pStartFrame;
    aSegment->mEndFrame = pEndFrame;
    aSegment->mID = pIdentifier;
    
    mSegmentList += aSegment;
}

void ModelAnimation::SizeKeys(int pSize)
{
    int aNewSize=pSize;
    
    int *aNewMix1=new int[aNewSize * 2 + 2];
    int *aNewMix2=&(aNewMix1[aNewSize+1]);
    
    for(int i=0;i<mFrameSize;i++)aNewMix1[i]=mKeyMix1[i];
    for(int i=0;i<mFrameSize;i++)aNewMix2[i]=mKeyMix2[i];
    
    int aCap=aNewSize+1;
    
    for(int i=mFrameSize;i<aCap;i++)
    {
        aNewMix1[i]=0;
    }
    
    for(int i=mFrameSize;i<aCap;i++)
    {
        aNewMix2[i]=0;
    }
    
    delete [] mKeyMix1;
    
    mKeyMix1 = aNewMix1;
    mKeyMix2 = aNewMix2;
    
    bool *aNewKey=new bool[aNewSize+1];
    
    for(int i=0;i<mFrameSize;i++)aNewKey[i]=mIsKey[i];
    for(int i=mFrameSize;i<aNewSize;i++)aNewKey[i]=false;
    
    delete [] mIsKey;
    
    mIsKey = aNewKey;
    mFrameSize=aNewSize;
}

void ModelAnimation::MakeKey(const char *pCommaSeparatedFrames)
{
    FString aString = pCommaSeparatedFrames;
    
    
    FString aNumberString = aString.GetNumber();
    while(aNumberString.mLength > 0)
    {
        int aFrame = aNumberString.ToInt();
        MakeKey(aFrame);
        printf("Made key From String(%d)\n", aFrame);
        aNumberString = aString.GetNextNumber();
    }
    
    
}

void ModelAnimation::MakeKey(int pFrame)
{
    if(pFrame < 0)
    {
        return;
    }
    
    if(pFrame >= mFrameSize)
    {
        SizeKeys(pFrame + (pFrame / 2) + 16);
    }
    
    mIsKey[pFrame]=true;
    
}

void ModelAnimation::ComputeKeyIndeces(int pStartFrame, int pEndFrame)
{
    
    printf("Indeces1: %d %d\n", pStartFrame, pEndFrame);
    
    if(pEndFrame >= mFrameSize)
    {
        pEndFrame = (mFrameSize - 1);
    }
    
    printf("Indeces2: %d %d\n", pStartFrame, pEndFrame);
    
    if(pEndFrame >= mFrameCount)mFrameCount=pEndFrame+1;
    
    printf("Indeces3: %d %d\n", pStartFrame, pEndFrame);
    
    if((mFrameSize >= mFrameCount) && (mFrameCount > 0))
    {
        mIsKey[pStartFrame] = true;
        mIsKey[pEndFrame] = true;
        
        int aPreviousKey=0;
        
        for(int i=pStartFrame;i<=pEndFrame;i++)
        {
            if((mIsKey[i]) && (i != pEndFrame))aPreviousKey=i;
            mKeyMix1[i] = aPreviousKey;
        }
        
        int aNextKey = (pEndFrame);
        for(int i=pEndFrame;i>=pStartFrame;i--)
        {
            mKeyMix2[i] = aNextKey;
            if((mIsKey[i]) && (i != pStartFrame))aNextKey=i;
        }
        
        for(int i=0;i<mFrameCount;i++)
        {
            //printf("%d)KeyGrid[%d]={%d-%d}\n", mIsKey[i], i, mKeyMix1[i], mKeyMix2[i]);
        }
    }
    
    int aSize=mFrameCount*3;
    
    //mFrameXYZ=new float[aSize * 3 + 1];
    //mFrameUVW=&(mFrameXYZ[aSize]);
    //mFrameNormal=&(mFrameUVW[aSize]);
}

////////////////////////////////////////////////////
//////
//////       Layer Stuff
//////

void ModelAnimation::Add(ModelAnimationLayer *pLayer)
{
    
    if(pLayer->mFrameCount > mFrameCount)
    {
        mFrameCount = pLayer->mFrameCount;
    }
    
    if(mParentList.Find(pLayer->mParent) == -1)
    {
        mParentList += pLayer->mParent;
    }
    
    mLayerList += pLayer;
    
}

//////
//////       End Layer Stuff
//////
////////////////////////////////////////////////////

void ModelAnimation::Save(const char *pFile)
{
    Buffer aBuffer;
    
    
    aBuffer.WriteInt(mFrameCount);
    
    for(int i=0;i<mFrameCount;i++)
    {
        if(mIsKey[i])aBuffer.WriteChar(1);
        
        else aBuffer.WriteChar(0);
        
        aBuffer.WriteShort(mKeyMix1[i]);
        aBuffer.WriteShort(mKeyMix2[i]);
    }
    
    aBuffer.Save(pFile);
    
    
    EnumList(ModelAnimationLayer, aLayer, mLayerList)
    {
        aLayer->StripToKeyframes(mIsKey);
    }
}

void ModelAnimation::Load(const char *pFile)
{
    Free();
    
    Buffer aBuffer;
    aBuffer.Load(pFile);
    
    
    int aFrameCount = aBuffer.ReadInt();
    //aBuffer.WriteInt();
    SizeKeys(aFrameCount);
    mFrameCount=aFrameCount;
    
    
    for(int i=0;i<mFrameCount;i++)
    {
        
        if(aBuffer.ReadBool())
        {
            mIsKey[i]=true;
        }
        else
        {
            mIsKey[i]=false;
        }
        
        
        mKeyMix1[i] = aBuffer.ReadShort();
        mKeyMix2[i] = aBuffer.ReadShort();
    }
    
    for(int i=0;i<mFrameCount;i++)
    {
        if(i % 10 == 0)
        {
            printf("\n");
        }
        
        printf(" %d - [%d](%d-%d),",i, mIsKey[i], mKeyMix1[i], mKeyMix2[i]);
    }
}

////////////////////////////////////////////////////
//////
//////       Internal Play Stuff
//////



void ModelAnimation::Play(int pId, bool pLoop)
{
    ModelAnimationSegment *aCurrent = 0;
    
    EnumList(ModelAnimationSegment, aSegment, mSegmentList)
    {
        if(aSegment->mID == pId)
        {
            aCurrent = aSegment;
        }
    }
    
    if(aCurrent)
    {
        mPlayID=pId;
        mPlayLoop=false;
        mPlay=true;
        
        mPlayFrameStart = aCurrent->mStartFrame;
        mPlayFrameEnd = aCurrent->mEndFrame;
        
        mPlayFrame = (float)mPlayFrameStart;
    }
    else
    {
        mPlayID=-1;
        mPlayLoop=pLoop;
        mPlay=false;
    }
}


//////
//////       End Internal Play Stuff
//////
////////////////////////////////////////////////////





















