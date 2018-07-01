//
//  CNVWorld.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVWorld_hpp
#define CNVWorld_hpp

#include "FCanvas.hpp"
#include "CNVGame.hpp"

class CNVWorld : public FCanvas {
public:
    CNVWorld();
    virtual ~CNVWorld();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
    
    CNVGame                                *mGame;
    
    bool                                    mLarge;
};

#endif /* CNVWorld_hpp */
