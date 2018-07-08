//
//  TextureMesh.cpp
//  RamPreview
//
//  Created by Nick Raptis on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TextureMesh.h"
#include "stdafx.h"

TextureMesh::TextureMesh()
{
    mMeshGranularity=0;
    
    mControlMeshWidth=0;
    mControlMeshHeight=0;
    
    mRenderMeshWidth=0;
    mRenderMeshHeight=0;
    
    mControlMeshX=0;
    mControlMeshY=0;
    mControlMeshZ=0;
    
    mRenderMeshX=0;
    mRenderMeshY=0;
    mRenderMeshZ=0;
    
    mRenderMeshU=0;
    mRenderMeshV=0;
    mRenderMeshW=0;
    
    mRenderMeshNormalX=0;
    mRenderMeshNormalY=0;
    mRenderMeshNormalZ=0;
    
    mControlMeshData=0;
    
    mRenderMeshData=0;
}

TextureMesh::~TextureMesh()
{
    
//      delete[]mControlMeshX;
//      mControlMeshY=0;
//      mControlMeshZ=0;
//    
//      mRenderMeshX=0;
//      mRenderMeshY=0;
//      mRenderMeshZ=0;
//    
//      mRenderMeshU=0;
//      mRenderMeshV=0;
//      mRenderMeshW=0;
//    
//      mRenderMeshNormalX=0;
//      mRenderMeshNormalY=0;
//      mRenderMeshNormalZ=0;
    
}

void TextureMesh::Free()
{
    delete [] mRenderMeshData;
    delete [] mControlMeshData;
    
    delete [] mRenderMeshX;
    delete [] mRenderMeshY;
    delete [] mRenderMeshZ;
    
    delete [] mRenderMeshU;
    delete [] mRenderMeshV;
    delete [] mRenderMeshW;
    
    delete [] mRenderMeshNormalX;
    delete [] mRenderMeshNormalY;
    delete [] mRenderMeshNormalZ;
    
    mMeshGranularity=0;
    
    mControlMeshWidth=0;
    mControlMeshHeight=0;
    
    mRenderMeshWidth=0;
    mRenderMeshHeight=0;
    
    mControlMeshX=0;
    mControlMeshY=0;
    mControlMeshZ=0;
    
    mRenderMeshX=0;
    mRenderMeshY=0;
    mRenderMeshZ=0;
    
    mRenderMeshU=0;
    mRenderMeshV=0;
    mRenderMeshW=0;
    
    mRenderMeshNormalX=0;
    mRenderMeshNormalY=0;
    mRenderMeshNormalZ=0;
    
    mControlMeshData=0;
    mRenderMeshData=0;
}

void TextureMesh::Generate(int pControlGridWidth, int pControlGridHeight, int pMeshGranularity)
{
    mMeshGranularity = pMeshGranularity;
    
    mControlMeshWidth = pControlGridWidth;
    mControlMeshHeight = pControlGridHeight;
    
    mRenderMeshWidth = mControlMeshWidth * pMeshGranularity;
    mRenderMeshHeight = mControlMeshHeight * pMeshGranularity;
    
    int aControlMeshArea = mControlMeshWidth * mControlMeshHeight;
    int aRenderMeshArea = (aControlMeshArea * mMeshGranularity);
    
    mControlMeshData = new float[(aControlMeshArea) * 3];
    mRenderMeshData = new float[aRenderMeshArea * 9];
    
    mControlMeshX = new float*[mControlMeshWidth];
    mControlMeshY = new float*[mControlMeshWidth];
    mControlMeshZ = new float*[mControlMeshWidth];
    
    mRenderMeshX = new float*[mRenderMeshWidth];
    mRenderMeshY = new float*[mRenderMeshWidth];
    mRenderMeshZ = new float*[mRenderMeshWidth];
    
    mRenderMeshU = new float*[mRenderMeshWidth];
    mRenderMeshV = new float*[mRenderMeshWidth];
    mRenderMeshW = new float*[mRenderMeshWidth];
    
    mRenderMeshNormalX = new float*[mRenderMeshWidth];
    mRenderMeshNormalY = new float*[mRenderMeshWidth];
    mRenderMeshNormalZ = new float*[mRenderMeshWidth];
    
    float *aPtr;
    
    aPtr = mControlMeshData;
    for(int i=0;i<mControlMeshWidth;i++)
    {
        mControlMeshX[i]=aPtr;
        aPtr += mControlMeshHeight;
    }
    for(int i=0;i<mControlMeshWidth;i++)
    {
        mControlMeshY[i]=aPtr;
        aPtr += mControlMeshHeight;
    }
    for(int i=0;i<mControlMeshWidth;i++)
    {
        mControlMeshZ[i]=aPtr;
        aPtr += mControlMeshHeight;
    }
    
    for(int i=0;i<mControlMeshWidth;i++)
    {
        for(int n=0;n<mControlMeshHeight;n++)
        {
            mControlMeshX[i][n]=i;
            mControlMeshY[i][n]=n;
            
            mControlMeshZ[i][n]=gRand.GetFloat();
        }
    }
}

void TextureMesh::MakeFloor(float pLeft, float pTop, float pWidth, float pHeight, bool pXZAxis)
{
    
}

void TextureMesh::PrintMesh()
{
    printf("Texture Mesh: [%d x %d]\n Render Mesh: [%d x %d]\n", mControlMeshWidth, mControlMeshHeight, mRenderMeshWidth, mRenderMeshHeight);
    
    for(int i=0;i<mControlMeshWidth;i++)
    {
        for(int n=0;n<mControlMeshHeight;n++)
        {
            printf("ControlMesh[%d %d] = (%f, %f, %f)\n", i, n, 
                   mControlMeshX[i][n], mControlMeshY[i][n], mControlMeshZ[i][n]);
        }
    }
    
}


void TextureMesh::SetX(int pControlX, int pControlY, float pX)
{
    if(pControlX >= 0 && pControlX < mControlMeshWidth)
    {
        mControlMeshX[pControlX][pControlY]=pX;
    }
}

void TextureMesh::SetY(int pControlX, int pControlY, float pY)
{
    if(pControlX >= 0 && pControlX < mControlMeshWidth)
    {
        mControlMeshY[pControlX][pControlY]=pY;
    }
}

void TextureMesh::SetZ(int pControlX, int pControlY, float pZ)
{
    if(pControlX >= 0 && pControlX < mControlMeshWidth)
    {
        mControlMeshZ[pControlX][pControlY]=pZ;
    }
}

void TextureMesh::SetXYZ(int pControlX, int pControlY, float pX, float pY, float pZ)
{
    SetX(pControlX, pControlY, pX);
    SetX(pControlX, pControlY, pY);
    SetX(pControlX, pControlY, pZ);
}