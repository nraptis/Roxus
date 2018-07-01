//
//  TestWorldContainerContainerContainer.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/17/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestWorldContainerContainerContainer_hpp
#define TestWorldContainerContainerContainer_hpp

#include "DemoView.hpp"
#include "TestWorldContainer.hpp"

class TestWorldContainerContainer : public FView {
public:
    TestWorldContainerContainer();
    virtual ~TestWorldContainerContainer();
    
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
    
    TestWorldContainer                      *mWorldContainer;
    
};

#endif /* TestWorldContainerContainer_hpp */

