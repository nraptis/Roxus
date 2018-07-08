/*
 *  Font.cpp
 *  Word Master
 *
 *  Created by Nick Raptis on 6/26/10.
 *  Copyright 2010 Raptisoft LLC. All rights reserved.
 *
 */

#include "Font.h"
#include "Buffer.h"

Font::Font()
{
	mSpaceWidth=5;
	mLineHeight=0;
	mPadding=0;
}

Font::~Font()
{
	
}

void Font::LoadWithSplat(char *pFile)
{
	//Splat aSplat;
	//aSplat.Load(pFile);
	//Load(pFile);
	//aSplat.Kill();
}

void Font::Load(char *pFile)
{
	for(int i=0;i<256;i++)
	{
		for(int n=0;n<256;n++)
		{
			mLetter[i].mSpacing[n]=0;
		}
	}
	mLineHeight=0;
	Buffer aBuffer;
	aBuffer.Load(gSandbox + FString(pFile) + "_files.txt");
	if(aBuffer.mLength > 0)
	{
		unsigned char *aData=aBuffer.mData;
		unsigned char *aShelf=&aData[aBuffer.mLength];
		unsigned char *aPtr;
		while(aData<aShelf)
		{
			aPtr=aData;
			while(*aPtr>=32)aPtr++;
			*aPtr=0;
			mLetter[(unsigned int)(*aData)].mSprite.Load((char*)(aData+2));
			//printf("Char Width[%c]=%d\n", *aData, mLetter[(unsigned int)(*aData)].mSprite.mWidth);
			if(mLetter[(unsigned int)(*aData)].mSprite.mHeight>mLineHeight)
			{
				mLineHeight=mLetter[(unsigned int)(*aData)].mSprite.mHeight;
			}
			
			
			aData=aPtr+1;
			while(*aData && *aData<32)aData++;
		}
	}
	
	aBuffer.Load(gSandbox + FString(pFile) + "_kern.txt");
	if(aBuffer.mLength > 0)
	{
		char *aData=(char*)aBuffer.mData;
		char *aShelf=&aData[aBuffer.mLength-2];
		//char *aPtr;
		
		int aIndex1, aIndex2;
		char aShiftChar;
		int aShift;
		
		while(aData<aShelf)
		{
			aIndex1=(unsigned int)(*aData);
			aIndex2=(unsigned int)(*(aData+1));
			
			aShiftChar=*(aData+2);
			aShift=(int)aShiftChar;
			
			if(aShift & 0x0008)aShift|=0xFFF0;
			
			mLetter[(unsigned int)(*(aData))].mSpacing[(unsigned int)(*(aData+1))]=aShift;
			//*(aData+2) ? -(int)(aShift) : (int)aShift;
			
			//printf("Kern[%c - %c] = %d\n", (char)aIndex1, (char)aIndex2, aShift);
			
			aData+=3;
			while (*aData && *aData<=32)aData++;
			
		}
	}
}

float Font::Width(char *pString)
{
	float aReturn=0;
	if(pString)
	{
	while(*pString)
	{
		aReturn+=Spacing(pString);
		pString++;
	}
	}
	return aReturn;
}

float Font::Spacing(char pChar, char pNext)
{
	if(pChar<=' ')return mSpaceWidth;
	FontLetter *aLetter=&mLetter[(unsigned int)((unsigned char)(pChar))];
	return (float)(mPadding+aLetter->mSprite.mWidth+aLetter->mSpacing[(unsigned int)((unsigned char)(pNext))]);
}

void Font::Draw(char *pString, float x, float y)
{
	if(pString)
	{
		char *aPtr=pString;
		float aDrawX=x;
		float aDrawY=y;
		float aStartX=x;
		while(*aPtr)
		{
			
			if(*aPtr==' ')
			{
				aDrawX+=mSpaceWidth;
			}
			else if(*aPtr<' ')
			{
				aDrawY+=mLineHeight+30;
				aDrawX=aStartX;
			}
			else
			{
				Sprite *aSprite=&(mLetter[(unsigned int)((unsigned char)(*aPtr))].mSprite);
				aSprite->Draw(aDrawX,aDrawY);
				aDrawX+=Spacing(aPtr);
				//aSprite->mWidth+mPadding+mLetter[(unsigned int)((unsigned char)(*aPtr))].mSpacing[(unsigned int)((unsigned char)(*(aPtr+1)))];
			}
			
			aPtr++;
		}
	}
}

void Font::Center(char *pString, float x, float y)
{
	Draw(pString,x-Width(pString)/2,y);
}

void Font::Right(char *pString, float x, float y)
{
	Draw(pString,x-Width(pString),y);
}

