//
//  OpenGLView.hpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef OPENGL_VIEW_HPP
#define OPENGL_VIEW_HPP

#include "FVec2.hpp"
#include "FRect.h"
#include "FString.h"
#include "core_app_shell.h"
#include "os_core_app_shell.h"

#if (CURRENT_ENV == ENV_WIN32)
#include <windows.h>
#endif

struct GLContextAttrs {
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
    int multisamplingCount;
};

class OpenGLView {
public:
    OpenGLView();
    virtual ~OpenGLView();
    
    virtual void Kill() { }
    
    virtual bool IsReady() { return false; }
    
    virtual void SetName(const char *pName) { mName = pName; }
    
    virtual void SetContext() { }
    virtual void Prerender() { }
    virtual void Render() { }
    virtual void Postrender() { }
    virtual bool IsVSyncReady() { return false; }
    virtual void SwapBuffers() { }
    
    virtual void PollEvents() { }
    
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
    
    virtual void SetFrameSize(float width, float height) {
        mScreenSize.mX = width;
        mScreenSize.mY = height;
    }
    
#if (CURRENT_ENV == ENV_IOS)
    virtual void *GetEAGLView() const { return nullptr; }
#endif
    
#if (CURRENT_ENV == ENV_WIN32)
    virtual HWND GetWin32Window() { return NULL; }
#endif
    
#if (CURRENT_ENV == ENV_MAC)
    virtual void *GetCocoaWindow() { return NULL; }
#endif
    
//protected:
    
    FVec2                       mScreenSize;
    FVec2                       mScreenOrigin;
    FRect                       mViewport;
    
    FString                     mName;
};

extern GLContextAttrs cContextAttrs;

#endif

