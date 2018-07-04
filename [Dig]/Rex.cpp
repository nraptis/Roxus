//
//  Rex.cpp
//  Digplex
//
//  Created by Nick Raptis on 12/5/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "Rex.h"
#include "core_includes.h"
#include "MainApp.h"

RexPiece::RexPiece(FSprite &pSprite)
{
    mSprite = (&pSprite);
    
    mX = 0.0f;
    mY = 0.0f;
    
    mDrawX = 0.0f;
    mDrawY = 0.0f;
    
    mDrawScaleX = 1.0f;
    mDrawScaleY = 1.0f;
    
    mDrawRotation = 0.0f;
    mRotationOffset = 0;
    
    mRotationWobbler.SetInterval(-1.0f, 1.0f);
    mScaleWobbler.SetInterval(0.995f, 1.05f);
    mXWobbler.SetInterval(-0.25f, 0.25f);
    mYWobbler.SetInterval(-0.25f, 0.5f);
    mScaleYWobbler.SetInterval(0.995f, 1.004f);
}

RexPiece::~RexPiece()
{
    FreeList(RexPiece, mPiecesBack);
    FreeList(RexPiece, mPieces);
}

void RexPiece::Update()
{
    mRotationWobbler.Update();
    mScaleWobbler.Update();
    mXWobbler.Update();
    mYWobbler.Update();
    mScaleYWobbler.Update();
    
}


void RexPiece::ComputeDraw(FMatrix &pParentTransform)
{
    
    float aShiftX = mX + mXWobbler.V();
    float aShiftY = mY + mYWobbler.V();
    
    float aRotation = mRotationOffset + mRotationWobbler.V();
    
    float aScaleX = mScaleWobbler.V();
    float aScaleY = mScaleYWobbler.V() * mScaleWobbler.V();
    
    
    mTransform = pParentTransform;
    
    mTransform.Translate(aShiftX, aShiftY);
    mTransform.Scale(aScaleX, aScaleY, 1.0f);
    mTransform.Rotate(aRotation);
    
    
    EnumList(RexPiece, aPiece, mPiecesBack)aPiece->ComputeDraw(mTransform);
    EnumList(RexPiece, aPiece, mPieces)aPiece->ComputeDraw(mTransform);
    
    
}


void RexPiece::ComputeDraw(float pParentRotation, float pParentX, float pParentY, float pParentScaleX, float pParentScaleY)
{
    //The piece's stuff is going to be relevant to parent..
    
    //First we apply ouw own scales and shit
    
    float aRotation = pParentRotation + mRotationOffset + mRotationWobbler.V();
    
    float aScaleX = mScaleWobbler.V();
    float aScaleY = mScaleYWobbler.V() * mScaleWobbler.V();
    
    FVec2 aBase = PivotPoint(FVec2(mX, mY), (180.0f - aRotation) , FVec2(pParentX, pParentY), aScaleX, aScaleY);
    
    aBase += FVec2(pParentX, pParentY);
    
    mDrawX = aBase.mX;
    mDrawY = aBase.mY;
    
    mDrawRotation = aRotation;
    
    mDrawScaleX = aScaleX;
    mDrawScaleY = aScaleY;
    
    EnumList(RexPiece, aPiece, mPiecesBack)aPiece->ComputeDraw(mDrawRotation, mDrawX, mDrawY, mDrawScaleX, mDrawScaleY);
    EnumList(RexPiece, aPiece, mPieces)aPiece->ComputeDraw(mDrawRotation, mDrawX, mDrawY, mDrawScaleX, mDrawScaleY);
    
    //mScaleYWobbler
    
    
    
}

void RexPiece::Draw()
{
    EnumList(RexPiece, aPiece, mPiecesBack)
    {
        aPiece->Draw();
    }
    
    Graphics::SetMatrix(mTransform);
    mSprite->Draw();
    
    //mSprite->DrawScaled(mDrawX, mDrawY, mDrawScaleX, mDrawScaleY, mDrawRotation);
    
    EnumList(RexPiece, aPiece, mPieces)
    {
        aPiece->Draw();
    }
}

void RexPiece::DrawSelf()
{
    Graphics::SetMatrix(mTransform);
    mSprite->Draw();
}

void RexPiece::DrawPieces()
{
    Graphics::SetMatrix(mTransform);
    
    EnumList(RexPiece, aPiece, mPieces)
    {
        aPiece->Draw();
    }
}

/*
void RexPiece::Draw(float pX, float pY)
{
    
    EnumList(RexPiece, aPiece, mPiecesBack)
    {
        aPiece->Draw(mX + pX, mY + pY);
    }
    
    mSprite->Center(pX + mX, pY + mY);

    EnumList(RexPiece, aPiece, mPieces)
    {
        aPiece->Draw(mX + pX, mY + pY);
    }
}
*/

