//
//  PlatformOpenGLView.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PlatformOpenGLView.hpp"
#include "FApp.hpp"

//#include "platform/desktop/CCPlatformOpenGLView-desktop.h"

//#include <GL/glcorearb.h>
//#elif defined(GLFW_INCLUDE_ES1)
//#include <GLES/gl.h>

#include <cmath>

PlatformOpenGLView* GLFWEventHandler::_view = nullptr;

const std::string PlatformOpenGLView::EVENT_WINDOW_RESIZED = "glview_window_resized";
const std::string PlatformOpenGLView::EVENT_WINDOW_FOCUSED = "glview_window_focused";
const std::string PlatformOpenGLView::EVENT_WINDOW_UNFOCUSED = "glview_window_unfocused";

////////////////////////////////////////////////////
//

/*
static keyCodeItem g_keyCodeStructArray[] = {
    { GLFW_KEY_UNKNOWN         , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_SPACE           , EventKeyboard::KeyCode::KEY_SPACE         },
    { GLFW_KEY_APOSTROPHE      , EventKeyboard::KeyCode::KEY_APOSTROPHE    },
    { GLFW_KEY_COMMA           , EventKeyboard::KeyCode::KEY_COMMA         },
    { GLFW_KEY_MINUS           , EventKeyboard::KeyCode::KEY_MINUS         },
    { GLFW_KEY_PERIOD          , EventKeyboard::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_SLASH           , EventKeyboard::KeyCode::KEY_SLASH         },
    { GLFW_KEY_0               , EventKeyboard::KeyCode::KEY_0             },
    { GLFW_KEY_1               , EventKeyboard::KeyCode::KEY_1             },
    { GLFW_KEY_2               , EventKeyboard::KeyCode::KEY_2             },
    { GLFW_KEY_3               , EventKeyboard::KeyCode::KEY_3             },
    { GLFW_KEY_4               , EventKeyboard::KeyCode::KEY_4             },
    { GLFW_KEY_5               , EventKeyboard::KeyCode::KEY_5             },
    { GLFW_KEY_6               , EventKeyboard::KeyCode::KEY_6             },
    { GLFW_KEY_7               , EventKeyboard::KeyCode::KEY_7             },
    { GLFW_KEY_8               , EventKeyboard::KeyCode::KEY_8             },
    { GLFW_KEY_9               , EventKeyboard::KeyCode::KEY_9             },
    { GLFW_KEY_SEMICOLON       , EventKeyboard::KeyCode::KEY_SEMICOLON     },
    { GLFW_KEY_EQUAL           , EventKeyboard::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_A               , EventKeyboard::KeyCode::KEY_A             },
    { GLFW_KEY_B               , EventKeyboard::KeyCode::KEY_B             },
    { GLFW_KEY_C               , EventKeyboard::KeyCode::KEY_C             },
    { GLFW_KEY_D               , EventKeyboard::KeyCode::KEY_D             },
    { GLFW_KEY_E               , EventKeyboard::KeyCode::KEY_E             },
    { GLFW_KEY_F               , EventKeyboard::KeyCode::KEY_F             },
    { GLFW_KEY_G               , EventKeyboard::KeyCode::KEY_G             },
    { GLFW_KEY_H               , EventKeyboard::KeyCode::KEY_H             },
    { GLFW_KEY_I               , EventKeyboard::KeyCode::KEY_I             },
    { GLFW_KEY_J               , EventKeyboard::KeyCode::KEY_J             },
    { GLFW_KEY_K               , EventKeyboard::KeyCode::KEY_K             },
    { GLFW_KEY_L               , EventKeyboard::KeyCode::KEY_L             },
    { GLFW_KEY_M               , EventKeyboard::KeyCode::KEY_M             },
    { GLFW_KEY_N               , EventKeyboard::KeyCode::KEY_N             },
    { GLFW_KEY_O               , EventKeyboard::KeyCode::KEY_O             },
    { GLFW_KEY_P               , EventKeyboard::KeyCode::KEY_P             },
    { GLFW_KEY_Q               , EventKeyboard::KeyCode::KEY_Q             },
    { GLFW_KEY_R               , EventKeyboard::KeyCode::KEY_R             },
    { GLFW_KEY_S               , EventKeyboard::KeyCode::KEY_S             },
    { GLFW_KEY_T               , EventKeyboard::KeyCode::KEY_T             },
    { GLFW_KEY_U               , EventKeyboard::KeyCode::KEY_U             },
    { GLFW_KEY_V               , EventKeyboard::KeyCode::KEY_V             },
    { GLFW_KEY_W               , EventKeyboard::KeyCode::KEY_W             },
    { GLFW_KEY_X               , EventKeyboard::KeyCode::KEY_X             },
    { GLFW_KEY_Y               , EventKeyboard::KeyCode::KEY_Y             },
    { GLFW_KEY_Z               , EventKeyboard::KeyCode::KEY_Z             },
    { GLFW_KEY_LEFT_BRACKET    , EventKeyboard::KeyCode::KEY_LEFT_BRACKET  },
    { GLFW_KEY_BACKSLASH       , EventKeyboard::KeyCode::KEY_BACK_SLASH    },
    { GLFW_KEY_RIGHT_BRACKET   , EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
    { GLFW_KEY_GRAVE_ACCENT    , EventKeyboard::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_1         , EventKeyboard::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_2         , EventKeyboard::KeyCode::KEY_NONE          },
 
    { GLFW_KEY_ESCAPE          , EventKeyboard::KeyCode::KEY_ESCAPE        },
    { GLFW_KEY_ENTER           , EventKeyboard::KeyCode::KEY_ENTER      },
    { GLFW_KEY_TAB             , EventKeyboard::KeyCode::KEY_TAB           },
    { GLFW_KEY_BACKSPACE       , EventKeyboard::KeyCode::KEY_BACKSPACE     },
    { GLFW_KEY_INSERT          , EventKeyboard::KeyCode::KEY_INSERT        },
    { GLFW_KEY_DELETE          , EventKeyboard::KeyCode::KEY_DELETE        },
    { GLFW_KEY_RIGHT           , EventKeyboard::KeyCode::KEY_RIGHT_ARROW   },
    { GLFW_KEY_LEFT            , EventKeyboard::KeyCode::KEY_LEFT_ARROW    },
    { GLFW_KEY_DOWN            , EventKeyboard::KeyCode::KEY_DOWN_ARROW    },
    { GLFW_KEY_UP              , EventKeyboard::KeyCode::KEY_UP_ARROW      },
    { GLFW_KEY_PAGE_UP         , EventKeyboard::KeyCode::KEY_PG_UP      },
    { GLFW_KEY_PAGE_DOWN       , EventKeyboard::KeyCode::KEY_PG_DOWN    },
    { GLFW_KEY_HOME            , EventKeyboard::KeyCode::KEY_HOME       },
    { GLFW_KEY_END             , EventKeyboard::KeyCode::KEY_END           },
    { GLFW_KEY_CAPS_LOCK       , EventKeyboard::KeyCode::KEY_CAPS_LOCK     },
    { GLFW_KEY_SCROLL_LOCK     , EventKeyboard::KeyCode::KEY_SCROLL_LOCK   },
    { GLFW_KEY_NUM_LOCK        , EventKeyboard::KeyCode::KEY_NUM_LOCK      },
    { GLFW_KEY_PRINT_SCREEN    , EventKeyboard::KeyCode::KEY_PRINT         },
    { GLFW_KEY_PAUSE           , EventKeyboard::KeyCode::KEY_PAUSE         },
    { GLFW_KEY_F1              , EventKeyboard::KeyCode::KEY_F1            },
    { GLFW_KEY_F2              , EventKeyboard::KeyCode::KEY_F2            },
    { GLFW_KEY_F3              , EventKeyboard::KeyCode::KEY_F3            },
    { GLFW_KEY_F4              , EventKeyboard::KeyCode::KEY_F4            },
    { GLFW_KEY_F5              , EventKeyboard::KeyCode::KEY_F5            },
    { GLFW_KEY_F6              , EventKeyboard::KeyCode::KEY_F6            },
    { GLFW_KEY_F7              , EventKeyboard::KeyCode::KEY_F7            },
    { GLFW_KEY_F8              , EventKeyboard::KeyCode::KEY_F8            },
    { GLFW_KEY_F9              , EventKeyboard::KeyCode::KEY_F9            },
    { GLFW_KEY_F10             , EventKeyboard::KeyCode::KEY_F10           },
    { GLFW_KEY_F11             , EventKeyboard::KeyCode::KEY_F11           },
    { GLFW_KEY_F12             , EventKeyboard::KeyCode::KEY_F12           },
    { GLFW_KEY_F13             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F14             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F15             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F16             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F17             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F18             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F19             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F20             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F21             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F22             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F23             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F24             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F25             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_KP_0            , EventKeyboard::KeyCode::KEY_0             },
    { GLFW_KEY_KP_1            , EventKeyboard::KeyCode::KEY_1             },
    { GLFW_KEY_KP_2            , EventKeyboard::KeyCode::KEY_2             },
    { GLFW_KEY_KP_3            , EventKeyboard::KeyCode::KEY_3             },
    { GLFW_KEY_KP_4            , EventKeyboard::KeyCode::KEY_4             },
    { GLFW_KEY_KP_5            , EventKeyboard::KeyCode::KEY_5             },
    { GLFW_KEY_KP_6            , EventKeyboard::KeyCode::KEY_6             },
    { GLFW_KEY_KP_7            , EventKeyboard::KeyCode::KEY_7             },
    { GLFW_KEY_KP_8            , EventKeyboard::KeyCode::KEY_8             },
    { GLFW_KEY_KP_9            , EventKeyboard::KeyCode::KEY_9             },
    { GLFW_KEY_KP_DECIMAL      , EventKeyboard::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_KP_DIVIDE       , EventKeyboard::KeyCode::KEY_KP_DIVIDE     },
    { GLFW_KEY_KP_MULTIPLY     , EventKeyboard::KeyCode::KEY_KP_MULTIPLY   },
    { GLFW_KEY_KP_SUBTRACT     , EventKeyboard::KeyCode::KEY_KP_MINUS      },
    { GLFW_KEY_KP_ADD          , EventKeyboard::KeyCode::KEY_KP_PLUS       },
    { GLFW_KEY_KP_ENTER        , EventKeyboard::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_KP_EQUAL        , EventKeyboard::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_LEFT_SHIFT      , EventKeyboard::KeyCode::KEY_LEFT_SHIFT         },
    { GLFW_KEY_LEFT_CONTROL    , EventKeyboard::KeyCode::KEY_LEFT_CTRL          },
    { GLFW_KEY_LEFT_ALT        , EventKeyboard::KeyCode::KEY_LEFT_ALT           },
    { GLFW_KEY_LEFT_SUPER      , EventKeyboard::KeyCode::KEY_HYPER         },
    { GLFW_KEY_RIGHT_SHIFT     , EventKeyboard::KeyCode::KEY_RIGHT_SHIFT         },
    { GLFW_KEY_RIGHT_CONTROL   , EventKeyboard::KeyCode::KEY_RIGHT_CTRL          },
    { GLFW_KEY_RIGHT_ALT       , EventKeyboard::KeyCode::KEY_RIGHT_ALT           },
    { GLFW_KEY_RIGHT_SUPER     , EventKeyboard::KeyCode::KEY_HYPER         },
    { GLFW_KEY_MENU            , EventKeyboard::KeyCode::KEY_MENU          },
    { GLFW_KEY_LAST            , EventKeyboard::KeyCode::KEY_NONE          }
};
*/

