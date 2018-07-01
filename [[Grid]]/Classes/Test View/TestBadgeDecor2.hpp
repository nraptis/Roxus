//
//  TestBadgeDecor2Decor2.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestBadgeDecor2Decor2_hpp
#define TestBadgeDecor2Decor2_hpp

#include "FView.h"

class TestBadgeDecor2 : public FView {
public:
    TestBadgeDecor2();
    virtual ~TestBadgeDecor2();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};
#endif /* TestBadgeDecor2Decor2_hpp */
