//
//  TestBadgeDecor1Decor1.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestBadgeDecor1Decor1_hpp
#define TestBadgeDecor1Decor1_hpp

#include "FView.h"

class TestBadgeDecor1 : public FView {
public:
    TestBadgeDecor1();
    virtual ~TestBadgeDecor1();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};

#endif /* TestBadgeDecor1Decor1_hpp */
