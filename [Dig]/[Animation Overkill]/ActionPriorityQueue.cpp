//
//  ActionPriorityQueue.cpp
//  2015 Jeep Cherokee Middle East Complete
//
//  Created by Nick Raptis on 10/12/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include "core_includes.h"

#include "ActionPriorityQueue.h"

ActionPriorityQueue::ActionPriorityQueue()
{
    mActiveCount = 0;
    mQueueLength = 0;
    
    for(int i=0;i<APQ_MAX_STATE_COUNT;i++)
    {
        mStateActive[i] = false;
    }
    
    for(int i=0;i<APQ_MAX_ACTION_COUNT;i++)
    {
        mAction[i] = 0;
        mActionOnCount[i] = 0;
        mActionEnqueuedCount[i] = 0;
    }
    
    for(int i=0;i<APQ_MAX_QUEUE_LENGTH;i++)
    {
        mQueueAction[i] = 0;
        mQueuePriority[i] = 0;
    }    
}

ActionPriorityQueue::~ActionPriorityQueue()
{
    
}

/*



void ActionPriorityQueue::ActionStart(int pActionID)
{
    if((pActionID >= 0) && (pActionID < APQ_MAX_ACTION_COUNT))
    {
        mActionOnCount[pActionID]++;
    }
}

void ActionPriorityQueue::ActionStop(int pActionID)
{
    if((pActionID >= 0) && (pActionID < APQ_MAX_ACTION_COUNT))
    {
        mActionOnCount[pActionID] = 0;
    }
}

bool ActionPriorityQueue::ActionIsOn(int pActionID)
{
    bool aReturn = false;
    
    if((pActionID >= 0) && (pActionID < APQ_MAX_ACTION_COUNT))
    {
        if(mActionOnCount[pActionID] > 0)
        {
            aReturn = true;
        }
    }
    
    return aReturn;
}

bool ActionPriorityQueue::ActionIsEnqueued(int pActionID)
{
    bool aReturn = false;
    
    if((pActionID >= 0) && (pActionID < APQ_MAX_ACTION_COUNT))
    {
        if(mActionEnqueuedCount[pActionID] > 0)
        {
            aReturn = true;
        }
    }
    
    return aReturn;
}

*/


void ActionPriorityQueue::SetState(int pStateID, bool pOn)
{
    
    if((pStateID >= 0) && (pStateID < APQ_MAX_STATE_COUNT))
    {
        if(pOn)
        {
            if(mStateActive[pStateID] == false)
            {
                mActiveCount++;
                mStateActive[pStateID] = true;
            }
        }
        else
        {
            if(mStateActive[pStateID] == true)
            {
                mActiveCount--;
                mStateActive[pStateID] = false;
            }
        }
    }
    
    if(pOn)
    {
        //printf("State On(%s) = ON [Total = %d]\n\n", GetActionName(pStateID).c(), mActiveCount);
        
    }
    else
    {
        //printf("State Off(%s) = ON (Total = %d)\n", GetActionName(pStateID).c(), mActiveCount);
        //pOn
        
    }
}

void ActionPriorityQueue::SetActive(int pStateID)
{
    SetState(pStateID, true);
}


void ActionPriorityQueue::SetInactive(int pStateID)
{
    SetState(pStateID, false);
}

bool ActionPriorityQueue::IsActive(int pStateID)
{
    bool aReturn = false;
    
    if((pStateID >= 0) && (pStateID < APQ_MAX_STATE_COUNT))
    {
        if(mStateActive[pStateID] == true)
        {
            aReturn = true;
        }
    }
    
    //State(pStateID, false);
    return aReturn;
}



ActionPriorityQueueAction *ActionPriorityQueue::GetActon(int pActionID)
{
    ActionPriorityQueueAction *aAction = 0;
    
    if((pActionID >= 0) && (pActionID < APQ_MAX_ACTION_COUNT))
    {
        aAction = mAction[pActionID];
        
        if(aAction == 0)
        {
            aAction = new ActionPriorityQueueAction(pActionID);
            
            aAction->mName = GetActionName(pActionID);
            
            mAction[pActionID] = aAction;
        }
    }
    
    return aAction;
}

