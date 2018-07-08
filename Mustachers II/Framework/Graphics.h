#include "Color.h"
#include "Rectangle.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GRAPHICS_MODEL_TYPE unsigned short
#define GRAPHICS_LIGHT_COUNT 8
#define GRAPHICS_MODEL_SAFETY 1

void Clip(float x, float y, float pWidth, float pHeight);
void Clip(Rectangle pRect);
void Clip();



void SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha);
void SetColorHex(int pRed, int pGreen, int pBlue);
void SetColorHex(int pAlpha);



void SetColor(float pRed, float pGreen, float pBlue, float pAlpha);
void SetColor(float pRed, float pGreen, float pBlue);
void SetColor(float pIntensity);
void SetColor();
void SetColor(Color pColor);
void SetColorSwatch(int pSwatchIndex);

void Rotate(float pDegrees);

void DrawQuad(float x1, float y1,
			  float x2, float y2,
			  float x3, float y3,
			  float x4, float y4);


void OutlineRect(float x, float y, float pWidth, float pHeight, float pThickness);


void DrawRect(float x, float y, float pWidth, float pHeight);
inline void DrawRect(FPoint pPos, float pWidth, float pHeight){DrawRect(pPos.mX,pPos.mY,pWidth,pHeight);}
inline void DrawRect(FPoint pPos, FPoint pSize){DrawRect(pPos.mX,pPos.mY,pSize.mX,pSize.mY);}
inline void DrawRect(Rectangle pRect){DrawRect(pRect.mX,pRect.mY,pRect.mWidth,pRect.mHeight);}
inline void DrawRect(IRectangle pRect){DrawRect((float)pRect.mX,(float)pRect.mY,(float)pRect.mWidth,(float)pRect.mHeight);}

void		SetAdditive(bool pState);

void		Translate(float x, float y);
inline void	Translate(FPoint pPosition){Translate(pPosition.mX,pPosition.mY);}

void		Scale(float pScale);

void        DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength=7.5);

void		DrawLine(float x1, float y1, float x2, float y2);
inline void	DrawLine(FPoint p1, FPoint p2){DrawLine(p1.mX,p1.mY,p2.mX,p2.mY);}

void		DrawLine(float x1, float y1, float x2, float y2, float pThickness);
inline void	DrawLine(FPoint p1, FPoint p2, float pThickness){DrawLine(p1.mX,p1.mY,p2.mX,p2.mY, pThickness);}

void		SetTranslate(float x, float y);

void		DrawPoint(float x, float y, float pSize=7);
inline void	DrawPoint(FPoint pPoint, float pSize=7){DrawPoint(pPoint.mX,pPoint.mY,pSize);}

void		ClearBuffer(Color pColor=Color(0,0,0,1));
inline void	ClearBuffer(float pRed, float pGreen, float pBlue, float pAlpha){ClearBuffer(Color(pRed,pGreen,pBlue,pAlpha));}
inline void	ClearBuffer(float pRed, float pGreen, float pBlue){ClearBuffer(Color(pRed,pGreen,pBlue,1));}
inline void	ClearBuffer(float pIntensity){ClearBuffer(Color(pIntensity,pIntensity,pIntensity,1));}

void		RenderWhite(bool theState, Color pColor);


class Graphics
{
public:
    Graphics();
    ~Graphics();
    