Rex::Rex()
{
    
    mSelectedPiece = 0;
    
    mSelectTouchX = 0.0f;
    mSelectTouchY = 0.0f;
    
    mSelectTouchPieceX = 0.0f;
    mSelectTouchPieceY = 0.0f;
    
    
    mX = 0.0f;
    mY = 0.0f;
    
    mWidth = (gApp->mTutorialRexCircle.mWidth);
    mHeight = (gApp->mTutorialRexCircle.mHeight);
    
    mWidth2 = (mWidth / 2.0f);
    mHeight2 = (mHeight / 2.0f);
    
    mPieceBackground= new RexPiece(gApp->mTutorialRexBackground);
    mPieceCircle= new RexPiece(gApp->mTutorialRexCircle);
    
    mPieceBody= new RexPiece(gApp->mTutorialRexBody);
    
    mPieceJawLower= new RexPiece(gApp->mTutorialRexJawLower);
    mPieceHeadBack= new RexPiece(gApp->mTutorialRexHeadBack);
    
    mPieceTooth[0] = new RexPiece(gApp->mTutorialRexTooth[0]);
    mPieceTooth[1] = new RexPiece(gApp->mTutorialRexTooth[1]);
    mPieceTooth[2] = new RexPiece(gApp->mTutorialRexTooth[2]);
    mPieceTooth[3] = new RexPiece(gApp->mTutorialRexTooth[3]);
    
    mPieceEye = new RexPiece(gApp->mTutorialRexEye);
    mPieceEyePupil = new RexPiece(gApp->mTutorialRexEyePupil);
    
    mPieceNoseSegment = new RexPiece(gApp->mTutorialRexNoseSegment);
    mPieceNose = new RexPiece(gApp->mTutorialRexNose);
    
    mPieceNostrilBack = new RexPiece(gApp->mTutorialRexNostrilBack);
    mPieceNostrilFront = new RexPiece(gApp->mTutorialRexNostrilFront);
    
    
    mPieceNose->mPiecesBack += mPieceTooth[0];
    mPieceNose->mPiecesBack += mPieceTooth[1];
    mPieceNose->mPiecesBack += mPieceTooth[2];
    mPieceNose->mPiecesBack += mPieceTooth[3];
    
    
    //mPieceNose->mX = 1.718781;mPieceNose->mY = -167.578064;
    mPieceJawLower->mX = 2.578125;mPieceJawLower->mY = -149.531250;
    mPieceBody->mX = 48.984375;mPieceBody->mY = 167.578125;
    
    mPieceEye->mX = 13.749969;mPieceEye->mY = -8.593811;
    mPieceEyePupil->mX = 5.156311;mPieceEyePupil->mY = -12.031311;
    
    mPieceNose->mX = -0.859344;mPieceNose->mY = -166.718704;
    
    mPieceHeadBack->mX = -2.578125;mPieceHeadBack->mY = -201.953125;
    mPieceNoseSegment->mX = -52.421875;mPieceNoseSegment->mY = -213.125000;
    mPieceNose->mX = 51.562531;mPieceNose->mY = 46.406296;
    mPieceNostrilBack->mX = -153.828156;mPieceNostrilBack->mY = -82.500046;
    mPieceNostrilFront->mX = -68.750031;mPieceNostrilFront->mY = -84.218796;
    
    
    mPieceBody->mPieces += mPieceJawLower;
    mPieceBody->mPieces += mPieceHeadBack;
    mPieceBody->mPieces += mPieceNoseSegment;
    
    
    mPieceNoseSegment->mPieces += mPieceNose;
    
    
    mPieceNose->mPiecesBack += mPieceNostrilBack;
    mPieceNose->mPieces += mPieceNostrilFront;
    

    mPieceHeadBack->mPieces += mPieceEye;
    mPieceEye->mPieces += mPieceEyePupil;
    
    mPieceTooth[0]->mX = -121.171936;mPieceTooth[0]->mY = 32.656250;
    mPieceTooth[1]->mX = -89.375000;mPieceTooth[1]->mY = 30.937347;
    mPieceTooth[2]->mX = -16.328217;mPieceTooth[2]->mY = 31.796783;
    mPieceTooth[3]->mX = -2.578186;mPieceTooth[3]->mY = 21.484222;

    mPieceTooth[0]->mScaleYWobbler.SetInterval(0.99f, 1.03f);
    mPieceTooth[1]->mScaleYWobbler.SetInterval(0.99f, 1.06f);
    
    mPieceTooth[2]->mScaleYWobbler.SetInterval(0.99f, 1.02f);
    
    mPieceJawLower->mRotationWobbler.SetInterval(-6.0f, 2.0f);
    mPieceJawLower->mRotationWobbler.SetTime(130, 40);
    
    mPieceNoseSegment->mXWobbler.SetInterval(-3.0f, 2.0f);
    mPieceHeadBack->mYWobbler.SetInterval(-2.0f, 5.0f);
    mPieceHeadBack->mYWobbler.SetTime(200);
    
}

Rex::~Rex()
{
    delete mPieceBody;
    mPieceBody = 0;
}

void Rex::Update()
{
    mPieceBody->Update();
}

void Rex::Draw()
{
    
    float aScale = 0.74f;
    
    float aShiftX = mWidth2 * aScale;
    float aShiftY = mHeight2 * aScale;
    
    Graphics::BlendSetPremultiplied();
    
    FMatrix aMatrix = Graphics::GetMatrixModelView();
    aMatrix.Translate(mX + aShiftX, mY + aShiftY);
    aMatrix.Scale(aScale);
    
    
    gApp->mTutorialRexBackground.Draw(mX + aShiftX, mY + aShiftY, aScale, 0.0f);
    Graphics::MatrixPush();
    mPieceBody->ComputeDraw(aMatrix);
    mPieceBody->DrawSelf();
    Graphics::MatrixPop();
    gApp->mTutorialRexCircle.Draw(mX + aShiftX, mY + aShiftY, aScale, 0.0f);
    Graphics::MatrixPush();
    mPieceBody->DrawPieces();
    Graphics::MatrixPop();
    
    Graphics::BlendSetAlpha();
    
}

