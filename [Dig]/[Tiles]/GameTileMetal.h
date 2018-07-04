//
//  GameTileMetal.h
//  Digplex
//
//  Created by Nick Raptis on 11/25/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__GameTileMetal__
#define __Digplex__GameTileMetal__

#include "GameTile.h"



class GameTileMetal : public GameTile
{
public:
    
    GameTileMetal();
    virtual ~GameTileMetal();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawBuried();
    
    
    DamageFlashOscillator           mDamageFlash;
    virtual bool                    Damage(int pDamage){mDamageFlash.Hit();return GameTile::Damage(pDamage);}
    
    
};

#endif /* defined(__Digplex__GameTileMetal__) */
