#include "XML.h"
#include "Buffer.h"
#include "stdafx.h"

XML::XML()
{
	mRoot=0;
	mOutput=0;
	mOutputSize=0;
	mOutputLength=0;
}

XML::~XML()
{
	Clear();
}

void XML::Clear()
{
	if(mRoot)delete mRoot;
	mRoot=0;
	delete[]mOutput;
	mOutput=0;
	mOutputSize=0;
	mOutputLength=0;
}



char *SkipQuote(char *pSeek)
{
	char *aSeek=pSeek;
	if(*aSeek=='\"')
	{
		aSeek++;
		while(*aSeek&&*aSeek!='\"')aSeek++;
	}
	return aSeek;
}

//*pSeek= ! or ?
//returns *'>' if not error..
char *SkipComment(char *pSeek)
{
	char *aSeek=pSeek;
	
	
	while(*aSeek&&*aSeek<=32)aSeek++;

		
		int aBraceDepth=1;
		START_SKIP_COMMENT:
		while(*aSeek&&
			  *aSeek!='<'&&
			  *aSeek!='\"'&&
			  *aSeek!='>')aSeek++;
	
		if(*aSeek=='\"')
		{
			aSeek=SkipQuote(aSeek);
			if(*aSeek=='\"')aSeek++;
			goto START_SKIP_COMMENT;
		}
		if(*aSeek=='<')
		{
			aSeek++;
			aBraceDepth++;
			goto START_SKIP_COMMENT;
		}
		if(*aSeek=='>')
		{
			if(aBraceDepth!=1)
			{
				aSeek++;
				aBraceDepth--;
				goto START_SKIP_COMMENT;
			}
		}
	
	return aSeek;
}

void XML::ExportAppend(char *pText)
{
	if(!pText)return;
	int aStrLen=0;
	char *aPtr=pText;
	while(*aPtr)aPtr++;
	aStrLen=aPtr-pText;
	
	int aLen=mOutputLength+aStrLen;
	if(aLen>=mOutputSize)
	{
		mOutputSize=aLen+aLen/2+1;
		char *aNew=new char[mOutputSize+1];
		memcpy(aNew,mOutput,mOutputLength);
		delete[]mOutput;
		mOutput=aNew;
	}
	//printf("Length -> %d  [%d]\n", mOutputLength, mOutputLength+aStrLen, mOutputSize);
	memcpy(mOutput+mOutputLength,pText,aStrLen);
	mOutput[aLen]=0;
	mOutputLength=aLen;
}


void XML::Export()
{
	delete[]mOutput;
	mOutput=0;
	mOutput=new char[1];
	mOutput[0]=0;
	mOutputLength=0;
	mOutputSize=0;
	if(mRoot)Export(0,mRoot);
}

void XML::Export(int depth, XMLTag *tag)
{
	if(!tag)return;
	
	for(int aTabIndex=0;aTabIndex<depth;aTabIndex++)ExportAppend("\t");
	
	ExportAppend("<");
	ExportAppend(tag->mName);
	
	for(int i=0;i<tag->mParameters.mCount;i++)
	{
		//if(i != tag->mParameters.mCount-1)
		ExportAppend(" ");
		ExportAppend(tag->mParameters.mElement[i]->mName);
		ExportAppend("=\"");
		ExportAppend(tag->mParameters.mElement[i]->mValue);
		ExportAppend("\"");
	}

	
	if(tag->mValue)
	{
		ExportAppend(">");
		ExportAppend(tag->mValue);
		ExportAppend("</");
		ExportAppend(tag->mName);
		ExportAppend(">\n");
	}
	else
	{
		if(tag->mTags.mCount>0)
		{
			ExportAppend(">");
			ExportAppend("\n");
			for(int i=0;i<tag->mTags.mCount;i++)
			{
				Export(depth+1,(XMLTag*)tag->mTags.mElement[i]);
			}
			for(int aTabIndex=0;aTabIndex<depth;aTabIndex++)ExportAppend("\t");
			ExportAppend("</");
			ExportAppend(tag->mName);
			//printf("Tag... [%s]\n", tag->mName);
			ExportAppend(">\n");
		}
		else
		{
			ExportAppend("/>\n");
		}
	}
}

