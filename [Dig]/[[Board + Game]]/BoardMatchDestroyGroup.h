//
//  BoardMatchDestroyGroup.h
//  Digplex
//
//  Created by Nick Raptis on 9/23/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

//Some coffee right now sounds good.

#ifndef __Digplex__BoardMatchDestroyGroup__
#define __Digplex__BoardMatchDestroyGroup__

#include "BoardGenericMatch.h"
#include "GameTile.h"

class DestroyGroupCorner
{
public:
    
    DestroyGroupCorner();
    virtual ~DestroyGroupCorner();
    
    bool                                    mCornerTL;
    bool                                    mCornerTR;
    bool                                    mCornerBL;
    bool                                    mCornerBR;
    
    int                                     mGridX;
    int                                     mGridY;
    
};

class BoardMatchDestroyGroup : public BoardGenericMatch
{
public:
    
    BoardMatchDestroyGroup();
    virtual ~BoardMatchDestroyGroup();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    AddTile(GameTile *pTile);
    
    virtual void                            Compute(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY);
    
    int                                     mDestroyTimer;
    
    FList                                   mList;
    
    
    int                                     mComboType;
    int                                     mComboIndex;
    
    int                                     mScoreValue;
    
    
};


#endif /* defined(__Digplex__BoardMatchDestroyGroup__) */
