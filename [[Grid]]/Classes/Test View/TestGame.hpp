//
//  TestGame.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TestGame_hpp
#define TestGame_hpp

#include "DemoView.hpp"
#include "TestBoard.hpp"
#include "TestHeader.hpp"
#include "TestFooter.hpp"

class TestGame : public DemoView {
public:
    TestGame();
    virtual ~TestGame();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            PositionContent();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
    
    TestBoard                               *mBoard;

    TestHeader                              mHeader;
    TestFooter                              mFooter;
    
};

#endif /* TestGame_hpp */
