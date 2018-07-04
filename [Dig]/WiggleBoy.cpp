//
//  WiggleBoy.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "WiggleBoy.h"
#include "core_includes.h"
#include "MainApp.h"


WiggleBoy::WiggleBoy()
{
    //mX = 0.0f;
    //mY = 0.0f;
    
    //mScale = 1.0f;
    
    //mRotation = 0.0f;
    
    //mWidth = 16.0f;
    //mHeight = 16.0f;
    
    
    mTestSin1 = gRand.Rot();
    mTestSin2 = gRand.Rot();
    mTestSin3 = gRand.Rot();
    
    mTestRotMode = false;
    mTestRotTarget = 0.0f;
    
    
}

WiggleBoy::~WiggleBoy()
{
    
}

void WiggleBoy::Update()
{
    mTestSin1 += 2.5f;
    if(mTestSin1 >= 360.0f)mTestSin1 -= 360.0f;
    
    mTestSin2 += 0.15f;
    if(mTestSin2 >= 360.0f)mTestSin2 -= 360.0f;
    
    mTestSin3 += 4.265f;
    if(mTestSin3 >= 360.0f)mTestSin3 -= 360.0f;
    
    

    
    EnumList(WiggleBoyPart, aPart, mPartList)
    {
        if(aPart->mParent == 0)
        {
            aPart->Update(mX, mY, mScale, mRotation);
        }
    }
    
    
    /*
    if(gRand.Get(150) == 46)
    {
        mTestRotMode = (!mTestRotMode);
        mTestRotTarget = gRand.F(12.0f, 32.0f, true);
        
    }
    
    if(mTestRotMode == true)
    {
        mRotation *= 0.99f;
        
        if(mRotation > 0)
        {
            mRotation -= 0.01f;
            if(mRotation < 0.0f)mRotation = 0.0f;
        }
        else
        {
            mRotation += 0.01f;
            if(mRotation > 0.0f)mRotation = 0.0f;
        }
        
        //
        
        
    }
    else
    {
        mRotation += DistanceBetweenAngles(mRotation, mTestRotTarget) * 0.0025f;
    }
    
    */
    
}

void WiggleBoy::Draw()
{
    
    Graphics::BlendSetPremultiplied();
    
    EnumList(WiggleBoyPart, aPart, mPartList)
    {
        aPart->Draw();
    }
    
    GeoQuad aQuad;
    
    //float aRot = mRotation + Sin(mTestSin1) * 8.0f;
    //float aScale = mScale + Sin(mTestSin2) * 0.010f;
    
    
    
    aQuad.SetRect(-(mWidth / 2.0f), -(mHeight / 2.0f), mWidth, mHeight);
    aQuad.SetCenter();
    aQuad.Rotate(mRotation);
    aQuad.Scale(mScale);
    aQuad.Translate(mX, mY);
    
    
    
    //Graphics::SetColor(0.7f, 0.3f, 0.1f, 0.25f);
    //aQuad.DrawMarkers();
    
    //Graphics::SetColor(0.4f, 0.3f, 0.1f, 0.88f);
    //Graphics::DrawPoint(mX, mY, 10.0f);
    //Graphics::SetColor(0.3f, 0.6f, 0.9f);
    //Graphics::DrawLine(mX, mY, mX + Sin(aRot) * 32.0f, mY - Cos(aRot) * 32.0f);
    
    
    Graphics::BlendSetAlpha();
    
}


void WiggleBoy::SetSize(FSprite *pSprite)
{
    if(pSprite)
    {
        SetSize(pSprite->mWidth, pSprite->mHeight);
    }
}

void WiggleBoy::SetSize(float pWidth, float pHeight)
{
    mWidth = pWidth;
    mHeight = pHeight;
}

