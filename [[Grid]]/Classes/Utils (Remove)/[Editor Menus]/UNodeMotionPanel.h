//
//  UNodeMotionPanel.h
//  2015 Fleet XP
//
//  Created by Nicholas Raptis on 12/26/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#ifndef ___015_Fleet_XP__UNodeMotionPanel__
#define ___015_Fleet_XP__UNodeMotionPanel__

//#include "UMenu.h"

#include "UMenuStyleExtended.h"




class UNodeMotionPanel : public UMenu
{
public:
    UNodeMotionPanel();
    virtual ~UNodeMotionPanel();
    
    
    virtual void                                Notify(void *pSender);
    virtual void                                SetSelectedNode(UNode *pNode);
    
    
    
    UMenuPane                                   *mQuadPane;
    
    //UMenuPane                                   *mQuadPaneStart;
    UExtendedSlider                             *mQuadSliderShiftLeftX;
    UExtendedSlider                             *mQuadSliderShiftLeftY;
    
    UExtendedSlider                             *mQuadSliderShiftRightX;
    UExtendedSlider                             *mQuadSliderShiftRightY;
    
    
    
    
    UExtendedSlider                             *mQuadSliderRotation1;
    UExtendedSlider                             *mQuadSliderRotation2;
    
    UButton                                     *mQuadButtonPrint;
    
    //UExtendedSlider                             *mLookTransformSliderRotation;
    

    
};

#endif /* defined(___015_Fleet_XP__UNodeMotionPanel__) */
