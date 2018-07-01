//
//  TileMulti.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/2/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "TileMulti.h"
#include "GLApp.h"

TileMulti::TileMulti(){
    mMultiTile = true;
}

TileMulti::~TileMulti(){
    FreeList(TileMultiPart, mPartList);
}

void TileMulti::SetUp(int pGridX, int pGridY){
    Tile::SetUp(pGridX, pGridY);
    EnumList(TileMultiPart, aPart, mPartList){
        aPart->SetUp(mGridX + aPart->mGridOffsetX, mGridY + aPart->mGridOffsetY);
    }
}

void TileMulti::Draw()
{
    Tile *aLastTile = this;
    EnumList(TileMultiPart, aPart, mPartList){
        
        Graphics::DrawLine(mX, mY, aPart->mX, aPart->mY, 2.0f);
        Graphics::DrawLine(aPart->mX, aPart->mY, aLastTile->mX, aLastTile->mY);
        
        aLastTile = aPart;
    }
}

void TileMulti::AddPart(int pGridX, int pGridY){
    TileMultiPart *aPart = new TileMultiPart();
    
    aPart->mGridOffsetX = pGridX;
    aPart->mGridOffsetY = pGridY;
    aPart->mMultiParent = this;
    aPart->SetUp(mGridX + pGridX, mGridY + pGridY);
    
    mPartList.Add(aPart);
}
