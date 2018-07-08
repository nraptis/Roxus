#import "OCInlets.h"
#import "OCOutlets.h"

#import "Root.h"
#import "Root.h"
#include "GLApp.h"

void LoadImageOver(UIImage *pImage, unsigned int *pData, int &pWidth, int &pHeight,float &pScale)
{
    pWidth=(int)pImage.size.width;
    pHeight=(int)pImage.size.height;
    pScale=pImage.scale;
    
    CGImageRef aCGImage=pImage.CGImage;
    
    CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
    
    CGContextRef aCGContext=CGBitmapContextCreate(pData, pWidth, pHeight, 8, pImage.size.width*4, aColorSpace, kCGImageAlphaPremultipliedLast);
    
    CGContextClearRect(aCGContext, CGRectMake(0, 0, pWidth, pHeight));
    
    CGContextDrawImage(aCGContext,CGRectMake(0,0,pWidth,pHeight),aCGImage);
    CGContextRelease(aCGContext);
}

void LoadImageOver(UIImage *pImage, unsigned int *pData, int &pWidth, int &pHeight)
{
    pWidth=(int)pImage.size.width;
    pHeight=(int)pImage.size.height;
    
    CGImageRef aCGImage=pImage.CGImage;
    
    CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
    
    CGContextRef aCGContext=CGBitmapContextCreate(pData, pWidth, pHeight, 8, pImage.size.width*4, aColorSpace, kCGImageAlphaPremultipliedLast);
    
    CGContextClearRect(aCGContext, CGRectMake(0, 0, pWidth, pHeight));
    CGContextDrawImage(aCGContext,CGRectMake(0,0,pWidth,pHeight),aCGImage);
    
    CGContextRelease(aCGContext);
}

unsigned int *LoadImage(UIImage *pImage,int &pWidth,int &pHeight,float &pScale)
{
    pWidth=0;
	pHeight=0;
    pScale=1.0f;
	unsigned int *aData=0;
	if(pImage)
	{
		if(pImage.size.width>0&&pImage.size.width<=4096&&pImage.size.height>0&&pImage.size.height<=4096)
		{
            
            
#ifdef IPAD_RETINA_TEST_MODE
            
            pWidth=(int)pImage.size.width / 4.0f;
            pHeight=(int)pImage.size.height / 4.0f;
            
            NSLog(@"Image Scaled Down[%d %d] [%f %f]", pWidth, pHeight, pImage.size.width, pImage.size.height);
            pScale=pImage.scale;
            
            aData = new unsigned int[(unsigned int)(pWidth*pHeight)];
            LoadImageOver(pImage, aData, pWidth, pHeight, pScale);
#else
            pWidth=(int)pImage.size.width;
            pHeight=(int)pImage.size.height;
            pScale=pImage.scale;
            
            aData = new unsigned int[(unsigned int)(pWidth*pHeight)];
            LoadImageOver(pImage, aData, pWidth, pHeight, pScale);
            
#endif
            
			
		}
	}
	return aData;
}


unsigned int *LoadImage(UIImage *pImage, int &pWidth, int &pHeight)
{
	float aScale=1.0f;
    return LoadImage(pImage, pWidth, pHeight, aScale);
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
    
    [pImage drawInRect:CGRectMake(pOffsetX, pOffsetY, pImage.size.width * pScale, pImage.size.height * pScale)];
    
    UIImage *aReturn = UIGraphicsGetImageFromCurrentImageContext();    
    UIGraphicsEndImageContext();
    return aReturn;
}





UIImage *ImageRotated(UIImage *pImage, float pDegrees)
{
    
    NSLog(@"Image [%f %f] Sc[%f]", pImage.size.width, pImage.size.height, pImage.scale);
    
    float aRads = pDegrees * D_R;
    
    // calculate the size of the rotated view's containing box for our drawing space
    UIView *rotatedViewBox = [[UIView alloc] initWithFrame:CGRectMake(0,0,pImage.size.width, pImage.size.height)];
    CGAffineTransform t = CGAffineTransformMakeRotation(aRads);
    rotatedViewBox.transform = t;
    CGSize rotatedSize = rotatedViewBox.frame.size;
    
    // Create the bitmap context
    UIGraphicsBeginImageContext(rotatedSize);
    CGContextRef bitmap = UIGraphicsGetCurrentContext();
    
    // Move the origin to the middle of the image so we will rotate and scale around the center.
    CGContextTranslateCTM(bitmap, rotatedSize.width/2, rotatedSize.height/2);
    
    //   // Rotate the image context
    CGContextRotateCTM(bitmap, aRads);
    
    // Now, draw the rotated/scaled image into the context
    CGContextScaleCTM(bitmap, 1.0, -1.0);
    CGContextDrawImage(bitmap, CGRectMake(-pImage.size.width / 2, -pImage.size.height / 2, pImage.size.width, pImage.size.height), [pImage CGImage]);
    
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
    
}

