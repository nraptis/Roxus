//
//  Rex.h
//  Digplex
//
//  Created by Nick Raptis on 12/5/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__Rex__
#define __Digplex__Rex__

#include "FSprite.h"
#include "FObject.h"
#include "FMatrix.h"

class RexPiece
{
public:
    RexPiece(FSprite &pSprite);
    virtual ~RexPiece();
    
    void                                Update();
    
    
    
    void                                Draw();
    //void                                Draw(float pX, float pY);
    
    
    void                                DrawSelf();
    void                                DrawPieces();
    
    
    void                                ComputeDraw(float pParentRotation, float pParentX, float pParentY, float pParentScaleX, float pParentScaleY);
    
    void                                ComputeDraw(FMatrix &pParentTransform);
    
    
    
    FList                               mPiecesBack;
    
    FSprite                             *mSprite;
    
    FList                               mPieces;
    
    
    FMatrix                             mTransform;
    
    
    float                               mX;
    float                               mY;
    
    FWobbler                            mRotationWobbler;
    FWobbler                            mScaleWobbler;
    FWobbler                            mXWobbler;
    FWobbler                            mYWobbler;
    FWobbler                            mScaleYWobbler;
    
    float                               mDrawX;
    float                               mDrawY;
    float                               mDrawScaleX;
    float                               mDrawScaleY;
    float                               mDrawRotation;
    
    float                               mRotationOffset;
    
};

class Rex : public FObject //ComponentAnimation
{
public:
    Rex();
    virtual ~Rex();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    RexPiece                                *mSelectedPiece;
    
    float                                   mSelectTouchX;
    float                                   mSelectTouchY;
    
    float                                   mSelectTouchPieceX;
    float                                   mSelectTouchPieceY;
    
    
    //FList                                   mPieceList;
    
    float                                   mX;
    float                                   mY;
    
    float                                   mWidth;
    float                                   mHeight;
    
    float                                   mWidth2;
    float                                   mHeight2;
    
    RexPiece                                *mPieceBackground;
    RexPiece                                *mPieceCircle;
    
    RexPiece                                *mPieceBody;
    
    RexPiece                                *mPieceJawLower;
    RexPiece                                *mPieceHeadBack;
    
    RexPiece                                *mPieceTooth[4];
    
    RexPiece                                *mPieceEye;
    RexPiece                                *mPieceEyePupil;
    
    RexPiece                                *mPieceNoseSegment;
    RexPiece                                *mPieceNose;
    
    RexPiece                                *mPieceNostrilBack;
    RexPiece                                *mPieceNostrilFront;
    
};

#endif /* defined(__Digplex__Rex__) */
