//
//  FontDraw.cpp
//  CrazyDartsArc
//
//  Created by Nick Raptis on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "FontDraw.h"

FontDraw::FontDraw()
{
    mData = 0;
    mSize = 0;
    mWriteIndex = 0;
    
    for(int i=0;i<256;i++)
    {
        mSpacingBefore[i]=0;
        mSpacingAfter[i]=0;
    }
    
    mVerticalHeight=0.0f;
    mVerticalSpacing=5.0f;
    
    mMaxWidth = 0.0f;
    mMaxHeight = 0.0f;
    
}

FontDraw::~FontDraw()
{
    
}

void FontDraw::Reset()
{
    mWriteIndex=0;
    if(mData)mData[0]=0;
}

void FontDraw::LoadRange(char pStart, char pEnd, const char *pFilePrefix)
{
    
    int aStart = (int)((unsigned char)pStart);
    int aEnd = (int)((unsigned char)pEnd);
    
    if(aStart > aEnd)
    {
        int aHold=aStart;
        aStart=aEnd;
        aEnd=aHold;
    }
    
    for(int i=aStart;i<=aEnd;i++)
    {
        FString aCharString = FString((char)i);
        FString aPathString = FString(pFilePrefix) + aCharString;
        
        mSprite[i].Load(aPathString.c());
        
        if(mSprite[i].mWidth > mMaxWidth)mMaxWidth = mSprite[i].mWidth;
        if(mSprite[i].mHeight > mMaxHeight)mMaxHeight = mSprite[i].mHeight;
    }
    
    if(mPrefix.mLength == 0)mPrefix = pFilePrefix;
}

void FontDraw::Load(char *pCharacters, const char *pFilePrefix)
{
    
    if(pFilePrefix == 0)pFilePrefix = mPrefix.c();
    
    FString aPrefixString = FString(pFilePrefix);
    FString aPath;
    
    int aIndex = 0;
    
    if(pCharacters)
    {
        while(*pCharacters)
        {
            aPath = FString(aPrefixString.c()) + FString((*pCharacters));
            aIndex = (int)((unsigned char)(*pCharacters));
            
            mSprite[aIndex].Load(aPath);
            
            if(mSprite[aIndex].mWidth <= 0)
            {
                aPath = FString(aPrefixString.c()) + FString(aIndex);
                mSprite[aIndex].Load(aPath);
            }
            
            if(mSprite[aIndex].mWidth > mMaxWidth)mMaxWidth = mSprite[aIndex].mWidth;
            if(mSprite[aIndex].mHeight > mMaxHeight)mMaxHeight = mSprite[aIndex].mHeight;
            
            //printf("Loaded[%d] ==> [%d x %d]\n", aIndex, mSprite[aIndex].mWidth, mSprite[aIndex].mHeight);
            
            pCharacters++;
        }
    }
    
    
}


void FontDraw::LoadAlphaNumeric(const char *pFilePrefix)
{
    LoadRange('a', 'z', pFilePrefix);
    LoadRange('A', 'Z', pFilePrefix);
    LoadRange('0', '9', pFilePrefix);
}

void FontDraw::Write(const char *pText)
{
    
    if(pText)
    {
        const char*aPtr=pText;
        while(*aPtr)aPtr++;
        int aLength = (int)(aPtr-pText);
        
        if(aLength > 0)
        {
            PadLength(aLength);
            while(*pText)
            {
                mData[mWriteIndex] = *pText;
                pText++;
                mWriteIndex++;
            }
            mData[mWriteIndex]=0;
        }
    }
}

void FontDraw::PadLength(int pLengthPad)
{
    int aLength = mWriteIndex + pLengthPad;
    
    if(aLength >= mSize)
    {
        mSize = mSize + aLength;
        mSize = mSize + (mSize / 2) + 1;
        
        char *aNew = new char[mSize];
        for(int i=0;i<mWriteIndex;i++)
        {
            aNew[i] = mData[i];
        }
        
        delete [] mData;
        mData = aNew;
        
        mData[mWriteIndex] = 0;
    }
}

static const char *gNumberChar = "0123456789";
static char	gNumberBuffer[32];

void FontDraw::WriteNumber(int pNumber)
{
    
    int aNumber = pNumber;
	int aIndex = 0;
    
    if(aNumber < 0)
    {
        aNumber = -aNumber;
        gNumberBuffer[aIndex++] = '-';
    }
    
	if(aNumber == 0)
    {
        gNumberBuffer[aIndex++] = '0';
    }
	else
	{
		while(aNumber != 0)
		{
			gNumberBuffer[aIndex++] = gNumberChar[((aNumber) % 10)];
			aNumber = aNumber / 10;
		}
	}
    PadLength(aIndex);
    int aCount=aIndex;
    while(aCount > 0)
    {
        aCount--;
        mData[mWriteIndex] = gNumberBuffer[aCount];
        mWriteIndex++;
    }
    mData[mWriteIndex]=0;
}


