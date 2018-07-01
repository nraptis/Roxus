//
//  TileMultiPart.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/2/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef TileMultiPart_hpp
#define TileMultiPart_hpp

#include "Tile.h"

class TileMulti;

class TileMultiPart : public Tile {
public:
    
    TileMultiPart();
    virtual ~TileMultiPart();
    
    
    virtual void                            DrawEffectsUnder(int pDepth);
    virtual void                            DrawEffectsOver(int pDepth);
    
    int                                     mGridOffsetX;
    int                                     mGridOffsetY;
    
    TileMulti                               *mMultiParent;
};

#endif /* TileMultiPart_hpp */
