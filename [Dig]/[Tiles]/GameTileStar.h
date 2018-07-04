//
//  GameTileStar.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__GameTileStar__
#define ___015_Jeep_Arcon__GameTileStar__

#include "GameTile.h"

class GameTileStar : public GameTile
{
public:
    
    GameTileStar();
    virtual ~GameTileStar();
    
    virtual void                            Update();
    
    virtual void                            Draw();
    
    int                                     mStarIndex;
    
    virtual void                            Save(FXMLTag *pTag);
    virtual void                            Load(FXMLTag *pTag);
    
};

#endif /* defined(___015_Jeep_Arcon__GameTileStar__) */
