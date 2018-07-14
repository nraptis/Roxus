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
#include "FObject.h"

class GameObject : public FObject {
public:
    GameObject();
    virtual ~GameObject();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    float                               mX;
    float                               mY;
    float                               mZ;
    
    int                                 mDrawZ;
    
    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;
    
    
    
    void                                SetUp(int pGridX, int pGridY);
    void                                SetUp(int pGridX, int pGridY, int pGridZ);
};


#endif
