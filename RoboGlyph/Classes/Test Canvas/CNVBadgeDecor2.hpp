//
//  CNVBadgeDecor2Decor2.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVBadgeDecor2Decor2_hpp
#define CNVBadgeDecor2Decor2_hpp

#include "FCanvas.hpp"

class CNVBadgeDecor2 : public FCanvas {
public:
    CNVBadgeDecor2();
    virtual ~CNVBadgeDecor2();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};
#endif /* CNVBadgeDecor2Decor2_hpp */
