
#include "os_core_includes.h"
#include "core_includes.h"
#include "os_core_app_shell.h"

static int gOpenGLWindow = 0;

//Here is a iPad emulating screen, LOL!!
/*
int gWindowX = 300.0f;
int gWindowY = 8.0f;
int gWindowWidth = 768.0f * 7.0f / 8.0f;
int gWindowHeight = 1024.0f * 7.0f / 8.0f;

int gVirtualX = 0.0f;
int gVirtualY = 0.0f;
int gVirtualWidth = gWindowWidth;
int gVirtualHeight = gWindowHeight;
*/

int gWindowX = 110.0f;
int gWindowY = 4.0f;
int gWindowWidth = 320.0f * 1.44f;
int gWindowHeight = 568.0f * 1.44f;

int gVirtualX = 4.0f;
int gVirtualY = 4.0f;
int gVirtualWidth = gWindowWidth - 8.0f;
int gVirtualHeight = gWindowHeight - 8.0f;

using namespace std;

bool gKeyDownCtrl = false;
bool gKeyDownShift = false;
bool gKeyDownAlt = false;

#import <Foundation/Foundation.h>

void os_core_findDirectories() {
    FString aPathBundle;
    if(gDirBundle.mLength > 0){ aPathBundle = gDirBundle.c(); }

    FString aPathDocuments;
    if(gDirDocuments.mLength > 0) { aPathDocuments = gDirDocuments.c(); }

//    NSError *error;
//    NSFileManager *manager = [NSFileManager defaultManager];
//    NSURL *applicationSupport = [manager URLForDirectory:NSApplicationSupportDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:false error:&error];
//    NSString *identifier = [[NSBundle mainBundle] bundleIdentifier];
//    NSURL *folder = [applicationSupport URLByAppendingPathComponent:identifier];
//    [manager createDirectoryAtURL:folder withIntermediateDirectories:true attributes:nil error:&error];
//    NSURL *fileURL = [folder URLByAppendingPathComponent:@"TSPlogfile.txt"];
//

    printf("PATH: %s", [NSHomeDirectory() UTF8String]);

    AppShellSetDirectoryBundle(aPathBundle.c());
    AppShellSetDirectoryDocuments(aPathDocuments.c());

    //TODO: What scale?
    AppShellSetSpriteScale(2);

}

void os_core_refreshModifierKeys() {
    int aModifier = glutGetModifiers();
    if ((aModifier & GLUT_ACTIVE_SHIFT) != 0) {
        if (gKeyDownShift == false) {
            gKeyDownShift = true;
            AppShellKeyDown(DIK_LSHIFT);
        }
    } else {
        if (gKeyDownShift == true) {
            gKeyDownShift = false;
            AppShellKeyUp(DIK_LSHIFT);
        }
    }

    if ((aModifier & GLUT_ACTIVE_CTRL) != 0) {
        if (gKeyDownCtrl == false) {
            gKeyDownCtrl = true;
            AppShellKeyDown(DIK_LCONTROL);
        }
    } else {
        if (gKeyDownCtrl == true) {
            gKeyDownCtrl = false;
            AppShellKeyUp(DIK_LCONTROL);
        }
    }
    
    if ((aModifier & GLUT_ACTIVE_ALT) != 0) {
        if (gKeyDownAlt == false) {
            gKeyDownAlt = true;
            AppShellKeyDown(DIK_LALT);
        }
    } else {
        if (gKeyDownAlt == true) {
            gKeyDownAlt = false;
            AppShellKeyUp(DIK_LALT);
        }
    }
}


void os_core_render()
{
    AppShellUpdate();
    AppShellDraw();
    
    glutSwapBuffers();
}

void os_core_idle()
{
    glutPostRedisplay();
}

void os_core_resizeScreen(int pWidth, int pHeight)
{
    //Log("Resize[%d x %d]\n", pWidth, pHeight);
    AppShellSetDeviceSize((float)pWidth, (float)pHeight);
}

//glutReshapeFunc(void (*func)(int width, int height)) OPENGL_DEPRECATED(10_0, 10_9);


int os_core_getSystemKeySpecial(int pKey)
{
    int aKey = pKey;
    
    if((pKey >= 0) && (pKey <= 12))
    {
        if(pKey == 1)aKey = DIK_F1;
        if(pKey == 2)aKey = DIK_F2;
        if(pKey == 3)aKey = DIK_F3;
        if(pKey == 4)aKey = DIK_F4;
        if(pKey == 5)aKey = DIK_F5;
        if(pKey == 6)aKey = DIK_F6;
        if(pKey == 7)aKey = DIK_F7;
        if(pKey == 8)aKey = DIK_F8;
        if(pKey == 9)aKey = DIK_F9;
        if(pKey == 10)aKey = DIK_F10;
        if(pKey == 11)aKey = DIK_F11;
        if(pKey == 12)aKey = DIK_F12;
    }
    else if(pKey == 101){aKey = DIK_UP;}
    else if(pKey == 102){aKey = DIK_RIGHT;}
    else if(pKey == 103){aKey = DIK_DOWN;}
    else if(pKey == 100){aKey = DIK_LEFT;}
    return aKey;
}

