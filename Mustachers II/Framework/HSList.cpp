/*
 *  HSList.cpp
 *  GetLucky
 *
 *  Created by Nick Raptis on 8/10/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "HSList.h"
#include "stdafx.h"

HSList::HSList()
{
	mName=0;
	mScore=0;
	mSize=0;
	mRecent=0;
	Size(5);
}

HSList::~HSList()
{
	Clear();
}

void HSList::Clear()
{
	for(int i=0;i<mSize;i++)
	{
		delete []mName[i];
	}
	delete[]mName;
	delete[]mScore;
	mName=0;
	mScore=0;
	mSize=0;
	mRecent=0;
	
}

void HSList::Add(char *name, int score)
{
	if(!name)return;
	
	if(mSize<1)Size(10);
	
	
	mRecent=-1;
	
	char *aStart=name;
	char *aEnd=aStart;
	while(*aEnd)aEnd++;
    
	char *aPtr=name;
	while(*aPtr)aPtr++;
	int aLen=aPtr-name;
	if(aLen<=0)return;
	
	if(score>=mScore[mSize-1])
	{
		for(int i=0;i<mSize;i++)
		{
			if(mScore[i]<=score)
			{
				mRecent=i;
				
				delete mName[mSize-1];
				
				for(int k=mSize-1;k>i;k--)
				{
					mName[k]=mName[k-1];
					mScore[k]=mScore[k-1];
				}
				
				char *aName=new char[aLen+1];
				aName[aLen]=0;
				
				aPtr=aName;
				while(aStart<aEnd)
				{
					*aPtr=*aStart;
					aStart++;
					aPtr++;
				}
				
				mScore[i]=score;
				mName[i]=aName;
				
				return;
			}
		}
	}
	
}

bool HSList::Exists(char *name)
{
	char *aPtr1, *aPtr2;
	
	
	for(int i=0;i<mSize;i++)
	{
		if(mName[i])
		{
			aPtr1=name;
			aPtr2=mName[i];
			
			while(*aPtr1&&*aPtr2&&*aPtr1==*aPtr2)
			{
				aPtr1++;
				aPtr2++;
			}
			
			if(*aPtr1==*aPtr2)return true;
			
		}
	}
	
	
	return false;
}

void HSList::Size(int size)
{
	Clear();
	if(size>0)
	{
		mSize=size;
		mName=new char*[mSize];
		mScore=new int[mSize];
		
		for(int i=0;i<mSize;i++)
		{
			mName[i]=0;
			mScore[i]=0;
		}
		
	}
}


void HSList::Save(FString theString)
{
	Buffer aBuffer;
	
	for(int i=0;i<mSize;i++)
	{
		if(mName[i])
		{
			aBuffer.WriteBool(true);
			
			
			int aStrlen=strlen(mName[i]);
            
			aBuffer.WriteInt(aStrlen);
			
			for(int n=0;n<aStrlen;n++)
			{
				aBuffer.WriteChar(mName[i][n]);
			}
			
			aBuffer.WriteInt(mScore[i]);
			
		}
		else
		{
			aBuffer.WriteBool(false);
		}
	}
	aBuffer.Save(theString);
}

void HSList::Load(FString theString)
{
	//Size(10);
	
	Buffer aBuffer;
	aBuffer.Load(theString);
	
	for(int i=0;i<mSize;i++)
	{
		if(aBuffer.ReadBool())
		{
			int aStrlen=aBuffer.ReadInt();
			
			delete[]mName[i];
			
			char *aChar=new char[aStrlen+1];
			aChar[aStrlen]=0;
			
			for(int n=0;n<aStrlen;n++)
			{
				aChar[n]=aBuffer.ReadChar();
			}
			
			mScore[i]=aBuffer.ReadInt();
			mName[i]=aChar;
		}
		else
		{
			
		}
		
	}
}

int HSList::GetHighestScore(char *pName)
{
	
	int aReturn=0;
	
	for(int i=0;i<mSize;i++)
	{
		if(FString(mName[i]) == pName)
		{
			aReturn = mScore[i];
			break;
		}
	}
	
	return aReturn;
}

int HSList::GetHighestScore()
{
    int aReturn=0;
    
    for(int i=0;(i<mSize) && (aReturn==0);i++)
    {
        if(FString(mName[i]) != "-")
        {
            if(mScore[i] > aReturn)
            {
                aReturn=mScore[i];
            }
        }
    }
    
    return aReturn;
}

void HSList::PadScore(int pScore)
{
	int aExists=false;
	for(int i=0;i<mSize;i++)
	{
		if(mScore[i]==pScore)aExists=true;
	}
	
	if(aExists==false)
	{
		Add("-", pScore);
	}
}

int HSList::NewScoreIndex(int theScore)
{
	for(int i=0;i<mSize;i++)
	{
		if(mScore[i]<=theScore)return i;
	}
	return -1;
}

void HSList::Print()
{
	for(int i=0;i<mSize;i++)
	{
		if(mName[i])
		{
			printf("Score[%d] {%s} -- %d [%d]\n", i, mName[i], mScore[i], mRecent == i);
		}
	}
}
