//
//  UImagePicker.h
//  2015 Fleet XP
//
//  Created by Nick Raptis on 12/13/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UImagePicker__
#define ___015_Fleet_XP__UImagePicker__

#include "FView.h"
#include "FScrollView.h"
#include "UMenuStyle.h"
#include "UImageCell.h"
#include "UMenu.h"
#include "FDrawQuad.h"

#define IMG_PICK_RESPONSE_CANCEL 39
#define IMG_PICK_RESPONSE_SPRITE 34
#define IMG_PICK_RESPONSE_SEQUENCE 35

class UImagePicker;
class UImagePickerScrollContent : public FGestureView
{
public:
    
    UImagePickerScrollContent(float pX, float pY, float pWidth, float pHeight);
    virtual ~UImagePickerScrollContent();
    
    virtual void                                Update();
    virtual void                                Draw();
    
    void                                        AddCell(UImageCell *pCell);
    
    virtual void                                TouchDown(float pX, float pY, void *pData);
    
    virtual void                                PanBegin(float pX, float pY);
    virtual void                                Pan(float pX, float pY);
    virtual void                                PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);
    
    virtual void                                LayoutSubviews();
    
    FList                                       mCellList;
    
    UImageCell                                  ***mCellGrid;
    
    int                                         mScreenGridWidth;
    int                                         mMaxRows;
    
    int                                         mColCount;
    int                                         mRowCount;
    
    float                                       mScrollSpeedX;
    float                                       mScrollSpeedY;
    float                                       mScrollFlingSpeed;
    
    float                                       mScrollOffsetX;
    float                                       mScrollOffsetY;
    
    int                                         mGridOffsetX;
    int                                         mGridOffsetY;
    
    float                                       mCellSpacingH;
    float                                       mCellSpacingV;
    
    float                                       mCellWidth;
    float                                       mCellHeight;
    
};

class UImagePicker : public UMenu
{
public:
    
    
    UImagePicker(FView *pListener);
    //UImagePicker(float pX, float pY, float pWidth, float pHeight);
    
    virtual ~UImagePicker();
    
    virtual void                                Update();
    virtual void                                Draw();
    
    virtual void                                TouchDown(float pX, float pY, void *pData);
    
    virtual void                                Notify(void *pSender, int pID, void *pObject);
    
    void                                        FillWithAny();
    void                                        FillWithImages();
    void                                        FillWithImageSequences();
    
    FView                                       *mListener;
    
    UImagePickerScrollContent                   *mScrollContent;
    
    void                                        AddSprite(const char *pSpritePath);
    void                                        AddSprite(FSprite *pSprite);
    
    void                                        AddSpriteSequence(FSpriteSequence *pSpriteSequence);
    
    void                                        LayoutSubviews();
    bool                                        mDidLayoutSubviews;
};

#endif /* defined(___015_Fleet_XP__UImagePicker__) */
