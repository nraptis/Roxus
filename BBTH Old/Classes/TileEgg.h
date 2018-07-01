//
//  TileEgg.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/13/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef TILEEGG_H
#define TILEEGG_H

#include "Tile.h"

class TileEgg : public Tile
{
public:
    
    TileEgg();
    virtual ~TileEgg();
    
    virtual void                            Update();
    
    virtual void                            Draw();
    
    virtual void                            DrawEffectsUnder(int pDepth);
    virtual void                            DrawEffectsOver(int pDepth);
    
    virtual void                            Matched();
    
    
    void                                    SetUp(int pGridX, int pGridY, int pMatchType);
    
    int                                     mMatchType;
    
    void                                    Select();
    void                                    Deselect();
    
    
    
    float                                   mMatchAnimationFade;
    float                                   mMatchAnimationOuterFrame;
    float                                   mMatchAnimationInnerFrame;
    float                                   mMatchShakeX;
    float                                   mMatchShakeY;
    
    
};

#endif



