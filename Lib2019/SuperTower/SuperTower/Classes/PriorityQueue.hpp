//
//  PriorityQueue.hpp
//  Apex
//
//  Created by Nicholas Raptis on 8/8/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

#include "PriorityQueue.hpp"

class PQNode
{
public:
    PQNode(void *item, int priority)
    {
        mItem=item;
        mPriority=priority;
        mHeapLeft=0;
        mHeapRight=0;
    }
    ~PQNode()
    {
        //delete mItem; //Are we storing these pointers elsewhere??
        if(mHeapRight)delete mHeapRight;
        if(mHeapLeft)delete mHeapLeft;
    }
    void    *mItem;
    int        mPriority;
    PQNode    *mHeapRight;
    PQNode    *mHeapLeft;
    PQNode    *mHeapParent;
};

class PriorityQueue
{
public:
    PQNode    *mHeapRoot;
    PQNode    *mHeapLast;
    int        mCount;
    PriorityQueue(void)
    {
        mCount=0;
        mHeapRoot=0;
    }
    
    ~PriorityQueue(void)
    {
        //Gets rid of all nodes!
        delete mHeapRoot;
    }
    
    //Hmm... I wonder what this does?!
    void Clear()
    {
        delete mHeapRoot;
        mHeapRoot=0;
        mHeapLast=0;
        mCount=0;
    }
    
    //Add an item to the priority Queue!
    void Enqueue(void *item, int priority=0)
    {
        PQNode *p = new PQNode(item, priority);
        if (mHeapRoot == 0) {
            mHeapRoot = p;
        } else {
            //Find Next Parent To Add.
            //TODO: Make this less complicated ifpossible.
            PQNode *aPick = mHeapLast;
            //Go Up Until We're At A Right Node
            while ((aPick != mHeapRoot) && (aPick->mHeapParent->mHeapLeft != aPick)) {
                aPick = aPick->mHeapParent;
            }
            if (aPick != mHeapRoot) {
                if (aPick->mHeapParent->mHeapRight == 0) {
                    aPick = aPick->mHeapParent;
                } else {
                    aPick = aPick->mHeapParent->mHeapRight;
                    while (aPick->mHeapLeft != 0) {
                        aPick = aPick->mHeapLeft;
                    }
                }
            } else {
                while (aPick->mHeapLeft != 0) {
                    aPick = aPick->mHeapLeft;
                }
            }
            
            //We've got the parent of the node we're adding,
            //so add the node!
            if (aPick->mHeapLeft == 0) {
                aPick->mHeapLeft=p;
            } else {
                aPick->mHeapRight=p;
            }
            
            p->mHeapParent = aPick;
            
            //Reheapify Upward!
            aPick = p;
            void *aTempItem;
            int aTempP;
            while (aPick != mHeapRoot && aPick->mPriority < aPick->mHeapParent->mPriority) {
                aTempItem = aPick->mItem;
                aTempP = aPick->mPriority;
                aPick->mItem = aPick->mHeapParent->mItem;
                aPick->mPriority = aPick->mHeapParent->mPriority;
                aPick->mHeapParent->mItem = aTempItem;
                aPick->mHeapParent->mPriority = aTempP;
                aPick=aPick->mHeapParent;
            }
        }
        //Last node added!
        mHeapLast = p;
        mCount++;
    }
    
    //Look at top item without popping it.
    void * Peek()
    {
        if(mCount <=0)
        {
            return 0;
        }
        return mHeapRoot->mItem;
    }
    
    //Return highest priority item after dequeueing it.
    void * Dequeue()
    {
        if(mCount <=0)
        {
            return 0;
        }
        void *aReturn = mHeapRoot->mItem;
        
        if(mCount == 1)
        {
            delete mHeapRoot;
            mCount=0;
            mHeapRoot=0;
            mHeapLast=0;
            return aReturn;
        }
        
        //Find Our New Last Node!
        PQNode *aLast = mHeapLast;
        while ((aLast != mHeapRoot) && (aLast->mHeapParent->mHeapLeft == aLast)) {
            aLast = aLast->mHeapParent;
        }
        
        if (aLast != mHeapRoot) {
            aLast=aLast->mHeapParent->mHeapLeft;
        }
        while (aLast->mHeapRight != 0) {
            aLast=aLast->mHeapRight;
        }
        
        
        //Remove Pointer To Last Item!
        if(mHeapLast->mHeapParent->mHeapLeft == mHeapLast) {
            mHeapLast->mHeapParent->mHeapLeft = NULL;
        } else {
            mHeapLast->mHeapParent->mHeapRight = 0;
        }
        
        //Swap Last And Root
        mHeapRoot->mItem = mHeapLast->mItem;
        mHeapRoot->mPriority = mHeapLast->mPriority;
        
        delete mHeapLast;//Free up memory.
        //Remember, the pointer may still be there!
        
        mHeapLast = aLast;
        
        //Reheapify Down
        //Current node
        PQNode *aNode = mHeapRoot;
        PQNode *aLeft = aNode->mHeapLeft;
        PQNode *aRight = aNode->mHeapRight;
        //Next node. Is it gonna be null?
        PQNode *aNext;
        
        //Which direction do we probe in?
        if((aLeft == 0) && (aRight == 0))aNext = 0;
        else if(aLeft == 0)aNext = aRight;
        else if(aRight == 0)aNext = aLeft;
        else if(aLeft->mPriority < aRight->mPriority)aNext = aLeft;
        else aNext = aRight;
        
        //Moved out of loop for speed!
        //The compiler will do this anyway,
        //but what the hell!
        void *aTempItem;
        int aTempP;
        
        //While we can trickle down...
        while ((aNext != 0) && (aNext->mPriority < aNode->mPriority))
        {
            //Swap current node and next node!
            aTempItem = aNode->mItem;
            aTempP=aNode->mPriority;
            aNode->mItem=aNext->mItem;
            aNode->mPriority=aNext->mPriority;
            aNext->mItem=aTempItem;
            aNext->mPriority=aTempP;
            
            //Advance Node
            aNode = aNext;
            aLeft = aNode->mHeapLeft;
            aRight = aNode->mHeapRight;
            
            //Which direction do we probe in next?
            if ((aLeft == 0) && (aRight == 0)) { aNext = 0; }
            else if(aLeft == 0)aNext = aRight;
            else if(aRight == 0)aNext = aLeft;
            else if(aLeft->mPriority < aRight->mPriority)aNext = aLeft;
            else aNext = aRight;
        }
        //Phew!
        
        mCount--;
        return aReturn;
    }
    
    bool Empty()
    {
        return mCount <= 0;
    }
};



#endif /* PriorityQueue_hpp */
