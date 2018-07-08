/*
 *  Slider.h
 *  Fly Swatter
 *
 *  Created by Nick Raptis on 12/31/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#ifndef SLIDER_H
#define SLIDER_H

#include "Application.h"
#include "Include.h"
#include "Button.h"


class Slider : public Canvas
{
public:
	Slider();
	~Slider();
	
	virtual void			Touch(int x, int y);
	virtual void			Drag(int x, int y);
	virtual void			Release(int x, int y);
    
    void                    Setup(int x, int y, Sprite *pSiderThumb, Sprite *pSiderThumbDown, Sprite *pBarImage=0, Sprite *pBarImageDown=0);
    
    void                    SetSprite(Sprite *pSprite);
    
	virtual void			Size(int x, int y, int pWidth, int pHeight);
	void					SetBorder(int pBorder);
	void					SetVertical();
	
	float					GetPercent();
	void					SetPercent(float pPercent);
    
	virtual void			Draw();
	virtual void			DrawOver();
	
	void					FindEdges();
	
    
    Sprite                  *mSpriteBack;
    Sprite                  *mSpriteBackDown;
    
    Sprite                  *mSpriteThumb;
    Sprite                  *mSpriteThumbDown;
    
	int						mClickX, mClickY, mClickSpriteX, mClickSpriteY;
	int						mClicked;
	int						mDrawOver;
	int						mBorder;
	int						mVertical;
	int						mDrawRect;
	
	int						mSliderOffsetX;
	int						mSliderOffsetY;
	
	
	int						mSpriteX,mSpriteY;
	int						mMax,mMin;
	
	bool					mAutoSnap;
    
#ifdef BUTTON_SETUP
    
    int                     mTouchMouseX;
    int                     mTouchMouseY;
    
    int                     mTouchOffseX;
    int                     mTouchOffseY;
    
    int                     mDragTimer;
    
#endif
    
};

#endif