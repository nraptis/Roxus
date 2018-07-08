
//
//  ModelUtilities.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MODEL_UTILITIES_H
#define MODEL_UTILITIES_H

#include"stdafx.h"

extern bool gModelDiscardNormals;
extern bool gModelDiscardUVW;

class Model;
class ModelData;
class ModelDataIndexed;
class ModelCodex;
class Sprite;

ModelData           *LoadOBJ(const char *pFile, List *pList=0);
ModelDataIndexed    *LoadOBJIndexed(const char *pFile);

void                LoadOBJIndexed(ModelDataIndexed *pData, const char *pFile);

ModelDataIndexed    *LoadOBJIndexed(const char *pFile, Sprite &pSprite);

void                LoadOBJIndexed(ModelDataIndexed *pData, const char *pFile, Sprite &pSprite);

void                Load3DI(const char *pFile);
void                Load3DI(ModelDataIndexed *pData, const char *pFile);

ModelDataIndexed    *Load3D(const char *pFile);
void                Load3D(ModelDataIndexed &pData, const char *pFile);
void                Load3D(ModelDataIndexed &pData, const char *pFile, Sprite &pSprite);

ModelData           *LoadOBJ(const char *pFile, Sprite &pSprite);



#endif
