    //
//  GLViewController.m
//  JeepWranglerPhone
//
//  Created by Nick Raptis on 7/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"
#import "GLViewController.h"
#import <QuartzCore/QuartzCore.h>

bool gDrawManual = false;

enum
{
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.

enum
{
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

@interface GLViewController ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, retain) CADisplayLink *displayLink;

- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;

@end

@implementation GLViewController

@synthesize animating;
@synthesize context;
@synthesize displayLink;

@synthesize updateTimer;
@synthesize updateInterval;

- (id)init
{
	self = [super initWithNibName:nil bundle:nil];
    
    updateDelay=60;
    updateDelayTimer=0;
    
    self.view.frame = CGRectMake(self.view.frame.origin.x,self.view.frame.origin.y,gAppWidth,gAppHeight);
    
	return self;
}

- (void)load
{
	NSLog(@"~~~ *** Initialize GL");
    
	self.view.frame = CGRectMake(self.view.frame.origin.x,self.view.frame.origin.y,gAppWidth,gAppHeight);
    
	glView = [[GLView alloc] initWithFrame:self.view.frame];
	
    [self.view addSubview:glView];
    
    [glView setUp];
    
	self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    [glView setContext:context];
    [glView setFramebuffer];
    
    animating = FALSE;
    
    self.animationFrameInterval = 1;
    
    self.displayLink = nil;
    
	gApp->Load();
	gApp->LoadComplete();
    
	[self.view setMultipleTouchEnabled:YES];
	
    [glView setMultipleTouchEnabled:YES];
    
}

- (void)didReceiveMemoryWarning
{
    
    NSLog(@"**** MEMORY WARNING **** GLViewController!");
    
}

- (void)dealloc
{
    if(program)
    {
        glDeleteProgram(program);
        program = 0;
    }
    
    // Tear down context.
    if([EAGLContext currentContext] == context)[EAGLContext setCurrentContext:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
    if(program)
    {
        glDeleteProgram(program);
        program = 0;
    }
	
    if([EAGLContext currentContext] == context)[EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    if(frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        
        if(animating)
        {
            [gGLViewController stopAnimation];
            [gGLViewController startAnimation];
        }
    }
}

- (void)startAnimation
{
    if(!animating)
    {
        //self.displayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawFrame)];
        //[self.displayLink setFrameInterval:animationFrameInterval];
        //[self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
        self.updateTimer = [NSTimer scheduledTimerWithTimeInterval:updateInterval target:self selector:@selector(updateView) userInfo:nil repeats:YES];
        
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if(animating)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
        self.updateTimer = nil;
    }
}

- (void)updateView
{
    if(!gApp)return;
    if(gApp->mLoadComplete == false)
    {
        return;
    }
    gApp->BaseUpdate();
    
    
    updateDelayTimer++;
    if(updateDelayTimer >= 2)
    {
        //NSLog(@"drawManually = %d", drawManually);
        
        updateDelayTimer = 0;
        
        //NSLog(@"Draw Mode: %d", gDrawManual);
        
        if(gDrawManual == false)
        {
            
            [self drawFrame];
        }
    }
}

- (void)setManualDraw:(BOOL)targetState
{
    gDrawManual = targetState;
    
    NSLog(@"GL DRAW MANUAL: %d", gDrawManual);
}


- (void)drawFrameWithoutPresenting
{
    if(!gApp)return;
    
    if(gApp->mLoadComplete == false)
    {
        return;
    }
    
    if(gApp->mActive == false)
    {
        return;
    }
    
    [glView setFramebuffer];
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	glViewport(0, 0, gAppWidth, gAppHeight);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    
	glOrthof(0, gAppWidth, gAppHeight, 0, -4096.0f, 4096.0f);
	
	gApp->BaseDraw();
}

- (void)andThenWePresent
{
    [glView presentFramebuffer];
}

- (void)drawFrame
{
    if(!gApp)return;
    
    if(gApp->mLoadComplete == false)
    {
        return;
    }
    
    if(gApp->mActive == false)
    {
        return;
    }
    
    [glView setFramebuffer];
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	glViewport(0, 0, gAppWidth, gAppHeight);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    
	glOrthof(0, gAppWidth, gAppHeight, 0, -4096.0f, 4096.0f);
	
	gApp->BaseDraw();
    
    [glView presentFramebuffer];
}

- (UIImage*)drawToImage:(unsigned char*)targetBuffer withFlipBuffer:(unsigned char*)targetBufferFlipped withWidth:(int)targetWidth withHeight:(int)targetHeight
{
    [self drawFrame];
    return [glView drawToImage:targetBuffer withFlipBuffer:targetBufferFlipped withWidth:targetWidth withHeight:targetHeight];
}


//CGContextRelease(cgcontext);
//CFRelease(colorspace);

//
//  = CGColorSpaceCreateDeviceRGB();

- (CVPixelBufferRef)toPixelBuffer:(unsigned char*)targetBuffer withColorSpace:(CGColorSpaceRef)targetColorspace withDataProvider:(CGDataProviderRef)targetDataProvider withImageRef:(CGImageRef)targetImageRef
{
    [self drawFrameWithoutPresenting];
    
    int aWidth = gAppWidth;
    int aHeight = gAppHeight;
    
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(0, 0, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, targetBuffer);
    
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:
                             [NSNumber numberWithBool:YES], kCVPixelBufferCGImageCompatibilityKey,
                             [NSNumber numberWithBool:YES], kCVPixelBufferCGBitmapContextCompatibilityKey,
                             nil];
    CVPixelBufferRef aPixelBuffer = NULL;
    
    CVPixelBufferCreate(kCFAllocatorDefault, aWidth,
                                          aHeight, kCVPixelFormatType_32ARGB, (__bridge CFDictionaryRef) options,
                                          &aPixelBuffer);
    
    CVPixelBufferLockBaseAddress(aPixelBuffer, 0);
    
    void *aPixelData = CVPixelBufferGetBaseAddress(aPixelBuffer);
    
    CGContextRef aContext = CGBitmapContextCreate(aPixelData, aWidth, aHeight, 8, 4*aWidth, targetColorspace, kCGImageAlphaNoneSkipFirst);
    
    //NSParameterAssert(context);
    //CGContextConcatCTM(context, CGAffineTransformMakeScale(1.0f, -1.0f));
    //CGContextConcatCTM(context, CGAffineTransformMakeRotation(0));
    //CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
    //CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
    //CGContextConcatCTM(aContext, CGAffineTransformMakeScale(1.0f, -1.0f));
    //CGContextConcatCTM(aContext, CGAffineTransformMakeRotation(PI));
    //CGContextRotateCTM(aContext, PI_2);
    //CGContextScaleCTM(aContext, -1.0f, -1.0f);
    
    CGContextConcatCTM(aContext, CGAffineTransformMakeTranslation(0.0f, aHeight));
    CGContextConcatCTM(aContext, CGAffineTransformMakeScale(1.0f, -1.0f));
    CGContextDrawImage(aContext, CGRectMake(0, 0, aWidth, aHeight), targetImageRef);
    CVPixelBufferUnlockBaseAddress(aPixelBuffer, 0);
    
    [self andThenWePresent];
    return aPixelBuffer;
    
}

- (UIImage*)drawImageFast:(unsigned char*)targetBuffer withColorSpace:(CGColorSpaceRef)targetColorspace withContext:(CGContextRef)targetContext withDataProvider:(CGDataProviderRef)targetDataProvider withImageRef:(CGImageRef)targetImageRef withWidth:(int)targetWidth withHeight:(int)targetHeight
{
    int aWidth = gAppWidth;
    int aHeight = gAppHeight;
    
    NSInteger x = 0, y = 0;
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(x, y, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, targetBuffer);
    //UIImage *image = [UIImage imageWithCGImage:targetImageRef];
    
    
    

    NSInteger widthInPoints, heightInPoints;
    
    bool aHighRez = false;
    
    if(true)
    {
        if (NULL != UIGraphicsBeginImageContextWithOptions)
        {
            aHighRez = true;
            
            CGFloat scale = 0.5f;
            widthInPoints = targetWidth * 2;
            heightInPoints = targetHeight * 2;
            UIGraphicsBeginImageContextWithOptions(CGSizeMake(widthInPoints, heightInPoints), NO, scale);
        }
    }
    
    if (aHighRez == false)
    {
        //widthInPoints = width;
        //heightInPoints = height;
        //UIGraphicsBeginImageContext(CGSizeMake(widthInPoints, heightInPoints));
    }
    
    NSLog(@"Width = %d x %d", widthInPoints, heightInPoints);
    
    CGContextRef cgcontext = UIGraphicsGetCurrentContext();
    // UIKit coordinate system is upside down to GL/Quartz coordinate system
    // Flip the CGImage by rendering it to the flipped bitmap context
    // The size of the destination area is measured in POINTS
    CGContextSetBlendMode(cgcontext, kCGBlendModeCopy);
    CGContextDrawImage(cgcontext, CGRectMake(0.0, 0.0, widthInPoints, heightInPoints), targetImageRef);
    
    // Retrieve the UIImage from the current context
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    
    
    
    
    return image;
}

- (UIImage*)drawImageFast:(unsigned char*)targetBuffer withColorSpace:(CGColorSpaceRef)targetColorspace withContext:(CGContextRef)targetContext withDataProvider:(CGDataProviderRef)targetDataProvider withImageRef:(CGImageRef)targetImageRef
{
    int aWidth = gAppWidth;
    int aHeight = gAppHeight;
    NSInteger x = 0, y = 0;
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(x, y, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, targetBuffer);
    UIImage *image = [UIImage imageWithCGImage:targetImageRef];
    return image;
}

- (UIImage*)drawImage:(unsigned char*)targetBuffer
{
    [self drawFrameWithoutPresenting]; // drawFrame];
    
    //GLint backingWidth, backingHeight;
    
    //glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    
    int aWidth = gAppWidth;
    int aHeight = gAppHeight;
    
    NSInteger x = 0, y = 0;
    
    NSInteger dataLength = aWidth * aHeight * 4;
    
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    
    glReadPixels(x, y, aWidth, aHeight, GL_RGBA, GL_UNSIGNED_BYTE, targetBuffer);
    
    
    CGDataProviderRef ref = CGDataProviderCreateWithData(NULL, targetBuffer, dataLength, NULL);
    
    
    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    
    
    CGImageRef iref = CGImageCreate(aWidth, aHeight, 8, 32, aWidth * 4, colorspace, kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast, ref, NULL, true, kCGRenderingIntentDefault);
    
    
    //UIGraphicsBeginImageContext(CGSizeMake(aWidth, aHeight));
    
    
    CGContextRef cgcontext = CGBitmapContextCreate(NULL, aWidth, aHeight, 8, aWidth * 4,
                                            colorspace, kCGImageAlphaNoneSkipLast);
    
    //CGContextRef cgcontext = UIGraphicsGetCurrentContext();
    //CGContextSetBlendMode(cgcontext, kCGBlendModeCopy);
    
    CGContextDrawImage(cgcontext, CGRectMake(0.0, 0.0, aWidth, aHeight), iref);
    
    //CGContextScaleCTM(cgcontext, 1.0f, -1.0f);
    
    UIImage *image = [UIImage imageWithCGImage:iref]; //UIGraphicsGetImageFromCurrentImageContext();
    
    //UIGraphicsEndImageContext();
    //free(data);
    
    CGContextRelease(cgcontext);
    CFRelease(ref);
    CFRelease(colorspace);
    CGImageRelease(iref);
    
    
    [self andThenWePresent];
    
    return image;
}

- (UIImage*)renderToImage:(unsigned char*)targetBuffer
{
    [self drawFrameWithoutPresenting];
    
    
    //if(gRand.GetBool()) return  [UIImage imageNamed:@"home_back.png"];
    //else  return  [UIImage imageNamed:@"home_back_upgraded.png"];
    
    //GLint backingWidth, backingHeight;
    
    // Bind the color renderbuffer used to render the OpenGL ES view
    // If your application only creates a single color renderbuffer which is already bound at this point, 
    // this call is redundant, but it is needed if you're dealing with multiple renderbuffers.
    // Note, replace "_colorRenderbuffer" with the actual name of the renderbuffer object defined in your class.
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    
    // Get the size of the backing CAEAGLLayer
    //glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    //glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    NSInteger x = 0, y = 0, width = gAppWidth, height = gAppHeight;
    NSInteger dataLength = width * height * 4;
    
    //GLubyte *data = (GLubyte*)malloc(dataLength * sizeof(GLubyte));
    
    // Read pixel data from the framebuffer
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, targetBuffer);
    
    // Create a CGImage with the pixel data
    // If your OpenGL ES content is opaque, use kCGImageAlphaNoneSkipLast to ignore the alpha channel
    // otherwise, use kCGImageAlphaPremultipliedLast
    CGDataProviderRef ref = CGDataProviderCreateWithData(NULL, targetBuffer, dataLength, NULL);
    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref = CGImageCreate(width, height, 8, 32, width * 4, colorspace, kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast,
                                    ref, NULL, true, kCGRenderingIntentDefault);
    
    // OpenGL ES measures data in PIXELS
    // Create a graphics context with the target size measured in POINTS
    NSInteger widthInPoints, heightInPoints;
    
    /*
    if (NULL != UIGraphicsBeginImageContextWithOptions) {
        // On iOS 4 and later, use UIGraphicsBeginImageContextWithOptions to take the scale into consideration
        // Set the scale parameter to your OpenGL ES view's contentScaleFactor
        // so that you get a high-resolution snapshot when its value is greater than 1.0
        CGFloat scale = glView.contentScaleFactor;
        
        NSLog(@"Image Scale: %f", scale);
        
        
        widthInPoints = width / scale;
        heightInPoints = height / scale;
        
        UIGraphicsBeginImageContextWithOptions(CGSizeMake(widthInPoints, heightInPoints), NO, scale);
    }
    else {
        // On iOS prior to 4, fall back to use UIGraphicsBeginImageContext
        widthInPoints = width;
        heightInPoints = height;
        UIGraphicsBeginImageContext(CGSizeMake(widthInPoints, heightInPoints));
    }
     */
    /////
    //
    widthInPoints = width;
    heightInPoints = height;
    UIGraphicsBeginImageContext(CGSizeMake(widthInPoints, heightInPoints));
    //
    /////
    
    
    CGContextRef cgcontext = UIGraphicsGetCurrentContext();
    
    // UIKit coordinate system is upside down to GL/Quartz coordinate system
    // Flip the CGImage by rendering it to the flipped bitmap context
    // The size of the destination area is measured in POINTS
    CGContextSetBlendMode(cgcontext, kCGBlendModeCopy);
    CGContextDrawImage(cgcontext, CGRectMake(0.0, 0.0, widthInPoints, heightInPoints), iref);
    
    // Retrieve the UIImage from the current context
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    // Clean up
    //free(data);
    CGDataProviderRelease(ref);
    CGColorSpaceRelease(colorspace);
    CGImageRelease(iref);
    
    //CFRelease(ref);
    //CFRelease(colorspace);
    //CGImageRelease(iref);
    
    [self andThenWePresent];
    
    return image;
}


- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load vertex shader");
        return FALSE;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        
        //NSLog(@"Shader compile log:\n%s", log);
        
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(*shader);
        return FALSE;
    }
    
    return TRUE;
}

