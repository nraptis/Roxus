#include "core_includes.h"
#include "core_graphics.h"
#include "core_includes.h"
#include "FApp.hpp"
#include "PlatformOpenGLView.hpp"

#define GRAPHICS_CLIP_STACK_COUNT 256

#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)

#ifndef glOrthof

#define glOrthof glOrtho

#endif
#endif

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE GL_CLAMP

#endif

int gGraphicsThread = -1;

static float                cClipRect[4];
static float                cClipRectBase[4];
static bool                 cClipEnabled = false;

static float                cEnvironmentColor[4];

static float                cFogColor[4];
static float                cFogDensity;
static float                cFogStart;
static float                cFogEnd;


static unsigned int         gLight[GRAPHICS_LIGHT_COUNT] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

static float                cLightAmbient[GRAPHICS_LIGHT_COUNT][4];
static float                cLightDiffuse[GRAPHICS_LIGHT_COUNT][4];
static float                cLightSpecular[GRAPHICS_LIGHT_COUNT][4];

static float                cLightPosition[GRAPHICS_LIGHT_COUNT][4];
static float                cLightSpotDirection[GRAPHICS_LIGHT_COUNT][4];

static float                cLightSpotCutoff[GRAPHICS_LIGHT_COUNT];
static float                cLightSpotExponent[GRAPHICS_LIGHT_COUNT];

static float                cLightConstantAttenuation[GRAPHICS_LIGHT_COUNT];
static float                cLightLinearAttenuation[GRAPHICS_LIGHT_COUNT];
static float                cLightQuadraticAttenuation[GRAPHICS_LIGHT_COUNT];

static bool                 cLightEnabled[GRAPHICS_LIGHT_COUNT];

static float                cRectBuffer[12];

static float                cMaterialAmbient[4];
static float                cMaterialDiffuse[4];
static float                cMaterialSpecular[4];
static float                cMaterialEmission[4];
static float                cMaterialShininess;

static int                  cBindIndex;

void core_graphics_initialize()
{
    cClipRect[0] = 0.0f;
    cClipRect[1] = 0.0f;
    cClipRect[2] = 640.0f;
    cClipRect[3] = 480.0f;
    
    Graphics::BlendEnable();
    Graphics::BlendSetAlpha();
    Graphics::TextureSetClamp();
    Graphics::TextureSetFilterLinear();
    Graphics::TextureSetModulate();
    Graphics::TextureEnable();
    Graphics::EnableTextureCoordinateArray();
    Graphics::EnableVertexArray();
}

void SetAdditive(bool pState)
{
    if (pState) {
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    } else {
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }
}

void Scale(float pScale){glScalef(pScale,pScale,pScale);}

void Translate(float x, float y){glTranslatef(x,y,0);}

void SetTranslate(float x, float y){Translate(x,y);}

void RenderWhite(bool theState, FColor pColor)
{
    if(theState==true)
    {
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_BLEND);
        glTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_COLOR,(GLfloat*)&pColor);
    }
    else
    {
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        //glTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_COLOR,(GLfloat*)&mColor);
    }
}

Graphics::Graphics()
{
    //cBindIndex=-1;
    //MaterialSetDefault();
    //LightSetDefault();
    
}

Graphics::~Graphics()
{
    
}


void Graphics::ThreadLock() {
    
    if (os_thread_lock_exists(gGraphicsThread) == false) {
        gGraphicsThread = os_create_thread_lock();
    }
    os_lock_thread(gGraphicsThread);
    if (gOpenGLView) {
        gOpenGLView->SetContext();
        
    }
}

void Graphics::ThreadUnlock() {
    os_unlock_thread(gGraphicsThread);
}

void Graphics::DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2,
                        float x3, float y3, float z3, float x4, float y4, float z4)
{
    cRectBuffer[0]=x1;
    cRectBuffer[1]=y1;
    cRectBuffer[2]=z1;
    
    cRectBuffer[3]=x2;
    cRectBuffer[4]=y2;
    cRectBuffer[5]=z2;
    
    cRectBuffer[6]=x3;
    cRectBuffer[7]=y3;
    cRectBuffer[8]=z3;
    
    cRectBuffer[9]=x4;
    cRectBuffer[10]=y4;
    cRectBuffer[11]=z4;
    
    TextureDisable();
    ArrayVertices(cRectBuffer, 3);
    DrawTriangleStrips(4);
    
    //glDisable( GL_TEXTURE_2D);
    //glVertexPointer(3,GL_FLOAT,0,cRectBuffer);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void Graphics::SetColor(float pRed, float pGreen, float pBlue, float pAlpha){glColor4f(pRed,pGreen,pBlue,pAlpha);}
void Graphics::SetColor(float pRed, float pGreen, float pBlue){Graphics::SetColor(pRed,pGreen,pBlue,1);}
void Graphics::SetColor(float pIntensity){Graphics::SetColor(1,1,1,pIntensity);}
void Graphics::SetColor(){Graphics::SetColor(1,1,1,1);}
void Graphics::SetColor(FColor pColor){Graphics::SetColor(pColor.mRed,pColor.mGreen,pColor.mBlue,pColor.mAlpha);}


void Graphics::SetEnvironmentColor(float pRed, float pGreen, float pBlue, float pAlpha)
{
    cEnvironmentColor[0] = pRed;
    cEnvironmentColor[1] = pGreen;
    cEnvironmentColor[2] = pBlue;
    cEnvironmentColor[3] = pAlpha;
    
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, (GLfloat*)cEnvironmentColor);
}
void Graphics::SetEnvironmentColor(float pRed, float pGreen, float pBlue){Graphics::SetEnvironmentColor(pRed,pGreen,pBlue,1);}
void Graphics::SetEnvironmentColor(float pIntensity){Graphics::SetEnvironmentColor(1,1,1,pIntensity);}
void Graphics::SetEnvironmentColor(){Graphics::SetEnvironmentColor(1,1,1,1);}
void Graphics::SetEnvironmentColor(FColor pColor)
{Graphics::SetEnvironmentColor(pColor.mRed,pColor.mGreen,pColor.mBlue,pColor.mAlpha);}



void Graphics::SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha)
{
    Graphics::SetColor((float)pRed/255.0f, (float)pGreen/255.0f, (float)pBlue/255.0f, (float)pAlpha/255.0f);
}

void Graphics::SetColorHex(int pRed, int pGreen, int pBlue)
{
    SetColorHex(pRed, pGreen, pBlue, 255);
}

void Graphics::SetColorHex(int pAlpha)
{
    SetColorHex(255,255,255,pAlpha);
}



void Graphics::DrawQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4)
{
    
    cRectBuffer[0] = pX1;
    cRectBuffer[1] = pY1;
    
    cRectBuffer[2] = pX2;
    cRectBuffer[3] = pY2;
    
    cRectBuffer[4] = pX3;
    cRectBuffer[5] = pY3;
    
    cRectBuffer[6] = pX4;
    cRectBuffer[7] = pY4;

    TextureDisable();
    ArrayVertices(cRectBuffer, 2);
    DrawTriangleStrips(4);
}

void Graphics::DrawTriangle2D(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
{
    cRectBuffer[0] = pX1;
    cRectBuffer[1] = pY1;

    cRectBuffer[2] = pX2;
    cRectBuffer[3] = pY2;

    cRectBuffer[4] = pX3;
    cRectBuffer[5] = pY3;


    TextureDisable();
    ArrayVertices(cRectBuffer, 2);
    DrawTriangles(3);
}

void Graphics::DrawRect(float pX, float pY, float pWidth, float pHeight)
{
    DrawQuad(pX, pY, pX + pWidth, pY, pX, pY + pHeight, pX + pWidth, pY + pHeight);
}

void Graphics::OutlineRect(float pX, float pY, float pWidth, float pHeight, float pThickness)
{
    DrawRect(pX-pThickness, pY-pThickness, pWidth + pThickness * 2, pThickness);
    DrawRect(pX-pThickness, pY+pHeight, pWidth + pThickness * 2, pThickness);
    DrawRect(pX-pThickness, pY, pThickness, pHeight);
    DrawRect(pX+pWidth, pY, pThickness, pHeight);
    
}

void Graphics::OutlineRectInside(float pX, float pY, float pWidth, float pHeight, float pThickness)
{
    OutlineRect(pX + pThickness, pY + pThickness, pWidth - pThickness * 2, pHeight - pThickness * 2, pThickness);
}

void Graphics::OutlineRect(FRect pRect, float pThickness)
{
    OutlineRect(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight, pThickness);
}

void Graphics::OutlineRectInside(FRect pRect, float pThickness)
{
    OutlineRectInside(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight, pThickness);
}





void Graphics::SetColorSwatch(int pSwatchIndex, float pAlpha)
{
    bool aSign = pSwatchIndex < 0;
    
    if(aSign)
    {
        pSwatchIndex = (-pSwatchIndex);
    }
    
    if(pSwatchIndex >= 8)
    {
        pSwatchIndex = (pSwatchIndex % 8);
    }
    
    if(aSign)
    {
        pSwatchIndex = (8 - pSwatchIndex);
    }
    
    if(pSwatchIndex==0)
    {
        Graphics::SetColor(1,0,0, pAlpha);
    }
    else if(pSwatchIndex==1)
    {
        Graphics::SetColor(0,1,0, pAlpha);
    }
    else if(pSwatchIndex==2)
    {
        Graphics::SetColor(0,0,1, pAlpha);
    }
    else if(pSwatchIndex==3)
    {
        Graphics::SetColor(0.5f,1,1, pAlpha);
    }
    else if(pSwatchIndex==4)
    {
        Graphics::SetColor(1,0.5f,1, pAlpha);
    }
    else if(pSwatchIndex==5)
    {
        Graphics::SetColor(1,1,0.5, pAlpha);
    }
    else if(pSwatchIndex==6)
    {
        Graphics::SetColor(1,0.5f,0.5, pAlpha);
    }
    else if(pSwatchIndex==7)
    {
        Graphics::SetColor(0.5f,1,0.5, pAlpha);
    }
    else
    {
        Graphics::SetColor(0.5f,0.5f,1, pAlpha);
    }
}

void Graphics::SetColorSwatch(int pSwatchIndex)
{
    SetColorSwatch(pSwatchIndex, 1.0f);
}





//static void                                 ;
//static void                                 ;


void Graphics::DrawLine(float pX1, float pY1, float pX2, float pY2)
{
    glDisable( GL_TEXTURE_2D);

    float aPos[4];
    aPos[0] = pX1;
    aPos[1] = pY1;
    aPos[2] = pX2;
    aPos[3] = pY2;

    glVertexPointer(2,GL_FLOAT,0,aPos);
    glDrawArrays(GL_LINES, 0, 2);
}

void Graphics::DrawLine(float pX1, float pY1, float pX2, float pY2, float pThickness) {
    float aDirX = pX2 - pX1;
    float aDirY = pY2 - pY1;
    float aDist = sqrtf((aDirX * aDirX) + (aDirY * aDirY));

    aDirX /= aDist;
    aDirY /= aDist;

    float aHold = aDirX;
    
    aDirX=-aDirY;
    aDirY=aHold;
    aDirX*=pThickness;
    aDirY*=pThickness;

    DrawQuad(pX2-aDirX,pY2-aDirY,pX2+aDirX,pY2+aDirY,pX1-aDirX,pY1-aDirY,pX1+aDirX,pY1+aDirY);
}

void Graphics::DrawPoint(float pX, float pY, float pSize) {
    DrawRect(pX-pSize/2, pY-pSize/2, pSize, pSize);
}

void Graphics::DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength, float pThickness) {
    DrawLine(pStartX, pStartY, pEndX, pEndY, pThickness);
    
    float aDiffX = pStartX - pEndX;
    float aDiffY = pStartY - pEndY;
    
    float aAngle = RADIANS_TO_DEGREES(atan2f(aDiffX, aDiffY));
    
    float aAngle1 = aAngle + 35;
    float aAngle2 = aAngle - 35;
    
    DrawLine(pEndX, pEndY, pEndX + Sin(aAngle1) * pHeadLength, pEndY + Cos(aAngle1) * pHeadLength, pThickness);
    DrawLine(pEndX, pEndY, pEndX + Sin(aAngle2) * pHeadLength, pEndY + Cos(aAngle2) * pHeadLength, pThickness);
}



