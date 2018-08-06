//
//  SmallGameObject.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/26/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef SMALL_GAME_OBJECT_HPP
#define SMALL_GAME_OBJECT_HPP

#include "GLApp.hpp"
#include "FObject.h"

class SmallGameObject : public FObject {
public:
    SmallGameObject();
    virtual ~SmallGameObject();

    virtual void                        Update();
    virtual void                        Draw();

    float                               mX;
    float                               mY;
    float                               mZ;
    
    //On which render pass do we draw this object? (Hiding behind bridge, etc)
    int                                 mDrawZ;

    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;

    //void                                SetUp(int pGridX, int pGridY);
    void                                SetUp(int pGridX, int pGridY, int pGridZ);
};

#endif
