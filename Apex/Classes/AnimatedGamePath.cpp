//
//  AnimatedGamePath.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/12/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "AnimatedGamePath.hpp"
#include "FLine.h"

AnimatedGamePath::AnimatedGamePath() {
    mSelected = false;
    mEditorMode = false;

    mPathWidth = 24.0f;
    mPathWidth2 = (mPathWidth / 2.0f);

    mTrackWidth = 3.0f;
    mTrackOffset = 2.0f;

    mTextureAnimationOffset = 0.0f;

    mTrackColorInner.mRed = 1.0f;
    mTrackColorInner.mGreen = 1.0f;
    mTrackColorInner.mBlue = 1.0f;
    mTrackColorInner.mAlpha = 1.0f;

    mTrackColorOuter.mRed = 1.0f;
    mTrackColorOuter.mGreen = 1.0f;
    mTrackColorOuter.mBlue = 1.0f;
    mTrackColorOuter.mAlpha = 1.0f;

    mUpRampScaleFactor = 1.5f;
    mDownRampScaleFactor = 0.5f;

    mSprite = &gApp->m1024x1024;
}

AnimatedGamePath::~AnimatedGamePath() {

}

void AnimatedGamePath::Update() {
    mTextureAnimationOffset += 0.0050f;
    if (mTextureAnimationOffset >= 1.0f) {
        mTextureAnimationOffset -= 1.0f;
    }

    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {

        aChunk->mDemoIndexTimer++;
        if (aChunk->mDemoIndexTimer >= 5) {
            aChunk->mDemoIndexTimer = 0;

            aChunk->mDemoIndex++;
            if (aChunk->mDemoIndex > aChunk->mPathNodeList.mCount) {
                aChunk->mDemoIndex = 0;
            }
        }
    }
}

void AnimatedGamePath::DrawEditorMarkers() {


    if (mLength >= 2) {
        int aStartDirX = mPathX[1] - mPathX[0];
        int aStartDirY = mPathY[1] - mPathY[0];
        int aPrevGridX = mPathX[0] - aStartDirX;
        int aPrevGridY = mPathY[0] - aStartDirY;
        int aPrevGridZ = mPathZ[0];
        int aGridX = 0;
        int aGridY = 0;
        int aGridZ = 0;
        for (int i=0;i<mLength;i++) {

            aGridX = mPathX[i];
            aGridY = mPathY[i];
            aGridZ = mPathZ[i];

            float aPreviousCenterX = CX(aPrevGridX, aPrevGridZ);
            float aPreviousCenterY = CY(aPrevGridY, aPrevGridZ);
            float aCenterX = CX(aGridX, aGridZ);
            float aCenterY = CY(aGridY, aGridZ);

            if (mSelected) {
                Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.2f);
                Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 2.0f);
                Graphics::SetColor(0.85f, 0.15f, 0.15f, 0.2f);
                Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 1.0f);
            } else {
                Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.15f);
                Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 2.0f);
                Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.1f);
                Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 1.0f);
            }

            aPrevGridX = aGridX;
            aPrevGridY = aGridY;
            aPrevGridZ = aGridZ;
        }
    }




    float aX1 = CX(mStartX, mStartZ);
    float aY1 = CY(mStartY, mStartZ);
    float aX2 = CX(mEndX, mEndZ);
    float aY2 = CY(mEndY, mEndZ);

    if (mLength < 2) {
        Graphics::SetColor(0.75f, 0.75f, 0.125f, 0.75f);
        Graphics::DrawLine(aX1, aY1, aX2, aY2, 8.0f);
    }

    Graphics::SetColor();

    gApp->mUnitCircleSoft.Center(aX1, aY1);
    gApp->mUnitCircleSoft.Center(aX2, aY2);



    if (mSelected) {
        gApp->mUnitCircleHard.Center(aX1, aY1);
        gApp->mUnitCircleHard.Center(aX2, aY2);
    }


    /*
     int aModex = 0;
     EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {
     Graphics::SetColorSwatch(aModex, 0.666f);

     EnumList(AnimatedGamePathNode, aNode, aChunk->mPathNodeList) {
     float aX1 = aNode->mCenterX + aNode->mNormX * 20.0f;
     float aY1 = aNode->mCenterY + aNode->mNormY * 20.0f;

     float aX2 = aNode->mCenterX - aNode->mNormX * 20.0f;
     float aY2 = aNode->mCenterY - aNode->mNormY * 20.0f;

     Graphics::DrawLine(aX1, aY1, aX2, aY2, 0.5f);
     }
     aModex += 1;
     }
     */

}

void AnimatedGamePath::DrawPrepare() {
    GenerateTextureQuads();
}

void AnimatedGamePath::Draw(int pDepth) {

    //Graphics::CullFacesEnable();
    //Graphics::CullFacesSetBack();

    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {
        if (aChunk->mDepth == pDepth) {

            if (gApp->mDarkMode) {
                Graphics::SetColor(0.10f, 0.10f, 0.10f, 0.75f);
            } else {
                Graphics::SetColor();
            }
            
            aChunk->mBufferMainPath.SetTexture(mSprite->mTexture);
            aChunk->mBufferMainPath.Draw();
            aChunk->mBufferTrack1.Draw(0);
            aChunk->mBufferTrack2.Draw(0);

            AnimatedGamePathNode *aNode = (AnimatedGamePathNode *)(aChunk->mPathNodeList.Fetch(aChunk->mDemoIndex));

            Graphics::SetColor(1.0f, 0.25f, 0.05f, 0.85f);
            if (aNode) {
                Graphics::DrawPoint(aNode->mCenterX, aNode->mCenterY, 6.0f);
            }
        }
    }
}

