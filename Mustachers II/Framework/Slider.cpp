/*
 *  Slider.cpp
 *  Fly Swatter
 *
 *  Created by Nick Raptis on 12/31/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "Slider.h"

Slider::Slider()
{
	mClickX=0;
	mClickY=0;
	mClicked=0;
	mDrawOver=0;
	
	mSliderOffsetX=0;
	mSliderOffsetY=0;
	
	mMax=0;
	mMin=0;
    
	mBorder=0;
	mVertical=0;
	mDrawRect=0;
	mAutoSnap=true;
    
    
    mSpriteBack=0;
    mSpriteBackDown=0;
    
    mSpriteThumb=0;
    mSpriteThumbDown=0;
    
}

Slider::~Slider()
{
	
}


void Slider::Setup(int x, int y, Sprite *pSiderThumb, Sprite *pSiderThumbDown, Sprite *pBarImage, Sprite *pBarImageDown)
{
    
    int aWidth = mWidth;
    int aHeight = mHeight;
    
    if(pBarImage == 0)pBarImage=pBarImageDown;
    
    mSpriteBack=pBarImage;
    mSpriteBackDown=pBarImageDown;
    
    if(pBarImage)
    {
        aWidth = pBarImage->mWidth;
        aHeight = pBarImage->mHeight;
    }
    
    if(!pSiderThumb)pSiderThumb=pSiderThumbDown;
    
    mSpriteThumb=pSiderThumb;
    mSpriteThumbDown=pSiderThumbDown;
    
    Canvas::Size(x,y,aWidth,aHeight);
    
    
	FindEdges();
}


void Slider::SetVertical()
{
	mVertical=1;
	FindEdges();
}

void Slider::Size(int x, int y, int pWidth, int pHeight)
{
	Canvas::Size(x,y,pWidth,pHeight);
	FindEdges();
}

void Slider::SetBorder(int pBorder)
{
	mBorder=pBorder;
	FindEdges();
}

void Slider::FindEdges()
{
	if(mSpriteThumb)
	{
		if(mVertical)
		{
			mMin=mSpriteThumb->mHeight/2+mBorder;
			mMax=mHeight-mSpriteThumb->mHeight/2-mBorder;
			
			
			mSpriteY=mMin;
			mSpriteX=mWidth/2;
		}
		else
		{
			mMin=mSpriteThumb->mWidth/2+mBorder;
			mMax=mWidth-mSpriteThumb->mWidth/2-mBorder;
			
			
			mSpriteX=mMin;
			mSpriteY=mHeight/2;
		}
		
	}
}

void Slider::Touch(int x, int y)
{
	mClicked=0;
	if(!mSpriteThumb)return;
	if(x>=mSpriteX-mSpriteThumb->mWidth/2&&
	   x<=mSpriteX+mSpriteThumb->mWidth/2&&
	   y>=mSpriteY-mSpriteThumb->mHeight/2&&
	   y<=mSpriteY+mSpriteThumb->mHeight/2)
	{
		mClicked=1;
		mClickX=x;
		mClickY=y;
		mClickSpriteX=mSpriteX;
		mClickSpriteY=mSpriteY;
        
        
#ifdef BUTTON_SETUP
        
        if(x >= 0 && y >= 0 && x <= mWidth && y<= mHeight)
        {
            mDragTimer=0;
            
            mTouchMouseX=x;
            mTouchMouseY=y;
            
            mTouchOffseX=mX;
            mTouchOffseY=mY;
        }
#endif
	}
	else
	{
		if(mAutoSnap)
		{
			mClicked=1;
			mClickX=x;
			mClickY=y;
			
			if(mVertical)
			{
				mSpriteY=y;
			}
			else
			{
				mSpriteX=x;
			}
			
			mClickSpriteX=mSpriteX;
			mClickSpriteY=mSpriteY;
			
		}
        
        

        
        
        
	}
	Drag(x,y);
}

void Slider::Drag(int x, int y)
{
	if(!mSpriteThumb||!mClicked)return;
    
#ifdef BUTTON_SETUP
    
    
    
    mX = mTouchOffseX - (mTouchMouseX - x);
    mY = mTouchOffseY - (mTouchMouseY - y);
    
#endif
    
	if(mVertical)
	{
		mSpriteY=mClickSpriteY+(y-mClickY);
		if(mSpriteY<mMin)mSpriteY=mMin;
		if(mSpriteY>mMax)mSpriteY=mMax;
	}
	else
	{
		mSpriteX=mClickSpriteX+(x-mClickX);
		if(mSpriteX<mMin)mSpriteX=mMin;
		if(mSpriteX>mMax)mSpriteX=mMax;
	}
	
}

void Slider::Release(int x, int y)
{
#ifdef BUTTON_SETUP
    
    printf("Slider Position [%d %d] - %x\n", (int)mX, (int)mY, this);
    
#endif
    
	mClicked=0;
}

void Slider::SetSprite(Sprite *pSprite)
{
	mSpriteThumb=pSprite;
	FindEdges();
}

void Slider::Draw()
{
	
    
    
    
}



float  Slider::GetPercent()
{
	float aReturn=0;
	
	if(mMax!=mMin)
	{
		if(mVertical)aReturn=(float)(mSpriteY-mMin)/(float)(mMax-mMin);
		else aReturn=(float)(mSpriteX-mMin)/(float)(mMax-mMin);
	}
	
	if(aReturn>1)aReturn=1;
	if(aReturn<0)aReturn=0;
	return aReturn;
}
void  Slider::SetPercent(float pPercent)
{
	if(pPercent<0)pPercent=0.0f;
	if(pPercent>1)pPercent=1.0f;
	if(mMax>0)
	{
		if(mVertical)
		{
			mSpriteY=mMin+(int)((float)(mMax-mMin)*pPercent);
		}
		else
		{
			mSpriteX=mMin+(int)((float)(mMax-mMin)*pPercent);
		}
	}
}

void Slider::DrawOver()
{
	if(mDrawRect)
	{
		SetColor(1,0.5f,1,0.25f);
		DrawRect(0,0,mWidth,mHeight);
		
	}
	SetColor();
    
    
    
    if(mClicked && mSpriteBackDown)
    {
        mSpriteBackDown->Center((float)mWidth / 2, (float)mHeight / 2);
    }
    else if(mSpriteBack)
    {
        mSpriteBack->Center(((float)mWidth / 2), (float)mHeight / 2);
    }
    
    
	if(mSpriteThumbDown && mClicked)
	{
		mSpriteThumbDown->Center(mSpriteX + mSliderOffsetX,mSpriteY + mSliderOffsetY);
	}
	else if(mSpriteThumb)
	{
		mSpriteThumb->Center(mSpriteX + mSliderOffsetX,mSpriteY + mSliderOffsetY);
	}
    
#ifdef BUTTON_SETUP
    
    SetColor(0,0,0,0.25f);
    DrawRect(0,0,mWidth,mHeight);
    
    SetColor(1,1,1,0.25f);
    OutlineRect(0,0,mWidth,mHeight,6);
    
    if(mSpriteThumb)
    {
        //mSpriteThumb
        
        
        if(mVertical)
        {
            SetColor(0.25f);
            
            mSpriteThumb->Center(mSpriteX + mSliderOffsetX,mMin + mSliderOffsetY);
            mSpriteThumb->Center(mSpriteX + mSliderOffsetX,mMax + mSliderOffsetY);
            
            SetColor();
        }
        else
        {
            SetColor(0.25f);
            
            mSpriteThumb->Center(mMin + mSliderOffsetX,mSpriteY + mSliderOffsetY);
            mSpriteThumb->Center(mMax + mSliderOffsetX,mSpriteY + mSliderOffsetY);
            
            SetColor();
        }
    }
    
#endif
	
}