//
//  FTouchManager.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 2/15/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FTouchManager.h"
#include "FApp.h"
#include "core_includes.h"


FMouseAction::FMouseAction() {
    mX = 0.0f;
    mY = 0.0f;
    mType = MOUSE_MOVE;
    mDirection = 1;
    mButton = -1;
}

FMouseAction::~FMouseAction() { }

FTouchAction::FTouchAction() {
    mX = 0.0f;
    mY = 0.0f;
    mTouchState = TOUCH_STATE_INACTIVE;
    mData = 0;
}

FTouchAction::~FTouchAction() { }

FTouch::FTouch()
{
    mRenderIndex = 0;
    
    for(int i=0;i<TOUCH_HISTORY_STATES;i++)
    {
        mHistoryX[i] = 0.0f;
        mHistoryY[i] = 0.0f;
        mHistoryTime[i] = 0;
    }
    
    Reset(0.0f, 0.0f, 0);
}

FTouch::~FTouch()
{
    
}

void FTouch::Reset(float pX, float pY, void *pData)
{
    Reset(pX, pY);
    mData = pData;
    
    mHistoryX[0] = pX;
    mHistoryY[0] = pY;
    mHistoryTime[0] = mTimer;
    
    mHistoryCount = 1;
}

void FTouch::Reset(float pX, float pY)
{
    mHistoryCount = 0;
    
    mX = pX;
    mY = pY;
    
    mTimer = 0;
    mLastActionTime = 0;
    
    mState = TOUCH_STATE_DOWN;
    
    mChanged = true;
    
    mData = 0;
}


void FTouch::Move(float pX, float pY)
{
    mX = pX;
    mY = pY;
    
    mChanged = true;
    
    if(mState == TOUCH_STATE_DOWN || mState == TOUCH_STATE_INACTIVE)
    {
        mState = TOUCH_STATE_MOVING;
    }
    
    mX = pX;
    mY = pY;
    
    mLastActionTime = mTimer;
    
    if(mHistoryCount == TOUCH_HISTORY_STATES)
    {
        for(int i=1;i<TOUCH_HISTORY_STATES;i++)mHistoryX[i - 1] = mHistoryX[i];
        for(int i=1;i<TOUCH_HISTORY_STATES;i++)mHistoryY[i - 1] = mHistoryY[i];
        for(int i=1;i<TOUCH_HISTORY_STATES;i++)mHistoryTime[i - 1] = mHistoryTime[i];
        
        mHistoryX[TOUCH_HISTORY_STATES - 1] = pX;
        mHistoryY[TOUCH_HISTORY_STATES - 1] = pY;
        mHistoryTime[TOUCH_HISTORY_STATES - 1] = mTimer;
    }
    else
    {
        mHistoryX[mHistoryCount] = pX;
        mHistoryY[mHistoryCount] = pY;
        mHistoryTime[mHistoryCount] = mTimer;
        mHistoryCount++;
    }
}

void FTouch::Up(float pX, float pY)
{
    mX = pX;
    mY = pY;
    mChanged = true;
    mState = TOUCH_STATE_MOVING;
}

FTouchManager::FTouchManager() {
	mKeyQueueLength = 0;
    for (int i=0;i<TOUCH_MANAGER_MAX_QUEUE_TOUCHES;i++) {
        FTouch *aTouch = new FTouch();
        aTouch->Reset(0.0f, 0.0f);
        mTouchQueue[i] = aTouch;
    }
    mTouchQueue[TOUCH_MANAGER_MAX_QUEUE_TOUCHES] = 0;
    
    for (int i=0;i<TOUCH_MANAGER_MAX_TOUCHES;i++) {
        mTouch[i] = 0;
    }
    mTouch[TOUCH_MANAGER_MAX_TOUCHES] = 0;
    
    mTouchCount = 0;
    mTouchQueueCount = TOUCH_MANAGER_MAX_QUEUE_TOUCHES;
    
    mRenderIndex = 0;
    
    mAndroidFakePointer[0] = (void *)(0xDEADBEE7);
    mAndroidFakePointer[1] = (void *)(0xBA5EBA11);
    mAndroidFakePointer[2] = (void *)(0xC0A1E5CE);
    mAndroidFakePointer[3] = (void *)(0xDEADBEA7);
    mAndroidFakePointer[4] = (void *)(0xE5CA1ADE);
    mAndroidFakePointer[5] = (void *)(0xF005BA11);
    mAndroidFakePointer[6] = (void *)(0x57EE1EDF);
    mAndroidFakePointer[7] = (void *)(0x0DDBA11E);
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
	mMouseLeftDown = false;
	mMouseRightDown = false;
	mMouseMiddleDown = false;
}