void AnimatedGamePath::ComputePath(GameArena *pArena) {
    GamePath::ComputePath(pArena);
    Generate();
}

void AnimatedGamePath::Reset() {
    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {
        EnumList(AnimatedGamePathNode, aNode, aChunk->mPathNodeList) {
            mPathNodeQueue.Add(aNode);
        }
        aChunk->mPathNodeList.RemoveAll();
        mPathChunkQueue.Add(aChunk);
    }
    mPathChunkList.RemoveAll();

}

void AnimatedGamePath::Generate() {
    Reset();

    if (mLength < 2) { return; }

    int aStartDirX = mPathX[1] - mPathX[0];
    int aStartDirY = mPathY[1] - mPathY[0];
    int aPrevGridX = mPathX[0] - aStartDirX;
    int aPrevGridY = mPathY[0] - aStartDirY;
    int aPrevGridZ = mPathZ[0];
    int aGridX = 0;
    int aGridY = 0;
    int aGridZ = 0;
    int aNextGridX = 0;
    int aNextGridY = 0;
    int aNextGridZ = 0;

    aPrevGridX = mPathX[0];
    aPrevGridY = mPathY[0];
    aPrevGridZ = mPathZ[0];

    aGridX = mPathX[1];
    aGridY = mPathY[1];
    aGridZ = mPathZ[1];

    for (int i=2;i<mLength;i++) {
        aNextGridX = mPathX[i];
        aNextGridY = mPathY[i];
        aNextGridZ = mPathZ[i];
        float aCenterX = CX(aGridX, aGridZ);
        float aCenterY = CY(aGridY, aGridZ);

        // Up
        // ---
        // ++-
        // -+-
        if (aPrevGridX == aGridX &&
            aPrevGridY > aGridY &&
            aNextGridX < aGridX &&
            aNextGridY == aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aBottomY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Up
        // ---
        // -++
        // -+-
        else if (aPrevGridX == aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY == aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aBottomY, aCenterX, aCenterY, aRightX, aCenterY);
        }

        // Left
        // -+-
        // ++-
        // ---
        else if (aPrevGridX < aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX == aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Left
        // ---
        // ++-
        // -+-
        else if (aPrevGridX < aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX == aGridX &&
                 aNextGridY > aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        // Right
        // -+-
        // -++
        // ---
        else if (aPrevGridX > aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX == aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Right
        // ---
        // -++
        // -+-
        else if (aPrevGridX > aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX == aGridX &&
                 aNextGridY > aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        // Down
        // -+-
        // ++-
        // ---
        else if (aPrevGridX == aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY == aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Down
        // -+-
        // -++
        // ---
        else if (aPrevGridX == aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY == aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aRightX, aCenterY);
        }

        // Left
        // --+
        // ++-
        // ---
        else if (aPrevGridX > aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY == aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aTopY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Left
        // ---
        // ++-
        // --+
        else if (aPrevGridX > aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY == aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aBottomY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Left
        // +--
        // -++
        // ---
        else if (aPrevGridX > aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aLeftX, aTopY);
        }


        // Left
        // ---
        // -++
        // +--
        else if (aPrevGridX > aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY > aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aLeftX, aBottomY);
        }

        // Right
        // --+
        // ++-
        // ---
        else if (aPrevGridX < aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aRightX, aTopY);
        }

        // Right
        // ---
        // ++-
        // --+
        else if (aPrevGridX < aGridX &&
                 aPrevGridY == aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY > aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aRightX, aBottomY);
        }

        // Right
        // +--
        // -++
        // ---
        else if (aPrevGridX < aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY == aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aTopY, aCenterX, aCenterY, aRightX, aCenterY);
        }
        
        // Right
        // ---
        // -++
        // +--
        else if (aPrevGridX < aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY == aGridY) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aBottomY, aCenterX, aCenterY, aRightX, aCenterY);
        }

        // Up
        // -+-
        // -+-
        // --+
        else if (aPrevGridX > aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX == aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aBottomY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Up
        // -+-
        // -+-
        // +--
        else if (aPrevGridX < aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX == aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aBottomY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Up
        // +--
        // -+-
        // -+-
        else if (aPrevGridX == aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aBottomY, aCenterX, aCenterY, aLeftX, aTopY);
        }

        // Up
        // --+
        // -+-
        // -+-
        else if (aPrevGridX == aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY < aGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aBottomY, aCenterX, aCenterY, aRightX, aTopY);
        }

        // Down
        // -+-
        // -+-
        // --+
        else if (aPrevGridX == aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX > aGridX &&
                 aGridY < aNextGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aRightX, aBottomY);
        }

        // Down
        // -+-
        // -+-
        // +--
        else if (aPrevGridX == aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX < aGridX &&
                 aGridY < aNextGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aLeftX, aBottomY);
        }

        // Down
        // +--
        // -+-
        // -+-
        else if (aPrevGridX < aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX == aGridX &&
                 aGridY < aNextGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aTopY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        // Down
        // --+
        // -+-
        // -+-
        else if (aPrevGridX > aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX == aGridX &&
                 aGridY < aNextGridY) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aTopY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        // Top-Left
        // +--
        // -+-
        // --+
        else if (aPrevGridX < aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY > aGridY) {
            float aLeftX = aCenterX - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            AddStraight(aGridZ, aLeftX, aTopY, aRightX, aBottomY);
        }
        // Bottom-Right
        // +--
        // -+-
        // --+
        else if (aPrevGridX > aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY < aGridY) {
            float aLeftX = aCenterX - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            AddStraight(aGridZ, aRightX, aBottomY, aLeftX, aTopY);
        }

        // Top-Right
        // --+
        // -+-
        // +--
        else if (aPrevGridX > aGridX &&
                 aPrevGridY < aGridY &&
                 aNextGridX < aGridX &&
                 aNextGridY > aGridY) {
            float aLeftX = aCenterX - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            AddStraight(aGridZ, aRightX, aTopY, aLeftX, aBottomY);
        }
        // Bottom-Left
        // --+
        // -+-
        // +--
        else if (aPrevGridX < aGridX &&
                 aPrevGridY > aGridY &&
                 aNextGridX > aGridX &&
                 aNextGridY < aGridY) {
            float aLeftX = aCenterX - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            AddStraight(aGridZ, aLeftX, aBottomY, aRightX, aTopY);
        }

        //This is a vertical line...
        else if (aNextGridX == aGridX && aPrevGridX == aGridX) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aPrevCenterY = CY(aPrevGridY, aPrevGridZ);
            float aNextCenterY = CY(aNextGridY, aNextGridZ);
            //Going DOWN...
            if (aPrevGridY < aGridY) {
                //Going down, we were on level ground.
                if (aPrevGridZ == aGridZ) {
                    //Going down, we were on level ground, next tile is lower
                    if (aNextGridZ < aGridZ) {
                        //Since we are going down, this tile is a ramp...
                        float aNextTop = aNextCenterY - gTileSize2;
                        AddVerticalRamp(aGridZ, mDownRampScaleFactor, aCenterX, aTopY, aCenterX, aNextTop);
                    } else {
                        AddStraight(aGridZ, aCenterX, aTopY, aCenterX, aBottomY);
                    }
                }
                //Going down, we were on a different level...
                else {
                    if (aNextGridZ != aGridZ) {
                        //We are on a flat crest between 2 ramps...
                        if (aNextGridZ == aPrevGridZ) {
                            AddStraight(aGridZ, aCenterX, aTopY, aCenterX, aBottomY);
                        } else {
                            if (aNextGridZ > aGridZ) {
                                float aPrevBottom = aPrevCenterY + gTileSize2;
                                AddVerticalRamp(aGridZ, mUpRampScaleFactor, aCenterX, aPrevBottom, aCenterX, aBottomY);
                            } else {
                                float aNextTop = aNextCenterY - gTileSize2;
                                AddVerticalRamp(aGridZ, mDownRampScaleFactor, aCenterX, aTopY, aCenterX, aNextTop);
                            }
                        }
                        //We are on a ramp TO a ramp...
                    } else {
                        if (aPrevGridZ > aGridZ) {
                            //Here we just finished going down a ramp...
                            AddStraight(aGridZ, aCenterX, aTopY, aCenterX, aBottomY);
                        } else {
                            float aPrevBottom = aPrevCenterY + gTileSize2;
                            AddVerticalRamp(aGridZ, mUpRampScaleFactor, aCenterX, aPrevBottom, aCenterX, aBottomY);
                        }
                    }
                }
            }

            //Up
            else {


                //Going up, we were on level ground.
                if (aPrevGridZ == aGridZ) {
                    //Going down, we were on level ground, next tile is lower
                    if (aNextGridZ < aGridZ) {
                        //Since we are going down, this tile is a ramp...
                        float aNextBottom = aNextCenterY + gTileSize2;
                        AddVerticalRamp(aGridZ, mUpRampScaleFactor, aCenterX, aBottomY, aCenterX, aNextBottom);
                    } else {
                        AddStraight(aGridZ, aCenterX, aBottomY, aCenterX, aTopY);
                    }
                }
                //Going up, we were on a different level...
                else {
                    if (aNextGridZ != aGridZ) {
                        //We are on a flat crest between 2 ramps...
                        if (aNextGridZ == aPrevGridZ) {
                            AddStraight(aGridZ, aCenterX, aBottomY, aCenterX, aTopY);
                        } else {
                            if (aNextGridZ > aGridZ) {
                                float aPrevTop = aPrevCenterY - gTileSize2;
                                AddVerticalRamp(aGridZ, mDownRampScaleFactor, aCenterX, aPrevTop, aCenterX, aTopY);
                            } else {
                                float aNextBottom = aNextCenterY + gTileSize2;
                                AddVerticalRamp(aGridZ, mUpRampScaleFactor, aCenterX, aBottomY, aCenterX, aNextBottom);
                            }
                        }
                        //We are on a ramp TO a ramp...
                    } else {
                        if (aPrevGridZ > aGridZ) {
                            //Here we just finished going down a ramp...
                            AddStraight(aGridZ, aCenterX, aBottomY, aCenterX, aTopY);
                        } else {
                            float aPrevTop = aPrevCenterY - gTileSize2;
                            AddVerticalRamp(aGridZ, mDownRampScaleFactor, aCenterX, aPrevTop, aCenterX, aTopY);
                        }
                    }
                }
            }
        }
        //Horizontal line...
        else { //if (aNextGridY == aGridY && aPrevGridY == aGridY) {
            float aLeftX = aCenterX - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aPrevCenterY = CY(aPrevGridY, aPrevGridZ);
            float aNextCenterY = CY(aNextGridY, aNextGridZ);
            //Going to the right...
            if (aPrevGridX < aGridX) {
                //Going to the right, we were on level ground.
                if (aPrevGridZ == aGridZ) {
                    //Going to the right, we were on level ground, next tile is lower
                    if (aNextGridZ < aGridZ) {
                        //Since we are going down, this tile is a ramp...
                        AddHorizontalRamp(aGridZ, aLeftX, aCenterY, aRightX, aNextCenterY);
                    } else {
                        AddStraight(aGridZ, aLeftX, aCenterY, aRightX, aCenterY);
                    }
                }
                //Going to the right, we were on a different level...
                else {
                    if (aNextGridZ != aGridZ) {
                        //We are on a flat crest between 2 ramps...
                        if (aNextGridZ == aPrevGridZ) {
                            AddStraight(aGridZ, aLeftX, aCenterY, aRightX, aCenterY);
                        } else {
                            if (aNextGridZ > aGridZ) {
                                AddHorizontalRamp(aGridZ, aLeftX, aPrevCenterY, aRightX, aCenterY);
                            } else {
                                AddHorizontalRamp(aGridZ, aLeftX, aCenterY, aRightX, aNextCenterY);
                            }
                        }
                        //We are on a ramp TO a ramp...
                    } else {
                        if (aPrevGridZ > aGridZ) {
                            //Here we just finished going down a ramp...
                            AddStraight(aGridZ, aLeftX, aCenterY, aRightX, aCenterY);

                        } else {
                            //Here we are going up a ramp...
                            AddHorizontalRamp(aGridZ, aLeftX, aPrevCenterY, aRightX, aCenterY);
                        }
                    }
                }
            }
            //Going to the left...
            else {
                //Going to the left, we were on level ground.
                if (aPrevGridZ == aGridZ) {
                    //Going to the left, we were on level ground, next tile is lower
                    if (aNextGridZ < aGridZ) {
                        //Since we are going down, this tile is a ramp...
                        AddHorizontalRamp(aGridZ, aRightX, aCenterY, aLeftX, aNextCenterY);
                    } else {
                        AddStraight(aGridZ, aRightX, aCenterY, aLeftX, aCenterY);
                    }
                }
                //Going to the left, we were on a different level...
                else {
                    if (aNextGridZ != aGridZ) {
                        //We are on a flat crest between 2 ramps...
                        if (aNextGridZ == aPrevGridZ) {
                            AddStraight(aGridZ, aRightX, aCenterY, aLeftX, aCenterY);
                        } else {
                            if (aNextGridZ > aGridZ) {
                                AddHorizontalRamp(aGridZ, aRightX, aPrevCenterY, aLeftX, aCenterY);
                            } else {
                                AddHorizontalRamp(aGridZ, aRightX, aCenterY, aLeftX, aNextCenterY);
                            }
                        }
                        //We are on a ramp TO a ramp...
                    } else {
                        if (aPrevGridZ > aGridZ) {
                            //Here we just finished going down a ramp...
                            AddStraight(aGridZ, aRightX, aCenterY, aLeftX, aCenterY);
                        } else {
                            //Here we are going up a ramp...
                            AddHorizontalRamp(aGridZ, aRightX, aPrevCenterY, aLeftX, aCenterY);
                        }
                    }
                }
            }
        }

        //Increment path...
        aPrevGridX = aGridX;
        aPrevGridY = aGridY;
        aPrevGridZ = aGridZ;
        aGridX = aNextGridX;
        aGridY = aNextGridY;
        aGridZ = aNextGridZ;
    }
    GenerateTracks();
    GenerateTextureQuads();
}


