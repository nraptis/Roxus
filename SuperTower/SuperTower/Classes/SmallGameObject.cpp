//
//  SmallGameObject.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/26/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "SmallGameObject.hpp"
#include "GLApp.h"
#include "GameArena.h"

SmallGameObject::SmallGameObject() {
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    mDrawZ = -1;
    mGridX = -1;
    mGridY = -1;
    mGridZ = -1;
}

SmallGameObject::~SmallGameObject() {

}

void SmallGameObject::Update() {

}

void SmallGameObject::Draw() {

}

void SmallGameObject::SetUp(int pGridX, int pGridY, int pGridZ) {
    mGridX = pGridX;
    mGridY = pGridY;
    mGridZ = pGridZ;
    mDrawZ = pGridZ;
    mX = gArena->GetUnitGridX(mGridX, mGridY, mGridZ);
    mY = gArena->GetUnitGridY(mGridX, mGridY, mGridZ);
}


