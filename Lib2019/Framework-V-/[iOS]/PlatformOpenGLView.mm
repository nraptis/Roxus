//
//  PlatformOpenGLView.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PlatformOpenGLView.hpp"
#include "FApp.hpp"
#include "GLViewController.h"
#include "GLView.h"

#import <UIKit/UIKit.h>

void* PlatformOpenGLView::_pixelFormat = (void *)kEAGLColorFormatRGB565;
int PlatformOpenGLView::_depthFormat = GL_DEPTH_COMPONENT16;
int PlatformOpenGLView::_multisamplingCount = 0;

PlatformOpenGLView* PlatformOpenGLView::createWithEAGLView(void *eaglview)
{
    auto ret = new (std::nothrow) PlatformOpenGLView;
    if(ret && ret->initWithEAGLView(eaglview)) {
        //ret->autorelease();
        return ret;
    }
    delete ret;
    ret = nullptr;
    return nullptr;
}

void PlatformOpenGLView::convertAttrs() {
    if(cContextAttrs.redBits==8 && cContextAttrs.greenBits==8 && cContextAttrs.blueBits==8 && cContextAttrs.alphaBits==8)
    {
        _pixelFormat = (void *)kEAGLColorFormatRGBA8;
    } else if (cContextAttrs.redBits==5 && cContextAttrs.greenBits==6 && cContextAttrs.blueBits==5 && cContextAttrs.alphaBits==0)
    {
        _pixelFormat = (void *)kEAGLColorFormatRGB565;
    } else
    {
        //CCASSERT(0, "Unsupported render buffer pixel format. Using default");
    }
    
    if(cContextAttrs.depthBits==24 && cContextAttrs.stencilBits==8)
    {
        _depthFormat = GL_DEPTH24_STENCIL8_OES;
    } else if (cContextAttrs.depthBits==0 && cContextAttrs.stencilBits==0)
    {
        _depthFormat = 0;
    } else
    {
        //CCASSERT(0, "Unsupported format for depth and stencil buffers. Using default");
        
    }
    
    _multisamplingCount = cContextAttrs.multisamplingCount;
}

PlatformOpenGLView::PlatformOpenGLView()
{
}

PlatformOpenGLView::~PlatformOpenGLView()
{
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    //[glview release];
}

bool PlatformOpenGLView::initWithEAGLView(void *eaglview)
{
    _eaglview = eaglview;
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    
    mScreenSize.mX = gDeviceWidth;
    mScreenSize.mY = gDeviceHeight;
    
    //_screenSize.width = _designResolutionSize.width = gAppWidth;
    //_screenSize.height = _designResolutionSize.height = gAppHeight;
    //    _scaleX = _scaleY = [glview contentScaleFactor];
    
    return true;
}

bool PlatformOpenGLView::IsReady() {
    return _eaglview != nullptr;
}

bool PlatformOpenGLView::setContentScaleFactor(float contentScaleFactor)
{
    //_scaleX = _scaleY = contentScaleFactor;
    
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //[eaglview setNeedsLayout];
    
    return true;
}

float PlatformOpenGLView::getContentScaleFactor()
{
    return 1.0f;
    /*
    CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    
    float scaleFactor = [eaglview contentScaleFactor];
    
    //    CCASSERT(scaleFactor == _scaleX == _scaleY, "Logic error in GLView::getContentScaleFactor");
    
    return scaleFactor;
    */
}

void PlatformOpenGLView::Kill() {
    //[CCDirectorCaller destroy];
    // destroy EAGLView
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //[eaglview removeFromSuperview];
    //[eaglview release];
    //release();
}

void PlatformOpenGLView::Prerender() {
    
    
    
    [gGLView setFramebuffer];
    
    //AppShellUpdate();
    
    //if(displayLinkOn)
    //{
    //    displayLinkOn = NO;
    //    AppShellDraw();
    //}
    //else
    //{
    //    displayLinkOn = YES;
    //}
    
    
    
}

void PlatformOpenGLView::Render() {
    
}

void PlatformOpenGLView::Postrender() {
    //[glView presentFramebuffer];
}

bool PlatformOpenGLView::IsVSyncReady() {
    return false;
}

void PlatformOpenGLView::SetContext() {
    [gGLView setContext];
}


void PlatformOpenGLView::SwapBuffers() {
    //
    //
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //[eaglview swapBuffers];
    //
    //
    [gGLView presentFramebuffer];
    
}

void PlatformOpenGLView::setIMEKeyboardState(bool open) {
    
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //if (open) {
    //    [eaglview becomeFirstResponder];
    //} else {
    //    [eaglview resignFirstResponder];
    //}
}

FRect PlatformOpenGLView::getSafeAreaRect()
{
    
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 110000
    float version = [[UIDevice currentDevice].systemVersion floatValue];
    if (version >= 11.0f)
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpartial-availability"
        UIEdgeInsets safeAreaInsets = gGLView.safeAreaInsets;
#pragma clang diagnostic pop
        
        // Multiply contentScaleFactor since safeAreaInsets return points.
        safeAreaInsets.left *= gGLView.contentScaleFactor;
        safeAreaInsets.right *= gGLView.contentScaleFactor;
        safeAreaInsets.top *= gGLView.contentScaleFactor;
        safeAreaInsets.bottom *= gGLView.contentScaleFactor;
        
        /*
        // Get leftBottom and rightTop point in UI coordinates
        Vec2 leftBottom = Vec2(safeAreaInsets.left, _screenSize.height - safeAreaInsets.bottom);
        Vec2 rightTop = Vec2(_screenSize.width - safeAreaInsets.right, safeAreaInsets.top);
        
        // Convert a point from UI coordinates to which in design resolution coordinate.
        leftBottom.x = (leftBottom.x - _viewPortRect.origin.x) / _scaleX,
        leftBottom.y = (leftBottom.y - _viewPortRect.origin.y) / _scaleY;
        rightTop.x = (rightTop.x - _viewPortRect.origin.x) / _scaleX,
        rightTop.y = (rightTop.y - _viewPortRect.origin.y) / _scaleY;
        
        // Adjust points to make them inside design resolution
        leftBottom.x = MAX(leftBottom.x, 0);
        leftBottom.y = MIN(leftBottom.y, _designResolutionSize.height);
        rightTop.x = MIN(rightTop.x, _designResolutionSize.width);
        rightTop.y = MAX(rightTop.y, 0);
        
        // Convert to GL coordinates
        //leftBottom = Director::getInstance()->convertToGL(leftBottom);
        //rightTop = Director::getInstance()->convertToGL(rightTop);
        */
        
        return FRect(safeAreaInsets.left, safeAreaInsets.top, gDeviceWidth - (safeAreaInsets.left + safeAreaInsets.right), gDeviceHeight - (safeAreaInsets.top + safeAreaInsets.bottom));
    }
#endif
    
    // If running on iOS devices lower than 11.0, return visiable rect instead.
    return FRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
}
