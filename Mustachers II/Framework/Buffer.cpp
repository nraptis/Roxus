//#import "Management.h"
#include "Buffer.h"
#include "stdafx.h"
#include "Application.h"
#include <sys/stat.h>

bool gDisableQuickSaveToDesktop=false;

Buffer::Buffer()
{
	mLength=0;
	mSize=0;
	mReadCursor=0;
	mWriteCursor=0;
	mData=0;
	mPath=0;
}

Buffer::~Buffer()
{
	delete[]mPath;
	mPath=0;
	Clear();
}

/*
bool MakeDirectory(char *pFile)
{
	if(!pFile)return false;
	const char*aPtr=pFile;
	while(*aPtr)aPtr++;
	int aLength=(int)(aPtr-pFile);
	
	if(aLength < 1)return false;
	
	bool aContinue = true;
	char *aPath = new char[aLength+1];
	char *aPathPtr = aPath;
	char *aSeek = pFile;
	bool aValid=true;
	while(*aSeek == '\\' || *aSeek == '/')
	{
		aValid=false;
		aSeek++;
	}
	while(aContinue)
	{
		aContinue=false;
		while(*aSeek != 0 && *aSeek != '\\' && *aSeek != '/')
		{
			aValid=true;
			*aPathPtr=*aSeek;
			aSeek++;
			aPathPtr++;
		}
		if(*aSeek != 0 && aSeek != pFile)
		{
			while(*aSeek == '\\' || *aSeek == '/')
			{
				aSeek++;
			}
			if(*aSeek == 0)
			{
				aValid=false;
			}
			else
			{
				*aPathPtr++=DIR_SEPARATOR;
				*aPathPtr=0;
				mkdir(aPath,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
				aContinue=true;
				aValid=true;
			}
		}
	}
 
	delete[]aPath;
	// *aPathPtr=0;
	
	return aValid;
}
 */

void Buffer::Clear()
{
	delete[]mData;
	mLength=0;
	mSize=0;
	mReadCursor=0;
	mWriteCursor=0;
	mData=0;
}

void Buffer::Grow()
{
	int aSize=mLength+mLength/2+1;
	unsigned char *aNew=new unsigned char[aSize];
	unsigned char *aCopy=mData;
	unsigned char *aPaste=aNew;
	unsigned char *aShelf=mData+mSize;
	while(aCopy<aShelf)*aPaste++=*aCopy++;
	aShelf=aNew+aSize;
	while(aPaste<aShelf)*aPaste++=0;
	delete[]mData;
	mData=aNew;
	mSize=aSize;
}

void Buffer::Size(int size)
{
	if(size<=0)
	{
		Clear();
		return;
	}
	if(mLength>size)mLength=size;
	unsigned char *aNew=new unsigned char[size];
	unsigned char *aCopy=mData;
	unsigned char *aPaste=aNew;
	unsigned char *aShelf=mData+mLength;
	while(aCopy<aShelf)*aPaste++=*aCopy++;
	aShelf=aNew+size;
	while(aPaste<aShelf)*aPaste++=0;
	mData=aNew;
	mSize=size;
	mReadCursor=0;
}

void Buffer::Write(char *write, int theLength)
{
	if(mLength+theLength>mSize)Size(mLength+theLength);
	unsigned int aShift=mWriteCursor%8;
	unsigned int aIndex=(mWriteCursor)>>3;
	unsigned char *aCopy=(unsigned char*)write;
	unsigned char *aShelf=(unsigned char*)(write+theLength);
	if(aShift)
	{
		while(aCopy<aShelf)WriteChar(*aCopy++);
	}
	else
	{
		unsigned char *aPaste=mData+aIndex;
		while(aCopy<aShelf)*aPaste++=*aCopy++;
		mWriteCursor+=(theLength<<3);
		mLength=((mWriteCursor+7)>>3);
	}
	
}

void Buffer::Write(char *write)
{
	char *aPtr=write;
	while(*aPtr)aPtr++;
	Write(write,(int)(aPtr-write));
}

void Buffer::WriteInt(int write)
{
	WriteBits(write,32);
}

int Buffer::ReadInt()
{
	return ReadBits(32);
}

void Buffer::WriteShort(short write)
{
	WriteBits(write, 16);
}

short Buffer::ReadShort()
{
	return ReadBits(16);
}

