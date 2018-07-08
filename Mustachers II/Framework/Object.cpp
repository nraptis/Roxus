#include "Object.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	FreeList(Object,mPurgatory);
	FreeList(Object,mDelete);
}

void ObjectManager::Update()
{
	FreeList(Object,mPurgatory);
	EnumList(Object,aObject,mList)
	{
		aObject->Update();
		if(aObject->mKill)
		{
			mPurgatory+=aObject;
		}
	}
	mList-=mPurgatory;
}

void ObjectManager::Draw()
{
	EnumList(Object,aObject,mList)
	{
		aObject->Draw();
	}
}

void ObjectManager::Free()
{
	FreeList(Object,mList);
}


void ObjectManager::KillAll()
{
    EnumList(Object,aObject,mList)
	{
		aObject->Kill();
	}
}


