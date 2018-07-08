
#include "FString.h"
#include <fcntl.h>

#ifndef BUFFER_H
#define BUFFER_H

#define DIR_SEPARATOR ((char)'/')

extern bool gDisableQuickSaveToDesktop;

bool FileExists(char *pPfile);

int CountLeadingZeros(const char *pBaseFile, const char *pExtension, int pStartIndex);
int CountLeadingZeros(const char *pBaseFile, const char *pExtension, const char*pPrefix, int pStartIndex);

//String DataToAlphanumeric(unsigned char*pData, int pLength);
//String FloatToAlphanumeric(float pFloat);

int FloatToInt(float pFloat);
float IntToFloat(int pInt);

class Buffer
{
		
	public:
		
	Buffer();
	~Buffer();
		
	virtual void		Clear();
	
	inline void			SetSize(int size){Size(size);}
	void				Size(int size);
	
	void				WriteBool(bool write);
	bool				ReadBool();
	
	void				WriteChar(unsigned char write);
	char				ReadChar();
	
	void				WriteShort(short write);
	short				ReadShort();
	
	void				WriteInt(int write);
	int					ReadInt();
	
	void				Write(char *write, int theLength);
	void				Write(char *write);
		
	inline void			WriteFloat(float write){WriteInt(*((int*)(&write)));}
	inline float		ReadFloat(){unsigned int aRead = ReadInt(); return *((float*)(&aRead));}
	
	
	void				WriteString(char *pString);
    inline void			WriteString(FString pString){WriteString(pString.c());}
    inline void			WriteString(const char * pString){WriteString((char*)pString);}
    
	FString				ReadString();
	
	void				WriteBits(unsigned int pWrite, int pBitCount);
	unsigned int		ReadBits(int pBitCount);
	int					ReadBits(int pBitCount, bool pSigned);
	
	void				Encrypt(char *password);
    virtual void        Encrypt(const char *password){Encrypt((char*)password);}
    
	void				Decrypt(char *password);
    virtual void        Decrypt(const char *password){Decrypt((char*)password);}
	
	void				Compress();
	void				Decompress();
	
	
	bool				HasMoreData(int pBitCount);
    
	void				Save(char *pFile=0);
    virtual void		Save(const char *pFile){Save((char*)pFile);}
	inline void			Save(FString pString){Save(pString.c());}
	
	void				Load(char *pFile=0);
    virtual void		Load(const char *pFile){Load((char*)pFile);}
	inline void			Load(FString pString){Load(pString.c());}
    
    
    
    bool				FileExists(char *pFile=0);
    virtual bool		FileExists(const char *pFile){return FileExists((char*)pFile);}
	inline bool			FileExists(FString pString){return FileExists(pString.c());}
    
	
	void				Transform();
	
	//original index stored as last 4 bytes of mData..
	void				Untransform();
	
	void				Untransform(int aLastIndex);
    
	void				Print(bool include_tail=true);
    
    void                PrintFile();
	
	void				operator=(Buffer &theBuffer);
    
	char				*MakeFile(char *pFile, bool pMakeDirectory=true);
	char				*GetFile(char *pFile){return MakeFile(pFile,false);}
	
	char				*mPath;
	unsigned char		*mData;
	unsigned int		mLength;
	unsigned int		mSize;
	
	//protected:
	unsigned int		mReadCursor;
	unsigned int		mWriteCursor;
	void				Grow();
};


class WordIndexList
	{
	public:
		WordIndexList(){mData=0;mSize=0;mCount=0;mWord=0;mListSize=0;}
		~WordIndexList(void){Free();}
		
		struct WTItem
		{
			WTItem(int start, int length, int index)
			{
				mStartIndex=start;
				mLength=length;
				mIndex=index;
				mNext=0;
			}
			int mStartIndex, mIndex, mLength;
			WTItem *mNext;
		};
		
		void		Free()
		{
			mCount=0;
			if(mData)
			{
				for(int i=0;i<mSize;i++)
				{
					WTItem *aItem=mData[i];
					while(aItem)
					{
						WTItem *aNext=aItem->mNext;
						delete aItem;
						aItem=aNext;
					}
					mData[i]=0;
				}
				delete[]mData;
			}
			delete[]mWord;
			mWord=0;
			mListSize=0;
			mData=0;
		}
		
		int			Hash(int start, int length, char*data)
		{
			unsigned long aReturn = 5381;
			length+=start;
			while(start<length)aReturn=((aReturn<< 5)+aReturn)^data[start++];
			return (int)(aReturn % mSize);
		}
		void		AddWord(int start, int length, char *data)
		{
			int aHash=Hash(start, length, data);
			WTItem *aItem=mData[aHash];
			WTItem *aPrevious=aItem;
			//int aShelf=start+length;
			for(;aItem!=0;)
			{			
				aPrevious=aItem;
				aItem=aItem->mNext;
			}
			WTItem *aNewItem=new WTItem(start,length,mCount);
			if(aPrevious)aPrevious->mNext=aNewItem;
			else mData[aHash]=aNewItem;
			
			if(mCount>=mListSize)
			{
				mListSize=mCount+mCount/2+1;
				WTItem **aNew=new WTItem*[mListSize];
				for(int i=0;i<mCount;i++)aNew[i]=mWord[i];
				delete[]mWord;
				mWord=aNew;
			}
			//int aHold=mCount;
			mWord[mCount]=aNewItem;
			mCount++;
		}
		int	Index(int start, int length, char *data)
		{
			int aHash=Hash(start, length, data);
			WTItem *aItem=mData[aHash];
			WTItem *aPrevious=aItem;
			int aStart1, aStart2, aShelf=start+length;
			for(;aItem!=0;)
			{
				if(aItem->mLength==length)
				{
					aStart1=start;
					aStart2=aItem->mStartIndex;
					while(aStart1<aShelf)
					{
						if(data[aStart1]!=data[aStart2])break;
						aStart1++;
						aStart2++;
					}
					if(aStart1==aShelf)
					{
						return aItem->mIndex;
					}
				}
				
				aPrevious=aItem;
				aItem=aItem->mNext;
			}
			return -1;
		}
		void		Size(int theSize)
		{
			Free();
			mSize=theSize;
			mData=new WTItem*[mSize];
			for(int i=0;i<mSize;i++)mData[i]=0;
			mListSize=0;
		}
		
		int			mMaxIterDepth;
		
		WTItem		**mData;
		WTItem		**mWord;
		
		int			mSize;
		int			mCount;
		int			mListSize;
		int			mBufferSize;
	};

#endif