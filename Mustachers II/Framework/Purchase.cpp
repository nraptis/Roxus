/*
 *  Purchase.cpp
 *  Darts
 *
 *  Created by Nick Raptis on 12/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Purchase.h"


Purchase::Purchase()
{
	mConsumable=false;
	mPurchaseCount=0;
	mPurchased=true;
}

Purchase::Purchase(FString pName, bool pConsumable)
{
	mConsumable=pConsumable;
	mName=pName;
}
	
Purchase::~Purchase()
{
	
}
	
void Purchase::Load(Buffer *pBuffer)
{
	if(pBuffer)
	{
		pBuffer->WriteString(mName.c());
		pBuffer->WriteInt(mPurchaseCount);
		pBuffer->WriteBool(mPurchased);
		pBuffer->WriteBool(mConsumable);
		
	}
}

void Purchase::Save(Buffer *pBuffer)
{
	if(pBuffer)
	{
		pBuffer->WriteString(mName.c());
		pBuffer->WriteInt(mPurchaseCount);
		pBuffer->WriteBool(mPurchased);
		pBuffer->WriteBool(mConsumable);
		
	}
}

void Purchase::Buy()
{
	mPurchased=true;
	mPurchaseCount++;
}

void Purchase::Print()
{
	
}

PurchaseManager::PurchaseManager()
{
	
}

PurchaseManager::~PurchaseManager()
{
	
}
	
void PurchaseManager::Load()
{
	Buffer aBuffer;
	aBuffer.Load(FString(gDocuments + FString("purchases.dat")).c());
	
	int aCount=aBuffer.ReadInt();
	for(int i=0;i<aCount;i++)
	{
		Purchase *aAchievement=new Purchase();
		aAchievement->Load(&aBuffer);
		mList+=aAchievement;
	}
}

void PurchaseManager::Save()
{
	Buffer aBuffer;
	aBuffer.WriteInt(mList.mCount);
	EnumList(Purchase, aAchievement, mList)
	{
		aAchievement->Save(&aBuffer);
	}
	aBuffer.Save(FString(gDocuments + FString("purchases.dat")).c());
}

void PurchaseManager::Buy(Purchase *pPurchase)
{
	if(pPurchase)
	{
		if(Exists(pPurchase->mName)==false)mList+=pPurchase;
		pPurchase->Buy();
		Save();
	}
}

bool PurchaseManager::Buy(FString pName)
{
	bool aFound=false;
	EnumList(Purchase, aPurchase, mList)
	{
		if(aPurchase->mName == pName)
		{
			Buy(aPurchase);
			aFound=true;
		}
	}
	if(!aFound)
	{
		Purchase *aPurchase = new Purchase(pName);
		Buy(aPurchase);
	}
	Save();
    return aFound;
}

bool PurchaseManager::Exists(FString pName)
{
	bool aReturn=false;
	EnumList(Purchase, aPurchase, mList)
	{
		if(aPurchase->mName == pName)aReturn=true;
	}
	return aReturn;
}

void PurchaseManager::Print()
{
	
}