- (BOOL)linkProgram:(GLuint)prog
{
    GLint status;
    
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0)
        return FALSE;
    
    return TRUE;
}

- (BOOL)validateProgram:(GLuint)prog
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0)
        return FALSE;
    
    return TRUE;
}




- (void)setUpdateTimer:(NSTimer *)newTimer
{
    [updateTimer invalidate];
    updateTimer=nil;
    updateTimer = newTimer;
}

- (void)setUpdateInterval:(NSTimeInterval)interval
{
    updateInterval = interval;
    if (updateInterval)
    {
        self.updateTimer=nil;
        self.updateTimer = [NSTimer scheduledTimerWithTimeInterval:updateInterval target:self selector:@selector(updateView) userInfo:nil repeats:YES];
    }
}

- (void)setContext:(EAGLContext *)newContext
{
    if (context != newContext)
    {
        //[self deleteFramebuffer];
        //[EAGLContext setCurrentContext:newContext];
        context=newContext;
    }
}

- (void)createFramebuffer
{
    if(context && !defaultFramebuffer)
    {
        [EAGLContext setCurrentContext:context];
		
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)glView];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, framebufferWidth, framebufferHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
        
	}
}

- (void)deleteFramebuffer
{
    if(context)
    {
        [EAGLContext setCurrentContext:context];
        
        if(defaultFramebuffer)
        {
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

- (void)setFramebuffer
{
    if(context)
    {
        [EAGLContext setCurrentContext:context];
        if(!defaultFramebuffer)[self createFramebuffer];
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glViewport(0,0,framebufferWidth, framebufferHeight);
    }
}

- (BOOL)presentFramebuffer
{
    BOOL success = FALSE;
    if(context)
    {
        [EAGLContext setCurrentContext:context];
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    return success;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
#ifdef LANDSCAPE_MODE
	if(interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight)
	{
		return YES;
	}
#else
	if(interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
	{
		return YES;
	}
#endif
	return NO;
}

- (void)enterBackground
{
    
}

- (void)enterForeground
{
    
}

@end
