//
//  CNVBadgeDecor3Decor3.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVBadgeDecor3Decor3_hpp
#define CNVBadgeDecor3Decor3_hpp

#include "FCanvas.hpp"

class CNVBadgeDecor3 : public FCanvas {
public:
    CNVBadgeDecor3();
    virtual ~CNVBadgeDecor3();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};

#endif /* CNVBadgeDecor3Decor3_hpp */
