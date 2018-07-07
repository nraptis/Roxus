

#ifndef CORE_INC_H
#define CORE_INC_H

#define ENV_WIN32 0
#define ENV_MAC 1
#define ENV_IPHONE 2
#define ENV_ANDROID 3


#define LANDSCAPE_MODE 1
#undef LANDSCAPE_MODE

//#include "os_core_includes.h"
//#include "app_global.h"

#include "os_core_includes.h"
#include "os_core_outlets.h"
#include "os_core_sound.h"
#include "core_graphics.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef WIN_32_ENV
#include <strings.h>
#endif

#include <stdint.h>
#include <math.h>

#include "FTouchManager.h"
#include "FRandomizer.h"
#include "FImage.h"
#include "FRect.h"
#include "FSprite.h"
#include "FSpriteSequence.h"
#include "FString.h"
#include "FVec2.h"
#include "FVec3.h"
#include "FPoint.h"
#include "FGestureView.h"
#include "FScrollView.h"
#include "FView.h"
#include "FViewController.h"
#include "FCanvas.hpp"
#include "FWindow.hpp"
#include "FTexture.h"
#include "FTextureCache.h"
#include "FButton.h"
#include "FMatrix.h"
#include "FMath.h"
#include "FColor.h"
#include "FList.h"
#include "FFile.h"
#include "FObject.h"
#include "FSound.h"
#include "FResource.h"
#include "FNotificationCenter.hpp"

extern float gAppWidth;
extern float gAppHeight;

extern float gAppWidth2;
extern float gAppHeight2;

extern float gTouchX;
extern float gTouchY;

extern float gVirtualDevX;
extern float gVirtualDevY;

extern float gVirtualDevWidth;
extern float gVirtualDevHeight;


extern float gDeviceWidth;
extern float gDeviceHeight;

extern float gDeviceWidth2;
extern float gDeviceHeight2;

extern float gAdBannerWidth;
extern float gAdBannerHeight;
extern float gAdBannerX;
extern float gAdBannerY;

extern bool gAdBannerVisible;

extern float gVolumeSound;
extern float gVolumeMusic;

extern float gOSVersion;

extern float gAdjustmentScale;


extern bool gIsLargeScreen;
extern bool gIsRetina;

extern int gEnvironment;

extern int gSpriteScale;


extern FString gDirDocuments;
extern FString gDirBundle;
extern FString gDirExport;

extern FRandomizer gRand;
extern Graphics gG;

extern FTouchManager gTouch;
extern FTextureCache gTextureCache;
extern FNotificationCenter gNotify;

static FList sSoundList;
static FList sSoundInstanceList;
static FList sSpriteList;

#define SQRT_EPSILON 0.025f

#define DEGREES_TO_RADIANS(value) ((value) * 0.01745329251994329576923690768488)
#define RADIANS_TO_DEGREES(value) ((value) * 57.2957795130823208767981548141052)

#define DIK_ESCAPE          0x01
#define DIK_1               0x02
#define DIK_2               0x03
#define DIK_3               0x04
#define DIK_4               0x05
#define DIK_5               0x06
#define DIK_6               0x07
#define DIK_7               0x08
#define DIK_8               0x09
#define DIK_9               0x0A
#define DIK_0               0x0B

#define DIK_MINUS           0x0C    /* - on main keyboard */
#define DIK_EQUALS          0x0D
#define DIK_BACK            0x0E    /* backspace */
#define DIK_TAB             0x0F
#define DIK_Q               0x10
#define DIK_W               0x11
#define DIK_E               0x12
#define DIK_R               0x13
#define DIK_T               0x14
#define DIK_Y               0x15
#define DIK_U               0x16
#define DIK_I               0x17
#define DIK_O               0x18
#define DIK_P               0x19
#define DIK_LBRACKET        0x1A
#define DIK_RBRACKET        0x1B
#define DIK_RETURN          0x1C    /* Enter on main keyboard */
#define DIK_ENTER			0x1C    /* Enter on main keyboard */

