//
//  TempView.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/14/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef TempView_hpp
#define TempView_hpp

#include "FView.h"

class TempView : public FView {
public:
    TempView();
    virtual ~TempView();
    
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

#endif /* TempView_hpp */
