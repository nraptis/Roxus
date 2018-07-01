//
//  TestBadgeDecor3Decor3.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestBadgeDecor3Decor3_hpp
#define TestBadgeDecor3Decor3_hpp

#include "FView.h"

class TestBadgeDecor3 : public FView {
public:
    TestBadgeDecor3();
    virtual ~TestBadgeDecor3();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};

#endif /* TestBadgeDecor3Decor3_hpp */
