//
//  BoardGenericLayer.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/15/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef BOARD_GENERIC_LAYER
#define BOARD_GENERIC_LAYER

#include "FString.h"

class BoardGenericLayer
{
public:
    
    BoardGenericLayer();
    virtual ~BoardGenericLayer();
    
    virtual void                            Free();
    virtual void                            SetSize(int pGridWidth, int pGridHeight);
    virtual void                            Resize(int pGridWidth, int pGridHeight);
    
    FString                                 mName;
    
    int                                     mWidth;
    int                                     mHeight;
    
};

#endif