int Font::LineCount(char *pString, float pWidth)
{
	int aLineHeight=0;
	if(pString)
	{
		char *aSeek=pString;
		while(*aSeek)aSeek++;
		int aStringLength=(int)(aSeek-pString);
		float aLength=0;
		aSeek=pString;
		while(*aSeek)
		{
			if(*aSeek<=' ')aLength+=mSpaceWidth;
			else aLength+=Spacing(*aSeek,*(aSeek+1));
			aSeek++;
		}
		if(aLength<=pWidth)aLineHeight=1;
		else
		{
			int aLineStart=0;
			int aSeekIndex=0;
			int aSpaceCount=0;
			int aSpaceIndex;
			while(aSeekIndex<aStringLength)
			{
				aSpaceCount=0;
				aLength=0;
				while(aSeekIndex<aStringLength && pString[aSeekIndex]<=' ')aSeekIndex++;
				aLineStart=aSeekIndex;
				while(aSeekIndex<aStringLength && aLength <= pWidth)
				{
					if(pString[aSeekIndex]<=' ')
					{
						aSpaceCount++;
						aLength+=mSpaceWidth;
					}
					else
					{
						aLength+=mLetter[pString[aSeekIndex]].mSprite.mWidth
						+mPadding+mLetter[pString[aSeekIndex]].
						mSpacing[pString[aSeekIndex+1]];
					}
					aSeekIndex++;
				}
				if(aSeekIndex>aLineStart && aSeekIndex < aStringLength)
				{
					aSpaceCount=0;
					for(int i=aLineStart;i<aSeekIndex;i++)if(pString[i]<=' ')aSpaceCount++;
					aSeekIndex--;
					if(aSeekIndex>aLineStart)
					{
						if(aSpaceCount>0)
						{
							aSpaceIndex=aSeekIndex;
							while(pString[aSpaceIndex]>' ')
							{
								aSpaceIndex--;
							}
							aSeekIndex=aSpaceIndex+1;
						}
					}
				}
				if(aSeekIndex<=aLineStart)aSeekIndex++;
				aLineHeight++;
			}
		}		
	}
	return aLineHeight;
}

void Font::Draw(char *pString, float x, float y, float pWidth)
{
	if(pString)
	{
		char *aSeek=pString;
		while(*aSeek)aSeek++;
		int aStringLength=(int)(aSeek-pString);
		float aLength=0;
		aSeek=pString;
		while(*aSeek)
		{
			if(*aSeek<=' ')aLength+=mSpaceWidth;
			else aLength+=Spacing(*aSeek,*(aSeek+1));
			aSeek++;
		}
		if(aLength<=pWidth)Draw(pString,x,y);
		else
		{
			char *aBuffer=new char[aStringLength+1];
			float aDrawY=y;
			int aLineStart=0;
			int aSeekIndex=0;
			int aSpaceCount=0;
			int aBufferIndex=0;
			int aSpaceIndex;
			while(aSeekIndex<aStringLength)
			{
				aSpaceCount=0;
				aLength=0;
				aBufferIndex=0;
				while(aSeekIndex<aStringLength && pString[aSeekIndex]<=' ')aSeekIndex++;
				aLineStart=aSeekIndex;
				while(aSeekIndex<aStringLength && aLength <= pWidth)
				{
					aBuffer[aBufferIndex]=pString[aSeekIndex];
					aBufferIndex++;
					if(pString[aSeekIndex]<=' ')
					{
						aSpaceCount++;
						aLength+=mSpaceWidth;
					}
					else
					{
						aLength+=mLetter[pString[aSeekIndex]].mSprite.mWidth
						+mPadding+mLetter[pString[aSeekIndex]].
						mSpacing[pString[aSeekIndex+1]];
					}
					aSeekIndex++;
				}
				aBuffer[aBufferIndex]=0;
				if(aSeekIndex>aLineStart && aSeekIndex < aStringLength)
				{
					aSpaceCount=0;
					for(int i=aLineStart;i<aSeekIndex;i++)if(pString[i]<=' ')aSpaceCount++;
					aSeekIndex--;
					if(aSeekIndex>aLineStart)
					{
						if(aSpaceCount>0)
						{
							aSpaceIndex=aSeekIndex;
							while(pString[aSpaceIndex]>' ')
							{
								aBufferIndex--;
								aBuffer[aBufferIndex]=0;
								aSpaceIndex--;
							}
							aSeekIndex=aSpaceIndex+1;
						}
						else
						{
							aBuffer[aBufferIndex-1]=0;
						}
					}
				}
				if(aSeekIndex<=aLineStart)aSeekIndex++;
				Draw(aBuffer,x,aDrawY);
				aDrawY+=mLineHeight;
			}
		}		
	}
}