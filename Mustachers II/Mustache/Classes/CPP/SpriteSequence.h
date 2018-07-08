//
//  SpriteSequence.h
//  Mustache
//
//  Created by Nick Raptis on 9/9/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_SpriteSequence_h
#define Mustache_SpriteSequence_h

#include "Sprite.h"
#include "FileSequence.h"

class SpriteSequence
{
public:
    
    SpriteSequence();
    virtual ~SpriteSequence();
    
    void                            Free();
    
    Sprite                          *mSprite;
    int                             mSpriteCount;
    
    void                            Load(const char *pFilePrefix, int pStartIndex, int pEndIndex);
    
    
    void                            Draw(float pX, float pY, float pFrame);
    void                            Draw(float pX, float pY, float pFrame, float pScale, float pSpriteRotation=0.0f);
    void                            Center(float pX, float pY, float pFrame);
    
    
};

#endif
