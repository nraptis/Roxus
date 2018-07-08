#include "DragRecorder.h"
#include "stdafx.h"

DragRecorder::DragRecorder()
{
	StartDrag(0,0);
}

DragRecorder::~DragRecorder()
{
	
}

void DragRecorder::StartDrag(float x, float y)
{
	for(int i=0;i<DRAG_STATES-1;i++)
	{
		mHistoryX[i]=0;
		mHistoryY[i]=0;
	}
	mLastX=x;
	mLastY=y;
	mSumX=0;
	mSumY=0;
}

void DragRecorder::Record(float x, float y)
{
	float aMoveX=x-mLastX;
	float aMoveY=y-mLastY;
	mLastX=x;
	mLastY=y;
	mSumX+=aMoveX;
	mSumY+=aMoveY;
	mSumX-=mHistoryX[0];
	mSumY-=mHistoryY[0];
	for(int i=0;i<DRAG_STATES;i++)
	{
		mHistoryX[i]=mHistoryX[i+1];
		mHistoryY[i]=mHistoryY[i+1];
	}
	mHistoryX[DRAG_STATES-1]=aMoveX;
	mHistoryY[DRAG_STATES-1]=aMoveY;
}

FPoint DragRecorder::Release()
{
	return FPoint(mSumX/DRAG_STATES,mSumY/DRAG_STATES);
}