//////////////////////////////////////////////////////////////////////////
// implement PlatformOpenGLView
//////////////////////////////////////////////////////////////////////////


PlatformOpenGLView::PlatformOpenGLView(bool initglfw) {
    
    gOpenGLView = this;
    
    _captured = false;
    _supportTouch = false;
    _isInRetinaMonitor = false;
    _isRetinaEnabled = false;
    _retinaFactor = 1;
    _mainWindow = nullptr;
    _monitor = nullptr;
    _mouseX = 0.0f;
    _mouseY = 0.0f;
    GLFWEventHandler::SetOpenGLView(this);
    if (initglfw) {
        glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
        glfwInit();
    }
}

PlatformOpenGLView::~PlatformOpenGLView() {
    printf("GLFW TERMINATION...\n\n\n\n");
    
    GLFWEventHandler::SetOpenGLView(nullptr);
    printf("glfwTerminate()\n");
    glfwTerminate();
}

PlatformOpenGLView* PlatformOpenGLView::create(const std::string& viewName)
{
    return PlatformOpenGLView::create(viewName, false);
}

PlatformOpenGLView* PlatformOpenGLView::create(const std::string& viewName, bool resizable)
{
    auto ret = new (std::nothrow) PlatformOpenGLView;
    if(ret && ret->initWithRect(viewName, FRect(0.0f, 0.0f, 960.0f, 640.0f), 1.0f, resizable)) {
        //ret->autorelease();
        return ret;
    }
    delete ret;
    ret = nullptr;
    return nullptr;
}

