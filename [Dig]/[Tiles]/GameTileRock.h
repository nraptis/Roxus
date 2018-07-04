//
//  GameTileRock.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__GameTileRock__
#define ___015_Jeep_Arcon__GameTileRock__

#include "GameTile.h"


class GameTileRock : public GameTile
{
public:
    
    GameTileRock();
    virtual ~GameTileRock();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawBuried();
    
    
    DamageFlashOscillator           mDamageFlash;
    virtual bool                    Damage(int pDamage){mDamageFlash.Hit();return GameTile::Damage(pDamage);}
    
    
};


#endif /* defined(___015_Jeep_Arcon__GameTileRock__) */
