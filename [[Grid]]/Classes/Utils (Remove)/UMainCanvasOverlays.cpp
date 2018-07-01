//
//  UMainCanvasOverlays.cpp
//  Digplex
//
//  Created by Nicholas Raptis on 12/25/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "UMainCanvasOverlays.h"
#include "UMainCanvas.h"
#include "core_includes.h"
#include "core_app_shell.h"
#include "FApp.h"

UMainCanvasPanOverlay::UMainCanvasPanOverlay()
{
    SetStaticTransform(true);
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);

    mTouchDragStartX = 0.0f;
    mTouchDragStartY = 0.0f;
    
    mTouchDragTouchStartX = 0.0f;
    mTouchDragTouchStartY = 0.0f;
    
    mDrawTouchX = 10.0f;
    mDrawTouchY = 10.0f;
    
    mTouchDragData = 0;
    
	float aX = gVirtualDevX;// + gAppOffsetX;
	float aY = gVirtualDevY;// + gAppOffsetY;
    
    aX = aX;
    aY = aY;
    
    gUtils->mScreenResizeCornerX[0] = aX;
    gUtils->mScreenResizeCornerY[0] = aY;
    
    gUtils->mScreenResizeCornerX[1] = aX;
	gUtils->mScreenResizeCornerY[1] = aY + gVirtualDevHeight;
    
	gUtils->mScreenResizeCornerX[2] = aX + gVirtualDevWidth;
    gUtils->mScreenResizeCornerY[2] = aY;
    
	gUtils->mScreenResizeCornerX[3] = aX + gVirtualDevWidth;
	gUtils->mScreenResizeCornerY[3] = aY + gVirtualDevHeight;
    
    //ComputeResizeRect();
    
    mButtonClose = new UButton("X");
    mButtonClose->SetMenuItemFrame(gDeviceWidth2 - 40.0f, gDeviceHeight2 - 20.0f, 80.0f, mButtonClose->mHeight);
    AddSubview(mButtonClose);
    
}

UMainCanvasPanOverlay::~UMainCanvasPanOverlay()
{
    
}



void UMainCanvasPanOverlay::Update()
{
    
}

void UMainCanvasPanOverlay::Draw()
{
	Graphics::SetColor(0.75f, 0.9f, 0.25f, 0.5f);

	Graphics::DrawRect(5.0f, 5.0f, mWidth - 10.0f, mHeight - 10.0f);

	Graphics::SetColor();

	for(int i = 0; i<4; i++)
	{
		float aX = gUtils->mScreenResizeCornerX[i];
		float aY = gUtils->mScreenResizeCornerY[i];

		Graphics::DrawRect(aX - 4, aY - 4, 8, 8);
	}

	Graphics::SetColor(1.0f, 0.0f, 0.0f);
	Graphics::DrawRect(mDrawTouchX, mDrawTouchY, 4, 4);
	Graphics::SetColor();
    
}

void UMainCanvasPanOverlay::TouchDown(float pX, float pY, void *pData)
{
    mDrawTouchX = pX;
    mDrawTouchY = pY;

    mTouchDragData = pData;
    
    //mTouchDragData = 0;
    
    float aMinDist = 45.0f;
    
    if(gDeviceWidth < 600.0f)aMinDist = 24.0f;
    
    mResizeDragIndex = -1;
    
    mResizeDragStartTouchX = pX;
    mResizeDragStartTouchY = pY;
    
    for(int i=0;i<4;i++)
    {
        float aX = gUtils->mScreenResizeCornerX[i];
        float aY = gUtils->mScreenResizeCornerY[i];
        
        float aDist = Distance(pX, pY, aX, aY);
        
        if(aDist < aMinDist)
        {
            mResizeDragIndex = i;
            
            mResizeDragStartX = aX;
            mResizeDragStartY = aY;
            
            
        }
    }
    
    if(mResizeDragIndex == -1)
    {
        //mResizeDragStartX = gAppOffsetX;
        //mResizeDragStartY = gAppOffsetY;
    }
}