PlatformOpenGLView* PlatformOpenGLView::createWithRect(const std::string& viewName, FRect rect, float frameZoomFactor, bool resizable)
{
    auto ret = new (std::nothrow) PlatformOpenGLView;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor, resizable)) {
        //ret->autorelease();
        return ret;
    }
    delete ret;
    ret = nullptr;
    return nullptr;
}

PlatformOpenGLView* PlatformOpenGLView::createWithFullScreen(const std::string& viewName)
{
    auto ret = new (std::nothrow) PlatformOpenGLView();
    if(ret && ret->initWithFullScreen(viewName)) {
        //ret->autorelease();
        return ret;
    }
    
    delete ret;
    ret = nullptr;
    
    return nullptr;
}

PlatformOpenGLView* PlatformOpenGLView::createWithFullScreen(const std::string& viewName, const GLFWvidmode &videoMode, GLFWmonitor *monitor)
{
    auto ret = new (std::nothrow) PlatformOpenGLView();
    if(ret && ret->initWithFullscreen(viewName, videoMode, monitor)) {
        //ret->autorelease();
        return ret;
    }
    
    delete ret;
    ret = nullptr;
    
    return nullptr;
}

bool PlatformOpenGLView::initWithRect(const std::string& viewName, FRect rect, float frameZoomFactor, bool resizable) {
    SetName(viewName.c_str());
    glfwWindowHint(GLFW_RESIZABLE,resizable?GL_TRUE:GL_FALSE);
    glfwWindowHint(GLFW_RED_BITS,cContextAttrs.redBits);
    glfwWindowHint(GLFW_GREEN_BITS,cContextAttrs.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS,cContextAttrs.blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS,cContextAttrs.alphaBits);
    glfwWindowHint(GLFW_DEPTH_BITS,cContextAttrs.depthBits);
    glfwWindowHint(GLFW_STENCIL_BITS,cContextAttrs.stencilBits);
    
    glfwWindowHint(GLFW_SAMPLES, cContextAttrs.multisamplingCount);
    
    int neededWidth = rect.mWidth;
    int neededHeight = rect.mHeight;
    
    _mainWindow = glfwCreateWindow(neededWidth, neededHeight, viewName.c_str(), _monitor, nullptr);
    
    if (_mainWindow == nullptr) {
        std::string message = "Can't create window";
        if (!_glfwError.empty()) {
            message.append("\nMore info: \n");
            message.append(_glfwError);
        }
        os_message_box("Error launch application", message.c_str());
        return false;
    }
    
    /*
     *  Note that the created window and context may differ from what you requested,
     *  as not all parameters and hints are
     *  [hard constraints](@ref window_hints_hard).  This includes the size of the
     *  window, especially for full screen windows.  To retrieve the actual
     *  attributes of the created window and context, use queries like @ref
     *  glfwGetWindowAttrib and @ref glfwGetWindowSize.
     *
     *  see declaration glfwCreateWindow
     */
    int realW = 0, realH = 0;
    glfwGetWindowSize(_mainWindow, &realW, &realH);
    if (realW != neededWidth) {
        rect.mWidth = realW;
    }
    if (realH != neededHeight) {
        rect.mHeight = realH;
    }
    
    glfwMakeContextCurrent(_mainWindow);
    
    glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
    glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
    glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
    glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
    glfwSetFramebufferSizeCallback(_mainWindow, GLFWEventHandler::onGLFWframebuffersize);
    glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeFunCallback);
    glfwSetWindowIconifyCallback(_mainWindow, GLFWEventHandler::onGLFWWindowIconifyCallback);
    glfwSetWindowFocusCallback(_mainWindow, GLFWEventHandler::onGLFWWindowFocusCallback);
    glfwSetWindowCloseCallback(_mainWindow, GLFWEventHandler::onGLFWWindowCloseCallback);
    
    SetFrameSize(rect.mWidth, rect.mHeight);
    
    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);
    if (atof((const char*)glVersion) < 1.5) {
        char strComplain[256] = {0};
        sprintf(strComplain,
                "OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
                glVersion);
        os_message_box("OpenGL version too old", strComplain);
        return false;
    }
    
    initGlew();
    
    // Enable point size by default.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    if (cContextAttrs.multisamplingCount > 0) {
        glEnable(GL_MULTISAMPLE);
    }
    return true;
}

