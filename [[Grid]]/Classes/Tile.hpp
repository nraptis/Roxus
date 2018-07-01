//
//  Tile.hpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 4/28/16.
//  Copyright © 2016 Nick Raptis. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "FObject.h"

class Tile : public FObject
{
public:
    Tile();
    virtual ~Tile();
    
    virtual void                        SetUp(int pGridX, int pGridY, int pMatchType=-1);
    
    virtual void                        Update();
    virtual void                        Draw();
    
    
    
    
};


#endif /* Tile_hpp */