void AnimatedGamePath::AddBend(int pDepth, float pStartX, float pStartY,
                               float pCenterX, float pCenterY,
                               float pEndX, float pEndY) {
    mPointList.Reset();
    float aStartDirX = pCenterX - pStartX;
    float aStartDirY = pCenterY - pStartY;
    float aStartLength = aStartDirX * aStartDirX + aStartDirY * aStartDirY;
    aStartLength = sqrtf(aStartLength);
    aStartDirX /= aStartLength;
    aStartDirY /= aStartLength;
    float aEndDirX = pEndX - pCenterX;
    float aEndDirY = pEndY - pCenterY;
    float aEndLength = aEndDirX * aEndDirX + aEndDirY * aEndDirY;
    aEndLength = sqrtf(aEndLength);
    aEndDirX /= aEndLength;
    aEndDirY /= aEndLength;
    float aInset = gPathBendInset45;
    float aKnot1X = pCenterX - aStartDirX * aInset;
    float aKnot1Y = pCenterY - aStartDirY * aInset;
    float aKnot2X = pCenterX + aEndDirX * aInset;
    float aKnot2Y = pCenterY + aEndDirY * aInset;
    float aStartNormX = aStartDirY;
    float aStartNormY = -aStartDirX;
    float aEndNormX = aEndDirY;
    float aEndNormY = -aEndDirX;
    float aLineLength = 300.0f;
    float aLine1X1 = aKnot1X - aStartNormX * aLineLength;
    float aLine1Y1 = aKnot1Y - aStartNormY * aLineLength;
    float aLine1X2 = aKnot1X + aStartNormX * aLineLength;
    float aLine1Y2 = aKnot1Y + aStartNormY * aLineLength;
    float aLine2X1 = aKnot2X - aEndNormX * aLineLength;
    float aLine2Y1 = aKnot2Y - aEndNormY * aLineLength;
    float aLine2X2 = aKnot2X + aEndNormX * aLineLength;
    float aLine2Y2 = aKnot2Y + aEndNormY * aLineLength;
    float aCircleCenterX = pCenterX;
    float aCircleCenterY = pCenterY;
    if (FLine::LineLineIntersection(aLine1X1, aLine1Y1, aLine1X2, aLine1Y2, aLine2X1, aLine2Y1, aLine2X2, aLine2Y2, aCircleCenterX, aCircleCenterY)) {
        float aSpokeDiffX = aCircleCenterX - aKnot1X;
        float aSpokeDiffY = aCircleCenterY - aKnot1Y;
        float aSpokeRadius = aSpokeDiffX * aSpokeDiffX + aSpokeDiffY * aSpokeDiffY;
        aSpokeRadius = sqrtf(aSpokeRadius);
        float aStartAngle = FaceTarget(aCircleCenterX, aCircleCenterY, aKnot1X, aKnot1Y);
        float aEndAngle = FaceTarget(aCircleCenterX, aCircleCenterY, aKnot2X, aKnot2Y);
        float aAngleDifference = aStartAngle - aEndAngle;
        if (aAngleDifference < 0) { aAngleDifference += 360.0f; }
        if (aAngleDifference > 180) {
            aAngleDifference = (360.0f - aAngleDifference);
        } else {
            aAngleDifference = -aAngleDifference;
        }
        mPointList.Add(pStartX, pStartY);
        mPointList.Add(aKnot1X, aKnot1Y);
        int aPointCount = 12;
        for (int i=1;i<aPointCount;i++) {
            float aPercent = ((float)i) / ((float)aPointCount);
            float aAngle = aStartAngle + aAngleDifference * aPercent;
            float aDirX = Sin(aAngle);
            float aDirY = -Cos(aAngle);
            float aX = aCircleCenterX + aSpokeRadius * aDirX;
            float aY = aCircleCenterY + aSpokeRadius * aDirY;
            mPointList.Add(aX, aY);
        }
        mPointList.Add(aKnot2X, aKnot2Y);
        mPointList.Add(pEndX, pEndY);
    }
    AppendPointListToPath(pDepth, 1.0f);
}

