//
//  MeshGround.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MeshGround.h"
#include "GLApp.h"

MeshGround::MeshGround()
{
    mControlWidth=0;
    mControlHeight=0;
    
    mRenderWidth=0;
    mRenderHeight=0;
    
    mRenderFidelity=6;
    
    mControlData=0;
    
    mControlX=0;
    mControlY=0;
    mControlZ=0;
    
    mRenderX=0;
    mRenderY=0;
    mRenderZ=0;
    
    mRenderU=0;
    mRenderV=0;
    mRenderW=0;
    
    mRenderNormalX=0;
    mRenderNormalY=0;
    mRenderNormalZ=0;
}

MeshGround::~MeshGround()
{
    mControlWidth=0;
    mControlHeight=0;
    
    mRenderWidth=0;
    mRenderHeight=0;
    
    mRenderFidelity=0;
    
    mControlData=0;
    
    mControlX=0;
    mControlY=0;
    mControlZ=0;
    
    mRenderX=0;
    mRenderY=0;
    mRenderZ=0;
    
    mRenderU=0;
    mRenderV=0;
    mRenderW=0;
    
    mRenderNormalX=0;
    mRenderNormalY=0;
    mRenderNormalZ=0;
}


void MeshGround::Clear()
{
    
}

void MeshGround::Update()
{
    
    
}

void MeshGround::Draw()
{
    for(int i=0;i<mControlWidth;i++)
    {
        for(int n=0;n<mControlHeight;n++)
        {
            
            Graphics::MatrixPush();
            Graphics::Translate(mControlX[i][n], mControlY[i][n], mControlZ[i][n]);
            Graphics::Scale(0.25f);
            Graphics::Rotate(5.0f);
            
            //GAPP->mTestSphere->Draw();
            
            Graphics::MatrixPop();
            
            //GAPP->mTestSphere.Dr
            
        }
    }
    
    SetColor(1,0,0);
    Generate();
    SetColor();
}

void MeshGround::Size(int pWidth, int pHeight, float pSize)
{
    mControlWidth=pWidth;
    mControlHeight=pHeight;
    
    mRenderWidth=mControlWidth * mRenderFidelity;
    mRenderHeight=mControlHeight * mRenderFidelity;
    
    int aControlArea = mControlWidth * mControlHeight;
    int aRenderArea = mRenderWidth * mRenderHeight;
    
    mControlData = new float[aControlArea * 3];
    
    mControlX=new float*[mControlWidth];
    mControlY=new float*[mControlWidth];
    mControlZ=new float*[mControlWidth];
    
    
    float *aNode = mControlData;
    
    for(int i=0;i<mControlWidth;i++)
    {
        mControlX[i]=aNode;
        aNode += mControlHeight;
    }
    
    for(int i=0;i<mControlWidth;i++)
    {
        mControlY[i]=aNode;
        aNode += mControlHeight;
    }
    
    for(int i=0;i<mControlWidth;i++)
    {
        mControlZ[i]=aNode;
        aNode += mControlHeight;
    }
    
    for(int i=0;i<mControlWidth;i++)
    {
        for(int n=0;n<mControlHeight;n++)
        {
            mControlX[i][n] = pSize * i;
            mControlY[i][n] = pSize * n;
            mControlZ[i][n] = 2.0f + gRand.GetFloat() * 2.25f;
        }
    }
    
    mRenderData = new float[aRenderArea * 27];
    aNode = mRenderData;
    
    mRenderX=new float*[mRenderWidth];
    mRenderY=new float*[mRenderWidth];
    mRenderZ=new float*[mRenderWidth];
    
    mRenderU=new float*[mRenderWidth];
    mRenderV=new float*[mRenderWidth];
    mRenderW=new float*[mRenderWidth];
    
    mRenderNormalX=new float*[mRenderWidth];
    mRenderNormalY=new float*[mRenderWidth];
    mRenderNormalZ=new float*[mRenderWidth];
    
    
    for(int i=0;i<mRenderWidth;i++)
    {
        mRenderX[i]=aNode;
        aNode += mRenderHeight;
    }
    for(int i=0;i<mRenderWidth;i++)
    {
        mRenderY[i]=aNode;
        aNode += mRenderHeight;
    }
    for(int i=0;i<mRenderWidth;i++)
    {
        mRenderZ[i]=aNode;
        aNode += mRenderHeight;
    }

    
}


