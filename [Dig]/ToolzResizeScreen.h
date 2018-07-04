//
//  ToolzResizeScreen.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__ToolzResizeScreen__
#define __DigMMMac__ToolzResizeScreen__

#include "FView.h"

class ToolzResizeScreen : public FView
{
public:
    ToolzResizeScreen();
    virtual ~ToolzResizeScreen();
    
    virtual void                            PositionContent();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    void                                    ComputeResizeRect();
    
    float                                   mScreenResizeCornerX[4];
    float                                   mScreenResizeCornerY[4];
    float                                   mScreenResizeCornerDragStartX[4];
    float                                   mScreenResizeCornerDragStartY[4];
    
    
    float                                   mResizeLeft;
    float                                   mResizeTop;
    float                                   mResizeRight;
    float                                   mResizeBottom;
    float                                   mResizeWidth;
    float                                   mResizeHeight;
    
    
    float									mResizeDragCornerX;
    float									mResizeDragCornerY;
    int                                     mResizeCornerIndex;
    
    
    void									PanStart();
    void									PanEnd();
    
    float                                   mPanWindowStartX;
    float                                   mPanWindowStartY;
    float                                   mPanTouchStartX;
    float                                   mPanTouchStartY;
    void                                    *mPanDragData;
    
    
};

#endif /* defined(__DigMMMac__ToolzResizeScreen__) */
