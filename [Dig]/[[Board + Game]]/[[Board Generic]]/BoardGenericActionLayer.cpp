//
//  BoardGenericActionLayer.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/15/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "BoardGenericActionLayer.h"
#include "core_includes.h"

BoardGenericActionLayer::BoardGenericActionLayer()
{
    mWidth = 0;
    mHeight = 0;
    
    mData = 0;
    mDataBase = 0;
    
    mDefaultValue = -1;
}

BoardGenericActionLayer::~BoardGenericActionLayer()
{
    delete [] mData;
    delete [] mDataBase;
    
    mData = 0;
    mDataBase = 0;
}

void BoardGenericActionLayer::Free()
{
    delete [] mData;
    delete [] mDataBase;
    
    mData = 0;
    mDataBase = 0;
    
    mWidth = 0;
    mHeight = 0;
}

void BoardGenericActionLayer::SetSize(int pGridWidth, int pGridHeight)
{
    Free();
    
    if((pGridWidth > 0) && (pGridHeight > 0))
    {
        int aArea = pGridWidth * pGridHeight;
    
        int **aData = new int*[pGridWidth];
        int *aDataBase = new int[aArea];
        
        int *aDataPtr = aDataBase;
        
        for(int i=0;i<pGridWidth;i++)
        {
            aData[i] = aDataPtr;
         
            for(int n=0;n<pGridHeight;n++)
            {
                
                aData[i][n] = mDefaultValue;
            }
            
            aDataPtr += pGridHeight;
        }
        
        delete [] mDataBase;
        delete [] mData;
        
        mDataBase = aDataBase;
        mData = aData;
    }
    
    mWidth = pGridWidth;
    mHeight = pGridHeight;
    
}

void BoardGenericActionLayer::Resize(int pGridWidth, int pGridHeight)
{
    printf("BoardGenericActionLayer::Resize(%d, %d)\n", pGridWidth, pGridHeight);
    
    if((pGridWidth > 0) && (pGridHeight > 0))
    {
        int aArea = pGridWidth * pGridHeight;
        
        int **aData = new int*[pGridWidth];
        
        int *aDataBase = new int[aArea];
        int *aDataPtr = aDataBase;
        
        for(int i=0;i<pGridWidth;i++)
        {
            aData[i] = aDataPtr;
            
            for(int n=0;n<pGridHeight;n++)aData[i][n] = mDefaultValue;
            
            aDataPtr += pGridHeight;
        }
        
        int aCopyWidth = pGridWidth;
        if(mWidth < aCopyWidth)aCopyWidth = mWidth;
        
        int aCopyHeight = pGridHeight;
        if(mHeight < aCopyHeight)aCopyHeight = mHeight;
        
        for(int i=0;i<aCopyWidth;i++)
        {
            for(int n=0;n<aCopyHeight;n++)
            {
                aData[i][n] = mData[i][n];
            }
        }
        
        delete [] mDataBase;
        delete [] mData;
        
        mDataBase = aDataBase;
        mData = aData;
    }
    else
    {
        delete [] mDataBase;
        delete [] mData;
        
        mDataBase = 0;
        mData = 0;
    }
}

int BoardGenericActionLayer::Get(int pGridX, int pGridY)
{
    int aReturn = 0;
    
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight))
    {
        aReturn = mData[pGridX][pGridY];
    }
    
    return aReturn;
}


void BoardGenericActionLayer::Flood(int pValue)
{
    for(int i=0;i<mWidth;i++)
    {
        for(int n=0;n<mHeight;n++)
        {
            mData[i][n] = pValue;
            
        }
    }
}

void BoardGenericActionLayer::Set(int pGridX, int pGridY, int pValue)
{
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight))
    {
        mData[pGridX][pGridY] = pValue;
    }
}


