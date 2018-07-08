/*
 *  Utils.cpp
 *  Fly Swatter
 *
 *  Created by Nick Raptis on 12/27/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "Utils.h"

FString RandomString(int pLength)
{
	if(pLength<0)pLength=0;
	
	char aPick[256]="abcdefghijklmnopqrstuvqxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";
	
	char *aChar=new char[pLength+1];
	aChar[pLength]=0;
	
	for(int i=0;i<pLength;i++)aChar[i]=aPick[gRand.Get(26+26+10)];
	
	FString aReturn=aChar;
	delete [] aChar;
	return aReturn;
}

FString Chop(FString pString, Font *pFont, int pWidth)
{
	
	FString aReturn=FString(pString);
	if(pFont->Width(aReturn)>pWidth)
	{
		aReturn += "...";
		while(pFont->Width(aReturn)>pWidth&&aReturn.mLength>3)
		{
			aReturn.Truncate(aReturn.mLength-4);
			aReturn += "...";
		}
	}
	
	
	return aReturn;
}

FString TicksToTime(int pTicks, int pUpdatesPerSecond)
{
	int aSec=(pTicks/pUpdatesPerSecond) % 60;
	int aMin=pTicks/(pUpdatesPerSecond*pUpdatesPerSecond);
	
	FString aSecString;
	aSecString.ParseInt(aSec);
	if(aSecString.mLength<2)
	{
		aSecString="0"+aSecString;
	}
	
	
	FString aMinString;
	aMinString.ParseInt(aMin);
	
	if(aMinString.mLength<2)
	{
		aMinString="0"+aMinString;
	}
	
	FString aReturn = aMinString + ":" + aSecString;
	return aReturn;
}
