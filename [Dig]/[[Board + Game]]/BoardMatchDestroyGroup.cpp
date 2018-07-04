//
//  BoardMatchDestroyGroup.cpp
//  Digplex
//
//  Created by Nick Raptis on 9/23/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "BoardMatchDestroyGroup.h"

DestroyGroupCorner::DestroyGroupCorner()
{
    mCornerTL = false;
    mCornerTR = false;
    mCornerBL = false;
    mCornerBR = false;
    
    mGridX = 0;
    mGridY = 0;
    
}

DestroyGroupCorner::~DestroyGroupCorner()
{
    
}

//int                                     mGridX;
//int                                     mGridY;


BoardMatchDestroyGroup::BoardMatchDestroyGroup()
{
    mDestroyTimer = 0;
    
    mComboType = 0;
    mComboIndex = 0;
    
    mScoreValue = 0;
    
}

BoardMatchDestroyGroup::~BoardMatchDestroyGroup()
{
    
}

void BoardMatchDestroyGroup::Update()
{
    
}

void BoardMatchDestroyGroup::Draw()
{
    EnumList(GameTile, aTile, mList)
    {
        //Graphics::DrawPoint(aTile->mCenterX, aTile->mCenterY, 20.0f);
    }
}

void BoardMatchDestroyGroup::AddTile(GameTile *pTile)
{
    if(pTile)
    {
        mList += pTile;
        Add(pTile->mGridX, pTile->mGridY);
    }
}

void BoardMatchDestroyGroup::Compute(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY)
{
    BoardGenericMatch::Compute(pGridStartX, pGridStartY, pGridEndX, pGridEndY);
    
    EnumList(GameTile, aTile, mList)aTile->mDestroyTimer = 999;
    
    mDestroyTimer = 220;
}

