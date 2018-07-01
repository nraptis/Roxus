//
//  TestWorldContainer.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestWorldContainer_hpp
#define TestWorldContainer_hpp

#include "DemoView.hpp"
#include "TestWorld.hpp"

class TestWorldContainer : public DemoView {
public:
    TestWorldContainer();
    virtual ~TestWorldContainer();
    
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
    
    TestWorld                               *mWorld1;
    TestWorld                               *mWorld2;
    
    float                                   mWobbleRot;
};

#endif /* TestWorldContainer_hpp */