bool PlatformOpenGLView::initWithFullScreen(const std::string& viewName)
{
    //Create fullscreen window on primary monitor at its current video mode.
    _monitor = glfwGetPrimaryMonitor();
    if (nullptr == _monitor)
        return false;
    
    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    return initWithRect(viewName, FRect(0.0f, 0.0f, videoMode->width, videoMode->height), 1.0f, false);
}

bool PlatformOpenGLView::initWithFullscreen(const std::string &viewname, const GLFWvidmode &videoMode, GLFWmonitor *monitor)
{
    //Create fullscreen on specified monitor at the specified video mode.
    _monitor = monitor;
    if (nullptr == _monitor)
        return false;
    
    //These are soft constraints. If the video mode is retrieved at runtime, the resulting window and context should match these exactly. If invalid attribs are passed (eg. from an outdated cache), window creation will NOT fail but the actual window/context may differ.
    glfwWindowHint(GLFW_REFRESH_RATE, videoMode.refreshRate);
    glfwWindowHint(GLFW_RED_BITS, videoMode.redBits);
    glfwWindowHint(GLFW_BLUE_BITS, videoMode.blueBits);
    glfwWindowHint(GLFW_GREEN_BITS, videoMode.greenBits);
    
    return initWithRect(viewname, FRect(0.0f, 0.0f, videoMode.width, videoMode.height), 1.0f, false);
}

void *PlatformOpenGLView::GetCocoaWindow() {
    return glfwGetCocoaWindow(_mainWindow);
}

bool PlatformOpenGLView::IsReady() {
    return nullptr != _mainWindow;
}

void PlatformOpenGLView::Kill() {
    if(_mainWindow)
    {
        glfwSetWindowShouldClose(_mainWindow, 1);
        _mainWindow = nullptr;
    }
    // Release self. Otherwise, PlatformOpenGLView could not be freed.
    //release();
}

void PlatformOpenGLView::SetContext() {
    
    glfwMakeContextCurrent(_mainWindow);
    
}

void PlatformOpenGLView::Prerender() {
    
}

void PlatformOpenGLView::Render() {
    
}

void PlatformOpenGLView::Postrender() {
    
}

bool PlatformOpenGLView::IsVSyncReady() {
    return true;
}

void PlatformOpenGLView::SwapBuffers() {
    if(_mainWindow) {
        glfwSwapBuffers(_mainWindow);
    }
}

bool PlatformOpenGLView::ShouldCloseWindow() {
    if(_mainWindow)
        return glfwWindowShouldClose(_mainWindow) ? true : false;
    else
        return true;
}

void PlatformOpenGLView::PollEvents() {
    glfwPollEvents();
}

bool PlatformOpenGLView::isFullscreen() const {
    return (_monitor != nullptr);
}

void PlatformOpenGLView::setFullscreen() {
    if (this->isFullscreen()) {
        return;
    }
    _monitor = glfwGetPrimaryMonitor();
    if (nullptr == _monitor) {
        return;
    }
    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    this->setFullscreen(*videoMode, _monitor);
}

void PlatformOpenGLView::setFullscreen(int monitorIndex) {
    // set fullscreen on specific monitor
    int count = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    if (monitorIndex < 0 || monitorIndex >= count) {
        return;
    }
    GLFWmonitor* monitor = monitors[monitorIndex];
    if (nullptr == monitor) {
        return;
    }
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    this->setFullscreen(*videoMode, monitor);
}

void PlatformOpenGLView::setFullscreen(const GLFWvidmode &videoMode, GLFWmonitor *monitor) {
    _monitor = monitor;
    glfwSetWindowMonitor(_mainWindow, _monitor, 0, 0, videoMode.width, videoMode.height, videoMode.refreshRate);
}

