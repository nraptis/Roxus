/*
 *  Model.h
 *  SteakNinja
 *
 *  Created by Nick Raptis on 9/14/10.
 *  Copyright 2010 Raptisoft LLC. All rights reserved.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include "FPoint.h"
#include "FString.h"
#include "Color.h"
#include "Sprite.h"
#include "ModelData.h"

class Model
{
public:
    
    Model(ModelDataIndexed *pData, Sprite *pSprite=0);
	Model();
    
    
	virtual ~Model();
    
    ModelDataIndexed                *mData;
    
    virtual void                    FixUVW(Sprite *pSprite=0);
    
    
    virtual void                    Load(ModelDataIndexed *pData, Sprite *pSprite);
	
    virtual void                    Load(const char *pFileName);
    inline virtual void             Load(char *pFileName){Load((const char*)pFileName);}
    inline virtual void             Load(FString pFileName){Load((const char*)(pFileName.c()));}
    
    
    virtual void                    Load(const char *pFileName, Sprite *pSprite){Load(pFileName);mBindSprite=pSprite;}
    inline virtual void             Load(char *pFileName, Sprite *pSprite){Load((const char*)pFileName,pSprite);}
    inline virtual void             Load(FString pFileName, Sprite *pSprite){Load((const char*)(pFileName.c()),pSprite);}
    
	virtual void                    Free();
    
	virtual void                    Draw();
    virtual void                    DrawBase();
	
	Sprite                          *mBindSprite;
	int                             mBindIndex;
    
	virtual Vector3                 GetCentroid();
    virtual Vector3                 GetCentroidRotated();
	
    
    
    
    virtual void                    SetAffine(float pTranslationX, float pTranslationY, float pTranslationZ, float pScale, float pRotationX=0, float pRotationY=0, float pRotationZ=0, float pRotationAmount=0);
    
	Vector3                         GetRotationAxis(){return Vector3(mRotationX,mRotationY,mRotationZ);}
    
    FString                         mName;
	
	float                           mX;
	float                           mY;
	float                           mZ;
    
    float                           mScale;
    
    float                           mRotation;
    bool                            mRotateSingleAxis;
	
    float                           mRotationX;
	float                           mRotationY;
	float                           mRotationZ;
    
    
    float                           mCentroidX;
    float                           mCentroidY;
    float                           mCentroidZ;
    
    bool                            mCentroidIsComputed;
};

#endif

