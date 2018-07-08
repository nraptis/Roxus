//
//  ModelAnimation.h
//  BerryChopper
//
//  Created by Nick Raptis on 1/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MODEL_ANIMATION_H
#define MODEL_ANIMATION_H

#define MODEL_ANIMATION_MODE_STOP 0
#define MODEL_ANIMATION_MODE_REPEAT 1
#define MODEL_ANIMATION_MODE_PLAY_ONCE 2

#include "Model.h"
#include "List.h"
#include "ModelAnimationLayer.h"
#include "ModelDataOptimizer.h"

class ModelAnimationSegment
{
public:
    
    int                 mID;
    
    int                 mStartFrame;
    int                 mEndFrame;
};

class ModelAnimation
{
public:
    
    ModelAnimation(const char *pFile);
    ModelAnimation(FString pFile);
    ModelAnimation();
    ~ModelAnimation();
    
    //ModelDataIndexed            *mData;
    
    virtual void                Free();
    
    virtual void                Draw();
    virtual void                Draw(float pFrame);
    
    virtual void                Update();
    
    void                        SetTexture(Sprite *pSprite, int pIndex=-1);
    
    void                        Generate();
    
    void                        Optimize();
    
    bool                        *mIsKey;
    
    int                         *mKeyMix1;
    int                         *mKeyMix2;
    
    int                         mFrameCount;
    int                         mFrameSize;
    
    void                        SizeKeys(int pSize);
    void                        MakeKey(int pFrame);
    void                        MakeKey(const char *pCommaSeparatedFrames);
    void                        ComputeKeyIndeces(int pStartFrame, int pEndFrame);
    
    
    void                        MakeSegment(int pStartFrame, int pEndFrame, int pIdentifier);
    
    
    
    ////////////////////////////////////////////////////
    //////
    //////
    //////       Layer Stuff
    //////
    //////
    
    virtual void                Add(ModelAnimationLayer *pLayer);
    
    /*
    virtual void                Remove(ModelAnimationLayer *pLayer);
    
    ModelAnimationLayer         *Find(const char *pName);
    inline ModelAnimationLayer  *Find(char *pName){return Find((const char*)pName);}
    inline ModelAnimationLayer  *Find(FString pName){return Find((const char*)(pName.c()));}                
    
    bool                        Remove(const char *pName);
    inline bool                 Remove(char *pName){return Remove((const char*)pName);}
    inline bool                 Remove(FString pName){return Remove((const char*)(pName.c()));}
    */
    
    List                        mSegmentList;
    List                        mLayerList;
    List                        mParentList;
    
    
    //////
    //////       End Layer Stuff
    //////
    ////////////////////////////////////////////////////
    
    void                        Save(const char *pFile);
    inline void                 Save(char *pFile){Save((const char*)(pFile));}
    inline void                 Save(FString pFile){Save((const char*)(pFile.c()));}
    
    void                        Load(const char *pFile);
    inline void                 Load(char *pFile){Load((const char*)(pFile));}
    inline void                 Load(FString pFile){Load((const char*)(pFile.c()));}
    
    
    
    
    
    void                        Play(int pId, bool pLoop=false);
    
    int                         mPlayID;
    
    bool                        mPlay;
    bool                        mPlayLoop;
    bool                        mPlayComplete;
    
    float                       mPlayFrame;
    float                       mPlayFrameSpeed;
    
    int                         mPlayFrameEnd;
    int                         mPlayFrameStart;
    
    bool                        mInterpolated;
    
};

#endif
