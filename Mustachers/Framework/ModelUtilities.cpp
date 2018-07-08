//////////////////////////////////////////////////////////////////////////
//  ModelUtilities.cpp                                                  //
//  DoomKnights                                                         //
//////////////////////////////////////////////////////////////////////////
//  Created by Nick Raptis on 1/18/12.                                  //
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.          //
//////////////////////////////////////////////////////////////////////////

#include "ModelUtilities.h"
#include "ModelData.h"
#include "ModelDataOptimizer.h"
#include "Sprite.h"

bool gModelDiscardNormals = false;
bool gModelDiscardUVW = false;

void Load3D(ModelDataIndexed &pData, const char *pFile)
{
    pData.Free();
    
    if(pData.mXYZCount <= 0)
    {
        
        Load3DI(&pData, pFile);
        
    }
    
    if(pData.mXYZCount > 0)
    {
        
        //printf("Successfully Loaded 3DI: [%s] [%d][%d][%d]\n", pFile, pData.mXYZCount, pData.mUVWCount, pData.mNormalCount);
        
    }
    
    if(pData.mXYZCount <= 0)
    {
        LoadOBJIndexed(&pData, pFile);
    }
    
}

ModelData *LoadOBJ(const char *pFile, List *pList)
{
    ModelData *aReturn = new ModelData();
    
    ModelDataIndexed *aTemp = new ModelDataIndexed();
    
    int aPreviousIndexStart = 0;
    int aError=0;
    
	Buffer aBuffer;
	aBuffer.Load(pFile);
    
    if(aBuffer.mLength <= 0)aBuffer.Load(FString(pFile) + FString(".obj"));
    if(aBuffer.mLength <= 0)aBuffer.Load(FString(pFile) + FString(".OBJ"));
    if(aBuffer.mLength <= 0)
    {
        printf("Could Not Load 3D Model [%s]\n", pFile);
        aError = 1;
        return aReturn;
    }
    
    float aX, aY, aZ, aU, aV, aW, aNX, aNY, aNZ;
    
    int aXYZIndex = 0;
    int aUVWIndex = 0;
    int aNormalIndex = 0;
    
	char *aData=(char*)aBuffer.mData;
	int aLength=aBuffer.mLength;
	
	char *aEnd=&aData[aLength];
	char *aLineStart=aData;
	char *aLineEnd=aData;
    
    int aLineLength;
    int aWriteIndex;
    int aNumberCount;
    
    char *aSeek;
    
    char aNumberString[128];
    float aFloat[32];
    int aFace[4][3];
    int aFaceIndex;
    int aFaceCol;
    
    bool aContinue;
    int aLine=1;
    
	while((aLineStart<aEnd)&&(aError==0))
	{
		while(*aLineStart <= 32 && aLineStart < aEnd)
		{
			aLineStart++;
		}
        
		aLineEnd=aLineStart;
        
		while(*aLineEnd >= 32 && aLineEnd < aEnd)
		{
			aLineEnd++;
		}
        
		if((aLineEnd>aLineStart)&&(aError==0))
		{
            aLineLength = (int)(aLineEnd - aLineStart);
            if(aLineLength > 1)
            {
                if(aLineStart[0] == 'g')
                {
                    if(pList != 0)
                    {
                        if(aTemp->mIndexCount != aPreviousIndexStart)
                        {
                            ModelData *aModel = new ModelData();
                            
                            for(int i=aPreviousIndexStart;i<aTemp->mIndexCount;i+=3)
                            {
                                aXYZIndex = aTemp->mIndex[i];
                                aUVWIndex = aTemp->mIndex[i+1];
                                aNormalIndex = aTemp->mIndex[i+2];
                                
                                aX = aTemp->GetX(aXYZIndex);
                                aY = aTemp->GetY(aXYZIndex);
                                aZ = aTemp->GetZ(aXYZIndex);
                                
                                aU = aTemp->GetU(aUVWIndex);
                                aV = aTemp->GetV(aUVWIndex);
                                aW = aTemp->GetW(aUVWIndex);
                                
                                aNX = aTemp->GetNormX(aNormalIndex);
                                aNY = aTemp->GetNormY(aNormalIndex);
                                aNZ = aTemp->GetNormZ(aNormalIndex);
                                
                                aModel->AddXYZ(aX, aY, aZ);
                                aModel->AddUVW(aU, aV, aW);
                                aModel->AddNormal(aNX, aNY, aNZ);
                            }
                            
                            aModel->InvertV();
                            pList->Add(aModel);
                            aPreviousIndexStart = aTemp->mIndexCount;
                        }
                    }
                }
            }
            
            if(aLineLength > 5)
            {
                if(aLineStart[0] == 'v')
                {
                    aNumberCount=0;
                    aSeek=aLineStart;
                    while((aNumberCount < 3) && (aSeek < aLineEnd))
                    {
                        while(aSeek < aLineEnd)
                        {
                            if((*aSeek >= '0' && *aSeek <= '9') || (*aSeek == '.'))
                            {
                                aWriteIndex=0;
                                if(aSeek > aLineStart)
                                {
                                    if(*(aSeek-1)=='-')
                                    {
                                        aNumberString[aWriteIndex++]='-';
                                    }
                                }
                                while(((*aSeek >= '0' && *aSeek <= '9') || (*aSeek == '.')) && (aSeek < aEnd))
                                {
                                    aNumberString[aWriteIndex++]=*aSeek;
                                    aSeek++;
                                }
                                aNumberString[aWriteIndex]=0;
                                aFloat[aNumberCount] = atof(aNumberString);
                                aNumberCount++;
                                break;
                            }
                            else
                            {
                                aSeek++;
                            }
                        }
                    }
                    
                    if(aLineStart[1] <= ' ')
                    {
                        if(aNumberCount < 3)aError=2;
                        else aTemp->AddXYZ(aFloat[0], aFloat[1], aFloat[2]);  
                    }
                    
                    if(aLineStart[1] == 't')
                    {
                        if(aNumberCount < 2)aError=3;
                        else if(aNumberCount == 2)aTemp->AddUVW(aFloat[0], aFloat[1], 0);
                        else aTemp->AddUVW(aFloat[0], aFloat[1], aFloat[2]);  
                    }
                    
                    if(aLineStart[1] == 'n')
                    {
                        if(aNumberCount < 3)aError=4;
                        else aTemp->AddNormal(aFloat[0], aFloat[1], aFloat[2]);
                    }
                }
                
                if(aLineStart[0] == 'f' && aLineStart[1] <= ' ')
                {
                    
                    for(int i=0;i<4;i++)
                    {
                        for(int n=0;n<3;n++)
                        {
                            aFace[i][n]=-1;
                        }
                    }
                    
                    aFaceCol=0;
                    aFaceIndex=0;
                    aContinue=false;
                    aSeek=aLineStart;
                    
                    while((aSeek < aLineEnd) && (aError == 0))
                    {
                        if(aFaceCol > 4)
                        {
                            aError=9;
                            break;
                        }
                        else if(*aSeek >= '0' && *aSeek <= '9')
                        {
                            if(aFaceIndex > 3)
                            {
                                aError=10;
                            }
                            
                            aWriteIndex=0;
                            
                            while(*aSeek >= '0' && *aSeek <= '9')
                            {
                                aNumberString[aWriteIndex++]=*aSeek;
                                aSeek++;
                            }
                            
                            aNumberString[aWriteIndex]=0;
                            aFace[aFaceCol][aFaceIndex]=(atoi(aNumberString) - 1);
                            
                            if(*aSeek=='/')
                            {
                                if(*(aSeek+1)=='/')
                                {
                                    aSeek++;
                                    aFaceIndex++;
                                }
                                aFaceIndex++;
                            }
                            else
                            {
                                aFaceIndex=0;
                                aFaceCol++;
                            }
                        }
                        else
                        {   
                            aSeek++;
                        }
                    }
                    
                    if(aFaceCol == 3)
                    {
                        aTemp->AddIndex(aFace[0][0]);
                        aTemp->AddIndex(aFace[0][1]);
                        aTemp->AddIndex(aFace[0][2]);
                        
                        aTemp->AddIndex(aFace[1][0]);
                        aTemp->AddIndex(aFace[1][1]);
                        aTemp->AddIndex(aFace[1][2]);
                        
                        aTemp->AddIndex(aFace[2][0]);
                        aTemp->AddIndex(aFace[2][1]);
                        aTemp->AddIndex(aFace[2][2]);
                    }
                }
                aSeek=aLineStart;
            }
		}
        aLine++;
		aLineStart = aLineEnd + 1;
	}
    
    
    if(pList != 0)
    {
        if(aTemp->mIndexCount != aPreviousIndexStart)
        {
            ModelData *aModel = new ModelData();
            
            for(int i=aPreviousIndexStart;i<aTemp->mIndexCount;i+=3)
            {
                aXYZIndex = aTemp->mIndex[i];
                aUVWIndex = aTemp->mIndex[i+1];
                aNormalIndex = aTemp->mIndex[i+2];
                
                aX = aTemp->GetX(aXYZIndex);
                aY = aTemp->GetY(aXYZIndex);
                aZ = aTemp->GetZ(aXYZIndex);
                
                aU = aTemp->GetU(aUVWIndex);
                aV = aTemp->GetV(aUVWIndex);
                aW = aTemp->GetW(aUVWIndex);
                
                aNX = aTemp->GetNormX(aNormalIndex);
                aNY = aTemp->GetNormY(aNormalIndex);
                aNZ = aTemp->GetNormZ(aNormalIndex);
                
                aModel->AddXYZ(aX, aY, aZ);
                aModel->AddUVW(aU, aV, aW);
                aModel->AddNormal(aNX, aNY, aNZ);
            }
            
            aModel->InvertV();
            
            pList->Add(aModel);
            
            aPreviousIndexStart = aTemp->mIndexCount;
            
        }
    }
    
    
    
    int aIndexCount = aTemp->mIndexCount;
    for(int i=0;i<aIndexCount;i+=3)
    {
        aXYZIndex = aTemp->mIndex[i];
        aUVWIndex = aTemp->mIndex[i+1];
        aNormalIndex = aTemp->mIndex[i+2];
        
        aX = aTemp->GetX(aXYZIndex);
        aY = aTemp->GetY(aXYZIndex);
        aZ = aTemp->GetZ(aXYZIndex);
        
        aU = aTemp->GetU(aUVWIndex);
        aV = aTemp->GetV(aUVWIndex);
        aW = aTemp->GetW(aUVWIndex);
        
        aNX = aTemp->GetNormX(aNormalIndex);
        aNY = aTemp->GetNormY(aNormalIndex);
        aNZ = aTemp->GetNormZ(aNormalIndex);
        
        aReturn->AddXYZ(aX, aY, aZ);
        aReturn->AddUVW(aU, aV, aW);
        aReturn->AddNormal(aNX, aNY, aNZ);
    }
    
    aReturn->InvertV();
    delete aTemp;
    
    if(gModelDiscardNormals)
    {
        aReturn->DiscardNormal();
    }
    
    if(gModelDiscardUVW)
    {
        aReturn->DiscardUVW();
    }
    
    return aReturn;
    
}

