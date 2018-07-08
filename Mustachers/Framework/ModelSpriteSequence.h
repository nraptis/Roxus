//
//  ModelSpriteSequence.h
//  LizDash
//
//  Created by Nick Raptis on 9/2/12.
//
//

#ifndef LizDash_ModelSpriteSequence_h
#define LizDash_ModelSpriteSequence_h

#include "Sprite.h"
#include "ModelData.h"
#include "FileSequence.h"

class ModelSpriteSequence : ModelDataIndexed
{
public:
    
    ModelSpriteSequence();
    virtual ~ModelSpriteSequence();
    
    float                                   **mUVWList;
    Sprite                                  **mSprite;
    int                                     mCount;
    
    virtual void                            Free();
    
    virtual void                            Load(const char *pModelPath, const char *pPrefix, int pStartIndex, int pEndIndex, const char *pSuffix=0);
    virtual void                            Draw(float pFrame);
    
    
};


#endif
