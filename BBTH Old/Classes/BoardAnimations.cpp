//
//  BoardAnimations.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//



#include "BoardAnimations.hpp"
#include "GLApp.h"
#include "Board.h"
#include "FXML.h"

BoardAnimations::BoardAnimations(Board *pBoard){
    mBoard = pBoard;
}

BoardAnimations::~BoardAnimations(){
    
}

float BoardAnimations::CenterX(int pGridX){
    return mBoard->GetTileCenterX(pGridX);
}

float BoardAnimations::CenterY(int pGridY){
    return mBoard->GetTileCenterY(pGridY);
}

FParticle *BoardAnimations::GenerateSparkle()
{
    return GenerateSparkle(&(gApp->mEffectParticleWarm [gRand.Get(4)]));
}

FParticle *BoardAnimations::GenerateSparkle(FSprite *pSprite)
{
    FParticle *aReturn = new FParticle(pSprite);
    aReturn->SetPos(gRand.F(-6.0f, 6.0f), gRand.F(-6.0f, 6.0f));
    aReturn->mAlpha = 0.96f + gRand.F(0.2f);
    aReturn->mAlphaSpeed = 0.02f + gRand.F(0.005f);
    aReturn->mScale = 0.82f + gRand.F(0.04f);
    aReturn->mYSpeed = gRand.F(-0.3f, 2.6f);
    aReturn->mXSpeed = gRand.F(-1.33f, 1.33f);
    aReturn->mSpeedAccel = 0.940f;
    aReturn->mGravityY = 0.01f;
    aReturn->SetRRN(4.0f, 0.98f);
    aReturn->SetRotation();
    return aReturn;
}

FParticle *BoardAnimations::GenerateTwinkle()
{
    return GenerateTwinkle(&(gApp->mEffectTwinkleWhite[0]), 0.4f + gRand.GetFloat(0.2f));
}

FParticle *BoardAnimations::GenerateTwinkle(FSprite *pSprite, float pSpeed)
{
    FParticle *aReturn = new FParticle(pSprite);
    
    aReturn->SetPos(gRand.F(-6.0f, 6.0f), gRand.F(-6.0f, 6.0f));
    aReturn->SetRotation(-20.0f, -15.0f);
    aReturn->SetScale(0.05f);
    aReturn->mScaleSpeed = 0.20f + gRand.GetFloat(0.02f);
    aReturn->mScaleSpeedAdd = -0.0125f;
    aReturn->mRotationSpeed = gRand.GetFloat(0.5f) + 1.5f;
    
    //mAnimationsRelative.Add(aTwinkle);
    
    return aReturn;
}

