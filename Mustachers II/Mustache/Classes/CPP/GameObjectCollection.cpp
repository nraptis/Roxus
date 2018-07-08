//
//  GameObjectCollection.cpp
//  Mustache
//
//  Created by Nick Raptis on 9/17/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "GameObjectCollection.h"


GameObjectCollection::GameObjectCollection()
{
    mList = 0;
    mCount = 0;
    mSize = 0;
}

GameObjectCollection::~GameObjectCollection()
{
    
}

void GameObjectCollection::Update()
{
    GameObject *aObject = 0;
    //List aDeleteList;
    for(int i=0;i<mCount;i++)
    {
        aObject = mList[i];
        if(aObject->mKill == 0)
        {
            aObject->Update();
        } else {
            aObject->mKill--;
            if (aObject->mKill <= 0) {
                aDeleteList.Add(aObject);

            }
        }
    }
    for(int i=0;i<mCount;i++)
    {
        //aObject = (GameObject *)aDeleteList.mData[i];
    }

}

void GameObjectCollection::Draw()
{
    GameObject *aObject = 0;
    for(int i=0;i<mCount;i++)
    {
        aObject = mList[i];
        if(aObject->mKill == 0)
        {
            aObject->Draw();
        }
    }
}

void GameObjectCollection::AddObject(GameObject *pGameObject)
{
    if(mCount == mSize)
    {
        mSize = mCount + mCount / 2 + 1;
        
        GameObject **aList = new GameObject*[mSize];
        
        for(int i=0;i<mCount;i++)aList[i] = mList[i];
        
        delete [] mList;
        mList = aList;
    }
    
    mList[mCount] = pGameObject;
    mCount++;
}

void GameObjectCollection::SortAscendingY()
{
    
}
