//
//  TileChainLink.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__TileChainLink__
#define ___015_Jeep_Arcon__TileChainLink__

#include "FObject.h"
#include "FSpline.h"

class TileChainLink : public FObject
{
public:
    
    TileChainLink(int pStartIndex, int pEndIndex);
    virtual ~TileChainLink();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    SetUp(float pStartX, float pStartY, float pEndX, float pEndY);
    
    void                                    PhaseOut();
    
    bool                                    mPhasing;
    float                                   mPhasePercent;
    
    float                                   mStartX;
    float                                   mStartY;
    
    float                                   mEndX;
    float                                   mEndY;
    
    float                                   mDirX;
    float                                   mDirY;
    
    float                                   mNormX;
    float                                   mNormY;
    
    int                                     mKnotCount;
    
    float                                   *mKnotControlX;
    float                                   *mKnotControlY;
    
    float                                   *mKnotSin;
    float                                   *mKnotSinSpeed;
    
    float                                   *mKnotShiftMagnitude;
    
    float                                   *mKnotShiftDirX;
    float                                   *mKnotShiftDirY;
    
    int                                     mStartIndex;
    int                                     mEndIndex;
    
    FSpline                                 mSpline;
    
    //TexSpline                               mStreamSpline;
    
};


#endif /* defined(___015_Jeep_Arcon__TileChainLink__) */
