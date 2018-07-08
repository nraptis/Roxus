//
//  Canvas3D.h
//  Lancia
//
//  Created by Nick Raptis on 8/30/12.
//
//

#ifndef CANVAS_3D_H
#define CANVAS_3D_H

#include "Canvas.h"

class Canvas3D : public Canvas
{
public:
    
    Canvas3D();
    virtual ~Canvas3D();
    
    virtual void                        Go3D();
    virtual void                        Go2D();
    
    /////////////////////////////////////////
    //
    //          Camera Baseline Stuff
    //
    
    float                               mCameraX;
    float                               mCameraY;
    float                               mCameraZ;
    
    float                               mCameraTargetX;
    float                               mCameraTargetY;
    float                               mCameraTargetZ;
    
    float                               mCameraFOV;
    float                               mCameraAspect;
    
    //
    /////////////////////////////////////////
    
    
    /////////////////////////////////////////
    //
    //          Camera Swivel Stuff
    //
    
    float                               mCameraDistance;
    float                               mCameraHeight;
    float                               mCameraRotaion;
    
    //
    /////////////////////////////////////////
    
    
};

#endif
