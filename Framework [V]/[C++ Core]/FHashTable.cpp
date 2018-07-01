//
//  FHashTable.cpp
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FHashTable.h"
#include "core_includes.h"

FHashTableNode::FHashTableNode()
{
    mObject = 0;
    //mKeyData = 0;
    mNext = 0;
}

FHashTableNode::~FHashTableNode()
{
    
}

FHashTable::FHashTable()
{
    mTable = 0;
    
    mTableCount = 0;
    mTableSize = 0;
    
    mAllowDuplicateKeys = false;
    mAllowDuplicateFullKeys = false;
}

FHashTable::~FHashTable()
{
    //mTable = 0;
    //mTableCount = 0;
    //mTableSize = 0;
}

void FHashTable::Add(const char *pKey, const char *pKeyFull, void *pObject)
{
    FHashTableNode *aNode = 0;
    FHashTableNode *aHold = 0;
    
    unsigned int aHashBase = Hash(pKey);
    unsigned int aHash = 0;
    
    //mKeyFull
    
    if(mTableSize > 0)
    {
        aHash = (aHashBase % mTableSize);
        
        aNode = mTable[aHash];
        
        while(aNode)
        {
            if(aNode->mKey == pKey)
            {
                
                if(mAllowDuplicateKeys == false)
                {
					//Log("^^^^^\n^^^^^\n^^^^^\nBANNING DUPE 1 [%s]\n\n^^^^\n^^^^^^^^^^^^^^^\n\n", aNode->mKey.c());
                    
                    return;
                }
                else
                {
                    if(aNode->mKeyFull == pKeyFull)
                    {
                        if(mAllowDuplicateFullKeys == false)
                        {
							//Log("^^^^^\n^^^^^\n^^^^^\nBANNING DUPE 2 [%s]\n\n^^^^\n^^^^^^^^^^^^^^^\n\n", aNode->mKey.c());
                            return;
                        }
                    }
                }
                
            }
            aNode = aNode->mNext;
        }
        
        if(mTableCount >= (mTableSize / 2))
        {
            int aNewSize = mTableCount + 1;
            
            if(mTableCount < ((7 / 2) - 1))aNewSize = 7;
            else if(mTableCount < ((13 / 2) - 1))aNewSize = 13;
            else if(mTableCount < ((29 / 2) - 1))aNewSize = 29;
            else if(mTableCount < ((41 / 2) - 1))aNewSize = 41;
            else if(mTableCount < ((53 / 2) - 1))aNewSize = 53;
            else if(mTableCount < ((97 / 2) - 1))aNewSize = 97;
            else if(mTableCount < ((149 / 2) - 5))aNewSize = 149;
            else if(mTableCount < ((193 / 2) - 5))aNewSize = 193;
            else if(mTableCount < ((269 / 2) - 5))aNewSize = 269;
            else if(mTableCount < ((389 / 2) - 5))aNewSize = 389;
            else if(mTableCount < ((439 / 2) - 5))aNewSize = 439;
            else if(mTableCount < ((631 / 2) - 5))aNewSize = 631;
            else if(mTableCount < ((769 / 2) - 5))aNewSize = 769;
            else if(mTableCount < ((907 / 2) - 7))aNewSize = 907;
            else if(mTableCount < ((1213 / 2) - 7))aNewSize = 1213;
            else if(mTableCount < ((1543 / 2) - 7))aNewSize = 1543;
            else if(mTableCount < ((2089 / 2) - 7))aNewSize = 2089;
            else if(mTableCount < ((2557 / 2) - 9))aNewSize = 2557;
            else if(mTableCount < ((3079 / 2) - 13))aNewSize = 3079;
            else if(mTableCount < ((3613 / 2) - 13))aNewSize = 3613;
            else if(mTableCount < ((4013 / 2) - 13))aNewSize = 4013;
            else if(mTableCount < ((5119 / 2) - 13))aNewSize = 5119;
            else if(mTableCount < ((6151 / 2) - 13))aNewSize = 6151;
            else if(mTableCount < ((7151 / 2) - 13))aNewSize = 7151;
            else if(mTableCount < ((12289 / 2) - 17))aNewSize = 12289;
            else {
                aNewSize = (mTableCount + (mTableCount * 2) / 3 + 7);
            }

            SetTableSize(aNewSize);//mTableCount + (mTableCount / 2) + 12);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }

    FHashTableNode *aNew = new FHashTableNode();
    aNew->mKey = pKey;
    aNew->mKeyFull = pKeyFull;
    aNew->mObject = pObject;
    aNew->mNext = 0;
    
    if(mTable[aHash])
    {
        aNode = mTable[aHash];
        
        while(aNode)
        {
            aHold = aNode;
            aNode = aNode->mNext;
        }
        
        aHold->mNext = aNew;
    }
    else
    {
        mTable[aHash] = aNew;
    }
    
    mTableCount++;
}

void FHashTable::Add(const char *pKey, void *pObject)
{
    Add(pKey, 0, pObject);
}

void *FHashTable::Get(const char *pKey)
{
    void *aReturn = 0;
    if(mTableSize > 0)
    {
        unsigned int aHash = (Hash(pKey) % mTableSize);
        FHashTableNode *aNode = mTable[aHash];
        while(aNode)
        {
            if(aNode->mKey == pKey)
            {
                return aNode->mObject;
            }
            aNode = aNode->mNext;
        }
    }
    return aReturn;
}


FHashTableNode *FHashTable::GetNode(const char *pKey)
{
    FHashTableNode *aReturn = 0;
    
    if(mTableSize > 0)
    {
        unsigned int aHash = (Hash(pKey) % mTableSize);
        aReturn = mTable[aHash];
    }
    
    return aReturn;
}

void FHashTable::GetAllNodes(const char *pKey, FList &pList)
{
    pList.RemoveAll();
    
    //FHashTableNode *aNode = 0;
    
    if(mTableSize > 0)
    {
        unsigned int aHash = (Hash(pKey) % mTableSize);
        FHashTableNode *aNode = mTable[aHash];
        
        while (aNode)
        {
            if(aNode->mKey == pKey)
            {
                pList.Add(aNode);
            }
            aNode = (aNode->mNext);
        }
    }
}

void FHashTable::SetTableSize(int pSize)
{
	FHashTableNode *aCheck = 0;
    FHashTableNode *aNext = 0;
    FHashTableNode *aNode = 0;
    
    int aNewSize = pSize;
    
    FHashTableNode **aTableNew = new FHashTableNode*[aNewSize];
    
    for(int i=0;i<aNewSize;i++)
    {
        aTableNew[i] = 0;
    }
    
    unsigned int aHash = 0;
    for(int i=0;i<mTableSize;i++)
    {
        aNode = mTable[i];

		while (aNode)
		{
			aNext = aNode->mNext;
			aNode->mNext = 0;

			aHash = (Hash(aNode->mKey.c()) % aNewSize);

			if(aTableNew[aHash] == 0)
			{
				aTableNew[aHash] = aNode;
			}
			else
			{
				aCheck = aTableNew[aHash];

				while (aCheck->mNext)
				{
					aCheck = aCheck->mNext;
				}

				aCheck->mNext = aNode;
			}
			aNode = aNext;
		}
    }
    
    delete [] mTable;
    
    mTable = aTableNew;
    mTableSize = aNewSize;
}





/*
 

FTexture *FHashTable::Load(const char *pFileName, FImage *pImage, bool pRetainImage)
{
    FTexture *aReturn = 0;
 
    int aHashBase = Hash(pFileName);
 
    if(mTableCount >= (mTableSize))
    {
        int aNewSize = (mTableCount * 2) + 4;
        
        
        
        //mNextTexture
        
        
        
    }
    
    return aReturn;
}

FTexture *FHashTable::GetTexture(const char *pFileName, bool pRetainImage)
{
    FTexture *aReturn = 0;
    
    unsigned int aHashBase = 0;
    unsigned int aHash = 0;
    
    FTexture *aTexture = 0;
    FTexture *aHold = 0;
    FTexture *aNext = 0;
    
    FString aName = pFileName;
    
    if(mTableCount >= (mTableSize / 2))
    {
        
        int aNewSize = (mTableSize * 2) + 1;
        
        FTexture **aHashTableNew = new FTexture*[aNewSize];
        
        for(int i=0;i<aNewSize;i++)
        {
            aHashTableNew[i] = 0;
        }
        
        //Log("Re-Sizing Texture Table Was [%d] Is Now [%d]\n", mTableCount, aNewSize);
        //Re-Hash All Da Nodez Yo..!
        
        for(int i=0;i<mTableSize;i++)
        {
            aHold = mTable[i];
            
            //aTexture = mTable[i];
            while(aHold)
            {
                aTexture = aHold;
                aHold = aTexture->mNextTexture;
                aTexture->mNextTexture = 0;
                
                aHashBase = Hash(aTexture->mFileName.c());
                aHash = (unsigned int)(aHashBase % ((unsigned int)aNewSize));
                
                //Log("Re-Hashed [%s] To [%d]\n", aTexture->mFileName.c(), aHash);
                
                if(aHashTableNew[aHash])
                {
                    aNext = aHashTableNew[aHash];
                    
                    while(true)
                    {
                        if(aNext->mNextTexture)
                        {
                            aNext = aNext->mNextTexture;
                            
                            
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    aNext->mNextTexture = aTexture;
                    
                }
                else
                {
                    aHashTableNew[aHash] = aTexture;
                }
                
                aTexture = aHold;
                
            }
        }
        
        delete [] mTable;
        
        mTable = aHashTableNew;
        mTableSize = aNewSize;
        
    }
    
    aHashBase = Hash(pFileName);
    aHash = (unsigned int)(aHashBase % ((unsigned int)mTableSize));
    
    
    //Does the texture ALREADY EXIST?
    
    aTexture = 0;
    
    //Log("Rehashed(%s) Was[%d] Now[%d]\n", aTexture->mFileName.c(), aHashBase, aHash);
    
    if(mTable[aHash])
    {
        aNext = mTable[aHash];
        
        while(aNext)
        {
            if(aNext->mFileName == aName)
            {
                aTexture = aNext;
                break;
            }
            aNext = (aNext->mNextTexture);
        }
    }
    
    if(aTexture)
    {
        //Log("Texture [%s] Already Existed!!\n", pFileName);
    }
    else
    {
        //Log("Texture [%s] Doesn't Yet Existed!!\n", pFileName);
        
        aTexture = new FTexture();
        aTexture->mFileName = pFileName;
        aTexture->mNextTexture = 0;
        
        
        //And then now we add it to the haish table..!
        if(mTable[aHash])
        {
            aNext = mTable[aHash];
            aHold = aNext;
            
            while(aNext)
            {
                aHold = aNext;
                
                aNext = (aNext->mNextTexture);
            }
            
            aHold->mNextTexture = aTexture;
        }
        else
        {
            mTable[aHash] = aTexture;
        }
        
        mTableCount++;
        
        Log("Hash Textures![%d / %d]\n", mTableCount, mTableSize);
        
    }
    
    
    //Now, "Dirty" texture versus non-dirty texture..
    
    
    
    return aReturn;
}

*/

unsigned int FHashTable::Hash(const char *pString)
{
    unsigned long aHash = 5381;
	
    if(pString)
    {
        unsigned char *aString = (unsigned char *)pString;
        while(*aString)
        {
            int aVal = *aString;
            aHash = ((aHash << 5)+aHash)^aVal;
            aString++;
        }
    }
    
    return (unsigned int)aHash;
}

void FHashTable::Print()
{
	Log("____\n____Hash Table____\n_Count = %d  Size = %d\n\n", mTableCount, mTableSize);
    
    
    FHashTableNode *aNode = 0;
    
    
    for(int i=0;i<mTableSize;i++)
    {
        int aCount = 0;
        aNode = mTable[i];
        while(aNode)
        {
            aCount++;
            
            aNode = aNode->mNext;
        }
        
		Log("Row[%d] (%d)\t{", i, aCount);
        
        aNode = mTable[i];
        while(aNode)
        {
			Log("{%s}", aNode->mKey.c());
            aNode = aNode->mNext;
        }
		Log("}\n");
    }
    
}


//unsigned int FHashTable::Hash(void *pData)
//{
//    unsigned long aReturn = ((unsigned long)pData);
//    return (unsigned int)aReturn;
//}
