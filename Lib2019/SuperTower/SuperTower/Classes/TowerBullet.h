//
//  TowerBulletBullet.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_TowerBulletBullet_h
#define Mustache_TowerBulletBullet_h

#include "GLApp.hpp"

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