void PlatformOpenGLView::setWindowed(int width, int height) {
    if (!this->isFullscreen()) {
        this->SetFrameSize(width, height);
    } else {
        const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
        int xpos = 0, ypos = 0;
        glfwGetMonitorPos(_monitor, &xpos, &ypos);
        xpos += (videoMode->width - width) * 0.5;
        ypos += (videoMode->height - height) * 0.5;
        _monitor = nullptr;
        glfwSetWindowMonitor(_mainWindow, nullptr, xpos, ypos, width, height, GLFW_DONT_CARE);
#if (CURRENT_ENV == ENV_MAC)
        // on mac window will sometimes lose title when windowed
        glfwSetWindowTitle(_mainWindow, mName.c());
#endif
    }
}

int PlatformOpenGLView::getMonitorCount() const {
    int count = 0;
    glfwGetMonitors(&count);
    return count;
}

FVec2 PlatformOpenGLView::getMonitorSize() const {
    GLFWmonitor* monitor = _monitor;
    if (nullptr == monitor) {
        GLFWwindow* window = this->getWindow();
        monitor = glfwGetWindowMonitor(window);
    }
    if (nullptr == monitor) {
        monitor = glfwGetPrimaryMonitor();
    }
    if (nullptr != monitor) {
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        FVec2 size = FVec2(videoMode->width, videoMode->height);
        return size;
    }
    return FVec2(0.0f, 0.0f);
}

void PlatformOpenGLView::updateFrameSize() {
    if (mScreenSize.mX > 0 && mScreenSize.mY > 0) {
        int w = 0, h = 0;
        glfwGetWindowSize(_mainWindow, &w, &h);
        printf("Read Window Size[%d x %d]\n", w, h);
        
        int frameBufferW = 0, frameBufferH = 0;
        glfwGetFramebufferSize(_mainWindow, &frameBufferW, &frameBufferH);
        
        printf("Read Frame Buffer [%d x %d]\n", frameBufferW, frameBufferH);
        
        if (frameBufferW == 2 * w && frameBufferH == 2 * h) {
            if (_isRetinaEnabled)
            {
                _retinaFactor = 1;
            }
            else
            {
                _retinaFactor = 2;
            }
            glfwSetWindowSize(_mainWindow, mScreenSize.mX/2 * _retinaFactor, mScreenSize.mY/2 * _retinaFactor);
            _isInRetinaMonitor = true;
            
            AppShellSetDeviceSize(mScreenSize.mX * 2.0f, mScreenSize.mY * 2.0f);
            
        } else {
            if (_isInRetinaMonitor) {
                _retinaFactor = 1;
            }
            glfwSetWindowSize(_mainWindow, mScreenSize.mX * _retinaFactor, mScreenSize.mY *_retinaFactor);
            _isInRetinaMonitor = false;
            AppShellSetDeviceSize(mScreenSize.mX, mScreenSize.mY);
        }
        
        
        printf("Resized [%f x %f] Ret [%d] Scale [%d]\n", mScreenSize.mX, mScreenSize.mY, _isRetinaEnabled, _retinaFactor);
    }
}

void PlatformOpenGLView::SetFrameSize(float pWidth, float pHeight) {
    OpenGLView::SetFrameSize(pWidth, pHeight);
    updateFrameSize();
}

void PlatformOpenGLView::onGLFWError(int errorID, const char* errorDesc) {
    if (_mainWindow) {
        printf("GLFWError #%d Happen, %s", errorID, errorDesc);
    } else {
        printf("GLFWError #%d Happen, %s\n", errorID, errorDesc);
    }
}

void PlatformOpenGLView::onGLFWMouseCallBack(GLFWwindow* /*window*/, int button, int action, int /*modify*/) {
    if (action == 0) {
        AppShellMouseUp(_mouseX, _mouseY, button);
    } else {
        AppShellMouseDown(_mouseX, _mouseY, button);
    }
}

void PlatformOpenGLView::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y) {
    _mouseX = (float)x;
    _mouseY = (float)y;
    if (_isInRetinaMonitor) {
        if (_retinaFactor == 1) {
            _mouseX *= 2;
            _mouseY *= 2;
        }
    }
    AppShellMouseMove(_mouseX, _mouseY);
}

void PlatformOpenGLView::onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y) {
    if (y > 0) {
        AppShellMouseWheel(-1);
    } else {
        AppShellMouseWheel(1);
    }
}



void PlatformOpenGLView::onGLFWKeyCallback(GLFWwindow* /*window*/, int key, int scancode, int action, int mods) {
    
    printf("Key: %d [%d]\n", key, action);
    
    int aKeyCode = DecodeKey(key);
    if (action == 0) {
        AppShellKeyUp(aKeyCode);
    } else {
        AppShellKeyDown(aKeyCode);
    }
}

void PlatformOpenGLView::onGLFWCharCallback(GLFWwindow* /*window*/, unsigned int character)
{
    
    /*
    char16_t wcharString[2] = { (char16_t) character, 0 };
    std::string utf8String;
    
    StringUtils::UTF16ToUTF8( wcharString, utf8String );
    static std::set<std::string> controlUnicode = {
        "\xEF\x9C\x80", // up
        "\xEF\x9C\x81", // down
        "\xEF\x9C\x82", // left
        "\xEF\x9C\x83", // right
        "\xEF\x9C\xA8", // delete
        "\xEF\x9C\xA9", // home
        "\xEF\x9C\xAB", // end
        "\xEF\x9C\xAC", // pageup
        "\xEF\x9C\xAD", // pagedown
        "\xEF\x9C\xB9"  // clear
    };
    // Check for send control key
    if (controlUnicode.find(utf8String) == controlUnicode.end())
    {
        IMEDispatcher::sharedDispatcher()->dispatchInsertText( utf8String.c_str(), utf8String.size() );
    }
    */
}

