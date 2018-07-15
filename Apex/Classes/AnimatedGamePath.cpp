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

}

AnimatedGamePath::~AnimatedGamePath() {

}

void AnimatedGamePath::Update() {

}

void AnimatedGamePath::Draw() {
    GenerateQuads();



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
                    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.5f);
                    Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 4.0f);
                    Graphics::SetColor(0.85f, 0.15f, 0.15f, 0.5f);
                    Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 2.0f);
                } else {
                    Graphics::SetColor(0.25f, 0.25f, 0.25f, 0.45f);
                    Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 4.0f);
                    Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.4f);
                    Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 2.0f);
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

}

void AnimatedGamePath::ResetQuads() {

}

void AnimatedGamePath::GenerateQuads() {
    ResetQuads();
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
            Add45DegreeBend(aRightX, aBottomY, aCenterX, aCenterY, aCenterX, aTopY);
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
            Add45DegreeBend(aLeftX, aBottomY, aCenterX, aCenterY, aCenterX, aTopY);
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
            Add45DegreeBend(aCenterX, aBottomY, aCenterX, aCenterY, aLeftX, aTopY);
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
            Add45DegreeBend(aCenterX, aBottomY, aCenterX, aCenterY, aRightX, aTopY);
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
            Add45DegreeBend(aCenterX, aTopY, aCenterX, aCenterY, aRightX, aBottomY);
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
            Add45DegreeBend(aCenterX, aTopY, aCenterX, aCenterY, aLeftX, aBottomY);
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
            Add45DegreeBend(aLeftX, aTopY, aCenterX, aCenterY, aCenterX, aBottomY);
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
            Add45DegreeBend(aRightX, aTopY, aCenterX, aCenterY, aCenterX, aBottomY);
        }

        //float aCenterX = CX(aGridX, aGridZ);
        //float aCenterY = CY(aGridY, aGridZ);


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
}


void AnimatedGamePath::Add45DegreeBend(float pStartX, float pStartY,
                                       float pCenterX, float pCenterY,
                                       float pEndX, float pEndY) {


    mGeneratePointList.Reset();


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

    float aCollideX = pCenterX;
    float aCollideY = pCenterY;

    if (FLine::LineLineIntersection(aLine1X1, aLine1Y1, aLine1X2, aLine1Y2, aLine2X1, aLine2Y1, aLine2X2, aLine2Y2, aCollideX, aCollideY)) {
        float aSpokeDiffX = aCollideX - aKnot1X;
        float aSpokeDiffY = aCollideY - aKnot1Y;
        float aSpokeRadius = aSpokeDiffX * aSpokeDiffX + aSpokeDiffY * aSpokeDiffY;
        aSpokeRadius = sqrtf(aSpokeRadius);
        float aStartAngle = FaceTarget(aCollideX, aCollideY, aKnot1X, aKnot1Y);
        float aEndAngle = FaceTarget(aCollideX, aCollideY, aKnot2X, aKnot2Y);

        float aAngleDifference = aStartAngle - aEndAngle;

        if (aAngleDifference < 0) { aAngleDifference += 360.0f; }
        if (aAngleDifference > 180) {
            aAngleDifference = (360.0f - aAngleDifference);
        } else {
            aAngleDifference = -aAngleDifference;
        }

        mGeneratePointList.Add(pStartX, pStartY);
        mGeneratePointList.Add(aKnot1X, aKnot1Y);
        int aPointCount = 8;
        for (int i=1;i<aPointCount;i++) {
            float aPercent = ((float)i) / ((float)aPointCount);
            float aAngle = aStartAngle + aAngleDifference * aPercent;
            float aDirX = Sin(aAngle);
            float aDirY = -Cos(aAngle);
            float aX = aCollideX + aSpokeRadius * aDirX;
            float aY = aCollideY + aSpokeRadius * aDirY;
            mGeneratePointList.Add(aX, aY);
        }
        mGeneratePointList.Add(aKnot2X, aKnot2Y);
        mGeneratePointList.Add(pEndX, pEndY);

    } else {
        printf("FATAL ERROR, OUR SETUP IS FLAWED!!!\n\n");

    }

    float aLastX = mGeneratePointList.mX[0];
    float aLastY = mGeneratePointList.mY[0];

    float aX = 0.0f;
    float aY = 0.0f;
    for (int i=1;i<mGeneratePointList.mCount;i++) {
        Graphics::SetColor(((float)i) / ((float)(mGeneratePointList.mCount - 1)), 1.0f, 1.0f, 0.5f);
        aX = mGeneratePointList.mX[i];aY = mGeneratePointList.mY[i];
        Graphics::DrawLine(aLastX, aLastY, aX, aY, 0.25f);
        Graphics::DrawPoint(aX, aY, 1.0f);
        aLastX = aX;aLastY = aY;
    }
}
