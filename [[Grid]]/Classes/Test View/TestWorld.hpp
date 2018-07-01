//
//  TestWorld.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestWorld_hpp
#define TestWorld_hpp

#include "DemoView.hpp"
#include "TestGame.hpp"

class TestWorld : public DemoView {
public:
    TestWorld();
    virtual ~TestWorld();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
    
    TestGame                                *mGame;
    
    bool                                    mLarge;
};

#endif /* TestWorld_hpp */