#define DIK_LCONTROL        0x1D
#define DIK_A               0x1E
#define DIK_S               0x1F
#define DIK_D               0x20
#define DIK_F               0x21
#define DIK_G               0x22
#define DIK_H               0x23
#define DIK_J               0x24
#define DIK_K               0x25
#define DIK_L               0x26
#define DIK_SEMICOLON       0x27
#define DIK_APOSTROPHE      0x28
#define DIK_GRAVE           0x29    /* accent grave */
#define DIK_LSHIFT          0x2A
#define DIK_BACKSLASH       0x2B
#define DIK_Z               0x2C
#define DIK_X               0x2D
#define DIK_C               0x2E
#define DIK_V               0x2F
#define DIK_B               0x30
#define DIK_N               0x31
#define DIK_M               0x32
#define DIK_COMMA           0x33
#define DIK_PERIOD          0x34    /* . on main keyboard */
#define DIK_SLASH           0x35    /* / on main keyboard */
#define DIK_RSHIFT          0x36
#define DIK_MULTIPLY        0x37    /* * on numeric keypad */
#define DIK_LMENU           0x38    /* left Alt */
#define DIK_SPACE           0x39
#define DIK_CAPITAL         0x3A
#define DIK_F1              0x3B
#define DIK_F2              0x3C
#define DIK_F3              0x3D
#define DIK_F4              0x3E
#define DIK_F5              0x3F
#define DIK_F6              0x40
#define DIK_F7              0x41
#define DIK_F8              0x42
#define DIK_F9              0x43
#define DIK_F10             0x44
#define DIK_NUMLOCK         0x45
#define DIK_SCROLL          0x46    /* Scroll Lock */
#define DIK_NUMPAD7         0x47
#define DIK_NUMPAD8         0x48
#define DIK_NUMPAD9         0x49
#define DIK_SUBTRACT        0x4A    /* - on numeric keypad */
#define DIK_NUMPAD4         0x4B
#define DIK_NUMPAD5         0x4C
#define DIK_NUMPAD6         0x4D
#define DIK_ADD             0x4E    /* + on numeric keypad */
#define DIK_NUMPAD1         0x4F
#define DIK_NUMPAD2         0x50
#define DIK_NUMPAD3         0x51
#define DIK_NUMPAD0         0x52
#define DIK_DECIMAL         0x53    /* . on numeric keypad */
#define DIK_OEM_102         0x56    /* < > | on UK/Germany keyboards */
#define DIK_F11             0x57
#define DIK_F12             0x58


#define DIK_KANA            0x70    /* (Japanese keyboard)            */
#define DIK_ABNT_C1         0x73    /* / ? on Portugese (Brazilian) keyboards */
#define DIK_CONVERT         0x79    /* (Japanese keyboard)            */
#define DIK_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define DIK_YEN             0x7D    /* (Japanese keyboard)            */
#define DIK_ABNT_C2         0x7E    /* Numpad . on Portugese (Brazilian) keyboards */
#define DIK_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define DIK_PREVTRACK       0x90    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
#define DIK_AT              0x91    /*                     (NEC PC98) */
#define DIK_COLON           0x92    /*                     (NEC PC98) */
#define DIK_UNDERLINE       0x93    /*                     (NEC PC98) */
#define DIK_KANJI           0x94    /* (Japanese keyboard)            */
#define DIK_STOP            0x95    /*                     (NEC PC98) */
#define DIK_AX              0x96    /*                     (Japan AX) */
#define DIK_UNLABELED       0x97    /*                        (J3100) */
#define DIK_NEXTTRACK       0x99    /* Next Track */
#define DIK_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define DIK_RCONTROL        0x9D
#define DIK_MUTE            0xA0    /* Mute */
#define DIK_CALCULATOR      0xA1    /* Calculator */
#define DIK_PLAYPAUSE       0xA2    /* Play / Pause */
#define DIK_MEDIASTOP       0xA4    /* Media Stop */
#define DIK_VOLUMEDOWN      0xAE    /* Volume - */
#define DIK_VOLUMEUP        0xB0    /* Volume + */
#define DIK_WEBHOME         0xB2    /* Web home */
#define DIK_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define DIK_DIVIDE          0xB5    /* / on numeric keypad */
#define DIK_SYSRQ           0xB7
#define DIK_RMENU           0xB8    /* right Alt */
#define DIK_PAUSE           0xC5    /* Pause */
#define DIK_HOME            0xC7    /* Home on arrow keypad */
#define DIK_UP              0xC8    /* UpArrow on arrow keypad */
#define DIK_PRIOR           0xC9    /* PgUp on arrow keypad */
#define DIK_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define DIK_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define DIK_END             0xCF    /* End on arrow keypad */
#define DIK_DOWN            0xD0    /* DownArrow on arrow keypad */
#define DIK_NEXT            0xD1    /* PgDn on arrow keypad */
#define DIK_INSERT          0xD2    /* Insert on arrow keypad */
#define DIK_DELETE          0xD3    /* Delete on arrow keypad */
#define DIK_LWIN            0xDB    /* Left Windows key */
#define DIK_RWIN            0xDC    /* Right Windows key */
#define DIK_APPS            0xDD    /* AppMenu key */
#define DIK_POWER           0xDE    /* System Power */
#define DIK_SLEEP           0xDF    /* System Sleep */
#define DIK_WAKE            0xE3    /* System Wake */
#define DIK_WEBSEARCH       0xE5    /* Web Search */
#define DIK_WEBFAVORITES    0xE6    /* Web Favorites */
#define DIK_WEBREFRESH      0xE7    /* Web Refresh */
#define DIK_WEBSTOP         0xE8    /* Web Stop */
#define DIK_WEBFORWARD      0xE9    /* Web Forward */
#define DIK_WEBBACK         0xEA    /* Web Back */
#define DIK_MYCOMPUTER      0xEB    /* My Computer */
#define DIK_MAIL            0xEC    /* Mail */
#define DIK_MEDIASELECT     0xED    /* Media Select */