void AnimatedGamePath::AddStraight(int pDepth, float pStartX, float pStartY, float pEndX, float pEndY) {
    mPointList.Reset();
    float aDirX = pEndX - pStartX;
    float aDirY = pEndY - pStartY;
    float aDistance = aDirX * aDirX + aDirY * aDirY;
    aDistance = sqrtf(aDistance);
    aDirX /= aDistance;
    aDirY /= aDistance;
    mPointList.Add(pStartX, pStartY);
    int aPointCount = 8;
    for (int i=1;i<aPointCount;i++) {
        float aPercent = ((float)i) / ((float)aPointCount);
        float aScalar = aDistance * aPercent;
        float aX = pStartX + aScalar * aDirX;
        float aY = pStartY + aScalar * aDirY;
        mPointList.Add(aX, aY);
    }
    mPointList.Add(pEndX, pEndY);
    AppendPointListToPath(pDepth, 1.0f);
}

void AnimatedGamePath::AddHorizontalRamp(int pDepth, float pStartX, float pStartY, float pEndX, float pEndY) {

    mPointList.Reset();
    float aDirX = pEndX - pStartX;
    float aDirY = 0.0f;

    float aVerticalChange = pEndY - pStartY;

    float aDistance = aDirX;
    aDirX = 1.0f;

    if (aDistance < 0.0f) {
        aDistance = -aDistance;
        aDirX = -1.0f;
    }

    mPointList.Add(pStartX, pStartY);
    int aPointCount = 8;
    for (int i=1;i<aPointCount;i++) {
        float aPercent = ((float)i) / ((float)aPointCount);
        float aScalar = aDistance * aPercent;
        float aX = pStartX + aScalar * aDirX;
        float aY = pStartY + aVerticalChange * aPercent;
        mPointList.Add(aX, aY);
    }

    mPointList.Add(pEndX, pEndY);

    AppendPointListToPath(pDepth, 1.0f, aDirX, aDirY);
}