void Graphics::LightSetDefault()
{
    for(int i=0;i<GRAPHICS_LIGHT_COUNT;i++)
    {
        cLightEnabled[i]=false;
        
        cLightConstantAttenuation[i]=1.0f;
        cLightLinearAttenuation[i]=0.0f;
        cLightQuadraticAttenuation[i]=0.0f;
        
        cLightSpotCutoff[i]=0.0f;
        cLightSpotExponent[i]=0.0f;
        
        cLightPosition[i][0]=0.0f;
        cLightPosition[i][1]=0.0f;
        cLightPosition[i][2]=-1.0f;
        cLightPosition[i][3]=0.0f;
        
        cLightSpotDirection[i][0]=0.0f;
        cLightSpotDirection[i][1]=0.0f;
        cLightSpotDirection[i][2]=-1.0f;
        cLightSpotDirection[i][3]=0.0f;
        
        cLightAmbient[i][0] = 0.66f;
        cLightAmbient[i][1] = 0.66f;
        cLightAmbient[i][2] = 0.66f;
        cLightAmbient[i][3] = 1.0f;
        
        cLightDiffuse[i][0] = 0.66f;
        cLightDiffuse[i][1] = 0.66f;
        cLightDiffuse[i][2] = 0.66f;
        cLightDiffuse[i][3] = 1.0f;
        
        cLightSpecular[i][0] = 0.66f;
        cLightSpecular[i][1] = 0.66f;
        cLightSpecular[i][2] = 0.66f;
        cLightSpecular[i][3] = 1.0f;
    }
    
    cLightEnabled[0] = true;
    
    cLightAmbient[0][0]=1.0f;
    cLightDiffuse[0][0]=1.0f;
    cLightSpecular[0][0]=1.0f;
    
    cLightAmbient[1][1]=1.0f;
    cLightDiffuse[1][1]=1.0f;
    cLightSpecular[1][1]=1.0f;
    
    cLightAmbient[2][2]=1.0f;
    cLightDiffuse[2][2]=1.0f;
    cLightSpecular[2][2]=1.0f;
    
    
    cFogStart=2.0f;
    cFogEnd=10.0f;
    
}

void Graphics::MaterialSetDefault()
{
    MaterialSetShininess(0.0f);
    MaterialSetAmbient(0.2f, 0.2f, 0.2f, 1.0f);
    MaterialSetDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
    MaterialSetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    MaterialSetEmission(0.0f,0.0f,0.0f,1.0f);
    
    //cMaterialAmbient[0]=0.2f;
    //cMaterialAmbient[1]=0.2f;
    //cMaterialAmbient[2]=0.2f;
    //cMaterialAmbient[3]=1.0f;
    
    //cMaterialDiffuse[0]=0.8f;
    //cMaterialDiffuse[1]=0.8f;
    //cMaterialDiffuse[2]=0.8f;
    //cMaterialDiffuse[3]=1.0f;
    
    //cMaterialSpecular[0]=0.0f;
    //cMaterialSpecular[1]=0.0f;
    //cMaterialSpecular[2]=0.0f;
    //cMaterialSpecular[3]=0.0f;
    
    //cMaterialEmission[0]=0.0f;
    //cMaterialEmission[1]=0.0f;
    //cMaterialEmission[2]=0.0f;
    //cMaterialEmission[3]=1.0f;
}


void Graphics::DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation)
{
    
    float aPerpX = y1*z2 - y2*z1;
    float aPerpY = x1*z2 - z1*x2;
    float aPerpZ = x1*y2 - y1*x2;
    
    float aDist = aPerpX * aPerpX + aPerpY * aPerpY + aPerpZ * aPerpZ;
    
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        
        aPerpX /= aDist;
        aPerpY /= aDist;
        aPerpZ /= aDist;
    }
    
    DrawQuad(x1-pSize, y1, z1, x1+pSize, y1, z1,
             x2-pSize, y2, z2, x2+pSize, y2, z2);
    
    DrawQuad(x1-pSize, y1, z1, x1, y1+pSize, z1,
             x2-pSize, y2, z2, x2, y2+pSize, z2);
    
    DrawQuad(x1, y1, z1-pSize, x1, y1+pSize, z1,
             x2, y2, z2-pSize, x2, y2+pSize, z2);
    
    DrawQuad(x1, y1, z1-pSize, x1, y1, z1+pSize,
             x2, y2, z2-pSize, x2, y2, z2+pSize);
}




void Graphics::EnableDepth()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    //if(pClear)
    //{
    //    ClearDepth();
    //}
}

void Graphics::DisableDepth()
{
    glDisable(GL_DEPTH_TEST);
}

void Graphics::DepthDisable()
{
    DisableDepth();
}

void Graphics::DepthEnable()
{
    glEnable(GL_DEPTH_TEST);
}

void Graphics::DepthClear()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Graphics::DepthMaskFalse()
{
    glDepthMask(GL_FALSE);
}

void Graphics::DepthMaskTrue()
{
    glDepthMask(GL_TRUE);
}

void Graphics::ClearDepth(float pRed, float pGreen, float pBlue, float pAlpha)
{
    Clear(pRed, pGreen, pBlue, pAlpha);
    ClearDepth();
}

void Graphics::ClearDepth(float pRed, float pGreen, float pBlue)
{
    Clear(pRed, pGreen, pBlue, 1.0f);
    ClearDepth();
}

void Graphics::ClearDepth()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Graphics::Clear(float pRed, float pGreen, float pBlue, float pAlpha)
{
    glClearColor(pRed, pGreen, pBlue, pAlpha);
    Clear();
}

void Graphics::Clear(float pRed, float pGreen, float pBlue)
{
    Clear(pRed, pGreen, pBlue, 1.0f);
}

void Graphics::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::EnableCullFaces()
{
    glEnable(GL_CULL_FACE);
}

void Graphics::DisableCullFaces()
{
    glDisable(GL_CULL_FACE);
}

void Graphics::EnableLighting()
{
    glEnable(GL_LIGHTING);
}

void Graphics::DisableLighting()
{
    glDisable(GL_LIGHTING);
}

void Graphics::TextureSetWrap() {

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);


    glEnable(GL_TEXTURE_2D);

    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    ////glEnable( GL_TEXTURE_2D);

}

void Graphics::TextureSetClamp() {
#ifdef WIN_32_ENV
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
#else
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

#endif
    
}

void Graphics::TextureSetFilterMipMap() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Graphics::TextureSetFilterLinear() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Graphics::TextureSetFilterNearest() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Graphics::TextureSetModulate()
{
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}

void Graphics::TextureSetReplace()
{
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
}



void Graphics::ArrayNormals(float *pArray)
{
    glNormalPointer(GL_FLOAT,0,pArray);
}

void Graphics::ArrayCoords(float *pArray, int pDimensionality)
{
    glTexCoordPointer(pDimensionality, GL_FLOAT, 0, pArray);
}

void Graphics::ArrayVertices(float *pArray, int pDimensionality)
{
    glVertexPointer(pDimensionality, GL_FLOAT, 0, pArray);
}

void Graphics::ArrayColor(float *pArray, int pDimensionality)
{
    glColorPointer(pDimensionality, GL_FLOAT, 0, pArray);
}

void Graphics::ArrayCoords(float *pArray, int pStride, int pDimensionality)
{
    glTexCoordPointer(pDimensionality, GL_FLOAT, pStride, pArray);
}

void Graphics::ArrayVertices(float *pArray, int pStride, int pDimensionality)
{
    glVertexPointer(pDimensionality, GL_FLOAT,pStride,pArray);
}

void Graphics::ArrayColor(float *pArray, int pStride, int pDimensionality)
{
    glColorPointer(pDimensionality, GL_FLOAT, pStride, pArray);
}



