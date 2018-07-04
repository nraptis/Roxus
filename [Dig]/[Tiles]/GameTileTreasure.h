//
//  GameTileTreasure.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef TILE_TREASURE_H
#define TILE_TREASURE_H

#include "GameTile.h"

class GameTileTreasure : public GameTile
{
public:
    
    GameTileTreasure();
    virtual ~GameTileTreasure();
    
    virtual void                    Update();
    
    virtual void                    Draw();
    virtual void                    DrawTop();
    //int                             mSlateIndex;
};


#endif /* defined(___015_Jeep_Arcon__GameTileTreasure__) */
