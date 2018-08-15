//
//  Unit.cpp
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "Unit.hpp"
#include "MapArena.hpp"
#include "UnitPath.hpp"
#include "AnimatedLevelPath.hpp"

#define UNIT_DEFAULT_SLEEP_TIME 32

Unit::Unit() {
    mTrackingPath = 0;

    mPrevGridX = -1;
    mPrevGridY = -1;
    mPrevGridZ = -1;

    mStepPercent = 0.0f;

    mGroup = 0;
    mPath = 0;

    mMovePercent = 0.0f;

    mMoveStartX = 0.0f;
    mMoveStartY = 0.0f;

    mMoveEndX = 0.0f;
    mMoveEndY = 0.0f;

    mPathIndex = 0;

    mKill = 0;

    mIsLeader = false;

    mWalkSpeed = 0.0f;
    mIsWalking = false;

    mDidStartWalking = false;

    mDidReachEndOfPath = false;

    mDestinationGridX = -1;
    mDestinationGridY = -1;
    mDestinationGridZ = -1;
    
    mWalkSpeed = 0.025f;

    mHPMax = 200;
    mHP = mHPMax;

    mIsSleeping = false;
    mSleepTimer = 0;
    
    mRotation = 0.0f;
    mRotationSpeed = 2.0f;

    mFrame = 0.0f;
}

Unit::~Unit() {
    printf("Delete Unit [%lx]\n", (unsigned long)this);

    if (mGroup) {

    }
    
    delete mPath;
    mPath = 0;
}

void Unit::Update() {
    float aMaxFrame = (float)gApp->mNinja.mSequenceFrameCount;
    if (mIsWalking) {
        mFrame += 1.25f;
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
        if (mIsLeader) {
            if (mIsWalking == false && mPath != NULL) {
                if (AttemptToAdvanceToNextPathSegment(0.0f)) {
                    gArena->UnitDidStartWalkingFromIdle(this);
                }
            }
        }
    }

    if (mIsWalking) {
        float aTargetRotation = FaceTarget(mMoveStartX, mMoveStartY, mX, mY);
        mRotation = aTargetRotation; //+= DistanceBetweenAngles(mRotation, aTargetRotation) / 3.0f;

        float aDirX = mMoveEndX - mMoveStartX;
        float aDirY = mMoveEndY - mMoveStartY;
        float aDistance = aDirX * aDirX + aDirY * aDirY;
        if (aDistance > 0.01f) {
            aDistance = sqrtf(aDistance);
            aDirX /= aDistance;
            aDirY /= aDistance;
        }
        
        Unit *aLeader = mGroup->Leader();
        if (mIsLeader) {
            float aEndDirX = mMoveEndX - mX;
            float aEndDirY = mMoveEndY - mY;
            float aEndDistance = aEndDirX * aEndDirX + aEndDirY * aEndDirY;
            if (aEndDistance > 0.01f) {
                aEndDistance = sqrtf(aEndDistance);
            }

            float aOvershoot = mWalkSpeed;
            bool aGoToNextSegment = false;
            if (aEndDistance > 0.01f) {
                if (aEndDistance > mWalkSpeed) {
                    //Just inch towards the next location...
                    mX += aDirX * mWalkSpeed;
                    mY += aDirY * mWalkSpeed;
                    RefreshStepPercent();
                } else {
                    aOvershoot = mWalkSpeed - aEndDistance;
                    mX = mMoveEndX;
                    mY = mMoveEndY;
                    aGoToNextSegment = true;
                }
            } else {
                aGoToNextSegment = true;
            }

            if (aGoToNextSegment) {
                if (AttemptToAdvanceToNextPathSegment(aOvershoot)) {
                    gArena->UnitDidFinishWalkingStep(this);
                }
            }
        } else {
            mStepPercent = aLeader->mStepPercent;
            mX = mMoveStartX + aDirX * aDistance * mStepPercent;
            mY = mMoveStartY + aDirY * aDistance * mStepPercent;
        }
    }

    if (mGridX == mDestinationGridX && mGridY == mDestinationGridY && mGridZ == mDestinationGridZ) {
        mDidReachEndOfPath = true;
    }
}

