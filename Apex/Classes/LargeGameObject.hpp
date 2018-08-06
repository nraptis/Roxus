//
//  LargeGameObject.h
//  Mustache
//
//  Created by Nick Raptis on 7/8/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef LARGE_GAME_OBJECT_HPP
#define LARGE_GAME_OBJECT_HPP

#include "GLApp.hpp"
#include "FObject.h"

class LargeGameObject : public FObject {
public:
    LargeGameObject();
    virtual ~LargeGameObject();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    float                               mX;
    float                               mY;
    float                               mZ;

    int                                 mDrawZ;

    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;

    //void                                SetUp(int pGridX, int pGridY);
    void                                SetUp(int pGridX, int pGridY, int pGridZ);
};

#endif