    static void                 DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation=0);
    static void                 DrawQuad(float x1, float y1, float z1,
                                         float x2, float y2, float z2,
                                         float x3, float y3, float z3,
                                         float x4, float y4, float z4);
    
    static void                 Go3D();
    static void                 Go2D();
    
    static void                 EnableDepth();
    static void                 DisableDepth();
    
    static void                 ClearDepth(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                 ClearDepth(float pRed, float pGreen, float pBlue);
    static void                 ClearDepth();
    
    
    static void                 Clear(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                 Clear(float pRed, float pGreen, float pBlue);
    static void                 Clear();
    
    
    
    static void                 DepthEnable();
    static void                 DepthClear();
    static void                 DepthMaskFalse();
    static void                 DepthMaskTrue();
    
    
    
    static void                 EnableCullFaces();
    static void                 DisableCullFaces();
    
    static void                 EnableColorArray();
    static void                 DisableColorArray();
    
    
    static void                 TestBlend(int pType1, int pType2);
    
    static void                 EnableTextureCoordinateArray();
    static void                 DisableTextureCoordinateArray();
    
    static void                 EnableVertexArray();
    static void                 DisableVertexArray();
    
    static void                 EnableNormalArray();
    static void                 DisableNormalArray();
    
    static void                 MatrixPush();
    static void                 MatrixPop();
    
    static void                 MatrixGoProjection(bool pLoadIdentity=true);
    static void                 MatrixGoModelView(bool pLoadIdentity=true);
    static void                 MatrixLoadIdentity();
    
    static void                 EnableLighting();
    static void                 DisableLighting();
    
    static void                 TextureSetWrap();
    static void                 TextureSetClamp();
    
    static void                 TextureSetFilterMipMap();
    static void                 TextureSetFilterLinear();
    
    static void                 EnableTexture();
    static void                 DisableTexture();
    
    static void                 DrawCube(float pX, float pY, float pZ, float pSize=1.0f);
    
    static int                  GenerateTexture(unsigned int *pData, int pWidth, int pHeight);

    static void                 BindTexture(int pIndex, unsigned int *pData, int pWidth, int pHeight);
    
    static void                 UnbindTexture(int pIndex);
    
    static void                 ArrayNormals(float *pArray);
    static void                 ArrayCoords(float *pArray, int pDimensionality=3);
    static void                 ArrayVertices(float *pArray, int pDimensionality=3);
    static void                 ArrayColor(float *pArray, int pDimensionality=4);
    
    static void                 DrawTriangles(int pCount);
    static void                 DrawTriangleStrips(int pCount);
    static void                 DrawTriangleFans(int pCount);
    
    static void                 DrawTriangles(unsigned int *pIndexList, int pCount);
    static void                 DrawTriangles(unsigned short *pIndexList, int pCount);
    
    static void                 DrawTriangles(int pCount, float *pXYZ, float *pUVW=0, float *pNormal=0);
    
    //Assumed - triangle list
    
    static void                 DrawModelEfficientSetup(float *pXYZ, float *pUVW, float *pNormal, int pBindIndex);
    
    
    static void                 DrawModelIndexedEfficientSetup(float *pXYZ, float *pUVW, float *pNormal, int pBindIndex);
    
    
    
    static void                 DrawModel(float *pXYZ, float *pUVW, float *pNormal, int pCount, int pBindIndex);
    
    static void                 DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned int *pIndex, int pCount, int pBindIndex);
    static void                 DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned short *pIndex, int pCount, int pBindIndex);
    
    static void                 DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned short *pIndex, int pBindIndex, int pStartIndex, int pEndIndex);
    
    static void                 DrawTrianglePrimitive(unsigned int pType, unsigned short *pIndexList, int pCount);
    static void                 DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount);
    static void                 DrawTrianglePrimitive(unsigned int pType, int pCount);
    
    static void                 DrawTrianglePrimitive(unsigned int pType, int pCount, float *pXYZ, float *pUVW=0, float *pNormal=0);
    static void                 DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount, float *pXYZ, float *pUVW=0, float *pNormal=0);
    
    
    static void                 DrawTrianglePrimitive(unsigned int pType, int pCount, float *pXYZ, float *pUVW, float *pNormal, int pXYZDimensinality, int pUVWDinonsionality);
    static void                 DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount, float *pXYZ, float *pUVW, float *pNormal, int pXYZDimensinality, int pUVWDinonsionality);
    
    
    static void                 MatrixOrtho2D(float pLeft, float pRight, float pBottom, float pTop);
    static void                 MatrixOrtho2D();
    
    static void                 MatrixPerspective(float pFov=64.0f);
    static void                 MatrixPerspective(float pFov, float pAspect);
    static void                 MatrixPerspective(float pFov, float pAspect, float pZNear, float pZFar);    
    
    static void                 MatrixLookAt(float pEyeX, float pEyeY, float pEyeZ,
                                             float pCenterX, float pCenterY, float pCenterZ,
                                             float pUpX, float pUpY, float pUpZ);
    
    
    static void                 SetShadeFlat();
    static void                 SetShadeSmooth();
    
    
    static void                 BlendEnable();
    static void                 BlendDisable();
    
    static void                 BlendSetAlpha();
    static void                 BlendSetAdditive();
    
    static void                 BindTexture(int pIndex);
    static void                 UnbindTexture();
    
    
    static void                 CullFacesEnable();
    static void                 CullFacesDisable();
    static void                 CullFacesSetFront();
    static void                 CullFacesSetBack();
    
    
    
    static void                 DrawSprite(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pVerts, float *pCoords, int pBindIndex);
    static void                 DrawSprite(float *pVerts, float *pCoords, int pBindIndex);
    
    //int                         mTextureSwaps;
    
    
    
    static void                 Rotate(float pDegrees, float pAxisX, float pAxisY, float pAxisZ);
    static void                 Rotate(float pDegreesX, float pDegreesY, float pDegreesZ);
    inline static void          RotateX(float pDegrees){Rotate(pDegrees,1,0,0);}
    inline static void          RotateY(float pDegrees){Rotate(pDegrees,0,1,0);}
    inline static void          RotateZ(float pDegrees){Rotate(pDegrees,0,0,1);}
    inline static void          Rotate(float pDegrees){RotateZ(pDegrees);}
    
    
    static void                 Translate(float x, float y, float z);
    inline static void          Translate(float x, float y){Translate(x,y,0);}
    inline static void          TranslateX(float x){Translate(x,0,0);}
    inline static void          TranslateY(float y){Translate(0,y,0);}
    inline static void          TranslateZ(float z){Translate(0,0,z);}
    
    static void                 Scale(float x, float y, float z);
    inline static void          Scale(float pScale){Scale(pScale,pScale,pScale);}
    
    
    static void                 DrawSphere12(float x, float y, float z, float pRadius=1.0f);
    
    
    
    static unsigned int         GetLight(int pIndex);
    static void                 LightSetAmbient(int pLightIndex, float pRed=1, float pGreen=1, float pBlue=1, float pAlpha=1); 
    static void                 LightSetDiffuse(int pLightIndex, float pRed=1, float pGreen=1, float pBlue=1, float pAlpha=1); 
    static void                 LightSetSpecular(int pLightIndex, float pRed=1, float pGreen=1, float pBlue=1, float pAlpha=1); 
    static void                 LightSetEnabled(int pLightIndex, bool pState=true);
    
    static void                 LightSetPos(int pLightIndex,float x, float y);
    static void                 LightSetPos(int pLightIndex,float x, float y, float z);
    static void                 LightSetPos(int pLightIndex,float x, float y, float z, float w);
    
    static void                 LightSetSpotDir(int pLightIndex, float x, float y);
    static void                 LightSetSpotDir(int pLightIndex, float x, float y, float z);
    static void                 LightSetSpotDir(int pLightIndex, float x, float y, float z, float w);
    
    static void                 LightSetXYAngle(int pLightIndex,float pRotation);
    static void                 LightSetZAngle(int pLightIndex,float pRotation);
    
    void                        LightFaceTarget(int pLightIndex, float pTargetX, float pTargetY, float pTargetZ=0);
    void                        LightFaceTargetAway(int pLightIndex, float pTargetX, float pTargetY, float pTargetZ=0);
    
    //Default: 1
    static void                 LightSetAttenuationConstant(int pLightIndex, float pValue);
    //Default: 0
    static void                 LightSetAttenuationLinear(int pLightIndex, float pValue);
    //Default: 0
    static void                 LightSetAttenuationQuadratic(int pLightIndex, float pValue);
    //Range [0 - 90, Special Value = 180] Default: 180
    static void                 LightSetSpotCutoff(int pLightIndex, float pValue);
    //Range [0 - 128] Default: 0
    static void                 LightSetSpotExponent(int pLightIndex, float pValue);
    
    
    
    
    static float                LightGetAttenuationConstant(int pLightIndex);
    static float                LightGetAttenuationLinear(int pLightIndex);
    static float                LightGetAttenuationQuadratic(int pLightIndex);
    static float                LightGetSpotCutoff(int pLightIndex);
    static float                LightGetSpotExponent(int pLightIndex);
    
    static float                LightGetColor(int pLight, int pType, int pChannel);
    static float                LightGetPos(int pLight, int pDimension);
    static float                LightGetSpotDir(int pLight, int pDimension);
    
    static bool                 LightGetEnabled(int pLight);
    
    static void                 ApplyLighting();
    static void                 ApplyLightingBasic();
    static void                 LightSetDefault();
    
    static void                 MaterialEnable();
    static void                 MaterialDisable();
    static void                 MaterialSetDefault();
    
    static void                 MaterialSetAmbient(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                 MaterialSetDiffuse(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                 MaterialSetSpecular(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                 MaterialSetEmission(float pRed, float pGreen, float pBlue, float pAlpha);
    //0-128
    static void                 MaterialSetShininess(float pShininess);
    
    static float                MaterialGetAmbient(int pChannel);
    static float                MaterialGetDiffuse(int pChannel);
    static float                MaterialGetSpecular(int pChannel);
    static float                MaterialGetEmission(int pChannel);
    
    static float                MaterialGetColor(int pType, int pChannel);
    static float                MaterialGetShininess();
    
    
    
    static void                 FogEnable();
    static void                 FogDisable();
    
    static void                 FogInitialize();
        
    static void                 FogSetStart(float pStart);
    static void                 FogSetEnd(float pEnd);
    static void                 FogSetColor(float pRed=0.0f, float pGreen=0.0f, float pBlue=0.0f, float pAlpha=1.0f);
    static void                 FogSetDensity(float pDensity);
    static void                 FogSetLinear();
    static void                 FogSetDiff();
    static void                 FogSetDiffSquared();
    
    
    /*
    
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209
     
     */
    
    
    static void                 PrintLight();
    
};

extern Graphics gGraphics;

#endif