//
//  MapScreenScrollContent.cpp
//  CrossBone
//
//  Created by Nick Raptis on 6/30/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#include "MapScreenScrollContent.h"
#include "MapScreenNode.h"
#include "FSpline.h"
#include "Game.h"
#include "core_includes.h"

MapScreenScrollContent::MapScreenScrollContent()
{
    
    SetFrame(0.0f, 0.0f, gAppWidth, 2200.0f);
    
    FSpline aSpline;
    
    mTouchNode = 0;
    
    aSpline.Add(100.0f, 140.0f);
    aSpline.Add(200.0f, 220.0f);
    aSpline.Add(140.0f, 260.0f);
    aSpline.Add(330.0f, 500.0f);
    aSpline.Add(200.0f, 800.0f);
    aSpline.Add(640.0f, 1320.0f);
    aSpline.Add(300.0f, 1560.0f);
    aSpline.Add(400.0f, 1950.0f);
    
    for(float aPos=0.0f;aPos<aSpline.Max();aPos+=1.0f)
    {
        float aX = aSpline.GetX(aPos);
        float aY = aSpline.GetY(aPos);
        
        MapScreenNode *aNode = new MapScreenNode();
        
        aNode->mCenterX = aX;
        aNode->mCenterY = aY * 2.225f;
        
        mNodeList += aNode;
    }
    
}

MapScreenScrollContent::~MapScreenScrollContent()
{
    
}

void MapScreenScrollContent::Update()
{
    EnumList(MapScreenNode, aNode, mNodeList)
    {
        aNode->Update();
    }
}

void MapScreenScrollContent::Draw()
{
    EnumList(MapScreenNode, aNode, mNodeList)
    {
        aNode->Draw();
    }
}

void MapScreenScrollContent::TouchDown(float pX, float pY, void *pData)
{
    if(mTouchNode)
    {
        mTouchNode->Deselect();
        mTouchNode = 0;
    }
    
    float aBestDistance = 80.0f * 80.0f;
    
    float aDiffX = 0.0f;
    float aDiffY = 0.0f;
    
    float aDist = 0.0f;
    
    float aX = pX;
    float aY = pY;
    
    EnumList(MapScreenNode, aNode, mNodeList)
    {
        //aNode->Update();
        
        aDiffX = aNode->mCenterX - aX;
        aDiffY = aNode->mCenterY - aY;
        
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist < aBestDistance)
        {
            aBestDistance = aDist;
            mTouchNode = aNode;
        }
    }
    
    if(mTouchNode)
    {
        mTouchNode->Select();
        
        
        
        
        //
    }
    
    //mTouchNode
    
}

void MapScreenScrollContent::TouchMove(float pX, float pY, void *pData)
{
    
}

void MapScreenScrollContent::TouchUp(float pX, float pY, void *pData)
{
    if(mTouchNode)
    {
        mTouchNode->Deselect();
        
        int aSelectedIndex = -1;
        int aCheckIndex = 0;
        
        EnumList(MapScreenNode, aNode, mNodeList)
        {
            if(aNode == mTouchNode)
            {
                aSelectedIndex = aCheckIndex;
            }
            aCheckIndex++;
        }
        
        printf("Selected Map Node = [%d]\n\n", aSelectedIndex);
        
        if(gApp->TransitionInProgress() == false)
        {
            gApp->TransitionTo(new Game(aSelectedIndex), 0, new Transition());
        }
        
        
        
        mTouchNode = 0;
    }
    
}

void MapScreenScrollContent::TouchFlush()
{
    
}



