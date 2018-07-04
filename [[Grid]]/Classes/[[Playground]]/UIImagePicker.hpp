//
//  UIImagePicker.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UTIL_IMAGE_PICKER_HPP
#define UTIL_IMAGE_PICKER_HPP

#include "FGestureCanvas.hpp"
#include "ToolMenu.hpp"
#include "FDrawQuad.h"

class UIImagePickerCell;
class UIImagePickerScrollContent : public FGestureCanvas {
public:
    
    UIImagePickerScrollContent();
    virtual ~UIImagePickerScrollContent();

    virtual void                                Layout();
    
    virtual void                                Update();
    virtual void                                Draw();

    virtual void                                TouchDown(float pX, float pY, void *pData);

    void                                        AddCell(UIImagePickerCell *pCell);
    
    virtual void                                PanBegin(float pX, float pY);
    virtual void                                Pan(float pX, float pY);
    virtual void                                PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);

    void                                        SetUp();

    FList                                       mCellList;
    UIImagePickerCell                           ***mCellGrid;

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

    float                                       mStartOffsetX;
    float                                       mStartOffsetY;
};

class UIImagePicker : public ToolMenu {
public:
    UIImagePicker();
    virtual ~UIImagePicker();

    virtual void                                Layout();
    virtual void                                Update();
    virtual void                                Draw();
    
    void                                        FillWithAny();
    void                                        FillWithImages();
    void                                        FillWithImageSequences();
    
    UIImagePickerScrollContent                  *mScrollContent;

    void                                        AddSprite(const char *pSpritePath);
    void                                        AddSprite(FSprite *pSprite);
    void                                        AddSpriteSequence(FSpriteSequence *pSpriteSequence);

    FList                                       mBlockedSprites;

    bool                                        mDidSetUp;


};

#endif

