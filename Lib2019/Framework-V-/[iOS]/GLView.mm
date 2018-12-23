//
//  GLView.m
//  Gnome
//
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "GLViewController.h"
#import "GLView.h"
#import "RootBase.h"
#import "core_app_shell.h"

GLView *gGLView;

@interface GLView (PrivateMethods)

- (void)createFramebuffer;
- (void)deleteFramebuffer;

@end

@implementation GLView

@dynamic context;

// You must implement this method
+ (Class)layerClass {
    return [CAEAGLLayer class];
}

//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:.
- (id)initWithCoder:(NSCoder*)coder {
    self = [super initWithCoder:coder];
	gGLView = self;
    return self;
}

- (void)setUp {
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
	eaglLayer.opaque = TRUE;
	eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
									kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
									nil];
    
    gGLView = self;
}

- (void)dealloc
{
    NSLog(@"Kill OpenGL View...");
    
    [self deleteFramebuffer];    
}

- (EAGLContext *)context
{
    return context;
}

- (void)setContext:(EAGLContext *)newContext
{
    if (context != newContext)
    {
        [self deleteFramebuffer];
        
        [EAGLContext setCurrentContext:newContext];
        
        context = newContext;
    }
}

- (void)createFramebuffer {
    if (context && !defaultFramebuffer) {
        [EAGLContext setCurrentContext:context];
		
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, framebufferWidth, framebufferHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
        
        NSLog(@"Frame Buffer Size [%d x %d]\n", framebufferWidth, framebufferHeight);
        NSLog(@"Device Size [%d x %d]\n", (int)gDeviceWidth, (int)gDeviceHeight);
	}
}

