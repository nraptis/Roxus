//
//  TestFooter.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/22/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestFooter_hpp
#define TestFooter_hpp


#include "FView.h"
#include "TestBadge.hpp"

class TestFooter : public FView {
public:
    TestFooter();
    virtual ~TestFooter();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            PositionContent();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;

    TestBadge                               *mBadgeLeft;
    TestBadge                               *mBadgeRight;


    float                                   mInsetLeft;
    float                                   mInsetRight;
    float                                   mInsetBottom;


};

#endif /* TestFooter_hpp */
