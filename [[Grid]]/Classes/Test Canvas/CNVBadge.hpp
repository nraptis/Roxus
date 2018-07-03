//
//  CNVBadge.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVBadge_hpp
#define CNVBadge_hpp

#include "FCanvas.hpp"
#include "CNVBadgeDecor1.hpp"
#include "CNVBadgeDecor2.hpp"
#include "CNVBadgeDecor3.hpp"
#include "CNVBadgeDecor4.hpp"


class CNVBadge : public FCanvas {
public:
    CNVBadge();
    virtual ~CNVBadge();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;

    CNVBadgeDecor1                         mDecor1;
    CNVBadgeDecor2                         mDecor2;
    CNVBadgeDecor3                         mDecor3;
    CNVBadgeDecor4                         *mDecor4;

    float                                   mFrame;

};

#endif /* CNVBadge_hpp */