void PlatformOpenGLView::onGLFWWindowPosCallback(GLFWwindow* window, int x, int y) {
    printf("Window Pos[%d, %d]\n", x, y);
    //Director::getInstance()->setViewport();
    
}

void PlatformOpenGLView::onGLFWframebuffersize(GLFWwindow* window, int w, int h)
{
    printf("onGLFWframebuffersize(%d x %d)\n", w, h);
    float frameSizeW = mScreenSize.mX;
    float frameSizeH = mScreenSize.mY;
    float factorX = frameSizeW / w * _retinaFactor;
    float factorY = frameSizeH / h * _retinaFactor;
    if (std::abs(factorX - 0.5f) < SQRT_EPSILON && std::abs(factorY - 0.5f) < SQRT_EPSILON) {
        _isInRetinaMonitor = true;
        if (_isRetinaEnabled) {
            _retinaFactor = 1;
        } else {
            _retinaFactor = 2;
        }
        
        glfwSetWindowSize(window, static_cast<int>(frameSizeW * 0.5f * _retinaFactor) , static_cast<int>(frameSizeH * 0.5f * _retinaFactor));
    }
    else if (std::abs(factorX - 2.0f) < SQRT_EPSILON && std::abs(factorY - 2.0f) < SQRT_EPSILON) {
        _isInRetinaMonitor = false;
        _retinaFactor = 1;
        glfwSetWindowSize(window, static_cast<int>(frameSizeW * _retinaFactor), static_cast<int>(frameSizeH * _retinaFactor));
    }
}

void PlatformOpenGLView::onGLFWWindowCloseCallback(GLFWwindow* window) {
    AppShellExit();
}

void PlatformOpenGLView::onGLFWWindowSizeFunCallback(GLFWwindow* /*window*/, int width, int height) {
    if (width > 0 && height > 0) {
        //Size baseDesignSize = _designResolutionSize;
        //ResolutionPolicy baseResolutionPolicy = _resolutionPolicy;
        
        int frameWidth = width + 0.25f;
        int frameHeight = height + 0.25f;
        SetFrameSize(frameWidth, frameHeight);
    }
}

void PlatformOpenGLView::onGLFWWindowIconifyCallback(GLFWwindow* /*window*/, int iconified) {
    if (iconified == GL_TRUE) {
        AppShellPause();
    } else {
        AppShellResume();
    }
}

void PlatformOpenGLView::onGLFWWindowFocusCallback(GLFWwindow* /*window*/, int focused) {
    if (focused == GL_TRUE) {
        printf("Focused!!!\n");
        AppShellResume();
    } else {
        printf("Unfocused!!!\n");
        AppShellPause();
    }
}



// helper
bool PlatformOpenGLView::initGlew() {
    return true;
}

