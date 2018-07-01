//
//  TileMulti.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/2/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef TileMulti_hpp
#define TileMulti_hpp

#include "Tile.h"
#include "TileMultiPart.h"

class TileMulti : public Tile {
    
public:
    TileMulti();
    virtual ~TileMulti();
    
    virtual void                            SetUp(int pGridX, int pGridY);
    
    virtual void                            Draw();
    
    void                                    AddPart(int pGridX, int pGridY);
    FList                                   mPartList;
    
};



#endif /* TileMulti_hpp */