void AnimatedGamePath::AddVerticalRamp(int pDepth, float pUVWSpreadFactor, float pStartX, float pStartY, float pEndX, float pEndY) {

    mPointList.Reset();
    float aDirX = 0.0f;
    float aDirY = pEndY - pStartY;
    float aHorizontalChange = pEndX - pStartX;
    float aDistance = aDirY;
    aDirY = 1.0f;
    if (aDistance < 0.0f) {
        aDistance = -aDistance;
        aDirY = -1.0f;
    }
    mPointList.Add(pStartX, pStartY);
    int aPointCount = 8;
    for (int i=1;i<aPointCount;i++) {
        float aPercent = ((float)i) / ((float)aPointCount);
        float aScalar = aDistance * aPercent;
        float aX = pStartX + aHorizontalChange * aPercent;
        float aY = pStartY + aScalar * aDirY;
        mPointList.Add(aX, aY);
    }
    mPointList.Add(pEndX, pEndY);
    AppendPointListToPath(pDepth, pUVWSpreadFactor, aDirX, aDirY);
}

void AnimatedGamePath::AppendPointListToPath(int pDepth, float pUVWSpreadFactor) {
    if (mPointList.mCount < 2) {
        return;
    }

    AnimatedGamePathChunk *aChunk = (AnimatedGamePathChunk *)mPathChunkQueue.PopLast();
    if (aChunk == 0) { aChunk = new AnimatedGamePathChunk(); }
    mPathChunkList.Add(aChunk);
    aChunk->mDepth = pDepth;
    aChunk->mDistance = 0.0f;
    aChunk->mDemoIndexTimer = 0;
    aChunk->mDemoIndex = 0;

    //Start Node...
    AnimatedGamePathNode *aStartNode = ((AnimatedGamePathNode *)mPathNodeQueue.PopLast());
    if (aStartNode == 0) { aStartNode = new AnimatedGamePathNode(); }

    aChunk->mPathNodeList.Add(aStartNode);

    float aDirX = mPointList.mX[1] - mPointList.mX[0];
    float aDirY = mPointList.mY[1] - mPointList.mY[0];
    float aDist = aDirX * aDirX + aDirY * aDirY;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
        aDirX /= aDist;
        aDirY /= aDist;
    }
    aStartNode->mCenterX = mPointList.mX[0];
    aStartNode->mCenterY = mPointList.mY[0];
    aStartNode->mDirX = aDirX;
    aStartNode->mDirY = aDirY;
    aStartNode->mNormX = aDirY;
    aStartNode->mNormY = -aDirX;
    aStartNode->mDistanceFromPrevious = 0.0f;

    float aLength = 0.0f;
    for (int i=1;i<mPointList.mCount;i++) {
        AnimatedGamePathNode *aNode = ((AnimatedGamePathNode *)mPathNodeQueue.PopLast());
        if (aNode == 0) { aNode = new AnimatedGamePathNode(); }
        aChunk->mPathNodeList.Add(aNode);

        float aX = mPointList.mX[i];
        float aY = mPointList.mY[i];
        aDirX = aX - mPointList.mX[i-1];
        aDirY = aY - mPointList.mY[i-1];
        aDist = aDirX * aDirX + aDirY * aDirY;
        if (aDist > SQRT_EPSILON) {
            aDist = sqrtf(aDist);
            aDirX /= aDist;
            aDirY /= aDist;
        }

        aDist *= pUVWSpreadFactor;

        aNode->mCenterX = aX;
        aNode->mCenterY = aY;
        aNode->mDirX = aDirX;
        aNode->mDirY = aDirY;
        aNode->mNormX = aDirY;
        aNode->mNormY = -aDirX;
        aNode->mDistanceFromPrevious = aDist;

        aLength += aDist;
    }

    aChunk->mLength = aLength;
    EnumList(AnimatedGamePathNode, aNode, aChunk->mPathNodeList) {
        aNode->mX1 = aNode->mCenterX + aNode->mNormX * mPathWidth2;
        aNode->mY1 = aNode->mCenterY + aNode->mNormY * mPathWidth2;
        aNode->mX2 = aNode->mCenterX - aNode->mNormX * mPathWidth2;
        aNode->mY2 = aNode->mCenterY - aNode->mNormY * mPathWidth2;
        aNode->mTrack1X1 = aNode->mCenterX + aNode->mNormX * (mPathWidth2 + mTrackOffset);
        aNode->mTrack1Y1 = aNode->mCenterY + aNode->mNormY * (mPathWidth2 + mTrackOffset);
        aNode->mTrack1X2 = aNode->mCenterX + aNode->mNormX * (mPathWidth2 + mTrackOffset + mTrackWidth);
        aNode->mTrack1Y2 = aNode->mCenterY + aNode->mNormY * (mPathWidth2 + mTrackOffset + mTrackWidth);
        aNode->mTrack2X1 = aNode->mCenterX - aNode->mNormX * (mPathWidth2 + mTrackOffset);
        aNode->mTrack2Y1 = aNode->mCenterY - aNode->mNormY * (mPathWidth2 + mTrackOffset);
        aNode->mTrack2X2 = aNode->mCenterX - aNode->mNormX * (mPathWidth2 + mTrackOffset + mTrackWidth);
        aNode->mTrack2Y2 = aNode->mCenterY - aNode->mNormY * (mPathWidth2 + mTrackOffset + mTrackWidth);
    }
}

