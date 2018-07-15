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


    mPathWidth = 48.0f;
    mPathWidth2 = (mPathWidth / 2.0f);

    mTextureAnimationOffset = 0.0f;

    mSprite = &gApp->m1024x1024;
}

AnimatedGamePath::~AnimatedGamePath() {

}

void AnimatedGamePath::Update() {

    mTextureAnimationOffset += 0.0010f;
    if (mTextureAnimationOffset >= 1.0f) {
        mTextureAnimationOffset -= 1.0f;
    }
}

void AnimatedGamePath::Draw() {
    Generate();



    if (mEditorMode) {


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
        gApp->mUnitCircleHard.Center(aX1, aY1);
        gApp->mUnitCircleHard.Center(aX2, aY2);

        if (mSelected) {
            gApp->mUnitCircleSoft.Center(aX1, aY1);
            gApp->mUnitCircleSoft.Center(aX2, aY2);
        }
    }

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




}

void AnimatedGamePath::Reset() {

    //mPathNodeQueue
    
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
    for (int i=2;i<mLength-2;i++) {

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
            aNextGridY == aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aBottomY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Up
        // ---
        // -++
        // -+-
        if (aPrevGridX == aGridX &&
            aPrevGridY > aGridY &&
            aNextGridX > aGridX &&
            aNextGridY == aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aBottomY, aCenterX, aCenterY, aRightX, aCenterY);
        }


        // Left
        // -+-
        // ++-
        // ---
        if (aPrevGridX < aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX == aGridX &&
            aNextGridY < aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Left
        // ---
        // ++-
        // -+-
        if (aPrevGridX < aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX == aGridX &&
            aNextGridY > aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        // Right
        // -+-
        // -++
        // ---
        if (aPrevGridX > aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX == aGridX &&
            aNextGridY < aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Right
        // ---
        // -++
        // -+-
        if (aPrevGridX > aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX == aGridX &&
            aNextGridY > aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aCenterX, aBottomY);
        }


        // Down
        // -+-
        // ++-
        // ---
        if (aPrevGridX == aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX < aGridX &&
            aNextGridY == aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Down
        // -+-
        // -++
        // ---
        if (aPrevGridX == aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX > aGridX &&
            aNextGridY == aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aRightX, aCenterY);
        }

        // Left
        // --+
        // ++-
        // ---
        if (aPrevGridX > aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX < aGridX &&
            aNextGridY == aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aTopY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Left
        // ---
        // ++-
        // --+
        if (aPrevGridX > aGridX &&
            aPrevGridY > aGridY &&
            aNextGridX < aGridX &&
            aNextGridY == aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aBottomY, aCenterX, aCenterY, aLeftX, aCenterY);
        }

        // Left
        // +--
        // -++
        // ---
        if (aPrevGridX > aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX < aGridX &&
            aNextGridY < aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aLeftX, aTopY);
        }


        // Left
        // ---
        // -++
        // +--
        if (aPrevGridX > aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX < aGridX &&
            aNextGridY > aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aRightX, aCenterY, aCenterX, aCenterY, aLeftX, aBottomY);
        }

        // Right
        // --+
        // ++-
        // ---
        if (aPrevGridX < aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX > aGridX &&
            aNextGridY < aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aRightX, aTopY);
        }

        // Right
        // ---
        // ++-
        // --+
        if (aPrevGridX < aGridX &&
            aPrevGridY == aGridY &&
            aNextGridX > aGridX &&
            aNextGridY > aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aCenterY, aCenterX, aCenterY, aRightX, aBottomY);
        }

        // Right
        // +--
        // -++
        // ---
        if (aPrevGridX < aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX > aGridX &&
            aNextGridY == aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aTopY, aCenterX, aCenterY, aRightX, aCenterY);
        }


        // Right
        // ---
        // -++
        // +--
        if (aPrevGridX < aGridX &&
            aPrevGridY > aGridY &&
            aNextGridX > aGridX &&
            aNextGridY == aGridY
            ) {
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aBottomY, aCenterX, aCenterY, aRightX, aCenterY);
        }

        // Up
        // -+-
        // -+-
        // --+
        if (aPrevGridX > aGridX &&
            aPrevGridY > aGridY &&
            aNextGridX == aGridX &&
            aNextGridY < aGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aBottomY, aCenterX, aCenterY, aCenterX, aTopY);
        }

        // Up
        // -+-
        // -+-
        // +--

        if (aPrevGridX < aGridX &&
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
        if (aPrevGridX == aGridX &&
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
        if (aPrevGridX == aGridX &&
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
        if (aPrevGridX == aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX > aGridX &&
            aGridY < aNextGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aRightX, aBottomY);
        }

        // Down
        // -+-
        // -+-
        // +--
        if (aPrevGridX == aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX < aGridX &&
            aGridY < aNextGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aCenterX, aTopY, aCenterX, aCenterY, aLeftX, aBottomY);
        }

        // Down
        // +--
        // -+-
        // -+-
        if (aPrevGridX < aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX == aGridX &&
            aGridY < aNextGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aLeftX = aCenterX - gTileSize2;
            AddBend(aGridZ, aLeftX, aTopY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        // Down
        // --+
        // -+-
        // -+-
        if (aPrevGridX > aGridX &&
            aPrevGridY < aGridY &&
            aNextGridX == aGridX &&
            aGridY < aNextGridY
            ) {
            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;
            float aRightX = aCenterX + gTileSize2;
            AddBend(aGridZ, aRightX, aTopY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        //This is a vertical line...
        if (aNextGridX == aGridX && aPrevGridX == aGridX) {

            float aTopY = aCenterY - gTileSize2;
            float aBottomY = aCenterY + gTileSize2;

            //Graphics::DrawArrow(aCenterX, aTopY, aCenterX, aBottomY, 38.0f, 4.0f);


            //gTileSize2 = gTileSize * 0.5f;
            //gTileSize2 = gTileSize * 0.5f;

            //float aCenterX = CX(aGridX, aGridZ);
            //float aCenterY = CY(aGridY, aGridZ);

        } else if (aNextGridY == aGridY && aPrevGridY == aGridY) {

            float aLeftX = aCenterX - gTileSize2;
            float aRightX = aCenterX + gTileSize2;

            //Graphics::DrawArrow(aLeftX, aCenterY, aRightX, aCenterY, 38.0f, 4.0f);

        } else {
            //We have some type of Turn...


        }



        //Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.35f);
        //Graphics::DrawPoint(aCenterX, aCenterY, 14.0f);

        //Graphics::SetColor(0.25f, 0.065f, 0.065f, 1.0f);
        //Graphics::DrawPoint(aCenterX, aCenterY, 8.0f);

        aPrevGridX = aGridX;
        aPrevGridY = aGridY;
        aPrevGridZ = aGridZ;

        aGridX = aNextGridX;
        aGridY = aNextGridY;
        aGridZ = aNextGridZ;

    }

    GenerateTextureQuads();
    
}


void AnimatedGamePath::AddBend(int pDepth, float pStartX, float pStartY,
                                       float pCenterX, float pCenterY,
                                       float pEndX, float pEndY) {


    mPointList.Reset();


    //Graphics::SetColor(1.0f, 0.25f, 0.25f, 1.0f);
    //Graphics::DrawArrow(pStartX, pStartY, pCenterX, pCenterY);
    //Graphics::DrawArrow(pCenterX, pCenterY, pEndX, pEndY);


    float aStartDirX = pCenterX - pStartX;
    float aStartDirY = pCenterY - pStartY;
    //float aStartMagnitudeX = aStartDirX;
    //if (aStartMagnitudeX < 0.0f) { aStartMagnitudeX = -aStartMagnitudeX; }
    //float aStartMagnitudeY = aStartDirY;
    //if (aStartMagnitudeY < 0.0f) { aStartMagnitudeY = -aStartMagnitudeY; }
    float aStartLength = aStartDirX * aStartDirX + aStartDirY * aStartDirY;
    aStartLength = sqrtf(aStartLength);
    aStartDirX /= aStartLength;
    aStartDirY /= aStartLength;

    float aEndDirX = pEndX - pCenterX;
    float aEndDirY = pEndY - pCenterY;
    //float aEndMagnitudeX = aEndDirX;
    //if (aEndMagnitudeX < 0.0f) { aEndMagnitudeX = -aEndMagnitudeX; }
    //float aEndMagnitudeY = aEndDirY;
    //if (aEndMagnitudeY < 0.0f) { aEndMagnitudeY = -aEndMagnitudeY; }
    float aEndLength = aEndDirX * aEndDirX + aEndDirY * aEndDirY;
    aEndLength = sqrtf(aEndLength);
    aEndDirX /= aEndLength;
    aEndDirY /= aEndLength;

    float aInset = gPathBendInset45;

    float aKnot1X = pCenterX - aStartDirX * aInset;
    float aKnot1Y = pCenterY - aStartDirY * aInset;
    float aKnot2X = pCenterX + aEndDirX * aInset;
    float aKnot2Y = pCenterY + aEndDirY * aInset;

    /*
    Graphics::SetColor(0.125f, 0.35f, 0.89f, 0.87f);
    Graphics::DrawPoint(aKnot1X, aKnot1Y, 8.0f);

    Graphics::SetColor(1.0f, 0.35f, 0.89f, 0.87f);
    Graphics::DrawPoint(aKnot2X, aKnot2Y, 8.0f);

    Graphics::SetColor(0.125f, 0.95f, 0.225f, 0.8863f);
    Graphics::DrawLine(aKnot1X, aKnot1Y, aKnot2X, aKnot2Y);
    */

    float aStartNormX = aStartDirY;
    float aStartNormY = -aStartDirX;
    float aEndNormX = aEndDirY;
    float aEndNormY = -aEndDirX;


    float aLineLength = 300.0f;

    float aLine1X1 = aKnot1X - aStartNormX * aLineLength;
    float aLine1Y1 = aKnot1Y - aStartNormY * aLineLength;
    float aLine1X2 = aKnot1X + aStartNormX * aLineLength;
    float aLine1Y2 = aKnot1Y + aStartNormY * aLineLength;
    //Graphics::SetColor(0.125f, 0.35f, 0.89f, 0.87f);
    //Graphics::DrawLine(aLine1X1, aLine1Y1, aLine1X2, aLine1Y2);
    float aLine2X1 = aKnot2X - aEndNormX * aLineLength;
    float aLine2Y1 = aKnot2Y - aEndNormY * aLineLength;
    float aLine2X2 = aKnot2X + aEndNormX * aLineLength;
    float aLine2Y2 = aKnot2Y + aEndNormY * aLineLength;
    //Graphics::SetColor(0.125f, 1.0f, 0.45f, 0.87f);
    //Graphics::DrawLine(aLine2X1, aLine2Y1, aLine2X2, aLine2Y2);

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
        int aPointCount = 8;
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

    } else {
        printf("FATAL ERROR, OUR SETUP IS FLAWED!!!\n\n");
    }

    AppendPointListToPath(1.0f);

    /*
    float aLastX = mPointList.mX[0];
    float aLastY = mPointList.mY[0];

    float aX = 0.0f;
    float aY = 0.0f;
    for (int i=1;i<mPointList.mCount;i++) {
        Graphics::SetColor(((float)i) / ((float)(mPointList.mCount - 1)), 0.25f, 0.25f, 0.5f);
        aX = mPointList.mX[i];aY = mPointList.mY[i];
        Graphics::DrawLine(aLastX, aLastY, aX, aY, 0.25f);
        Graphics::DrawPoint(aX, aY, 1.0f);
        aLastX = aX;aLastY = aY;

        //gApp->mTile1.Center(aX, aY);
    }
    */
}

void AnimatedGamePath::AppendPointListToPath(int pDepth, float pUVWSpreadFactor) {

    if (mPointList.mCount < 2) {
        printf("FATAL ERROR, NEED MORE PTS!\n");
        return;
    }

    AnimatedGamePathChunk *aChunk = (AnimatedGamePathChunk *)mPathChunkQueue.PopLast();
    if (aChunk == 0) { aChunk = new AnimatedGamePathChunk(); }
    mPathChunkList.Add(aChunk);
    aChunk->mDepth = pDepth;
    aChunk->mDistance = 0.0f;



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
    }


    //mDistanceFromPrevious;
    //mDistance;




    //mPointList


    //FList                               mPathNodeList;
    //FList                               mPathNodeQueue;

    //AnimatedGamePathNode

    //mDrawNodeList


}

void AnimatedGamePath::GenerateTextureQuads() {

    float aTextureOffset = mTextureAnimationOffset;

    float aImageWidth = mPathWidth;

    int aTotalIndex = 0;
    float aLength = 0.0f;
    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {
        aChunk->mBuffer.Reset();
        AnimatedGamePathNode *aPrevNode = (AnimatedGamePathNode *)aChunk->mPathNodeList.mData[0];
        float aPrevX1 = aPrevNode->mX1, aPrevY1 = aPrevNode->mY1;
        float aPrevX2 = aPrevNode->mX2, aPrevY2 = aPrevNode->mY2;
        float aPrevDist = aLength + aPrevNode->mDistanceFromPrevious;
        float aPrevU = (aPrevDist / aImageWidth) + aTextureOffset;
        float aX1 = aPrevX1, aY1 = aPrevY1, aX2 = aPrevX2, aY2 = aPrevY2;
        float aDist = aPrevDist;
        float aU = aPrevU;

        float aNodeDist = aLength;
        for (int i=1;i<aChunk->mPathNodeList.mCount;i++) {

            AnimatedGamePathNode *aNode = (AnimatedGamePathNode *)aChunk->mPathNodeList.mData[i];

            aNodeDist += aNode->mDistanceFromPrevious;

            aX1 = aNode->mX1;
            aY1 = aNode->mY1;
            aX2 = aNode->mX2;
            aY2 = aNode->mY2;
            aDist = aLength + aNode->mDistanceFromPrevious;
            aU = (aNodeDist / aImageWidth) + aTextureOffset;

            aTotalIndex++;

            //aImageWidth

            //aChunk->mDrawNodeList.Add(aPrevX1, aPrevY1, aZ, aPrevU, 0.0f, aW, aR, aG, aB, aA);
            //aChunk->mDrawNodeList.Add(aPrevX2, aPrevY2, aZ, aPrevU, 1.0f, aW, aR, aG, aB, aA);
            //aChunk->mDrawNodeList.Add(aX1, aY1, aZ, aU, 0.0f, aW, aR, aG, aB, aA);
            
            aChunk->mBuffer.Add(aPrevX1, aPrevY1, aPrevU, 0.0f);
            aChunk->mBuffer.Add(aPrevX2, aPrevY2, aPrevU, 1.0f);
            aChunk->mBuffer.Add(aX1, aY1, aU, 0.0f);


            aChunk->mBuffer.Add(aX1, aY1, aU, 0.0f);
            aChunk->mBuffer.Add(aPrevX2, aPrevY2, aPrevU, 1.0f);
            aChunk->mBuffer.Add(aX2, aY2, aU, 1.0f);




            //FDrawNode aNode1;



            
            aPrevX1 = aX1;
            aPrevY1 = aY1;
            aPrevX2 = aX2;
            aPrevY2 = aY2;
            aPrevDist = aDist;
            aPrevU = aU;

            aPrevNode = aNode;
        }

        aLength += aChunk->mLength;
    }
    


    //Graphics::TextureBind(mSprite->mTexture->mBindIndex);
    //Graphics::TextureSetWrap();
    Graphics::CullFacesEnable();
    Graphics::CullFacesSetBack();
    //Graphics::TextureSetFilterLinear();
    //Graphics::TextureSetFilterNearest();




    FTextureRect aRect;
    aRect.SetRect(100.0f, 100.0f, 200.0f, 200.0f);
    aRect.SetUVQuad(0.0f, 0.0f, 2.0f, 2.0f);

    //pTextureRect->SetQuad(pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
    //pTextureRect->SetUVQuad(aStartU, aStartV, aEndU, aEndV);

    Graphics::SetColor();
    Graphics::DrawSprite(aRect.mVertex, aRect.mTextureCoord, mSprite->mTexture);

    mSprite->DrawQuadRect(300.0f, 100.0f, 200.0f, 200.0f);


    EnumList(AnimatedGamePathChunk, aChunk, mPathChunkList) {

        //aChunk->mDrawNodeList.Draw(mSprite);
        aChunk->mBuffer.SetTexture(mSprite->mTexture);
        aChunk->mBuffer.Draw();
        //aChunk->mDrawNodeList


    }

    Graphics::CullFacesDisable();
    Graphics::TextureSetClamp();

    //mPathWidth = 48.0f;
    //mPathWidth2 = (mPathWidth / 2.0f);



    
}
