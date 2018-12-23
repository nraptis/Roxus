//
//  PlatformOpenGLView.hpp
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
#include "glfw3.h"

//#if (CURRENT_ENV == ENV_MAC)
#include "glfw3native.h"
//#endif


/*
class OpenGLView {
public:
    OpenGLView();
    virtual ~OpenGLView();
    
    virtual void Kill() { }
    
    virtual bool IsReady() { return false; }
    
    virtual void Prerender() { }
    virtual void Render() { }
    virtual void Postrender() { }
    virtual bool IsVSyncReady() { return false; }
    virtual void SwapBuffers() { }
    
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
    
    static PlatformOpenGLView* create(const std::string& viewName);
    static PlatformOpenGLView* create(const std::string& viewName, bool resizable);
    static PlatformOpenGLView* createWithRect(const std::string& viewName, FRect size, float frameZoomFactor = 1.0f, bool resizable = false);
    static PlatformOpenGLView* createWithFullScreen(const std::string& viewName);
    static PlatformOpenGLView* createWithFullScreen(const std::string& viewName, const GLFWvidmode &videoMode, GLFWmonitor *monitor);
    
    //virtual void SetName(const char *pName);
    
    virtual void Kill();
    virtual bool IsReady();
    
    virtual void PollEvents();
    virtual void Prerender();
    virtual void Render();
    virtual void Postrender();
    virtual bool IsVSyncReady();
    virtual void SwapBuffers();
    
    //On the MAC we close the window... iPhone, NO
    virtual bool ShouldCloseWindow();
    
    virtual void SetFrameSize(float pWidth, float pHeight);
    
    GLFWwindow* getWindow() const { return _mainWindow; }
    
    bool isFullscreen() const;
    void setFullscreen();
    void setFullscreen(int monitorIndex);
    void setFullscreen(const GLFWvidmode &videoMode, GLFWmonitor *monitor);
    void setWindowed(int width, int height);
    int getMonitorCount() const;
    FVec2 getMonitorSize() const;

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    virtual void *GetCocoaWindow();
#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    
protected:
    PlatformOpenGLView(bool initglfw = true);
    virtual ~PlatformOpenGLView();
    
    //();
    //virtual ~PlatformOpenGLView();
    
    
    
    bool initWithRect(const std::string& viewName, FRect rect, float frameZoomFactor, bool resizable);
    bool initWithFullScreen(const std::string& viewName);
    bool initWithFullscreen(const std::string& viewname, const GLFWvidmode &videoMode, GLFWmonitor *monitor);
    
    bool initGlew();
    
    void updateFrameSize();
    
    // GLFW callbacks
    void onGLFWError(int errorID, const char* errorDesc);
    void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
    void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
    void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
    void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
    void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified);
    void onGLFWWindowFocusCallback(GLFWwindow* window, int focused);
    void onGLFWWindowCloseCallback(GLFWwindow* window);
    
    int DecodeKey(int pKey);
    
    
    bool _captured;
    bool _supportTouch;
    bool _isInRetinaMonitor;
    bool _isRetinaEnabled;
    int  _retinaFactor;  // Should be 1 or 2
    
    //float _frameZoomFactor;
    
    GLFWwindow* _mainWindow;
    GLFWmonitor* _monitor;
    
    std::string _glfwError;
    
    float _mouseX;
    float _mouseY;
    
    friend class GLFWEventHandler;
    
public:
    // View will trigger an event when window is resized, gains or loses focus
    static const std::string EVENT_WINDOW_RESIZED;
    static const std::string EVENT_WINDOW_FOCUSED;
    static const std::string EVENT_WINDOW_UNFOCUSED;
    
    //private:
    //CC_DISALLOW_COPY_AND_ASSIGN(GLViewImpl);
};


class GLFWEventHandler
{
public:
    static void onGLFWError(int errorID, const char* errorDesc)
    {
        if (_view)
            _view->onGLFWError(errorID, errorDesc);
    }
    
    static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
    {
        if (_view)
            _view->onGLFWMouseCallBack(window, button, action, modify);
    }
    
    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
    {
        if (_view)
            _view->onGLFWMouseMoveCallBack(window, x, y);
    }
    
    static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
    {
        if (_view)
            _view->onGLFWMouseScrollCallback(window, x, y);
    }
    
    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (_view)
            _view->onGLFWKeyCallback(window, key, scancode, action, mods);
    }
    
    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character)
    {
        if (_view)
            _view->onGLFWCharCallback(window, character);
    }
    
    static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
    {
        if (_view)
            _view->onGLFWWindowPosCallback(windows, x, y);
    }
    
    static void onGLFWframebuffersize(GLFWwindow* window, int w, int h)
    {
        if (_view)
            _view->onGLFWframebuffersize(window, w, h);
    }
    
    static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
    {
        if (_view)
            _view->onGLFWWindowSizeFunCallback(window, width, height);
    }
    
    static void SetOpenGLView(PlatformOpenGLView* view) {
        _view = view;
    }
    
    static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
    {
        if (_view)
        {
            _view->onGLFWWindowIconifyCallback(window, iconified);
        }
    }
    
    static void onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
    {
        if (_view)
        {
            _view->onGLFWWindowFocusCallback(window, focused);
        }
    }
    
    static void onGLFWWindowCloseCallback(GLFWwindow* window) {
        if (_view) {
            _view->onGLFWWindowCloseCallback(window);
        }
    }
    
    
    
private:
    static PlatformOpenGLView* _view;
};

#endif

