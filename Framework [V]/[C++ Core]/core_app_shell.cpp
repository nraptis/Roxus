
#include "core_app_shell.h"
#include "core_graphics.h"
#include "os_core_social.h"

#include "FApp.h"

float gDeviceWidth = 1024.0f;
float gDeviceHeight = 768.0f;

float gDeviceWidth2 = (gDeviceWidth / 2.0f);
float gDeviceHeight2 = (gDeviceHeight / 2.0f);

float gVirtualDevX = 0.0f;
float gVirtualDevY = 0.0f;
float gVirtualDevWidth = 640.0f;
float gVirtualDevHeight = 700.0f;

float gTouchX = 0.0f;
float gTouchY = 0.0f;

float gAppWidth = 1024.0f;
float gAppHeight = 768.0f;
float gAppWidth2 = (gAppWidth / 2.0f);
float gAppHeight2 = (gAppHeight / 2.0f);

float gOSVersion = 1.0f;

float gAdjustmentScale = 1.0f;

float gVolumeSound = 1.0f;
float gVolumeMusic = 1.0f;

float gAdBannerWidth = 0.0f;
float gAdBannerHeight = 0.0f;
float gAdBannerX = 0.0f;
float gAdBannerY = 0.0f;
bool gAdBannerVisible = false;

const char *gKeyName[256];
bool gKeyPressed[256];

FString gDirDocuments;
FString gDirBundle;

FRandomizer gRand;
FTouchManager gTouch;
FTextureCache gTextureCache;
Graphics gG;

int gEnvironment = ENV_IPHONE;
bool gIsLargeScreen = false;
bool gIsRetina = false;

void AppShellInitialize(int pEnvironment) {
    gEnvironment = pEnvironment;

	FList aResourceList;
    
	os_getAllResources(gDirBundle.c(), &aResourceList);
	os_getAllResources(gDirDocuments.c(), &aResourceList);

	EnumList(FString, aPath, aResourceList)gRes.AddResource(aPath->c());
	FreeList(FString, aResourceList);
    
    core_graphics_initialize();
    core_sound_initialize();
    social_Init();

    if(gAppBase)(gAppBase)->BaseInitialize();
    //gTouch.Initialize(pEnvironment);
    
    //sSoundList.mUnique = true;
    //sSoundInstanceList.mUnique = true;
    //sSpriteList.mUnique = true;
    
	for (int aCount = 0; aCount < 255; aCount++) {
		gKeyPressed[aCount] = false;
		gKeyName[aCount] = "???";
	}
    
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

}

void AppShellSetDeviceSize(int pWidth, int pHeight) {
	gDeviceWidth = (float)pWidth;
	gDeviceHeight = (float)pHeight;
	gDeviceWidth2 = (gDeviceWidth / 2.0f);
	gDeviceHeight2 = (gDeviceHeight / 2.0f);
    
    FApp *aApp = (gAppBase);
    if (aApp) {
		aApp->BaseSetDeviceSize(gDeviceWidth, gDeviceHeight);
        if ((gVirtualDevWidth > 0.0f) && (gVirtualDevHeight > 0.0f)) {
            aApp->BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
        }
    }
}

void AppShellSetVirtualFrame(int pX, int pY, int pWidth, int pHeight)
{
	gVirtualDevX = (float)pX;
	gVirtualDevY = (float)pY;

	gVirtualDevWidth = (float)pWidth;
	gVirtualDevHeight = (float)pHeight;

    gAppWidth = (float)pWidth;
    gAppHeight = (float)pHeight;

	FApp *aApp = gAppBase;
	if (aApp) {
        aApp->BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
	}
}





void AppShellSetDirectoryBundle(const char *pFilePath)
{
    gDirBundle = pFilePath;
}

void AppShellSetDirectoryDocuments(const char *pFilePath)
{
    gDirDocuments = pFilePath;
}

void AppShellSetOSVersion(float pOSVersion)
{
    gOSVersion = pOSVersion;
}