void Buffer::PrintFile()
{
    printf("\n\n\n//Buffer Start\n\n\n");
    
    printf("int aBufferSize = %d;\n", mLength);
    
    printf("unsigned char aBufferData[%d] = {\n", mLength);
    
    int aRow=0;
	int aIndex=0;
	while(aIndex<mLength)
	{
        unsigned int aInt = (unsigned int)((unsigned char)mData[aIndex]);
        
        printf("%d", aInt);
        if(aIndex < (mLength - 1))printf(", ");
        
        aRow++;
        if(aRow >= 20)
        {
            printf("\n");
            aRow=0;
        }
        aIndex++;
	}
    
    printf("};\n");
    

    
    printf("\n\n\n//Buffer End\n\n\n");
    
}
int hax[3] = {0,402,5};


void Buffer::Print(bool include_tail)
{
	int aRow=0;
	int aIndex=0;
	FString aPrint;
	printf("\n**Buffer Print**\n");
	while(aIndex<mLength)
	{
		aPrint+=Sprintf("%2X", (int)mData[aIndex])+",";
		aIndex++;
		
		aRow++;
		if(aRow>=10)
		{
			aRow=0;
			printf("__[%s]\n", aPrint.c());
			aPrint="";
		}
	}
	printf("__[%s]\n", aPrint.c());
	aPrint="";
	
	
	while(aIndex<mSize)
	{
		aPrint+=Sprintf("%2X", (int)mData[aIndex])+",";
		aIndex++;
		
		aRow++;
		if(aRow>=10)
		{
			aRow=0;
			printf("++[%s]\n", aPrint.c());
			aPrint="";
		}
	}
	printf("++[%s]\n", aPrint.c());
	
}


void Buffer::WriteBool(bool write)
{
	mLength=(mWriteCursor+7+1)>>3;
	if(mLength>mSize)Grow();
	unsigned int aShift=mWriteCursor%8;
	unsigned int aIndex=(mWriteCursor)>>3;
	mWriteCursor++;
	if(write)mData[aIndex]|=(1<<aShift);
}

bool Buffer::ReadBool()
{
	bool aReturn=false;
	unsigned int aShift=mReadCursor%8;
	unsigned int aIndex=mReadCursor/8;
	mReadCursor+=1;
	if(((mReadCursor+7)>>3)<=mLength)
	{
		aReturn=(mData[aIndex]&(1<<aShift))!=0;
	}
	return aReturn;
	
}

void Buffer::WriteChar(unsigned char write)
{
	mLength=(mWriteCursor+7+8)>>3;
	if(mLength>mSize)Grow();
	unsigned int aShift=mWriteCursor%8;
	unsigned int aIndex=(mWriteCursor)>>3;
	mWriteCursor+=8;
	if(aShift)
	{
		mData[aIndex]|=(write<<aShift);
		mData[aIndex+1]=(write>>(8-aShift));
	}
	else
	{
		mData[aIndex]=write;
	}
}

char Buffer::ReadChar()
{
	unsigned int aShift=mReadCursor%8;
	unsigned int aIndex=mReadCursor/8;
	mReadCursor+=8;
	unsigned char aReturn = 0;
	if(((mReadCursor+7)>>3)<=mLength)
	{
		if(aShift)
		{
			aReturn=((unsigned char)(mData[aIndex])>>aShift)|((unsigned char)(mData[aIndex+1])<<(8-aShift));
		}
		else
		{
			aReturn=mData[aIndex];
		}
	}
	return aReturn;
}

void Buffer::WriteString(char *pString)
{
	int aLength=0;
	
	if(pString)
	{
		char *aPtr=pString;
		while(*aPtr)aPtr++;
		aLength=(int)(aPtr-pString);
		WriteInt(aLength);
        if(aLength>0)
        {
            aPtr=pString;
            while(*aPtr)
            {
                WriteChar(*aPtr);
                aPtr++;
            }
        }
	}
	else
	{
		WriteInt(0);  
	}
}

FString Buffer::ReadString()
{
	FString aReturn;
	int aLength=ReadInt();
	if(aLength>0)
	{
		char *aChar=new char[aLength+1];
		aChar[aLength]=0;
		char *aWrite=aChar;
		while(aLength>0)
		{
			*aWrite=ReadChar();
			aWrite++;
			aLength--;
		}
		aReturn=aChar;
		delete[]aChar;
	}
	return aReturn;
}

bool Buffer::HasMoreData(int pBitCount)
{
	//unsigned int aCursor = mReadCursor+pBitCount;
	return (((mReadCursor+7)>>3)<=mLength);
}