void XML::Print()
{
	Export();
	if(mOutput)
    {
        printf((const char*)mOutput);
    }
}

void XML::Save(char *pFile)
{
    Export();
    if(mOutput)
    {
        Buffer aBuffer;
        aBuffer.Write(mOutput, mOutputLength);
        aBuffer.Save(pFile);
    }
}

void XML::Load(char *pFile)
{
	Buffer aBuffer;
	aBuffer.Load(pFile);
	Parse((char*)aBuffer.mData, aBuffer.mLength);
}

void XML::Parse(char *pData, int pLength)
{
	Clear();
	
	if(!pData||(pLength<0))return;
	
	int aError=0;
	
	int aStackCount=0;
	int aStackSize=1;
	XMLTag**aStack=new XMLTag*[aStackSize];
	XMLTag**aNewStack;
	XMLTag*aParent;
	XMLTag*aTag=0;
	XMLParameter *aParam;
	
	aStack[0]=0;
	
	char *aName=0;
	char *aValue=0;
	
	int aLength;
	
	bool aFoundEscape;
	
	char *aHold;
	char *aCheck;
	
	char *aData=new char[pLength+1];
	aData[pLength]=0;
	memcpy(aData,pData,pLength);
	
	char *aSeek=aData;
	
	//Search for initial open bracket...
FIND_ROOT_TAG:
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek!='<')goto ERROR;
	aSeek++;
	
	//Skip White Space..
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek==0)goto ERROR;
	if(*aSeek=='!'||*aSeek=='?')
	{
		aSeek=SkipComment(aSeek);
		if(*aSeek!='>')goto ERROR;
		aSeek++;
		goto FIND_ROOT_TAG;
	}
	
	//Tag Name
	if(!XML_VARIABLE_START(*aSeek))goto ERROR;
	aHold=aSeek;
	aSeek++;
	while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
	if(*aSeek==0)goto ERROR;
	aLength=aSeek-aHold;
	aName=new char[aLength+1];
	memcpy(aName,aHold,aLength);
	aName[aLength]=0;
	//End Tag Name
	
	//Create the tag..
	mRoot=new XMLTag();
	mRoot->mName=aName;
	aName=0;
	
	//Keep on parsing it I guess.. We need to look for parameters...
FIND_ROOT_PARAMETERS:
	//Skip white space..
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek==0)goto ERROR;
	if(XML_VARIABLE_START(*aSeek))
	{
		//Parameter Name
		aHold=aSeek;
		aSeek++;
		while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
		if(*aSeek==0)goto ERROR;
		aLength=aSeek-aHold;
		aName=new char[aLength+1];
		memcpy(aName,aHold,aLength);
		aName[aLength]=0;
		
		//=
		while(*aSeek&&*aSeek<=32)aSeek++;
		if(*aSeek!='=')goto ERROR;
		aSeek++;
		while(*aSeek&&*aSeek<=32)aSeek++;
		//Stuff in quotes
		if(*aSeek!='\"')goto ERROR;
		aSeek++;
		aHold=aSeek;
		while(*aSeek&&*aSeek!='\"')aSeek++;
		//endquotes
		if(*aSeek!='\"')goto ERROR;
		aLength=aSeek-aHold;
		aValue=new char[aLength+1];
		aValue[aLength]=0;
		memcpy(aValue,aHold,aLength);
		
		aParam=new XMLParameter();
		aParam->mName=aName;
		aParam->mValue=aValue;
		
		aName=0;
		aValue=0;
		
		*mRoot+=aParam;
		
		aSeek++;
		
		goto FIND_ROOT_PARAMETERS;
	}
	
	if(*aSeek=='/')
	{
		aSeek++;
		while(*aSeek&&*aSeek<=32)aSeek++;
		if(*aSeek!='>')goto ERROR;
		//Ok, we had a single self-terminating root tag
		goto SUCCESS;
	}
	
	if(*aSeek!='>')goto ERROR;
	aSeek++;
	
	//Start up the stack!
	aStack[0]=mRoot;
	aStackCount=1;
	aParent=mRoot;
	
	//Now, we may either have subtags, or a body!
	
	//We are on post <name>{RIGHT HERE} whitespace/body/subtags
