//
//  TestBadgeDecor4Decor4.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestBadgeDecor4Decor4_hpp
#define TestBadgeDecor4Decor4_hpp

#include "FView.h"

class TestBadgeDecor4 : public FView {
public:
    TestBadgeDecor4();
    virtual ~TestBadgeDecor4();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};

#endif /* TestBadgeDecor4Decor4_hpp */
