//
//  ActionPriorityQueueAction.cpp
//  2015 Jeep Cherokee Middle East Complete
//
//  Created by Nick Raptis on 10/13/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include "ActionPriorityQueueAction.h"

ActionPriorityQueueAction::ActionPriorityQueueAction(int pID)
{
    mID = pID;
    
    mTriggerState = 0;
    
    mMultipleEnqueuesAllowed = false;
    
    mPriority = 0;
    
    mHasState = false;
    
    mTriggerStateCount = 0;
    mTriggerStateSize = 0;
}

ActionPriorityQueueAction::~ActionPriorityQueueAction()
{
    
}

void ActionPriorityQueueAction::TriggerStateAdd(int pActionID)
{
    if(mTriggerStateCount <= mTriggerStateSize)
    {
        mTriggerStateSize = (mTriggerStateCount + mTriggerStateCount / 2 + 1);
        
        int *aTriggerState = new int[mTriggerStateSize];
        
        for(int i=0;i<mTriggerStateCount;i++)
        {
            aTriggerState[i] = mTriggerState[i];
        }
        
        delete [] mTriggerState;
        
        mTriggerState = aTriggerState;
    }
    
    mTriggerState[mTriggerStateCount] = pActionID;
    mTriggerStateCount++;
}

void ActionPriorityQueueAction::ConcurrentAddAllowed(int pActionID)
{
    if(mAllowedConcurrentCount <= mAllowedConcurrentSize)
    {
        mAllowedConcurrentSize = (mAllowedConcurrentCount + mAllowedConcurrentCount / 2 + 1);
        
        int *aAllowedConcurrent = new int[mAllowedConcurrentSize];
        
        for(int i=0;i<mAllowedConcurrentCount;i++)
        {
            aAllowedConcurrent[i] = mAllowedConcurrent[i];
        }
    }
    
    mAllowedConcurrent[mAllowedConcurrentCount] = pActionID;
    mAllowedConcurrentCount++;
    
}


