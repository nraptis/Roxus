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

#define UNIT_DEFAULT_SLEEP_TIME 32

Unit::Unit() {
    mTrackingPath = 0;

    mPath = 0;

    mMovePercent = 0.0f;

    mMoveStartX = 0.0f;
    mMoveStartY = 0.0f;

    mMoveEndX = 0.0f;
    mMoveEndY = 0.0f;

    mPathIndex = 0;

    mKill = 0;

    mLeader = false;

    mWalkSpeed = 0.0f;
    mIsWalking = false;

    mDidStartWalking = false;

    mDestinationGridX = -1;
    mDestinationGridY = -1;
    mDestinationGridZ = -1;
    
    mWalkSpeed = gRand.GetFloat(1.25f, 4.0f);

    mHPMax = 200;
    mHP = mHPMax;

    mIsSleeping = false;
    mSleepTimer = 0;
    
    mRotation = 0.0f;
    mRotationSpeed = 2.0f;

    mFrame = 0.0f;
}

Unit::~Unit() {
    //printf("Delete Unit [%x]\n", this);
}

void Unit::Update() {
    float aMaxFrame = (float)gApp->mNinja.mSequenceFrameCount;

    if (mIsWalking) {

        mFrame += 0.48f;
        if (mFrame >= aMaxFrame) {
            mFrame -= aMaxFrame;
        }

    } else {
        mFrame = 0.0f;
    }


    if (mIsSleeping) {
        mSleepTimer -= 1;
        if (mSleepTimer <= 0) {
            mSleepTimer = 0;
            mIsSleeping = false;
        }

    }

    if (mIsSleeping == false) {
        if (mLeader && mIsWalking == false && mPath != NULL) {

            AttemptToAdvanceToNextPathSegment(0.0f);


        } //
    } // mIsSleeping == false

    /*
     mMovePercent = 0.0f;

     mMoveStartX = 0.0f;
     mMoveStartY = 0.0f;
     mMoveStartZ = 0.0f;

     mMoveEndX = 0.0f;
     mMoveEndY = 0.0f;
     mMoveEndZ = 0.0f;
     */

    if (mIsWalking) {
        float aTargetRotation = FaceTarget(mMoveStartX, mMoveStartY, mX, mY);
        mRotation += DistanceBetweenAngles(mRotation, aTargetRotation) / 14.0f;

        float aDirX = mMoveEndX - mX;
        float aDirY = mMoveEndY - mY;

        float aOvershoot = mWalkSpeed;
        bool aGoToNextSegment = false;

        float aDistance = aDirX * aDirX + aDirY * aDirY;
        if (aDistance > 0.01f) {
            aDistance = sqrtf(aDistance);
            aDirX /= aDistance;
            aDirY /= aDistance;

            if (aDistance > mWalkSpeed) {
                //Just inch towards the next location...
                mX += aDirX * mWalkSpeed;
                mY += aDirY * mWalkSpeed;
            } else {
                aOvershoot = mWalkSpeed - aDistance;
                mX = mMoveEndX;
                mY = mMoveEndY;
                aGoToNextSegment = true;
            }
        } else {
            aGoToNextSegment = true;
        }

        if (aGoToNextSegment) {
            AttemptToAdvanceToNextPathSegment(aOvershoot);
        }

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

void Unit::AttemptToAdvanceToNextPathSegment(float pMoveAmount) {

    if (mPath != NULL && mPathIndex < (mPath->mLength - 1)) {
        int aNextGridX = mPath->mPathX[mPathIndex + 1];
        int aNextGridY = mPath->mPathY[mPathIndex + 1];
        int aNextGridZ = mPath->mPathZ[mPathIndex + 1];

        PathNode *aNode = gArena->GetGridNode(mGridX, mGridY, mGridZ);
        PathNode *aNextNode = gArena->GetGridNode(aNextGridX, aNextGridY, aNextGridZ);

        if (gArena->CanUnitWalkToAdjacentGridPosition(this, aNextGridX, aNextGridY, aNextGridZ) == false) {
            printf("Unit - Unable to walk to next desired location...\n");
        } else if (aNode == NULL) {
            printf("Unit - Attempting to walk and CURRENT NODE isn't found...\n");
        } else if (aNextNode == NULL) {
            printf("Unit - Attempting to walk and NEXT NODE isn't found...\n");
        } else {

            mIsWalking = true;

            mPathIndex += 1;

            mGridX = aNextGridX;mGridY = aNextGridY;mGridZ = aNextGridZ;
            mMoveStartX = aNode->mCenterX;mMoveStartY = aNode->mCenterY;
            mMoveEndX = aNextNode->mCenterX;mMoveEndY = aNextNode->mCenterY;
        }
    } else {
        mIsWalking = false;
    }

    if (mIsWalking) {
        //Advance our distance along the path...
        float aDirX = mMoveEndX - mX;
        float aDirY = mMoveEndY - mY;
        float aDistance = aDirX * aDirX + aDirY * aDirY;
        if (aDistance > 0.01f) {
            aDistance = sqrtf(aDistance);
            aDirX /= aDistance;
            aDirY /= aDistance;
            mX += aDirX * pMoveAmount;
            mY += aDirY * pMoveAmount;
        }
    }
}

int Unit::GetCurrentPathIndex() {
    int aResult = -1;
    if (mPath != NULL) {
        for (int i=0;i<mPath->mLength;i++) {
            if (mPath->mPathX[i] == mGridX &&
                mPath->mPathY[i] == mGridY &&
                mPath->mPathZ[i] == mGridZ) {
                aResult = i;
                break;
            }
        }
    }
    return aResult;
}

void Unit::Sleep(int pSleepTime) {
    mIsSleeping = true;
    mSleepTimer = pSleepTime;
}

void Unit::PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, GameTile *pDestinationTile, LevelPath *pPath) {
    
    mGridX = pStartNode->mGridX;
    mGridY = pStartNode->mGridY;
    mGridZ = pStartNode->mGridZ;

    mStartNode = pStartNode;

    mX = gArena->GetUnitGridX(mGridX, mGridY, mGridZ);
    mY = gArena->GetUnitGridY(mGridX, mGridY, mGridZ);

    //Our Destination should be the center node of the end tile..
    mDestinationNode = pDestinationNode;
    mDestinationGridX = pDestinationNode->mGridX;
    mDestinationGridY = pDestinationNode->mGridY;
    mDestinationGridZ = pDestinationNode->mGridZ;

    mDestinationTile = pDestinationTile;

    mTrackingPath = pPath;
}



