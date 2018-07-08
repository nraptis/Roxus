/*
 *  LinePath.cpp
 *  Darts
 *
 *  Created by Nick Raptis on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "LinePath.h"

LinePath::LinePath()
{
	mSize=0;
	mCount=0;
	
	mX=0;
	mY=0;
	
	mCurrentNode=-1;
	mMode=0;
	mTimer=0;
	mTime=0;
	mSpeed=1.0f;
	
	mPathX=0;
	mPathY=0;
	mValue=0;
	mType=0;
	mTargetX=0;
	mTargetY=0;
	
	mDeceleration=0;
	mDecelerationDistance=0;
	
	mComplete=false;
}

LinePath::~LinePath()
{
	delete[]mPathX;
	mPathX=0;
	delete[]mPathY;
	mPathY=0;
	delete[]mType;
	mType=0;
	delete[]mValue;
	mValue=0;
}

void LinePath::AddNode(int pType, int pValue, float pX, float pY)
{
	if(mCount==mSize)
	{
		mSize=mCount+mCount/2+1;
		
		int *aType=new int[mSize*2+1];
		for(int i=0;i<mCount;i++)aType[i]=mType[i];
		delete[]mType;
		mType=aType;
		
		
		int *aValue=new int[mSize*2+1];
		for(int i=0;i<mCount;i++)aValue[i]=mValue[i];
		delete[]mValue;
		mValue=aValue;
		
		
		float *aX=new float[mSize*2+1];
		for(int i=0;i<mCount;i++)aX[i]=mPathX[i];
		delete[]mPathX;
		mPathX=aX;
		
		float *aY=new float[mSize*2+1];
		for(int i=0;i<mCount;i++)aY[i]=mPathY[i];
		delete[]mPathY;
		mPathY=aY;
	}
	
	
	
	mPathX[mCount]=pX;
	mPathY[mCount]=pY;
	mValue[mCount]=pValue;
	mType[mCount]=pType;
	mCount++;
}

void LinePath::AddPoint(float x, float y)
{
	AddNode(LINE_PATH_NODE_POINT, 0, x, y);
}

void LinePath::AddPause(int pTime)
{
	AddNode(LINE_PATH_NODE_PAUSE, pTime, 0, 0);
}



void LinePath::Update()
{
	if(mCurrentNode>=mCount)
	{
		return;
	}
	
	if(mCurrentNode==-1)
	{
		Advance();
	}
	
	if(mMode==LINE_PATH_NODE_PAUSE)
	{
		mTimer++;
		if(mTimer>=mTime)
		{
			Advance();
		}
	}
	else if(mMode==LINE_PATH_NODE_POINT)
	{
		float aDiffX = mTargetX - mX;
		float aDiffY = mTargetY - mY;
		float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
		
		if(aDist < 0.25f)
		{
			aDist = 0;
		}
		else
		{
			aDist = sqrtf(aDist);
			
			aDiffX /= aDist;
			aDiffY /= aDist;
		}
		
		
		//(- Vo^2) / (2 * dist)  = 2*a*s 
		
		
		
		if(aDist < mSpeed || mSpeed <= 0)
		{
			mX=mTargetX;
			mY=mTargetY;
			Advance();
		}
		else
		{
			if(aDist<mDecelerationDistance && mDeceleration==0)
			{
				mDeceleration = (mSpeed * mSpeed) / (2 * aDist);
			}
			
			mSpeed -= mDeceleration;
			
			mX += aDiffX * mSpeed;
			mY += aDiffY * mSpeed;
		}

		
	}
}

void LinePath::Advance()
{
	mDeceleration=0;
	if(mCurrentNode==-1)
	{
		for(int i=mCount-1;i>=0;i--)
		{
			if(mType[i]==LINE_PATH_NODE_POINT)
			{
				mX=mPathX[i];
				mY=mPathY[i];
			}
		}
		
		mCurrentNode=0;
		
		mTargetX=mX;
		mTargetY=mY;
	}
	else
	{
		mCurrentNode++;
		if(mCurrentNode>=0&&mCurrentNode<mCount)
		{
			mMode=mType[mCurrentNode];
		}
		else
		{
			mComplete=true;
		}

	}
	
	if(mCurrentNode>=0&&mCurrentNode<mCount)
	{
		if(mMode==LINE_PATH_NODE_PAUSE)
		{
			mTime=mValue[mCurrentNode];
			mTimer=0;
		}
		else if(mMode==LINE_PATH_NODE_POINT)
		{
			mTargetX=mPathX[mCurrentNode];
			mTargetY=mPathY[mCurrentNode];
		}
	}
}

void LinePath::ModifyPauses(float pPercent)
{
	for(int i=0;i<mCount;i++)
	{
		if(mType[i]==LINE_PATH_NODE_PAUSE)
		{
			mValue[i]=(int)((float)mValue[i] * (float)pPercent)+1;
		}
	}
}

LinePath *LinePath::Duplicate()
{
	LinePath *aReturn=new LinePath();
	
	if(mCount > 0)
	{
		int *aType=new int[mCount];
		int *aValue=new int[mCount];
		float *aX=new float[mCount];
		float *aY=new float[mCount];
		
		for(int i=0;i<mCount;i++)aType[i]=mType[i];
		for(int i=0;i<mCount;i++)aValue[i]=mValue[i];
		for(int i=0;i<mCount;i++)aX[i]=mPathX[i];
		for(int i=0;i<mCount;i++)aY[i]=mPathY[i];
		
		aReturn->mType=aType;
		aReturn->mValue=aValue;
		aReturn->mPathX=aX;
		aReturn->mPathY=aY;
	}
	
	aReturn->mDecelerationDistance=mDecelerationDistance;
	aReturn->mSize=mCount;
	aReturn->mCount=mCount;
	aReturn->mSpeed=mSpeed;
	
	return aReturn;
}


void LinePath::FlipHorizontal(float pCenter)
{
	for(int i=0;i<mCount;i++)
	{
		mPathX[i]=pCenter+(pCenter-mPathX[i]);
	}
}

void LinePath::FlipVertical(float pCenter)
{
	for(int i=0;i<mCount;i++)
	{
		mPathY[i]=pCenter+(pCenter-mPathY[i]);
	}
}




