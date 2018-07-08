/*
 *  Purchase.h
 *  Darts
 *
 *  Created by Nick Raptis on 12/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "stdafx.h"

class Purchase
{
public:
	Purchase();
	Purchase(FString pName, bool pConsumable=false);
	~Purchase();
	
	void					Print();
	
	void					Buy();
	
	FString					mName;
	
	//Consumable = true   : buy 50 gold.
	//Consumable = false  : upgrade to 'full version.'
	bool					mConsumable;
	
	int						mPurchaseCount;
	bool					mPurchased;
	
	virtual void			Load(Buffer *pBuffer);
	virtual void			Save(Buffer *pBuffer);	
	
};

class PurchaseManager
{
public:
	PurchaseManager();
	~PurchaseManager();
	
	virtual void			Load();
	virtual void			Save();
	
	void					Print();
	
	void					Buy(Purchase *pPurchase);
	bool					Buy(FString pName);
	bool					Exists(FString pName);
	
	List					mList;
};