BEGIN_STACK_LOOP:
	
	if(aStackCount<=0)
	{
		//Do we really wanna check for illegal trailing tags?
		//Nahhhhh... Later maybe
		goto SUCCESS;
	}
	
	aParent=aStack[aStackCount-1];
	
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek=='>'||*aSeek==0)goto ERROR;
	if(*aSeek=='<')
	{
		aSeek++;
		while(*aSeek&&*aSeek<=32)aSeek++;
		
		if(*aSeek=='!'||*aSeek=='?')
		{
			aSeek=SkipComment(aSeek);
			if(*aSeek!='>')goto ERROR;
			aSeek++;
			goto BEGIN_STACK_LOOP;
		}
		
		//Closing Tag... it BETTER damn well be the parent tag
		if(*aSeek=='/')
		{
			aSeek++;
			while(*aSeek&&*aSeek<=32)aSeek++;
			if(!XML_VARIABLE_START(*aSeek))goto ERROR;
			
			aHold=aSeek;
			aSeek++;
			while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
			if(*aSeek==0)goto ERROR;
			
			aCheck=aParent->mName;
			
			while(aHold<aSeek&&*aCheck&&*aHold==*aCheck)
			{
				aCheck++;
				aHold++;
			}
			
			if(*aCheck||(aHold<aSeek))goto ERROR;
			
			while(*aSeek&&*aSeek<=32)aSeek++;
			
			if(*aSeek!='>')goto ERROR;
			aSeek++;//move past end brace..
			
			//
			//We pop the stack when we get a closing tag...
			//
			aStackCount--;
			goto BEGIN_STACK_LOOP;
		}
		//non-closing tag it seems
		else
		{
			if(aParent->mValue)goto ERROR;
			
			while(*aSeek&&*aSeek<=32)aSeek++;
			if(!XML_VARIABLE_START(*aSeek))goto ERROR;
			aHold=aSeek;
			aSeek++;
			while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
			if(*aSeek==0)goto ERROR;
			
			aLength=aSeek-aHold;
			aName=new char[aLength+1];
			memcpy(aName,aHold,aLength);
			aName[aLength]=0;
			
			aTag=new XMLTag();
			aTag->mName=aName;
			*aParent+=aTag;
			
			//We always add our opening tag to the stack? k.
			if(aStackCount==aStackSize)
			{
				aStackSize=aStackSize+aStackSize+1;
				aNewStack=new XMLTag*[aStackSize];
				for(int i=0;i<aStackCount;i++)aNewStack[i]=aStack[i];
				delete[]aStack;
				aStack=aNewStack;
			}
			aStack[aStackCount++]=aTag;
			
			aName=0;
			
			
			
		FIND_PARAMETERS:
			//Skip white space..
			while(*aSeek&&*aSeek<=32)aSeek++;
			if(*aSeek==0)goto ERROR;
			if(XML_VARIABLE_START(*aSeek))
			{
				//Parameter Name
				aHold=aSeek;
				aSeek++;
				while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
				if(*aSeek==0)goto ERROR;
				aLength=aSeek-aHold;
				aName=new char[aLength+1];
				memcpy(aName,aHold,aLength);
				aName[aLength]=0;
				
				//=
				while(*aSeek&&*aSeek<=32)aSeek++;
				if(*aSeek!='=')goto ERROR;
				aSeek++;
				while(*aSeek&&*aSeek<=32)aSeek++;
				//Stuff in quotes
				if(*aSeek!='\"')goto ERROR;
				aSeek++;
				aHold=aSeek;
				while(*aSeek&&*aSeek!='\"')aSeek++;
				//endquotes
				if(*aSeek!='\"')goto ERROR;
				aLength=aSeek-aHold;
				aValue=new char[aLength+1];
				aValue[aLength]=0;
				memcpy(aValue,aHold,aLength);
				
				aParam=new XMLParameter();
				aParam->mName=aName;
				aParam->mValue=aValue;
				
				//if()
				
				aName=0;
				aValue=0;
				
				*aTag+=aParam;
				
				aSeek++;
				
				
				goto FIND_PARAMETERS;
			}
			
			if(*aSeek=='/')
			{
				aSeek++;
				while(*aSeek&&*aSeek<=32)aSeek++;
				if(*aSeek!='>')goto ERROR;
				aStackCount--;
			}
			
			if(*aSeek!='>')goto ERROR;
			aSeek++;
			goto BEGIN_STACK_LOOP;
		}
	}
	
	
	//WE WILL ATTEMPT TO TREAT THIS LIKE AN XML BODY TAG THING..
	
	//We will skip initial and end white spaces...
	//except for SPACEBAR 32 space itself...
	
	if(aParent->mTags.mCount>0)goto ERROR;
	
	while(*aSeek&&*aSeek<32)aSeek++;
	if(*aSeek==0)goto ERROR;
	
	aHold=aSeek;
	while(*aSeek&&*aSeek!='<')aSeek++;
	if(*aSeek==0)goto ERROR;
	
	aLength=aSeek-aHold;
	
	aValue=new char[aLength+1];
	memcpy(aValue,aHold,aLength);
	memset(aValue,0,aLength);
	aValue[aLength]=0;
	aCheck=aValue;
	while(aHold<aSeek)
	{
		while(aHold<aSeek
			  //&&*aHold!='&'
			  )*aCheck++=*aHold++;
		/*if(*aHold=='&')
		 {
		 aFoundEscape=false;
		 if(aHold+5<aSeek)
		 {
		 if(*(aHold+1)=='a'&&
		 *(aHold+2)=='p'&&
		 *(aHold+3)=='o'&&
		 *(aHold+4)=='s'&&
		 *(aHold+5)==';')
		 {
		 *aCheck++='\'';
		 aFoundEscape=true;
		 aHold+=6;
		 }
		 else if(*(aHold+1)=='q'&&
		 *(aHold+2)=='u'&&
		 *(aHold+3)=='o'&&
		 *(aHold+4)=='t'&&
		 *(aHold+5)==';')
		 {
		 *aCheck++='\"';
		 aFoundEscape=true;
		 aHold+=6;
		 }
		 }
		 if(aHold+4<aSeek&&aFoundEscape==false)
		 {
		 if(*(aHold+1)=='a'&&
		 *(aHold+2)=='m'&&
		 *(aHold+3)=='p'&&
		 *(aHold+4)==';')
		 {
		 *aCheck++='&';
		 aFoundEscape=true;
		 aHold+=5;
		 }
		 }
		 if(aHold+3<aSeek&&aFoundEscape==false)
		 {
		 if(*(aHold+1)=='g'&&
		 *(aHold+2)=='t'&&
		 *(aHold+3)==';')
		 {
		 *aCheck++='>';
		 aFoundEscape=true;
		 aHold+=4;
		 }
		 else if(*(aHold+1)=='l'&&
		 *(aHold+2)=='t'&&
		 *(aHold+3)==';')
		 {
		 *aCheck++='<';
		 aFoundEscape=true;
		 aHold+=4;
		 }
		 }
		 if(!aFoundEscape)
		 {
		 //goto ERROR;
		 
		 //How about.. if it's not an escape sequence
		 //we just allow the ampersand lol..
		 *aCheck++=*aHold++;
		 }
		 }*/
	}
	while(aCheck>aValue&&*aCheck<32)
	{
		*aCheck--=0;
	}
	aParent->mValue=aValue;
	aValue=0;
	goto BEGIN_STACK_LOOP;
	
