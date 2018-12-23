//
//  .hpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef PlatformOpenGLView_hpp
#define PlatformOpenGLView_hpp


#ifndef GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_NSGL
#endif

#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

//#include "base/CCRef.h"
//#include "platform/CCCommon.h"
//#include "platform/CCGLView.h"
#include "OpenGLView.hpp"


/*
class OpenGLView {
public:
    OpenGLView();
    virtual ~OpenGLView();
    
 
    
 
    
    virtual bool ShouldCloseWindow() { return false; };
    
    
    static void SetGLContextAttrs(GLContextAttrs& glContextAttrs);
    static GLContextAttrs GetGLContextAttrs();
    
    
    FVec2 GetFrameSize() {
        FVec2 aResult;
        aResult.mX = GetFrameWidth();aResult.mY = GetFrameHeight();
        return aResult;
    }
    virtual float GetFrameHeight() { return 800.0f; }
    virtual float GetFrameWidth() { return 600.0f; }
    
    virtual void SetFrameSize(float width, float height) { }
    
#if (CURRENT_ENV == ENV_IOS)
    virtual void *GetEAGLView() const { return nullptr; }
#endif
    
protected:
    
    FVec2                       mScreenSize;
    FVec2                       mScreenOrigin;
    FRect                       mViewport;
};
*/

class PlatformOpenGLView : public OpenGLView
{
public:
    static PlatformOpenGLView* createWithEAGLView(void* eaGLView);
    
    static void convertAttrs();
    static void* _pixelFormat;
    static int _depthFormat;
    static int _multisamplingCount;
    
    /** sets the content scale factor */
    bool setContentScaleFactor(float contentScaleFactor);
    
    float getContentScaleFactor();
    
    /** returns whether or not the view is in Retina Display mode */
    bool isRetinaDisplay() {
        return getContentScaleFactor() >= 2.0;
    }
    
    virtual void *GetEAGLView() const override { return _eaglview; }
    
    // overrides
    virtual void Kill() override;
    virtual bool IsReady() override;
    
    virtual void SetContext() override;
    
    virtual void Prerender() override;
    virtual void Render() override;
    virtual void Postrender() override;
    virtual bool IsVSyncReady() override;
    virtual void SwapBuffers() override;
    
    void setIMEKeyboardState(bool bOpen);
    
    FRect getSafeAreaRect();
    
protected:
    PlatformOpenGLView();
    virtual ~PlatformOpenGLView();
    
    bool initWithEAGLView(void* eaGLView);
    bool initWithRect(const std::string& viewName, const FRect& rect, float frameZoomFactor);
    
    void *_eaglview;
};

#endif

