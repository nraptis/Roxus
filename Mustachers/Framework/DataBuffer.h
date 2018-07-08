//
//  DataBuffer.h
//  DoomKnights
//
//  Created by Nick Raptis on 2/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FString.h"

#ifndef DoomKnights_DataBuffer_h
#define DoomKnights_DataBuffer_h

class DataBuffer
{
public:
    
    DataBuffer();
    ~DataBuffer();
    
	virtual void		Clear();
	void				Size(int pSize);
	
	void				WriteBool(bool pWrite);
	bool				ReadBool();
	
	void				WriteChar(unsigned char pWrite);
	char				ReadChar();
	
	void				WriteShort(short pWrite);
	short				ReadShort();
	
	void				WriteInt(int pWrite);
	int					ReadInt();
	
	void				Write(char *pWrite, int theLength);
	void				Write(char *pWrite);
    
	void                WriteFloat(float pWrite);
	float               ReadFloat();
	
	void				WriteString(char *pString);
    inline void			WriteString(FString pString){WriteString(pString.c());}
    inline void			WriteString(const char * pString){WriteString((char*)pString);}
    
	FString				ReadString();
    
	bool				HasMoreData();
    
	void				Save(char *pFile=0);
    virtual void		Save(const char *pFile){Save((char*)pFile);}
	inline void			Save(FString pString){Save(pString.c());}
	
	void				Load(char *pFile=0);
    virtual void		Load(const char *pFile){Load((char*)pFile);}
	inline void			Load(FString pString){Load(pString.c());}
    
    FString             mPath;
	unsigned char		*mData;
	unsigned int		mLength;
	unsigned int		mSize;
    unsigned int        mCursor;
};

#endif
