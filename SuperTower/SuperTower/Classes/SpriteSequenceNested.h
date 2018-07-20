//
//  SpriteSequenceNested.h
//  Mustache
//
//  Created by Nick Raptis on 9/9/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_SpriteSequenceNested_h
#define Mustache_SpriteSequenceNested_h

#include "FSpriteSequence.h"

class SpriteSequenceNested
{
public:
    
    SpriteSequenceNested();
    virtual ~SpriteSequenceNested();
    
    void                            Free();
    
    void                            LoadSection(const char *pFilePrefix, int pSectionStartIndex, int pSectionEndIndex, int pSectionLeadingZeros, const char *pSeparator, int pStartIndex, int pEndIndex);

    FList                           mSequenceList;
    //FSpriteSequence                 *mSequence;
    //int                             mSequenceCount;
    //int                             mSequenceLength;

    //Assuming all sequences have the same number of frames...
    //This is the count of the sequence, not the number of sequnces...
    int                             mSequenceFrameCount;
    
    void                            Draw(float pX, float pY, float pRotation, float pFrame, float pScale, float pSpriteRotation=0.0f);
    void                            Center(float pX, float pY, float pRotation, float pFrame);
    
};


#endif
