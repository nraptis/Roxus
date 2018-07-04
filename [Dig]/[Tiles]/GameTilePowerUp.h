//
//  GameTilePowerUp.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/28/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__GameTilePowerUp__
#define ___015_Jeep_Arcon__GameTilePowerUp__

#include "GameTile.h"

class GameTilePowerUp : public GameTile
{
public:
    GameTilePowerUp();
    virtual ~GameTilePowerUp();
    
    virtual void                            Update();
    
    virtual void                            Draw();
    virtual void                            DrawBuried();
    
};

#endif /* defined(___015_Jeep_Arcon__GameTilePowerUp__) */
