//
//  FIndexList.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FIndexList.h"


FIndexList::FIndexList()
{
    mCount = 0;
    mSize = 0;
    
    mIndex = 0;
}

FIndexList::~FIndexList()
{
    Clear();
}

void FIndexList::Clear()
{
    delete[] mIndex;
    
    mCount = 0;
    mSize = 0;
    
    mIndex = 0;
    //mY = 0;
}

void FIndexList::Add(GFX_MODEL_INDEX_TYPE pIndex)
{
    if(mCount >= mSize)
    {
        Size(mCount + (mCount / 2) + 1);
    }
    
    mIndex[mCount] = pIndex;
    mCount++;
}

void FIndexList::Add(FIndexList *pList)
{
    if(pList)
    {
        
        if(pList->mCount > mSize)
        {
            Size(pList->mCount);
        }
        
        for(int i = 0; i<pList->mCount; i++)
        {
            Add(pList->mIndex[i]);
            //Add(pList->mX[i], pList->mY[i]);
        }
        
    }
}

void FIndexList::AddIndeces(int pCount, GFX_MODEL_INDEX_TYPE pIndex1, GFX_MODEL_INDEX_TYPE pIndex2, GFX_MODEL_INDEX_TYPE pIndex3, GFX_MODEL_INDEX_TYPE pIndex4, GFX_MODEL_INDEX_TYPE pIndex5, GFX_MODEL_INDEX_TYPE pIndex6, GFX_MODEL_INDEX_TYPE pIndex7, GFX_MODEL_INDEX_TYPE pIndex8, GFX_MODEL_INDEX_TYPE pIndex9, GFX_MODEL_INDEX_TYPE pIndex10, GFX_MODEL_INDEX_TYPE pIndex11, GFX_MODEL_INDEX_TYPE pIndex12, GFX_MODEL_INDEX_TYPE pIndex13, GFX_MODEL_INDEX_TYPE pIndex14, GFX_MODEL_INDEX_TYPE pIndex15)
{
    if(pCount >= 15)
    {
        Add(pIndex1); Add(pIndex2); Add(pIndex3); Add(pIndex4); Add(pIndex5);
        Add(pIndex6); Add(pIndex7); Add(pIndex8); Add(pIndex9); Add(pIndex10);
        Add(pIndex11); Add(pIndex12); Add(pIndex13); Add(pIndex14); Add(pIndex15);
    }
    else
    {
        if(pCount > 0)Add(pIndex1);
        if(pCount > 1)Add(pIndex2);
        if(pCount > 2)Add(pIndex3);
        if(pCount > 3)Add(pIndex4);
        if(pCount > 4)Add(pIndex5);
        if(pCount > 5)Add(pIndex6);
        if(pCount > 6)Add(pIndex7);
        if(pCount > 7)Add(pIndex8);
        if(pCount > 8)Add(pIndex9);
        if(pCount > 9)Add(pIndex10);
        if(pCount > 10)Add(pIndex11);
        if(pCount > 11)Add(pIndex12);
        if(pCount > 12)Add(pIndex13);
        if(pCount > 13)Add(pIndex14);
        if(pCount > 14)Add(pIndex15);
    }
}


void FIndexList::AddIndecesReset(int pCount, GFX_MODEL_INDEX_TYPE pIndex1, GFX_MODEL_INDEX_TYPE pIndex2, GFX_MODEL_INDEX_TYPE pIndex3, GFX_MODEL_INDEX_TYPE pIndex4, GFX_MODEL_INDEX_TYPE pIndex5, GFX_MODEL_INDEX_TYPE pIndex6, GFX_MODEL_INDEX_TYPE pIndex7, GFX_MODEL_INDEX_TYPE pIndex8, GFX_MODEL_INDEX_TYPE pIndex9, GFX_MODEL_INDEX_TYPE pIndex10, GFX_MODEL_INDEX_TYPE pIndex11, GFX_MODEL_INDEX_TYPE pIndex12, GFX_MODEL_INDEX_TYPE pIndex13, GFX_MODEL_INDEX_TYPE pIndex14, GFX_MODEL_INDEX_TYPE pIndex15)
{
    mCount = 0;
    
    AddIndeces(pCount, pIndex1, pIndex2, pIndex3, pIndex4, pIndex5,
               pIndex6, pIndex7, pIndex8, pIndex9, pIndex10,
               pIndex11, pIndex12, pIndex13, pIndex14, pIndex15);
}

GFX_MODEL_INDEX_TYPE FIndexList::Get(int pIndex)
{
    GFX_MODEL_INDEX_TYPE aResult = 0;
    if((pIndex >= 0) && (pIndex < mCount))
    {
        aResult = mIndex[pIndex];
    }
    
    return aResult;
}