unsigned int Buffer::ReadBits(int pBitCount)
{
	if(pBitCount<0)pBitCount=0;
    
	unsigned int aShift=mReadCursor%8;
	unsigned int aIndex=(mReadCursor)>>3;
	
    mReadCursor+=pBitCount;
	
    unsigned int aReturn=0;
	
    if(((mReadCursor+7)>>3)<=mLength)
	{
		for(unsigned int i=0;i<pBitCount;i++)
		{
			if(mData[aIndex]&(1<<aShift))
			{
				aReturn|=(1<<i);
			}
			if(++aShift==8)
			{
				aIndex++;
				aShift=0;
			}
		}
	}
	return aReturn;
}

int Buffer::ReadBits(int pBitCount, bool pSigned)
{
	if(pBitCount<0)pBitCount=0;
	unsigned int aShift=mReadCursor%8;
	unsigned int aIndex=(mReadCursor)>>3;
	mReadCursor+=pBitCount;
	unsigned int aReturn=0;
	if(((mReadCursor+7)>>3)<=mLength)
	{
		for(unsigned int i=0;i<pBitCount;i++)
		{
			if(mData[aIndex]&(1<<aShift))
			{
				aReturn|=(1<<i);
			}
			if(++aShift==8)
			{
				aIndex++;
				aShift=0;
			}
		}
	}
	if(pBitCount>0&&pBitCount<33&&pSigned)
	{
		if(aReturn&(1<<(pBitCount-1)))
		{
			for(int i=pBitCount;i<32;i++)aReturn|=(1<<i);
		}
	}
	return aReturn;
}

void Buffer::WriteBits(unsigned int pWrite, int pBitCount)
{
	mLength=(mWriteCursor+pBitCount+7)>>3;
	if(mLength>mSize)Grow();
	unsigned int aShift=mWriteCursor%8;
	unsigned int aIndex=(mWriteCursor)>>3;
	mWriteCursor+=pBitCount;
	for(unsigned int i=0;i<pBitCount;i++)
	{
		if((pWrite>>i)&1)mData[aIndex]|=(0x1<<aShift);
		if(++aShift==8)
		{
			aIndex++;
			aShift=0;
		}
	}
}

void Buffer::operator=(Buffer &theBuffer)
{
	Clear();
	mSize=theBuffer.mLength;
	mLength=mSize;
	mWriteCursor=theBuffer.mWriteCursor;
	mReadCursor=0;
	mData=theBuffer.mData;
	theBuffer.mData=0;
	theBuffer.Clear();
}

void Buffer::Compress()
{
	WordIndexList aList;	
	aList.Size(131072);
	Buffer aSave;
    
	if(mLength>0)aSave.WriteInt(mLength);
    
	int aBestIndex, aTryIndex;
	int k;
	int aBits=8;
	int	aCount=256;
	int aNext=256;
	int aSkipAhead;
	int aNextI;
	for(int i=0;i<mLength;i++)
	{
		aBestIndex=-1;
		for(k=i+1;k<mLength;k++)
		{
			aTryIndex=aList.Index(i,k-i+1,(char*)mData);
			if(aTryIndex==-1)
			{
				break;
			}
			else
			{
				aBestIndex=aTryIndex;
			}
		}
		if(aBestIndex!=-1)
		{
			aNextI=k-1;
			aSave.WriteBits((unsigned int)(aBestIndex+256), aBits);
		}
		else
		{
			aSave.WriteBits((unsigned int)(mData[i]), aBits);
			aNextI=i;
		}
		aSkipAhead=k;
		aBestIndex=-1;
		for(int g=i;g<aSkipAhead;g++)
		{
			for(k=g-1;k>=0;k--)
			{
				aTryIndex=aList.Index(k,g-k+1,(char*)mData);
				if(aTryIndex==-1)
				{
					break;
				}
				else
				{
					aBestIndex=aTryIndex;
				}
			}
			if(k>=0)
			{
				aList.AddWord(k,g-k+1,(char*)mData);
				aCount++;
			}
		}
		if(aCount>=aNext)
		{
			aNext=aNext*2;
			aBits++;
		}
		i=aNextI;
	}
	*this=aSave;
}

