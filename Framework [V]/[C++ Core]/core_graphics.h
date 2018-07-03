#ifndef GRAPHICS_H
#define GRAPHICS_H


//#include "os_core_includes.h"


#include "FColor.h"
#include "FRect.h"
#include "FPoint.h"
#include "FVec2.h"
#include "FVec3.h"
#include "FPrimitive.h"
#include "FMatrix.h"
#include "FIndexList.h"

#define GFX_MODEL_INDEX_GL_TYPE GL_UNSIGNED_SHORT

#define GRAPHICS_LIGHT_COUNT 8

#define BLEND_TYPE_STANDARD 0
#define BLEND_TYPE_ADDITIVE 1
#define BLEND_TYPE_PREMULTIPLIED 2
#define BLEND_TYPE_SUBTRACT 3

#define BLEND_TYPE_INVERT_1 5
#define BLEND_TYPE_INVERT_2 6
#define BLEND_TYPE_GHOST_1 9
#define BLEND_TYPE_GHOST_2 10



class FTexture;

void core_graphics_initialize();

class Graphics
{
public:
    Graphics();
    ~Graphics();
    
    static void                             DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation=0);
	static void                             DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);

    
    
    static void                             RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture);
    static void                             RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4,
                                                       float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture);
    
    //static void                             RenderQuadPushed(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4,
                                                       //float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, //float pV4, FTexture *pTexture, float pPush);
    
    
    static void								RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale);
    
    static void								RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale, float pCenterX, float pCenterY);


	static void                             RenderTriangle(float pX1, float pY1, float pZ1, float pX2, float pY2, float pZ2, float pX3, float pY3, float pZ3);
	static void                             RenderTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);



    
    
    static void                             SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha);
    static void                             SetColorHex(int pRed, int pGreen, int pBlue);
    static void                             SetColorHex(int pAlpha);
    
    static void                             SetColor(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             SetColor(float pRed, float pGreen, float pBlue);
    static void                             SetColor(float pIntensity);
    static void                             SetColor();
    static void                             SetColor(FColor pColor);
    static void                             SetColorSwatch(int pSwatchIndex);
    static void                             SetColorSwatch(int pSwatchIndex, float pAlpha);
    
    
    
    static void                             SetEnvironmentColor(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             SetEnvironmentColor(float pRed, float pGreen, float pBlue);
    static void                             SetEnvironmentColor(float pIntensity);
    static void                             SetEnvironmentColor();
    static void                             SetEnvironmentColor(FColor pColor);
    
    
    static void                             DrawQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
    
    
    static void                             OutlineRect(float pX, float pY, float pWidth, float pHeight, float pThickness);
    static void                             OutlineRectInside(float pX, float pY, float pWidth, float pHeight, float pThickness);
    
    static void                             OutlineRect(FRect pRect, float pThickness);
    static void                             OutlineRectInside(FRect pRect, float pThickness);
    
    
    
    static void                             DrawRect(float pX, float pY, float pWidth, float pHeight);
    inline static void                             DrawRect(FVec2 pPos, float pWidth, float pHeight){DrawRect(pPos.mX,pPos.mY,pWidth,pHeight);}
    inline static void                             DrawRect(FVec2 pPos, FVec2 pSize){DrawRect(pPos.mX,pPos.mY,pSize.mX,pSize.mY);}
    inline static void                             DrawRect(FRect pRect){DrawRect(pRect.mX,pRect.mY,pRect.mWidth,pRect.mHeight);}
    //inline static void                             DrawRect(FRect pRect){DrawRect(pRect.mX,pRect.mY,pRect.mWidth,pRect.mHeight);}
    
    static void                             DrawLine(float pX1, float pY1, float pX2, float pY2);
    inline static void                             DrawLine(FVec2 pPoint1, FVec2 pPoint2){DrawLine(pPoint1.mX,pPoint1.mY,pPoint2.mX,pPoint2.mY);}
    inline static void                             DrawLine(FPoint pPoint1, FPoint pPoint2){DrawLine(pPoint1.mX,pPoint1.mY,pPoint2.mX,pPoint2.mY);}

    
    static void                             DrawLine(float pX1, float pY1, float pX2, float pY2, float pThickness);
    inline static void                             DrawLine(FVec2 pPoint1, FVec2 pPoint2, float pThickness){DrawLine(pPoint1.mX,pPoint1.mY,pPoint2.mX,pPoint2.mY, pThickness);}
    inline static void                             DrawLine(FPoint pPoint1, FPoint pPoint2, float pThickness){DrawLine(pPoint1.mX,pPoint1.mY,pPoint2.mX,pPoint2.mY, pThickness);}
    
    
    static void                             DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength=12, float pThickness=2.0f);
    
    
    static void                             DrawPoint(float pX, float pY, float pSize=7);
    inline static void                             DrawPoint(FVec2 pPoint, float pSize=7){DrawPoint(pPoint.mX,pPoint.mY,pSize);}
    
    
    
    //Deprecate these...
    static void                             Go3D();
    static void                             Go2D();
    
    
    static void                             EnableDepth();
    static void                             DisableDepth();
    
    static void                             DepthEnable();
    static void                             DepthDisable();
    
    static void                             DepthClear();
    static void                             DepthMaskFalse();
    static void                             DepthMaskTrue();
    
    
    
    static void                             ClearDepth(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             ClearDepth(float pRed, float pGreen, float pBlue);
    static void                             ClearDepth();
    
    
    static void                             Clear(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             Clear(float pRed, float pGreen, float pBlue);
    static void                             Clear();
    
    
    
    
    static void                             ClipEnable();
    static void                             ClipDisable();

    static void                             Clip(float pX, float pY, float pWidth, float pHeight);
    
    
    
    
    static void                             ClipSetAppFrame(float pX, float pY, float pWidth, float pHeight);
    
    
    
    
    static void                             ViewportSet(float pX, float pY, float pWidth, float pHeight);
    
    static void                             SetMatrixProjection(FMatrix &pMatrix);
    static void                             SetMatrixModelView(FMatrix &pMatrix);
    static void                             SetMatrix(FMatrix &pMatrix);
    
    static void                             ResetMatrixProjection();
    static void                             ResetMatrixModelView();
    
    static FMatrix                          GetMatrixProjection();
    static FMatrix                          GetMatrixModelView();
    
    
    static void                             EnableCullFaces();
    static void                             DisableCullFaces();
    
    static void                             EnableColorArray();
    static void                             DisableColorArray();
    
    
    static void                             MonocolorEnable();
    static void                             MonocolorEnable(float pRed, float pGreen, float pBlue);
    static void                             MonocolorEnable(FColor pColor);
    static void                             MonocolorDisable();
    
    
    static void                             TestBlend(int pType1, int pType2);
    
    static void                             EnableTextureCoordinateArray();
    static void                             DisableTextureCoordinateArray();
    
    static void                             EnableVertexArray();
    static void                             DisableVertexArray();
    
    static void                             EnableNormalArray();
    static void                             DisableNormalArray();
    
    static void                             MatrixPush();
    static void                             MatrixPop();
    
    static void                             MatrixGoProjection(bool pLoadIdentity);
    static void                             MatrixGoModelView(bool pLoadIdentity);
    
    static void                             MatrixGoProjection();
    static void                             MatrixGoModelView();
    
    static void                             MatrixLoadIdentity();
    
    static void                             EnableLighting();
    static void                             DisableLighting();
    
    
    
    
    
    static void                             TextureSetWrap();
    static void                             TextureSetClamp();
    
    static void                             TextureSetFilterMipMap();
    static void                             TextureSetFilterLinear();
    static void                             TextureSetFilterNearest();
    
    static void                             TextureSetModulate();
    static void                             TextureSetReplace();
    
    static void                             TextureEnable();
    static void                             TextureDisable();
    
    static int                                  TextureGenerate(unsigned int *pData, int pWidth, int pHeight);
    
    static void                             TextureSetData(int pIndex, unsigned int *pData, int pWidth, int pHeight);
    
    static void                             TextureDelete(int pIndex);
    
    static void                             TextureBind(int pIndex);
    static void                             TextureBind(FTexture *pTexture);
    static bool								TextureValid(FTexture *pTexture);
    
    
    
    
	static void                             DrawTriangle2D(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);
    
    
    
    static void                             DrawCube(float pX, float pY, float pZ, float pSize=1.0f);
    static void                             DrawCube(float pSize);
    static void                             DrawCube(){DrawCube(1.0f);}
    
    
    static void                             DrawSphere12(float x, float y, float z, float pRadius=1.0f);
    
    
    
    
    static void                             ArrayNormals(float *pArray);
    static void                             ArrayCoords(float *pArray, int pDimensionality=3);
    static void                             ArrayVertices(float *pArray, int pDimensionality=3);
    static void                             ArrayColor(float *pArray, int pDimensionality=4);
    
    static void                             ArrayCoords(float *pArray, int pStride, int pDimensionality);
    static void                             ArrayVertices(float *pArray, int pStride, int pDimensionality);
    static void                             ArrayColor(float *pArray, int pStride, int pDimensionality);
    
    static void                             DrawTriangles(int pCount);
    static void                             DrawTriangleStrips(int pCount);
    static void                             DrawTriangleFans(int pCount);
    
    static void                             DrawTriangles(unsigned int *pIndexList, int pCount);
    static void                             DrawTriangles(unsigned short *pIndexList, int pCount);
    
    static void                             DrawTriangles(int pCount, float *pXYZ, float *pUVW=0, float *pNormal=0);
    
    //Assumed - triangle list
    
    static void                             DrawModelEfficientSetup(float *pXYZ, float *pUVW, float *pNormal, FTexture *pTexture);
    
    
    static void                             DrawModelIndexedEfficientSetup(float *pXYZ, float *pUVW, float *pNormal, FTexture *pTexture);
    
    static void                             DrawModel(float *pXYZ, float *pUVW, float *pNormal, int pCount, FTexture *pTexture);
    
    static void                             DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned int *pIndex, int pCount, FTexture *pTexture);
    static void                             DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned short *pIndex, int pCount, FTexture *pTexture);
    
    static void                             DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned short *pIndex, FTexture *pTexture, int pStartIndex, int pEndIndex);
    
    static void                             DrawTrianglePrimitive(unsigned int pType, unsigned short *pIndexList, int pCount);
    static void                             DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount);
    static void                             DrawTrianglePrimitive(unsigned int pType, int pCount);
    
    static void                             DrawTrianglePrimitive(unsigned int pType, int pCount, float *pXYZ, float *pUVW=0, float *pNormal=0);
    static void                             DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount, float *pXYZ, float *pUVW=0, float *pNormal=0);
    
    static void                             DrawTrianglePrimitive(unsigned int pType, int pCount, float *pXYZ, float *pUVW, float *pNormal, int pXYZDimensinality, int pUVWDinonsionality);
	static void                             DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount, float *pXYZ, float *pUVW, float *pNormal, int pXYZDimensinality, int pUVWDinonsionality);
    
    
    static void                             Ortho2D(float pLeft, float pRight, float pBottom, float pTop);
    static void                             Ortho2D();
    
    static void                             MatrixPerspective(float pFov=64.0f);
    static void                             MatrixPerspective(float pFov, float pAspect);
    static void                             MatrixPerspective(float pFov, float pAspect, float pZNear, float pZFar);
    
    static void                             MatrixFrustum(float pLeft, float pRight, float pBottom, float pTop, float pNearZ, float pFarZ);
    
    
    
    static void                             MatrixLookAt(float pEyeX, float pEyeY, float pEyeZ,
                                             float pCenterX, float pCenterY, float pCenterZ,
                                             float pUpX, float pUpY, float pUpZ);
    
    
    static void                             SetShadeFlat();
    static void                             SetShadeSmooth();
    
    
    static void                             BlendEnable();
    static void                             BlendDisable();
    
    
    static void										BlendSetAlpha();
    static void										BlendSetAdditive();
    static void										BlendSetPremultiplied();
    static void										BlendSetSubtract();
    
    static void										BlendSetInvert1();
    static void										BlendSetInvert2();
    static void										BlendSetGhost1();
    static void										BlendSetGhost2();
    
    
    
    static void										BlendSetType(int pType);
    
    
    
    
    
    static void                             CullFacesEnable();
    static void                             CullFacesDisable();
    static void                             CullFacesSetFront();
    static void                             CullFacesSetBack();
    
    
    
    static void                             DrawSprite(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pVerts, float *pCoords, FTexture *pTexture);
    static void                             DrawSprite(float *pVerts, float *pCoords, FTexture *pTexture);
    
    
    static void                             DrawSpriteTriangle(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pVerts, float *pCoords, FTexture *pTexture);
    static void                             DrawSpriteTriangle(float *pVerts, float *pCoords, FTexture *pTexture);
    
    //int                         mTextureSwaps;
    
    
    
    static void                             Rotate(float pDegrees, float pAxisX, float pAxisY, float pAxisZ);
    static void                             Rotate(float pDegreesX, float pDegreesY, float pDegreesZ);
    inline static void                             RotateX(float pDegrees){Rotate(pDegrees,1,0,0);}
    inline static void                             RotateY(float pDegrees){Rotate(pDegrees,0,1,0);}
    inline static void                             RotateZ(float pDegrees){Rotate(pDegrees,0,0,1);}
    inline static void                             Rotate(float pDegrees){RotateZ(pDegrees);}
    
    
    static void                             Translate(float x, float y, float z);
    inline static void                             Translate(FVec2 pTranslation){Translate(pTranslation.mX, pTranslation.mY, 0.0f);}
    inline static void                             Translate(FVec3 pTranslation){Translate(pTranslation.mX, pTranslation.mY, pTranslation.mZ);}
    inline static void                             Translate(float x, float y){Translate(x,y,0);}
    inline static void                             TranslateX(float x){Translate(x,0,0);}
    inline static void                             TranslateY(float y){Translate(0,y,0);}
    inline static void                             TranslateZ(float z){Translate(0,0,z);}
    
    static void										Scale(float x, float y, float z);
    inline static void                             Scale(float pScale){Scale(pScale,pScale,pScale);}
    
    
    
    
    static unsigned int								GetLight(int pIndex);
    static void										LightSetAmbient(int pLightIndex, float pRed=1, float pGreen=1, float pBlue=1, float pAlpha=1); 
    static void                             LightSetDiffuse(int pLightIndex, float pRed=1, float pGreen=1, float pBlue=1, float pAlpha=1); 
    static void                             LightSetSpecular(int pLightIndex, float pRed=1, float pGreen=1, float pBlue=1, float pAlpha=1); 
    static void                             LightSetEnabled(int pLightIndex, bool pState=true);
    
    static void										LightSetPos(int pLightIndex,float x, float y);
    static void                             LightSetPos(int pLightIndex,float x, float y, float z);
    static void                             LightSetPos(int pLightIndex,float x, float y, float z, float w);
    
    static void                             LightSetSpotDir(int pLightIndex, float x, float y);
    static void                             LightSetSpotDir(int pLightIndex, float x, float y, float z);
    static void                             LightSetSpotDir(int pLightIndex, float x, float y, float z, float w);
    
    static void                             LightSetXYAngle(int pLightIndex,float pRotation);
    static void                             LightSetZAngle(int pLightIndex,float pRotation);
    
    static void                             LightFaceTarget(int pLightIndex, float pTargetX, float pTargetY, float pTargetZ=0);
    static void                             LightFaceTargetAway(int pLightIndex, float pTargetX, float pTargetY, float pTargetZ=0);
    
    //Default: 1
    static void                             LightSetAttenuationConstant(int pLightIndex, float pValue);
    //Default: 0
    static void                             LightSetAttenuationLinear(int pLightIndex, float pValue);
    //Default: 0
    static void                             LightSetAttenuationQuadratic(int pLightIndex, float pValue);
    //Range [0 - 90, Special Value = 180] Default: 180
    static void                             LightSetSpotCutoff(int pLightIndex, float pValue);
    //Range [0 - 128] Default: 0
    static void                             LightSetSpotExponent(int pLightIndex, float pValue);
    
    
    
    
    static float                            LightGetAttenuationConstant(int pLightIndex);
    static float                            LightGetAttenuationLinear(int pLightIndex);
    static float                            LightGetAttenuationQuadratic(int pLightIndex);
    static float                            LightGetSpotCutoff(int pLightIndex);
    static float                            LightGetSpotExponent(int pLightIndex);
    
    static float                            LightGetColor(int pLight, int pType, int pChannel);
    static float                            LightGetPos(int pLight, int pDimension);
    static float                            LightGetSpotDir(int pLight, int pDimension);
    
    static bool								LightGetEnabled(int pLight);
    
    static void                             ApplyLighting();
    static void                             ApplyLightingBasic();
    static void                             LightSetDefault();
    
    static void                             MaterialEnable();
    static void                             MaterialDisable();
    static void                             MaterialSetDefault();
    
    static void                             MaterialSetAmbient(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             MaterialSetDiffuse(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             MaterialSetSpecular(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             MaterialSetEmission(float pRed, float pGreen, float pBlue, float pAlpha);
    //0-128
    static void                             MaterialSetShininess(float pShininess);
    
    static float                            MaterialGetAmbient(int pChannel);
    static float                            MaterialGetDiffuse(int pChannel);
    static float                            MaterialGetSpecular(int pChannel);
    static float                            MaterialGetEmission(int pChannel);
    
    static float                            MaterialGetColor(int pType, int pChannel);
    static float                            MaterialGetShininess();
    
    
    
    static void                             FogEnable();
    static void                             FogDisable();
    
    static void                             FogInitialize();
        
    static void                             FogSetStart(float pStart);
    static void                             FogSetEnd(float pEnd);
    static void                             FogSetColor(float pRed=0.0f, float pGreen=0.0f, float pBlue=0.0f, float pAlpha=1.0f);
    static void                             FogSetDensity(float pDensity);
    static void                             FogSetLinear();
    static void                             FogSetDiff();
    static void                             FogSetDiffSquared();
    
    static void                             PrintLight();
    
};

//extern Graphics gGraphics;


/*
void DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation=0);
void DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);

void RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture);
void RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture);


void RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale);

//void SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha);
//void SetColorHex(int pRed, int pGreen, int pBlue);
//void SetColorHex(int pAlpha);

//void SetColor(float pRed, float pGreen, float pBlue, float pAlpha);
//void SetColor(float pRed, float pGreen, float pBlue);
//void SetColor(float pIntensity);
//void SetColor();
//void SetColor(FColor pColor);
//void SetColorSwatch(int pSwatchIndex);
//void SetColorSwatch(int pSwatchIndex, float pAlpha);

void DrawQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);


 
 
void OutlineRect(float pX, float pY, float pWidth, float pHeight, float pThickness);
void OutlineRectInside(float pX, float pY, float pWidth, float pHeight, float pThickness);


void DrawRect(float pX, float pY, float pWidth, float pHeight);
void DrawLine(float pX1, float pY1, float pX2, float pY2);


void DrawLine(float pX1, float pY1, float pX2, float pY2, float pThickness);
void DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength);
void DrawPoint(float pX, float pY, float pSize);


//Deprecate these...
void Go3D();
void Go2D();

//void EnableDepth();
//void DisableDepth();

//void DepthEnable();
//void DepthDisable();

//void DepthClear();
//void DepthMaskFalse();
//void DepthMaskTrue();

//void ClearDepth(float pRed, float pGreen, float pBlue, float pAlpha);
//void ClearDepth(float pRed, float pGreen, float pBlue);
//void ClearDepth();

//void Clear(float pRed, float pGreen, float pBlue, float pAlpha);
//void Clear(float pRed, float pGreen, float pBlue);
//void Clear();

*/

/*

void ClipEnable();
void ClipDisable();
void Clip(float pX, float pY, float pWidth, float pHeight);
void ClipAbsolute(float pX, float pY, float pWidth, float pHeight);

void ViewportSet(float pX, float pY, float pWidth, float pHeight);

void SetMatrixProjection(FMatrix &pMatrix);
void SetMatrixModelView(FMatrix &pMatrix);
void SetMatrix(FMatrix &pMatrix);

void ResetMatrixProjection();
void ResetMatrixModelView();

FMatrix GetMatrixProjection();
FMatrix GetMatrixModelView();


void EnableCullFaces();
void DisableCullFaces();

void EnableColorArray();
void DisableColorArray();


void MonocolorEnable();
void MonocolorEnable(float pRed, float pGreen, float pBlue);
void MonocolorEnable(FColor pColor);
void MonocolorDisable();


void TestBlend(int pType1, int pType2);

void EnableTextureCoordinateArray();
void DisableTextureCoordinateArray();

void EnableVertexArray();
void DisableVertexArray();

void EnableNormalArray();
void DisableNormalArray();

void MatrixPush();
void MatrixPop();

void MatrixGoProjection(bool pLoadIdentity);
void MatrixGoModelView(bool pLoadIdentity);

void MatrixGoProjection();
void MatrixGoModelView();

void MatrixLoadIdentity();

void EnableLighting();
void DisableLighting();

void TextureSetWrap();
void TextureSetClamp();

void TextureSetFilterMipMap();
void TextureSetFilterLinear();

void TextureSetModulate();

void TextureEnable();
void TextureDisable();

int TextureGenerate(unsigned int *pData, int pWidth, int pHeight);

void TextureSetData(int pIndex, unsigned int *pData, int pWidth, int pHeight);
void TextureDelete(int pIndex);
 
*/


#endif
