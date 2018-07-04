//
//  MapScreenNode.cpp
//  CrossBone
//
//  Created by Nick Raptis on 6/30/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#include "MapScreenNode.h"
#include "core_includes.h"

MapScreenNode::MapScreenNode()
{
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
    mComplete = false;
    
    mSelected = false;
    
    for(int i=0;i<3;i++)
    {
        mStarEarned[i] = false;
    }
    
}

MapScreenNode::~MapScreenNode()
{
    
}

void MapScreenNode::Update()
{
    
}

void MapScreenNode::Draw()
{
    if(mSelected)
    {
        Graphics::SetColor(1.0f, 0.0f, 0.5f);
        Graphics::DrawRect(mCenterX - 40.0f, mCenterY - 40.0f, 81.0f, 81.0f);
    }
    else
    {
        Graphics::SetColor(0.25f, 1.0f, 0.0f);
        Graphics::DrawRect(mCenterX - 40.0f, mCenterY - 40.0f, 81.0f, 81.0f);
    }
    
}

void MapScreenNode::Select()
{
    mSelected = true;
}

void MapScreenNode::Deselect()
{
    mSelected = false;
}