void Buffer::Decompress()
{
	WordIndexList aList;
	aList.Size(131072);
	mReadCursor=0;
		
	unsigned int aLength=ReadInt();
	
	Buffer aSave;
	aSave.Size(aLength);
	aSave.mLength=aLength;
	aSave.mWriteCursor=(aLength)<<3;
	
	unsigned int aWriteIndex=0;
	unsigned char *aWrite=aSave.mData;
	
	//Counters
	int k, n, g, i;
	
	int aBits=8;
	int aNext=256;
	int aRead;
	int aStart;
	int aStartIndex;
	int aSeek;
	for(i=0;aWriteIndex<aLength;i++)
	{
		aRead=ReadBits(aBits);
		aStart=aWriteIndex;
		
		if(aRead<256)
		{
			aWrite[aWriteIndex++]=aRead;
		}
		else
		{
			WordIndexList::WTItem *aItem=aList.mWord[aRead-256];
			aStartIndex=aItem->mStartIndex;
			aSeek=aStartIndex+aItem->mLength;
			for(n=aStartIndex;n<aSeek;n++)
			{
				aWrite[aWriteIndex++]=aWrite[n];
			}
		}
		for(g=aStart;g<aWriteIndex;g++)
		{
			for(k=g-1;k>=0;k--)
			{
				if(aList.Index(k,g-k+1,(char*)aWrite)==-1)break;
			}
			if(k>=0)
			{
				aList.AddWord(k,g-k+1,(char*)aWrite);
			}
		}
		if(aList.mCount+256>=aNext)
		{
			aNext=aNext*2;
			aBits++;
		}
	}
	*this=aSave;
}

void Buffer::Untransform()
{
	if(mLength<4)return;
	mLength-=4;
	Untransform(*((int*)(&mData[mLength])));
}

void Buffer::Untransform(int aLastIndex)
{
	if(aLastIndex<0||aLastIndex>=mLength)return;
	
	int aLength=mLength;
	int aOriginalIndex=aLastIndex;

	
	int *aTranslate=new int[aLength];
	int *aSum=new int[256+1];
	
	unsigned char *aData=mData;
	
	for(int i=0;i<257;i++)aSum[i]=0;
	for(int i=0;i<aLength;i++)aSum[aData[i]+1]++;
	for(int i=1;i<257;i++)aSum[i]+=aSum[i-1];
	for(int i=0;i<aLength;i++)aTranslate[aSum[aData[i]]++]=i;
	delete[]aSum;
	
	char *aNewData=new char[aLength];
	for(int i=0;i<aLength;i++)aNewData[i]=mData[aOriginalIndex=aTranslate[aOriginalIndex]];
	delete[]mData;
	mData=(unsigned char*)aNewData;
}

void Buffer::Transform()
{
	if(mLength<4)return;
	int aLength=mLength;
	int *aIndexList=new int[aLength];
	for(int i=0;i<aLength;i++)aIndexList[i]=i;
	for (int i=1;i<aLength;i++)
	{
		int aHold=aIndexList[i];
		int j=i;
		while(j>0)
		{
			int aIndex1=aHold;
			int aIndex2=aIndexList[j-1];
			int aCount=aLength;
			while(aCount>0&&mData[aIndex1]==mData[aIndex2])
			{
				if(++aIndex1==aLength)aIndex1=0;
				if(++aIndex2==aLength)aIndex2=0;
				aCount--;
			}
			if(mData[aIndex1]<mData[aIndex2])
			{
				aIndexList[j]=aIndexList[j-1];
				j--;
			}
			else
			{
				break;
			}
		}
		aIndexList[j]=aHold;
		
		
	} 
	
	char *aNewBuffer=new char[mLength+4];
	int aOriginalIndex=-1;
	for(int i=0;i<aLength;i++)
	{
		if(aIndexList[i]==0)aOriginalIndex=i;
		aNewBuffer[i]=mData[(aIndexList[i]+aLength-1)%aLength];
	}
	
	*((int*)(&aNewBuffer[mLength]))=aOriginalIndex;
	
	delete[]aIndexList;
	delete[]mData;
	
	mData=(unsigned char*)aNewBuffer;
	mLength+=4;
}

void Buffer::Save(char *pFile)
{
	if(!pFile)return;
	
	//MakeDirectory(pFile);
	
	int aFile=creat(pFile,S_IREAD|S_IWRITE);
	close(aFile);
	aFile=open(pFile,O_BINARY|O_RDWR);
	if (aFile!=-1)
	{
		write(aFile,mData,mLength);
		close(aFile);
	}
    else
    {
        if(gDisableQuickSaveToDesktop == true)
        {
            //printf("[Disabling Attempted Export (%s)\n", pFile);
        }
        
        else
        {
            
            
            //printf("File Failed To Open???\n\n\n");
            FString aPath = FString("/Users/nraptis/Desktop/Exports/") + pFile;
            
            aFile=creat(aPath.c(),S_IREAD|S_IWRITE);
            close(aFile);
            aFile=open(aPath.c(),O_BINARY|O_RDWR);
            if (aFile!=-1)
            {
                
                write(aFile,mData,mLength);
                close(aFile);
            }
            else {
                gDisableQuickSaveToDesktop = true;
            }
        }
    }
}

