//
//  UMainCanvasOverlays.h
//  Digplex
//
//  Created by Nicholas Raptis on 12/25/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef __Digplex__UMainCanvasOverlays__
#define __Digplex__UMainCanvasOverlays__

#include "FView.h"
#include "UMenuStyle.h"

class UMainCanvasPanOverlay : public FView
{
public:
    UMainCanvasPanOverlay();
    virtual ~UMainCanvasPanOverlay();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    
    float                                   mTouchDragStartX;
    float                                   mTouchDragStartY;
    
    float                                   mTouchDragTouchStartX;
    float                                   mTouchDragTouchStartY;
    
    UButton                                 *mButtonClose;
    
    void                                    *mTouchDragData;
    
    float                                   mDrawTouchX;
    float                                   mDrawTouchY;
    
    void                                    ComputeResizeRect();
    float                                   mResizeLeft;
    float                                   mResizeTop;
    float                                   mResizeRight;
    float                                   mResizeBottom;
    float                                   mResizeWidth;
    float                                   mResizeHeight;
    
    int                                     mResizeDragIndex;
    
    float                                   mResizeDragStartX;
    float                                   mResizeDragStartY;
    float                                   mResizeDragStartTouchX;
    float                                   mResizeDragStartTouchY;
};


#endif