void Graphics::EnableTextureCoordinateArray()
{
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Graphics::DisableTextureCoordinateArray()
{
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Graphics::EnableVertexArray()
{
    glEnableClientState(GL_VERTEX_ARRAY);
}

void Graphics::DisableVertexArray()
{
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Graphics::EnableNormalArray()
{
    glEnableClientState(GL_NORMAL_ARRAY);
}

void Graphics::DisableNormalArray()
{
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Graphics::EnableColorArray()
{
    glEnableClientState(GL_COLOR_ARRAY);
}

void Graphics::DisableColorArray()
{
    glDisableClientState(GL_COLOR_ARRAY);
}

int Graphics::TextureGenerate(unsigned int *pData, int pWidth, int pHeight)
{
    int aBindIndex=-1;
    
    glGenTextures(1, (GLuint*)(&aBindIndex));
    
    if(aBindIndex == -1)
    {
        Log("Error Binding Texture [%dx%d]\n", pWidth, pHeight);
    }
    else
    {
        TextureSetData(aBindIndex, pData, pWidth, pHeight);
    }
    
    return aBindIndex;
}

void Graphics::TextureDelete(int pIndex)
{
    if(pIndex > -1)
    {
        glDeleteTextures(1, (GLuint*)(&(pIndex)));
        glFlush();
    }
}

bool Graphics::TextureValid(FTexture *pTexture)
{
    bool aResult = false;
    
    if(pTexture)
    {
        if(pTexture->IsValid())
        {
            aResult = true;
        }
    }
    
    return aResult;
}

void Graphics::TextureSetData(int pIndex, unsigned int *pData, int pWidth, int pHeight) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    TextureBind(pIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
}

void Graphics::TextureBind(int pIndex)
{
    glBindTexture(GL_TEXTURE_2D, pIndex);
}

void Graphics::TextureBind(FTexture *pTexture)
{
    if(pTexture)
    {
        TextureBind(pTexture->mBindIndex);
    }
}

void Graphics::TextureEnable()
{
    glEnable(GL_TEXTURE_2D);
}

void Graphics::TextureDisable()
{
    glDisable(GL_TEXTURE_2D);
}





void Graphics::BlendEnable() {
    glEnable(GL_BLEND);
}

void Graphics::BlendDisable()
{
    glDisable(GL_BLEND);
}

void Graphics::BlendSetAlpha()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::BlendSetAdditive()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void Graphics::BlendSetPremultiplied()
{
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::BlendSetSubtract()
{
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::BlendSetInvert1()
{
    //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::BlendSetInvert2()
{
    //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
}

void Graphics::BlendSetGhost1()
{
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
}

void Graphics::BlendSetGhost2()
{
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE);
}

void Graphics::BlendSetType(int pType)
{
    if(pType == BLEND_TYPE_STANDARD)BlendSetAlpha();
    if(pType == BLEND_TYPE_ADDITIVE)BlendSetAdditive();
    if(pType == BLEND_TYPE_PREMULTIPLIED)BlendSetPremultiplied();
    if(pType == BLEND_TYPE_INVERT_1)BlendSetInvert1();
    if(pType == BLEND_TYPE_INVERT_2)BlendSetInvert2();
    if(pType == BLEND_TYPE_GHOST_1)BlendSetGhost1();
    if(pType == BLEND_TYPE_GHOST_2)BlendSetGhost2();
}

void Graphics::MonocolorEnable()
{
    MonocolorEnable(FColor(1.0f,1.0f,1.0f,1.0f));
}

void Graphics::MonocolorEnable(float pRed, float pGreen, float pBlue)
{
    MonocolorEnable(FColor(pRed,pBlue,pGreen,1.0f));
}

void Graphics::MonocolorEnable(FColor pColor)
{
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_COLOR,(GLfloat*)&pColor);
}

void Graphics::MonocolorDisable()
{
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}


void Graphics::ClipEnable()
{
    if (cClipEnabled == false) {
        cClipEnabled = true;
        //glEnable(GL_SCISSOR_TEST);
        glEnable(GL_CLIP_PLANE0);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);
        glEnable(GL_CLIP_PLANE3);
    }
}

void Graphics::ClipDisable()
{
    //glDisable(GL_SCISSOR_TEST);
    if (cClipEnabled == true) {
        cClipEnabled = false;

        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);
        glDisable(GL_CLIP_PLANE3);
    }
}


//#if defined(TEST_1) || defined(TEST_2)
// do stuff
//#endif

#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)

static double cClipPlane[4][4] = { { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f, 512.0f }, { 0.0f, -1.0f, 0.0f, 512.0f } };

void Graphics::Clip(float pX, float pY, float pWidth, float pHeight) {
    cClipPlane[0][0] = 0.0f;
    cClipPlane[0][1] = 1.0f;
    cClipPlane[0][2] = 0.0f;
    cClipPlane[0][3] = 0.0f;

    cClipPlane[1][0] = 1.0f;
    cClipPlane[1][1] = 0.0f;
    cClipPlane[1][2] = 0.0f;
    cClipPlane[1][3] = 0.0f;

    cClipPlane[2][0] = -1.0f;
    cClipPlane[2][1] = 0.0f;
    cClipPlane[2][2] = 0.0f;
    cClipPlane[2][3] = pWidth;
    
    cClipPlane[3][0] = 0.0f;
    cClipPlane[3][1] = -1.0f;
    cClipPlane[3][2] = 0.0f;
    cClipPlane[3][3] = pHeight;
    
    glClipPlane(GL_CLIP_PLANE0, cClipPlane[0]);
    glClipPlane(GL_CLIP_PLANE1, cClipPlane[1]);
    glClipPlane(GL_CLIP_PLANE2, cClipPlane[2]);
    glClipPlane(GL_CLIP_PLANE3, cClipPlane[3]);
}

#else

static float cClipPlane[4][4] = {{0.0f, 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f, 512.0f}, {0.0f, -1.0f, 0.0f, 512.0f}};

void Graphics::Clip(float pX, float pY, float pWidth, float pHeight)
{
    //glScissor(pX, gDeviceHeight - (pY + pHeight), pWidth, pHeight);

    //cClipRect[0] = pX;
    //cClipRect[1] = pY;
    //cClipRect[2] = pWidth;
    //cClipRect[3] = pHeight;

    cClipPlane[0][0] = 0.0f;
    cClipPlane[0][1] = 1.0f;
    cClipPlane[0][2] = 0.0f;
    cClipPlane[0][3] = 0.0f;

    cClipPlane[1][0] = 1.0f;
    cClipPlane[1][1] = 0.0f;
    cClipPlane[1][2] = 0.0f;
    cClipPlane[1][3] = 0.0f;

    cClipPlane[2][0] = -1.0f;
    cClipPlane[2][1] = 0.0f;
    cClipPlane[2][2] = 0.0f;
    cClipPlane[2][3] = pWidth;

    cClipPlane[3][0] = 0.0f;
    cClipPlane[3][1] = -1.0f;
    cClipPlane[3][2] = 0.0f;
    cClipPlane[3][3] = pHeight;

    glClipPlanef(GL_CLIP_PLANE0, cClipPlane[0]);
    glClipPlanef(GL_CLIP_PLANE1, cClipPlane[1]);
    glClipPlanef(GL_CLIP_PLANE2, cClipPlane[2]);
    glClipPlanef(GL_CLIP_PLANE3, cClipPlane[3]);
}

#endif

void Graphics::ClipSetAppFrame(float pX, float pY, float pWidth, float pHeight) {
    cClipRectBase[0] = pX;
    cClipRectBase[1] = pY;
    cClipRectBase[2] = pWidth;
    cClipRectBase[3] = pHeight;
}

void Graphics::ViewportSet(float pX, float pY, float pWidth, float pHeight) {
    glViewport(pX, pY, pWidth, pHeight);
}

void Graphics::DrawModelEfficientSetup(float *pXYZ, float *pUVW, float *pNormal, FTexture *pTexture) {
    EnableVertexArray();
    ArrayVertices(pXYZ);

    if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
    else {TextureDisable();DisableTextureCoordinateArray();}
    
    if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
    else {DisableNormalArray();}
}

void Graphics::DrawModelIndexedEfficientSetup(float *pXYZ, float *pUVW, float *pNormal, FTexture *pTexture)
{
    
    EnableVertexArray();
    ArrayVertices(pXYZ);
    
    if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
    else {TextureDisable();DisableTextureCoordinateArray();}
    
    if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
    else {DisableNormalArray();}
}

void Graphics::DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned int *pIndex, int pCount, FTexture *pTexture)
{
    if(pXYZ)
    {
        EnableVertexArray();
        ArrayVertices(pXYZ);
        
        if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
        else {TextureDisable();DisableTextureCoordinateArray();}
        
        if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
        else {DisableNormalArray();}
        
        if(pIndex){DrawTriangles(pIndex, pCount);}
        else{DrawTriangles(pCount);}
    }
}

void Graphics::DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned short *pIndex, int pCount, FTexture *pTexture)
{
    if(pXYZ)
    {
        EnableVertexArray();
        ArrayVertices(pXYZ);

        if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
        else {TextureDisable();DisableTextureCoordinateArray();}
        
        if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
        else {DisableNormalArray();}
        
        if(pIndex){DrawTriangles(pIndex, pCount);}
        else{DrawTriangles(pCount);}
    }
}

void Graphics::DrawModelIndexed(float *pXYZ, float *pUVW, float *pNormal, unsigned short *pIndex, FTexture *pTexture, int pStartIndex, int pEndIndex)
{
    DrawModelIndexed(pXYZ, pUVW, pNormal, pIndex + pStartIndex, (pEndIndex - pStartIndex) + 1, pTexture);
}

void Graphics::DrawModel(float *pXYZ, float *pUVW, float *pNormal, int pCount, FTexture *pTexture)
{
    if(pXYZ)
    {
        EnableVertexArray();
        ArrayVertices(pXYZ);
        
        if(TextureValid(pTexture) && (pUVW != 0)){TextureEnable();EnableTextureCoordinateArray();TextureBind(pTexture);ArrayCoords(pUVW);}
        else {TextureDisable();DisableTextureCoordinateArray();}
        
        if(pNormal != 0){EnableNormalArray();ArrayNormals(pNormal);}
        else {DisableNormalArray();}
        
        DrawTriangles(pCount);
    }
}

void Graphics::DrawTriangles(int pCount, float *pXYZ, float *pUVW, float *pNormal){DrawTrianglePrimitive(GL_TRIANGLES, pCount, pXYZ, pUVW, pNormal);}
void Graphics::DrawTriangles(int pCount){DrawTrianglePrimitive(GL_TRIANGLES, pCount);}
void Graphics::DrawTriangleStrips(int pCount){DrawTrianglePrimitive(GL_TRIANGLE_STRIP, pCount);}
void Graphics::DrawTriangleFans(int pCount){DrawTrianglePrimitive(GL_TRIANGLE_FAN, pCount);}
void Graphics::DrawTriangles(unsigned int *pIndexList, int pCount){DrawTrianglePrimitive(GL_TRIANGLES, pIndexList, pCount);}
void Graphics::DrawTriangles(unsigned short *pIndexList, int pCount){DrawTrianglePrimitive(GL_TRIANGLES, pIndexList, pCount);}

void Graphics::DrawTrianglePrimitive(unsigned int pType, int pCount, float *pXYZ, float *pUVW, float *pNormal)
{
    DrawTrianglePrimitive(pType,pCount, pXYZ, pUVW, pNormal, 3, 2);
}

void Graphics::DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount, float *pXYZ, float *pUVW, float *pNormal)
{
    DrawTrianglePrimitive(pType, pIndexList, pCount, pXYZ, pUVW, pNormal, 3, 2);
}