void FIndexList::Set(int pSlot, GFX_MODEL_INDEX_TYPE pIndex)
{
    if(pSlot >= mSize)
    {
        SetSize(pSlot + 1);
    }
    if(pSlot >= mCount)
    {
        mCount = (pSlot + 1);
    }
    
    if(pSlot >= 0)
    {
        mIndex[pSlot] = pIndex;
        
        //mY[pIndex] = pY;
    }
}

void FIndexList::Reset()
{
    mCount = 0;
}

void FIndexList::Size(int pSize)
{
    if(pSize != mSize)
    {
        if(pSize <= 0)
        {
            Clear();
        }
        else
        {
            if(mCount >= pSize)mCount=pSize;
            GFX_MODEL_INDEX_TYPE *aNew = new GFX_MODEL_INDEX_TYPE[pSize];
            for(int i = 0; i<mCount; i++)aNew[i] = mIndex[i];
            for(int i = mCount; i<pSize; i++)aNew[i] = 0;
            
            delete[] mIndex;
            mIndex = aNew;
            mSize = pSize;
        }
    }
}

void FIndexList::Save(FFile *pFile)
{
    if(pFile)
    {
        pFile->WriteInt(mCount);
        
        for(int i = 0; i<mCount; i++)
        {
            pFile->WriteShort(mIndex[i]);
            
            //pFile->WriteFloat(mX[i]);
            //pFile->WriteFloat(mY[i]);
        }
    }
}

void FIndexList::Load(FFile *pFile)
{
    Clear();
    
    if(pFile)
    {
        int aCount = pFile->ReadInt();
        
        Size(aCount);
        for(int i = 0; i<aCount; i++)
        {
            mIndex[i] = pFile->ReadShort();
        }
        mCount = aCount;
    }
}

void FIndexList::Reverse()
{
    if(mCount > 1)
    {
        int aStartIndex = 0;
        int aEndIndex = (mCount - 1);
        
        GFX_MODEL_INDEX_TYPE aHold = 0;
        
        while (aStartIndex < aEndIndex)
        {
            aHold = mIndex[aEndIndex];
            
            mIndex[aEndIndex] = mIndex[aStartIndex];
            
            mIndex[aStartIndex] = aHold;
            
            aStartIndex++;
            aEndIndex--;
        }
        
    }
    
}




void FIndexList::Clone(FIndexList *pPointList)
{
    if(pPointList)
    {
        if(pPointList->mCount > mSize)
        {
            Size(pPointList->mCount);
        }
        
        Reset();
        
        int aCount = pPointList->mCount;
        
        for(int i = 0; i<aCount; i++)
        {
            Add(pPointList->mIndex[i]);
        }
    }
}


int FIndexList::GetPrintLineCount()
{
    int aLineCount = 0;
    
    if(mCount > 0)
    {
        int aIndex = 0;
        bool aDone = false;
        
        while (aDone == false)
        {
            aLineCount++;
            aIndex += 15;
            if(aIndex >= mCount)aDone = true;
        }
        
    }
    
    return aLineCount;
}


FString FIndexList::GetPrintLine(int pLineNumber)
{
    FString aResult = "AddIndeces(";
    
    if(pLineNumber == 0)aResult = "AddIndecesReset(";
    
    
    int aStartIndex = pLineNumber * 15;
    int aEndIndex = (aStartIndex + 15);
    
    bool aFinish = false;
    
    if(aEndIndex >= mCount)
    {
        aFinish = true;
        aEndIndex = mCount;
    }
    
    int aLineCount = (aEndIndex - aStartIndex);
    if(aLineCount <= 0)aLineCount = 0;
    
    FString aLineCountString = FString(aLineCount);
    if(aLineCountString.mLength <= 1)aLineCountString += " ";
    
    aResult += aLineCountString;
    aResult += ", ";
    
    while (aLineCount > 0)
    {
        int aIndex = mIndex[aStartIndex];
        FString aIndexString = FString(aIndex);
        
        aResult += aIndexString;
        
        aStartIndex++;
        aLineCount--;
        
        if(aLineCount > 0)
        {
            aResult += FString(", ");
        }
        else
        {
            aResult += FString(")");
        }
    }
    
    return aResult;
}

FString FIndexList::GetPrintString(const char *pVariableName)
{
    FString aResult = "";
    
    int aLineCount = GetPrintLineCount();
    for(int i = 0; i<aLineCount; i++)
    {
        FString aLine = GetPrintLine(i);
        aLine = FString(FString(pVariableName) + FString(".") + FString(aLine.c()) + FString(";\n")).c();
        aResult += aLine;
    }
    
    return aResult;
}

