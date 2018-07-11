//
//  SpriteSequenceNested.cpp
//  Mustache
//
//  Created by Nick Raptis on 9/9/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "SpriteSequenceNested.h"
#include "core_includes.h"

SpriteSequenceNested::SpriteSequenceNested()
{
    mSequence = 0;
    mSequenceCount = 0;
    mSequenceLength = 0;
}

SpriteSequenceNested::~SpriteSequenceNested()
{
    Free();
}

void SpriteSequenceNested::Free() {
    for (int i=0;i<mSequenceCount;i++) {
        //delete mSequence[i]

    }
    
    delete [] mSequence;
    mSequence = 0;
    
    mSequenceCount = 0;
    mSequenceLength = 0;
}

void SpriteSequenceNested::LoadSequential(const char *pFilePrefix, int pStartIndex, int pSequenceCount, int pSequenceLength)
{
    Free();
    
    if(pSequenceCount > 0 && pSequenceLength > 0)
    {
        mSequenceCount = pSequenceCount;
        mSequenceLength = pSequenceLength;
        
        mSequence = new FSpriteSequence[mSequenceCount];
        
        int aStartIndex = pStartIndex;
        int aEndIndex = (pStartIndex + pSequenceLength) - 1;
        
        for(int aIndex=0;aIndex<mSequenceCount;aIndex++)
        {
            printf("Loading[%d] [%d to %d]\n", aIndex, aStartIndex, aEndIndex);
            
            mSequence[aIndex].Load(pFilePrefix, aStartIndex, aEndIndex);
            
            aStartIndex += pSequenceLength;
            aEndIndex += pSequenceLength;
        }
    }
}


void SpriteSequenceNested::Draw(float pX, float pY, float pRotation, float pFrame)
{
    
}

void SpriteSequenceNested::Draw(float pX, float pY, float pRotation, float pFrame, float pScale, float pSpriteRotation)
{
    if(pRotation < -360.0f || pRotation > 1080.0f)pRotation = fmodf(pRotation, 360.0f);
    
    while(pRotation >= 360.0f)pRotation -= 360.0f;
    while(pRotation < 0)pRotation += 360.0f;
    
    int aFrame = (int)((float)mSequenceCount * (pRotation / 360.0f));
    
    if(aFrame >= mSequenceCount)aFrame = (mSequenceCount - 1);
    if(aFrame < 0)aFrame = 0;
    
    if(mSequenceCount > 0)
    {
        mSequence[aFrame].Draw(pX, pY, pFrame, pScale, pSpriteRotation);
    }
}

void SpriteSequenceNested::Center(float pX, float pY, float pRotation, float pFrame)
{
    if(pRotation < -360.0f || pRotation > 1080.0f)pRotation = fmodf(pRotation, 360.0f);
    
    while(pRotation >= 360.0f)pRotation -= 360.0f;
    while(pRotation < 0)pRotation += 360.0f;
    
    int aFrame = (int)((float)mSequenceCount * (pRotation / 360.0f));
    
    if(aFrame >= mSequenceCount)aFrame = (mSequenceCount - 1);
    if(aFrame < 0)aFrame = 0;
    
    if(mSequenceCount > 0)
    {
        mSequence[aFrame].Center(pX, pY, pFrame);
    }
}