void Graphics::DrawTrianglePrimitive(unsigned int pType, int pCount, float *pXYZ, float *pUVW, float *pNormal, int pXYZDimensinality, int pUVWDinonsionality)
{
    if(pXYZ)ArrayVertices(pXYZ, pXYZDimensinality);
    else ArrayVertices(0);
    
    if(pUVW)ArrayCoords(pUVW, pUVWDinonsionality);
    else ArrayCoords(0);
    
    if(pNormal)ArrayNormals(pNormal);
    else ArrayNormals(0);
    
    DrawTrianglePrimitive(pType,pCount);
}

void Graphics::DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount, float *pXYZ, float *pUVW, float *pNormal, int pXYZDimensinality, int pUVWDinonsionality)
{
    if(pXYZ)ArrayVertices(pXYZ, pXYZDimensinality);
    else ArrayVertices(0);
    
    if(pUVW)ArrayCoords(pUVW, pUVWDinonsionality);
    else ArrayCoords(0);
    
    if(pNormal)ArrayNormals(pNormal);
    else ArrayNormals(0);
    
    DrawTrianglePrimitive(pType, pIndexList, pCount);
}

void Graphics::DrawTrianglePrimitive(unsigned int pType, unsigned int *pIndexList, int pCount) {
    glDrawElements(pType, pCount, GFX_MODEL_INDEX_GL_TYPE, pIndexList);
}

void Graphics::DrawTrianglePrimitive(unsigned int pType, unsigned short *pIndexList, int pCount) {
    glDrawElements(pType, pCount, GFX_MODEL_INDEX_GL_TYPE, pIndexList);
}

void Graphics::DrawTrianglePrimitive(unsigned int pType, int pCount) {
    glDrawArrays(pType, 0, pCount);
}

void Graphics::Rotate(float pDegreesX, float pDegreesY, float pDegreesZ) {
    RotateX(pDegreesX);
    RotateY(pDegreesY);
    RotateZ(pDegreesZ);
}

void Graphics::Rotate(float pDegrees, float pAxisX, float pAxisY, float pAxisZ) {
    if (pDegrees != 0) {
        glRotatef(pDegrees, pAxisX, pAxisY, pAxisZ);
    }
}

void Graphics::Translate(float x, float y, float z) {
    glTranslatef(x,y,z);
}

void Graphics::Scale(float x, float y, float z) {
    glScalef(x,y,z);
}

void Graphics::SetShadeFlat() {
    glShadeModel(GL_FLAT);
}

void Graphics::SetShadeSmooth() {
    glShadeModel(GL_SMOOTH);
}

void Graphics::Go3D() {
    MatrixGoProjection();
    MatrixGoModelView();
    
    glOrthof(0, gDeviceWidth, gDeviceHeight, 0, 1024.0f, -1024.0f);
    
    EnableDepth();
    ClearDepth();
    EnableCullFaces();
    SetShadeSmooth();
    //SetShadeFlat();
}


void Graphics::MatrixPush()
{
    glPushMatrix();
}

void Graphics::MatrixPop()
{
    glPopMatrix();
}

void Graphics::SetMatrixProjection(FMatrix &pMatrix) {
    MatrixGoProjection();
    glLoadMatrixf(pMatrix.m);
}

void Graphics::SetMatrixModelView(FMatrix &pMatrix) {
    MatrixGoModelView();
    glLoadMatrixf(pMatrix.m);
}

void Graphics::SetMatrix(FMatrix &pMatrix) {
    glLoadMatrixf(pMatrix.m);
}

void Graphics::ResetMatrixProjection() {
    MatrixGoProjection();
    MatrixLoadIdentity();
}

void Graphics::ResetMatrixModelView() {
    MatrixGoModelView();
    MatrixLoadIdentity();
}

FMatrix Graphics::GetMatrixProjection() {
    FMatrix aResult;
    glGetFloatv(GL_PROJECTION_MATRIX, aResult.m);
    return aResult;
}

FMatrix Graphics::GetMatrixModelView() {
    FMatrix aResult;
    glGetFloatv(GL_MODELVIEW_MATRIX, aResult.m);
    return aResult;
}

void Graphics::MatrixGoProjection(bool pLoadIdentity) {
    glMatrixMode(GL_PROJECTION);
    if(pLoadIdentity)MatrixLoadIdentity();
}

void Graphics::MatrixGoModelView(bool pLoadIdentity) {
    glMatrixMode(GL_MODELVIEW);
    if(pLoadIdentity)MatrixLoadIdentity();
}

void Graphics::MatrixGoProjection() {
    glMatrixMode(GL_PROJECTION);
}

void Graphics::MatrixGoModelView() {
    glMatrixMode(GL_MODELVIEW);
}

void Graphics::MatrixLoadIdentity() {
    glLoadIdentity();
}

void Graphics::Go2D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    SetShadeFlat();
    glOrthof(0, gDeviceWidth, gDeviceHeight, 0, 1024.0f, -1024.0f);
    DisableCullFaces();
    DisableDepth();
    DisableLighting();
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Graphics::CullFacesEnable() {
    glEnable(GL_CULL_FACE);
}

void Graphics::CullFacesDisable() {
    glDisable(GL_CULL_FACE);
}

void Graphics::CullFacesSetFront() {
    glCullFace(GL_FRONT);
}

void Graphics::CullFacesSetBack() {
    glCullFace(GL_BACK);
}

void Graphics::TestBlend(int pType1, int pType2) {
    unsigned int aBlend1 = GL_SRC_ALPHA;
    unsigned int aBlend2 = GL_ONE_MINUS_SRC_ALPHA;
    
    for (int i=0;i<2;i++) {
        unsigned int aIndex;
        int aCheck;
        if (i == 0) {
            aIndex = aBlend1;
            aCheck = pType1;
        } else {
            aIndex = aBlend2;
            aCheck = pType2;
        }

        if (aCheck == 0 ) aIndex = GL_ZERO;
        if (aCheck == 1 ) aIndex = GL_ONE;
        if (aCheck == 2 ) aIndex = GL_SRC_COLOR;
        if (aCheck == 3 ) aIndex = GL_ONE_MINUS_SRC_COLOR;
        if (aCheck == 4 ) aIndex = GL_DST_ALPHA;
        if (aCheck == 5 ) aIndex = GL_ONE_MINUS_DST_ALPHA;
        if (aCheck == 6 ) aIndex = GL_DST_COLOR;
        if (aCheck == 7 ) aIndex = GL_ONE_MINUS_DST_COLOR;
        if (aCheck == 8 ) aIndex = GL_SRC_ALPHA_SATURATE;

        if (i == 0) { aBlend1 = aIndex; }
        else { aBlend2 = aIndex; }
    }
    glBlendFunc(aBlend1, aBlend2);
}

void Graphics::RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture)
{
    //RenderQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, 0, 0, 1, 0, 0, 1, 1, 1, pBindIndex);
    RenderQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, 0, 0, 0, 1, 1, 0, 1, 1, pTexture);
}


static float cRenderQuadBufferXY[9];
static float cRenderQuadBufferUV[9];

void Graphics::RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture) {
    cRenderQuadBufferXY[0] = pX1;
    cRenderQuadBufferXY[1] = pY1;
    
    cRenderQuadBufferXY[2] = pX2;
    cRenderQuadBufferXY[3] = pY2;
    
    cRenderQuadBufferXY[4] = pX3;
    cRenderQuadBufferXY[5] = pY3;
    
    cRenderQuadBufferXY[6] = pX4;
    cRenderQuadBufferXY[7] = pY4;

    cRenderQuadBufferUV[0] = pU1;
    cRenderQuadBufferUV[1] = pV1;
    
    cRenderQuadBufferUV[2] = pU2;
    cRenderQuadBufferUV[3] = pV2;
    
    cRenderQuadBufferUV[4] = pU3;
    cRenderQuadBufferUV[5] = pV3;
    
    cRenderQuadBufferUV[6] = pU4;
    cRenderQuadBufferUV[7] = pV4;
    
    DrawSprite(cRenderQuadBufferXY, cRenderQuadBufferUV, pTexture);
}

//void Graphics::RenderQuadPushed(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4,
//float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, //float pV4, FTexture *pTexture, float pPush)

void Graphics::RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale)
{
    float aRangeX = (pX2 - pX1);
    float aRangeY = (pY3 - pY1);
    
    float aCenterX = pX1 + aRangeX / 2.0f;
    float aCenterY = pY1 + aRangeY / 2.0f;
    
    aRangeX *= pScale;
    aRangeY *= pScale;
    
    aRangeX /= 2.0f;
    aRangeY /= 2.0f;
    
    pX1 = aCenterX - aRangeX;
    pX2 = aCenterX + aRangeX;
    
    pY1 = aCenterY - aRangeY;
    pY3 = aCenterY + aRangeY;
    
    
    pX3 = pX1;
    pX4 = pX2;
    pY2 = pY1;
    pY4 = pY3;
    
    
    //pX1 -= pPush;
    //pX2 += pPush;
    
    cRenderQuadBufferXY[0] = pX1;
    cRenderQuadBufferXY[1] = pY1;
    
    cRenderQuadBufferXY[2] = pX2;
    cRenderQuadBufferXY[3] = pY2;
    
    cRenderQuadBufferXY[4] = pX3;
    cRenderQuadBufferXY[5] = pY3;
    
    cRenderQuadBufferXY[6] = pX4;
    cRenderQuadBufferXY[7] = pY4;
    
    
    
    cRenderQuadBufferUV[0] = pU1;
    cRenderQuadBufferUV[1] = pV1;
    
    cRenderQuadBufferUV[2] = pU2;
    cRenderQuadBufferUV[3] = pV2;
    
    cRenderQuadBufferUV[4] = pU3;
    cRenderQuadBufferUV[5] = pV3;
    
    cRenderQuadBufferUV[6] = pU4;
    cRenderQuadBufferUV[7] = pV4;
    
    DrawSprite(cRenderQuadBufferXY, cRenderQuadBufferUV, pTexture);
}


