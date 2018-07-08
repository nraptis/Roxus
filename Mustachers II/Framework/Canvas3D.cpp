//
//  Canvas3D.cpp
//  Lancia
//
//  Created by Nick Raptis on 8/30/12.
//
//

#include "Application.h"
#include "Canvas3D.h"
#include "Graphics.h"

Canvas3D::Canvas3D()
{
    mCameraX = 10.0f;
    mCameraY = 6.0f;
    mCameraZ = 2.5f;
    
    mCameraTargetX = 0.0f;
    mCameraTargetY = 0.0f;
    mCameraTargetZ = 0.0f;
    
    mCameraDistance=9.0f;
    mCameraHeight=1.5f;
    mCameraRotaion=0.0f;
    
    
    mCameraAspect = (float)gAppWidth / (float)gAppHeight;
    mCameraFOV = 64.0f;
    
    /*
    float                               mCameraDistance;
    float                               mCameraRotaion;
    
    float                               mCameraX;
    float                               mCameraY;
    float                               mCameraZ;
    
    float                               mCameraTargetX;
    float                               mCameraTargetY;
    float                               mCameraTargetZ;
    
    float                               mCameraFOV;
    */
    
    /*
    mCameraHeight = -7.25f;
    mCameraOffsetX = 0.0f;
    mCameraOffsetY = 0.0f;
    mCameraOffsetZ = 5.8f;
    mCameraFOV = 64.0f;
    mCameraDist = 25.87f;
    mCameraRotaionTarget = 0.0f;
    mCameraRotaionOffset = 0.0f;
    mCameraRotaion = 0.0f;
    */
}

Canvas3D::~Canvas3D()
{
    
}

void Canvas3D::Go3D()
{
    //Clip(0.0f,0.0f,gAppWidth,gAppHeight);
    
    Graphics::MatrixGoProjection();
    Graphics::MatrixLoadIdentity();
    
    Graphics::MatrixPerspective(mCameraFOV, mCameraAspect);
    
    Graphics::MatrixGoModelView();
    Graphics::MatrixLoadIdentity();
    
    float aDirX = Sin(mCameraRotaion);
    float aDirY = Cos(mCameraRotaion);
    
    mCameraX = mCameraTargetX + aDirX * mCameraDistance;
    mCameraY = mCameraTargetY + aDirY * mCameraDistance;
    mCameraZ = mCameraHeight;
    
    Graphics::MatrixLookAt(mCameraX, mCameraY, mCameraZ,
                               mCameraTargetX,mCameraTargetY,mCameraTargetZ,
                               0,0,1.0f);
    Graphics::SetShadeSmooth();
    
    
    Graphics::ClearDepth(0.1f,0.0f,0.0f);
    Graphics::EnableDepth();
    
    //GL_COLOR_BUFFER_BIT
    //Indicates the buffers currently enabled for color
    //    writing.
    //    GL_DEPTH_BUFFER_BIT
    
    Graphics::EnableCullFaces();
    Graphics::DepthMaskTrue();
    
}

void Canvas3D::Go2D()
{
    
    Graphics::Go2D();
    Graphics::DepthMaskTrue();
    Graphics::BlendSetAlpha();// ();// ();
    
    
}