void AnimatedGamePath::AppendPointListToPath(int pDepth, float pUVWSpreadFactor, float pDirX, float pDirY) {
    if (mPointList.mCount < 2) {
        return;
    }

    AnimatedGamePathChunk *aChunk = (AnimatedGamePathChunk *)mPathChunkQueue.PopLast();
    if (aChunk == 0) { aChunk = new AnimatedGamePathChunk(); }
    mPathChunkList.Add(aChunk);
    aChunk->mDepth = pDepth;
    aChunk->mDistance = 0.0f;
    aChunk->mDemoIndexTimer = 0;
    aChunk->mDemoIndex = 0;
    //Start Node...
    AnimatedGamePathNode *aStartNode = ((AnimatedGamePathNode *)mPathNodeQueue.PopLast());
    if (aStartNode == 0) { aStartNode = new AnimatedGamePathNode(); }
    aChunk->mPathNodeList.Add(aStartNode);
    aStartNode->mCenterX = mPointList.mX[0];
    aStartNode->mCenterY = mPointList.mY[0];
    aStartNode->mDirX = pDirX;
    aStartNode->mDirY = pDirY;
    aStartNode->mNormX = pDirY;
    aStartNode->mNormY = -pDirX;
    aStartNode->mDistanceFromPrevious = 0.0f;
    float aLength = 0.0f;
    float aDist = 0.0f;
    float aDirX = 0.0f;
    float aDirY = 0.0f;
    for (int i=1;i<mPointList.mCount;i++) {
        AnimatedGamePathNode *aNode = ((AnimatedGamePathNode *)mPathNodeQueue.PopLast());
        if (aNode == 0) { aNode = new AnimatedGamePathNode(); }
        aChunk->mPathNodeList.Add(aNode);
        float aX = mPointList.mX[i];
        float aY = mPointList.mY[i];
        aDirX = aX - mPointList.mX[i-1];
        aDirY = aY - mPointList.mY[i-1];
        aDist = aDirX * aDirX + aDirY * aDirY;
        if (aDist > SQRT_EPSILON) {
            aDist = sqrtf(aDist);
        }
        aDist *= pUVWSpreadFactor;
        aNode->mCenterX = aX;
        aNode->mCenterY = aY;
        aNode->mDirX = pDirX;
        aNode->mDirY = pDirY;
        aNode->mNormX = pDirY;
        aNode->mNormY = -pDirX;
        aNode->mDistanceFromPrevious = aDist;
        aLength += aDist;
    }

    aChunk->mLength = aLength;
    EnumList(AnimatedGamePathNode, aNode, aChunk->mPathNodeList) {
        aNode->mX1 = aNode->mCenterX + aNode->mNormX * mPathWidth2;
        aNode->mY1 = aNode->mCenterY + aNode->mNormY * mPathWidth2;
        aNode->mX2 = aNode->mCenterX - aNode->mNormX * mPathWidth2;
        aNode->mY2 = aNode->mCenterY - aNode->mNormY * mPathWidth2;
        aNode->mTrack1X1 = aNode->mCenterX + aNode->mNormX * (mPathWidth2 + mTrackOffset);
        aNode->mTrack1Y1 = aNode->mCenterY + aNode->mNormY * (mPathWidth2 + mTrackOffset);
        aNode->mTrack1X2 = aNode->mCenterX + aNode->mNormX * (mPathWidth2 + mTrackOffset + mTrackWidth);
        aNode->mTrack1Y2 = aNode->mCenterY + aNode->mNormY * (mPathWidth2 + mTrackOffset + mTrackWidth);
        aNode->mTrack2X1 = aNode->mCenterX - aNode->mNormX * (mPathWidth2 + mTrackOffset);
        aNode->mTrack2Y1 = aNode->mCenterY - aNode->mNormY * (mPathWidth2 + mTrackOffset);
        aNode->mTrack2X2 = aNode->mCenterX - aNode->mNormX * (mPathWidth2 + mTrackOffset + mTrackWidth);
        aNode->mTrack2Y2 = aNode->mCenterY - aNode->mNormY * (mPathWidth2 + mTrackOffset + mTrackWidth);
    }
}