void LoadOBJIndexed(ModelDataIndexed *pData, const char *pFile)
{
    if(pData)
    {
        pData->Free();
        
        ModelData *aTemp = LoadOBJ(pFile);
        ModelDataOptimizer *aOptimizer = new ModelDataOptimizer();
        
        //aOptimizer->Generate(aTemp);
        
        if(gModelDiscardNormals)aTemp->DiscardNormal();
        if(gModelDiscardUVW)aTemp->DiscardUVW();
        
        aOptimizer->Convert(aTemp, pData);
        
        FString aExport = FString("Exports\\") + FString(pFile);
        aExport.RemovePath(true);
        aExport += ".3di";
        
        if((pData->mXYZCount > 0) || (pData->mUVWCount > 0) || (pData->mNormalCount > 0) || pData->mIndexCount > 0)
        {
            pData->Save(aExport.c());
        }
    }
}

void Load3DI(const char *pFile)
{
    
}

void Load3DI(ModelDataIndexed *pData, const char *pFile)
{
    if(pData)
    {
        FString aFile = pFile;
        aFile = aFile.RemovePath(true);
        aFile += ".3di";
        
        pData->LoadData(aFile.c());
    }
}

ModelDataIndexed *Load3D(const char *pFile)
{
    ModelDataIndexed *aReturn = new ModelDataIndexed();
    Load3D(*aReturn, pFile);
    return aReturn;
}