void ExportPNGImage(UIImage *pImage, char *pPath)
{
	NSData *aImageData = UIImagePNGRepresentation(pImage);
	[aImageData writeToFile:[[NSString alloc] initWithUTF8String:(pPath)] atomically:YES];
}

void RootDeleteFile(NSString *pPath)
{
	NSFileManager *fileManager = [NSFileManager defaultManager];
	[fileManager removeItemAtPath:pPath error:NULL];
}





void ExportToPhotoLibrary(UIImage *pImage)
{
    NSLog(@"Exporting(%f, %f)", pImage.size.width, pImage.size.height);
    
	UIImageWriteToSavedPhotosAlbum(pImage, nil, nil, nil);
}

NSString *GetIPath(const char *pStart, int pIndex, const char *pEnd)
{
	NSString *aReturn=nil;
	FString aString = FString(pStart) + FString(pIndex) + FString(pEnd);
	
	if(aString.c())
	{
		aReturn = [NSString stringWithFormat:@"%s", aString.c()];
	}
	return aReturn;
}


NSString *S_NS(FString pString)
{
    return [NSString stringWithUTF8String:(pString.mLength > 0 ? pString.c():"")];
    
}

FString NS_S(NSString *pString)
{
    FString aReturn;
    
    if(pString)
    {
        if([pString length] > 0)
        {
            aReturn = [pString UTF8String];
        }
    }
    if(aReturn.mLength<=0)aReturn="";
    return aReturn;
}

NSString *NS(const char* pString)
{
    if(pString)
    {
        return [NSString stringWithUTF8String:pString];
    }
    else
    {
        return [NSString stringWithUTF8String:""];
    }
}


NSMutableArray *OrderedFiles(const char *pBaseName)
{
    List aList;
    
    aList += new FString("");
    aList += new FString(".png");
    aList += new FString(".jpg");
    
    
    NSMutableArray *aArray = [[NSMutableArray alloc] init];
    int aIndex = 0;
    
    /*
     
     EnumList(FString, aExtension, aList)
     {
     
     
     }
     
     FreeList(FString, aList);
     
     
     
     
     while(true)
     {
     NSString *aFileName = [[NSString alloc] initWithFormat:@"%@%d", basePath, aIndex];
     NSString *aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
     
     
     if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
     {
     [aArray addObject:aCheckPath];
     }
     else
     {
     
     
     aFileName = [[NSString alloc] initWithFormat:@"%@0%d", basePath, aIndex];
     aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
     
     
     
     if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
     {
     [aArray addObject:aCheckPath];
     }
     else
     {
     
     
     
     aFileName = [[NSString alloc] initWithFormat:@"%@00%d", basePath, aIndex];
     aCheckPath = [[NSBundle mainBundle] pathForResource:aFileName ofType:fileType];
     
     
     
     if([[NSFileManager defaultManager] fileExistsAtPath:aCheckPath])
     {
     [aArray addObject:aCheckPath];
     }
     else
     {
     if(aIndex!=0)
     {
     
     break;
     }
     }
     }
     }
     aIndex++;
     }
     return aArray;
     */
}

UIImage *ImageFromView(UIView *pView)
{
    UIGraphicsBeginImageContextWithOptions(pView.bounds.size, pView.opaque, 0.0);
    
    [pView.layer renderInContext:UIGraphicsGetCurrentContext()];
    
    UIImage * img = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    return img;
}

CGRect FitImage(CGRect pRect, CGSize pSize, float pBorder)
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
    return FitImage(pRect, CGSizeMake(pImage.size.width, pImage.size.height), pBorder);
}