void AnimatedGamePath::GenerateTracks() {
    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {
        aChunk->mBufferTrack1.Reset();
        aChunk->mBufferTrack2.Reset();
        AnimatedGamePathNode *aPrevNode = (AnimatedGamePathNode *)aChunk->mPathNodeList.mData[0];
        float aPrevTrack1X1 = aPrevNode->mTrack1X1, aPrevTrack1Y1 = aPrevNode->mTrack1Y1;
        float aPrevTrack1X2 = aPrevNode->mTrack1X2, aPrevTrack1Y2 = aPrevNode->mTrack1Y2;
        float aPrevTrack2X1 = aPrevNode->mTrack2X1, aPrevTrack2Y1 = aPrevNode->mTrack2Y1;
        float aPrevTrack2X2 = aPrevNode->mTrack2X2, aPrevTrack2Y2 = aPrevNode->mTrack2Y2;
        float aTrack1X1 = aPrevTrack1X1, aTrack1Y1 = aPrevTrack1Y1, aTrack1X2 = aPrevTrack1X2, aTrack1Y2 = aPrevTrack1Y2;
        float aTrack2X1 = aPrevTrack2X1, aTrack2Y1 = aPrevTrack2Y1, aTrack2X2 = aPrevTrack2X2, aTrack2Y2 = aPrevTrack2Y2;
        for (int i=1;i<aChunk->mPathNodeList.mCount;i++) {
            AnimatedGamePathNode *aNode = (AnimatedGamePathNode *)aChunk->mPathNodeList.mData[i];
            aTrack1X1 = aNode->mTrack1X1; aTrack1Y1 = aNode->mTrack1Y1; aTrack1X2 = aNode->mTrack1X2; aTrack1Y2 = aNode->mTrack1Y2;
            aTrack2X1 = aNode->mTrack2X1; aTrack2Y1 = aNode->mTrack2Y1; aTrack2X2 = aNode->mTrack2X2; aTrack2Y2 = aNode->mTrack2Y2;
            aChunk->mBufferTrack1.Add(aPrevTrack1X2, aPrevTrack1Y2, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorOuter.mRed, mTrackColorOuter.mGreen, mTrackColorOuter.mBlue, mTrackColorOuter.mAlpha);
            aChunk->mBufferTrack1.Add(aPrevTrack1X1, aPrevTrack1Y1, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorInner.mRed, mTrackColorInner.mGreen, mTrackColorInner.mBlue, mTrackColorInner.mAlpha);
            aChunk->mBufferTrack1.Add(aTrack1X1, aTrack1Y1, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorInner.mRed, mTrackColorInner.mGreen, mTrackColorInner.mBlue, mTrackColorInner.mAlpha);
            aChunk->mBufferTrack1.Add(aTrack1X1, aTrack1Y1, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorInner.mRed, mTrackColorInner.mGreen, mTrackColorInner.mBlue, mTrackColorInner.mAlpha);
            aChunk->mBufferTrack1.Add(aTrack1X2, aTrack1Y2, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorOuter.mRed, mTrackColorOuter.mGreen, mTrackColorOuter.mBlue, mTrackColorOuter.mAlpha);
            aChunk->mBufferTrack1.Add(aPrevTrack1X2, aPrevTrack1Y2, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorOuter.mRed, mTrackColorOuter.mGreen, mTrackColorOuter.mBlue, mTrackColorOuter.mAlpha);
            aChunk->mBufferTrack2.Add(aTrack2X1, aTrack2Y1, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorInner.mRed, mTrackColorInner.mGreen, mTrackColorInner.mBlue, mTrackColorInner.mAlpha);
            aChunk->mBufferTrack2.Add(aPrevTrack2X1, aPrevTrack2Y1, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorInner.mRed, mTrackColorInner.mGreen, mTrackColorInner.mBlue, mTrackColorInner.mAlpha);
            aChunk->mBufferTrack2.Add(aPrevTrack2X2, aPrevTrack2Y2, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorOuter.mRed, mTrackColorOuter.mGreen, mTrackColorOuter.mBlue, mTrackColorOuter.mAlpha);
            aChunk->mBufferTrack2.Add(aPrevTrack2X2, aPrevTrack2Y2, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorOuter.mRed, mTrackColorOuter.mGreen, mTrackColorOuter.mBlue, mTrackColorOuter.mAlpha);
            aChunk->mBufferTrack2.Add(aTrack2X2, aTrack2Y2, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorOuter.mRed, mTrackColorOuter.mGreen, mTrackColorOuter.mBlue, mTrackColorOuter.mAlpha);
            aChunk->mBufferTrack2.Add(aTrack2X1, aTrack2Y1, 0.0f, 0.0f, 0.0f, 0.0f, mTrackColorInner.mRed, mTrackColorInner.mGreen, mTrackColorInner.mBlue, mTrackColorInner.mAlpha);
            aPrevTrack1X1 = aTrack1X1;aPrevTrack1Y1 = aTrack1Y1;aPrevTrack1X2 = aTrack1X2;aPrevTrack1Y2 = aTrack1Y2;
            aPrevTrack2X1 = aTrack2X1;aPrevTrack2Y1 = aTrack2Y1;aPrevTrack2X2 = aTrack2X2;aPrevTrack2Y2 = aTrack2Y2;
        }
    }
}

