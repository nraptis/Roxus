//
//  ToolMenuContent.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuContent_hpp
#define ToolMenuContent_hpp

#include "FCanvas.hpp"
#include "UIButton.hpp"

class ToolMenuContent : public FCanvas {
public:
    ToolMenuContent();
    virtual ~ToolMenuContent();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    virtual void                            MouseDown(float pX, float pY, int pButton);
    virtual void                            MouseMove(float pX, float pY);
    virtual void                            MouseUp(float pX, float pY, int pButton);
    virtual void                            MouseWheel(int pDirection);

    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);

    UIButton                                mB1;
    UIButton                                mB2;
    UIButton                                mB3;
    UIButton                                mB4;

};

#endif /* ToolMenuContent_hpp */

