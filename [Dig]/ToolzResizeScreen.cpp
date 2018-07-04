//
//  ToolzResizeScreen.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "ToolzResizeScreen.h"
#include "core_includes.h"
#include "core_app_shell.h"
#include "FApp.h"

ToolzResizeScreen::ToolzResizeScreen()
{
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    mPanDragData = 0;
    mPanWindowStartX = 0.0f;
    mPanWindowStartY = 0.0f;
    mPanTouchStartX = 0.0f;
    mPanTouchStartY = 0.0f;
    
    
    
    mResizeLeft = gVirtualDevX;
    mResizeTop = gVirtualDevY;
    mResizeRight = gVirtualDevX + gVirtualDevWidth;
    mResizeBottom = gVirtualDevY + gVirtualDevHeight;
    mResizeWidth = gVirtualDevWidth;
    mResizeHeight = gVirtualDevHeight;
    
    mResizeDragCornerX = 0.0f;
    mResizeDragCornerY = 0.0f;
    mResizeCornerIndex = -1;
    
    
    mScreenResizeCornerX[0] = gVirtualDevX;
    mScreenResizeCornerY[0] = gVirtualDevY;
    mScreenResizeCornerX[1] = gVirtualDevX;
    mScreenResizeCornerY[1] = gVirtualDevY + gVirtualDevHeight;
    mScreenResizeCornerX[2] = gVirtualDevX + gVirtualDevWidth;
    mScreenResizeCornerY[2] = gVirtualDevY;
    mScreenResizeCornerX[3] = gVirtualDevX + gVirtualDevWidth;
    mScreenResizeCornerY[3] = gVirtualDevY + gVirtualDevHeight;
    
}

ToolzResizeScreen::~ToolzResizeScreen()
{
    
}

void ToolzResizeScreen::PositionContent()
{
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    if(mPanDragData == 0)
    {
        mScreenResizeCornerX[0] = gVirtualDevX;
        mScreenResizeCornerY[0] = gVirtualDevY;
        
        mScreenResizeCornerX[1] = gVirtualDevX;
        mScreenResizeCornerY[1] = gVirtualDevY + gVirtualDevHeight;
        
        mScreenResizeCornerX[2] = gVirtualDevX + gVirtualDevWidth;
        mScreenResizeCornerY[2] = gVirtualDevY;
        
        mScreenResizeCornerX[3] = gVirtualDevX + gVirtualDevWidth;
        mScreenResizeCornerY[3] = gVirtualDevY + gVirtualDevHeight;
    }
}

void ToolzResizeScreen::Update()
{
    
}

void ToolzResizeScreen::Draw()
{
    //Graphics::SetColor();
    Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Graphics::SetColor(0.0f, 0.0f, 0.0f, 0.0f);
    Graphics::DrawRect(0.0f, 0.0f, mScreenResizeCornerX[0], gDeviceHeight);
    Graphics::DrawRect(mScreenResizeCornerX[2], 0.0f, gDeviceWidth - mScreenResizeCornerX[2], gDeviceHeight);
    Graphics::DrawRect(mScreenResizeCornerX[0], 0.0f, (mScreenResizeCornerX[2] - mScreenResizeCornerX[0]), mScreenResizeCornerY[0]);
    Graphics::DrawRect(mScreenResizeCornerX[0], mScreenResizeCornerY[1], (mScreenResizeCornerX[2] - mScreenResizeCornerX[0]), gDeviceHeight - mScreenResizeCornerY[1]);
    
    Graphics::SetColor(0.02f, 0.03f, 0.35f, 0.8f);
    Graphics::DrawLine(mScreenResizeCornerX[0], mScreenResizeCornerY[0], mScreenResizeCornerX[1], mScreenResizeCornerY[1], 2.0f);
    Graphics::DrawLine(mScreenResizeCornerX[1], mScreenResizeCornerY[1], mScreenResizeCornerX[3], mScreenResizeCornerY[3], 2.0f);
    Graphics::DrawLine(mScreenResizeCornerX[2], mScreenResizeCornerY[2], mScreenResizeCornerX[3], mScreenResizeCornerY[3], 2.0f);
    Graphics::DrawLine(mScreenResizeCornerX[0], mScreenResizeCornerY[0], mScreenResizeCornerX[2], mScreenResizeCornerY[2], 2.0f);
    
    Graphics::SetColor(1.0f, 0.3f, 1.0f, 0.8f);
    Graphics::DrawLine(mScreenResizeCornerX[0], mScreenResizeCornerY[0], mScreenResizeCornerX[1], mScreenResizeCornerY[1]);
    Graphics::DrawLine(mScreenResizeCornerX[1], mScreenResizeCornerY[1], mScreenResizeCornerX[3], mScreenResizeCornerY[3]);
    Graphics::DrawLine(mScreenResizeCornerX[2], mScreenResizeCornerY[2], mScreenResizeCornerX[3], mScreenResizeCornerY[3]);
    Graphics::DrawLine(mScreenResizeCornerX[0], mScreenResizeCornerY[0], mScreenResizeCornerX[2], mScreenResizeCornerY[2]);
    
    
    for(int i = 0; i < 4; i++)
    {
        float aX = mScreenResizeCornerX[i];
        float aY = mScreenResizeCornerY[i];
            
            Graphics::SetColor();
            Graphics::DrawRect(aX - 5.0f, aY - 5.0f, 10.0f, 10.0f);
            
            
            Graphics::SetColor(0.4f, 0.4f, 0.4f);
        Graphics::DrawRect(aX - 3.0f, aY - 3.0f, 6.0f, 6.0f);
    }
    
    Graphics::SetColor();
}




