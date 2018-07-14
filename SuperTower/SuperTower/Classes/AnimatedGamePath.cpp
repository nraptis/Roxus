//
//  AnimatedGamePath.cpp
//  Apex
//
//  Created by Raptis, Nicholas on 7/12/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "AnimatedGamePath.hpp"

AnimatedGamePath::AnimatedGamePath() {

}

AnimatedGamePath::~AnimatedGamePath() {

}

void AnimatedGamePath::Update() {

}

void AnimatedGamePath::Draw() {
    GenerateQuads();
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

    Graphics::SetColor(0.75f, 0.75f, 0.75f, 0.25f);

    for (int i=0;i<mLength;i++) {
        /*
        aGridX = mPathX[i];
        aGridY = mPathY[i];
        aGridZ = mPathZ[i];

        float aPreviousCenterX = CX(aPrevGridX, aPrevGridZ);
        float aPreviousCenterY = CY(aPrevGridY, aPrevGridZ);
        float aCenterX = CX(aGridX, aGridZ);
        float aCenterY = CY(aGridY, aGridZ);

        Graphics::DrawLine(aPreviousCenterX, aPreviousCenterY, aCenterX, aCenterY, 6.0f);

        aPrevGridX = aGridX;
        aPrevGridY = aGridY;
        aPrevGridZ = aGridZ;
        */
    }


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

        //This is a vertical line...
        if (aNextGridX == aGridX && aPrevGridX == aGridX) {

            //gTileWidth2 = gTileWidth * 0.5f;
            //gTileHeight2 = gTileHeight * 0.5f;

            //float aCenterX = CX(aGridX, aGridZ);
            //float aCenterY = CY(aGridY, aGridZ);

        } else if (aNextGridY == aGridY && aPrevGridY == aGridY) {

            float aLeftX = aCenterX - gTileWidth2;
            float aRightX = aCenterX + gTileWidth2;

            Graphics::DrawArrow(aLeftX, aCenterY, aRightX, aCenterY, 38.0f, 4.0f);


        } else {
            //We have some type of Turn...


        }



        Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.35f);
        Graphics::DrawPoint(aCenterX, aCenterY, 14.0f);

        Graphics::SetColor(0.25f, 0.065f, 0.065f, 1.0f);
        Graphics::DrawPoint(aCenterX, aCenterY, 8.0f);

        aPrevGridX = aGridX;
        aPrevGridY = aGridY;
        aPrevGridZ = aGridZ;

        aGridX = aNextGridX;
        aGridY = aNextGridY;
        aGridZ = aNextGridZ;

    }

}

