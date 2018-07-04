//
//  BoardGeneric.h
//  Bone
//
//  Created by Nick Raptis on 8/6/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef BOARD_GENERIC_H
#define BOARD_GENERIC_H

//Alrighty, so the problem of over-crowding of one class can be solved by genericising the base board class. Theoretically
//

#include "FView.h"
#include "BoardGenericTile.h"

#include "ActionPriorityQueue.h"

//#include "BoardGenericAction.h"
//#include "BoardGenericActionQueue.h"
#include "BoardGenericActionLayer.h"

#include "BoardGenericLayer.h"
#include "BoardGenericMatch.h"

#include "FParticle.h"
#include "FSprite.h"
#include "FSpriteSequence.h"





class BoardGeneric : public FView
{
public:
    
    BoardGeneric();
    virtual ~BoardGeneric();
    
    void                                    Update();
    void                                    Draw();
    
    float                                   mTileWidth;
    float                                   mTileHeight;
    
    
    int                                     mMatchTypeCount;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    
    int                                     GetTouchGridX(float pX);
    int                                     GetTouchGridY(float pY);
    
    float                                   GetTileCenterX(int pGridX);
    float                                   GetTileCenterY(int pGridY);
    
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    ////
    ////     Grid freezing, locking, priority action allowance, etc.
    ////
    
    virtual FString                         GetActionName(int pActionID);
    
    
    
    void                                    ActionEnqueue(int pActionID);
    
    void                                    SetActive(int pStateID);
    void                                    SetInactive(int pStateID);
    
    
    //Basically, we decide which types of actions we allow in which cases.
    //We add and remove "locks" of certain types to the board.
    //Following this paradigm, the board can always be in a predictable state.
    
    //void                                    SetupLockCreate(int pLockID, const char *pLockName, bool pStacking=false);
    
    virtual bool                            AllowClick();
    virtual bool                            AllowDestroy();
    virtual bool                            AllowShift();
    
    //There's an important difference between when an action "starts" and when one becomes "enqueued"..
    //
    
    
    //void                                    ActionEnqueue(int pActionID);
    
    //void                                    ActionStart(int pActionID);
    //void                                    ActionStop(int pActionID);
    
    //void                                    ActionCheck(){ActionStart(BOARD_ACTION_CHECK_BOARD);}
    //virtual void                            ActionExecute(int pActionIndex);
    virtual void                            ActionExecute(int pActionIndex);
    
    //bool                                    ActionIsActive(int pActionID);
    
    //bool                                    ActionIsEnqueued(int pActionID);
    
    void                                    ProcessActionQueue();
    //BoardGenericActionQueue                 mActionQueue;
    
    ActionPriorityQueue                     mActionQueue;
    
    ////
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////

    
    FList                                   mLayerList;
    virtual void                            AddLayer(BoardGenericLayer *pLayer);
    
    
    
    FList                                   mTilesDeleted;
    FList                                   mTilesDeletedThisUpdate;
    
    virtual void                            PrintMatchContent(BoardGenericMatch *pMatch);
    
    //Some default layers that the boards will all have.. which, also, we need for here.
    BoardGenericActionLayer                 mLayerMatchType;
    BoardGenericActionLayer                 mLayerMatchCheck;
    BoardGenericActionLayer                 mLayerMatchFlagged;
    BoardGenericActionLayer                 mLayerMatchCount;
    
    
    BoardGenericActionLayer                 mLayerMatchStackX;
    BoardGenericActionLayer                 mLayerMatchStackY;
    
    
    void                                    MatchComputeAll();
    void                                    MatchComputeAll(int pGridStartY, int pGridEndY);
    void                                    MatchComputeAll(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY);
    
    void                                    MatchListSort();
    
    //BoardGenericMatch                       mMatchSearch;
    
    BoardGenericMatch                       **mMatch;
    int                                     mMatchCount;
    int                                     mMatchSize;
    
    bool                                    mMatchAllowDiagonal;
    
    
    //void                                    mMatchListCount;
    //void                                    mMatchListSize;
    
    
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    ////
    ////     Grid creation, resizing, etc etc.
    ////
    
    BoardGenericTile                        ***mGridGameTile;
    
    //For non-rectangular, we can actually stagger blanks at the end of rows, etc, so don't worry about that not.?
    //int                                     *mGridTileCount;
    
    int                                     mGridScreenTop;
    int                                     mGridScreenHeight;
    
    int                                     mGridWidth;
    int                                     mGridHeight;
    
    virtual bool                            OnGrid(int pGridX, int pGridY);
    
    virtual bool                            SetTile(int pGridX, int pGridY, BoardGenericTile *pTile);
    
    virtual bool                            CanSetTile(int pGridX, int pGridY, BoardGenericTile *pTile);
    
    BoardGenericTile                        *GetTileBase(int pGridX, int pGridY);
    BoardGenericTile                        *GetTileBase(int pGridX, int pGridY, int pTileType);
    
    BoardGenericTile                        *RemoveTile(int pGridX, int pGridY);
    
    void                                    DeleteTile(int pGridX, int pGridY);
    
    virtual void                            GridChanged(){/*mTile = mGridGameTile*/}
    
    
    virtual void                            FreeGrid();
    
    ////////////////////////////
    //
    //  Rectangular stuff
    //
    
    virtual void                            GenerateTiles(int pGridWidth, int pGridHeight);
    virtual void                            SizeGrid(int pGridWidth, int pGridHeight);
    virtual void                            ResizeGrid(int pGridWidth, int pGridHeight);
    
    virtual void                            PadGridTop(int pBlockCount){PadGrid(pBlockCount, 0);}
    virtual void                            PadGridBottom(int pBlockCount){PadGrid(0, pBlockCount);}
    virtual void                            PadGrid(int pBlockCountTop, int pBlockCountBottom);
    
    //
    ////////////////////////////
    
    
    ////
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    
    //////////
    // Basic utility stuff, ...
    ///
    
    FParticle                               *SpawnParticleSequenceGrid(FSpriteSequence *pSequence, int pGridX, int pGridY);
    FParticle                               *SpawnParticleSequence(FSpriteSequence *pSequence, float pX, float pY);
    
    virtual void                            Save(const char *pPath);
    virtual void                            Load(const char *pPath);
    
};


#endif /* defined(__Bone__BoardGeneric__) */
