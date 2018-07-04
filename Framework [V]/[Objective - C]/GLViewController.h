//
//  GLViewController.h
//  JeepWranglerPhone
//
//  Created by Nick Raptis on 7/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#import <UIKit/UIKit.h>

#import <GLKit/GLKit.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
//#import <OpenGLES/ES2/gl.h>
//#import <OpenGLES/ES2/glext.h>

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
    
    BOOL                                    displayLinkOn;
    
    NSTimer                                 *updateTimer;
    NSTimeInterval                          updateInterval;
    
    GLint                                   framebufferWidth;
    GLint                                   framebufferHeight;
    
    GLuint                                  defaultFramebuffer, colorRenderbuffer;
    GLuint                                  depthRenderbuffer;
}

@property (nonatomic, retain) NSTimer *updateTimer;
@property (nonatomic, assign) NSTimeInterval updateInterval;

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic, assign) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

- (void)drawFrame;

//- (void)drawFrameRetina;

- (void)load;

- (void)setContext:(EAGLContext *)newContext;
- (void)createFramebuffer;
- (void)deleteFramebuffer;
- (void)setFramebuffer;
- (BOOL)presentFramebuffer;

- (UIImage*)renderToImage:(unsigned char*)targetBuffer;
- (UIImage*)drawToImage:(unsigned char*)targetBuffer withFlipBuffer:(unsigned char*)targetBufferFlipped withWidth:(int)targetWidth withHeight:(int)targetHeight;

@end

extern GLViewController *gGLViewController;