FTouchManager::~FTouchManager() {
    
}

void FTouchManager::Update() {
	if (gAppBase == 0) {
        Reset();
        return;
    }

    for (int i = 0; i < mKeyQueueLength; i++) {
        if(mKeyActionType[i] == 1)gAppBase->ProcessKeyDown(mKeyQueue[i]);
        if(mKeyActionType[i] == -1)gAppBase->ProcessKeyUp(mKeyQueue[i]);
    }
    mKeyQueueLength = 0;

    EnumList(FTouchAction, aAction, mTouchActionQueue) {
        if(aAction->mTouchState == TOUCH_STATE_MOVING) {
            gAppBase->ProcessTouchMove(aAction->mX, aAction->mY, aAction->mData);
            FTouch *aTouch = GetTouch(aAction->mData);
            if(aTouch) {
                aTouch->Move(aAction->mX, aAction->mY);
            }
        } else if(aAction->mTouchState == TOUCH_STATE_DOWN) {
            gAppBase->ProcessTouchDown(aAction->mX, aAction->mY, aAction->mData);
            FTouch *aTouch = GetTouchDown(aAction->mData);
            if(aTouch) {
                aTouch->mRenderIndex = mRenderIndex;
                aTouch->Reset(aAction->mX, aAction->mY, aAction->mData);
                mRenderIndex++;
                if(mRenderIndex > 5)mRenderIndex = 0;
            }
        } else { //if((aAction->mTouchState == TOUCH_STATE_RELEASED) || (aAction->mTouchState == TOUCH_STATE_CANCELED))
            gAppBase->ProcessTouchUp(aAction->mX, aAction->mY, aAction->mData);
            FinishedTouch(GetTouch(aAction->mData));
        }
    }
    
    
    FTouch *aAutoDequeue = 0;
    for (int i=0;i<mTouchCount;i++) {
        mTouch[i]->mTimer++;
        if ((mTouch[i]->mTimer - mTouch[i]->mLastActionTime) > 1000) {
            aAutoDequeue = mTouch[i];
        }
    }
    
    if (aAutoDequeue) {
        Log("Touch Expired.. [%x]\n", (unsigned int)((unsigned long)(aAutoDequeue->mData)));
        FinishedTouch(aAutoDequeue);
    }
    
    EnumList (FTouchAction, aAction, mTouchActionQueue) {
        mTouchActionRecycle.Add(aAction);
    }
    mTouchActionQueue.RemoveAll();



    
    EnumList(FMouseAction, aAction, mMouseActionQueue) {
        if(aAction->mType == MOUSE_MOVE) {
            gAppBase->ProcessMouseMove(aAction->mX, aAction->mY);
        } else if(aAction->mType == MOUSE_DOWN) {
            gAppBase->ProcessMouseDown(aAction->mX, aAction->mY, aAction->mButton);
        } else if(aAction->mType == MOUSE_UP) {
            gAppBase->ProcessMouseUp(aAction->mX, aAction->mY, aAction->mButton);
        } else {
            gAppBase->ProcessMouseWheel(aAction->mDirection);
        }
    }
    EnumList (FMouseAction, aAction, mMouseActionQueue) {
        mMouseActionRecycle.Add(aAction);
    }
    mMouseActionQueue.RemoveAll();
}

void FTouchManager::Draw() {
    Graphics::SetColor(1.0f, 0.0f, 1.0f);
    for (int i=0;i<mTouchCount;i++) {
        Graphics::DrawPoint(mTouch[i]->mX, mTouch[i]->mY, 16.0f);
    }
}

void FTouchManager::Reset()
{
    
}

