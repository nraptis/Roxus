//
//  GameTileCoin.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef TILE_COIN_H
#define TILE_COIN_H

#include "GameTile.h"

class GameTileCoin : public GameTile
{
public:
    
    GameTileCoin();
    virtual ~GameTileCoin();
    
    virtual void                    Update();
    
    virtual void                    Draw();
    virtual void                    DrawTop();
    
    int                             mValue;
    
    
    
    
    float                           mRotation;
    
    //int                             mSlateIndex;
};


#endif /* defined(___015_Jeep_Arcon__GameTileCoin__) */
