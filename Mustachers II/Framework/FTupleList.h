//
//  FTupleList.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FTUPLE_LIST
#define FTUPLE_LIST

class FTupleList
{
public:
    
    FTupleList();
    ~FTupleList();
    
    void                Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6, float pData7, float pData8, float pData9);
    void                Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6, float pData7, float pData8);
    void                Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6, float pData7);
    void                Add(float pData1, float pData2, float pData3, float pData4, float pData5, float pData6);
    void                Add(float pData1, float pData2, float pData3, float pData4, float pData5);
    void                Add(float pData1, float pData2, float pData3, float pData4);
    void                Add(float pData1, float pData2, float pData3);
    
    void                Size(int pSize);
    void                Free();
    
    int                 mTupleSize;
    
    int                 mListSize;
    int                 mListCount;
    
    float               *mData;
    
};

#endif
