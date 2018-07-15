//
//  AnimatedGamePath.hpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/12/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef AnimatedGamePath_hpp
#define AnimatedGamePath_hpp

#include "GamePath.h"
#include "FDrawQuad.hpp"
#include "FPointList.h"
#include "FVertexBuffer.h"

struct AnimatedGamePathNode {
public:
    float                               mCenterX;
    float                               mCenterY;
    float                               mDirX;
    float                               mDirY;
    float                               mNormX;
    float                               mNormY;

    float                               mX1;
    float                               mY1;
    float                               mX2;
    float                               mY2;


    float                               mDistanceFromPrevious;
};

struct AnimatedGamePathChunk {
public:
    FList                               mPathNodeList;
    FVertexBuffer                       mBuffer;

    int                                 mDepth;

    //Length of all nodes
    float                               mLength;

    //Distance along total path...
    float                               mDistance;


};

class AnimatedGamePath : public GamePath {
public:
    AnimatedGamePath();
    virtual ~AnimatedGamePath();

    void                                Update();
    void                                Draw();
    
    void                                Reset();
    void                                Generate();

    float                               mPathWidth;
    float                               mPathWidth2;
    

    void                                AddBend(int pDepth, float pStartX, float pStartY, float pCenterX, float pCenterY, float pEndX, float pEndY);

    void                                AppendPointListToPath(int pDepth, float pUVWSpreadFactor=1.0f);


    void                                GenerateTextureQuads();

    FPointList                          mPointList;


    FList                               mPathChunkList;
    FList                               mPathChunkQueue;

    FList                               mPathNodeQueue;

    bool                                mSelected;
    bool                                mEditorMode;

    float                               mTextureAnimationOffset;

    FSprite                             *mSprite;


};

#endif /* AnimatedGamePath_hpp */
