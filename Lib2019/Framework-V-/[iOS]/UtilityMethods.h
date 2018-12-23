//
//  UtilityMethods.h
//
//  Created by Nick Raptis on 4/25/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//#import <OpenCV/OpenCV/opencv2/opencv.h>

/*
#include "OpenCV/OpenCV/opencv2/core/core.h"
#include "OpenCV/OpenCV/opencv2/highgui/highgui.h"
#include "OpenCV/OpenCV/opencv2/imgproc/imgproc.h"

#include "OpenCV/OpenCV/opencv2/opencv_modules.h"
#include "OpenCV/OpenCV/opencv2/opencv.h"

#include "OpenCV/OpenCV/opencv2/core/core_c.h"
#include "OpenCV/OpenCV/opencv2/core/core.h"
#include "OpenCV/OpenCV/opencv2/core/cuda_devptrs.h"
#include "OpenCV/OpenCV/opencv2/core/devmem2d.h"
//#include "OpenCV/OpenCV/opencv2/core/eigen.h"
#include "OpenCV/OpenCV/opencv2/core/gpumat.h"
#include "OpenCV/OpenCV/opencv2/core/internal.h":
#include "OpenCV/OpenCV/opencv2/core/mat.h"
#include "OpenCV/OpenCV/opencv2/core/opengl_interop_deprecated.h"
#include "OpenCV/OpenCV/opencv2/core/opengl_interop.h"
#include "OpenCV/OpenCV/opencv2/core/operations.h"
#include "OpenCV/OpenCV/opencv2/core/types_c.h"
#include "OpenCV/OpenCV/opencv2/core/version.h"
#include "OpenCV/OpenCV/opencv2/core/wimage.h"
*/


//using namespace cv;

//Mat MatFromImageColored(UIImage *pImage);
//Mat MatFromImageGray(UIImage *pImage);
//UIImage *ImageFromMat(Mat pMat);

void SaveDictionaryToDocuments(NSDictionary *pDictionary, NSString *pFileName);

NSDictionary *LoadDictionaryFromDocuments(NSString *pFileName);

CGRect FitImage(CGRect pRect, UIImage *pImage, float pBorder);
CGRect FitImageBase(CGRect pRect, CGSize pSize, float pBorder);

CGRect FitImageAspect(CGRect pRect, UIImage *pImage, float pBorder);
CGRect FitImageAspectBase(CGRect pRect, CGSize pSize, float pBorder);

void ExportToPhotoLibrary(UIImage *pImage);
UIImage *CropImageAspect(UIImage *pImage, CGSize pSize, float pBorder);

UIImage *MaskImage(UIImage *pImage, UIImage *pMask);

void ShowAlert(const char *pTitle, const char *pText, const char *pButton);

UIImage *ResizeImage(UIImage *pImage, int pWidth, int pHeight);
UIImage *CropImage(UIImage *pImage, float pScale, int pOffsetX, int pOffsetY, int pWidth, int pHeight);

UIImage *RotateImage(UIImage *pImage, float pDegrees);
UIImage *GreyscaleImage(UIImage *pImage);

UIImage *UIImageFromBits(unsigned int *pData, int pWidth, int pHeight);