void Unit::Draw() {
    Graphics::SetColor();

    if (gApp->mDarkMode) {
        Graphics::SetColor(0.2f, 0.2f, 0.2f, 0.15f);
    }

    gApp->mNinja.Draw(mRotation, mFrame, mX, mY, 0.5f, 0.0f);
    
    if (mIsLeader) {
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
        gApp->mUnitCircleHard.Draw(mX, mY, 0.25f, 0.0f, 1);
    }
    Graphics::SetColor();
}

void Unit::DrawGridPosInfo(float pShift) {
    FString aGridString = FString("[") + FString(mGridX) + FString(",")
     + FString(mGridY) + FString(",") + FString(mGridZ) + FString("]");
    gApp->mSysFont.Center(aGridString.c(), mX, mY - 24.0f + pShift, 0.45f);
}


bool Unit::ShouldResignLeadership() {

    bool aResult = false;

    if (mDidReachEndOfPath) aResult = true;
    if (mKill != 0) aResult = true;

    return aResult;
}

void Unit::ResetPath() {
    mPathIndex = -1;
    if (mPath != NULL) {
        mPath->Reset();
    }
}

void Unit::AttemptCopyPathFromUnit(Unit *pUnit) {
    ResetPath();
    if (pUnit != NULL && pUnit->mPath != NULL) {
        int aNewPathIndex = pUnit->mPath->GetIndexOfGridPosition(mGridX, mGridY, mGridZ);
        if (aNewPathIndex != -1) {
            if (mPath == NULL) {
                mPath = new UnitPath();
            }
            mPath->CloneFrom(pUnit->mPath);
            mPathIndex = aNewPathIndex;
            //TODO: Verify...
            //if (mIsWalking) {
            //    mPathIndex -= 1;
            //}
        }
    }
}

void Unit::FollowToNextPathSegment(int pGridX, int pGridY, int pGridZ, float pMovePercent) {
    PathNode *aPrevNode = gArena->GetGridNode(mGridX, mGridY, mGridZ);
    PathNode *aNode = gArena->GetGridNode(pGridX, pGridY, pGridZ);

    if (aPrevNode == NULL || aNode == NULL) {
        printf("Fatal Error: Node [%lX] Or Prev Node [%lX] is NULL...\n", (unsigned long)aPrevNode, (unsigned long)aNode);
        mIsWalking = false;
        return;
    }

    printf("FollowToNextPathSegment Prev:(%d %d %d) G:(%d %d %d) N:(%d %d %d)\n", mPrevGridX, mPrevGridY, mPrevGridZ, mGridX, mGridY, mGridZ, pGridX, pGridY, pGridZ);
    
    mPrevGridX = mGridX;mPrevGridY = mGridY;mPrevGridZ = mGridZ;
    mGridX = pGridX;mGridY = pGridY;mGridZ = pGridZ;

    mIsWalking = true;
    mDidStartWalking = true;

    mMoveStartX = aPrevNode->mCenterX;
    mMoveStartY = aPrevNode->mCenterY;
    mMoveEndX = aNode->mCenterX;
    mMoveEndY = aNode->mCenterY;

    float aDirX = mMoveEndX - mX;
    float aDirY = mMoveEndY - mY;
    float aDistance = aDirX * aDirX + aDirY * aDirY;
    if (aDistance > 0.01f) {
        aDistance = sqrtf(aDistance);
        aDirX /= aDistance;
        aDirY /= aDistance;
        float aMoveAmount = aDistance * pMovePercent;
        if (aDistance > aMoveAmount) {
            mX += aDirX * aMoveAmount;
            mY += aDirY * aMoveAmount;
            RefreshStepPercent();
        } else {
            mX = mMoveEndX;
            mY = mMoveEndY;
            RefreshStepPercent();
        }
    } else {
        mX = mMoveEndX;
        mY = mMoveEndY;
        RefreshStepPercent();
    }
}

