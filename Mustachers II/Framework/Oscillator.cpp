#include "Oscillator.h"
#include "stdafx.h"

Oscillator::Oscillator()
{
	mDir=1;
	mIndex=0;
	mTime=1;
	mPauseTimer=0;
	mPause=0;
}

Oscillator::Oscillator(int pTime)
{
	mDir=1;
	mIndex=0;
	mTime=pTime;
	mPauseTimer=0;
	mPause=0;
}

Oscillator::~Oscillator()
{
	
}

void Oscillator::Update()
{
	if(mPauseTimer>0)
	{
		mPauseTimer--;
	}
	else
	{
	if(mDir==1)
	{
		mIndex++;
		if(mIndex>=mTime)
		{
			mPauseTimer=mPause;
			mDir=-1;
		}
	}
	else
	{
		mIndex--;
		if(mIndex<=0)
		{
			mPauseTimer=mPause;
			mDir=1;
		}
	}
	}
}		

void Oscillator::Randomize()
{
	mIndex=gRand.Get(mTime);
	if(gRand.Get(2)==0)mDir=1;
	else mDir=-1;
}