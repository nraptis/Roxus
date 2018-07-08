/*
 *  Config.h
 *  Pony Suprise
 *
 *  Created by Nick Raptis on 12/28/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "stdafx.h"

class ConfigItem
{
public:
	int mData;
	FString mKey;
};

class Config
{
	
public:
	
	Config();
	
	~Config();
	
	bool				HasKey(FString pKey);
	//String				GetValue(FString pKey);
	
	int					ReadInt(FString pKey);
	float				ReadFloat(FString pKey);
	bool				ReadBool(FString pKey);
	
	void				WriteInt(FString pKey, int pValue);
	void				WriteFloat(FString pKey, float pValue);
	void				WriteBool(FString pKey, bool pValue);
	
	void				Save();
	
	List				mKeys;
};