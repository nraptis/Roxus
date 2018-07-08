// (C) 2006-2009 Nick Rapis

#include "FString.h"


#ifndef XML_H
#define XML_H

#define EnumTags(_tag,_subtag_name)for(XMLTag **_enum_start=(XMLTag**)_tag->mTags.mElement,**_enum_end=((_tag->mTags.mCount > 0)?((XMLTag**)(&(_tag->mTags.mElement[_tag->mTags.mCount]))) : ((XMLTag**)0)),*_subtag_name=((_tag->mTags.mCount > 0)?(*_enum_start):((XMLTag*)0));_subtag_name!=((XMLTag*)0);_subtag_name=(++_enum_start<_enum_end)?*_enum_start:NULL)

#define EnumParams(_tag,_param_name)for(XMLParameter **_enum_start=(XMLParameter**)_tag->mParameters.mElement,**_enum_end=((_tag->mParameters.mCount > 0)?((XMLParameter**)(&(_tag->mParameters.mElement[_tag->mParameters.mCount]))):((XMLParameter**)0)),*_param_name=((_tag->mParameters.mCount > 0)?(*_enum_start):((XMLParameter*)0));_param_name!=((XMLParameter*)0);_param_name=(++_enum_start<_enum_end)?*_enum_start:NULL)

#define EnumTagsMatching(_tag,_subtag_name,_name)EnumTags(_tag,_subtag_name)if(_subtag_name->mName&&_name)if(strcmp(_subtag_name->mName,_name)==0)
#define EnumParamsMatching(_tag,_param_name,_name)EnumParams(_tag,_param_name)if(strcmp(_param_name->mName,_name)==0)

#define XML_VARIABLE_START(c) (((c>='a'&&c<='z')||(c>='A'&&c<='Z'))||c=='_'||c=='$')
#define XML_VARIABLE_BODY(c) (((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))||c=='_'||c=='$')

class XMLElement
{
public:
	XMLElement(){mName=0;mValue=0;}
    
	virtual ~XMLElement(){delete[]mName;mName=0;delete[]mValue;mValue=0;}
    
    void            SetName(char *pName);
    void            SetName(const char *pName){SetName((char*)pName);}
    
    void            SetValue(char *pValue);
    void            SetValue(const char *pValue){SetValue((char*)pValue);}
    
	char            *mName;
	char            *mValue;
};

class XMLElementList
{
public:
	XMLElementList(){mElement=0;mCount=0;mSize=0;}
	~XMLElementList(){Clear();}
	void					Clear();
	void					operator += (XMLElement *theElement);
	inline XMLElement		*operator[](int theSlot){if(theSlot>=0&&theSlot<mCount)return mElement[theSlot];else return 0;}
	XMLElement				**mElement;
	int						mCount;
	int						mSize;
};


class XMLParameter : public XMLElement
{
public:
	
    XMLParameter(const char *pName=0, const char *pValue=0){XMLElement();mName=0;mValue=0;XMLElement();SetName(pName);SetValue(pValue);}
    
};

class XMLTag : public XMLElement
{
public:
    XMLTag(const char *pName=0, const char *pValue=0){XMLElement();mName=0;mValue=0;XMLElement();SetName(pName);SetValue(pValue);}
    
	virtual				~XMLTag(){delete[]mName;delete[]mValue;mName=0;mValue=0;}
	inline void			operator += (XMLTag *theTag){mTags += theTag;}
	inline void			operator += (XMLParameter *theParam){mParameters += theParam;}
	
	char				*GetParamValue(char *pName, const char*pDefault=0);
	inline char			*GetParamValue(const char *pName, const char*pDefault=0){return GetParamValue((char*)pName);}
	inline char			*GetParamValue(FString pName, const char*pDefault=0){return GetParamValue((char*)pName.c());}
    
    
    char				*GetSubtagValue(char *pName, const char*pDefault=0);
	inline char			*GetSubtagValue(const char *pName, const char*pDefault=0){return GetSubtagValue((char*)pName);}
	inline char			*GetSubtagValue(FString pName, const char*pDefault=0){return GetSubtagValue((char*)pName.c());}
    
    void                AddTag(const char* pName, const char* pValue);
    void                AddParam(const char* pName, const char* pValue);
	
	XMLElementList		mTags;
	XMLElementList		mParameters;
};

class XML
{
public:
    
	XML();
	~XML();
	
	void				Load(char *pFile);
	inline void			Load(const char *pFile){Load((char*)pFile);}
	inline void			Load(FString pFile){Load(pFile.c());}
    
    
    void                Save(char *pFile);
    inline void			Save(const char *pFile){Save((char*)pFile);}
	inline void			Save(FString pFile){Save(pFile.c());}
	
	void				Parse(char *pData, int pLength);
	
	void				Print();
	void				Export();
	void				Export(int depth, XMLTag *tag);
	void				ExportAppend(char *pText);
	inline void			ExportAppend(const char *pText){ExportAppend((char*)pText);}
	
	
	XMLTag				*GetNestedTag1(char *pName1);
	inline XMLTag		*GetNestedTag1(FString pName1){return GetNestedTag1(pName1.c());}
	
	XMLTag				*GetNestedTag2(char *pName1, char *pName2);
	inline XMLTag		*GetNestedTag2(FString pName1, FString pName2){return GetNestedTag2(pName1.c(),pName2.c());}
	
	XMLTag				*GetNestedTag3(char *pName1, char *pName2, char *pName3);
	inline XMLTag		*GetNestedTag3(FString pName1, FString pName2, FString pName3){return GetNestedTag3(pName1.c(),pName2.c(),pName3.c());}
	
	XMLTag				*GetNestedTag4(char *pName1, char *pName2, char *pName3, char *pName4);
	inline XMLTag		*GetNestedTag4(FString pName1, FString pName2, FString pName3, FString pName4){return GetNestedTag4(pName1.c(),pName2.c(),pName3.c(),pName4.c());}
	
	
	void				Clear();
	
	inline XMLTag		*GetRoot(){return mRoot;}
	
	XMLTag				*mRoot;
	
	
	char				*mOutput;
	int					mOutputSize;
	int					mOutputLength;
};

char *SkipQuote(char *pSeek);
char *SkipComment(char *pSeek);

#endif
