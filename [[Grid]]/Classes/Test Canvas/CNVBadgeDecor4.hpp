//
//  CNVBadgeDecor4Decor4.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef CNVBadgeDecor4Decor4_hpp
#define CNVBadgeDecor4Decor4_hpp

#include "FCanvas.hpp"

class CNVBadgeDecor4 : public FCanvas {
public:
    CNVBadgeDecor4();
    virtual ~CNVBadgeDecor4();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Layout();
    
    FColor                                  mTouchMarkerColor1;
    FColor                                  mTouchMarkerColor2;
};

#endif /* CNVBadgeDecor4Decor4_hpp */
