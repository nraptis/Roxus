//
//  FObject.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FObject.h"
#include "core_includes.h"

FObject::FObject()
{
    mKill = 0;
}

FObject::~FObject()
{
    
}

void FObject::Kill()
{
    if(mKill == 0)
    {
        mKill = 5;
    }
}

FObjectList::FObjectList()
{
    
}

FObjectList::~FObjectList()
{
    Free();
}

void FObjectList::Add(void *pObject)
{
    if(pObject)
    {
        mObjectsAddedRecently.Add(pObject);
    }
}

void FObjectList::Free()
{
    FreeList(FObject, (*this));
    FreeList(FObject, mObjectsKillThisUpdate);
    FreeList(FObject, mObjectsKill);
    FreeList(FObject, mObjectsDelete);
    FreeList(FObject, mObjectsAddedRecently);
}

void FObjectList::Update()
{
    if(mObjectsAddedRecently.mCount > 0)
    {
        EnumList(FObject, aObject, mObjectsAddedRecently)
        {
            FList::Add(aObject);
            //mObjects.Add(aObject);
        }
        
        mObjectsAddedRecently.RemoveAll();
    }
    
    EnumList(FObject, aObject, (*this))
    {
        if(aObject->mKill == 0)
        {
            aObject->Update();
        }
        
        if(aObject->mKill)
        {
            mObjectsKillThisUpdate.Add(aObject);
        }
    }
    
    if(mObjectsKillThisUpdate.mCount > 0)
    {
        EnumList(FObject, aObject, mObjectsKillThisUpdate)
        {
            FList::Remove(aObject);
            //mObjects.Remove(aObject);
            mObjectsKill.Add(aObject);
        }
        
        mObjectsKillThisUpdate.RemoveAll();
    }
    
    EnumList(FObject, aObject, mObjectsKill)
    {
        aObject->mKill--;
        if(aObject->mKill <= 0)
        {
            mObjectsDelete.Add(aObject);
        }
    }
    
    if(mObjectsDelete.mCount > 0)
    {
        EnumList(FObject, aObject, mObjectsDelete)
        {
            mObjectsKill.Remove(aObject);
            delete aObject;
        }
    
        mObjectsDelete.RemoveAll();
    }
}

void FObjectList::Draw()
{
    EnumList(FObject, aObject, (*this))
    {
        if(aObject->mKill == false)
        {
            aObject->Draw();
        }
    }
}

void FObjectList::ClearRecentlyAdded()
{
	if(mObjectsAddedRecently.mCount > 0)
	{
		EnumList(FObject, aObject, mObjectsAddedRecently)
		{
			FList::Add(aObject);
			//mObjects.Add(aObject);
		}

		mObjectsAddedRecently.RemoveAll();
	}
}

void FObjectList::KillAll()
{
    EnumList(FObject, aObject, (*this))
    {
        aObject->Kill();
        mObjectsKill.Add(aObject);
    }
    RemoveAll();
    //mObjects.RemoveAll();
}









