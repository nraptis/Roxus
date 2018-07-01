//
//  FInterp.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FInterp__
#define __DigMMMac__FInterp__

#include "FFloatList.h"

class FInterp
{
public:
    FInterp();
    ~FInterp();
    
    void                            Add(float pPercent);
    void                            Reset();
    void                            Clear();
    
    float                           Get(float pPercent, float pMaxPercent, int &pIndexStart, int &pIndexEnd);
    
    FFloatList                      mPercentList;
    
    
    //void                        Set(float)
    
    
    
};

#endif /* defined(__DigMMMac__FInterp__) */
