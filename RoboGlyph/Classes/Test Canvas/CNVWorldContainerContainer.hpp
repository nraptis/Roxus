//
//  CNVWorldContainerContainerContainer.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/17/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVWorldContainerContainerContainer_hpp
#define CNVWorldContainerContainerContainer_hpp

#include "FCanvas.hpp"
#include "CNVWorldContainer.hpp"

class CNVWorldContainerContainer : public FCanvas {
public:
    CNVWorldContainerContainer();
    virtual ~CNVWorldContainerContainer();
    
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
    
    CNVWorldContainer                      *mWorldContainer;
    
};

#endif /* CNVWorldContainerContainer_hpp */

