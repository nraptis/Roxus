//
//  CNVBoard.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "FCanvas.hpp"
#include "CNVMiniWindow.hpp"
#include "FDrawQuad.h"

#ifndef CNVBoard_hpp
#define CNVBoard_hpp

class CNVBoard : public FCanvas {
public:
    CNVBoard();
    virtual ~CNVBoard();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
    
    float                                   mSpriteRotation;
    
    float                                   mSphereRotation1;
    float                                   mSphereRotation2;
    
    float                                   mTestAngle;
    float                                   mSpriteEndAngle;
    
    int                                     mGridWidth;
    int                                     mGridHeight;
    
    
    CNVMiniWindow                          *mRotView1;
    CNVMiniWindow                          *mRotView2;
    
    CNVMiniWindow                          *mRotView1UT;
    CNVMiniWindow                          *mRotView2UT;


    FDrawQuadSnake                          mSnake;
    FDrawNodeList                           mNodeList;
    
};

#endif /* CNVBoard_hpp */
