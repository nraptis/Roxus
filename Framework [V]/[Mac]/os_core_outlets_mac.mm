#define _CRT_SECURE_NO_WARNINGS 1


#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>

#include "os_core_outlets.h"
#include "core_includes.h"

#include "FString.h"
#include "FFile.h"
#include "FList.h"

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

#include <algorithm>
#include <vector>
#include <thread>
#include <string>
#include <iostream>


#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>


using namespace std;
bool os_fileExists(const char *pFilePath)
{
    FString aPath;
    aPath.Set(pFilePath);
    
    
    //NSString *documentsDirectory = [paths objectAtIndex:0];
    //NSString *pdfPath = [[documentsDirectory stringByAppendingPathComponent:@"aimprojectdownloads" ] stringByAppendingPathComponent:entry.articleTitle];
    
    return [[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithUTF8String:(aPath.c())]];
    
    
    //struct stat buf;
    //int aFileStat = stat(pFilePath, &buf);
    //if((0 != aFileStat) || !(buf.st_mode & S_IFMT))return false;
    //return true;
}

bool os_is_portrait()
{
#ifdef ORIENTATION_LANDSCAPE
    return false;
#else
    return true;
#endif
}

void os_log(const char *pMessage)
{
    printf("%s", pMessage);
    //NSLog(@"%s", pMessage);
}

unsigned long os_system_time()
{
    unsigned long aResult = (unsigned long)(CFAbsoluteTimeGetCurrent() * 10000.0f);
    return aResult;
}

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength)
{
    unsigned char *aResult = 0;
    pLength = 0;
    
    if(os_fileExists(pFileName))
    {
        FString aPath;
        aPath.Set(pFileName);
        
        
        NSData *aData = [NSData dataWithContentsOfFile: [NSString stringWithUTF8String:(aPath.c())]];
        
        if(aData != nil)
        {
            pLength = (unsigned int)([aData length]);
            
            if(pLength > 0)
            {
                unsigned char *aFileData = (unsigned char *)[aData bytes];
                
                aResult = new unsigned char[pLength];
                
                for(int i=0;i<pLength;i++)
                {
                    //aResult[i] = aFileData[i];
                }
                
                memcpy(aResult, aFileData, pLength);
                
                
            }
            
            
            
        }
        
        
        
        
        
        
        
        /*
         
         
         
         
         //unsigned char * pBuffer = NULL;
         //CCAssert(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invalid parameters.");
         
         
         //*pSize = 0;
         
         // read the file from hardware
         
         //std::string fullPath = fullPathForFilename(pszFileName);
         //FILE *fp = fopen(pFileName, pszMode);
         FILE *aFile = fopen(pFileName, "r");
         
         //EXP
         
         if(aFile)
         {
         
         //CC_BREAK_IF(!fp);
         
         fseek(aFile,0,SEEK_END);
         pLength = ((int)(ftell(aFile)));
         
         if(pLength <= 0)
         {
         pLength = 0;
         }
         else
         {
         
         //*pSize = ftell(fp);
         fseek(aFile,0,SEEK_SET);
         aResult = new unsigned char[pLength];
         
         //pLength = (int)(
         fread(aResult,sizeof(unsigned char), pLength, aFile);//);
         
         if(aResult != 0)
         {
         for(int i=0;(i<8) && (i<pLength);i++)
         {
         Log("Read File[%d] = [%d]\n", i, (int)((aResult[i])));
         }
         
         }
         
         fclose(aFile);
         }
         }
         */
    }
    
    return aResult;
}

bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength)
{
    bool aResult = false;
    
    FString aPath = FString(pFileName);
    
    if((pLength > 0) && (pData != 0) && (pFileName != 0))
    {
        NSData *aData = [NSData dataWithBytes:pData length:pLength];
        NSError *aError = nil;
        //
        
        [aData writeToFile:[NSString stringWithUTF8String:(aPath.c())] options:NSDataWritingAtomic error:&aError];
        
        if(aError)
        {
            NSLog(@"Write returned error: %@", [aError localizedDescription]);
        }
        else
        {
            //gRes.AddResource(pFileName, true);
            gRes.AddResource(pFileName);
            
            aResult = true;
        }
        
    }
    
    
    /*
     [aData writeToFile:[[NSString alloc] initWithUTF8String:(pFileName)] atomically:YES];
     
     
     SString *content = [[NSString alloc]  initWithBytes:[data bytes]
     length:[data length] encoding: NSUTF8StringEncoding];
     
     NSLog(@"%@", content); // verifies data was downloaded correctly
     
     NSError* error;
     [data writeToFile:storePath options:NSDataWritingAtomic error:&error];
     
     if(error != nil)
     NSLog(@"write error %@", error);
     
     
     
     if(pData != 0)
     {
     for(int i=0;(i<8) && (i<pLength);i++)
     {
     Log("Write File[%d] = [%d]\n", i, (int)((pData[i])));
     }
     
     }
     
     if(pFileName == 0)
     {
     return false;
     }
     
     //O_BINARY|O_RDONLY
     
     int aFile = creat(pFileName, O_RDWR);
     //int aFile = creat(pFileName,S_IWRITE);
     //Log("File 1.1 = [%d]\n", aFile);
     
     if(aFile != -1)close(aFile);
     aFile = open(pFileName, O_BINARY|O_RDONLY);
     //Log("File 1.2 = [%d]\n", aFile);
     
     //Users/nraptis/Desktop/Darkswarm/[[Dig Mac]]/Assets/Exports/bonk_fat_216_bold_data.dat
     if(aFile != -1)
     {
     ///Users/nraptis/Desktop/Darkswarm/[[Dig Mac]]/Assets/Exports/bonk_fat_216_bold_data.dat
     
     write(aFile, pData, pLength);
     close(aFile);
     
     return true;
     }
     else
     {
     FString aPath = FString(gDirDocuments + pFileName);
     
     //Log("Write Path = [%s]\n", aPath.c());
     
     aFile = creat(aPath.c(), O_RDWR);
     if(aFile != -1)close(aFile);
     
     aFile = open(aPath.c(), O_RDWR);
     if(aFile != -1)
     {
     write(aFile, pData, pLength);
     close(aFile);
     
     return true;
     }
     }
     
     return false;
     
     */
    
    
    /*
     if((pData != 0) && (pLength > 0) && (pFileName != 0))
     {
     NSData *aData = [NSData dataWithBytes:pData length:pLength];
     
     [aData writeToFile:[[NSString alloc] initWithUTF8String:(pFileName)] atomically:YES];
     
     
     }
     */
    
    /*
     
     NSData *aImageData = UIImagePNGRepresentation(pImage);
     
     
     
     // Create a file to store current file.
     FILE *aFile = fopen(pFileName, "wb");
     if(!aFile)
     {
     fclose(aFile);
     return false;
     }
     
     int aError = 0;
     
     
     fwrite(pData, pLength, aError, aFile);
     
     //fwrite(<#const void *#>, <#size_t#>, <#size_t#>, <#FILE *#>)
     
     fclose(aFile);
     */
    
    return aResult;
}


bool MakeDirectory(const char *pFile)
{
    bool aValid = true;
    /*
     if(!pFile)return false;
     const char*aPtr = pFile;
     while (*aPtr)aPtr++;
     int aLength = (int)(aPtr - pFile);
     
     if(aLength < 1)return false;
     
     bool aContinue = true;
     char *aPath = new char[aLength + 1];
     char *aPathPtr = aPath;
     char *aSeek = (char *)pFile;
     
     while (*aSeek == '\\' || *aSeek == '/')
     {
     aValid = false;
     aSeek++;
     }
     while (aContinue)
     {
     aContinue = false;
     while (*aSeek != 0 && *aSeek != '\\' && *aSeek != '/')
     {
     aValid = true;
     *aPathPtr = *aSeek;
     aSeek++;
     aPathPtr++;
     }
     if(*aSeek != 0 && aSeek != pFile)
     {
     while (*aSeek == '\\' || *aSeek == '/')
     {
     aSeek++;
     }
     if(*aSeek == 0)
     {
     aValid = false;
     }
     else
     {
     *aPathPtr++ = '/';
     *aPathPtr = 0;
     
     _mkdir(aPath);// , _S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
     aContinue = true;
     aValid = true;
     }
     }
     }
     
     delete[]aPath;
     */
    
    return aValid;
}

