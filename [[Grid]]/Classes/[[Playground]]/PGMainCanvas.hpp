//
//  PGMainCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGMainCanvas_hpp
#define PGMainCanvas_hpp

#include "FCanvas.hpp"
#include "DragableCanvas.hpp"
#include "FDrawQuad.h"
#include "ToolMenu.hpp"
#include "PolygonMenu.hpp"
#include "PGMainToolbar.hpp"

class PGMainCanvas : public FCanvas {
public:
    PGMainCanvas();
    virtual ~PGMainCanvas();

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

    DragableCanvas                          *mDragCanvas1;
    DragableCanvas                          *mDragCanvas2;
    DragableCanvas                          *mDragCanvas3;

    FDrawQuad                               mBackQuad;

    ToolMenu                                *mToolMenu1;
    ToolMenu                                *mToolMenu2;
    ToolMenu                                *mToolMenu3;

    PolygonMenu                             *mPolyMenu;

    PGMainToolbar                           *mMainToolbar;

    int                                     mMenuIndex;
};

extern PGMainCanvas *gTool;


#endif /* PGMainCanvas_hpp */
