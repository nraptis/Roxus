//
//  MapScreenNode.h
//  CrossBone
//
//  Created by Nick Raptis on 6/30/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#ifndef __CrossBone__MapScreenNode__
#define __CrossBone__MapScreenNode__

class MapScreenNode
{
public:
    
    MapScreenNode();
    virtual ~MapScreenNode();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    Select();
    void                                    Deselect();
    
    float                                   mCenterX;
    float                                   mCenterY;
    
    bool                                    mComplete;
    
    bool                                    mSelected;
    
    bool                                    mStarEarned[3];
};

#endif /* defined(__CrossBone__MapScreenNode__) */