void MeshGround::Generate()
{
    Spline3D **aSplineGrid=new Spline3D*[mControlWidth + 1];
    
    for(int i=0;i<mControlWidth;i++)
    {
        aSplineGrid[i]=new Spline3D();
        
        for(int n=0;n<mControlHeight;n++)
        {
            aSplineGrid[i]->Add(mControlX[i][n], mControlY[i][n], mControlZ[i][n]);
            
        }
        
        for(float k=0;k<aSplineGrid[i]->Max();k+=0.1f)
        {
            float aX=aSplineGrid[i]->GetX(k);
            float aY=aSplineGrid[i]->GetY(k);
            float aZ=aSplineGrid[i]->GetZ(k);
            
            //Graphics::MatrixPush();
            //Graphics::Translate(aX, aY, aZ);
            //Graphics::Scale(0.066f);
            
            //GAPP->mTestSphere->Draw();
            
            //Graphics::MatrixPop();
            
        }
    }
    
    
    Spline3D aSpline;
    
    
    float aXPercent=0, aSplinePos=0;
    
    SetColor(0.0f, 1.0f, 0.33f, 0.25f);
    
    for(int i=0;i<mRenderWidth;i++)
    {
        aXPercent = (float)i / (float)(mRenderWidth-1);
        float aX, aY, aZ;
        aSpline.mPointCount=0;
        for(int k=0;k<mControlWidth;k++)
        {
            aSplinePos = aXPercent * (float)aSplineGrid[k]->Max();
			
            aX = aSplineGrid[k]->GetX(aSplinePos);
            aY = aSplineGrid[k]->GetY(aSplinePos);
            aZ = aSplineGrid[k]->GetZ(aSplinePos);
			
            aSpline.Add(aX, aY, aZ);
        }
        
        for(int n=0;n<mRenderWidth;n++)
        {
            aSplinePos = ((float)n / (float)(mRenderWidth-1)) * (float)aSpline.Max();
            
            aX = aSpline.GetX(aSplinePos);
            aY = aSpline.GetY(aSplinePos);
            aZ = aSpline.GetZ(aSplinePos);
            
            Graphics::MatrixPush();
            Graphics::Translate(aX, aY, aZ);
            Graphics::Scale(0.066f);
            
            //GAPP->mTestSphere->Draw();
            
            
            
            mRenderX[i][n] = aX;
            mRenderY[i][n] = aY;
            mRenderZ[i][n] = aZ;
            
            /*
            float                               **mControlY;
            float                               **mControlZ;
            
            float                               *mRenderData;
            
            float                               **mRenderX;
            float                               **mRenderY;
            float                               **mRenderZ;
            
            float                               **mRenderU;
            float                               **mRenderV;
            float                               **mRenderW;
            */
            
            Graphics::MatrixPop();
            
            
        }
    }
    
    /*
    for(int i=0;i<mRenderWidth;i++)
    {
        aSpline.Clear();
        
        float aXPercent = (float)i / (float)(mRenderWidth-1);
        
        float aSplinePos;
        float aXPercent;
        
        for(int k=0;k<mControlWidth;k++)
        {
            aSplinePos=aXPercent * (float)mSplineX[k].Max();
            
            aX = mSplineX[k].GetX(aSplinePos);
            aY = mSplineX[k].GetY(aSplinePos);
            
            mSpline.AddPoint(aX,  aY);
        }
        
        
        for(int n=0;n<mRenderHeight;n++)
        {
            
            //aSpline
            
            
            
            for(int n=0;n<RENDER_MESH_SIZE;n++)
            {
                aSplinePos = ((float)n / (float)(RENDER_MESH_SIZE-1)) * (float)mSpline.Max();
                
                aX = mSpline.GetX(aSplinePos);
                aY = mSpline.GetY(aSplinePos);
                
                mWarpX[i][n]=aX;
                mWarpY[i][n]=aY;
            }
        }
    }
    */
    
}



