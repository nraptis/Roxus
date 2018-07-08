/*
 *  Font.h
 *  Word Master
 *
 *  Created by Nick Raptis on 6/26/10.
 *  Copyright 2010 Raptisoft LLC. All rights reserved.
 *
 */

#ifndef SUPER_FONT_H
#define SUPER_FONT_H

#include "Sprite.h"

class FontLetter
{
public:
	Sprite				mSprite;
	int					mSpacing[256];
};

class Font
{
public:
	Font();
	~Font();
	
	FontLetter			mLetter[256];
	
	float				mSpaceWidth;
	float				mLineHeight;
	float				mPadding;
	
	inline float		Spacing(char *pString){return Spacing(*pString,*(pString+1));}
	float				Spacing(char pChar, char pNext);
	
	inline void			Load(FString pFile){Load(pFile.c());}
	inline void			Load(const char *pFile){Load((char*)pFile);}
	void				Load(char *pFile);
	
	inline void			LoadWithSplat(FString pFile){LoadWithSplat(pFile.c());}
	inline void			LoadWithSplat(const char *pFile){LoadWithSplat((char*)pFile);}
	void				LoadWithSplat(char *pFile);
	
	inline void			Draw(FString pString, float x, float y){Draw((char*)pString.c(),x,y);}
	inline void			Draw(const char *pString, float x, float y){Draw((char*)pString,x,y);}
	void				Draw(char *pString, float x, float y);
	
	
	inline void			Center(const char *pString, FPoint pPos){Center((char*)pString,pPos.mX,pPos.mY);}
	inline void			Center(char *pString, FPoint pPos){Center(pString,pPos.mX,pPos.mY);}
	inline void			Center(const char *pString, float x, float y){Center((char*)pString,x,y);}
	void				Center(char *pString, float x, float y);
	
	inline void			Right(const char *pString, float x, float y){Center((char*)pString,x,y);}
	void				Right(char *pString, float x, float y);
	
	inline float		Width(FString pString){return Width(pString.c());}
	float				Width(char *pString);
	
	void				Draw(char *pString, float x, float y, float pWidth);
	int					LineCount(char *pString, float pWidth);
};

#endif