#import "OCInlets.h"
#import "OCOutlets.h"
#import "Root.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#include <QuartzCore/QuartzCore.h>

#import <CoreGraphics/CGImage.h>

#import <UIKit/UIKit.h>

#include <AudioToolbox/extendedaudiofile.h>
#include <AudioToolbox/AudioToolbox.h>
#include "stdafx.h"
#include <sys/time.h>
#include "Application.h"


unsigned long SystemTime()
{
	struct timeval aTime;
	gettimeofday(&aTime,NULL);
	return aTime.tv_sec*1000000+aTime.tv_usec;
}

FString SystemTimeString()
{
	struct timeval aTime;
	gettimeofday(&aTime,NULL);
    
	FString aString = Sprintf("%d", aTime.tv_sec);
	
	return aString;
}


void OpenItunesURL(FString pURL)
{
    
}

void OpenURL(FString pURL)
{
	NSString *aString = [NSString stringWithUTF8String:pURL.c()];
	NSURL *aURL = [NSURL URLWithString:aString];
	[[UIApplication sharedApplication] openURL:aURL];
}

void PlayMusic(FString pFile)
{
	[gRoot playMusic:[NSString stringWithUTF8String:pFile.c()]];
}

void SetMusicVolume(float pVolume)
{
	[gRoot setMusicVolume:pVolume];
}

void ShowControl()
{
    
}

void HideControl()
{
    
}

bool IsDevicePlayingMusic()
{
    /*
    if ([[MPMusicPlayerController iPodMusicPlayer] playbackState] == MPMusicPlaybackStatePlaying)
    {
        return true;
    }
    */
    return false;
}

void SwitchToDeviceMusic()
{
    GAPP->mMusicOn=false;
    gRoot.loopMusic=NO;
    [gRoot killMusic];
}

void SwitchToAppMusic()
{
    GAPP->mMusicOn=true;
    gRoot.loopMusic=YES;
    [gRoot killMusic];
}


void GetBundleDirectory(char *pPath)
{
	CFBundleRef mainBundle=CFBundleGetMainBundle();
	CFURLRef resourcesURL=CFBundleCopyBundleURL(mainBundle);
	CFStringRef str =CFURLCopyFileSystemPath(resourcesURL,kCFURLPOSIXPathStyle);
	CFRelease(resourcesURL);
	char aPath[4096];
	CFStringGetCString(str,aPath,FILENAME_MAX,kCFStringEncodingASCII);
	CFRelease(str);
	strcpy(pPath,aPath);
}

void GetDocumentsDirectory(char *pPath)
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString* docDir=[paths objectAtIndex:0];
	char aPath[4096];
    [docDir getCString:aPath maxLength:PATH_MAX encoding:NSASCIIStringEncoding];
	strcpy(pPath,aPath);
}