void Buffer::Load(char *pFile)
{
	Clear();
	if(!pFile)return;
    
	int aFileLength=-1;
	int aFile=open(pFile,O_BINARY|O_RDONLY);
	
    if(aFile==-1)
    {
        aFile=open(FString(gSandbox + pFile).c(),O_BINARY|O_RDONLY);
    }
    
    if(aFile==-1)
    {
        aFile=open(FString(gDocuments + pFile).c(),O_BINARY|O_RDONLY);
    }
    
	if(aFile!=-1)
	{
		struct stat aFileStats;
		if(fstat(aFile,&aFileStats) == 0)aFileLength=aFileStats.st_size;
		if(aFileLength<1)return;
		mLength=aFileLength;
		mSize=mLength;
		mWriteCursor=(mLength<<3);
		mData=new unsigned char[mLength+256];
		read(aFile,mData,mLength);
		close(aFile);
	}
    else
    {
        FString aErrorString = FString(pFile);
        aErrorString.RemovePath(false);
    }
}

bool Buffer::FileExists(char *pFile)
{
    bool aReturn = false;
    if(pFile != 0)
    {
        int aFileLength=-1;
        int aFile=open(pFile,O_BINARY|O_RDONLY);
        if(aFile==-1)
        {
            aFile=open(FString(gSandbox + pFile).c(),O_BINARY|O_RDONLY);
        }
        if(aFile==-1)
        {
            aFile=open(FString(gDocuments + pFile).c(),O_BINARY|O_RDONLY);
        }
        if(aFile!=-1)
        {
            struct stat aFileStats;
            if(fstat(aFile,&aFileStats) == 0)aFileLength=aFileStats.st_size;
            if(aFileLength>0)
            {
                aReturn = true;
            }
        }
    }
    return aReturn;
}

void Buffer::Encrypt(char *password)
{
	
}

void Buffer::Decrypt(char *password)
{
	
}

/*
static char gAlpha64[64] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$";

String DataToAlphanumeric(unsigned char*pData, int pLength)
{
    FString aReturn;
    
    if(pLength > 0)
    {
        char *aString = new char[pLength * 4 + 1];
        
        for(int i=0;i<pLength;i++)
        {
            
            unsigned char aChar = pData[i];
            
            unsigned char aChar1 = (aChar>>0) & 0x3F;
            unsigned char aChar2 = (aChar>>2) & 0x3F;
            unsigned char aChar3 = (aChar>>4) & 0x3F;
            unsigned char aChar4 = (aChar>>6) & 0x3F;
            
        }
    }
}


String FloatToAlphanumeric(float pFloat)
{
    return DataToAlphanumeric((unsigned char*)(&write), 4);
}

*/

bool FileExists(char *pPfile)
{
	return access(pPfile,0)==0;
}

int FloatToInt(float pFloat)
{
    return *((int*)(&pFloat));
}

float IntToFloat(int pInt)
{
    return *((float*)(&pInt));
}


int CountLeadingZeros(const char *pBaseFile, const char *pExtension, int pStartIndex)
{
    int aCheck = CountLeadingZeros(pBaseFile, pExtension, "", pStartIndex);
    if(aCheck >= 0)return aCheck;
    
    aCheck = CountLeadingZeros(pBaseFile, pExtension, gSandbox.c(), pStartIndex);
    if(aCheck >= 0)return aCheck;
    
    aCheck = CountLeadingZeros(pBaseFile, pExtension, gDocuments.c(), pStartIndex);
    if(aCheck >= 0)return aCheck;
    
    return 0;
}

int CountLeadingZeros(const char *pBaseFile, const char *pExtension, const char*pPrefix, int pStartIndex)
{
    FString aBasePath = FString(pPrefix) + FString(pBaseFile);
    FString aNumberString = FString(((int)pStartIndex));
    FString aExtension = FString(".") + pExtension;
    FString aFile;
    aFile.Write(aBasePath,0);
    for(int aLeadingZeroCount=0;aLeadingZeroCount<10;aLeadingZeroCount++)
    {
        int aLengthDifference = aLeadingZeroCount - aNumberString.mLength;
        if(aLengthDifference > 0)aNumberString.Insert('0', aLengthDifference, 0);
        aFile.Write(aNumberString,aBasePath.mLength);
        aFile.Write(aExtension.c(),aBasePath.mLength + aNumberString.mLength);
        if(FileExists(aFile.c()))
        {
            return aLeadingZeroCount;
        }
    }
    return -1;
}