int PlatformOpenGLView::DecodeKey(int pKey) {
    int aResult = pKey;
    
    if (pKey == GLFW_KEY_0) { return DIK_0; }
    if (pKey == GLFW_KEY_1) { return DIK_1; }
    if (pKey == GLFW_KEY_2) { return DIK_2; }
    if (pKey == GLFW_KEY_3) { return DIK_3; }
    if (pKey == GLFW_KEY_4) { return DIK_4; }
    if (pKey == GLFW_KEY_5) { return DIK_5; }
    if (pKey == GLFW_KEY_6) { return DIK_6; }
    if (pKey == GLFW_KEY_7) { return DIK_7; }
    if (pKey == GLFW_KEY_8) { return DIK_8; }
    if (pKey == GLFW_KEY_9) { return DIK_9; }
    
    
    if (pKey == GLFW_KEY_A) { return DIK_A; }
    if (pKey == GLFW_KEY_B) { return DIK_B; }
    if (pKey == GLFW_KEY_C) { return DIK_C; }
    if (pKey == GLFW_KEY_D) { return DIK_D; }
    if (pKey == GLFW_KEY_E) { return DIK_E; }
    if (pKey == GLFW_KEY_F) { return DIK_F; }
    if (pKey == GLFW_KEY_G) { return DIK_G; }
    
    if (pKey == GLFW_KEY_H) { return DIK_H; }
    if (pKey == GLFW_KEY_I) { return DIK_I; }
    if (pKey == GLFW_KEY_J) { return DIK_J; }
    if (pKey == GLFW_KEY_K) { return DIK_K; }
    if (pKey == GLFW_KEY_L) { return DIK_L; }
    if (pKey == GLFW_KEY_M) { return DIK_M; }
    if (pKey == GLFW_KEY_N) { return DIK_N; }
    if (pKey == GLFW_KEY_O) { return DIK_O; }
    if (pKey == GLFW_KEY_P) { return DIK_P; }
    
    if (pKey == GLFW_KEY_Q) { return DIK_Q; }
    if (pKey == GLFW_KEY_R) { return DIK_R; }
    if (pKey == GLFW_KEY_S) { return DIK_S; }
    if (pKey == GLFW_KEY_T) { return DIK_T; }
    if (pKey == GLFW_KEY_U) { return DIK_U; }
    if (pKey == GLFW_KEY_V) { return DIK_V; }
    if (pKey == GLFW_KEY_W) { return DIK_W; }
    if (pKey == GLFW_KEY_X) { return DIK_X; }
    if (pKey == GLFW_KEY_Y) { return DIK_Y; }
    if (pKey == GLFW_KEY_Z) { return DIK_Z; }
    
    
    if (pKey == GLFW_KEY_F1) { return DIK_F1; }
    if (pKey == GLFW_KEY_F2) { return DIK_F2; }
    if (pKey == GLFW_KEY_F3) { return DIK_F3; }
    if (pKey == GLFW_KEY_F4) { return DIK_F4; }
    if (pKey == GLFW_KEY_F5) { return DIK_F5; }
    if (pKey == GLFW_KEY_F6) { return DIK_F6; }
    if (pKey == GLFW_KEY_F7) { return DIK_F7; }
    if (pKey == GLFW_KEY_F8) { return DIK_F8; }
    if (pKey == GLFW_KEY_F9) { return DIK_F9; }
    if (pKey == GLFW_KEY_F10) { return DIK_F10; }
    if (pKey == GLFW_KEY_F11) { return DIK_F11; }
    if (pKey == GLFW_KEY_F12) { return DIK_F12; }
    
    
    if (pKey == GLFW_KEY_ESCAPE) { return DIK_ESCAPE; }
    
    if (pKey == GLFW_KEY_DELETE) { return DIK_DELETE; }
    
    if (pKey == GLFW_KEY_SPACE) { return DIK_SPACE; }
    
    
    if (pKey == GLFW_KEY_PAUSE) { return DIK_PAUSE; }
    if (pKey == GLFW_KEY_BACKSPACE) { return DIK_BACKSPACE; }
    
    if (pKey == GLFW_KEY_LEFT_SHIFT) { return DIK_LSHIFT; }
    if (pKey == GLFW_KEY_RIGHT_SHIFT) { return DIK_RSHIFT; }
    
    if (pKey == GLFW_KEY_LEFT_ALT) { return DIK_LALT; }
    if (pKey == GLFW_KEY_RIGHT_ALT) { return DIK_RALT; }
    
    if (pKey == GLFW_KEY_LEFT_SUPER) { return DIK_LWIN; }
    if (pKey == GLFW_KEY_RIGHT_SUPER) { return DIK_RWIN; }
    
    if (pKey == GLFW_KEY_UP) { return DIK_UP; }
    if (pKey == GLFW_KEY_DOWN) { return DIK_DOWN; }
    if (pKey == GLFW_KEY_RIGHT) { return DIK_RIGHT; }
    if (pKey == GLFW_KEY_LEFT) { return DIK_LEFT; }
    
    
    
    
    
    
    
    
    
    /*
     gKeyName[DIK_0] = "0";
     gKeyName[DIK_1] = "1";
     gKeyName[DIK_2] = "2";
     gKeyName[DIK_3] = "3";
     gKeyName[DIK_4] = "4";
     gKeyName[DIK_5] = "5";
     gKeyName[DIK_6] = "6";
     gKeyName[DIK_7] = "7";
     gKeyName[DIK_8] = "8";
     gKeyName[DIK_9] = "9";
     gKeyName[DIK_A] = "A";
     gKeyName[DIK_B] = "B";
     gKeyName[DIK_C] = "C";
     gKeyName[DIK_D] = "D";
     gKeyName[DIK_E] = "E";
     gKeyName[DIK_F] = "F";
     gKeyName[DIK_G] = "G";
     gKeyName[DIK_H] = "H";
     gKeyName[DIK_I] = "I";
     gKeyName[DIK_J] = "J";
     gKeyName[DIK_K] = "K";
     gKeyName[DIK_L] = "L";
     gKeyName[DIK_M] = "M";
     gKeyName[DIK_N] = "N";
     gKeyName[DIK_O] = "O";
     gKeyName[DIK_P] = "P";
     gKeyName[DIK_Q] = "Q";
     gKeyName[DIK_R] = "R";
     gKeyName[DIK_S] = "S";
     gKeyName[DIK_T] = "T";
     gKeyName[DIK_U] = "U";
     gKeyName[DIK_V] = "V";
     gKeyName[DIK_W] = "W";
     gKeyName[DIK_X] = "X";
     gKeyName[DIK_Y] = "Y";
     gKeyName[DIK_Z] = "Z";
     gKeyName[DIK_APOSTROPHE] = "'";
     gKeyName[DIK_APPS] = "APPLICATION";
     gKeyName[DIK_BACK] = "BACKSPACE";
     gKeyName[DIK_BACKSLASH] = "\\";
     gKeyName[DIK_BACKSPACE] = "BACKSPACE";
     gKeyName[DIK_CALCULATOR] = "CALCULATOR";
     gKeyName[DIK_CAPITAL] = "CAPS LOCK";
     gKeyName[DIK_COMMA] = ",";
     gKeyName[DIK_DECIMAL] = ". (KEYPAD)";
     gKeyName[DIK_DELETE] = "DELETE";
     gKeyName[DIK_DIVIDE] = "/ (KEYPAD)";
     gKeyName[DIK_DOWN] = "DOWN ARROW";
     gKeyName[DIK_UP] = "UP ARROW";
     gKeyName[DIK_LEFT] = "LEFT ARROW";
     gKeyName[DIK_RIGHT] = "RIGHT ARROW";
     gKeyName[DIK_END] = "END";
     gKeyName[DIK_EQUALS] = "=";
     gKeyName[DIK_ESCAPE] = "ESC";
     gKeyName[DIK_F1] = "F1";
     gKeyName[DIK_F2] = "F2";
     gKeyName[DIK_F3] = "F3";
     gKeyName[DIK_F4] = "F4";
     gKeyName[DIK_F5] = "F5";
     gKeyName[DIK_F6] = "F6";
     gKeyName[DIK_F7] = "F7";
     gKeyName[DIK_F8] = "F8";
     gKeyName[DIK_F9] = "F9";
     gKeyName[DIK_F10] = "F10";
     gKeyName[DIK_F11] = "F11";
     gKeyName[DIK_F12] = "F12";
     gKeyName[DIK_GRAVE] = "`";
     gKeyName[DIK_HOME] = "HOME";
     gKeyName[DIK_INSERT] = "INSERT";
     gKeyName[DIK_LALT] = "LEFT ALT";
     gKeyName[DIK_RALT] = "RIGHT ALT";
     gKeyName[DIK_LBRACKET] = "[";
     gKeyName[DIK_RBRACKET] = "]";
     gKeyName[DIK_LCONTROL] = "LEFT CTRL";
     gKeyName[DIK_RCONTROL] = "RIGHT CTRL";
     gKeyName[DIK_LSHIFT] = "LEFT SHIFT";
     gKeyName[DIK_RSHIFT] = "RIGHT SHIFT";
     gKeyName[DIK_LWIN] = "LEFT WIN";
     gKeyName[DIK_RWIN] = "RIGHT WIN";
     gKeyName[DIK_MAIL] = "MAIL";
     gKeyName[DIK_MEDIASELECT] = "MEDIA SELECT";
     gKeyName[DIK_MEDIASTOP] = "MEDIA STOP";
     gKeyName[DIK_MINUS] = "-";
     gKeyName[DIK_MULTIPLY] = "* (KEYPAD)";
     gKeyName[DIK_MUTE] = "MUTE";
     gKeyName[DIK_MYCOMPUTER] = "MY COMPUTER";
     gKeyName[DIK_NEXTTRACK] = "NEXT TRACK";
     gKeyName[DIK_NUMLOCK] = "NUMLOCK";
     gKeyName[DIK_NUMPAD1] = "1 (KEYPAD)";
     gKeyName[DIK_NUMPAD2] = "2 (KEYPAD)";
     gKeyName[DIK_NUMPAD3] = "3 (KEYPAD)";
     gKeyName[DIK_NUMPAD4] = "4 (KEYPAD)";
     gKeyName[DIK_NUMPAD5] = "5 (KEYPAD)";
     gKeyName[DIK_NUMPAD6] = "6 (KEYPAD)";
     gKeyName[DIK_NUMPAD7] = "7 (KEYPAD)";
     gKeyName[DIK_NUMPAD8] = "8 (KEYPAD)";
     gKeyName[DIK_NUMPAD9] = "9 (KEYPAD)";
     gKeyName[DIK_NUMPAD0] = "0 (KEYPAD)";
     gKeyName[DIK_NUMPADCOMMA] = ", (KEYPAD)";
     gKeyName[DIK_NUMPADENTER] = "ENTER (KEYPAD)";
     gKeyName[DIK_NUMPADEQUALS] = "= (KEYPAD)";
     gKeyName[DIK_NUMPADMINUS] = "- (KEYPAD)";
     gKeyName[DIK_NUMPADPERIOD] = ". (KEYPAD)";
     gKeyName[DIK_NUMPADPLUS] = "+ (KEYPAD)";
     gKeyName[DIK_NUMPADSLASH] = "/ (KEYPAD)";
     gKeyName[DIK_PAUSE] = "PAUSE";
     gKeyName[DIK_PERIOD] = ".";
     gKeyName[DIK_PGDN] = "PAGE DOWN";
     gKeyName[DIK_PGUP] = "PAGE UP";
     gKeyName[DIK_PLAYPAUSE] = "PAUSE";
     gKeyName[DIK_POWER] = "POWER";
     gKeyName[DIK_PREVTRACK] = "PREVIOUS";
     gKeyName[DIK_RETURN] = "ENTER";
     gKeyName[DIK_SCROLL] = "SCROLL LOCK";
     gKeyName[DIK_SEMICOLON] = ";";
     gKeyName[DIK_SLASH] = "/";
     gKeyName[DIK_SLEEP] = "SLEEP";
     gKeyName[DIK_SPACE] = "SPACE";
     gKeyName[DIK_TAB] = "TAB";
     gKeyName[DIK_VOLUMEDOWN] = "VOLUME DOWN";
     gKeyName[DIK_VOLUMEUP] = "VOLUME UP";
     gKeyName[DIK_WAKE] = "WAKE";
     gKeyName[DIK_WEBBACK] = "WEB BACK";
     gKeyName[DIK_WEBFAVORITES] = "FAVORITES";
     gKeyName[DIK_WEBFORWARD] = "WEB FORWARD";
     gKeyName[DIK_WEBHOME] = "WEB HOME";
     gKeyName[DIK_WEBREFRESH] = "WEB REFRESH";
     gKeyName[DIK_WEBSEARCH] = "WEB SEARCH";
     gKeyName[DIK_WEBSTOP] = "WEB STOP";
     */
    
    
    return aResult;
}