unsigned int *LoadImage(char *pFile, int &pWidth, int &pHeight, float &pScale)
{
	UIImage *aImage;
	NSString *aPath=[NSString stringWithUTF8String:pFile];
	
	aImage=//[[UIImage alloc] initWithContentsOfFile:aPath];
    
    [UIImage imageWithContentsOfFile:aPath];
    
	pWidth=0;
	pHeight=0;
    pScale=1.0f;
	
	unsigned int *aData=0;
	
    if(aImage)
    {
        if(aImage.size.width>0&&aImage.size.height>0)
        {
            FString aMaskPath = pFile;
            FString aExtension = aMaskPath.RemoveExtension();
            
            aMaskPath = aMaskPath + FString("_alpha.") + aExtension;
            
            UIImage *aMaskImage = [UIImage imageWithContentsOfFile:[NSString stringWithUTF8String:aMaskPath.c()]];
            if(aMaskImage.size.width == aImage.size.width)
            {
                
                CGImageRef aMaskRef = aMaskImage.CGImage;
                
                CGImageRef aMask = CGImageMaskCreate(CGImageGetWidth(aMaskRef),
                                                     CGImageGetHeight(aMaskRef),
                                                     CGImageGetBitsPerComponent(aMaskRef),
                                                     CGImageGetBitsPerPixel(aMaskRef),
                                                     CGImageGetBytesPerRow(aMaskRef),
                                                     CGImageGetDataProvider(aMaskRef), NULL, false);
                
                CGImageRef aMaskedImage = CGImageCreateWithMask([aImage CGImage], aMask);
                
                aImage = [UIImage imageWithCGImage:aMaskedImage];
                
            }
            
            pWidth=aImage.size.width;
            pHeight=aImage.size.height;
            
            
#ifdef IPAD_RETINA_TEST_MODE
            
            if(gSpriteIgnoreRetina == false)
            {
                if(gIsIpad == false)
                {
                    pWidth /= 2;
                    pHeight /= 2;
                    
                    if(gDoubleRez == false)
                    {
                        pWidth /= 2;
                        pHeight /= 2;
                    }
                    
                }
                else
                {
                    if(gDoubleRez == false)
                    {
                        pWidth /= 2;
                        pHeight /= 2;
                    }
                }
            }
            
#else
            
#endif
            
            //pScale=aImage.scale;
            
            //NSLog(@"Image Info: Scale %f  W: %f  H: %f Ipad[%d]", aImage.scale, aImage.size.width, aImage.size.height, gIsIpad);
            
            
            //TODO: Universal? What?
            /*
            if(gIsIpad)
            {
                if(aImage.scale > 1.5f)
                {
                    pWidth  *= 2;
                    pHeight *= 2;
                }
            }
            */
            
            CGImageRef aCGImage=aImage.CGImage;
            aData = new unsigned int[(unsigned int)(pWidth*pHeight)];
            CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
            CGContextRef aCGContext=CGBitmapContextCreate(aData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
            CGContextClearRect(aCGContext, CGRectMake(0, 0, pWidth, pHeight));
            CGContextDrawImage(aCGContext,CGRectMake(0, 0, pWidth, pHeight),aCGImage);
            CGContextRelease(aCGContext);
            CGColorSpaceRelease(aColorSpace);
            
        }
    }
    
	return aData;
}




unsigned int *LoadSound(char *theFilename, int *theDataSize, int *theDataFormat, int* theSampleRate)
{
	NSString *aPath=[NSString stringWithUTF8String: theFilename];	
	NSURL *aUrl=[NSURL fileURLWithPath:aPath];
	
	
	//NSLog(@"Previous App: %@", @"file://localhost/var/mobile/Applications/54D96072-CAF8-406B-A4A9-487EA0088C03/Chrysler300.app/menu_down.aif");
	
	
	//NSLog(@"FileURL: %@", aUrl);
	
	CFURLRef						aFileURL=(__bridge CFURLRef)aUrl;
	OSStatus						aResult = noErr;	
	SInt64							aFileLengthInFrames = 0;
	AudioStreamBasicDescription		aFileFormat;
	UInt32							aPropertySize = sizeof(aFileFormat);
	ExtAudioFileRef					aExtRef = NULL;
	unsigned int*					aData = NULL;
	AudioStreamBasicDescription		aOutputFormat;
	
	for(;;)
	{
		aResult=ExtAudioFileOpenURL(aFileURL, &aExtRef);
		if(aResult) {
            //printf("AudioToBits: ExtAudioFileOpenURL FAILED, Error = %ld\n", aResult);
		//	break;
		}
		
		aResult=ExtAudioFileGetProperty(aExtRef, kExtAudioFileProperty_FileDataFormat, &aPropertySize, &aFileFormat);
		if(aResult) {
            //printf("AudioToBits: ExtAudioFileGetProperty(kExtAudioFileProperty_FileDataFormat) FAILED, Error = %ld\n",aResult);
            break;}
		if (aFileFormat.mChannelsPerFrame>2)  {
            //printf("MyGetOpenALAudioData - Unsupported Format, channel count is greater than stereo\n");
            break;}
		
		
		aOutputFormat.mSampleRate=aFileFormat.mSampleRate;
		aOutputFormat.mChannelsPerFrame=aFileFormat.mChannelsPerFrame;
		
		
		aOutputFormat.mFormatID=kAudioFormatLinearPCM;
		aOutputFormat.mBytesPerPacket=2*aOutputFormat.mChannelsPerFrame;
		aOutputFormat.mFramesPerPacket=1;
		aOutputFormat.mBytesPerFrame=2*aOutputFormat.mChannelsPerFrame;
		aOutputFormat.mBitsPerChannel=16;
		aOutputFormat.mFormatFlags=kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
		
		aResult=ExtAudioFileSetProperty(aExtRef, kExtAudioFileProperty_ClientDataFormat,sizeof(aOutputFormat),&aOutputFormat);
		if(aResult)
		{
			//printf("AudioToBits: ExtAudioFileSetProperty(kExtAudioFileProperty_ClientDataFormat) FAILED, Error = %ld\n",aResult);
			break;
		}
		
		aPropertySize=sizeof(aFileLengthInFrames);
		aResult=ExtAudioFileGetProperty(aExtRef, kExtAudioFileProperty_FileLengthFrames, &aPropertySize, &aFileLengthInFrames);
		if(aResult)
		{
			//printf("AudioToBits: ExtAudioFileGetProperty(kExtAudioFileProperty_FileLengthFrames) FAILED, Error = %ld\n",aResult);
			break;
		}
		
		unsigned int aDataSize=aFileLengthInFrames*aOutputFormat.mBytesPerFrame;;
		aData = (unsigned int*)malloc(aDataSize);
		if (aData)
		{
			AudioBufferList		aDataBuffer;
			aDataBuffer.mNumberBuffers = 1;
			aDataBuffer.mBuffers[0].mDataByteSize=aDataSize;
			aDataBuffer.mBuffers[0].mNumberChannels=aOutputFormat.mChannelsPerFrame;
			aDataBuffer.mBuffers[0].mData=aData;
			
			aResult=ExtAudioFileRead(aExtRef, (UInt32*)&aFileLengthInFrames, &aDataBuffer);
			if(aResult==noErr)
			{
				*theDataSize = (int)aDataSize;
				*theDataFormat = aOutputFormat.mChannelsPerFrame;//(aOutputFormat.mChannelsPerFrame>1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
				*theSampleRate = (int)aOutputFormat.mSampleRate;
			}
			else 
			{ 
				free(aData);
				aData=NULL;
				//printf("AudioToBits: ExtAudioFileRead FAILED, Error = %ld\n",aResult); break;
			}	
		}
		break;
	}
	
	// Dispose the ExtAudioFileRef, it is no longer needed
	if(aExtRef)
	{
		ExtAudioFileDispose(aExtRef);
	}
	return aData;
}

bool IsIPodMusicPlaying()
{
	UInt32 aPropertySize;
	UInt32 aOtherAudioIsPlaying;
	
	AudioSessionInitialize(NULL, NULL, NULL, NULL);	
	aPropertySize = sizeof aOtherAudioIsPlaying;
	AudioSessionGetProperty(kAudioSessionProperty_OtherAudioIsPlaying,&aPropertySize,&aOtherAudioIsPlaying);
	
	if (aOtherAudioIsPlaying)
	{
		UInt32 aSessionCategory = kAudioSessionCategory_UserInterfaceSoundEffects;
		AudioSessionSetProperty( kAudioSessionProperty_AudioCategory, sizeof aSessionCategory, &aSessionCategory );
		AudioSessionSetActive( true );	
	}
	
	return (aOtherAudioIsPlaying!=0);
}

bool OpenURL( const char* utf8url )
{
	NSString* urlString = [NSString stringWithUTF8String:utf8url];
	NSURL* url = [NSURL URLWithString:urlString];
	BOOL aReturn = [[UIApplication sharedApplication] openURL:url];
	return aReturn == YES;
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

//UIImage *ImageFromView(UIView *pView)
//{
//	UIGraphicsBeginImageContextWithOptions(pView.bounds.size, pView.opaque, [[UIScreen mainScreen] scale]); 
//    [pView.layer renderInContext:UIGraphicsGetCurrentContext()];
//    UIImage * img = UIGraphicsGetImageFromCurrentImageContext();
//    UIGraphicsEndImageContext();
//    return img;
//	
//}

void ExportPNGImage(unsigned int *pData, char *pPath, int pWidth, int pHeight)
{
	UIImage *aImage;
	CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
	CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
	CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
	aImage = [[UIImage alloc] initWithCGImage:aRef];
	ExportPNGImage(aImage, pPath);
	
	CGContextRelease(aBitmap);
}

void ExportJPEGImage(unsigned int *pData, char *pPath, int pWidth, int pHeight, float pQuality)
{
	UIImage *aImage;
	CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
	CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
	CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
	aImage = [[UIImage alloc] initWithCGImage:aRef];
	ExportJPEGImage(aImage, pPath,pQuality);
	CGContextRelease(aBitmap);
}

void ExportJPEGImage(UIImage *pImage, char *pPath, float pQuality)
{
	NSData *aImageData = UIImageJPEGRepresentation(pImage, pQuality);
	[aImageData writeToFile:[[NSString alloc] initWithUTF8String:(pPath)] atomically:YES];
}

void ExportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight)
{
	UIImage *aImage;
	CGColorSpaceRef aColorSpace=CGColorSpaceCreateDeviceRGB();
	CGContextRef aBitmap = CGBitmapContextCreate(pData, pWidth, pHeight, 8, pWidth*4, aColorSpace, kCGImageAlphaPremultipliedLast);
	CGImageRef aRef = CGBitmapContextCreateImage(aBitmap);
	aImage = [[UIImage alloc] initWithCGImage:aRef];
	
	ExportToPhotoLibrary(aImage);
    
	CGContextRelease(aBitmap);
}

void RootDeleteFile(char *pPath)
{
	RootDeleteFile([NSString stringWithUTF8String:pPath]);
}

float NSStringToFloat(NSString *pString)
{
    FString aString = [pString UTF8String];
    return aString.ToFloat();
}

float TextBoxToFloat(UITextField *pTextField)
{
    return NSStringToFloat(pTextField.text);
    
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

void ShowAlert(char *pTitle,char *pText,char *pButton)
{
	ShowAlert((const char*)pTitle,(const char*)pText,(const char*)pButton);
}



/*
void GoOpenFeint()
{
	[OpenFeint launchDashboard];
}
*/


/*
UIImage *thumbWithSideOfLength()
{
	
    NSString *subdir = @"my/images/directory";
    NSString *filename = @"myOriginalImage.png";
    NSString *fullPathToThumbImage = [subdir FStringByAppendingPathComponent:[NSString stringWithFormat:@"%dx%d%@",(int) length, (int) length,filename];
 NSString *fullPathToMainImage = [subdir FStringByAppendingPathComponent:filename];
 
 UIImage *thumbnail;
 
 NSFileManager *fileManager = [NSFileManager defaultManager];
 
 if ([fileManager fileExistsAtPath:fullPathToThumbImage] == YES) {
 thumbnail = [UIImage imageWithContentsOfFile:fullPathToThumbImage];
 
 }
 else {
 //couldn’t find a previously created thumb image so create one first…
 UIImage *mainImage = [UIImage imageWithContentsOfFile:fullPathToMainImage];
 
 UIImageView *mainImageView = [[UIImageView alloc] initWithImage:mainImage];
 
 BOOL widthGreaterThanHeight = (mainImage.size.width > mainImage.size.height);
 float sideFull = (widthGreaterThanHeight) ? mainImage.size.height : mainImage.size.width;
 
 CGRect clippedRect = CGRectMake(0, 0, sideFull, sideFull);
 
 //creating a square context the size of the final image which we will then
 // manipulate and transform before drawing in the original image
 UIGraphicsBeginImageContext(CGSizeMake(length, length));
 CGContextRef currentContext = UIGraphicsGetCurrentContext();
 
 CGContextClipToRect( currentContext, clippedRect);
 
 CGFloat scaleFactor = length/sideFull;
 
 if (widthGreaterThanHeight) {
 //a landscape image – make context shift the original image to the left when drawn into the context
 CGContextTranslateCTM(currentContext, -((mainImage.size.width – sideFull) / 2) * scaleFactor, 0);
 
 }
 else {
 //a portfolio image – make context shift the original image upwards when drawn into the context
 CGContextTranslateCTM(currentContext, 0, -((mainImage.size.height – sideFull) / 2) * scaleFactor);
 
 }
 //this will automatically scale any CGImage down/up to the required thumbnail side (length) when the CGImage gets drawn into the context on the next line of code
 CGContextScaleCTM(currentContext, scaleFactor, scaleFactor);
 
 [mainImageView.layer renderInContext:currentContext];
 
 thumbnail = UIGraphicsGetImageFromCurrentImageContext();
 
 UIGraphicsEndImageContext();
 NSData *imageData = UIImagePNGRepresentation(thumbnail);
 
 [imageData writeToFile:fullPathToThumbImage atomically:YES];
 
 thumbnail = [UIImage imageWithContentsOfFile:fullPathToThumbImage];
 }
 return thumbnail;
 }
 */


//- (NSMutableArray*)fetchOrderedFiles:(NSString*)basePath ofType:(NSString*)fileType






bool StoreIsConnecting()
{
    return gStore.isConnecting;
}

bool StoreIsRequesting()
{
    return gStore.isRequesting;
}

bool StoreIsPaying()
{
     return gStore.isPaying;
}


bool StoreDidSucceed()
{
     return gStore.didSucceed;
}

bool StoreDidFail()
{
     return gStore.didFail;
}

bool StoreDidCancel()
{
     return gStore.didCancel;
}


void StoreBuy(const char *pItem)
{
    [gStore buy:[NSString stringWithUTF8String:pItem]];
}

void StoreRestore()
{
    [gStore restorePurchases];
}

void StoreReset()
{
    [gStore resetAll];
}


void GameCenterShowAchievements()
{
    [gGameCenter showAchievements];
}

void GameCenterShowLeaderboard(FString pName)
{
    [gGameCenter showLeaderboard:[NSString stringWithUTF8String:pName.c()]];
}

bool GameCenterIsConnecting()
{
    return gGameCenter.isConnecting;
}

bool GameCenterIsConnected()
{
    return gGameCenter.isConnecting;
}

bool GameCenterDidFail()
{
    return gGameCenter.didFail;
}

bool GameCenterModeLeaderboard()
{
    return gGameCenter.modeLeaderboard;
}
bool GameCenterModeAchievements()
{
    return gGameCenter.modeAchievements;
}

bool GameCenterIsShowingLeaderboard()
{
    return gGameCenter.isShowingLeaderboard;
}

bool GameCenterIsShowingAchievements()
{
    return gGameCenter.isShowingAchievements;
}

bool GameCenterIsShowing()
{
    return gGameCenter.isShowingLeaderboard || gGameCenter.isShowingAchievements;
}

void GameCenterSubmitScore(int pScore, const char *pLeaderboard)
{
    [gGameCenter submitScore:[NSString stringWithUTF8String:pLeaderboard] withScore:pScore];
}

void GameCenterSubmitScore(int pScore, char *pLeaderboard)
{
    GameCenterSubmitScore(pScore, (const char*)pLeaderboard);
}

void GameCenterSubmitScore(int pScore, FString pLeaderboard)
{
    GameCenterSubmitScore(pScore, (const char*)pLeaderboard.c());
}

void GameCenterSyncAll()
{
    [gGameCenter syncAchievements];
}

void GameCenterConnect()
{
    [gGameCenter signIn];
}

void GameCenterUpdateAchievement(const char *pAchievement, float pPercent)
{
    
}

void GameCenterUpdateAchievement(char *pAchievement, float pPercent)
{
    GameCenterUpdateAchievement((const char *)pAchievement, pPercent);
}

void GameCenterUpdateAchievement(FString pAchievement, float pPercent)
{
    GameCenterUpdateAchievement((const char*)pAchievement.c(), pPercent);
}
