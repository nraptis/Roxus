//
//  UtilityMethods.m
//
//  Created by Nick Raptis on 4/25/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#import "UtilityMethods.h"

void SaveDictionaryToDocuments(NSDictionary *pDictionary, NSString *pFileName)
{
    
    NSString *aErrorString = nil;
    NSData *aData = [NSPropertyListSerialization dataFromPropertyList:pDictionary format:NSPropertyListXMLFormat_v1_0 errorDescription:&aErrorString];
    
    if(aErrorString != nil)
    {
        NSLog(@"Error Saving!");
        NSLog(@"%@", aErrorString);
    }
    
    if(aData == nil)
    {
        NSLog(@"Error Writing Dictionary! [Data Null!]");
        return;
    }
    
    NSString *aDocumentsDirectory = [NSSearchPathForDirectoriesInDomains (NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *aPath = [aDocumentsDirectory stringByAppendingPathComponent:pFileName];
    
    [aData writeToFile:aPath atomically:YES];
}


NSDictionary *LoadDictionaryFromDocuments(NSString *pFileName)
{
    NSString *aDocumentsDirectory = [NSSearchPathForDirectoriesInDomains (NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *aPath = [aDocumentsDirectory stringByAppendingPathComponent:pFileName];
    NSDictionary *aDictionary = [NSDictionary dictionaryWithContentsOfFile:aPath];
    return aDictionary;
}

CGRect FitImageBase(CGRect pRect, CGSize pSize, float pBorder)
{
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    float aImageWidth = pSize.width;
    float aImageHeight = pSize.height;
    
    float aProperWidth = pRect.size.width - pBorder * 2.0f;
    float aProperHeight = pRect.size.height - pBorder * 2.0f;
    
    aWidth = aProperWidth;
    aHeight = aProperHeight;
    
    if(aImageWidth > 0 && aImageHeight > 0 && aProperWidth > 0 && aProperHeight > 0)
    {
        
        float aRatioWidth = aImageWidth / aImageHeight;
        float aRatioHeight = aImageHeight / aImageWidth;
        
        aWidth = aProperWidth;
        aHeight = aProperWidth * aRatioHeight;
        
        if(aHeight > pRect.size.height)
        {
            aWidth = aProperHeight * aRatioWidth;
            aHeight = aProperHeight;
        }
    }
    
    float aX = (pRect.origin.x + pRect.size.width / 2.0f) - aWidth / 2.0f;
    float aY = (pRect.origin.y + pRect.size.height / 2.0f) - aHeight / 2.0f;
    
    return CGRectMake(aX, aY, aWidth, aHeight);
}

CGRect FitImage(CGRect pRect, UIImage *pImage, float pBorder)
{
    return FitImageBase(pRect, CGSizeMake(pImage.size.width, pImage.size.height), pBorder);
}


CGRect FitImageAspectBase(CGRect pRect, CGSize pSize, float pBorder)
{
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    float aImageWidth = pSize.width;
    float aImageHeight = pSize.height;
    
    float aProperWidth = pRect.size.width - pBorder * 2.0f;
    float aProperHeight = pRect.size.height - pBorder * 2.0f;
    
    aWidth = aProperWidth;
    aHeight = aProperHeight;
    
    if(aImageWidth > 0 && aImageHeight > 0 && aProperWidth > 0 && aProperHeight > 0)
    {
        
        float aRatioWidth = aImageWidth / aImageHeight;
        float aRatioHeight = aImageHeight / aImageWidth;
        
        aWidth = aProperWidth;
        aHeight = aProperWidth * aRatioHeight;
        
        if(aHeight < pRect.size.height)
        {
            aWidth = aProperHeight * aRatioWidth;
            aHeight = aProperHeight;
        }
    }
    
    float aX = (pRect.origin.x + pRect.size.width / 2.0f) - aWidth / 2.0f;
    float aY = (pRect.origin.y + pRect.size.height / 2.0f) - aHeight / 2.0f;
    
    return CGRectMake(aX, aY, aWidth, aHeight);
}

CGRect FitImageAspect(CGRect pRect, UIImage *pImage, float pBorder)
{
    return FitImageAspectBase(pRect, CGSizeMake(pImage.size.width, pImage.size.height), pBorder);
}

UIImage *CropImageAspect(UIImage *pImage, CGSize pSize, float pBorder)
{
    CGRect aFitRect = FitImageAspect(CGRectMake(0.0f, 0.0f, pSize.width, pSize.height), pImage, pBorder);
    UIGraphicsBeginImageContext(CGSizeMake(pSize.width, pSize.height));
    
    //CGContextRef aContext = UIGraphicsGetCurrentContext();
    
    //CGContextSetFillColorWithColor(aContext, [UIColor colorWithRed:0.0f green:0.0f blue:0.0f alpha:1.0f].CGColor);
    //CGContextSetAlpha(aContext,1.0f);
    //CGContextFillRect(aContext, CGRectMake(0, 0, pWidth, pHeight));
    
    [pImage drawInRect:aFitRect];
    
    UIImage *aReturn = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    //ExportToPhotoLibrary(pImage);
    //ExportToPhotoLibrary(aReturn);
    
    return aReturn;
}

void ExportToPhotoLibrary(UIImage *pImage)
{
    NSLog(@"Exporting(%f, %f)", pImage.size.width, pImage.size.height);
    
    UIImageWriteToSavedPhotosAlbum(pImage, nil, nil, nil);
}

UIImage *ResizeImage(UIImage *pImage, int pWidth, int pHeight)
{
    UIGraphicsBeginImageContext(CGSizeMake(pWidth,pHeight));
    [pImage drawInRect:CGRectMake(0, 0, pWidth, pHeight)];
    UIImage *aReturn = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return aReturn;
}


UIImage *CropImage(UIImage *pImage, float pScale, int pOffsetX, int pOffsetY, int pWidth, int pHeight)
{
    UIGraphicsBeginImageContext(CGSizeMake(pWidth,pHeight));
    
    CGContextRef aContext = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(aContext, [UIColor colorWithRed:0.0f green:0.0f blue:0.0f alpha:1.0f].CGColor);
    CGContextSetAlpha(aContext,1.0f);
    CGContextFillRect(aContext, CGRectMake(0, 0, pWidth, pHeight));
    
    [pImage drawInRect:CGRectMake(-pOffsetX, -pOffsetY, pImage.size.width * pScale, pImage.size.height * pScale)];
    
    UIImage *aReturn = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return aReturn;
}

UIImage *MaskImage(UIImage *pImage, UIImage *pMask)
{
    CGImageRef aMaskRef = pMask.CGImage;
    
    CGImageRef aMask = CGImageMaskCreate(CGImageGetWidth(aMaskRef),
                                         CGImageGetHeight(aMaskRef),
                                         CGImageGetBitsPerComponent(aMaskRef),
                                         CGImageGetBitsPerPixel(aMaskRef),
                                         CGImageGetBytesPerRow(aMaskRef),
                                         CGImageGetDataProvider(aMaskRef), NULL, false);
    
    CGImageRef aMaskedImage = CGImageCreateWithMask([pImage CGImage], aMask);
    return [UIImage imageWithCGImage:aMaskedImage];
}

void ShowAlert(const char *pTitle,const char *pText,const char *pButton)
{
    UIAlertView  *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:(const char*)pTitle]
                                                     message:[NSString stringWithUTF8String:(const char*)pText]
                                                    delegate:nil
                                           cancelButtonTitle:[NSString stringWithUTF8String:(const char*)pButton]
                                           otherButtonTitles:nil];
    [alert show];
    
}


UIImage *RotateImage(UIImage *pImage, float pDegrees)
{
    return 0;
}

UIImage *GreyscaleImage(UIImage *pImage)
{
    
    int kRed = 1;
    int kGreen = 2;
    int kBlue = 4;
    
    int colors = kGreen | kBlue | kRed;
    int m_width = pImage.size.width;
    int m_height = pImage.size.height;
    
    uint32_t *rgbImage = (uint32_t *) malloc(m_width * m_height * sizeof(uint32_t));
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(rgbImage, m_width, m_height, 8, m_width * 4, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaNoneSkipLast);
    CGContextSetInterpolationQuality(context, kCGInterpolationHigh);
    CGContextSetShouldAntialias(context, NO);
    CGContextDrawImage(context, CGRectMake(0, 0, m_width, m_height), [pImage CGImage]);
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    
    // now convert to grayscale
    uint8_t *m_imageData = (uint8_t *) malloc(m_width * m_height);
    for(int y = 0; y < m_height; y++) {
        for(int x = 0; x < m_width; x++) {
            uint32_t rgbPixel=rgbImage[y*m_width+x];
            uint32_t sum=0,count=0;
            if (colors & kRed) {sum += (rgbPixel>>24)&255; count++;}
            if (colors & kGreen) {sum += (rgbPixel>>16)&255; count++;}
            if (colors & kBlue) {sum += (rgbPixel>>8)&255; count++;}
            m_imageData[y*m_width+x]=sum/count;
        }
    }
    free(rgbImage);
    
    // convert from a gray scale image back into a UIImage
    uint8_t *result = (uint8_t *) calloc(m_width * m_height *sizeof(uint32_t), 1);
    
    // process the image back to rgb
    for(int i = 0; i < m_height * m_width; i++) {
        result[i*4]=0;
        int val=m_imageData[i];
        result[i*4+1]=val;
        result[i*4+2]=val;
        result[i*4+3]=val;
    }
    
    // create a UIImage
    colorSpace = CGColorSpaceCreateDeviceRGB();
    context = CGBitmapContextCreate(result, m_width, m_height, 8, m_width * sizeof(uint32_t), colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaNoneSkipLast);
    CGImageRef image = CGBitmapContextCreateImage(context);
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    UIImage *resultUIImage = [UIImage imageWithCGImage:image];
    CGImageRelease(image);
    
    free(m_imageData);
    
    // make sure the data will be released by giving it to an autoreleased NSData
    [NSData dataWithBytesNoCopy:result length:m_width * m_height];
    
    return resultUIImage;
}



UIImage *UIImageFromBits(unsigned int *pData, int pWidth, int pHeight)
{
    UIImage *aImage;
    CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
    CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
    CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
    aImage = [[UIImage alloc] initWithCGImage:aRef];
    CGContextRelease(aBitmap);
    
    return aImage;
}

//- (cv::Mat)cvMatFromUIImage:(UIImage *)image

/*
Mat MatFromImageColored(UIImage *pImage)
{
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(pImage.CGImage);
    CGFloat cols = pImage.size.width;
    CGFloat rows = pImage.size.height;
    
    cv::Mat cvMat(rows, cols, CV_8UC4); // 8 bits per component, 4 channels (color channels + alpha)
    
    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to  data
                                                    cols,                       // Width of bitmap
                                                    rows,                       // Height of bitmap
                                                    8,                          // Bits per component
                                                    cvMat.step[0],              // Bytes per row
                                                    colorSpace,                 // Colorspace
                                                    kCGImageAlphaNoneSkipLast |
                                                    kCGBitmapByteOrderDefault); // Bitmap info flags
    
    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), pImage.CGImage);
    CGContextRelease(contextRef);
    
    return cvMat;
}



//- (cv::Mat)cvMatGrayFromUIImage:(UIImage *)image

Mat MatFromImageGray(UIImage *pImage)
{
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(pImage.CGImage);
    CGFloat cols = pImage.size.width;
    CGFloat rows = pImage.size.height;
    
    cv::Mat cvMat(rows, cols, CV_8UC1); // 8 bits per component, 1 channels
    
    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to data
                                                    cols,                       // Width of bitmap
                                                    rows,                       // Height of bitmap
                                                    8,                          // Bits per component
                                                    cvMat.step[0],              // Bytes per row
                                                    colorSpace,                 // Colorspace
                                                    kCGImageAlphaNoneSkipLast |
                                                    kCGBitmapByteOrderDefault); // Bitmap info flags
    
    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), pImage.CGImage);
    CGContextRelease(contextRef);
    
    return cvMat;
}

//-(UIImage *)UIImageFromCVMat:(cv::Mat)cvMat
UIImage *ImageFromMat(Mat pMat)
{
    NSData *data = [NSData dataWithBytes:pMat.data length:pMat.elemSize()*pMat.total()];
    CGColorSpaceRef colorSpace;
    
    if (pMat.elemSize() == 1) {
        colorSpace = CGColorSpaceCreateDeviceGray();
    } else {
        colorSpace = CGColorSpaceCreateDeviceRGB();
    }
    
    CGDataProviderRef provider = CGDataProviderCreateWithCFData((__bridge CFDataRef)data);
    
    // Creating CGImage from cv::Mat
    CGImageRef imageRef = CGImageCreate(pMat.cols,                                 //width
                                        pMat.rows,                                 //height
                                        8,                                          //bits per component
                                        8 * pMat.elemSize(),                       //bits per pixel
                                        pMat.step[0],                            //bytesPerRow
                                        colorSpace,                                 //colorspace
                                        kCGImageAlphaNone|kCGBitmapByteOrderDefault,// bitmap info
                                        provider,                                   //CGDataProviderRef
                                        NULL,                                       //decode
                                        false,                                      //should interpolate
                                        kCGRenderingIntentDefault                   //intent
                                        );
    
    
    // Getting UIImage from CGImage
    UIImage *finalImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);
    
    return finalImage;
}
*/

/*
- (UIImage *)rotateImage:(UIImage *)image onDegrees:(float)degrees
{
    CGFloat rads = M_PI * degrees / 180;
    float newSide = MAX([image size].width, [image size].height);
    CGSize size =  CGSizeMake(newSide, newSide);
    UIGraphicsBeginImageContext(size);
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    CGContextTranslateCTM(ctx, newSide/2, newSide/2);
    CGContextRotateCTM(ctx, rads);
    CGContextDrawImage(UIGraphicsGetCurrentContext(),CGRectMake(-[image size].width/2,-[image size].height/2,size.width, size.height),image.CGImage);
    UIImage *i = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return i;
*/