/*
*  Alternate names for keys, to facilitate transition from DOS.
*/
#define DIK_BACKSPACE       DIK_BACK            /* backspace */
#define DIK_NUMPADSTAR      DIK_MULTIPLY        /* * on numeric keypad */
#define DIK_LALT            DIK_LMENU           /* left Alt */
#define DIK_CAPSLOCK        DIK_CAPITAL         /* CapsLock */
#define DIK_NUMPADMINUS     DIK_SUBTRACT        /* - on numeric keypad */
#define DIK_NUMPADPLUS      DIK_ADD             /* + on numeric keypad */
#define DIK_NUMPADPERIOD    DIK_DECIMAL         /* . on numeric keypad */
#define DIK_NUMPADSLASH     DIK_DIVIDE          /* / on numeric keypad */
#define DIK_RALT            DIK_RMENU           /* right Alt */
#define DIK_UPARROW         DIK_UP              /* UpArrow on arrow keypad */
#define DIK_PGUP            DIK_PRIOR           /* PgUp on arrow keypad */
#define DIK_LEFTARROW       DIK_LEFT            /* LeftArrow on arrow keypad */
#define DIK_RIGHTARROW      DIK_RIGHT           /* RightArrow on arrow keypad */
#define DIK_DOWNARROW       DIK_DOWN            /* DownArrow on arrow keypad */
#define DIK_PGDN            DIK_NEXT            /* PgDn on arrow keypad */

enum FKeys
{
	m0 = DIK_0,
	m1 = DIK_1,
	m2 = DIK_2,
	m3 = DIK_3,
	m4 = DIK_4,
	m5 = DIK_5,
	m6 = DIK_6,
	m7 = DIK_7,
	m8 = DIK_8,
	m9 = DIK_9,

