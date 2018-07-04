//
//  ActionPriorityQueueAction.h
//  2015 Jeep Cherokee Middle East Complete
//
//  Created by Nick Raptis on 10/13/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#ifndef ___015_Jeep_Cherokee_Middle_East_Complete__ActionPriorityQueueAction__
#define ___015_Jeep_Cherokee_Middle_East_Complete__ActionPriorityQueueAction__

#include "FString.h"

#define APQ_ACTION_WALK 1
#define APQ_ACTION_SPLASH 2
#define APQ_ACTION_SWIM 3
#define APQ_ACTION_DIVE 4
#define APQ_ACTION_SURFACE 5
#define APQ_ACTION_DRY_OFF 6

#define APQ_STATE_WALK 1
#define APQ_STATE_SWIM 3
#define APQ_STATE_DIVE 4
#define APQ_STATE_SURFACE 5
#define APQ_STATE_DRY_OFF 6

class ActionPriorityQueueAction
{
public:
    
    ActionPriorityQueueAction(int pID);
    virtual ~ActionPriorityQueueAction();
    
    FString                             mName;
    
    int                                 mID;
    
    bool                                mMultipleEnqueuesAllowed;
    
    int                                 mPriority;
    
    bool                                mHasState;
    
    void                                TriggerStateAdd(int pActionID);
    
    int                                 *mTriggerState;
    int                                 mTriggerStateCount;
    int                                 mTriggerStateSize;
    
    void                                ConcurrentAddAllowed(int pActionID);
    
    int                                 *mAllowedConcurrent;
    int                                 mAllowedConcurrentCount;
    int                                 mAllowedConcurrentSize;
    
};

#endif /* defined(___015_Jeep_Cherokee_Middle_East_Complete__ActionPriorityQueueAction__) */