void Graphics::RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale, float pCenterX, float pCenterY)
{
    pX1 = pCenterX - (pCenterX - pX1) * pScale;
    pX2 = pCenterX - (pX2 - pCenterX) * pScale;
    
    pY1 = pCenterY - (pCenterY - pY1) * pScale;
    pY3 = pCenterY - (pY2 - pCenterY) * pScale;
    
    
    pX3 = pX1;
    pX4 = pX2;
    pY2 = pY1;
    pY4 = pY3;
    
    //pX1 -= pPush;
    //pX2 += pPush;
    
    cRenderQuadBufferXY[0] = pX1;
    cRenderQuadBufferXY[1] = pY1;
    
    cRenderQuadBufferXY[2] = pX2;
    cRenderQuadBufferXY[3] = pY2;
    
    cRenderQuadBufferXY[4] = pX3;
    cRenderQuadBufferXY[5] = pY3;
    
    cRenderQuadBufferXY[6] = pX4;
    cRenderQuadBufferXY[7] = pY4;
    
    cRenderQuadBufferUV[0] = pU1;
    cRenderQuadBufferUV[1] = pV1;
    
    cRenderQuadBufferUV[2] = pU2;
    cRenderQuadBufferUV[3] = pV2;
    
    cRenderQuadBufferUV[4] = pU3;
    cRenderQuadBufferUV[5] = pV3;
    
    cRenderQuadBufferUV[6] = pU4;
    cRenderQuadBufferUV[7] = pV4;
    
    DrawSprite(cRenderQuadBufferXY, cRenderQuadBufferUV, pTexture);
}

void Graphics::RenderTriangle(float pX1, float pY1, float pZ1, float pX2, float pY2, float pZ2, float pX3, float pY3, float pZ3)
{
    cRenderQuadBufferXY[0] = pX1;
    cRenderQuadBufferXY[1] = pY1;
    cRenderQuadBufferXY[2] = pZ1;

    cRenderQuadBufferXY[3] = pX2;
    cRenderQuadBufferXY[4] = pY2;
    cRenderQuadBufferXY[5] = pZ2;

    cRenderQuadBufferXY[6] = pX3;
    cRenderQuadBufferXY[7] = pY3;
    cRenderQuadBufferXY[8] = pZ3;


    ArrayVertices(cRenderQuadBufferXY, 3);

    DisableTextureCoordinateArray();
    TextureDisable();

    DrawTriangles(3);

    EnableTextureCoordinateArray();
    TextureEnable();

}

void Graphics::RenderTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
{
    RenderTriangle(pX1, pY1, 0.0f, pX2, pY2, 0.0f, pX3, pY3, 0.0f);
}


void Graphics::DrawSprite(float *pVerts, float *pCoords, FTexture *pTexture)
{
    ArrayVertices(pVerts, 2);
    ArrayCoords(pCoords, 2);
    
    if(pTexture)
    {
        if(pTexture->mBindIndex != cBindIndex)
        {
            TextureEnable();
            TextureBind(pTexture);
        }
        if(pTexture->mBindIndex != -1)DrawTriangleStrips(4);
    }
}

void Graphics::DrawSprite(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pVerts, float *pCoords, FTexture *pTexture)
{
    TextureEnable();
    //if(pBindIndex != cBindIndex)
    //{
    //BindTexture(pBindIndex);
    //cBindIndex=pBindIndex;
    //}
    
    //ArrayVertices(pVerts, 2);
    //ArrayCoords(pCoords, 2);
    
    
    if(pScaleX != 1.0f || pScaleY != 1.0f || pScaleZ != 1.0f || pRotation != 0)
    {
        MatrixPush();
        
        Translate(pX, pY);
        
        Scale(pScaleX,pScaleY,pScaleZ);
        RotateZ(pRotation);
        
        DrawSprite(pVerts, pCoords, pTexture);
        
        MatrixPop();
    }
    else
    {
        MatrixPush();
        Translate(pX, pY);
        
        DrawSprite(pVerts, pCoords, pTexture);
        
        MatrixPop();
    }
}

void Graphics::DrawSpriteTriangle(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pVerts, float *pCoords, FTexture *pTexture) {
    TextureEnable();
    if (pScaleX != 1.0f || pScaleY != 1.0f || pScaleZ != 1.0f || pRotation != 0) {
        MatrixPush();
        Translate(pX, pY);
        Scale(pScaleX,pScaleY,pScaleZ);
        RotateZ(pRotation);
        DrawSpriteTriangle(pVerts, pCoords, pTexture);
        MatrixPop();
    } else {
        MatrixPush();
        Translate(pX, pY);
        DrawSpriteTriangle(pVerts, pCoords, pTexture);
        MatrixPop();
    }
}

void Graphics::DrawSpriteTriangle(float *pVerts, float *pCoords, FTexture *pTexture)
{
    ArrayVertices(pVerts, 2);
    ArrayCoords(pCoords, 2);
    
    if(pTexture)
    {
        if(pTexture->mBindIndex != cBindIndex)
        {
            TextureEnable();
            TextureBind(pTexture);
            
        }
        
        if(pTexture->mBindIndex != -1)
        {
            DrawTriangleStrips(3);
        }
        
    }
}

void Graphics::DrawCube(float pX, float pY, float pZ, float pSize)
{
    
    /*
     static float aXYZ[72]={-0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0.5};
     static float aUVW[72]={1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00};
     static float aNormal[72]={0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000};
     static unsigned short aIndex[36]={0,1,2,2,3,0,4,5,6,6,7,4,8,9,10,10,11,8,12,13,14,14,15,12,16,17,18,18,19,16,20,21,22,22,23,20};

     MatrixPush();
     Translate(pX, pY, pZ);
     Scale(pSize);

     ArrayVertices(aXYZ);
     ArrayCoords(aUVW);
     ArrayNormals(aNormal);
     DrawTriangles(aIndex, 36);

     MatrixPop();
     
     */
    
    DrawCube(pSize);
}

void Graphics::DrawCube(float pSize)
{
    
    static float aXYZ[72]={-0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,-0.5,-0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0.5};
    static float aUVW[72]={1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00,0.00,1.00,0.00,1.00,1.00,0.00,1.00,0.00,0.00,0.00,0.00,0.00};
    static float aNormal[72]={0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,0.000000,-0.000000,1.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000};
    
    static unsigned short aIndex[36]={0,1,2,2,3,0,4,5,6,6,7,4,8,9,10,10,11,8,12,13,14,14,15,12,16,17,18,18,19,16,20,21,22,22,23,20};
    
    
    ArrayVertices(aXYZ);
    ArrayCoords(aUVW);
    ArrayNormals(aNormal);
    DrawTriangles(aIndex, 36);
}
//Lighting Stuff!

void Graphics::ApplyLightingBasic()
{
    for(int i=0;i<GRAPHICS_LIGHT_COUNT;i++)
    {
        unsigned int aLight = gLight[i];
        if(cLightEnabled[i])
        {
            glEnable(aLight);
            glLightfv(aLight, GL_POSITION, cLightPosition[i]);
            glLightfv(aLight, GL_AMBIENT, cLightAmbient[i]);
            glLightfv(aLight, GL_DIFFUSE, cLightDiffuse[i]);
        }
        else
        {
            glDisable(aLight);
        }
    }
}

void Graphics::ApplyLighting()
{
    
    for(int i=0;i<GRAPHICS_LIGHT_COUNT;i++)
    {
        unsigned int aLight = gLight[i];
        if(cLightEnabled[i])
        {
            glEnable(aLight);
            
            glLightfv(aLight, GL_POSITION, cLightPosition[i]);
            //glLightfv(aLight, GL_SPOT_DIRECTION, cLightSpotDirection[i]);
            
            glLightfv(aLight, GL_AMBIENT, cLightAmbient[i]);
            glLightfv(aLight, GL_DIFFUSE, cLightDiffuse[i]);
            //glLightfv(aLight, GL_SPECULAR, cLightSpecular[i]);
            
            //glLightf(aLight, GL_CONSTANT_ATTENUATION, cLightConstantAttenuation[i]);
            //glLightf(aLight, GL_LINEAR_ATTENUATION, cLightLinearAttenuation[i]);
            //glLightf(aLight, GL_QUADRATIC_ATTENUATION, cLightQuadraticAttenuation[i]);
            
            //glLightf(aLight,GL_SPOT_CUTOFF,cLightSpotCutoff[i]);
            //glLightf(aLight,GL_SPOT_EXPONENT,cLightSpotExponent[i]);
            
        }
        else
        {
            glDisable(aLight);
        }
    }
}



void Graphics::LightSetAmbient(int pLightIndex, float pRed, float pGreen, float pBlue, float pAlpha)
{
    cLightAmbient[pLightIndex][0]=pRed;
    cLightAmbient[pLightIndex][1]=pGreen;
    cLightAmbient[pLightIndex][2]=pBlue;
    cLightAmbient[pLightIndex][3]=pAlpha;
}
void Graphics::LightSetDiffuse(int pLightIndex, float pRed, float pGreen, float pBlue, float pAlpha)
{
    cLightDiffuse[pLightIndex][0]=pRed;
    cLightDiffuse[pLightIndex][1]=pGreen;
    cLightDiffuse[pLightIndex][2]=pBlue;
    cLightDiffuse[pLightIndex][3]=pAlpha;
}

void Graphics::LightSetSpecular(int pLightIndex, float pRed, float pGreen, float pBlue, float pAlpha)
{    
    cLightSpecular[pLightIndex][0]=pRed;
    cLightSpecular[pLightIndex][1]=pGreen;
    cLightSpecular[pLightIndex][2]=pBlue;
    cLightSpecular[pLightIndex][3]=pAlpha;
}

void Graphics::LightSetPos(int pLightIndex,float x, float y)
{
    cLightPosition[pLightIndex][0]=x;
    cLightPosition[pLightIndex][1]=y;
}

