//
//  TestBoard.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "DemoView.hpp"
#include "TestMiniWindow.hpp"
#include "FDrawQuad.h"

#ifndef TestBoard_hpp
#define TestBoard_hpp

class TestBoard : public DemoView {
public:
    TestBoard();
    virtual ~TestBoard();
    
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
    
    int                                     mGridWidth;
    int                                     mGridHeight;
    
    
    TestMiniWindow                          *mRotView1;
    TestMiniWindow                          *mRotView2;
    
    TestMiniWindow                          *mRotView1UT;
    TestMiniWindow                          *mRotView2UT;


    FDrawQuadSnake                          mSnake;
    FDrawNodeList                           mNodeList;
    
};

#endif /* TestBoard_hpp */
