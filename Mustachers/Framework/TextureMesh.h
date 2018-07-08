//
//  TextureMesh.h
//  RamPreview
//
//  Created by Nick Raptis on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TEXTURE_MESH_H
#define TEXTURE_MESH_H

class TextureMesh
{
public:
    
    TextureMesh();
    ~TextureMesh();
    
    void                Free();
    
    void                SetX(int pControlX, int pControlY, float pX);
    void                SetY(int pControlX, int pControlY, float pY);
    void                SetZ(int pControlX, int pControlY, float pZ);
    void                SetXYZ(int pControlX, int pControlY, float pX, float pY, float pZ);
    
    
    int                 mControlMeshWidth;
    int                 mControlMeshHeight;
    
    int                 mRenderMeshWidth;
    int                 mRenderMeshHeight;
    
    int                 mMeshGranularity;
    
    float               *mControlMeshData;
    
    float               **mControlMeshX;
    float               **mControlMeshY;
    float               **mControlMeshZ;
    
    float               *mRenderMeshData;
    
    float               **mRenderMeshX;
    float               **mRenderMeshY;
    float               **mRenderMeshZ;
    
    float               **mRenderMeshU;
    float               **mRenderMeshV;
    float               **mRenderMeshW;
    
    float               **mRenderMeshNormalX;
    float               **mRenderMeshNormalY;
    float               **mRenderMeshNormalZ;
    
    void                Generate(int pControlGridWidth, int pControlGridHeight, int pMeshGranularity);
    
    void                MakeFloor(float pLeft, float pTop, float pWidth, float pHeight, bool pXZAxis);
    
    void                PrintMesh();
    
    
};

#endif
