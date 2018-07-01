//
//  CNVBadgeDecor1Decor1.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVBadgeDecor1Decor1_hpp
#define CNVBadgeDecor1Decor1_hpp

#include "FCanvas.hpp"

class CNVBadgeDecor1 : public FCanvas {
public:
    CNVBadgeDecor1();
    virtual ~CNVBadgeDecor1();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};

#endif /* CNVBadgeDecor1Decor1_hpp */
