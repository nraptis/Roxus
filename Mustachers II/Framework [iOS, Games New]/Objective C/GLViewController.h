//
//  GLViewController.h
//  JeepWranglerPhone
//
//  Created by Nick Raptis on 7/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import <GameKit/GameKit.h>
#import <AVFoundation/AVFoundation.h>

#import "GLView.h"

@interface GLViewController : UIViewController
{
    EAGLContext								*context;
    GLuint									program;
	
	GLView									*glView;
	
    BOOL									animating;
    NSInteger								animationFrameInterval;
    CADisplayLink							*displayLink;
    
    NSTimer                                 *updateTimer;
    NSTimeInterval                          updateInterval;
    
    int                                     updateDelay;
    int                                     updateDelayTimer;
    
    GLint                                   framebufferWidth;
    GLint                                   framebufferHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
    GLuint                                  defaultFramebuffer, colorRenderbuffer;
    GLuint                                  depthRenderbuffer;
}

@property (nonatomic, retain) NSTimer *updateTimer;
@property (nonatomic, assign) NSTimeInterval updateInterval;

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic, assign) NSInteger animationFrameInterval;

//@property (nonatomic, retain) GLView *glView;

//- (void)transitionImage;

- (void)load;

- (void)setManualDraw:(BOOL)targetState;

- (void)startAnimation;
- (void)stopAnimation;

- (void)startUpdates;
- (void)stopUpdates;

- (void)drawFrame;

- (void)drawFrameWithoutPresenting;
- (void)andThenWePresent;

- (void)drawFrameRetina;
- (void)setContext:(EAGLContext *)newContext;

- (void)createFramebuffer;
- (void)deleteFramebuffer;

- (void)setFramebuffer;
- (BOOL)presentFramebuffer;

- (UIImage*)renderToImage:(unsigned char*)targetBuffer;
- (UIImage*)drawToImage:(unsigned char*)targetBuffer withFlipBuffer:(unsigned char*)targetBufferFlipped withWidth:(int)targetWidth withHeight:(int)targetHeight;

- (UIImage*)drawImage:(unsigned char*)targetBuffer;

- (UIImage*)drawImageFast:(unsigned char*)targetBuffer withColorSpace:(CGColorSpaceRef)targetColorspace withContext:(CGContextRef)targetContext withDataProvider:(CGDataProviderRef)targetDataProvider withImageRef:(CGImageRef)targetImageRef;

- (UIImage*)drawImageFast:(unsigned char*)targetBuffer withColorSpace:(CGColorSpaceRef)targetColorspace withContext:(CGContextRef)targetContext withDataProvider:(CGDataProviderRef)targetDataProvider withImageRef:(CGImageRef)targetImageRef withWidth:(int)targetWidth withHeight:(int)targetHeight;

- (CVPixelBufferRef)toPixelBuffer:(unsigned char*)targetBuffer withColorSpace:(CGColorSpaceRef)targetColorspace withDataProvider:(CGDataProviderRef)targetDataProvider withImageRef:(CGImageRef)targetImageRef;

@end

extern bool gDrawManual;