void os_load_image_to_buffer(char *pFile, unsigned int *pData)
{
    FFile aFile;
    aFile.LoadDirect(pFile);
    
    int aWidth = 0;
    int aHeight = 0;
    
    if(aFile.mLength > 0)
    {
        NSData *aData = [NSData dataWithBytes:aFile.mData length:aFile.mLength];
        CGImageSourceRef aSource = CGImageSourceCreateWithData((CFDataRef)aData, NULL);
        CGImageRef aCGImage = CGImageSourceCreateImageAtIndex(aSource, 0, NULL);
        
        if((aCGImage != 0) && (aSource != 0))
        {
            aWidth = (int)(CGImageGetWidth(aCGImage));
            aHeight = (int)(CGImageGetHeight(aCGImage));
            
            if((aWidth > 0) && (aHeight > 0))
            {
                CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
                CGContextRef aCGContext=CGBitmapContextCreate(pData, aWidth, aHeight, 8, aWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
                CGContextClearRect(aCGContext, CGRectMake(0, 0, aWidth, aHeight));
                CGContextDrawImage(aCGContext,CGRectMake(0, 0, aWidth, aHeight),aCGImage);
                CGContextRelease(aCGContext);
                CGColorSpaceRelease(aColorSpace);
            }
            
            CFRelease(aCGImage);
            CFRelease(aSource);
        }
    }
}

unsigned int *os_load_image(char *pFile,int &pWidth, int &pHeight)
{
    unsigned int *aResult = 0;
    
    FFile aFile;
    aFile.LoadDirect(pFile);
    
    pWidth = 0;
    pHeight = 0;
    
    if(aFile.mLength > 0)
    {
        NSData *aData = [NSData dataWithBytes:aFile.mData length:aFile.mLength];
        CGImageSourceRef aSource = CGImageSourceCreateWithData((CFDataRef)aData, NULL);
        CGImageRef aCGImage = CGImageSourceCreateImageAtIndex(aSource, 0, NULL);
        
        if((aCGImage != 0) && (aSource != 0))
        {
            pWidth = (int)(CGImageGetWidth(aCGImage));
            pHeight = (int)(CGImageGetHeight(aCGImage));
            
            if((pWidth < 0) || (pHeight <= 0))
            {
                pWidth = 0;
                pHeight = 0;
            }
            else
            {
                aResult = new unsigned int[(unsigned int)(pWidth*pHeight)];
                CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
                CGContextRef aCGContext=CGBitmapContextCreate(aResult, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
                CGContextClearRect(aCGContext, CGRectMake(0, 0, pWidth, pHeight));
                CGContextDrawImage(aCGContext,CGRectMake(0, 0, pWidth, pHeight),aCGImage);
                CGContextRelease(aCGContext);
                CGColorSpaceRelease(aColorSpace);
            }
            CFRelease(aCGImage);
            CFRelease(aSource);
        }
    }
    return aResult;
}





bool os_createDirectory(const char *pDirectory)
{
    if(!pDirectory)return false;
    
    bool aValid = true;
    
    return aValid;
}

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight)
{
    int aArea = (pWidth * pHeight);
    if((pWidth <= 0) || (aArea <= 0))
    {

    }
    else
    {
        FString aPath;
        aPath += pFilePath;

        unsigned char **aCharData = new unsigned char*[pWidth];
        for(int i=0;i<pWidth;i++)aCharData[i] = (unsigned char *)(&(pData[i * pHeight]));
        
        NSBitmapImageRep *aBitmapRep =
        [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:aCharData pixelsWide:pWidth pixelsHigh:pHeight
                                             bitsPerSample:8 samplesPerPixel:4 hasAlpha:YES isPlanar:NO
                                            colorSpaceName:NSDeviceRGBColorSpace bytesPerRow:(pWidth * 4) bitsPerPixel:32];
        NSData *aData = [aBitmapRep representationUsingType:NSPNGFileType properties:nil];
        [aData writeToFile:[[NSString alloc] initWithUTF8String:(aPath.c())] atomically:YES];
        delete [] aCharData;
    }
}

void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(pFilePath)) == NULL)return;
    
    FString aBasePath;
    aBasePath.Append(pFilePath);
    
    FString aProbePath;
    while ((dirp = readdir(dp)) != NULL)
    {
        FString aPath;
        aPath.Set(dirp->d_name);
        
        if((aPath.Compare(".") != 0) && (aPath.Compare("..") != 0) && (aPath.mLength > 0))
        {
            int aDotIndex = aPath.FindReverse('.');
            bool aIsDirectory = false;
            
            if(aDotIndex == -1)
            {
                aIsDirectory = true;
            }
            else
            {
                int aDist = aPath.mLength - aDotIndex;
                if(aDist >= 6)aIsDirectory = true;
            }
            
            if(aIsDirectory == false)
            {
                aProbePath.Set(aBasePath);
                aProbePath.Append(aPath);
                FString *aNewFile = new FString(aProbePath);
                pList->Add(aNewFile);
            }
            else
            {
                aProbePath.Set(aBasePath);
                aProbePath.Append(aPath);
                aProbePath.Append('/');
                os_getFilesInDirectoryRecursive(aProbePath.c(), pList);
            }
        }
    }
    closedir(dp);
}

void os_getFilesInDirectory(const char *pFilePath, FList *pList) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(pFilePath)) == NULL)return;
    
    FString aBasePath;
    aBasePath.Append(pFilePath);
    
    FString aProbePath;
    while ((dirp = readdir(dp)) != NULL)
    {
        FString aPath;
        aPath.Set(dirp->d_name);
        if((aPath.Compare(".") != 0) && (aPath.Compare("..") != 0) && (aPath.mLength > 0))
        {
            int aDotIndex = aPath.FindReverse('.');
            bool aIsDirectory = false;
            
            if(aDotIndex == -1)
            {
                aIsDirectory = true;
            }
            else
            {
                int aDist = aPath.mLength - aDotIndex;
                if(aDist >= 6)aIsDirectory = true;
            }
            
            if(aIsDirectory == false)
            {
                aProbePath.Set(aBasePath);
                aProbePath.Append(aPath);
                FString *aNewFile = new FString(aProbePath);
                pList->Add(aNewFile);
            }
        }
    }
    closedir(dp);
}

void os_getAllResources(const char *pFilePath, FList *pList)
{
    os_getFilesInDirectoryRecursive(pFilePath, pList);
}

void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality)
{
    
}

void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight)
{
    
}