void FTouchManager::EnqueueTouchActionDroid(float pX, float pY, int pTouchState, int pIndex) {
    if ((pIndex >= 0) && (pIndex < TOUCH_FAKE_POINTER_COUNT)) {
        void *aData = mAndroidFakePointer[pIndex];
        if (pTouchState == TOUCH_STATE_MOVING) {
            
        } else if ((pTouchState == TOUCH_STATE_RELEASED) || (pTouchState == TOUCH_STATE_CANCELED)) {
            void *aHold = mAndroidFakePointer[pIndex];
            for(int i=pIndex;i<(TOUCH_FAKE_POINTER_COUNT - 1);i++)
            {
                mAndroidFakePointer[i] = mAndroidFakePointer[i + 1];
            }
            mAndroidFakePointer[TOUCH_FAKE_POINTER_COUNT - 1] = aHold;
        } else if (pTouchState == TOUCH_STATE_DOWN) {
            void *aHold = mAndroidFakePointer[TOUCH_FAKE_POINTER_COUNT - 1];
            for (int i=(TOUCH_FAKE_POINTER_COUNT - 2);i>=pIndex;i--) {
                mAndroidFakePointer[i + 1] = mAndroidFakePointer[i];
            }
            mAndroidFakePointer[pIndex] = aHold;
            aData = aHold;
        }
        EnqueueTouchAction(pX, pY, pTouchState, aData);
    }
}

void FTouchManager::EnqueueTouchAction(float pX, float pY, int pTouchState, void *pData) {
    FTouchAction *aAction = 0;
    if(pTouchState == TOUCH_STATE_MOVING) {
        for(int i=mTouchActionQueue.mCount - 1;i>=0;i--) {
            aAction = (FTouchAction *)mTouchActionQueue.mData[i];
            if(aAction->mTouchState == TOUCH_STATE_MOVING) {
                if(aAction->mData == pData) {
                    aAction->mX = pX;
                    aAction->mY = pY;
                    return;
                }
            }
        }
    }
    
    aAction = 0;

    if (mTouchActionRecycle.mCount > 0) {
        aAction = (FTouchAction *)(mTouchActionRecycle.mData[mTouchActionRecycle.mCount - 1]);
        mTouchActionRecycle.mCount --;
    }
    
    if(aAction == 0) {
        aAction = new FTouchAction();
    }

    aAction->mX = pX;
    aAction->mY = pY;
    aAction->mData = pData;
    aAction->mTouchState = pTouchState;
    mTouchActionQueue.Add(aAction);
}

void FTouchManager::EnqueueMouseAction(float pX, float pY, int pType, int pButton, int pDirection) {
    FMouseAction *aAction = 0;
    if (pType == MOUSE_MOVE) {
        for(int i=mTouchActionQueue.mCount - 1;i>=0;i--) {
            aAction = (FMouseAction *)mTouchActionQueue.mData[i];
            if(aAction->mType == MOUSE_MOVE) {
                aAction->mX = pX;
                aAction->mY = pY;
                return;
            }
        }
    }

    aAction = 0;

    if (mMouseActionRecycle.mCount > 0) {
        aAction = (FMouseAction *)(mMouseActionRecycle.mData[mMouseActionRecycle.mCount - 1]);
        mMouseActionRecycle.mCount --;
    }

    if(aAction == 0) {
        aAction = new FMouseAction();
    }

    aAction->mX = pX;
    aAction->mY = pY;
    aAction->mButton = pButton;
    aAction->mType = pType;
    aAction->mDirection = pDirection;
    mMouseActionQueue.Add(aAction);
}

void FTouchManager::Active() {
    FlushTouches();
}

void FTouchManager::Inactive() {
    FlushTouches();
}

void FTouchManager::FinishedTouch(FTouch *pTouch) {
    if (pTouch) {
        int aSlot = -1;
        for (int i=0;i<mTouchCount;i++) {
            if (mTouch[i] == pTouch) {
                aSlot = i;
            }
        }
        if (aSlot >= 0) {
            FTouch *aTouch = 0;
            for(int i=aSlot+1;i<mTouchCount;i++) {
                aTouch = mTouch[i];
                mTouch[i - 1] = aTouch;
            }
            mTouchCount--;
        }
        
        if (mTouchQueueCount < TOUCH_MANAGER_MAX_QUEUE_TOUCHES) {
            mTouchQueue[mTouchQueueCount] = pTouch;
            mTouchQueueCount++;
        }
    }
}

