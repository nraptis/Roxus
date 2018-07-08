/*
 *  Config.cpp
 *  Pony Suprise
 *
 *  Created by Nick Raptis on 12/28/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "Config.h"

Config::Config()
{
	Buffer aBuffer;
	aBuffer.Load("config.cfg");
	
	int aDataLen=aBuffer.mLength;
	char *aPtr=(char*)(aBuffer.mData);
	char *aShelf=&aPtr[aDataLen];
	
	while(aPtr<aShelf)
	{
		while(*aPtr<=32&&aPtr<aShelf)aPtr++;
		char *aNameStart=aPtr;
		while(*aPtr!=':'&&aPtr<aShelf)aPtr++;
		if(*aPtr==':')
		{
			FString aString;
			aString.Write((char*)aNameStart,0,aPtr-aNameStart);
			
			ConfigItem *aConfig=new ConfigItem();
			mKeys+=aConfig;
			
			aConfig->mKey.Write((char*)aNameStart,0,aPtr-aNameStart);

			aPtr++;
			
			aConfig->mData=(int)(*((int*)(aPtr)));
			
			aPtr+=4;
		}
		else
		{
			break;
		}
		aPtr++;
	}
}

Config::~Config()
{
	Save();
	FreeList(ConfigItem,mKeys);
}

bool Config::HasKey(FString pKey)
{
	EnumList(ConfigItem,aConfig,mKeys)
	{
		if(aConfig->mKey == pKey)
		{
			return true;
		}
	}
	return false;
}

void Config::WriteInt(FString pKey, int pValue)
{
	EnumList(ConfigItem,aConfig,mKeys)
	{
		if(aConfig->mKey == pKey)
		{
			aConfig->mData=pValue;
			return;
		}
	}
	ConfigItem *aNew=new ConfigItem();
	aNew->mKey=pKey;
	aNew->mData=pValue;
	mKeys+=aNew;
}

void Config::WriteFloat(FString pKey, float pValue)
{
	WriteInt(pKey, *((int*)(&pValue)));
}

void Config::WriteBool(FString pKey, bool pValue)
{
	WriteInt(pKey, (int)pValue);
}

int Config::ReadInt(FString pKey)
{
	EnumList(ConfigItem,aConfig,mKeys)
	{
		if(aConfig->mKey == pKey)
		{
			return aConfig->mData;
		}
	}
	return 0;
}

float Config::ReadFloat(FString pKey)
{
	int aRead=ReadInt(pKey);
	float aReturn=*((float*)(&aRead));
	return aReturn;
}

bool Config::ReadBool(FString pKey)
{
	return ReadInt(pKey)!=0;
}

void Config::Save()
{
	Buffer aBuffer;
	
	EnumList(ConfigItem,aItem,mKeys)
	{
		aBuffer.Write(aItem->mKey.c());
		aBuffer.WriteChar(':');
		aBuffer.WriteInt(aItem->mData);
		aBuffer.WriteChar('\n');
	}
	
	aBuffer.Save(gDocuments + "config.cfg");
}