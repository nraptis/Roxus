//
//  FResource.cpp
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FResource.h"
#include "core_includes.h"

FResourceManager gRes;


FResource::FResource()
{
    //mPath;
    //mName;
    
    //mInstanceCount = 0;
    //mResourceType = RESOURCE_TYPE_UNKNOWN;
    
    //mHashBase = 0;
    
    //mNext = 0;
}

FResource::~FResource() {

}

FResourceManager::FResourceManager() {
    mTable.mAllowDuplicateKeys = true;
    mTable.mAllowDuplicateFullKeys = false;
    mSearchIndex = 0;
}

FResourceManager::~FResourceManager() {

}

FResource *FResourceManager::AddResource(const char *pResourcePath, bool pPrint) {
    FResource *aResult = 0;
    
	FString aName = ResourceName(pResourcePath);
    FString aFullPath = FString(pResourcePath);
	FString aExtension = aFullPath.GetExtension();

    aExtension = aExtension.ToLower();
    
    if((aName.mLength > 0) && (aFullPath.mLength > 0) && (aExtension.mLength > 0))
    {
        aResult = new FResource();
        aResult->mName = aName;
        aResult->mExtension = aExtension;
        aResult->mResourceType = 0;

        if((aExtension == "png") || (aExtension == "jpg") || (aExtension == "jpeg") || (aExtension == "gif") || (aExtension == "tga") || (aExtension == "bmp"))
        {
            (aResult->mResourceType) |= RESOURCE_TYPE_IMAGE;
        }
        else if((aExtension == "caf") || (aExtension == "aif") || (aExtension == "aiff") || (aExtension == "wav") || (aExtension == "ogg") || (aExtension == "pcm"))
        {
            (aResult->mResourceType) |= RESOURCE_TYPE_SOUND_EFFECT;
            (aResult->mResourceType) |= RESOURCE_TYPE_AUDIO;
            
        }
        else if((aExtension == "mp3") || (aExtension == "mod") || (aExtension == "midi"))
        {
            (aResult->mResourceType) |= RESOURCE_TYPE_MUSIC;
            (aResult->mResourceType) |= RESOURCE_TYPE_AUDIO;
        }
        else if((aExtension == "xml") || (aExtension == "cml"))
        {
            (aResult->mResourceType) |= RESOURCE_TYPE_XML;
        }
        else if((aExtension == "dat") || (aExtension == "sav"))
        {
            (aResult->mResourceType) |= RESOURCE_TYPE_BINARY;
        }
        
        mTable.Add(aName.c(), pResourcePath, aResult);
        mResourceList.Add(aResult);

        if(pPrint)
        {
            FString aTypeString = "";
            //Log("+++[New Recource]+++ (%s) [%s]", aName.c(), aExtension.c());
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_IMAGE) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "IMG";
                else aTypeString += ", IMG";
            }
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_AUDIO) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "AUDIO";
                else aTypeString += ", AUDIO";
            }
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_SOUND_EFFECT) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "SFX";
                else aTypeString += ", SFX";
            }
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_MUSIC) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "MUSIC";
                else aTypeString += ", MUSIC";
            }
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_BINARY) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "BIN";
                else aTypeString += ", BIN";
            }
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_CONFIG) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "CONFIG";
                else aTypeString += ", CONFIG";
            }
            
            if(((aResult->mResourceType) & RESOURCE_TYPE_BUNDLE) != 0)
            {
                if(aTypeString.mLength <= 0)aTypeString += "BUNDLE";
                else aTypeString += ", BUNDLE";
            }
            
            if(aTypeString.mLength > 0)
            {
                Log(" {{ %s }}\n", aTypeString.c());
            }
            else Log("\n");
        }
    }
    else
    {
        if(pPrint)
        {
            Log("--[[Already Had Resource]] -- (%s)\n", aName.c());
        }
    }
    
    return aResult;
}

FString FResourceManager::ResourceName(const char *pFilePath)
{
    FString aFullPath = FString(pFilePath);
    FString aName;// = aFullPath;
    int aPathIndex = aFullPath.GetPathIndex();
    if((aPathIndex >= 0) && (aPathIndex < aFullPath.mLength))
    {
        aName = aFullPath.GetSubString(aPathIndex, ((aFullPath.mLength - aPathIndex) + 1));
    }
    aName.RemoveExtension();
    return aName;
}

const char *FResourceManager::GetResourcePath(const char *pFileName)
{
	const char *aResult = 0;
    FString aName = ResourceName(pFileName);
    mSearchResults.RemoveAll();
    mTable.GetAllNodes(aName.c(), mSearchResults);
    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(0));
    if(aNode)
    {
        mSearchIndex = 1;
        aResult = aNode->mKeyFull.c();
    }
    else
    {
        mSearchIndex = 0;
    }
	return aResult;
}

