//
//  CNVWorldContainer.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVWorldContainer_hpp
#define CNVWorldContainer_hpp

#include "FCanvas.hpp"
#include "CNVWorld.hpp"

class CNVWorldContainer : public FCanvas {
public:
    CNVWorldContainer();
    virtual ~CNVWorldContainer();
    
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
    
    CNVWorld                               *mWorld1;
    CNVWorld                               *mWorld2;
    
    float                                   mWobbleRot;
};

#endif /* CNVWorldContainer_hpp */
