//
//  UIButton.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIButton_hpp
#define UIButton_hpp

#include "FButton.h"
#include "UIRoundedRect.hpp"

class UIButton : public FButton {
public:
    UIButton();
    virtual ~UIButton();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    UIRoundedRect                           mButtonBackground;
    UIRoundedRect                           mButtonOutline;

    UIRoundedRect                           mButtonBackgroundDown;
    UIRoundedRect                           mButtonOutlineDown;

    bool                                    mDrawCloseX;
    bool                                    mDrawMinimize;

    FString                                 mText;


};

#endif /* UIButton_hpp */
