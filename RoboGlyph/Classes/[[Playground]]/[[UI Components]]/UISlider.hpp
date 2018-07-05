//
//  UISlider.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UI_SLIDER_HPP
#define UI_SLIDER_HPP

#include "ToolMenuSectionRow.hpp"
#include "FSlider.hpp"
#include "UIRoundedRect.hpp"
#include "UILabel.hpp"


class UISlider : public ToolMenuSectionRow {
public:
    UISlider();
    virtual ~UISlider();


    virtual void                                Layout();

    virtual void                                Draw();

    virtual void                                Notify(void *pSender, const char *pNotification);

    float                                       GetValue();
    void                                        SetValue(float *pTargetValue);
    float                                       *mTargetValue;
    float                                       mValue;


    UILabel                                     mLabelTitle;
    UILabel                                     mLabelValue;

    float                                       mLabelTitleWidth;
    float                                       mLabelValueWidth;

    FSlider                                     mBaseSlider;
    float                                       mBarHeight;
    float                                       mBarHeightInner;

    UIRoundedRect                               mRectBar;
    UIRoundedRect                               mRectBarShine;

    UIRoundedRect                               mRectThumb;
    UIRoundedRect                               mRectThumbShine;



    float                                       mPreviousDrawMin;
    float                                       mPreviousDrawMax;

};

#endif /* UISlider_hpp */
