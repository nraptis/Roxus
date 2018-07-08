//
//  MeshGround.h
//  DoomKnights
//
//  Created by Nick Raptis on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MESH_GROUND_H
#define MESH_GROUND_H

#include "Spline3D.h"

class MeshGround
{
public:
    
    MeshGround();
    virtual ~MeshGround();
    
    void                                Clear();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    int                                 mControlWidth;
    int                                 mControlHeight;
    
    int                                 mRenderWidth;
    int                                 mRenderHeight;
    
    int                                 mRenderFidelity;
    
    void                                Size(int pWidth, int pHeight, float pSize=6.0f);
    
    void                                Generate();
    
    
    float                               *mControlData;
    
    float                               **mControlX;
    float                               **mControlY;
    float                               **mControlZ;
    
    float                               *mRenderData;
    
    float                               **mRenderX;
    float                               **mRenderY;
    float                               **mRenderZ;
    
    float                               **mRenderU;
    float                               **mRenderV;
    float                               **mRenderW;
    
    float                               **mRenderNormalX;
    float                               **mRenderNormalY;
    float                               **mRenderNormalZ;
    
    int                                 **mRenderIndex;
    
    
};



#endif
