//
//  ModelSpriteSequence.cpp
//  LizDash
//
//  Created by Nick Raptis on 9/2/12.
//
//

#include "ModelSpriteSequence.h"


ModelSpriteSequence::ModelSpriteSequence()
{
    mUVWList = 0;
    mSprite = 0;
    mCount = 0;
}

ModelSpriteSequence::~ModelSpriteSequence()
{
    
}

void ModelSpriteSequence::Free()
{
    
    for(int i=0;i<mCount;i++)delete mSprite[i];
    for(int i=0;i<mCount;i++)delete [] mUVWList[i];
    
    delete [] mSprite;
    delete [] mUVWList;
    
    mUVWList = 0;
    mSprite = 0;
    mCount = 0;
    
    ModelDataIndexed::Free();
    
}

void ModelSpriteSequence::Load(const char *pModelPath, const char *pPrefix, int pStartIndex, int pEndIndex, const char *pSuffix)
{
    Free();
    
    ModelDataIndexed::Load(pModelPath);
    
    int aUVWCount = mUVWCount;
    mCount = (pEndIndex - pStartIndex) + 1;
    
    List aFileList;
    
    FileSequence::LoadSequence
    
    (pPrefix, ".png", aFileList, pStartIndex, pEndIndex);
    
    EnumList(FString, aString, aFileList)
    {
        printf("Loading Image From [%s]\n", aString->c());
    }
    
    //(, "png", &aFileList, pStartIndex);//, pEndIndex);
    
    
    if((mCount > 0) && (mUVWCount > 0))
    {
        
        mSprite = new Sprite*[mCount];
        mUVWList = new float*[mCount];
        
        int aIndex=0;
        for(int i=pStartIndex;i<=pEndIndex;i++)
        {
            FString aPath = FString(pPrefix);
            if(pStartIndex <= 9)
            {
                //aPath += FString("0") + FString(
            }
            else
            {
                
            }
            
            mSprite[i] = new Sprite();
            
            
               aIndex++;
        }
    }
    
    for(int i=0;i<mCount;i++)delete mSprite[i];
    for(int i=0;i<mCount;i++)delete [] mUVWList[i];
    
    delete [] mSprite;
    delete [] mUVWList;
    
    mUVWList = 0;
    mSprite = 0;
    mCount = 0;
    
}

void ModelSpriteSequence::Draw(float pFrame)
{
    
}