- (void)deleteFramebuffer {
    if (context) {
        [EAGLContext setCurrentContext:context];
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if(colorRenderbuffer)
        {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
    }
}

- (void)setFramebuffer {
    if (context) {
        [EAGLContext setCurrentContext:context];
        if(!defaultFramebuffer)[self createFramebuffer];
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glViewport(0,0,framebufferWidth, framebufferHeight);
    }
}

- (void)setContext {
    if (context != NULL) {
        [EAGLContext setCurrentContext:context];
    }
}

- (BOOL)presentFramebuffer {
    BOOL success = FALSE;
    if (context) {
        [EAGLContext setCurrentContext:context];
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    return success;
}

- (void)layoutSubviews
{
    [self deleteFramebuffer];
}


- (UIImage*)drawToImage:(unsigned char*)targetBuffer withFlipBuffer:(unsigned char*)targetBufferFlipped withWidth:(int)targetWidth withHeight:(int)targetHeight
{
    int aWidth = targetWidth;
    int aHeight = targetHeight;
    
    NSInteger myDataLength = gDeviceWidth * gDeviceHeight * 4;
	
    glReadPixels(0, 0, gDeviceWidth, gDeviceHeight, GL_RGBA, GL_UNSIGNED_BYTE, targetBuffer);
    
    //int aHeight4 = gDeviceWidth * 4;
    int aWidth4 = gDeviceWidth * 4;
    
    for (int y = 0; y < gDeviceHeight; y++) {
        for (int x = 0; x < aWidth4; x++) {
            targetBufferFlipped[((aHeight-1) - y) * aWidth4 + x] = targetBuffer[y * aWidth4 + x];
        }
    }

    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, targetBufferFlipped, myDataLength, NULL);
    
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow = 4 * aWidth;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    //CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    // make the cgimage
    CGImageRef imageRef = CGImageCreate(aWidth, aHeight, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    
    // then make the uiimage from that
    UIImage *myImage = [UIImage imageWithCGImage:imageRef];    
    
    //CGImageRelease(imageRef);
    //CGColorSpaceRelease(colorSpaceRef);
    //CGDataProviderRelease(provider);
    
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpaceRef);
    CGImageRelease(imageRef);

    
    return myImage;
    
}

/*

- (UIImage*)drawToImage
{
    //glFinish();

    
    int aWidth = gDeviceWidth;
    int aHeight = gDeviceHeight;
    
    NSInteger myDataLength = aWidth * aHeight * 4;
    
    // allocate array and read pixels into it.
    GLubyte *buffer = (GLubyte *) malloc(myDataLength);
	
    glReadPixels(0, 0, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	
	//[self drawView];
	//glReadPixels(0, 0, aWidth, 480, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    // gl renders "upside down" so swap top to bottom into new array.
    // there's gotta be a better way, but this works.

    
    // make data provider with data.
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, myDataLength, NULL);
                                                              //buffer2, myDataLength, NULL);
    
    // prep the ingredients
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow = 4 * aWidth;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    //CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    // make the cgimage
    CGImageRef imageRef = CGImageCreate(aWidth, aHeight, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    
    // then make the uiimage from that
    UIImage *myImage = [UIImage imageWithCGImage:imageRef];    
    
    //CGImageRelease(imageRef);
    //CGColorSpaceRelease(colorSpaceRef);
    //CGDataProviderRelease(provider);
    
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpaceRef);
    CGImageRelease(imageRef);

    //free(FFile);
    //free(FFile2);
    //
    
    return myImage;
    
}

- (UIImage*)convertToImage
{
    
    NSLog(@"Converting GL Buffer To Image!!!");
	
	glFinish();
	
	//Double Draw This Crap??
	[EAGLContext setCurrentContext:context];
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, framebufferWidth, framebufferHeight);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glOrthof(0, gDeviceWidth, gDeviceHeight, 0, -100, 100);
	gApp->BaseDraw();
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
	[context presentRenderbuffer:GL_RENDERBUFFER_OES];
	//End Double Draw...
	
    
    int aWidth = gDeviceWidth;
    int aHeight = gDeviceHeight;
    
    NSInteger myDataLength = aWidth * aHeight * 4;
    
    // allocate array and read pixels into it.
    GLubyte *buffer = (GLubyte *) malloc(myDataLength);
	
    glReadPixels(0, 0, 320, 480, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	
	//[self drawView];
	//glReadPixels(0, 0, 320, 480, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    // gl renders "upside down" so swap top to bottom into new array.
    // there's gotta be a better way, but this works.
    GLubyte *buffer2 = (GLubyte *) malloc(myDataLength);
    for(int y = 0; y < 480; y++)
    {
        for(int x = 0; x < 320 * 4; x++)
        {
            buffer2[(479 - y) * 320 * 4 + x] = buffer[y * 4 * 320 + x];
        }
    }
 
    // make data provider with data.
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer2, myDataLength, NULL);
    
    // prep the ingredients
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow = 4 * 320;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    //CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    // make the cgimage
    CGImageRef imageRef = CGImageCreate(320, 480, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    
    // then make the uiimage from that
    UIImage *myImage = [UIImage imageWithCGImage:imageRef];
    
    CGDataProviderRelease(provider);
	CGImageRelease(imageRef);
	//CGImageRelease(imagem);
	//CGContextRelease(context);
    CGColorSpaceRelease(colorSpaceRef);
 
    return myImage;
}
 
*/


- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
	for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
		if([aTouch phase] == UITouchPhaseBegan)
		{			
			CGPoint aLocation = [aTouch locationInView:self];
            
            //AppShellTouchDownDroid(aLocation.x, aLocation.y, 0);
			AppShellTouchDown(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}		
	}
}


- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
	for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
		
		if([aTouch phase] == UITouchPhaseMoved)
		{
			CGPoint aLocation = [aTouch locationInView:self];
            //AppShellTouchMoveDroid(aLocation.x, aLocation.y, 0);
            AppShellTouchMove(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}		
	}
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
	for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
		if([aTouch phase] == UITouchPhaseEnded)
		{
			CGPoint aLocation = [aTouch locationInView:self];
            //AppShellTouchUpDroid(aLocation.x, aLocation.y, 0);
            AppShellTouchUp(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(int i=0;i<[touches count];i++)
	{
		UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
		if([aTouch phase]  == UITouchPhaseCancelled)
		{
			CGPoint aLocation = [aTouch locationInView:self];
            //AppShellTouchCanceledDroid(aLocation.x, aLocation.y, 0);
			AppShellTouchCanceled(aLocation.x, aLocation.y, (__bridge void*)aTouch);
		}
	}
}

@end