FTouch *FTouchManager::GetTouchDown(void *pData) {
    FTouch *aTouch = 0;
    if(mTouchCount < (TOUCH_MANAGER_MAX_TOUCHES - 1)) {
        if(mTouchQueueCount > 0) {
            aTouch = mTouchQueue[mTouchQueueCount - 1];
            mTouchQueueCount--;
        }
        if(aTouch) {
            mTouch[mTouchCount] = aTouch;
            mTouchCount++;
        }
    }
    return aTouch;
}

FTouch *FTouchManager::GetTouch(void *pData) {
    FTouch *aTouch = 0;
    for(int i=0;i<mTouchCount;i++) {
        if(mTouch[i]->mData == pData) {
            aTouch = mTouch[i];
        }
    }
    return aTouch;
}

void FTouchManager::BaseTouchDown(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_DOWN, pData);
    //EnqueueMouseDown(pX, pY, -1);
    EnqueueMouseAction(pX, pY, MOUSE_DOWN, -1, 0);
}

void FTouchManager::BaseTouchMove(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_MOVING, pData);
    //EnqueueMouseMove(pX, pY);
    EnqueueMouseAction(pX, pY, MOUSE_MOVE, 0, 0);

}

void FTouchManager::BaseTouchUp(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_RELEASED, pData);
    //EnqueueMouseUp(pX, pY, -1);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);

}

void FTouchManager::BaseTouchCanceled(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_CANCELED, pData);
    //EnqueueMouseUp(pX, pY, -1);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);

}

void FTouchManager::BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_DOWN, pIndex);
    //EnqueueMouseDown(pX, pY, -1);
    EnqueueMouseAction(pX, pY, MOUSE_DOWN, -1, 0);

}

void FTouchManager::BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_MOVING, pIndex);
    //EnqueueMouseMove(pX, pY);
    EnqueueMouseAction(pX, pY, MOUSE_MOVE, 0, 0);

}

void FTouchManager::BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_RELEASED, pIndex);
    //EnqueueMouseUp(pX, pY, -1);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);

}

void FTouchManager::BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, pIndex);
    //EnqueueMouseUp(pX, pY, -1);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);

}

void FTouchManager::BaseMouseDown(float pX, float pY, int pButton) {
	if (pButton == 0) {
		if(mMouseLeftDown)EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, 0);
		mMouseLeftDown = true;
	}
	if (pButton == 1) {
		if(mMouseMiddleDown)EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, 1);
		mMouseMiddleDown = true;
	}
	if (pButton == 2) {
		if(mMouseRightDown)EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, 2);
		mMouseRightDown = true;
	}

	EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_DOWN, pButton);
    EnqueueMouseAction(pX, pY, MOUSE_DOWN, pButton, 0);
}

void FTouchManager::BaseMouseMove(float pX, float pY)
{
	if (mMouseLeftDown) {
		EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_MOVING, 0);
	}
    EnqueueMouseAction(pX, pY, MOUSE_MOVE, 0, 0);
}

void FTouchManager::BaseMouseWheel(int pDir) {
    EnqueueMouseAction(0.0f, 0.0f, MOUSE_WHEEL_SCROLL, 0, pDir);
}

void FTouchManager::BaseMouseUp(float pX, float pY, int pButton)
{
	if(pButton == 0)mMouseLeftDown = false;
	if(pButton == 1)mMouseMiddleDown = false;
	if(pButton == 2)mMouseRightDown = false;
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, pButton);
    //EnqueueMouseUp(pX, pY, pButton);
    EnqueueMouseAction(pX, pY, MOUSE_UP, pButton, 0);

}

void FTouchManager::FlushTouches() {
    gAppBase->ProcessTouchFlush();
    mTouchCount = 0;
}

void FTouchManager::EnqueueKeyDown(int pKey) {
	if (mKeyQueueLength < 256) {
		mKeyQueue[mKeyQueueLength] = pKey;
		mKeyActionType[mKeyQueueLength] = 1;
		mKeyQueueLength++;
	}
}

void FTouchManager::EnqueueKeyUp(int pKey) {
	if (mKeyQueueLength < 256) {
		mKeyQueue[mKeyQueueLength] = pKey;
		mKeyActionType[mKeyQueueLength] = -1;
		mKeyQueueLength++;
	}
}



