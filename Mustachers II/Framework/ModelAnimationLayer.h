//
//  ModelAnimationLayer.h
//  DoomKnights
//
//
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MODEL_ANIMATION_LAYER_H
#define MODEL_ANIMATION_LAYER_H

#include "ModelData.h"
#include "ModelDataOptimizer.h"
#include "ModelDataSequence.h"
#include "List.h"

class Sprite;

class ModelAnimationLayer
{
public:
    
    ModelAnimationLayer();
    
    virtual ~ModelAnimationLayer();
    
    virtual void                Free(){}
    
    virtual void                SetParent(ModelDataIndexed *pData);
    
    unsigned char               mType;
    ModelDataIndexed            *mParent;
    
    Sprite                      *mSprite;
    int                         mBindIndex;
    FString                     mName;
    
    virtual void                StripToKeyframes(bool *pKeyFrames){}
    
    virtual void                Draw(float pFrame, int *pKeyStart, int *pKeyEnd, int pFrameCount){}
    virtual void                Draw(float pFrame){}
    
    virtual void                Save(Buffer *pBuffer);
    virtual void                Load(Buffer *pBuffer);
    
    
    virtual void                Save(const char *pFile){Buffer aBuffer;Save(&aBuffer);aBuffer.Save(pFile);}
    virtual void                Save(char *pFile){Save((const char*)pFile);}
    virtual void                Save(FString pFile){Save((const char*)pFile.c());}
    
    virtual void                Load(const char *pFile){Buffer aBuffer;aBuffer.Load(pFile);Load(&aBuffer);}
    virtual void                Load(char *pFile){Load((const char*)pFile);}
    virtual void                Load(FString pFile){Load((const char*)pFile.c());}
    
    int                         mFrameCount;
    int                         mListSize;
};

//
//We take 1 instance of a model and apply rotation & translations to it...
//Might want to eventually add scale?
//

class ModelAnimationLayerTransformNode
{
public:
    float mX, mY, mZ, mAxisX, mAxisY, mAxisZ, mRot;
};

class ModelAnimationLayerTransform : public ModelAnimationLayer
{
public:
    
    ModelAnimationLayerTransform();
    virtual ~ModelAnimationLayerTransform();
    
    virtual void                            SetParent(ModelDataIndexed *pData);
    
    virtual void                            Save(Buffer *pBuffer);
    virtual void                            Load(Buffer *pBuffer);
    
    
    virtual void                            StripToKeyframes(bool *pKeyFrames);
    
    
    virtual void                            Save(const char *pFile){Buffer aBuffer;Save(&aBuffer);aBuffer.Save(pFile);}
    virtual void                            Save(char *pFile){Save((const char*)pFile);}
    virtual void                            Save(FString pFile){Save((const char*)pFile.c());}
    
    virtual void                            Load(const char *pFile){Buffer aBuffer;aBuffer.Load(pFile);Load(&aBuffer);}
    virtual void                            Load(char *pFile){Load((const char*)pFile);}
    virtual void                            Load(FString pFile){Load((const char*)pFile.c());}
    
    
    
    //int                                     mListSize;
    ModelAnimationLayerTransformNode        **mData;
    
    virtual void                            Free();
    
    virtual void                            Draw(float pFrame, int *pKeyStart, int *pKeyEnd, int pFrameCount);
    virtual void                            Draw(float pFrame);
    
    
    void                                    SetUp(const char *pModelFile, const char *pXMLFile, int pStartFrame=0, int pEndFrame=-1);
    
    void                                    SizeTransforms(int pSize);
    void                                    AddTransform(float pX, float pY, float pZ, float pAxisX, float pAxisY, float pAxisZ, float pRot);
};

class ModelAnimationLayerMesh : public ModelAnimationLayer
{
public:
    
    ModelAnimationLayerMesh();
    virtual ~ModelAnimationLayerMesh();
    
    virtual void                            SetParent(ModelDataIndexed *pData);
    
    virtual void                            Save(Buffer *pBuffer);
    virtual void                            Load(Buffer *pBuffer);
    
    virtual void                            Save(const char *pFile){Buffer aBuffer;Save(&aBuffer);aBuffer.Save(pFile);}
    virtual void                            Save(char *pFile){Save((const char*)pFile);}
    virtual void                            Save(FString pFile){Save((const char*)pFile.c());}
    
    virtual void                            Load(const char *pFile){Buffer aBuffer;aBuffer.Load(pFile);Load(&aBuffer);}
    virtual void                            Load(char *pFile){Load((const char*)pFile);}
    virtual void                            Load(FString pFile){Load((const char*)pFile.c());}
    
    virtual void                            SetUp(ModelDataSequence *pSequence);
    void                                    SetUp(ModelDataOptimizer *pOptimizer, const char *pBasePath, int pStartIndex, int pEndIndex);
    
    virtual void                            Free();
    
    virtual void                            Draw(float pFrame, int *pKeyStart, int *pKeyEnd, int pFrameCount);
    virtual void                            Draw(float pFrame);
    
    void                                    SizeData(int pSize);
    void                                    AddNode(ModelData *pData, int pIndex=-1);
    
    virtual void                            StripToKeyframes(bool *pKeyFrames);
    
    
    
    float                                   *mXYZInterp;
    float                                   *mNormalInterp;
    
    ModelData                               **mData;
};

#endif
