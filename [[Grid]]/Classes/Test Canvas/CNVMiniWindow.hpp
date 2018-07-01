//
//  CNVMiniWindow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/18/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVMiniWindow_hpp
#define CNVMiniWindow_hpp

#include "FCanvas.hpp"

class CNVMiniWindow : public FCanvas {
public:
    CNVMiniWindow();
    virtual ~CNVMiniWindow();
    
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
    
    float                                   mSpriCNVartAngle;
    float                                   mSpriteEndAngle;
    
};

#endif /* CNVMiniWindow_hpp */
