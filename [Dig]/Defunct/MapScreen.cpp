//
//  MapScreen.cpp
//  CrossBone
//
//  Created by Nick Raptis on 6/30/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#include "MapScreen.h"
#include "core_includes.h"

MapScreen::MapScreen()
{
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    AddSubview(mMapScreenScrollContent);
    SetContentSize(mMapScreenScrollContent.GetWidth(), mMapScreenScrollContent.GetHeight());
    
    
}

MapScreen::~MapScreen()
{
    
}

void MapScreen::Update()
{
    
}

void MapScreen::Draw()
{
    
}