//
//  MapScreenScrollContent.h
//  CrossBone
//
//  Created by Nick Raptis on 6/30/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#ifndef __CrossBone__MapScreenScrollContent__
#define __CrossBone__MapScreenScrollContent__

#include "FList.h"
#include "FView.h"
#include "FSpline.h"

class MapScreenNode;

class MapScreenScrollContent : public FView
{
public:
    
    MapScreenScrollContent();
    virtual ~MapScreenScrollContent();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    FList                                   mNodeList;
    
    MapScreenNode                           *mTouchNode;
};

#endif