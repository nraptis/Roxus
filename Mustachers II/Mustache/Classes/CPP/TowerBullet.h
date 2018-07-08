//
//  TowerBulletBullet.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_TowerBulletBullet_h
#define Mustache_TowerBulletBullet_h

#include "GLApp.h"

class TowerBullet
{
public:
    
    TowerBullet();
    virtual ~TowerBullet();
    
    GLApp                               *mApp;
    
    virtual void                        Update();
    virtual void                        Draw();
};

#endif