const char *FResourceManager::GetResourcePathOfType(const char *pFileName, int pType)
{
    const char *aResult = 0;
    
    GetResourcePath(pFileName);
    
    mSearchResultsFilter.RemoveAll();
    
    EnumList(FHashTableNode, aNode, mSearchResults)
    {
        FResource *aResource = ((FResource *)(aNode->mObject));
        if(aResource)
        {
            if(((aResource->mResourceType) & pType) != 0)
            {
                mSearchResultsFilter.Add(aNode);
            }
        }
    }
    
    mSearchResults.RemoveAll();
    EnumList(FHashTableNode, aNode, mSearchResultsFilter)mSearchResults.Add(aNode);

    mSearchResultsFilter.RemoveAll();

    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(0));
    if(aNode)
    {
        mSearchIndex = 1;
        aResult = aNode->mKeyFull.c();
    }
    else
    {
        mSearchIndex = 0;
    }
    
    return aResult;
}

const char *FResourceManager::GetResourcePathImage(const char *pFileName) {
    
    return GetResourcePathOfType(pFileName, RESOURCE_TYPE_IMAGE);
    
    /*
	const char *aResult = 0;
    
    GetResourcePath(pFileName);
    
    mSearchResultsFilter.RemoveAll();
    
    EnumList(FHashTableNode, aNode, mSearchResults)
    {
        FResource *aResource = ((FResource *)(aNode->mObject));
        if(aResource)
        {
            if(((aResource->mResourceType) & RESOURCE_TYPE_IMAGE) != 0)
            {
                mSearchResultsFilter.Add(aNode);
            }
        }
    }
    
    mSearchResults.RemoveAll();
    
    EnumList(FHashTableNode, aNode, mSearchResultsFilter)mSearchResults.Add(aNode);
    
    mSearchResultsFilter.RemoveAll();
    
    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(0));
    if(aNode)
    {
        mSearchIndex = 1;
        aResult = aNode->mKeyFull.c();
    }
    else mSearchIndex = 0;
    return aResult;
    */
    
}

const char *FResourceManager::GetResourcePathSound(const char *pFileName)
{
    
    return GetResourcePathOfType(pFileName, RESOURCE_TYPE_SOUND_EFFECT);
    
    /*
    const char *aResult = 0;
    
    GetResourcePath(pFileName);
    mSearchResultsFilter.RemoveAll();
    EnumList(FHashTableNode, aNode, mSearchResults)
    {
        FResource *aResource = ((FResource *)(aNode->mObject));
        if(aResource)
        {
            if(((aResource->mResourceType) & RESOURCE_TYPE_SOUND_EFFECT) != 0)mSearchResultsFilter.Add(aNode);
        }
    }
    
    mSearchResults.RemoveAll();
    EnumList(FHashTableNode, aNode, mSearchResultsFilter)mSearchResults.Add(aNode);
    
    mSearchResultsFilter.RemoveAll();
    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(0));
    if(aNode)
    {
        mSearchIndex = 1;
        aResult = aNode->mKeyFull.c();
    }
    else mSearchIndex = 0;
    return aResult;
    */
}

const char *FResourceManager::GetResourcePathMusic(const char *pFileName)
{
    return GetResourcePathOfType(pFileName, RESOURCE_TYPE_MUSIC);
    
    /*
    const char *aResult = 0;
    
    GetResourcePath(pFileName);
    mSearchResultsFilter.RemoveAll();
    EnumList(FHashTableNode, aNode, mSearchResults)
    {
        FResource *aResource = ((FResource *)(aNode->mObject));
        if(aResource)
        {
            if(((aResource->mResourceType) & RESOURCE_TYPE_SOUND_EFFECT) != 0)mSearchResultsFilter.Add(aNode);
        }
    }
    
    mSearchResults.RemoveAll();
    EnumList(FHashTableNode, aNode, mSearchResultsFilter)mSearchResults.Add(aNode);
    
    mSearchResultsFilter.RemoveAll();
    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(0));
    if(aNode)
    {
        mSearchIndex = 1;
        aResult = aNode->mKeyFull.c();
    }
    else mSearchIndex = 0;
    return aResult;
    */
}

const char *FResourceManager::GetResourcePathFile(const char *pFileName)
{
    const char *aResult = 0;
    
    GetResourcePath(pFileName);
    
    mSearchResultsFilter.RemoveAll();
    
    EnumList(FHashTableNode, aNode, mSearchResults)
    {
        FResource *aResource = ((FResource *)(aNode->mObject));
        if(aResource)
        {
            if(((aResource->mResourceType) & RESOURCE_TYPE_IMAGE) == 0)
            {
                mSearchResultsFilter.Add(aNode);
            }
        }
    }
    
    mSearchResults.RemoveAll();
    
    EnumList(FHashTableNode, aNode, mSearchResultsFilter)
    {
        mSearchResults.Add(aNode);
    }
    
    mSearchResultsFilter.RemoveAll();
    
    
    
    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(0));
    if(aNode)
    {
        mSearchIndex = 1;
        aResult = aNode->mKeyFull.c();
    }
    else
    {
        mSearchIndex = 0;
    }
    return aResult;
}

const char *FResourceManager::GetNextResourcePath()
{
    const char *aResult = 0;
    
    FHashTableNode *aNode = (FHashTableNode *)(mSearchResults.Fetch(mSearchIndex));
    
    if(aNode)
    {
        aResult = aNode->mKeyFull.c();
        mSearchIndex++;
    }
    
    return aResult;
}


void FResourceManager::Print()
{
    mTable.Print();
}


