//
//  BoardGenericTile.h
//  Bone
//
//  Created by Nick Raptis on 8/6/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef __Bone__BoardGenericTile__
#define __Bone__BoardGenericTile__

#include "FObject.h"
#include "core_includes.h"

//#define TILE_MULTI_PART_MAX_COUNT 12

//class BoardGenericMultiTilePart;

class BoardGenericTile : public FObject
{
public:
    
    BoardGenericTile();
    virtual ~BoardGenericTile();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        SetUp(int pGridX, int pGridY, float pTileWidth, float pTileHeight);
    
    
    
    virtual bool                        CanReceiveDamage(int pDamageType);
    bool                                mCanReceiveDamage;
    
    virtual bool                        Damage(int pDamage);
    //virtual bool                        Damage(int pDamage, int pDamageType);
    
    
    int                                 mHP;
    
    
    virtual void                        Destroy(int pDestroyType, int pDestroyTime);
    int                                 mDestroyTimer;
    int                                 mDestroyTypeIndex;
    bool                                mDestroyed;
    bool                                mDestroyRealized;
    
    int                                 mTimerDelete;
    
    bool                                mInitialized;
    
    int                                 mGridX;
    int                                 mGridY;
    
    float                               mCenterX;
    float                               mCenterY;
    
    float                               mOffsetX;
    float                               mOffsetY;
    
    float                               mWidth;
    float                               mHeight;
    
    //Like, which type of tile is it? A matcher, a powerup, etc etc?
    int                                 mTileType;
    
    //We put this flag on everything..
    int                                 mMatchType;
    
    
    //**IMPORTANT**
    //Be sure to overload this for multi-tiles, with your base tile class...
    virtual BoardGenericTile            *SpawnPart();
    
    bool                                mMultiPart;
    int                                 mMultiPartGridOffsetX;
    int                                 mMultiPartGridOffsetY;
    BoardGenericTile                    *mMultiPartParent;
    
    
    bool                                mMulti;
    
    BoardGenericTile                    **mMultiPartList;
    int                                 mMultiPartCount;
    
    void                                AddPart(int pOffsetX, int pOffsetY);
    
    //bool                                mMultiPart;
    
    
};



#endif /* defined(__Bone__BoardGenericTile__) */
