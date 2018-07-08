//
//  FileSequence.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 1/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FileSequence.h"
#include "Buffer.h"

FileSequence::FileSequence()
{
    
}

FileSequence::~FileSequence()
{
    
}


bool FileSequence::LoadSequence(const char *pFileBase, const char *pExtension, List &pList, int pStartIndex, int pEndIndex, int pLeadingZeroCount)
{
    bool aReturn = false;
    
    FString aFileBase = pFileBase;
    FString aExtension = pExtension;
    FString aNumberString = FString(pStartIndex);
    
    if(aNumberString.mLength < pLeadingZeroCount)
    {
        FString aZeroString;
        aZeroString.Write('0', (pLeadingZeroCount - aNumberString.mLength), 0);
        aNumberString = (aZeroString + aNumberString);
    }
    
    FString aCheck = (aFileBase + aNumberString + FString(".") + aExtension);
    if(FileExists(aCheck.c()))
    {
        pList += new FString(aCheck);
        aReturn=true;
    }
    
    if(aReturn == false)
    {
        aCheck = (gSandbox + aFileBase + aNumberString + FString(".") + aExtension);
        if(FileExists(aCheck.c()))
        {
            pList += new FString(aCheck);
            aFileBase = (gSandbox + aFileBase);
            aReturn=true;
        }
    }
    
    if(aReturn == false)
    {
        aCheck = (gDocuments + aFileBase + aNumberString + FString(".") + aExtension);
        if(FileExists(aCheck.c()))
        {
            pList += new FString(aCheck);
            aFileBase = (gDocuments + aFileBase);
            aReturn=true;
        }
    }
    
    if(aReturn)
    {
        for(int aIndex=pStartIndex+1;((aIndex<=pEndIndex) || (pEndIndex == -1));aIndex++)
        {
            aNumberString = FString(aIndex);
            if(aNumberString.mLength < pLeadingZeroCount)
            {
                FString aZeroString;
                aZeroString.Write('0', (pLeadingZeroCount - aNumberString.mLength), 0);
                aNumberString = (aZeroString + aNumberString);
            }
            
            aCheck = (aFileBase + aNumberString + FString(".") + aExtension);
            
            if(FileExists(aCheck.c()))
            {
                pList += new FString(aCheck);
            }
            else
            {
                break;
            }
        }
    }
    return aReturn;
}

bool FileSequence::LoadSequence(const char *pFileBase, const char *pExtension, List &pList, int pStartIndex, int pEndIndex)
{
    bool aReturn = false;
    for(int aLeadingZeros=1;((aLeadingZeros<8) && (aReturn==false));aLeadingZeros++)
    {
        aReturn = LoadSequence(pFileBase, pExtension, pList, pStartIndex, pEndIndex, aLeadingZeros);
    }
    return aReturn;
}

bool FileSequence::LoadSequence(const char *pFileBase, List &pList, int pStartIndex, int pEndIndex)
{
    bool aReturn = false;
    
    if(!aReturn)
    {
        aReturn = LoadSequence(pFileBase, "png", pList, pStartIndex, pEndIndex);
    }
    if(!aReturn)
    {
        aReturn = LoadSequence(pFileBase, "jpg", pList, pStartIndex, pEndIndex);
    }
    if(!aReturn)
    {
        aReturn = LoadSequence(pFileBase, "obj", pList, pStartIndex, pEndIndex);
    }
    
    return aReturn;
}





