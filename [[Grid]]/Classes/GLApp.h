//
//  GLApp.h
//  OptimizeRX
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#ifndef GLApp_hpp
#define GLApp_hpp

#include "FApp.h"
#include "FSprite.h"
#include "FFont.h"
#include "FModelData.h"
#include "FCanvas.hpp"

class CNVWorldContainerContainer;
class TestWorldContainerContainer;
class TestWorldContainer;
class TempView;
class GLApp : public FApp
{
public:
    
    GLApp();
    virtual ~GLApp();
    
    virtual void                                Update();
    virtual void                                Draw();
    virtual void                                Load();
    virtual void                                LoadComplete();
    
    void                                        UpdateRot(float pX);
    
    virtual void                                SetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetDeviceSize(float pWidth, float pHeight);

    bool                                        SegmentSegmentIntersection(FVec2 l1p1, FVec2 l1p2, FVec2 l2p1, FVec2 l2p2, FVec2 *intersection);
    
    virtual void                                MouseWheel(int pDirection);
    virtual void                                KeyDown(int pKey);
    virtual void                                KeyUp(int pKey);
    
    
    virtual void                                TouchDown(float pX, float pY, void *pData);
    virtual void                                TouchMove(float pX, float pY, void *pData);
    virtual void                                TouchUp(float pX, float pY, void *pData);
    virtual void                                TouchFlush();
    
    TestWorldContainerContainer                 *mContainer;

    CNVWorldContainerContainer                  *mCanvasContainer;
    
    //TestWorldContainer                          *mWorldContainer;
    
    FSound                                      mSound;
    
    FVec2                                       mLine1Point1;
    FVec2                                       mLine1Point2;
    
    FVec2                                       mLine2Point1;
    FVec2                                       mLine2Point2;
    
    FVec2                                       *mSelectedPoint;
    FVec2                                       mSelectedPointStart;
    FVec2                                       mSelectedTouchStart;
    
    FModelDataIndexed                           mSphere;
    
    FSprite                                     mTestSprite;
    FSprite                                     mBackground;
    FSprite                                     mBackgroundLarge;
    
    FSprite                                     mTessPattern;
    
    FSprite                                     mDarkTile;
    
    FSprite                                     mWallLeft;
    FSprite                                     mWallRight;
    
    FSprite                                     mSillyMeme;


    FSprite                                     mTest_800x600_1;
    FSprite                                     mTest_800x600_2;
    FSprite                                     mTest_Small_1;


    FSprite                                     mInterfaceBottom;
    FSprite                                     mInterfaceBottomGray;


    FSpriteSequence                             mSequenceSquare;

    FSpriteSequence                             mParticleStream;
    
    FSprite                                     mTile1;
    FSprite                                     mTile2;
    FSprite                                     mTile3;
    FSprite                                     mTile4;

    FCanvas                                     mCanvas1;
    FCanvas                                     mCanvas2;
    FCanvas                                     *mCanvas3;

    FSprite                                     mJiggleMascot;
    
    int                                         mSpawnNewWorldTimer;
    
    
    
};

extern GLApp *gApp;

#endif /* GLApp_hpp */
