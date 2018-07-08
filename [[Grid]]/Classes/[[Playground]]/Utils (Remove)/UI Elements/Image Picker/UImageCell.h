//
//  UImageCell.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/13/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UImageCell__
#define ___015_Fleet_XP__UImageCell__

#include "FView.h"
#include "FSprite.h"
#include "FSpriteSequence.h"
#include "FDrawQuad.h"
#include "UMenu.h"

class UImageCell : public UMenuItem
{
public:
    
    UImageCell();
    UImageCell(FSprite *pSprite, bool pDestroy);
    UImageCell(const char *pPath);
    virtual ~UImageCell();
    
    
    virtual void                                SetUp(float pWidth, float pHeight);
    virtual void                                SetUp(float pX, float pY, float pWidth, float pHeight);
    
    virtual void                                Update();
    virtual void                                Draw();
    
    virtual void                                TouchUp(float pX, float pY, void *pData);
    
    //bool                                      mCancelTouch;
    
    FSprite                                     *mSprite;
    bool                                        mDestroySprite;
    
    FDrawQuad                                       mSpriteQuad;
};

class UImageCellSequence : public UImageCell
{
public:
    
    UImageCellSequence();
    UImageCellSequence(FSpriteSequence *pSequence, bool pDestroy);
    
    virtual ~UImageCellSequence();
    
    virtual void                                SetUp(float pWidth, float pHeight);
    virtual void                                SetUp(float pX, float pY, float pWidth, float pHeight);
    
    virtual void                                Update();
    virtual void                                Draw();
    
    virtual void                                TouchUp(float pX, float pY, void *pData);
    
    FSpriteSequence                             *mSequence;
    
    float                                       mFrame;
    float                                       mFrameMax;
    
    
};

#endif









