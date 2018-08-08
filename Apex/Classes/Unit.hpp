//
//  Unit.h
//  Mustache
//
//  Created by Nick Raptis on 6/17/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef UNIT_HPP
#define UNIT_HPP

#include "GLApp.hpp"
#include "LevelPath.hpp"
#include "SmallGameObject.hpp"


class GameArena;
class AnimatedLevelPath;
class GameTile;
class UnitPath;
class UnitGroup;

class Unit : public SmallGameObject {
public:

    Unit();
    virtual ~Unit();

    virtual void                        Update();
    virtual void                        Draw();

    void                                DrawGridPosInfo(float pShift);


    //Rule: We always have a unit group.
    UnitGroup                           *mGroup;
    bool                                mIsLeader;

    int                                 mPrevGridX;
    int                                 mPrevGridY;
    int                                 mPrevGridZ;

    int                                 mHP;
    int                                 mHPMax;

    bool                                ShouldResignLeadership();

    //The percent we are between  the move start position and
    //the move end position.
    void                                RefreshStepPercent();
    float                               mStepPercent;
    

    //The FIRST time we start walking, whether the leader or a follower.
    bool                                mDidStartWalking;
    
    float                               mWalkSpeed;
    bool                                mIsWalking;

    float                               mMovePercent;

    float                               mMoveStartX;
    float                               mMoveStartY;

    float                               mMoveEndX;
    float                               mMoveEndY;

    float                               mRotation;
    float                               mRotationSpeed;
    
    float                               mFrame;
    
    void                                Sleep(int pSleepTime);
    bool                                mIsSleeping;
    int                                 mSleepTimer;


    void                                ForceCompleteCurrentWalkPathSegment();


    //Assumption, this is not our current grid location and is an adjacent
    //grid location, and is unblocked.
    void                                FollowToNextPathSegment(int pGridX, int pGridY, int pGridZ, float pMovePercent);

    ///////////////////////////////////////////////
    //                                           //
    //           Only Pathing Stuff              //
    //                                           //

    //We make an ATTEMPT to clone the path, if we are not on the path,
    //then forget about it, there is no way to reconcile the current index.
    void                                AttemptCopyPathFromUnit(Unit *pUnit);
    void                                ResetPath();


    bool                                AttemptToAdvanceToNextPathSegment(float pMoveAmount);

    int                                 GetCurrentPathIndex();

    //This only happens ONCE as the units enter the game arena / grid.
    void                                PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, GameTile *pDestinationTile, LevelPath *pPath);

    int                                 mDestinationGridX;
    int                                 mDestinationGridY;
    int                                 mDestinationGridZ;

    LevelPath                           *mTrackingPath;

    GameTile                            *mDestinationTile;

    PathNode                            *mStartNode;
    PathNode                            *mDestinationNode;

    UnitPath                            *mPath;

    int                                 mPathIndex;

    bool                                mDidReachEndOfPath;

    //                                           //
    //                                           //
    //                                           //
    ///////////////////////////////////////////////
    
};

#endif