void ToolzResizeScreen::TouchDown(float pX, float pY, void *pData)
{
    
        mPanDragData = pData;
        
        mPanTouchStartX = pX;
        mPanTouchStartY = pY;
        
        mPanWindowStartX = gVirtualDevX;
        mPanWindowStartY = gVirtualDevY;
        
        float aMinDist = 45.0f;
        if(gDeviceWidth < 600.0f)aMinDist = 24.0f;
        
        mResizeCornerIndex = -1;
        
        for(int i = 0; i<4; i++)
        {
            
            mScreenResizeCornerDragStartX[i] = mScreenResizeCornerX[i];
            mScreenResizeCornerDragStartY[i] = mScreenResizeCornerY[i];
            
            float aX = mScreenResizeCornerX[i];
            float aY = mScreenResizeCornerY[i];
            
            float aDist = Distance(pX, pY, aX, aY);
            
            if(aDist < aMinDist)
            {
                mResizeCornerIndex = i;
                
                mResizeDragCornerX = aX;
                mResizeDragCornerY = aY;
            }
        }
    
    if(mResizeCornerIndex == -1)
    {
        if((pX >= gVirtualDevX) && (pY >= gVirtualDevY) &&
           (pX <= (gVirtualDevX + gVirtualDevWidth)) && (pY <= (gVirtualDevY + gVirtualDevHeight)))
        {
            mPanDragData = 0;
        }
    }
    
}

void ToolzResizeScreen::TouchMove(float pX, float pY, void *pData)
{
    
        if(mPanDragData == pData)
        {
            
            if((mResizeCornerIndex >= 0) && (mResizeCornerIndex < 4))
            {
                float aX = mResizeDragCornerX + (pX - mPanTouchStartX);
                float aY = mResizeDragCornerY + (pY - mPanTouchStartY);
                
                mScreenResizeCornerX[mResizeCornerIndex] = aX;
                mScreenResizeCornerY[mResizeCornerIndex] = aY;
                
                if(mResizeCornerIndex == 0){mScreenResizeCornerX[1] = aX;mScreenResizeCornerY[2] = aY;}
                if(mResizeCornerIndex == 1){mScreenResizeCornerX[0] = aX;mScreenResizeCornerY[3] = aY;}
                if(mResizeCornerIndex == 2){mScreenResizeCornerX[3] = aX;mScreenResizeCornerY[0] = aY;}
                if(mResizeCornerIndex == 3){mScreenResizeCornerX[2] = aX;mScreenResizeCornerY[1] = aY;}
                
                ComputeResizeRect();
                
                AppShellSetVirtualFrame(mResizeLeft, mResizeTop, mResizeWidth, mResizeHeight);
            }
            else
            {
                float aDeltaX = pX - mPanTouchStartX;
                float aDeltaY = pY - mPanTouchStartY;
                
                float aX = mPanWindowStartX + (aDeltaX);
                float aY = mPanWindowStartY + (aDeltaY);
                
                for(int i=0;i<4;i++)
                {
                    mScreenResizeCornerX[i] = (mScreenResizeCornerDragStartX[i] + aDeltaX);
                    mScreenResizeCornerY[i] = (mScreenResizeCornerDragStartY[i] + aDeltaY);
                }
                
                AppShellSetVirtualFrame(aX, aY, gVirtualDevWidth, gVirtualDevHeight);
                
                PositionContent();
            }
        }
}

void ToolzResizeScreen::TouchUp(float pX, float pY, void *pData)
{
    mPanDragData = 0;
}

void ToolzResizeScreen::TouchFlush()
{
    mPanDragData = 0;
}


void ToolzResizeScreen::PanStart()
{
    mPanDragData = 0;
}

void ToolzResizeScreen::PanEnd()
{
    mPanDragData = 0;
}

void ToolzResizeScreen::ComputeResizeRect()
{
    
    for(int i = 0; i<4; i++)
    {
        if(mScreenResizeCornerX[i] < 0.0f)mScreenResizeCornerX[i] = 0.0f;
        if(mScreenResizeCornerX[i] > gDeviceWidth)mScreenResizeCornerX[i] = gDeviceWidth;
        
        if(mScreenResizeCornerY[i] < 0.0f)mScreenResizeCornerY[i] = 0.0f;
        if(mScreenResizeCornerY[i] > gDeviceHeight)mScreenResizeCornerY[i] = gDeviceHeight;
    }
    
    mResizeLeft = mScreenResizeCornerX[0];
    mResizeTop = mScreenResizeCornerY[0];
    
    mResizeRight = mScreenResizeCornerX[3];
    mResizeBottom = mScreenResizeCornerY[3];
    
    for(int i = 0; i<4; i++)
    {
        int aX = mScreenResizeCornerX[i];
        int aY = mScreenResizeCornerY[i];
        
        if(aX < mResizeLeft)mResizeLeft = aX;
        if(aX > mResizeRight)mResizeRight = aX;
        
        if(aY < mResizeTop)mResizeTop = aY;
        if(aY > mResizeBottom)mResizeBottom = aY;
    }
    
    mResizeWidth = mResizeRight - mResizeLeft;
    mResizeHeight = mResizeBottom - mResizeTop;
    
    //BaseDeviceSizeChanged(mResizeLeft, mResizeTop, mResizeWidth, mResizeHeight);
    
}


