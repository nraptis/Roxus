//
//  SpriteSequenceNested.cpp
//  Mustache
//
//  Created by Nick Raptis on 9/9/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "SpriteSequenceNested.h"
#include "core_includes.h"

SpriteSequenceNested::SpriteSequenceNested() {
    mSequenceFrameCount = 0;
}

SpriteSequenceNested::~SpriteSequenceNested() {
    Free();
}

void SpriteSequenceNested::Free() {
    FreeList(FSpriteSequence, mSequenceList);
}

//ninja_rot_00_0300@1x.png

void SpriteSequenceNested::LoadSection(const char *pFilePrefix, int pSectionStartIndex, int pSectionEndIndex, int pSectionLeadingZeros, const char *pSeparator, int pStartIndex, int pEndIndex) {

    FString aBaseFilePath = FString(pFilePrefix);
    FString aSeparator = FString(pSeparator);

    for (int aIndex=pSectionStartIndex;aIndex<=pSectionEndIndex;aIndex++) {
        FString aNumberString = FString(aIndex);
        if (aNumberString.mLength < pSectionLeadingZeros) {
            FString aZeroString;
            aZeroString.InsChars('0', (pSectionLeadingZeros - aNumberString.mLength), 0);
            aNumberString = FString(aZeroString + aNumberString);
        }
        FString aPath = aBaseFilePath + aNumberString + aSeparator;

        FSpriteSequence *aSequence = new FSpriteSequence();
        aSequence->Load(aPath, pStartIndex, pEndIndex);
        if (aSequence->mList.mCount > 0) {

            if (aSequence->mList.mCount > mSequenceFrameCount) {
                mSequenceFrameCount = aSequence->mList.mCount;
            }
            mSequenceList.Add(aSequence);
        } else {
            delete aSequence;
        }
    }
}

/*
void SpriteSequenceNested::LoadSequential(const char *pFilePrefix, int pStartIndex, int pSequenceCount, int pSequenceLength) {
    if(pSequenceCount > 0 && pSequenceLength > 0) {
        mSequenceCount = pSequenceCount;
        mSequenceLength = pSequenceLength;
        mSequence = new FSpriteSequence[mSequenceCount];
        int aStartIndex = pStartIndex;
        int aEndIndex = (pStartIndex + pSequenceLength) - 1;
        for(int aIndex=0;aIndex<mSequenceCount;aIndex++) {
            printf("Loading[%d] [%d to %d]\n", aIndex, aStartIndex, aEndIndex);
            mSequence[aIndex].Load(pFilePrefix, aStartIndex, aEndIndex);
            aStartIndex += pSequenceLength;
            aEndIndex += pSequenceLength;
        }
    }
}
*/

void SpriteSequenceNested::Draw(float pRotation, float pFrame, float pX, float pY, float pScale, float pSpriteRotation) {
    if(pRotation < -360.0f || pRotation > 1080.0f)pRotation = fmodf(pRotation, 360.0f);
    while(pRotation >= 360.0f)pRotation -= 360.0f;
    while(pRotation < 0)pRotation += 360.0f;
    int aFrame = (int)((float)mSequenceList.mCount * (pRotation / 360.0f));
    if(aFrame >= mSequenceList.mCount)aFrame = (mSequenceList.mCount - 1);
    if(aFrame < 0)aFrame = 0;
    FSpriteSequence *aSequence = (FSpriteSequence *)mSequenceList.Fetch(aFrame);
    if (aSequence != 0) {
        aSequence->Draw(pFrame, pX, pY, pScale, pSpriteRotation);
    }
}

void SpriteSequenceNested::Center(float pX, float pY, float pRotation, float pFrame) {
    Draw(pX, pY, pRotation, pFrame, 1.0f, 0.0f);
}
