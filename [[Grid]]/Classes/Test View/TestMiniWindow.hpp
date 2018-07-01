//
//  TestMiniWindow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/18/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestMiniWindow_hpp
#define TestMiniWindow_hpp

#include "FView.h"

class TestMiniWindow : public FView {
public:
    TestMiniWindow();
    virtual ~TestMiniWindow();
    
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
    
    float                                   mSphereRotation1;
    float                                   mSphereRotation2;
    
    float                                   mSpriteStartAngle;
    float                                   mSpriteEndAngle;
    
};

#endif /* TestMiniWindow_hpp */
