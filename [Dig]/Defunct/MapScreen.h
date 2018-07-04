//
//  MapScreen.h
//  CrossBone
//
//  Created by Nick Raptis on 6/30/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#ifndef __CrossBone__MapScreen__
#define __CrossBone__MapScreen__

#include "FScrollView.h"
#include "MapScreenScrollContent.h"

class MapScreen : public FScrollView
{
public:
    
    MapScreen();
    virtual ~MapScreen();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    MapScreenScrollContent                  mMapScreenScrollContent;
    
};

#endif /* defined(__CrossBone__MapScreen__) */
