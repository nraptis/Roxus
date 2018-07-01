//
//  BoardActionLayer.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/15/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "BoardActionLayer.h"
#include "core_includes.h"

BoardActionLayer::BoardActionLayer()
{
    mWidth = 0;
    mHeight = 0;
    
    mData = 0;
    mDataBase = 0;
    
    mDefaultValue = 0;
}

BoardActionLayer::~BoardActionLayer()
{
    Free();
}

void BoardActionLayer::Free()
{
    delete [] mDataBase;
    delete [] mData;
    
    mData = 0;
    mDataBase = 0;
    
    mWidth = 0;
    mHeight = 0;
}

void BoardActionLayer::Make(int pGridWidth, int pGridHeight)
{
    Free();
    
    if((pGridWidth > 0) && (pGridHeight > 0))
    {
        int aArea = pGridWidth * pGridHeight;
        
        short *aDataBase = new short[aArea + 1];
        short **aData = new short*[pGridWidth];
        
        short *aDataPtr = aDataBase;
        
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
        
        mWidth = pGridWidth;
        mHeight = pGridHeight;
    }
}

void BoardActionLayer::Make(int pGridWidth, int pGridHeight, int pType)
{
    Make(pGridWidth, pGridHeight);
    Flood(pType);
}

void BoardActionLayer::Resize(int pGridWidth, int pGridHeight)
{
    //printf("BoardActionLayer::Resize(%d, %d)\n", pGridWidth, pGridHeight);
    
    if((pGridWidth > 0) && (pGridHeight > 0)){
        int aArea = pGridWidth * pGridHeight;
        
        short **aData = new short*[pGridWidth + 1];
        short *aDataBase = new short[aArea];
        short *aDataPtr = aDataBase;
        
        for(int i=0;i<pGridWidth;i++){
            aData[i] = aDataPtr;
            for(int n=0;n<pGridHeight;n++)aData[i][n] = mDefaultValue;
            aDataPtr += pGridHeight;
        }
        
        int aCopyWidth = pGridWidth;
        if(mWidth < aCopyWidth)aCopyWidth = mWidth;
        
        int aCopyHeight = pGridHeight;
        if(mHeight < aCopyHeight)aCopyHeight = mHeight;
        
        for(int i=0;i<aCopyWidth;i++){
            for(int n=0;n<aCopyHeight;n++)aData[i][n] = mData[i][n];
        }
        
        delete [] mDataBase;
        delete [] mData;
        
        mDataBase = aDataBase;
        mData = aData;
        
        mWidth = pGridWidth;
        mHeight = pGridHeight;
    }
    else{
        Free();
    }
}

int BoardActionLayer::Get(int pGridX, int pGridY)
{
    int aReturn = 0;
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight)){
        aReturn = mData[pGridX][pGridY];
    }
    return aReturn;
}


void BoardActionLayer::Flood(int pValue)
{
    for(int i=0;i<mWidth;i++){
        for(int n=0;n<mHeight;n++){
            mData[i][n] = pValue;
        }
    }
}

void BoardActionLayer::Set(int pGridX, int pGridY, int pValue)
{
    if((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight)){
        mData[pGridX][pGridY] = pValue;
    }
}

void BoardActionLayer::Stamp(int pGridX, int pGridY, BoardActionLayer *pLayer)
{
    int aGridX = pGridX;
    int aGridY = pGridY;
    if(pLayer){
        if((pLayer->mWidth > 0) && (pLayer->mHeight > 0)){
            for(int aOffsetX=0;aOffsetX<pLayer->mWidth;aOffsetX++){
                for(int aOffsetY=0;aOffsetY<pLayer->mHeight;aOffsetY++){
                    aGridX = pGridX + aOffsetX;
                    aGridY = pGridY + aOffsetY;
                    if((aGridX >= 0) && (aGridX < mWidth) && (aGridY >= 0) && (aGridY < mHeight)){
                        mData[aGridX][aGridY] = pLayer->mData[aOffsetX][aOffsetY];
                    }
                }
            }
        }
    }
}

bool BoardActionLayer::SwapAllowed(int pGridX1, int pGridY1, int pGridX2, int pGridY2){
    bool aResult = false;
    if((pGridX1 >= 0) && (pGridY1 >= 0) && (pGridX1 < mWidth) && (pGridY1 < mHeight) && (pGridX2 >= 0) && (pGridY2 >= 0) && (pGridX2 < mWidth) && (pGridY2 < mHeight)){
        if((mData[pGridX1][pGridY1] > 0) && (mData[pGridX2][pGridY2] > 0)){
            aResult = true;
        }
    }
    return aResult;
}

void BoardActionLayer::Swap(int pGridX1, int pGridY1, int pGridX2, int pGridY2)
{
    if(SwapAllowed(pGridX1, pGridY1, pGridX2, pGridY2)){
        int aHold = mData[pGridX1][pGridY1];
        mData[pGridX1][pGridY1] = mData[pGridX2][pGridY2];
        mData[pGridX2][pGridY2] = aHold;
    }
}

bool BoardActionLayer::MatchExists(int pGridX, int pGridY){
    if(MatchExistsH(pGridX, pGridY))return true;
    if(MatchExistsV(pGridX, pGridY))return true;
    return false;
}

bool BoardActionLayer::MatchExistsH(int pGridX, int pGridY){
    if(OnGrid(pGridX, pGridY)){
        int aType = mData[pGridX][pGridY];
        if(aType > 0){
            int aCount = 1;
            for(int i=pGridX+1;i<mWidth;i++){
                if(mData[i][pGridY] == aType)aCount++;
                else break;
            }
            for(int i=pGridX-1;i>=0;i--){
                if(mData[i][pGridY] == aType)aCount++;
                else break;
            }
            if(aCount >= 3)return true;
        }
    }
    return false;
}

bool BoardActionLayer::MatchExistsV(int pGridX, int pGridY){
    if(OnGrid(pGridX, pGridY)){
        int aType = mData[pGridX][pGridY];
        if(aType > 0){
            int aCount = 1;
            for(int n=pGridY+1;n<mHeight;n++){
                if(mData[pGridX][n] == aType)aCount++;
                else break;
            }
            for(int n=pGridY-1;n>=0;n--){
                if(mData[pGridX][n] == aType)aCount++;
                else break;
            }
            if(aCount >= 3)return true;
        }
    }
    return false;
}









































