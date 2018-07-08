//
//  FTupleList.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FTupleList.h"

FTupleList::FTupleList()
{
    mTupleSize=0;
    
    mListSize=0;
    mListCount=0;
}

FTupleList::~FTupleList()
{
    
}

void FTupleList::Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6, float pData7, float pData8, float pData9)
{
    mTupleSize=9;
}

void FTupleList::Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6, float pData7, float pData8)
{
    mTupleSize=8;
}

void FTupleList::Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6, float pData7)
{
    mTupleSize=7;
}

void FTupleList::Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6)
{
    mTupleSize=6;
}

void FTupleList::Add(float pData1, float pData2, float pData3, float pData4, float pData5)
{
    mTupleSize=5;
}

void FTupleList::Add(float pData1, float pData2, float pData3, float pData4)
{
    mTupleSize=3;
}

void FTupleList::Add(float pData1, float pData2, float pData3)
{
    mTupleSize=3;
}

void FTupleList::Size(int pSize)
{
    int aDataSize = pSize * mTupleSize;
    
    float *aNewData = new float[aDataSize];
    
    
    
}

void FTupleList::Free()
{
    
}




