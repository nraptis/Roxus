/*
 *  LinePath.h
 *  Darts
 *
 *  Created by Nick Raptis on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "stdafx.h"

#ifndef LINE_PATH_H
#define LINE_PATH_H

#define LINE_PATH_NODE_PAUSE 0
#define LINE_PATH_NODE_POINT 1
#define LINE_PATH_NODE_POINT_EASE 2


class LinePath
{
public:
	LinePath();
	~LinePath();
	
	void				Update();
	
	LinePath			*Duplicate();
    
    
	
	void				AddNode(int pType, int pValue, float pX, float pY);
	void				AddPoint(float x, float y);
	void				AddPause(int pTime);
	
	void				ModifyPauses(float pPercent);
	
	void				FlipHorizontal(float pCenter=320/2);
	void				FlipVertical(float pCenter=480/2);
	
	int					*mType;
    
	int					*mValue;
    
    float				*mPathX;
	float				*mPathY;
	
	float				mX;
	float				mY;
	
	float				mTargetX;
	float				mTargetY;
	
	int					mCount;
	int					mSize;
	
	bool				mComplete;
	
	int					mCurrentNode;
	int					mMode;
	int					mTimer;
	int					mTime;
	
	float				mSpeed;
	
	
	
	float				mDeceleration;
	float				mDecelerationDistance;
	
protected:
	
	void				Advance();
								 
};

#endif