void FontDraw::Draw(float pX, float pY)
{
    float aDrawX = pX;
    float aDrawY = pY;
    
    float aCharWidth = 0.0f;
    int aIndex = 0;
    
    if(mData)
    {
        char *aPtr = mData;
        
        while(*aPtr)
        {
            aIndex = (int)((unsigned char)(*aPtr));
            aCharWidth = mSprite[aIndex].mWidth;
            mSprite[aIndex].Draw(aDrawX, aDrawY);
            aDrawX += aCharWidth;
            aPtr++;
        }
    }
    Reset();
}

void FontDraw::DrawTime(float pX, float pY, int pHours, int pMinutes, int pSeconds)
{
    float aFixedWidth = mMaxWidth;
    float aFixedHeight = mMaxHeight;
    char aDelim = ':';
    
    int aDelimInex = (int)((unsigned char)(aDelim));
    
    float aDelimWidth = mSprite[aDelimInex].mWidth;
    
    
    pX += aFixedWidth / 2.0f;
    pY += aFixedHeight / 2.0f;
    
    Reset();
    WriteNumber(pHours);
    
    if(mWriteIndex <= 1)
    {
        mSprite[(int)((unsigned char)('0'))].Center(pX, pY);
        pX += aFixedWidth;
    }
    for(int i=0;i<mWriteIndex;i++)
    {
        mSprite[(int)((unsigned char)(mData[i]))].Center(pX, pY);
        
        if(i == (mWriteIndex - 1))pX += aDelimWidth;
        else pX += aFixedWidth;
    }
    
    //pX -= (aFixedWidth - aDelimWidth) / 2.0f;
    
    mSprite[aDelimInex].Center(pX, pY);
    pX += aFixedWidth;
    
    
    
    Reset();
    WriteNumber(pMinutes);
    
    if(mWriteIndex <= 1)
    {
        mSprite[(int)((unsigned char)('0'))].Center(pX, pY);
        pX += aFixedWidth;
    }
    for(int i=0;i<mWriteIndex;i++)
    {
        mSprite[(int)((unsigned char)(mData[i]))].Center(pX, pY);
        if(i == (mWriteIndex - 1))pX += aDelimWidth;
        else pX += aFixedWidth;
    }
    
    
    
    
    
    
    mSprite[aDelimInex].Center(pX + (aFixedWidth - aDelimWidth) / 2.0f, pY);
    pX += aFixedWidth;
    
    
    
    Reset();
    WriteNumber(pSeconds);
    
    if(mWriteIndex <= 1)
    {
        mSprite[(int)((unsigned char)('0'))].Center(pX, pY);
        pX += aFixedWidth;
    }
    for(int i=0;i<mWriteIndex;i++)
    {
        mSprite[(int)((unsigned char)(mData[i]))].Center(pX, pY);
        pX += aFixedWidth;
    }
    
    
    
    
}

void FontDraw::Right(float pX, float pY)
{
    
}

void FontDraw::Center(float pX, float pY)
{
    
}

void FontDraw::Center(float pX, float pY, float pScale)
{
    float aWidth = Width();
    
    aWidth = aWidth * pScale;
    
    float aDrawX = pX - aWidth / 2.0f;
    float aDrawY = pY;
    float aCharWidth = 0.0f;
    
    int aIndex = 0;
    
    if(mData)
    {
        char *aPtr = mData;
        while(*aPtr)
        {
            aIndex = (int)((unsigned char)(*aPtr));
            aCharWidth = ((float)mSprite[aIndex].mWidth) * pScale;
            mSprite[aIndex].Draw(aDrawX + (aCharWidth / 2.0f), aDrawY, pScale, 0.0f);
            aDrawX += aCharWidth;
            aPtr++;
        }
    }
    
    Reset();
}

float FontDraw::Width(char *pText)
{
    float aReturn = 10.0f;
    int aIndex = 0;
    
    if(mData)
    {
        char *aPtr = mData;
        while(*aPtr)
        {
            aIndex = (int)((unsigned char)(*aPtr));
            aReturn += (float)(mSprite[aIndex].mWidth);
            aPtr++;
        }
    }
    return aReturn;
}




