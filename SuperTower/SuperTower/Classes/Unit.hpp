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

class Unit : public SmallGameObject {
public:

    Unit();
    virtual ~Unit();

    virtual void                        Update();
    virtual void                        Draw();

    int                                 mHP;
    int                                 mHPMax;

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

    bool                                mLeader;

    void                                Sleep(int pSleepTime);
    bool                                mIsSleeping;
    int                                 mSleepTimer;


    ///////////////////////////////////////////////
    //                                           //
    //           Only Pathing Stuff              //
    //                                           //


    void                                AttemptToAdvanceToNextPathSegment(float pMoveAmount);


    int                                 GetCurrentPathIndex();

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

    //                                           //
    //                                           //
    //                                           //
    ///////////////////////////////////////////////


    
};

#endif
