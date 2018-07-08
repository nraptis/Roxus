//
//  SpriteSequenceNested.h
//  Mustache
//
//  Created by Nick Raptis on 9/9/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
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
    
    void                            LoadSequential(const char *pFilePrefix, int pStartIndex, int pSequenceCount, int pSequenceLength);
    
    FSpriteSequence                 *mSequence;
    int                             mSequenceCount;
    int                             mSequenceLength;
    
    
    void                            Draw(float pX, float pY, float pRotation, float pFrame);
    void                            Draw(float pX, float pY, float pRotation, float pFrame, float pScale, float pSpriteRotation=0.0f);
    void                            Center(float pX, float pY, float pRotation, float pFrame);
    
    
    
};


#endif