void ActionPriorityQueue::ActionEnqueue(int pActionID)
{
    //Log("Enqueue[%s]\n", GetActionName(pActionID).c());
    bool aDidEnqueue = false;
    
    ActionPriorityQueueAction *aAction = GetActon(pActionID);
    
    if(aAction)
    {
        int aPriority = aAction->mPriority;
        
        if(mQueueLength < APQ_MAX_QUEUE_LENGTH)
        {
            int aSearchIndex = 0;
            
            bool aContinue = true;
            bool aActionExists = false;
            bool aFoundEqualPriority = false;
            
            while((aSearchIndex < mQueueLength) && (aContinue == true))
            {
                if(mQueuePriority[aSearchIndex] >= aPriority)
                {
                    aContinue = false;
                    
                    if(mQueuePriority[aSearchIndex] == aPriority)
                    {
                        aFoundEqualPriority = true;
                    }
                    
                    if(mQueueAction[aSearchIndex] == pActionID)
                    {
                        aActionExists = true;
                    }
                }
                else
                {
                    aSearchIndex++;
                }
            }
            
            int aProbeIndex = aSearchIndex + 1;
            
            aContinue = true;
            
            while((aProbeIndex < mQueueLength) && (aContinue == true))
            {
                if(mQueuePriority[aProbeIndex] == aPriority)
                {
                    if(mQueueAction[aProbeIndex] == pActionID)aActionExists = true;
                    aSearchIndex = aProbeIndex;
                    aProbeIndex++;
                }
                else
                {
                    aContinue = false;
                }
            }
            
            bool aCanEnqueue = true;
            
            if(aActionExists)
            {
                //printf("Action[%s] Already Exists! (%d, %d)\n", GetActionName(pActionID).c(), aSearchIndex, aProbeIndex);
                
                if(aAction->mMultipleEnqueuesAllowed == false)
                {
                    aCanEnqueue = false;
                }
                
            }
            else
            {
                //printf("Action[%s] Does NOT Exists! (%d, %d)\n", GetActionName(pActionID).c(), aSearchIndex, aProbeIndex);
                
            }
            
            
            
            
            if(aCanEnqueue)
            {
                aDidEnqueue = true;
            
            if(aFoundEqualPriority)
            {
                aSearchIndex++;
            }
            
            
            for(int i=mQueueLength;i>aSearchIndex;i--)
            {
                mQueueAction[i] = mQueueAction[i - 1];
                mQueuePriority[i] = mQueuePriority[i - 1];
            }
            
            mQueueAction[aSearchIndex] = pActionID;
            mQueuePriority[aSearchIndex] = aPriority;
                
                mActionEnqueuedCount[pActionID]++;
            
            mQueueLength++;
                
            }
        }
        else
        {
            
        }
    }
    
    if(aDidEnqueue)
    {
        //printf("A Enqueue[%s][P=%d] (%d)\n", GetActionName(pActionID).c(), aAction->mPriority, mQueueLength);
    }
    else
    {
        //printf("A CAN'T Enqueue[%s] (%d)\n", GetActionName(pActionID).c(), mQueueLength);
    }
    
}

int ActionPriorityQueue::DequeueAction()
{
    int aActionIndex = -1;
    
    int aDequeueIndex = -1;
    
    //int mActiveCount;
    
    
    //for(int aIndex=0;(aIndex<mQueueLength) && (aActionIndex == -1);aIndex++)
    for(int aIndex=mQueueLength-1;(aIndex>=0) && (aActionIndex == -1);aIndex--)
        
    {
        ActionPriorityQueueAction *aAction = GetActon(mQueueAction[aIndex]);
        
        if(aAction != 0)
        {
            
            if(mActiveCount == 0)
            {
                aActionIndex = aAction->mID;
                aDequeueIndex = aIndex;
                
            }
        }
    }
    
    
    if(aDequeueIndex != -1)
    {
        for(int i=aDequeueIndex + 1;i<mQueueLength;i++)
        {
            mQueueAction[i - 1] = mQueueAction[i];
            mQueuePriority[i - 1] = mQueuePriority[i];
            
        }
        
        
        if((aActionIndex >= 0) && (aActionIndex < APQ_MAX_ACTION_COUNT))
        {
            mActionEnqueuedCount[aActionIndex]--;
            
            if(mActionEnqueuedCount[aActionIndex] <= 0)
            {
                //mEnqueuedActionCount--;
                
            }
        }
        else
        {
            Log("WAT?\n");
        }
        
        //
        
        //
        
        mQueueLength--;
    }
    
    
    return aActionIndex;
}

void ActionPriorityQueue::ActionSetTriggerState(int pActionID, int pStateID)
{
    ActionPriorityQueueAction *aAction = GetActon(pActionID);
    
    if(aAction)
    {
        aAction->TriggerStateAdd(pStateID);
    }
}

void ActionPriorityQueue::ActionSetPriority(int pActionID, int pPriority)
{
    ActionPriorityQueueAction *aAction = GetActon(pActionID);
    if(aAction)
    {
        aAction->mPriority = pPriority;
    }
}

void ActionPriorityQueue::ActionSetHasState(int pActionID)
{
    ActionPriorityQueueAction *aAction = GetActon(pActionID);
    
    if(aAction)
    {
        aAction->mHasState = true;
    }
}

