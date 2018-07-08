//
//  OCUtils.h
//  Template
//
//  Created by Nick Raptis on 11/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef OCOUTLETS_H
#define OCOUTLETS_H

#include "List.h"
#include "FString.h"



void RootDeleteFile(NSString *pPath);

unsigned int *LoadImage(UIImage *pImage,int &pWidth,int &pHeight);
unsigned int *LoadImage(UIImage *pImage,int &pWidth,int &pHeight,float &pScale);

void LoadImageOver(UIImage *pImage, unsigned int *pData, int &pWidth, int &pHeight,float &pScale);
void LoadImageOver(UIImage *pImage, unsigned int *pData, int &pWidth, int &pHeight);


UIImage *ResizeImage(UIImage *pImage, int pWidth, int pHeight);
UIImage *CropImage(UIImage *pImage, float pScale, int pOffsetX, int pOffsetY, int pWidth, int pHeight);
UIImage *UIImageFromBits(unsigned int *pData, int pWidth, int pHeight);
NSString *S_NS(FString pString);
FString NS_S(NSString *pString);
NSString *NS(const char* pString);
void ExportPNGImage(UIImage *pImage, char *pPath);
void ExportJPEGImage(UIImage *pImage, char *pPath, float pQuality=0.75f);
void ExportToPhotoLibrary(UIImage *pImage);
NSString *GetIPath(const char *pStart, int pIndex, const char *pEnd);
NSMutableArray *OrderedFiles(const char *pBaseName);
UIImage *ImageFromView(UIView *pView);
UIImage *ImageRotated(UIImage *pImage, float pDegrees);

CGRect FitImage(CGRect pRect, UIImage *pImage, float pBorder);
CGRect FitImage(CGRect pRect, CGSize pSize, float pBorder);

float NSStringToFloat(NSString *pString);
float TextBoxToFloat(UITextField *pTextField);


#endif