
//
//   Here's the rules. It's simple, watch.
//

// Simple Rule 1.) Each state had an action associated with it.
// Simple Rule 2.) Actions gets crunched LIFO (last in first out) wise based on priority.
// Simple Rule 3.) Wild Card priorities are to be supported. A wild card priority is tripped from an associative rule.

//
//   And then to make it do what we need to do, simplicity needs to take a nosedive and make a little room for conditional rules.
//


// Associative Rule 1.)



#ifndef ___015_Jeep_Cherokee_Middle_East_Complete__ActionPriorityQueue__
#define ___015_Jeep_Cherokee_Middle_East_Complete__ActionPriorityQueue__

#include "ActionPriorityQueueAction.h"
#include "FString.h"

#define APQ_MAX_ACTION_COUNT 256
#define APQ_MAX_STATE_COUNT 256

#define APQ_MAX_QUEUE_LENGTH 2048




#define BOARD_ACTION_NULL -1

#define BOARD_ACTION_SETTLED 9
#define BOARD_ACTION_CHECK_BOARD 10

#define BOARD_ACTION_DESTROYING 14


#define BOARD_ACTION_INTERFACE_PROC_1 16
#define BOARD_ACTION_INTERFACE_PROC_1_WAITING 17


#define BOARD_ACTION_INTERFACE_PROC_2 18
#define BOARD_ACTION_INTERFACE_PROC_2_WAITING 19

#define BOARD_ACTION_INTERFACE_PROC_3 20
#define BOARD_ACTION_INTERFACE_PROC_3_WAITING 21



#define BOARD_ACTION_MATCHING 25
#define BOARD_ACTION_MATCHING_COMPLETE_TRIGGER 26
#define BOARD_ACTION_COMBOING 28



#define BOARD_ACTION_DRAGGING 32


#define BOARD_ACTION_SHIFTING 38
#define BOARD_ACTION_SHIFT_COMPLETE_TRIGGER 39

#define BOARD_ACTION_TOPPLING 42
#define BOARD_ACTION_TOPPLE_COMPLETE_TRIGGER 43


#define BOARD_ACTION_SPECIAL_COMBO 46
#define BOARD_ACTION_SPECIAL_COMBO_COMPLETE_TRIGGER 47


#define BOARD_ACTION_FILLLING_HOLES 50

#define BOARD_ACTION_SETTLE_PENDING 55


#define BOARD_ACTION_TUTORIAL 80
#define BOARD_ACTION_LEVEL_UP 81
#define BOARD_ACTION_GAME_OVER 82
#define BOARD_ACTION_INITIALIZING 83


//We need a way to make actions automatically start states as they are dequeued.

class ActionPriorityQueue
{
public:
    
    ActionPriorityQueue();
    virtual ~ActionPriorityQueue();
    
    //Important distinction between a state and an action is the paradigm we start with.
    void                                SetState(int pStateID, bool pOn);
    
    void                                SetActive(int pStateID);
    void                                SetInactive(int pStateID);
    
    bool                                mStateActive[APQ_MAX_STATE_COUNT];
    
    
    bool                                IsActive(int pStateID);
    
    
    
    
    //We'll assume ass enqueued actions are independent, basically already enqueued actions aren't re-enqueued.
    
    ActionPriorityQueueAction           *GetActon(int pActionID);
    
    void                                ActionEnqueue(int pActionID);
    
    //void                                ActionStart(int pActionID);
    //void                                ActionStop(int pActionID);
    
    //bool                                ActionIsOn(int pActionID);
    //bool                                ActionIsEnqueued(int pActionID);
    
    
    
    //printf("\t\tAction[%d] = (%s)\n", aIndex, gQueue.GetActionName(aAction).c());
    
    //int                                 mEnqueuedActionCount;
    int                                 mActiveCount;
    
    //int                                 mEnqueuedActionCount;
    //int                                 mOnActionCount;
    
    //int                                 NextActionDequeue();
    //bool                                NextActionReady();
    
    void                                ActionSetTriggerState(int pActionID, int pStateID);
    void                                ActionSetPriority(int pActionID, int pPriority);
    
    ActionPriorityQueueAction           *mAction[APQ_MAX_ACTION_COUNT];
    
    int                                 mActionOnCount[APQ_MAX_ACTION_COUNT];
    int                                 mActionEnqueuedCount[APQ_MAX_ACTION_COUNT];
    
    void                                ActionSetHasState(int pActionID);
    bool                                ActionHasState(int pActionID);
    
    int                                 mQueueAction[APQ_MAX_QUEUE_LENGTH];
    int                                 mQueuePriority[APQ_MAX_QUEUE_LENGTH];
    
    int                                 mQueueLength;
    
    //bool                                HasAction();
    int                                 DequeueAction();
    
    bool                                CanDequeueAction(ActionPriorityQueueAction *pAction);
    
    
    void                                Print();
    
    virtual FString                     GetActionName(int pActionID);
    virtual FString                     GetSateName(int pStateID);
    
    
    
//    
//    //And acti
//    
//    SetMutualAllowance(arabic, english);
//    SetMutualAllowance(arabic, chinese);
//    
//    //stuff happens...
//    
//    //
//    EnqueuState(arabic);
//    
    
    
    
    
    
};

#endif /* defined(___015_Jeep_Cherokee_Middle_East_Complete__ActionPriorityQueue__) */