	mA = DIK_A,
	mB = DIK_B,
	mC = DIK_C,
	mD = DIK_D,
	mE = DIK_E,
	mF = DIK_F,
	mG = DIK_G,
	mH = DIK_H,
	mI = DIK_I,
	mJ = DIK_J,
	mK = DIK_K,
	mL = DIK_L,
	mM = DIK_M,
	mN = DIK_N,
	mO = DIK_O,
	mP = DIK_P,
	mQ = DIK_Q,
	mR = DIK_R,
	mS = DIK_S,
	mT = DIK_T,
	mU = DIK_U,
	mV = DIK_V,
	mW = DIK_W,
	mX = DIK_X,
	mY = DIK_Y,
	mZ = DIK_Z,
	mLeftShift = DIK_LSHIFT,
	mLShift = DIK_LSHIFT,
	mRightShift = DIK_RSHIFT,
	mRShift = DIK_RSHIFT,
	mLeftControl = DIK_LCONTROL,
	mRightControl = DIK_RCONTROL,
	mLeftCTRL = DIK_LCONTROL,
	mRightCTRL = DIK_RCONTROL,
	mLControl = DIK_LCONTROL,
	mRControl = DIK_RCONTROL,
	mLCTRL = DIK_LCONTROL,
	mRCTRL = DIK_RCONTROL,
	mApostrophe = DIK_APOSTROPHE,
	mApplication = DIK_APPS,
	mBack = DIK_BACK,
	mBackspace = DIK_BACKSPACE,
	mBackSpace = DIK_BACKSPACE,
	mBackSlash = DIK_BACKSLASH,
	mBackslash = DIK_BACKSLASH,
	mCalculator = DIK_CALCULATOR,
	mCapsLock = DIK_CAPITAL,
	mCapital = DIK_CAPITAL,
	mComma = DIK_COMMA,
	mDelete = DIK_DELETE,
	mSlash_Keypad = DIK_DIVIDE,
	mDivide_Keypad = DIK_DIVIDE,
	mDown = DIK_DOWN,
	mDownArrow = DIK_DOWN,
	mUp = DIK_UP,
	mUpArrow = DIK_UP,
	mLeft = DIK_LEFT,
	mLeftArrow = DIK_LEFT,
	mRight = DIK_RIGHT,
	mRightArrow = DIK_RIGHT,
	mEnd = DIK_END,
	mEquals = DIK_EQUALS,
	mPlus = DIK_EQUALS,
	mEqualSign = DIK_EQUALS,
	mEsc = DIK_ESCAPE,
	mEscape = DIK_ESCAPE,
	mF1 = DIK_F1,
	mF2 = DIK_F2,
	mF3 = DIK_F3,
	mF4 = DIK_F4,
	mF5 = DIK_F5,
	mF6 = DIK_F6,
	mF7 = DIK_F7,
	mF8 = DIK_F8,
	mF9 = DIK_F9,
	mF10 = DIK_F10,
	mF11 = DIK_F11,
	mF12 = DIK_F12,
	mTilde = DIK_GRAVE,
	mHome = DIK_HOME,
	mInsert = DIK_INSERT,
	mLeftAlt = DIK_LALT,
	mLAlt = DIK_LALT,
	mRightAlt = DIK_RALT,
	mRAlt = DIK_RALT,
	mLeftBracket = DIK_LBRACKET,
	mLBracket = DIK_LBRACKET,
	mRightBracket = DIK_RBRACKET,
	mRBracket = DIK_RBRACKET,
	mLeftWindows = DIK_LWIN,
	mLWindows = DIK_LWIN,
	mRightWindows = DIK_RWIN,
	mRWindows = DIK_RWIN,
	mMail = DIK_MAIL,
	mMediaSelect = DIK_MEDIASELECT,
	mMediaStop = DIK_MEDIASTOP,
	mMinus = DIK_MINUS,
	mUnderscore = DIK_MINUS,
	mMultiply_Keypad = DIK_MULTIPLY,
	mStar_Keypad = DIK_MULTIPLY,
	mStar = DIK_MULTIPLY,
	mAsterisk = DIK_MULTIPLY,
	mMute = DIK_MUTE,
	mMyComputer = DIK_MYCOMPUTER,
	mNext = DIK_NEXTTRACK,
	mNumLock = DIK_NUMLOCK,
	m1_Keypad = DIK_NUMPAD1,
	m2_Keypad = DIK_NUMPAD2,
	m3_Keypad = DIK_NUMPAD3,
	m4_Keypad = DIK_NUMPAD4,
	m5_Keypad = DIK_NUMPAD5,
	m6_Keypad = DIK_NUMPAD6,
	m7_Keypad = DIK_NUMPAD7,
	m8_Keypad = DIK_NUMPAD8,
	m9_Keypad = DIK_NUMPAD9,
	m0_Keypad = DIK_NUMPAD0,
	mComma_Keypad = DIK_NUMPADCOMMA,
	mEnter_Keypad = DIK_NUMPADENTER,
	mEquals_Keypad = DIK_NUMPADENTER,
	mMinus_Keypad = DIK_NUMPADMINUS,
	mPeriod_Keypad = DIK_DECIMAL,
	mPlus_Keypad = DIK_NUMPADPLUS,
	mPeriod = DIK_PERIOD,
	mPageDown = DIK_PGDN,
	mPgDn = DIK_PGDN,
	mPGDN = DIK_PGDN,
	mPageUp = DIK_PGUP,
	mPgUp = DIK_PGUP,
	mPGUP = DIK_PGUP,
	mPause = DIK_PAUSE,
	mPlayPause = DIK_PLAYPAUSE,
	mPower = DIK_POWER,
	mPreviousTrack = DIK_PREVTRACK,
	mEnter = DIK_RETURN,
	mReturn = DIK_RETURN,
	mScrollLock = DIK_SCROLL,
	mSemiColor = DIK_SEMICOLON,
	mSlash = DIK_SLASH,
	mSleep = DIK_SLEEP,
	mSpace = DIK_SPACE,
	mTab = DIK_TAB,
	mVolumeDown = DIK_VOLUMEDOWN,
	mVolumeUp = DIK_VOLUMEUP,
	mWake = DIK_WAKE,
	mWebBack = DIK_WEBBACK,
	mWebFavorites = DIK_WEBFAVORITES,
	mWebForward = DIK_WEBFORWARD,
	mWebHome = DIK_WEBHOME,
	mWebRefresh = DIK_WEBREFRESH,
	mWebSearch = DIK_WEBSEARCH,
	mWebStop = DIK_WEBSTOP,

	mNullKey
};

extern const char           *gKeyName[256];
extern bool 				gKeyPressed[256];



#endif
