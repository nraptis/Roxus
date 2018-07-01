//
//  Tile.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/12/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#ifndef TILE_H
#define TILE_H


#define TILE_TYPE_UNKNOWN -1
#define TILE_TYPE_EGG 1
#define TILE_TYPE_ROCK 2


#include "FObject.h"

class Tile
{
public:
    Tile();
    virtual ~Tile();
    
    virtual void                            Update();
    
    virtual void                            Draw();
    
    virtual void                            DrawBuried();
    
    virtual void                            DrawEffectsUnder(int pDepth);
    virtual void                            DrawEffectsOver(int pDepth);
    
    virtual void                            Matched(){mMatched = true;}
    
    
    int                                     mType;
    
    virtual void                            SetUp(int pGridX, int pGridY);
    
    int                                     mGridX;
    int                                     mGridY;
    
    float                                   mX;
    float                                   mY;
    
    virtual void                            Kill(){mKill = 8;}
    int                                     mKill;
    
    bool                                    mMatched;
    bool                                    mSelected;
    
    
    void                                    FallTo(int pGridY);
    
    float                                   mFallTargetY;
    float                                   mFallSpeed;
    bool                                    mFalling;
    
    
    //casting to multi / multi-parts.
    bool                                    mMultiTile;
    bool                                    mMultiTilePart;
    
    
    //Newly generated tiles that have not been
    //checked for possible matches yet...
    bool                                    mNew;
    
    
    
    void                                    FlagReset(){mFlag1=false;mFlag2=false;mFlagU=false;mFlagR=false;mFlagD=false;mFlagL=false;}
    
    bool                                    mFlag1;
    bool                                    mFlag2;
    
    bool                                    mFlagU;
    bool                                    mFlagR;
    bool                                    mFlagD;
    bool                                    mFlagL;
    
    
};


#endif /* Tile_hpp */