ERROR:
	Clear();
	printf("***XML Parse Error***\n");
	aError=1;
SUCCESS:
	delete[]aData;
	delete[]aStack;
	delete[]aName;
	delete[]aValue;
	if(!aError)
	{
		//printf("XML Parse Success :(\n");
	}
}


XMLTag *XML::GetNestedTag1(char *pName1)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		return aSubTag1;
	}
	return 0;
}

XMLTag *XML::GetNestedTag2(char *pName1, char *pName2)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		EnumTagsMatching(aSubTag1,aSubTag2,pName2)
		{
			return aSubTag2;
		}
	}
	return 0;
}

XMLTag *XML::GetNestedTag3(char *pName1, char *pName2, char *pName3)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		EnumTagsMatching(aSubTag1,aSubTag2,pName2)
		{
			EnumTagsMatching(aSubTag2,aSubTag3,pName3)
			{
				return aSubTag3;
			}
		}
	}
	return 0;
}

XMLTag *XML::GetNestedTag4(char *pName1, char *pName2, char *pName3, char *pName4)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		EnumTagsMatching(aSubTag1,aSubTag2,pName2)
		{
			EnumTagsMatching(aSubTag2,aSubTag3,pName3)
			{
				EnumTagsMatching(aSubTag3,aSubTag4,pName4)
				{
					return aSubTag4;
				}
			}
		}
	}
	return 0;
}


