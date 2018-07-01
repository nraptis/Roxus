//
//  TestHeader.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestHeader_hpp
#define TestHeader_hpp

#include "FView.h"

class TestHeader : public FView {
public:
    TestHeader();
    virtual ~TestHeader();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
    
    float                                   mSpriteRotation;

    float                                   mInsetLeft;
    float                                   mInsetRight;
    float                                   mInsetTop;

    //mInterfaceBottom.Load("game_interface_bottom_back_colored");
    //mInterfaceBottomGray.Load("game_interface_bottom_back_grey");


    
};

#endif /* TestHeader_hpp */