void AppShellLoad()
{
    if(gAppBase)(gAppBase)->BaseLoad();
}

void AppShellLoadComplete()
{
    if(gAppBase)(gAppBase)->BaseLoadComplete();
}

void AppShellUpdate()
{
    if(gAppBase)gAppBase->BaseUpdate();
}

void AppShellDraw()
{
    if (gAppBase) {
        (gAppBase)->BaseDraw();
    }
}

void AppShellTouchDownDroid(float pX, float pY, int pIndex, int pCount)
{
    if(gAppBase)(gAppBase)->BaseTouchDownDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchMoveDroid(float pX, float pY, int pIndex, int pCount)
{
    if(gAppBase)(gAppBase)->BaseTouchMoveDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchUpDroid(float pX, float pY, int pIndex, int pCount)
{
    if(gAppBase)(gAppBase)->BaseTouchUpDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchCanceledDroid(float pX, float pY, int pIndex, int pCount)
{
    if(gAppBase)(gAppBase)->BaseTouchCanceledDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchDown(float pX, float pY, void *pData)
{
    if(gAppBase) (gAppBase)->BaseTouchDown(pX, pY, pData);
}

void AppShellTouchMove(float pX, float pY, void *pData)
{
    if(gAppBase)(gAppBase)->BaseTouchMove(pX, pY, pData);
}

void AppShellTouchUp(float pX, float pY, void *pData)
{
    if(gAppBase)(gAppBase)->BaseTouchUp(pX, pY, pData);
}

void AppShellTouchCanceled(float pX, float pY, void *pData)
{
    if(gAppBase)(gAppBase)->BaseTouchCanceled(pX, pY, pData);
}

void AppShellMouseDown(float pX, float pY, int pButton)
{
	gTouchX = pX; gTouchY = pY;
	if(gAppBase)(gAppBase)->BaseMouseDown(pX, pY, pButton);
}

void AppShellMouseMove(float pX, float pY)
{
	gTouchX = pX; gTouchY = pY;
	if(gAppBase)(gAppBase)->BaseMouseMove(pX, pY);
}

void AppShellMouseUp(float pX, float pY, int pButton)
{
	gTouchX = pX; gTouchY = pY;
	if(gAppBase)(gAppBase)->BaseMouseUp(pX, pY, pButton);
}

void AppShellMouseWheel(int pDirection)
{
	if(gAppBase)gAppBase->BaseMouseWheel(pDirection);
}

void AppShellKeyDown(int pKey)
{
    //Log("AppShellKeyDown([%d]=>%s)\n", pKey, gKeyName[pKey]);
	if(gAppBase)gAppBase->BaseKeyDown(pKey);
}

void AppShellKeyUp(int pKey)
{
	if(gAppBase)gAppBase->BaseKeyUp(pKey);
}

void AppShellSetAdBannerWidth(float pWidth)
{
    
}

void AppShellSetAdBannerHeight(float pHeight)
{
    
}

void AppShellExit()
{
    if(gAppBase)
    {
        (gAppBase)->BaseInactive();
    }
}

void AppShellPause()
{
    if(gAppBase)
    {
        (gAppBase)->BaseInactive();
    }
}

void AppShellResume()
{
    if(gAppBase)
    {
        (gAppBase)->BaseActive();
    }
}


void AppShellMemoryWarning(bool pSevere)
{
    if(gAppBase)
    {
        
    }
}

void AppShellPurchaseSuccessful(const char *pName)
{
    
}

void AppShellPurchaseFailed(const char *pName)
{
    
}

void AppShellPurchaseCanceled(const char *pName)
{
    
}

void AppShellAdBannerSetHeight(const char *pName)
{
    
}

void AppShellAdBannerLoadFailed()
{
    
}

void AppShellAdBannerLoadSuccessful()
{
    
}

void AppShellAccelerometer(float pAccelX, float pAccelY, float pAccelZ)
{
    
}

