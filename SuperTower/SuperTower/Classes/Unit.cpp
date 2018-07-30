//
//  Unit.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "Unit.hpp"
#include "GameArena.hpp"
#include "UnitPath.hpp"
#include "AnimatedLevelPath.hpp"

Unit::Unit() {
    mTrackingPath = 0;

    mPath = 0;

    mMovePercent = 0.0f;

    mMoveStartX = 0.0f;
    mMoveStartY = 0.0f;
    mMoveStartZ = 0.0f;

    mMoveEndX = 0.0f;
    mMoveEndY = 0.0f;
    mMoveEndZ = 0.0f;

    mPathIndex = 0;

    mKill = 0;

    mLeader = false;

    mStartedWalking = false;

    mDestinationGridX = -1;
    mDestinationGridY = -1;
    mDestinationGridZ = -1;
    
    mWalkSpeed = gRand.GetFloat(1.25f, 4.0f);

    mHPMax = 200;
    mHP = mHPMax;
    
    mWalking = false;
    
    mRotation = 0.0f;
    mRotationSpeed = 2.0f;

    mFrame = 0.0f;
}

Unit::~Unit() {
    //printf("Delete Unit [%x]\n", this);
}

void Unit::Update() {
    float aMaxFrame = (float)gApp->mNinja.mSequenceFrameCount;

    if (mWalking) {


    mFrame += 0.48f;
    if (mFrame >= aMaxFrame) {
        mFrame -= aMaxFrame;
    }

    } else {
        mFrame = 0.0f;
    }

    if (mLeader) {


    }


    /*
    mMovePercent = 0.0f;

    mMoveStartX = 0.0f;
    mMoveStartY = 0.0f;
    mMoveStartZ = 0.0f;

    mMoveEndX = 0.0f;
    mMoveEndY = 0.0f;
    mMoveEndZ = 0.0f;
    */


    if (mWalking) {
        float aTargetRotation = FaceTarget(mMoveStartX, mMoveStartY, mX, mY);
        mRotation += DistanceBetweenAngles(mRotation, aTargetRotation) / 14.0f;

        //TODO: Position will be controlled by a smoothing track of some sort...
    }
}

void Unit::Draw() {
    Graphics::SetColor();

    if (gApp->mDarkMode) {
        Graphics::SetColor(0.2f, 0.2f, 0.2f, 0.15f);
    }

    gApp->mNinja.Draw(mRotation, mFrame, mX, mY, 1.0f, 0.0f);


    if (mLeader) {

        Graphics::SetColor(0.5f);
        if (gApp->mDarkMode) {
            Graphics::SetColor(0.2f, 0.2f, 0.2f, 0.15f);
        }

        gApp->mUnitCircleSoft.Draw(mX, mY, 0.5f, 0.0f, 1);

    } else {
        Graphics::SetColor(0.5f);
        if (gApp->mDarkMode) {
            Graphics::SetColor(0.2f, 0.2f, 0.2f, 0.15f);
        }
        gApp->mUnitCircleHard.Draw(mX, mY, 0.35f, 0.0f, 1);
    }

    Graphics::SetColor();
}

void Unit::PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, GameTile *pDestinationTile, LevelPath *pPath) {

    int aGridX = pStartNode->mGridX;
    int aGridY = pStartNode->mGridY;
    int aGridZ = pStartNode->mGridZ;

    mStartNode = pStartNode;
    mGridX = pStartNode->mGridX;
    mGridY = pStartNode->mGridY;
    mGridZ = pStartNode->mGridZ;

    mX = gArena->GetUnitGridX(aGridX, aGridY, aGridZ);
    mY = gArena->GetUnitGridY(aGridX, aGridY, aGridZ);

    //Our Destination should be the center node of the end tile..
    mDestinationNode = pDestinationNode;
    mDestinationGridX = pDestinationNode->mGridX;
    mDestinationGridY = pDestinationNode->mGridY;
    mDestinationGridZ = pDestinationNode->mGridZ;

    mDestinationTile = pDestinationTile;

    mTrackingPath = pPath;
}