void UMainCanvasPanOverlay::TouchMove(float pX, float pY, void *pData)
{
    if(pData == mTouchDragData)
    {
        mDrawTouchX = pX;
        mDrawTouchY = pY;
        
        int aDiffX = pX - mResizeDragStartTouchX;
        int aDiffY = pY - mResizeDragStartTouchY;
        
        if((mResizeDragIndex >= 0) && (mResizeDragIndex < 4))
        {
            int aX = mResizeDragStartX + aDiffX;
            int aY = mResizeDragStartY + aDiffY;
            
            gUtils->mScreenResizeCornerX[mResizeDragIndex] = aX;
            gUtils->mScreenResizeCornerY[mResizeDragIndex] = aY;
            
            if(mResizeDragIndex == 0)
            {
                gUtils->mScreenResizeCornerX[1] = aX;
                gUtils->mScreenResizeCornerY[2] = aY;
            }
            
            if(mResizeDragIndex == 1)
            {
                gUtils->mScreenResizeCornerX[0] = aX;
                gUtils->mScreenResizeCornerY[3] = aY;
            }
            
            if(mResizeDragIndex == 2)
            {
                gUtils->mScreenResizeCornerX[3] = aX;
                gUtils->mScreenResizeCornerY[0] = aY;
            }
            
            if(mResizeDragIndex == 3)
            {
                gUtils->mScreenResizeCornerX[2] = aX;
                gUtils->mScreenResizeCornerY[1] = aY;
            }
            
                    }
        
        ComputeResizeRect();
        
		float aShiftX = (gVirtualDevX);// + gAppOffsetX);
		float aShiftY = (gVirtualDevY);// + gAppOffsetY);
        
        
        if(gAppBase)
        {
			AppShellSetVirtualFrame(mResizeLeft, mResizeTop, mResizeWidth, mResizeHeight);

            //gAppBase->BaseSetVirtualFrame(mResizeLeft - aShiftX, mResizeTop - aShiftY, mResizeWidth, mResizeHeight);
        }

    }
}

void UMainCanvasPanOverlay::TouchUp(float pX, float pY, void *pData)
{
    mTouchDragData = 0;
    mResizeDragIndex = -1;
}

void UMainCanvasPanOverlay::TouchFlush()
{
    
}

void UMainCanvasPanOverlay::Notify(void *pSender)
{
    if(pSender == mButtonClose)
    {
        gUtils->KillOverlay();
        gUtilWS->SetMode(UTIL_WS_MODE_SELECT_AND_DRAG);
        gUtils->SetSelectedNode();
    }
}

void UMainCanvasPanOverlay::ComputeResizeRect()
{
    
    for(int i=0;i<4;i++)
    {
        if(gUtils->mScreenResizeCornerX[i] < 0.0f)gUtils->mScreenResizeCornerX[i] = 0.0f;
        if(gUtils->mScreenResizeCornerX[i] > gDeviceWidth)gUtils->mScreenResizeCornerX[i] = gDeviceWidth;
        
        if(gUtils->mScreenResizeCornerY[i] < 0.0f)gUtils->mScreenResizeCornerY[i] = 0.0f;
        if(gUtils->mScreenResizeCornerY[i] > gDeviceHeight)gUtils->mScreenResizeCornerY[i] = gDeviceHeight;
    }
    
    mResizeLeft = gUtils->mScreenResizeCornerX[0];
    mResizeTop = gUtils->mScreenResizeCornerY[0];
    
    mResizeRight = gUtils->mScreenResizeCornerX[3];
    mResizeBottom = gUtils->mScreenResizeCornerY[3];
    
    for(int i=0;i<4;i++)
    {
        int aX = gUtils->mScreenResizeCornerX[i];
        int aY = gUtils->mScreenResizeCornerY[i];
        
        if(aX < mResizeLeft)mResizeLeft = aX;
        if(aX > mResizeRight)mResizeRight = aX;
        
        if(aY < mResizeTop)mResizeTop = aY;
        if(aY > mResizeBottom)mResizeBottom = aY;
    }
    
    mResizeWidth = mResizeRight - mResizeLeft;
    mResizeHeight = mResizeBottom - mResizeTop;
    
    //BaseDeviceSizeChanged(mResizeLeft, mResizeTop, mResizeWidth, mResizeHeight);
	
    
}