ModelDataIndexed *LoadOBJIndexed(const char *pFile)
{
    
    /*
    
    ModelData *aTemp = LoadOBJ(pFile);
    ModelDataOptimizer *aOptimizer = new ModelDataOptimizer();
    aOptimizer->Generate(aTemp);
    
    ModelDataIndexed *aReturn = aOptimizer->Convert(aTemp);
    delete aTemp;
    
    FString aExport = FString(pFile);
    aExport.RemovePath(true);
    aExport += ".3di";
    aReturn->Save(aExport.c());
    
    */
    
    
    ModelDataIndexed *aReturn = new ModelDataIndexed();
    LoadOBJIndexed(aReturn, pFile);
    return aReturn;
}


ModelData           *LoadOBJ(const char *pFile, Sprite &pSprite)
{
    ModelDataIndexed *aData = LoadOBJIndexed(pFile);
    aData->mBindIndex = pSprite.mBindIndex;
    return aData;
}

ModelDataIndexed    *LoadOBJIndexed(const char *pFile, Sprite &pSprite)
{
    ModelDataIndexed *aData = LoadOBJIndexed(pFile);
    aData->mBindIndex = pSprite.mBindIndex;
    return aData;
}

void LoadOBJIndexed(ModelDataIndexed *pData, const char *pFile, Sprite &pSprite)
{
    if(pData)
    {
        LoadOBJIndexed(pData, pFile);
        pData->mBindIndex = pSprite.mBindIndex;
    }
}


void Load3D(ModelDataIndexed &pData, const char *pFile, Sprite &pSprite)
{
    FString aPath = pFile;
    aPath.RemovePath(true);
    
    //Load3D(pData, FString(aPath + FString(".3di")).c());
    
    Load3D(pData, aPath.c());
    
    
    //printf("Load3D Fin: [%d %d %d %d] ==> [%s]\n", pData.mXYZCount, pData.mUVWCount, pData.mNormalCount, pData.mIndexCount, pFile);
    
    if(pSprite.mBindIndex == -1)pSprite.Load(aPath + FString("_uvw"));
    if(pSprite.mBindIndex == -1)pSprite.Load(FString("uvw_") + aPath);
    if(pSprite.mBindIndex == -1)pSprite.Load(aPath.c());
    
    if(pSprite.mBindIndex != -1)
    {
        pData.mBindIndex = pSprite.mBindIndex;
    }
}








