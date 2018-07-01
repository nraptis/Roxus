//
//  TestBadge.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestBadge_hpp
#define TestBadge_hpp

#include "FView.h"
#include "TestBadgeDecor1.hpp"
#include "TestBadgeDecor2.hpp"
#include "TestBadgeDecor3.hpp"
#include "TestBadgeDecor4.hpp"


class TestBadge : public FView {
public:
    TestBadge();
    virtual ~TestBadge();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;

    TestBadgeDecor1                         mDecor1;
    TestBadgeDecor2                         mDecor2;
    TestBadgeDecor3                         mDecor3;
    TestBadgeDecor4                         mDecor4;

    float                                   mLoopFrame;

};

#endif /* TestBadge_hpp */
