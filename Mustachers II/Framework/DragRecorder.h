#define DRAG_STATES 6

#ifndef DRAG_RECORDER_H
#define DRAG_RECORDER_H

#include "FPoint.h"

class DragRecorder
{
public:
	DragRecorder();
	~DragRecorder();
	
	void			StartDrag(float x, float y);
	void			Record(float x, float y);
	FPoint			Release();
	
	float			mHistoryX[DRAG_STATES];
	float			mHistoryY[DRAG_STATES];
	float			mLastX;
	float			mLastY;
	float			mSumX;
	float			mSumY;
	
};

#endif