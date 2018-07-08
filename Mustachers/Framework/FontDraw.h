
//
//  FontDraw.h
//  CrazyDartsArc
//
//  Created by Nick Raptis on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
//

#ifndef FONT_DRAW_H
#define FONT_DRAW_H

#include "Sprite.h"

class FontDraw
{
public:
    
    FontDraw();
    ~FontDraw();
    
    char                *mData;
    int                 mSize;
    int                 mWriteIndex;
    
    float               mMaxWidth;
    float               mMaxHeight;
    
    FString             mPrefix;
    
    void                Reset();
    
    Sprite              mSprite[256];
    float               mSpacingBefore[256];
    float               mSpacingAfter[256];
    
    void                Write(const char *pText);
    void                WriteNumber(int pNumber);
    
    void                Draw(float pX, float pY);
    void                Right(float pX, float pY);
    void                Center(float pX, float pY);
    
    void                DrawTime(float pX, float pY, int pHours, int pMinutes, int pSeconds);
    
    void                Center(float pX, float pY, float pScale);
    
    float               Width(char *pText);
    float               Width(){return Width(mData);}
    
    void                PadLength(int pLengthPad);
    
    float               mVerticalHeight;
    float               mVerticalSpacing;
    
    void                LoadRange(char pStart, char pEnd, const char *pFilePrefix);
    
    void                LoadAlphaNumeric(const char *pFilePrefix);
    
    void                Load(char *pCharacters, const char *pFilePrefix=0);
    
};

#endif








