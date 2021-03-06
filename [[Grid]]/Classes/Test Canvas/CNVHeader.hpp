//
//  CNVHeader.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVHeader_hpp
#define CNVHeader_hpp

#include "FCanvas.hpp"

class CNVHeader : public FCanvas {
public:
    CNVHeader();
    virtual ~CNVHeader();
    
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

    float                                   mInsetLeft;
    float                                   mInsetRight;
    float                                   mInsetTop;

    //mInterfaceBottom.Load("game_interface_bottom_back_colored");
    //mInterfaceBottomGray.Load("game_interface_bottom_back_grey");


    
};

#endif /* CNVHeader_hpp */