void AnimatedGamePath::GenerateTextureQuads() {
    float aTextureOffset = mTextureAnimationOffset;
    float aImageWidth = mPathWidth;
    float aLength = 0.0f;
    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {
        aChunk->mBufferMainPath.Reset();
        AnimatedGamePathNode *aPrevNode = (AnimatedGamePathNode *)aChunk->mPathNodeList.mData[0];
        float aPrevX1 = aPrevNode->mX1, aPrevY1 = aPrevNode->mY1;
        float aPrevX2 = aPrevNode->mX2, aPrevY2 = aPrevNode->mY2;
        float aPrevDist = aLength;// + aPrevNode->mDistanceFromPrevious;
        float aPrevU = (aPrevDist / aImageWidth) + aTextureOffset;
        float aX1 = aPrevX1, aY1 = aPrevY1, aX2 = aPrevX2, aY2 = aPrevY2;
        float aDist = aPrevDist;
        float aU = aPrevU;
        float aNodeDist = aLength;
        for (int i=1;i<aChunk->mPathNodeList.mCount;i++) {
            AnimatedGamePathNode *aNode = (AnimatedGamePathNode *)aChunk->mPathNodeList.mData[i];
            aNodeDist += aNode->mDistanceFromPrevious;
            aX1 = aNode->mX1; aY1 = aNode->mY1; aX2 = aNode->mX2; aY2 = aNode->mY2;
            //aDist = aLength + aNode->mDistanceFromPrevious;
            aU = (aNodeDist / aImageWidth) + aTextureOffset;
            aChunk->mBufferMainPath.Add(aPrevX1, aPrevY1, aPrevU, 0.0f);
            aChunk->mBufferMainPath.Add(aPrevX2, aPrevY2, aPrevU, 1.0f);
            aChunk->mBufferMainPath.Add(aX1, aY1, aU, 0.0f);
            aChunk->mBufferMainPath.Add(aX1, aY1, aU, 0.0f);
            aChunk->mBufferMainPath.Add(aPrevX2, aPrevY2, aPrevU, 1.0f);
            aChunk->mBufferMainPath.Add(aX2, aY2, aU, 1.0f);
            aPrevX1 = aX1;
            aPrevY1 = aY1;
            aPrevX2 = aX2;
            aPrevY2 = aY2;
            aPrevDist = aDist;
            aPrevU = aU;
        }
        aLength += aChunk->mLength;
    }
}
