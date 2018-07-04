//
//  BoardGenericActionLayer.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/15/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef BOARD_GENERIC_ACTION_LAYER_H
#define BOARD_GENERIC_ACTION_LAYER_H

#include "BoardGenericLayer.h"

class BoardGenericActionLayer : public BoardGenericLayer
{
public:
    
    BoardGenericActionLayer();
    virtual ~BoardGenericActionLayer();
    
    virtual void                            Free();
    virtual void                            SetSize(int pGridWidth, int pGridHeight);
    virtual void                            Resize(int pGridWidth, int pGridHeight);
    
    virtual void                            Flood(int pValue);
    
    
    virtual void                            Set(int pGridX, int pGridY, int pValue);
    
    //inline int                              *operator[](int pIndex){return 0;}
    int                                     Get(int pGridX, int pGridY);
    
    int                                     mWidth;
    int                                     mHeight;
    
    int                                     **mData;
    int                                     *mDataBase;
    
    int                                     mDefaultValue;
};

#endif