bool ActionPriorityQueue::ActionHasState(int pActionID)
{
    bool aReturn = false;
    
    ActionPriorityQueueAction *aAction = GetActon(pActionID);
    if(aAction)
    {
        aReturn = aAction->mHasState;
    }
    
    //printf("ActionHasState(%s) = [%s]\n", GetActionName(pActionID).c(), (char *)(aReturn ? "YES" : "NO"));
    
    return aReturn;
}


void ActionPriorityQueue::Print()
{
    FString aNameString = "";
    
    for(int i=0;i<mQueueLength;i++)
    {
        aNameString += GetActionName(mQueueAction[i]).c();
        aNameString += FString(" (") + FString(mQueuePriority[i]) + FString(")");
        
        //                       %d)", mQueuePriority[i]).c();
        
        if(i < (mQueueLength - 1))aNameString += ", ";
    }
    
    printf("{{%s}}\n", aNameString.c());
    
}

FString ActionPriorityQueue::GetActionName(int pActionID)
{
    FString aReturn = "ACTION_NULL";
    
    if(pActionID == BOARD_ACTION_CHECK_BOARD)aReturn = "ACTION_CHECK_BOARD";
    else if(pActionID == BOARD_ACTION_DESTROYING)aReturn = "ACTION_DESTROYING";
    else if(pActionID == BOARD_ACTION_MATCHING)aReturn = "ACTION_MATCHING";
    else if(pActionID == BOARD_ACTION_COMBOING)aReturn = "ACTION_COMBOING";
    else if(pActionID == BOARD_ACTION_DRAGGING)aReturn = "DRAG";
    else if(pActionID == BOARD_ACTION_SHIFTING)aReturn = "SHIFT";
    else if(pActionID == BOARD_ACTION_TOPPLING)aReturn = "ACTION_TOPPLING";
    else if(pActionID == BOARD_ACTION_SETTLED)aReturn = "SETTLING";
    else if(pActionID == BOARD_ACTION_SETTLE_PENDING)aReturn = "SETTLE_PENDING";
    else if(pActionID == BOARD_ACTION_FILLLING_HOLES)aReturn = "FILL_HOLES";
    else if(pActionID == BOARD_ACTION_SHIFT_COMPLETE_TRIGGER)aReturn = "SHIFT_COMPLETE";
    else if(pActionID == BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER)aReturn = "ACTION_TOPPLE_COMPLETE_TRIGGER";
    else if(pActionID == BOARD_ACTION_MATCHING_COMPLETE_TRIGGER)aReturn = "MATCHING_COMPLETE";
    else if(pActionID == BOARD_ACTION_TUTORIAL)aReturn = "TUTORIAL";
    else if(pActionID == BOARD_ACTION_LEVEL_UP)aReturn = "LEVEL_UP";
    else if(pActionID == BOARD_ACTION_GAME_OVER)aReturn = "GAME_OVER";
    else if(pActionID == BOARD_ACTION_INITIALIZING)aReturn = "INIT";
    
    else if(pActionID == BOARD_ACTION_INTERFACE_PROC_1)aReturn = "INTERFACE_PROC_1";
    else if(pActionID == BOARD_ACTION_INTERFACE_PROC_2)aReturn = "INTERFACE_PROC_2";
    else if(pActionID == BOARD_ACTION_INTERFACE_PROC_3)aReturn = "INTERFACE_PROC_3";
    
    if(aReturn.mLength <= 0)aReturn = "NULL";
    return aReturn;
    
    /*
    FString aReturn = "ACTION_NULL";
    
    if(pActionID == APQ_ACTION_WALK)aReturn = "ACTION_WALK";
    if(pActionID == APQ_ACTION_SPLASH)aReturn = "ACTION_SPLASH";
    if(pActionID == APQ_ACTION_SWIM)aReturn = "ACTION_SWIM";
    if(pActionID == APQ_ACTION_DIVE)aReturn = "ACTION_DIVE";
    if(pActionID == APQ_ACTION_SURFACE)aReturn = "ACTION_SURFACE";
    if(pActionID == APQ_ACTION_DRY_OFF)aReturn = "ACTION_DRY_OFF";
    
    return aReturn;
    */
}

FString ActionPriorityQueue::GetSateName(int pStateID)
{
    FString aReturn = "STATE_NULL";
    
    if(pStateID == APQ_STATE_WALK)aReturn = "STATE_WALK";
    if(pStateID == APQ_STATE_SWIM)aReturn = "STATE_SWIM";
    if(pStateID == APQ_STATE_DIVE)aReturn = "STATE_DIVE";
    if(pStateID == APQ_STATE_SURFACE)aReturn = "STATE_SURFACE";
    if(pStateID == APQ_STATE_DRY_OFF)aReturn = "STATE_DRY_OFF";
    
    return aReturn;
}


