//
//  GLApp.h
//  OptimizeRX
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#ifndef GLApp_hpp
#define GLApp_hpp

#define TOWER_FRAMES 24

#define GAPP (gApp)

#include "FApp.hpp"
#include "FSprite.h"
#include "FFont.hpp"
#include "FModelData.h"
#include "FCanvas.hpp"
#include "SpriteSequenceNested.h"

class Game;
class TilePathFinder;
class WorldContainer;

#include <unordered_map>

using namespace std;
class DepthBucket {
public:
    DepthBucket() { }
    
    unordered_map <int, bool> mMap;
    vector<int> mHeap;
    
    bool Contains(int pHeight) {
        return mMap[pHeight];
    }
    
    void Add(int pHeight) {
        
        mHeap.push_back(pHeight);
        
        int aSwapHold = 0;
        unsigned int aBubbleIndex = mHeap.size() - 1;
        unsigned int aParentIndex = (aBubbleIndex - 1) / 2;
        
        while (aBubbleIndex > 0 && mHeap[aBubbleIndex] > mHeap[aParentIndex]) {
            aSwapHold = mHeap[aBubbleIndex];
            mHeap[aBubbleIndex] = mHeap[aParentIndex];
            mHeap[aParentIndex] = aSwapHold;
            aBubbleIndex = aParentIndex;
            aParentIndex = (aBubbleIndex - 1) / 2;
        }
    }
    
    int Pop() {
        
        if (mHeap.size() <= 0) {
            return -1;
        }
        
        int aResult = mHeap[0];
        
        int aSwapHold = 0;
        
        unsigned int aBubbleIndex = 0;
        unsigned int aLeftChild = 2 * aBubbleIndex + 1;
        unsigned int aRightChild = aLeftChild + 1;
        unsigned int aMinChild = aLeftChild;
        
        while (aLeftChild < mHeap.size()) {
            if (aRightChild < (mHeap.size()) && mHeap[aRightChild] > mHeap[aLeftChild]) {
                aMinChild = aRightChild;
            }
            if (mHeap[aMinChild] > mHeap[aBubbleIndex]) {
                aSwapHold = mHeap[aMinChild];
                mHeap[aMinChild] = mHeap[aBubbleIndex];
                mHeap[aBubbleIndex] = aSwapHold;
                aBubbleIndex = aMinChild;
                aLeftChild = (aBubbleIndex * 2) + 1;
                aRightChild = aLeftChild + 1;
                aMinChild = aLeftChild;
            } else {
                aLeftChild = mHeap.size();
            }
        }
        
        mHeap.pop_back();
        
        return aResult;
    }
    
    
};


class GLApp : public FApp {
public:
    GLApp();
    virtual ~GLApp();
    
    //Game                                        *mGame;
    WorldContainer                          *mWorld;

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Load();
    virtual void                            LoadComplete();

    virtual void                            SetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                            SetDeviceSize(float pWidth, float pHeight);

    virtual void                            MouseWheel(int pDirection);
    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    bool                                    mDarkMode;

    FSprite                                 mTileTunnel;
    FSprite                                 mTileFloor;
    FSprite                                 mTileBridge;

    FSprite                                 mBridgeRampU;
    FSprite                                 mBridgeRampD;
    FSprite                                 mBridgeRampL;
    FSprite                                 mBridgeRampR;

    FSprite                                 mFloorRampU;
    FSprite                                 mFloorRampD;
    FSprite                                 mFloorRampL;
    FSprite                                 mFloorRampR;

    FSprite                                 mBlocker;

    FSprite                                 mUnitCircleSoft;
    FSprite                                 mUnitCircleHard;

    FSpriteSequence                         mTowerBasicOff;
    FSpriteSequence                         mTowerBasicOn;


    SpriteSequenceNested                    mRobot;


    SpriteSequenceNested                    mNinja;
    //ninja_rot_00_0300@1x.png
    //ninja_rot_00_0340@1x.png
    //ninja_rot_15_0300@1x.png
    //ninja_rot_15_0340@1x.png



    FSprite                                 mTowerMenuButtonBack[2];
    FSprite                                 mTowerMenuButtonPrice8;
    FSprite                                 mTowerMenuButtonPrice20;
    FSprite                                 mTowerMenuButtonPrice45;
    FSprite                                 mTowerMenuButtonPrice65;
    FSprite                                 mTowerMenuButtonPrice75;
    FSprite                                 mTowerMenuButtonPrice100;
    FSprite                                 mTowerMenuButtonPrice125;


    FSprite                                 mTowerDetailMenuButtonInfo;
    FSprite                                 mTowerDetailMenuButtonSell;
    FSprite                                 mTowerDetailMenuButtonUpgrade;

    FSprite                                 mGridOverlay[2];

    FSprite                                 mLevelBackTunnel;
    FSprite                                 mLevelBackFloor;
    FSprite                                 mLevelBackBridge;
    
    FSprite                                 mPathArrow;

    FSprite                                 mCheck;

    FSprite                                 m1024x1024;
    FSprite                                 m2048x2048;


    FSprite                                 mTile1;
    FSprite                                 mTile2;
    FSprite                                 mTile3;
    FSprite                                 mTile4;
    
};

//float CX(int pGridX);
//float CY(int pGridY);
float CX(int pGridX, int pGridZ);
float CY(int pGridY, int pGridZ);
float SZ(int pGridZ);

//extern Game *gGame;
//extern TilePathFinder *gPathFinder;

extern bool gEditorMode;


extern float gArenaWidth;
extern float gArenaWidth2;
extern float gArenaHeight;
extern float gArenaHeight2;

extern float gArenaActiveWidth;
extern float gArenaActiveWidth2;
extern float gArenaActiveHeight;
extern float gArenaActiveHeight2;
extern float gArenaActiveX;
extern float gArenaActiveY;

extern float gTileSize;
extern float gTileSize2;
extern float gPathBendInset45;
extern float gPathBendInset90;

extern GLApp *gApp;

#endif