int os_core_getSystemKey(char pKey) {
    int aKey = (int)pKey;
    if (((aKey) >= 65) && ((aKey) <= 90)) { aKey += 32; }

    if ((aKey >= 'a') && (aKey <= 'z')) {
        aKey -= 'a';
        
             if(aKey == 0 )aKey = DIK_A;
        else if(aKey == 1 )aKey = DIK_B;
        else if(aKey == 2 )aKey = DIK_C;
        else if(aKey == 3 )aKey = DIK_D;
        else if(aKey == 4 )aKey = DIK_E;
        else if(aKey == 5 )aKey = DIK_F;
        else if(aKey == 6 )aKey = DIK_G;
        else if(aKey == 7 )aKey = DIK_H;
        else if(aKey == 8 )aKey = DIK_I;
        else if(aKey == 9 )aKey = DIK_J;
        else if(aKey == 10)aKey = DIK_K;
        else if(aKey == 11)aKey = DIK_L;
        else if(aKey == 12)aKey = DIK_M;
        else if(aKey == 13)aKey = DIK_N;
        else if(aKey == 14)aKey = DIK_O;
        else if(aKey == 15)aKey = DIK_P;
        else if(aKey == 16)aKey = DIK_Q;
        else if(aKey == 17)aKey = DIK_R;
        else if(aKey == 18)aKey = DIK_S;
        else if(aKey == 19)aKey = DIK_T;
        else if(aKey == 20)aKey = DIK_U;
        else if(aKey == 21)aKey = DIK_V;
        else if(aKey == 22)aKey = DIK_W;
        else if(aKey == 23)aKey = DIK_X;
        else if(aKey == 24)aKey = DIK_Y;
        else aKey = DIK_Z;
    }
    else if((aKey >= '0') && (aKey <= '9'))
    {
        aKey -= '0';
        
             if(aKey == 0)aKey = DIK_0;
        else if(aKey == 1)aKey = DIK_1;
        else if(aKey == 2)aKey = DIK_2;
        else if(aKey == 3)aKey = DIK_3;
        else if(aKey == 4)aKey = DIK_4;
        else if(aKey == 5)aKey = DIK_5;
        else if(aKey == 6)aKey = DIK_6;
        else if(aKey == 7)aKey = DIK_7;
        else if(aKey == 8)aKey = DIK_8;
        else if(aKey == 9)aKey = DIK_9;
    }
    else if(aKey == 127)aKey = DIK_DELETE;
    else if(aKey == 13)aKey = DIK_ENTER;
    else {
             if(aKey == ')')aKey = DIK_0;
        else if(aKey == '!')aKey = DIK_1;
        else if(aKey == '@')aKey = DIK_2;
        else if(aKey == '#')aKey = DIK_3;
        else if(aKey == '$')aKey = DIK_4;
        else if(aKey == '%')aKey = DIK_5;
        else if(aKey == '^')aKey = DIK_6;
        else if(aKey == '&')aKey = DIK_7;
        else if(aKey == '*')aKey = DIK_8;
        else if(aKey == '(')aKey = DIK_9;
    }
    
    return aKey;
}

void os_core_keyDown(unsigned char pKey, int pX, int pY)
{
    os_core_refreshModifierKeys();
    int aSysKey = os_core_getSystemKey(pKey);
    AppShellKeyDown(aSysKey);
    //Log("KeyDown[%c] (%d) [%s]\n", pKey, aSysKey, gKeyName[aSysKey]);
}

void os_core_keyUp(unsigned char pKey, int pX, int pY)
{
    os_core_refreshModifierKeys();
    int aSysKey = os_core_getSystemKey(pKey);
    AppShellKeyUp(aSysKey);
    //Log("KeyUp[%c] (%d) [%s]\n", pKey, aSysKey, gKeyName[aSysKey]);
}

void os_core_keyDownSpecial(int pKey, int pX, int pY)
{
    os_core_refreshModifierKeys();
    AppShellKeyDown(os_core_getSystemKeySpecial(pKey));
}

void os_core_keyUpSpecial(int pKey, int pX, int pY) {
    os_core_refreshModifierKeys();
    AppShellKeyUp(os_core_getSystemKeySpecial(pKey));
}

void os_core_mouseAction(int pButton, int pState, int pX, int pY) {
    os_core_refreshModifierKeys();
    if(pState == 0)AppShellMouseDown(pX, pY, pButton);
    else if(pState == 1)AppShellMouseUp(pX, pY, pButton);
}

void os_core_mouseMove(int pX, int pY)
{
    AppShellMouseMove(pX, pY);
}

int os_core_main(int argc, char **argv) {
    gEnvironment = ENV_MAC;
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(gWindowX, gWindowY);
    glutInitWindowSize(gWindowWidth, gWindowHeight);
    
    gOpenGLWindow = glutCreateWindow("Generic Application");
    gOSVersion = 1.0f;
    gIsLargeScreen = true;
    
    os_core_findDirectories();
    AppShellSetOSVersion(gOSVersion);
    
    AppShellInitialize(ENV_MAC);

    AppShellSetDeviceSize(gWindowWidth, gWindowHeight);
    AppShellSetVirtualFrame(gVirtualX, gVirtualY, gVirtualWidth, gVirtualHeight);
    
    
    AppShellLoad();
    AppShellLoadComplete();
    
    glutDisplayFunc(os_core_render);
    glutIdleFunc(os_core_idle);
    
    glutReshapeFunc(os_core_resizeScreen);
    glutMouseFunc(os_core_mouseAction);
    
    glutKeyboardFunc(os_core_keyDown);
    glutKeyboardUpFunc(os_core_keyUp);
    glutSpecialFunc(os_core_keyDownSpecial);
    glutSpecialUpFunc(os_core_keyUpSpecial);
    glutMotionFunc(os_core_mouseMove);
    
    glutMainLoop();
    
    glutDestroyWindow(gOpenGLWindow);

    return 0;

}

