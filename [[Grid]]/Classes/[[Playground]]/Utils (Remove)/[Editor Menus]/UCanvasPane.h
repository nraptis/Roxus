//
//  UCanvasPane.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef UTIL_CANVAS_MENU_H
#define UTIL_CANVAS_MENU_H

#include "UMenuStyleExtended.h"


class UCanvasPaneBackground : public UMenuPane
{
public:
    UCanvasPaneBackground();
    virtual ~UCanvasPaneBackground();
    
    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);
    
    UColorPicker                                *mColorPickerBackground;
    
    UExtendedSlider                             *mSliderGlobalOpacity;
    UExtendedSlider                             *mSliderBackOpacity;
    
    UButton                                     *mButtonEnableColor;
    UButton                                     *mButtonEnableImage;
    
    UButton                                     *mButtonPickImage;

    UButton                                     *mButtonLetterBoxEnable;
    UButton                                     *mButtonLetterBoxFront;
};

class UCanvasPane : public UMenu
{
public:
    
    UCanvasPane();
    virtual ~UCanvasPane();
    
    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);
    
	UMenuPane                                   *mControlPane;
	UButton										*mControlButtonClear;
	UButton										*mControlButtonSave;
	UButton										*mControlButtonLoad;
    UButton										*mControlButtonExport;
    
    UButton										*mControlButtonDeleteSaved;
    UButton										*mControlButtonExportOffsets;
    UButton										*mControlButtonExportParticle;
    UButton										*mControlButtonExportPaths;
    
	UMenuPane                                   *mCreatePane;
	UButton										*mCreateButtonSprite;
	UButton										*mCreateButtonSpriteSequence;
	UButton										*mCreateButtonParticle;
	UButton										*mCreateButtonRect;
    
    
    UMenuPane                                   *mPathPane;
    UExtendedSlider                             *mPathSliderStartScale;
    UButton                                     *mPathButtonTransform;
    
    
    UCanvasPaneBackground                       *mBackgroundPane;
    
};

#endif /* defined(___015_Fleet_XP__UCanvasPane__) */
