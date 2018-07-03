//
//  MouseTesterCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef MouseTesterCanvas_hpp
#define MouseTesterCanvas_hpp

#include "FCanvas.hpp"

class MouseTesterCanvas : public FCanvas {
public:
    MouseTesterCanvas();
    virtual ~MouseTesterCanvas();

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
};

#endif /* MouseTesterCanvas_hpp */