void Graphics::LightSetPos(int pLightIndex,float x, float y, float z)
{
    cLightPosition[pLightIndex][0]=x;
    cLightPosition[pLightIndex][1]=y;
    cLightPosition[pLightIndex][2]=z;
}

void Graphics::LightSetPos(int pLightIndex,float x, float y, float z, float w)
{
    cLightPosition[pLightIndex][0]=x;
    cLightPosition[pLightIndex][1]=y;
    cLightPosition[pLightIndex][2]=z;
    cLightPosition[pLightIndex][3]=w;
}



void Graphics::LightSetSpotDir(int pLightIndex,float x, float y)
{
    LightSetSpotDir(pLightIndex, x, y, 0.0f, 1.0f);
    //cLightSpotDirection[pLightIndex][0]=x;
    //cLightSpotDirection[pLightIndex][1]=y;
}


void Graphics::LightSetSpotDir(int pLightIndex,float x, float y, float z)
{
    LightSetSpotDir(pLightIndex, x, y, z, 1.0f);
    //cLightSpotDirection[pLightIndex][0]=x;
    //cLightSpotDirection[pLightIndex][1]=y;
    //cLightSpotDirection[pLightIndex][2]=z;
}


void Graphics::LightSetSpotDir(int pLightIndex,float x, float y, float z, float w)
{
    cLightSpotDirection[pLightIndex][0]=x;
    cLightSpotDirection[pLightIndex][1]=y;
    cLightSpotDirection[pLightIndex][2]=z;
    cLightSpotDirection[pLightIndex][3]=w;
}

void Graphics::LightSetAttenuationConstant(int pLightIndex, float pValue)
{
    cLightConstantAttenuation[pLightIndex]=pValue;
}

void Graphics::LightSetAttenuationLinear(int pLightIndex, float pValue)
{
    cLightLinearAttenuation[pLightIndex]=pValue;
}

void Graphics::LightSetAttenuationQuadratic(int pLightIndex, float pValue)
{
    cLightQuadraticAttenuation[pLightIndex]=pValue;
}

void Graphics::LightSetSpotCutoff(int pLightIndex, float pValue)
{
    if((pValue < 0.0f || pValue > 90.0f) && (pValue != 180.0f))
    {
        Log("Light Spot Cutoff %f Out Of Range [0 - 90, 180].\n", pValue);
        pValue = 180.0f;
    }
    cLightSpotCutoff[pLightIndex]=pValue;
}

void Graphics::LightSetSpotExponent(int pLightIndex, float pValue)
{
    if(pValue < 0 || pValue > 128.0f)
    {
        Log("Light Spot Exponent %f Out Of Range [0 - 128].\n", pValue);
        pValue = 0.0f;
    }
    cLightSpotExponent[pLightIndex]=pValue;
}

float Graphics::LightGetAttenuationConstant(int pLightIndex)
{
    return cLightConstantAttenuation[pLightIndex];
}

float Graphics::LightGetAttenuationLinear(int pLightIndex)
{
    return cLightLinearAttenuation[pLightIndex];
}

float Graphics::LightGetAttenuationQuadratic(int pLightIndex)
{
    return cLightQuadraticAttenuation[pLightIndex];
}

float Graphics::LightGetSpotCutoff(int pLightIndex)
{
    return cLightSpotCutoff[pLightIndex];
}

float Graphics::LightGetSpotExponent(int pLightIndex)
{
    return cLightSpotExponent[pLightIndex];
}

void Graphics::LightSetXYAngle(int pLightIndex,float pRotation)
{
    LightSetSpotDir(pLightIndex, Sin(pRotation), Cos(pRotation), cLightSpotDirection[pLightIndex][2], cLightSpotDirection[pLightIndex][3]);
}

void Graphics::LightSetZAngle(int pLightIndex,float pRotation)
{
    LightSetSpotDir(pLightIndex, cLightSpotDirection[pLightIndex][0], cLightSpotDirection[pLightIndex][1], Cos(pRotation), cLightSpotDirection[pLightIndex][3]);
}

void Graphics::LightSetEnabled(int pLightIndex, bool pState)
{
    cLightEnabled[pLightIndex]=pState;
}

float Graphics::LightGetColor(int pLight, int pType, int pChannel)
{
    if(pType==0)
    {
        return cLightAmbient[pLight][pChannel];
    }
    else if(pType==1)
    {
        return cLightDiffuse[pLight][pChannel];
    }
    else
    {
        return cLightSpecular[pLight][pChannel];
    }
}

void Graphics::LightFaceTarget(int pLightIndex, float pTargetX,float pTargetY, float pTargetZ)
{
    float aDiffX = pTargetX - cLightPosition[pLightIndex][0];
    float aDiffY = pTargetY - cLightPosition[pLightIndex][1];
    float aDiffZ = pTargetZ - cLightPosition[pLightIndex][2];
    
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY + aDiffZ * aDiffZ;
    
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        aDiffX /= aDist;
        aDiffY /= aDist;
        aDiffZ /= aDist;
    }
    else
    {
        aDiffX = 0.0f;
        aDiffY = 1.0f;
        aDiffZ = 0.0f;
    }
    
    cLightSpotDirection[pLightIndex][0] = aDiffX;
    cLightSpotDirection[pLightIndex][1] = aDiffY;
    cLightSpotDirection[pLightIndex][2] = aDiffZ;
}

void Graphics::LightFaceTargetAway(int pLightIndex, float pTargetX, float pTargetY, float pTargetZ)
{
    LightFaceTarget(pLightIndex, pTargetX, pTargetY, pTargetZ);
    
    cLightSpotDirection[pLightIndex][0] = -cLightSpotDirection[pLightIndex][0];
    cLightSpotDirection[pLightIndex][1] = -cLightSpotDirection[pLightIndex][1];
    cLightSpotDirection[pLightIndex][2] = -cLightSpotDirection[pLightIndex][2];
    
}

float Graphics::LightGetPos(int pLight, int pDimension)
{
    return cLightPosition[pLight][pDimension];
}

float Graphics::LightGetSpotDir(int pLight, int pDimension)
{
    return cLightSpotDirection[pLight][pDimension];
}

bool Graphics::LightGetEnabled(int pLight)
{
    return cLightEnabled[pLight];
}

void Graphics::MaterialEnable()
{
    glEnable(GL_COLOR_MATERIAL);
}

void Graphics::MaterialDisable()
{
    glDisable(GL_COLOR_MATERIAL);
    //MaterialSetDefault();
}

void Graphics::MaterialSetAmbient(float pRed, float pGreen, float pBlue, float pAlpha)
{
    cMaterialAmbient[0]=pRed;
    cMaterialAmbient[1]=pGreen;
    cMaterialAmbient[2]=pBlue;
    cMaterialAmbient[3]=pAlpha;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cMaterialAmbient);
}

void Graphics::MaterialSetDiffuse(float pRed, float pGreen, float pBlue, float pAlpha)
{
    cMaterialDiffuse[0]=pRed;
    cMaterialDiffuse[1]=pGreen;
    cMaterialDiffuse[2]=pBlue;
    cMaterialDiffuse[3]=pAlpha;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cMaterialDiffuse);
}

void Graphics::MaterialSetSpecular(float pRed, float pGreen, float pBlue, float pAlpha)
{
    cMaterialSpecular[0]=pRed;
    cMaterialSpecular[1]=pGreen;
    cMaterialSpecular[2]=pBlue;
    cMaterialSpecular[3]=pAlpha;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cMaterialSpecular);
}

void Graphics::MaterialSetEmission(float pRed, float pGreen, float pBlue, float pAlpha)
{
    cMaterialEmission[0]=pRed;
    cMaterialEmission[1]=pGreen;
    cMaterialEmission[2]=pBlue;
    cMaterialEmission[3]=pAlpha;
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, cMaterialEmission);
}


//0-128
void Graphics::MaterialSetShininess(float pShininess)
{
    if(pShininess < 0)
    {
        Log("Shininess %d Out Of Range (0 - 128).\n", (int)pShininess);
        pShininess=0;
    }
    if(pShininess > 128)
    {
        Log("Shininess %d Out Of Range (0 - 128).\n", (int)pShininess);
        pShininess = 128;
    }
    
    cMaterialShininess = pShininess;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pShininess);
}

float Graphics::MaterialGetAmbient(int pChannel)
{
    return cMaterialAmbient[pChannel];
}

float Graphics::MaterialGetDiffuse(int pChannel)
{
    return cMaterialDiffuse[pChannel];
}

float Graphics::MaterialGetSpecular(int pChannel)
{
    return cMaterialSpecular[pChannel];
}

float Graphics::MaterialGetEmission(int pChannel)
{
    return cMaterialEmission[pChannel];
}

float Graphics::MaterialGetColor(int pType, int pChannel)
{
    if(pType==0)return MaterialGetAmbient(pChannel);
    else if(pType==1)return MaterialGetDiffuse(pChannel);
    else if(pType==2)return MaterialGetSpecular(pChannel);
    else return MaterialGetEmission(pChannel);
}

float Graphics::MaterialGetShininess()
{
    return cMaterialShininess;
}


void Graphics::Ortho2D(float pLeft, float pRight, float pBottom, float pTop) {
    glOrthof(pLeft, pRight, pBottom, pTop, -1024.0f, 1024.0f);
}

