//
//  StringBuffer.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

class StringBuffer
{
public:
    
    StringBuffer(){}
    ~StringBuffer(){}
    
    char                *mData;
    int                 mLength;
    int                 mSize;
    
    void                Add(const char *pData);
    
    
};

#endif
