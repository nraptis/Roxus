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

    float                               mTrack1X1;
    float                               mTrack1Y1;
    float                               mTrack1X2;
    float                               mTrack1Y2;

    float                               mTrack2X1;
    float                               mTrack2Y1;
    float                               mTrack2X2;
    float                               mTrack2Y2;


    float                               mDistanceFromPrevious;
};

struct AnimatedGamePathChunk {
public:
    FList                               mPathNodeList;
    FVertexBuffer                       mBufferMainPath;

    FDrawNodeList                       mBufferTrack1;
    FDrawNodeList                       mBufferTrack2;

    int                                 mDepth;

    //Length of all nodes
    float                               mLength;

    //Distance along total path...
    float                               mDistance;

    int                                 mDemoIndex;
    int                                 mDemoIndexTimer;


};

class AnimatedGamePath : public GamePath {
public:
    AnimatedGamePath();
    virtual ~AnimatedGamePath();
    

    void                                Update();


    void                                DrawEditorMarkers();
    

    void                                DrawPrepare();
    void                                Draw(int pDepth);


    virtual void                        ComputePath(GameArena *pArena);

    void                                Reset();
    void                                Generate();

    float                               mPathWidth;
    float                               mPathWidth2;

    
    float                               mTrackWidth;
    float                               mTrackOffset;


    float                               mUpRampScaleFactor;
    float                               mDownRampScaleFactor;


    void                                AddBend(int pDepth, float pStartX, float pStartY, float pCenterX, float pCenterY, float pEndX, float pEndY);
    
    void                                AddStraight(int pDepth, float pStartX, float pStartY, float pEndX, float pEndY);

    void                                AddHorizontalRamp(int pDepth, float pStartX, float pStartY, float pEndX, float pEndY);
    void                                AddVerticalRamp(int pDepth, float pUVWSpreadFactor, float pStartX, float pStartY, float pEndX, float pEndY);




    //void                                AddVerticalLine(int pDepth, float pStartX, float pStartY, float pCenterX, float pCenterY, float pEndX, float pEndY);



    void                                AppendPointListToPath(int pDepth, float pUVWSpreadFactor);

    void                                AppendPointListToPath(int pDepth, float pUVWSpreadFactor, float pDirX, float pDirY);


    //Happens when path changes...
    void                                GenerateTracks();

    //Happens on every draw...
    void                                GenerateTextureQuads();

    FPointList                          mPointList;

    FList                               mPathChunkList;
    FList                               mPathChunkQueue;

    FColor                              mTrackColorInner;
    FColor                              mTrackColorOuter;

    FList                               mPathNodeQueue;

    bool                                mSelected;
    bool                                mEditorMode;

    float                               mTextureAnimationOffset;

    FSprite                             *mSprite;

};

#endif /* AnimatedGamePath_hpp */