void Graphics::Ortho2D() {
    Ortho2D(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
}

void Graphics::MatrixPerspective(float pFov) {
    float aAspect = ((float)gDeviceWidth) / ((float)gDeviceHeight);
    MatrixPerspective(pFov, aAspect, 0.1f, 255.0f);
}


void Graphics::MatrixPerspective(float pFov, float pAspect)
{
    MatrixPerspective(pFov, pAspect, 0.1f, 255.0f);
}

void Graphics::MatrixPerspective(float pFov, float pAspect, float pZNear, float pZFar)
{
    //gluPerspective(pFov, pAspect, pZNear, pZFar);
    
    FMatrix aMatrix = FMatrixCreatePerspective(pFov, pAspect, pZNear, pZFar);
    SetMatrix(aMatrix);
    
}

void Graphics::MatrixFrustum(float pLeft, float pRight, float pBottom, float pTop, float pNearZ, float pFarZ)
{
    FMatrix aMatrix = FMatrixCreateFrustum(pLeft, pRight, pBottom, pTop, pNearZ, pFarZ);
    SetMatrix(aMatrix);
}

void Graphics::MatrixLookAt(float pEyeX, float pEyeY, float pEyeZ,
                            float pCenterX, float pCenterY, float pCenterZ,
                            float pUpX, float pUpY, float pUpZ)
{
    FMatrix aMatrix = FMatrixCreateLookAt(pEyeX, pEyeY, pEyeZ, pCenterX, pCenterY, pCenterZ, pUpX, pUpY, pUpZ);
    SetMatrix(aMatrix);
}

void Graphics::FogEnable()
{
    glEnable(GL_FOG);
}

void Graphics::FogDisable()
{
    glDisable(GL_FOG);
}

void Graphics::FogInitialize()
{
#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)
    
#else
    glFogf(GL_FOG_DENSITY, cFogDensity);
    
    
    glFogf(GL_FOG_START, cFogStart);
    glFogf(GL_FOG_END, cFogEnd);
    
    glFogfv(GL_FOG_COLOR, cFogColor);
    
    glFogx(GL_FOG_MODE, GL_EXP2);
    glHint(GL_FOG_HINT, GL_NICEST);
#endif
}

void Graphics::FogSetStart(float pStart)
{
    cFogStart=pStart;
    glFogf(GL_FOG_START, cFogStart);
}

void Graphics::FogSetEnd(float pEnd)
{
    cFogEnd=pEnd;
    glFogf(GL_FOG_END, cFogEnd);
}

void Graphics::FogSetColor(float pRed, float pGreen, float pBlue, float pAlpha)
{
    cFogColor[0] = pRed;
    cFogColor[1] = pGreen;
    cFogColor[2] = pBlue;
    cFogColor[3] = pAlpha;
    
    glFogfv(GL_FOG_COLOR, cFogColor);
}

void Graphics::FogSetDensity(float pDensity)
{
#ifndef WIN_32_ENV
    cFogDensity = pDensity;
    glFogf(GL_FOG_DENSITY, cFogDensity);
#endif
}

void Graphics::FogSetLinear()
{
    
#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)
    
#else
    glFogx(GL_FOG_MODE, GL_LINEAR);
#endif
    
}

void Graphics::FogSetDiff()
{
#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)
    
#else
    glFogx(GL_FOG_MODE, GL_EXP);
#endif
}

void Graphics::FogSetDiffSquared()
{
#if defined(WIN_32_ENV) || defined(MAC_ENVIRONMENT)
    
#else
    glFogx(GL_FOG_MODE, GL_EXP2);
#endif
}

void Graphics::PrintLight()
{
    Log("\n");
    
    Log("////////////////////////\n");
    Log("//                    //\n");
    Log("//      Materials     //\n");
    Log("//                    //\n");
    Log("////////////////////////\n\n\n");
    
    
    Log("Graphics::MaterialSetAmbient(%f, %f, %f, %f);\n", MaterialGetAmbient(0), MaterialGetAmbient(1), MaterialGetAmbient(2), MaterialGetAmbient(3));
    Log("Graphics::MaterialSetDiffuse(%f, %f, %f, %f);\n", MaterialGetDiffuse(0), MaterialGetDiffuse(1), MaterialGetDiffuse(2), MaterialGetDiffuse(3));
    Log("Graphics::MaterialSetSpecular(%f, %f, %f, %f);\n", MaterialGetSpecular(0), MaterialGetSpecular(1), MaterialGetSpecular(2), MaterialGetSpecular(3));
    Log("Graphics::MaterialSetEmission(%f, %f, %f, %f);\n", MaterialGetEmission(0), MaterialGetEmission(1), MaterialGetEmission(2), MaterialGetEmission(3));
    Log("Graphics::MaterialSetShininess(%f);\n", MaterialGetShininess());
    
    Log("\n\n____Light____\n\n\n\n");
    /*
     Log("Light Enabled[");
     Log("%d, ", cLightEnabled[0]);
     Log("%d, ", cLightEnabled[1]);
     Log("%d, ", cLightEnabled[2]);
     Log("%d, ", cLightEnabled[3]);
     Log("%d, ", cLightEnabled[4]);
     Log("%d, ", cLightEnabled[5]);
     Log("%d, ", cLightEnabled[6]);
     Log("%d]\n", cLightEnabled[7]);
     */
    
    for(int i=0;i<GRAPHICS_LIGHT_COUNT;i++)
    {
        if(cLightEnabled[i] == true)
        {
            Log("Graphics::LightSetEnabled(%d, %s);\n", i, "true");
            Log("Graphics::LightSetAmbient(%d, %f, %f, %f, %f);\n", i, cLightAmbient[i][0], cLightAmbient[i][1], cLightAmbient[i][2], cLightAmbient[i][3]);
            Log("Graphics::LightSetDiffuse(%d, %f, %f, %f, %f);\n", i, cLightDiffuse[i][0], cLightDiffuse[i][1], cLightDiffuse[i][2], cLightDiffuse[i][3]);
            Log("Graphics::LightSetSpecular(%d, %f, %f, %f, %f);\n", i, cLightSpecular[i][0], cLightSpecular[i][1], cLightSpecular[i][2], cLightSpecular[i][3]);
            Log("Graphics::LightSetPos(%d, %f, %f, %f, %f);\n", i, cLightPosition[i][0], cLightPosition[i][1], cLightPosition[i][2], cLightPosition[i][3]);
            Log("Graphics::LightSetSpotDir(%d, %f, %f, %f, %f);\n", i, cLightSpotDirection[i][0], cLightSpotDirection[i][1], cLightSpotDirection[i][2], cLightSpotDirection[i][3]);
            Log("Graphics::LightSetSpotCutoff(%d, %f);\n", i, cLightSpotCutoff[i]);
            Log("Graphics::LightSetSpotExponent(%d, %f);\n", i, cLightSpotExponent[i]);
            
            if(i < (GRAPHICS_LIGHT_COUNT - 1))Log("\n");
        }
        else
        {
            Log("Graphics::LightSetEnabled(%d, %s);\n", i, "false");
        }
    }
    
    
    
    
    Log("\n\n\n\n");
    
}




static float cSphere12XYZ[267]={0.0,-0.0,1.0,-0.0,0.5,0.9,-0.2,0.4,0.9,0.0,-0.0,1.0,-0.4,0.2,0.9,0.0,-0.0,1.0,-0.5,-0.0,0.9,0.0,-0.0,1.0,-0.4,-0.2,0.9,0.0,-0.0,1.0,-0.2,-0.4,0.9,0.0,-0.0,1.0,-0.0,-0.5,0.9,0.0,-0.0,1.0,0.2,-0.4,0.9,0.0,-0.0,1.0,0.4,-0.2,0.9,0.0,-0.0,1.0,0.5,-0.0,0.9,0.0,-0.0,1.0,0.4,0.2,0.9,0.0,-0.0,1.0,0.2,0.4,0.9,0.0,-0.0,1.0,-0.0,0.5,0.9,-0.0,0.9,0.5,-0.4,0.8,0.5,-0.8,0.4,0.5,-0.9,-0.0,0.5,-0.8,-0.4,0.5,-0.4,-0.8,0.5,-0.0,-0.9,0.5,0.4,-0.8,0.5,0.8,-0.4,0.5,0.9,-0.0,0.5,0.8,0.4,0.5,0.4,0.7,0.5,-0.0,0.9,0.5,-0.0,1.0,-0.0,-0.5,0.9,-0.0,-0.9,0.5,-0.0,-1.0,-0.0,-0.0,-0.9,-0.5,-0.0,-0.5,-0.9,-0.0,-0.0,-1.0,-0.0,0.5,-0.9,-0.0,0.9,-0.5,-0.0,1.0,-0.0,-0.0,0.9,0.5,-0.0,0.5,0.9,-0.0,-0.0,1.0,-0.0,-0.0,0.9,-0.5,-0.4,0.8,-0.5,-0.8,0.4,-0.5,-0.9,-0.0,-0.5,-0.8,-0.4,-0.5,-0.4,-0.8,-0.5,-0.0,-0.9,-0.5,0.4,-0.8,-0.5,0.8,-0.4,-0.5,0.9,-0.0,-0.5,0.8,0.4,-0.5,0.4,0.7,-0.5,-0.0,0.9,-0.5,-0.0,0.5,-0.9,-0.2,0.4,-0.9,-0.4,0.2,-0.9,-0.5,-0.0,-0.9,-0.4,-0.2,-0.9,-0.2,-0.4,-0.9,-0.0,-0.5,-0.9,0.2,-0.4,-0.9,0.4,-0.2,-0.9,0.5,-0.0,-0.9,0.4,0.2,-0.9,0.2,0.4,-0.9,-0.0,0.5,-0.9,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0,0.0,-0.0,-1.0};

static float cSphere12UVW[267]={0.00,0.00,0.00,0.00,0.17,0.00,0.08,0.17,0.00,0.08,0.00,0.00,0.17,0.17,0.00,0.17,0.00,0.00,0.25,0.17,0.00,0.25,0.00,0.00,0.33,0.17,0.00,0.33,0.00,0.00,0.42,0.17,0.00,0.42,0.00,0.00,0.50,0.17,0.00,0.50,0.00,0.00,0.58,0.17,0.00,0.58,0.00,0.00,0.67,0.17,0.00,0.67,0.00,0.00,0.75,0.17,0.00,0.75,0.00,0.00,0.83,0.17,0.00,0.83,0.00,0.00,0.92,0.17,0.00,0.92,0.00,0.00,1.00,0.17,0.00,0.00,0.33,0.00,0.08,0.33,0.00,0.17,0.33,0.00,0.25,0.33,0.00,0.33,0.33,0.00,0.42,0.33,0.00,0.50,0.33,0.00,0.58,0.33,0.00,0.67,0.33,0.00,0.75,0.33,0.00,0.83,0.33,0.00,0.92,0.33,0.00,1.00,0.33,0.00,0.00,0.50,0.00,0.08,0.50,0.00,0.17,0.50,0.00,0.25,0.50,0.00,0.33,0.50,0.00,0.42,0.50,0.00,0.50,0.50,0.00,0.58,0.50,0.00,0.67,0.50,0.00,0.75,0.50,0.00,0.83,0.50,0.00,0.92,0.50,0.00,1.00,0.50,0.00,0.00,0.67,0.00,0.08,0.67,0.00,0.17,0.67,0.00,0.25,0.67,0.00,0.33,0.67,0.00,0.42,0.67,0.00,0.50,0.67,0.00,0.58,0.67,0.00,0.67,0.67,0.00,0.75,0.67,0.00,0.83,0.67,0.00,0.92,0.67,0.00,1.00,0.67,0.00,0.00,0.83,0.00,0.08,0.83,0.00,0.17,0.83,0.00,0.25,0.83,0.00,0.33,0.83,0.00,0.42,0.83,0.00,0.50,0.83,0.00,0.58,0.83,0.00,0.67,0.83,0.00,0.75,0.83,0.00,0.83,0.83,0.00,0.92,0.83,0.00,1.00,0.83,0.00,0.00,1.00,0.00,0.08,1.00,0.00,0.17,1.00,0.00,0.25,1.00,0.00,0.33,1.00,0.00,0.42,1.00,0.00,0.50,1.00,0.00,0.58,1.00,0.00,0.67,1.00,0.00,0.75,1.00,0.00,0.83,1.00,0.00,0.92,1.00,0.00};

static float cSphere12Normal[267]={-0.000000,-0.000000,1.000000,0.000000,0.530900,0.847435,-0.265450,0.459773,0.847435,-0.000000,-0.000000,1.000000,-0.459773,0.265450,0.847435,-0.000000,-0.000000,1.000000,-0.530900,0.000000,0.847435,-0.000000,-0.000000,1.000000,-0.459773,-0.265450,0.847435,-0.000000,-0.000000,1.000000,-0.265450,-0.459773,0.847435,-0.000000,-0.000000,1.000000,-0.000000,-0.530900,0.847435,-0.000000,-0.000000,1.000000,0.265450,-0.459773,0.847435,-0.000000,-0.000000,1.000000,0.459773,-0.265450,0.847435,-0.000000,-0.000000,1.000000,0.530900,-0.000000,0.847435,-0.000000,-0.000000,1.000000,0.459773,0.265450,0.847435,-0.000000,-0.000000,1.000000,0.265450,0.459773,0.847435,-0.000000,-0.000000,1.000000,0.000000,0.530900,0.847435,0.000000,0.875983,0.482342,-0.437992,0.758624,0.482342,-0.758624,0.437992,0.482342,-0.875983,0.000000,0.482342,-0.758624,-0.437991,0.482342,-0.437992,-0.758623,0.482342,-0.000000,-0.875983,0.482342,0.437991,-0.758624,0.482342,0.758623,-0.437992,0.482342,0.875983,-0.000001,0.482342,0.758624,0.437991,0.482342,0.437992,0.758623,0.482342,0.000000,0.875983,0.482342,0.000000,1.000000,-0.000000,-0.500000,0.866025,-0.000000,-0.866025,0.500000,-0.000000,-1.000000,0.000000,-0.000000,-0.866026,-0.500000,-0.000000,-0.500000,-0.866025,-0.000000,-0.000000,-1.000000,-0.000000,0.499999,-0.866026,-0.000000,0.866025,-0.500001,-0.000000,1.000000,-0.000001,-0.000000,0.866026,0.499999,-0.000000,0.500001,0.866025,-0.000000,0.000000,1.000000,-0.000000,0.000000,0.875983,-0.482342,-0.437992,0.758624,-0.482342,-0.758624,0.437992,-0.482342,-0.875983,0.000000,-0.482342,-0.758624,-0.437991,-0.482342,-0.437992,-0.758624,-0.482342,-0.000000,-0.875983,-0.482342,0.437991,-0.758624,-0.482342,0.758623,-0.437992,-0.482342,0.875983,-0.000001,-0.482342,0.758624,0.437991,-0.482342,0.437992,0.758623,-0.482342,0.000000,0.875983,-0.482342,0.000000,0.530900,-0.847435,-0.265450,0.459773,-0.847435,-0.459773,0.265450,-0.847435,-0.530900,0.000000,-0.847435,-0.459773,-0.265450,-0.847435,-0.265450,-0.459773,-0.847435,-0.000000,-0.530900,-0.847435,0.265450,-0.459773,-0.847435,0.459773,-0.265450,-0.847435,0.530900,-0.000000,-0.847435,0.459773,0.265450,-0.847435,0.265450,0.459773,-0.847435,0.000000,0.530900,-0.847435,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000,-0.000000,0.000000,-1.000000};

static unsigned short cSphere12Index[360]={0,1,2,3,2,4,5,4,6,7,6,8,9,8,10,11,10,12,13,12,14,15,14,16,17,16,18,19,18,20,21,20,22,23,22,24,1,25,26,1,26,2,2,26,27,2,27,4,4,27,28,4,28,6,6,28,29,6,29,8,8,29,30,8,30,10,10,30,31,10,31,12,12,31,32,12,32,14,14,32,33,14,33,16,16,33,34,16,34,18,18,34,35,18,35,20,20,35,36,20,36,22,22,36,37,22,37,24,25,38,39,25,39,26,26,39,40,26,40,27,27,40,41,27,41,28,28,41,42,28,42,29,29,42,43,29,43,30,30,43,44,30,44,31,31,44,45,31,45,32,32,45,46,32,46,33,33,46,47,33,47,34,34,47,48,34,48,35,35,48,49,35,49,36,36,49,50,36,50,37,38,51,52,38,52,39,39,52,53,39,53,40,40,53,54,40,54,41,41,54,55,41,55,42,42,55,56,42,56,43,43,56,57,43,57,44,44,57,58,44,58,45,45,58,59,45,59,46,46,59,60,46,60,47,47,60,61,47,61,48,48,61,62,48,62,49,49,62,63,49,63,50,51,64,65,51,65,52,52,65,66,52,66,53,53,66,67,53,67,54,54,67,68,54,68,55,55,68,69,55,69,56,56,69,70,56,70,57,57,70,71,57,71,58,58,71,72,58,72,59,59,72,73,59,73,60,60,73,74,60,74,61,61,74,75,61,75,62,62,75,76,62,76,63,77,65,64,78,66,65,79,67,66,80,68,67,81,69,68,82,70,69,83,71,70,84,72,71,85,73,72,86,74,73,87,75,74,88,76,75};

void Graphics::DrawSphere12(float x, float y, float z, float pRadius)
{
    MatrixPush();
    
    Translate(x, y, z);
    Scale(pRadius);
    
    DrawModelIndexed(cSphere12XYZ, cSphere12UVW, cSphere12Normal, cSphere12Index, 360, 0);
    
    MatrixPop();
}




/*
 void DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation){Graphics::DrawBox(x1, y1, z1, x2, y2, z2, pSize);}
 void DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){Graphics::DrawQuad(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);}



 void RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture){RenderQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, pTexture);}
 void RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture){RenderQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, pU1, pV1, pU2, pV2, pU3, pV3, pU4, pV4, pTexture);}

 void RenderQuadPushed(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pPush){RenderQuadPushed(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, pU1, pV1, pU2, pV2, pU3, pV3, pU4, pV4, pTexture, pPush);}

 void SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha){SetColorHex(pRed, pGreen, pBlue, pAlpha);}
 void SetColorHex(int pRed, int pGreen, int pBlue){SetColorHex(pRed, pGreen, pBlue);}
 void SetColorHex(int pAlpha){SetColorHex(pAlpha);}

 void SetColor(float pRed, float pGreen, float pBlue, float pAlpha){Graphics::SetColor(pRed, pGreen, pBlue, pAlpha);}
 void SetColor(float pRed, float pGreen, float pBlue){Graphics::SetColor(pRed, pGreen, pBlue);}
 void SetColor(float pIntensity){Graphics::SetColor(pIntensity);}
 void SetColor(){Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);}
 void SetColor(FColor pColor){Graphics::SetColor(pColor);}
 void SetColorSwatch(int pSwatchIndex){Graphics::SetColorSwatch(pSwatchIndex);}
 void SetColorSwatch(int pSwatchIndex, float pAlpha){Graphics::SetColorSwatch(pSwatchIndex, pAlpha);}

 void DrawQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4){Graphics::DrawQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4);}




 void OutlineRect(float pX, float pY, float pWidth, float pHeight, float pThickness){Graphics::OutlineRect(pX, pY, pWidth, pHeight, pThickness);}
 void OutlineRectInside(float pX, float pY, float pWidth, float pHeight, float pThickness){Graphics::OutlineRectInside(pX, pY, pWidth, pHeight, pThickness);}


 void DrawRect(float pX, float pY, float pWidth, float pHeight){Graphics::DrawRect(pX, pY, pWidth, pHeight);}
 void DrawLine(float pX1, float pY1, float pX2, float pY2){Graphics::DrawLine(pX1, pY1, pX2, pY2);}

 void DrawLine(float pX1, float pY1, float pX2, float pY2, float pThickness){Graphics::DrawLine(pX1, pY1, pX2, pY2, pThickness);}

 void DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength){Graphics::DrawArrow(pStartX, pStartY, pEndX, pEndY, pHeadLength);}

 void DrawPoint(float pX, float pY, float pSize){Graphics::DrawPoint(pX, pY, pSize);}


 //Deprecate these...
 void Go3D(){Graphics::Go3D();}
 void Go2D(){Graphics::Go2D();}

 void EnableDepth(){Graphics::EnableDepth();}
 void DisableDepth(){Graphics::DisableDepth();}

 void DepthEnable(){Graphics::DepthEnable();}
 void DepthDisable(){Graphics::DepthDisable();}

 void DepthClear(){Graphics::DepthClear();}
 void DepthMaskFalse(){Graphics::DepthMaskFalse();}
 void DepthMaskTrue(){Graphics::DepthMaskTrue();}

 void ClearDepth(float pRed, float pGreen, float pBlue, float pAlpha){Graphics::ClearDepth(pRed, pGreen, pBlue, pAlpha);}
 void ClearDepth(float pRed, float pGreen, float pBlue){Graphics::ClearDepth(pRed, pGreen, pBlue);}
 void ClearDepth(){Graphics::Clear();}

 void Clear(float pRed, float pGreen, float pBlue, float pAlpha){Graphics::Clear(pRed, pGreen, pBlue, pAlpha);}
 void Clear(float pRed, float pGreen, float pBlue)
 {
 Graphics::Clear(pRed, pGreen, pBlue);
 }
 void Clear()
 {
 Graphics::Clear();
 }
 */