bool Unit::AttemptToAdvanceToNextPathSegment(float pMoveAmount) {
    //By default we will have gone 0% forward...
    mStepPercent = 0.0f;
    bool aResult = false;

    //We can't advance to the next path location if we are at the last path location...
    if (mPath != NULL && mPathIndex < (mPath->mLength - 1)) {
        int aNextGridX = mPath->mPathX[mPathIndex + 1];
        int aNextGridY = mPath->mPathY[mPathIndex + 1];
        int aNextGridZ = mPath->mPathZ[mPathIndex + 1];

        PathNode *aNode = gArena->GetGridNode(mGridX, mGridY, mGridZ);
        PathNode *aNextNode = gArena->GetGridNode(aNextGridX, aNextGridY, aNextGridZ);

        if (gArena->CanUnitWalkToAdjacentGridPosition(this, aNextGridX, aNextGridY, aNextGridZ) == false) {
            //printf("Unit - Unable to walk to next desired location...\n");
        } else if (aNode == NULL) {
            //printf("Unit - Attempting to walk and CURRENT NODE isn't found...\n");
        } else if (aNextNode == NULL) {
            //printf("Unit - Attempting to walk and NEXT NODE isn't found...\n");
        } else {

            mDidStartWalking = true;

            mIsWalking = true;
            mPathIndex += 1;

            mPrevGridX = mGridX;
            mPrevGridY = mGridY;
            mPrevGridZ = mGridZ;

            mGridX = aNextGridX;
            mGridY = aNextGridY;
            mGridZ = aNextGridZ;
            
            mMoveStartX = aNode->mCenterX;
            mMoveStartY = aNode->mCenterY;
            mMoveEndX = aNextNode->mCenterX;
            mMoveEndY = aNextNode->mCenterY;

            aResult = true;
        }
    } else {
        mIsWalking = false;
    }

    if (mIsWalking) {
        //Advance our distance along the path...
        float aDirX = mMoveEndX - mMoveStartX;
        float aDirY = mMoveEndY - mMoveStartY;
        float aDistance = aDirX * aDirX + aDirY * aDirY;
        if (aDistance > 0.01f) {
            aDistance = sqrtf(aDistance);
            aDirX /= aDistance;
            aDirY /= aDistance;
            mX += aDirX * pMoveAmount;
            mY += aDirY * pMoveAmount;
            RefreshStepPercent();
        }
    }

    return aResult;
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

void Unit::ForceCompleteCurrentWalkPathSegment() {
    if (mIsWalking) {
        mX = mMoveEndX;
        mY = mMoveEndY;
    }
}

void Unit::RefreshStepPercent() {
    float aStepDiffX = (mMoveEndX - mMoveStartX);
    float aStepDiffY = (mMoveEndY - mMoveStartY);
    float aDiffX = mX - mMoveStartX;
    float aDiffY = mY - mMoveStartY;
    float aStepLength = aStepDiffX * aStepDiffX + aStepDiffY * aStepDiffY;
    if (aStepLength > SQRT_EPSILON) {
        aStepLength = sqrtf(aStepLength);
        float aMoveLength = aDiffX * aDiffX + aDiffY * aDiffY;
        if (aMoveLength > SQRT_EPSILON) {
            aMoveLength = sqrtf(aMoveLength);
        }
        mStepPercent = aMoveLength / aStepLength;
    } else {
        mStepPercent = 0.0f;
    }
}

void Unit::PlaceOnGrid(PathNode *pStartNode, PathNode *pDestinationNode, MapTile *pDestinationTile, LevelPath *pPath) {
    mGridX = pStartNode->mGridX;
    mGridY = pStartNode->mGridY;
    mGridZ = pStartNode->mGridZ;

    mPrevGridX = mGridX;
    mPrevGridY = mGridY;
    mPrevGridZ = mGridZ;

    mStartNode = pStartNode;
    
    mX = gArena->GetUnitGridX(mGridX, mGridY, mGridZ);
    mY = gArena->GetUnitGridY(mGridX, mGridY, mGridZ);
    
    mMoveStartX = mX;
    mMoveStartY = mY;
    
    mMoveEndX = mX;
    mMoveEndY = mY;
    
    //Our Destination should be the center node of the end tile..
    mDestinationNode = pDestinationNode;
    mDestinationGridX = pDestinationNode->mGridX;
    mDestinationGridY = pDestinationNode->mGridY;
    mDestinationGridZ = pDestinationNode->mGridZ;

    mDestinationTile = pDestinationTile;
    
    mTrackingPath = pPath;
}