void XMLElementList::Clear()
{
	for(int i=0;i<mCount;i++)delete mElement[i];
	delete[]mElement;
	mElement=0;
	mCount=0;
}

void XMLElementList::operator += (XMLElement *theElement)
{
	if(mCount==mSize)
	{
		mSize=mSize+(mSize>>1)+1;
		XMLElement**aElement=new XMLElement*[mSize];
		for(int i=0;i<mCount;i++)aElement[i]=mElement[i];
		delete[]mElement;
		mElement=aElement;
	}
	mElement[mCount++]=theElement;
}

char *XMLTag::GetParamValue(char *pName, const char*pDefault)
{
	EnumParamsMatching(this,aCheck,pName)return aCheck->mValue;
	return (char*)pDefault;
}



char *XMLTag::GetSubtagValue(char *pName, const char*pDefault)
{
    EnumTagsMatching(this, aCheck, pName)return aCheck->mValue;
	return (char*)pDefault;
}



void XMLElement::SetName(char *pString)
{
    char *aString = 0;
    if(pString)
    {
        char *aPtr=(char*)pString;
        while(*aPtr)aPtr++;
        int aLength = (int)(aPtr-(char*)pString);
        aString = new char[aLength+1];
        aPtr=aString;
        while(*pString)
        {
            *aString = *pString;
            pString++;
            aString++;
        }
        aString=aPtr;
        aString[aLength]=0;
    }
    mName=aString;
}

void XMLElement::SetValue(char *pString)
{
    char *aString = 0;
    if(pString)
    {
        char *aPtr=(char*)pString;
        while(*aPtr)aPtr++;
        int aLength = (int)(aPtr-(char*)pString);
        aString = new char[aLength+1];
        aPtr=aString;
        while(*pString)
        {
            *aString = *pString;
            pString++;
            aString++;
        }
        aString=aPtr;
        aString[aLength]=0;
    }
    mValue=aString;
}

void XMLTag::AddParam(const char* pName, const char* pValue)
{
    XMLParameter *aParam = new XMLParameter();
    
    aParam->SetName(pName);
    aParam->SetValue(pValue);
    
    *this += aParam;
}

void XMLTag::AddTag(const char* pName, const char* pValue)
{
    XMLTag *aTag=new XMLTag();
    
    aTag->SetName(pName);
    aTag->SetValue(pValue);
    
    *this += aTag;
}

