//
//  BoardGenericLayer.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/15/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "BoardGenericLayer.h"


BoardGenericLayer::BoardGenericLayer()
{
    mName = "Unnamed Layer";
    
    mWidth = 0;
    mHeight = 0;
    
}

BoardGenericLayer::~BoardGenericLayer()
{
    
}

void BoardGenericLayer::Free()
{
    mWidth = 0;
    mHeight = 0;
}

void BoardGenericLayer::SetSize(int pGridWidth, int pGridHeight)
{
    mWidth = pGridWidth;
    mHeight = pGridHeight;
}

void BoardGenericLayer::Resize(int pGridWidth, int pGridHeight)
{
    mWidth = pGridWidth;
    mHeight = pGridHeight;
    
}
