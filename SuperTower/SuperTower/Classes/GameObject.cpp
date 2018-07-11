//
//  GameObject.cpp
//  Mustache
//
//  Created by Nick Raptis on 7/8/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "GameObject.h"
#include "GLApp.h"
#include "Game.h"

GameObject::GameObject() {
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    
    mDrawZ = -1;
    
    mGridX = -1;
    mGridY = -1;
    mGridZ = -1;
}

GameObject::~GameObject()
{
    
}


void GameObject::Update()
{
    
}

void GameObject::Draw()
{
    
}

void GameObject::SetUp(int pGridX, int pGridY)
{
    
    /*
    mX = (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
    mY = (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
    
    mGridX = pGridX;
    mGridY = pGridY;
    mGridZ = 1;
    mDrawZ = 1;
    */
    
    SetUp(pGridX, pGridY, 1);
}

void GameObject::SetUp(int pGridX, int pGridY, int pGridZ)
{
    mGridX = pGridX;
    mGridY = pGridY;
    mGridZ = pGridZ;
    mDrawZ = pGridZ;
    
    mX = CX(mGridX, mGridZ);
    mY = CY(mGridY, mGridZ);
}


