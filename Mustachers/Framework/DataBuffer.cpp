//
//  DataBuffer.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 2/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DataBuffer.h"



DataBuffer::DataBuffer()
{
    mPath;
    mData=0;
    mLength=0;
    mSize=0;
    mCursor=0;
}

DataBuffer::~DataBuffer()
{
    
}

void DataBuffer::Clear()
{
    
}

void DataBuffer::Size(int pSize)
{
    
}

void DataBuffer::WriteBool(bool pWrite)
{
    
}

bool DataBuffer::ReadBool()
{
    
}

void DataBuffer::WriteChar(unsigned char pWrite)
{
    
}

char DataBuffer::ReadChar()
{
    
}

void DataBuffer::WriteShort(short pWrite)
{
    
}

short DataBuffer::ReadShort()
{
    
}

void DataBuffer::WriteInt(int pWrite)
{
    
}

int DataBuffer::ReadInt()
{
    
	int aReturn=0;
	if((mCursor+3)<mLength) 
	{
        aReturn = *(int*)(mData+mCursor);
        mCursor += 4;
	}
    return aReturn;
}

void DataBuffer::Write(char *pWrite, int theLength)
{
    
}

void DataBuffer::Write(char *pWrite)
{
    
}

void DataBuffer::WriteFloat(float pWrite)
{
    WriteInt(*((int*)(&pWrite)));
}

float DataBuffer::ReadFloat()
{
    unsigned int aRead = ReadInt();
    return *((float*)(&aRead));
}


void DataBuffer::WriteString(char *pString)
{
    
}

FString DataBuffer::ReadString()
{
    FString aReturn;
    
    
    
    return aReturn;
}

bool DataBuffer::HasMoreData()
{
    
}

void DataBuffer::Save(char *pFile)
{
    
}

void DataBuffer::Load(char *pFile)
{
    
}






