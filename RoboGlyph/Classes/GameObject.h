//
//  GameObject.h
//  Mustache
//
//  Created by Nick Raptis on 7/8/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_GameObject_h
#define Mustache_GameObject_h

#include "GLApp.h"

class GameObject {
public:

    GameObject();
    virtual ~GameObject();
    
    float                               mX;
    float                               mY;
    float                               mZ;
    
    int                                 mDrawZ;
    
    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;
    
    int                                 mKill;
    void                                Kill(){mKill=6;}
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                SetUp(int pGridX, int pGridY);
    void                                SetUp(int pGridX, int pGridY, int pGridZ);
};


#endif
