//
//  CNVFooter.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/22/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVFooter_hpp
#define CNVFooter_hpp


#include "FCanvas.hpp"
#include "CNVBadge.hpp"

class CNVFooter : public FCanvas {
public:
    CNVFooter();
    virtual ~CNVFooter();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;

    CNVBadge                               *mBadgeLeft;
    CNVBadge                               *mBadgeRight;


    float                                   mInsetLeft;
    float                                   mInsetRight;
    float                                   mInsetBottom;


};

#endif /* CNVFooter_hpp */
