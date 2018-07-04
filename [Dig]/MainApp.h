//
//  MainApp.h
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef MAIN_APP_H
#define MAIN_APP_H

#define EDITOR_MODE 1
#undef EDITOR_MODE


#define DISABLE_SOUNDS 1
//#undef DISABLE_SOUNDS

#include "FApp.h"
#include "FModelData.h"
#include "FSpriteSequence.h"
#include "WiggleButton.h"
#include "FXML.h"
#include "FFont.h"
#include "Transition.h"
#include "GameStoreScreen.h"

#include "GameMetaData.h"

#define DEFAULT_GRID_WIDTH 7

#define ACC_NONE 0
#define ACC_BOMB 1
#define ACC_HORIZONTAL 2
#define ACC_VERTICAL 3
#define ACC_QUAD 4
#define ACC_COMBO 5
#define ACC_FIREBALL 6
#define ACC_RANDOM 100

#define POWERUP_RANDOM_SMALL 100
#define POWERUP_RANDOM_BIG 101


#define TREASURE_RANDOM 200

#define LEVEL_STAR_1_RELIC_INDEX 750
#define LEVEL_STAR_2_RELIC_INDEX 751
#define LEVEL_STAR_3_RELIC_INDEX 752

extern float gTileWidth;
extern float gTileHeight;

extern float gTileWidth2;
extern float gTileHeight2;

class Game;
class MainMenu;
class GameMenu;

//class PopoverContainer;
//class PopoverView;

class MainApp : public FApp
{
public:

    MainApp();
    virtual ~MainApp();


	//FSpriteSequence							mNewSeqBust;

	//FSpriteSequence							mNewSeqSmoke1;
	//FSpriteSequence							mNewSeqSmoke2;
	//FSpriteSequence							mNewSeqSmoke3;

	//FSpriteSequence							mNewSeqSmokeFast1;
	//FSpriteSequence							mNewSeqSmokeFast2;
	//FSpriteSequence							mNewSeqSmokeFast3;

    
    FSpriteSequence							mSeqTest[64];
    

    
    virtual void                            Load();
    virtual void                            LoadComplete();
    
    
    void                                    LoadMain();
    void                                    LoadEffects();
    void                                    LoadInterface();
    void                                    LoadSounds();
    
    
    
    virtual void                            Update();
	virtual void                            Draw();
    virtual void                            DrawOver();
    
    virtual void                            MouseDown(float pX, float pY);
	virtual void                            MouseUp(float pX, float pY);
	virtual void                            MouseMove(float pX, float pY);
    
    bool                                    IsPaused();
    
    
    GameMetaData                            mMeta;
    
    void                                    PopupGameMenu();
    void                                    PopupOptionsMenu();
    void                                    PopupStoreMenu();
    
    
    void                                    ClosePopup();
    
    void                                    PopupAnimateTopOut();
    void                                    PopupAnimateInTop();
    void                                    PopupAnimateInSecond();
    
    bool                                    mPopoverShowing;
    float                                   mPopoverFade;
    
    
	//FSpriteSequence							mTestSequence[60];
    //FSprite                                 mWrapSprite;

    FSprite                                 mTileEggWhole[8];
    FSprite                                 mTileEggFront[8];
    FSprite                                 mTileEggFrontSelected[8];
    FSprite                                 mTileEggBack[8];
    
    
    //FSprite                                 mTileBubbleWhole[8][3];
    //FSprite                                 mTileBubbleBack[8][3];
    //FSprite                                 mTileBubbleEgg[8][3];
    //FSprite                                 mTileBubbleEggShadow[8];
    //FSprite                                 mTileBubbleEggSelected[8][3];
    
    
    FSprite                                 mTransitionCenter;
    
    
    
    
    FSprite                                 mHeroStegoMockup;
    
    
    FSprite                                 mHeroStegoBody;
    FSprite                                 mHeroStegoBelly;
    
    FSprite                                 mHeroStegoHeadNub;
    
    FSprite                                 mHeroStegoHead;

    
    FSprite                                 mHeroStegoFootFront[2];
    
    FSprite                                 mHeroStegoSpike[3];
    
    FSprite                                 mHeroStegoEye;
    FSprite                                 mHeroStegoNostril;
    
    
    FSprite                                 mHeroStegoTail;
    FSprite                                 mHeroStegoTailSpike[4];
    
    
    FSprite                                 mHeroStegoShadow;
    

    
    
    
    
    
    FSprite                                 mGameTileTreasureBuried[3][4];
    FSprite                                 mGameTileTreasureLarge[3];
    
    FSprite                                 mGameTileTreasureRandomSmall;
    FSprite                                 mGameTileTreasureRandomLarge;
    
    FSprite                                 mGameTilePowerupRandomSmall;
    FSprite                                 mGameTilePowerupRandomLarge;
    
    
    FSprite                                 mGameTileBone;
    
    
    

    FSprite                                 mTileDefaultBuriedMask;
    
    FSprite                                 mGameTileRockBuried;
    FSprite                                 mGameTileRock;
    FSprite                                 mGameTileRockCracked[2];
    
    
    FSprite                                 mGameTileMetal[9];
    FSprite                                 mGameTileMetalBuried[9][2];
    
    
    FSprite                                 mGameTilePowerupGenericBuried;
    FSprite                                 mGameTilePowerupBack;
    FSprite                                 mGameTilePowerupGeneric;
    
    
    
    FSprite                                 mGameTileLevelStar;
    FSprite                                 mGameTileLevelStarBuried[3];
    
    
    
    
    
    FSprite                                 mDirtTextureFill;
    FSprite                                 mDirtTextureSides;
    //FSprite                                 mDirtTextureTops;
    FSprite                                 mDirtTextureBottoms;
    FSprite                                 mBackgroundFill;
    
    
    FSprite                                 mWallLoopLeft[3];
    FSprite                                 mWallLoopRight[3];
    
    
    
    
    
    
    
    
    FSprite                                 mTitleTextLetterRow1[7];
    FSprite                                 mTitleTextLetterRow2[12];
    
    //FSprite                                 mLevelPickBack;
    //FSprite                                 mLevelPickCellBack;
    
    
    
    FSprite                                 mTitleVolcano[3];
    
    
    FSprite                                 mTitleVolcanoSmoke[5];
    FSprite                                 mTitleVolcanoSmokeShadow[5];
    
    
    
    
    
    
    FSprite                                 mTitleMonolith[3];
    FSprite                                 mTitleStego;
    
    
    FSprite                                 mTitleFloorDirt;
    FSprite                                 mTitleFloorMockup;
    
    
    //title_bottom_dirt
    
    
    
    
    //FSprite                                 mTitleMockup;
    
    
    
    //FSprite                                 mTitleButtonMockup;
    
    
    FSprite                                 mTitleButtonPlay[2];
    
    FSprite                                 mTitleButtonLogIn[2];
    FSprite                                 mTitleButtonStore[2];
    
    
    
    
    
    FSprite                                 mTitleButtonLeaf[2];

    FSprite                                 mTitleButtonTextPlay[4];
    
    FSprite                                 mTitleButtonTextStore[4];
    FSprite                                 mTitleButtonTextLogIn[5];
    
    
    FSprite                                 mTitleButtonStoreGem;
    

    
    
    FSprite                                 mTitleRock[4];
    FSprite                                 mTitleRockGrass[4][2];
    

    
    
    FSprite                                 mTitleSpewer;
    FSprite                                 mTitleSpewerShadow;
    
    
    
    
    FSprite                                 mTitleSun;
    
    FSprite                                 mTitleSunMiddle;
    FSprite                                 mTitleSunSpokes;
    
    
    
    FSprite                                 mTitleBackgroundSky;
    //FSprite                                 mTitleBackgroundCliff[2];
    
    
    //FSprite                                 mTitleSandBottom;
    
    FSprite                                 mTitleCloud[3];
    
    
    
    
    
    //mm_background_mountains_back.png
    //mm_background_mountains_front.png
    //mm_background_sky.png
    //mm_bottom_mockup.png
    //mm_bottom_sand.png
    
    
    
    //FSprite                                 mStarEarnText[4];
    //FSprite                                 mStarEarnTextGlow[4];
    
    
    
    
    
    //FSpriteSequence                         mSequenceEffectSmoke;
    //FSpriteSequence                         mSequenceEffectBurst;
    
    FSpriteSequence                         mSequenceBlast1;
    FSpriteSequence                         mSequenceBlast2;
    
    
    FSpriteSequence                         mSequenceParticleStream;
    
    FSpriteSequence                         mSequenceExplosion;
    
    FSpriteSequence                         mSequenceRockCrumble[2];

    
    FSpriteSequence                         mSequenceLaserLoop;
    
    //FSpriteSequence                         mSequenceBubbleRing;
    
    FSpriteSequence                         mSequenceSparkleSphereStart;
    FSpriteSequence                         mSequenceSparkleSphereLoop;
    FSpriteSequence                         mSequenceSparkleSphereStop;
    FSpriteSequence                         mSequenceSparkleYellow;
    
    
    FSpriteSequence                         mSequenceGlowBall;
    
    FSpriteSequence                         mSequenceEffectLightSmokePlume;
    
    FSpriteSequence                         mSequenceEffectBolt;
    //FSpriteSequence                         mSequenceEffectBoltGlow;
    
    
    FSpriteSequence                         mSequenceBurst;
    
    FSpriteSequence                         mSequenceEffectHilight1;
    FSpriteSequence                         mSequenceEffectHilight2;
    //FSpriteSequence                         mSequenceEffectHilightSquareWhite;
    
    FSpriteSequence                         mSequenceEffectSpiralLoop;
    FSpriteSequence                         mSequenceEffectSpiralLoopWide;
    
    FSpriteSequence                         mSequenceTwinkleSphere;
    
    FSpriteSequence                         mSequenceCoinSpin[5];
    
    
    
    FSpriteSequence                         mSequenceEffectEnegyBoom;
    FSpriteSequence                         mSequenceEffectJetBlast;
    FSpriteSequence                         mSequenceEffectSmallBurnLoop;
    //FSpriteSequence                         mSequenceEffectZipFlare;
    
    
    
    //FSpriteSequence                         mSequenceEffectBlastJet1;
    //FSpriteSequence                         mSequenceEffectBlastJet2;
    //FSpriteSequence                         mSequenceEffectBlastColor;
    
    
    
    
    
    
    FSprite                                 mEffectParticleHot[4];
    //FSprite                                 mEffectParticleHotSmall[4];
    FSprite                                 mEffectParticleCool[4];
    //FSprite                                 mEffectParticleCoolSmall[4];
    FSprite                                 mEffectSparkleAdditive[8][8];
    
    
    
    
    
    
    FSprite                                 mEffectParticleStar[6];
    
    FSprite                                 mEffectParticleFlare[2][4];
    FSprite                                 mEffectParticleFlareLarge[2][4];
    
    
    
    
    FSprite                                 mEffectTwinkleYellow[8];
    FSprite                                 mEffectTwinkleYellowLarge[8];
    
    //FSprite                                 mEffectTwinkleWhiteLarge[2];
    //FSprite                                 mEffectTwinkleWhite[2];
    
    
    FSprite                                 mEffectTwinkle[2];
    FSprite                                 mEffectTwinkleLarge[2];
    FSprite                                 mEffectTwinkleAdditivePinwheel[2];
    FSprite                                 mEffectTwinkleAdditive[3];
    FSprite                                 mEffectTwinkleAdditiveLarge[3];
    

    
    //FSprite                                 mEffectLightRay[6];
    //FSprite                                 mEffectLightRayWide[6];
    
    
    
    FSprite                                 mEffectLaserNode[2];
    FSprite                                 mEffectLaserNodeLarge[2];
    
    
    //FSprite                                 mEffectHaloSmall[2];
    FSprite                                 mEffectHaloMedium[3];
    FSprite                                 mEffectHaloLarge[2];
    
    
    FSprite                                 mEffectLightSpinner[3];
    FSprite                                 mEffectLightSpinnerLarge[3];
    
    
    
    //FSprite                                 mEffectDebrisCoin;
    
    //FSprite                                 mEffectLightSmearBlue;
    //FSprite                                 mEffectLightSmearBlueBubbles;
    
    FSprite                                 mEffectSpecialOrbiter;
    FSprite                                 mEffectSpecialOrbiterHalo;
    FSprite                                 mEffectSpecialOrbiterHaloNaked;
    
    FSprite                                 mEffectBeamAdditive;
    FSprite                                 mEffectBeamColor;
    
    FSprite                                 mEffectBoomHalo;
    
    


    FSprite                                 mSexyButt;
    FSprite                                 mSexyButtBlurred;
    

    
    FSprite                                 mGIButtonPause;
    
    FSprite                                 mGIScoreBarBack;
    FSprite                                 mGIScoreBarShadow;
    FSprite                                 mGIScoreBarMockup;
    
    FSprite                                 mGIProgressBarBack;
    FSprite                                 mGIProgressBarShadow;
    FSprite                                 mGIProgressBarFill;
    FSprite                                 mGIProgressBarMockup;
    
    FSprite                                 mGIMovesBox;
    
    FSprite                                 mGIStarBarBack[3];
    FSprite                                 mGIStarBarShadow[3];
    FSprite                                 mGIStarBarComplete[3];
    
    //FSprite                                 mGIStarBarMockup;
    
    
    //FSprite                                 mGIChargerMockup;
    
    FSprite                                 mGIItemBack;
    FSprite                                 mGIItemBackInactive;
    
    //FSprite                                 mGIItemBackInset;
    //FSprite                                 mGIItemBackInsetActive;
    
    
    
    
    
    FSprite                                 mGIRockHammerBack;
    FSprite                                 mGIThunderboneBack;
    
    
    
    FSprite                                 mGIPaperMenuBack;
    FSprite                                 mGIPaperMenuCloseButton;
    
    
    FSprite                                 mGITutorialArrow;
    FSprite                                 mGIAccessoryBone[2];
    
    FSprite                                 mTutorialRexMockup;
    
    FSprite                                 mTutorialRexBackground;
    FSprite                                 mTutorialRexCircle;
    
    FSprite                                 mTutorialRexBody;
    
    FSprite                                 mTutorialRexJawLower;
    FSprite                                 mTutorialRexHeadBack;
    
    FSprite                                 mTutorialRexTooth[4];
    FSprite                                 mTutorialRexEye;
    FSprite                                 mTutorialRexEyePupil;
    
    FSprite                                 mTutorialRexNoseSegment;
    FSprite                                 mTutorialRexNose;
    
    FSprite                                 mTutorialRexNostrilBack;
    FSprite                                 mTutorialRexNostrilFront;
    
    //                                                      //
    //////////////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
    /////////////////          M.I.             //////////////
    //                                                      //
    //                                                      //
    
    
    FSprite                                 mMIButtonPlayConnected;
    FSprite                                 mMIButtonPlayAsGuest;
    
    


    
    
    FSprite                                 mMIBigButton[3];
    FSprite                                 mMIBigButtonShadow[3];
    
    FSprite                                 mMIBigButtonTextOkay;
    FSprite                                 mMIBigButtonTextCancel;
    FSprite                                 mMIBigButtonTextDone;
    FSprite                                 mMIBigButtonTextGotIt;
    FSprite                                 mMIBigButtonTextOptions;
    FSprite                                 mMIBigButtonTextQuit;
    FSprite                                 mMIBigButtonTextResume;
    FSprite                                 mMIBigButtonTextRetry;
    FSprite                                 mMIBigButtonTextStore;
    FSprite                                 mMIBigButtonTextYes;
    
    
    FSprite                                 mMIDialogBackSmall;
    FSprite                                 mMIDialogBackLarge;
    
    
    FSprite                                 mMIPrizeChestClosed;
    FSprite                                 mMIPrizeChestOpen;
    
    FSprite                                 mMIPrizeGem[2];
    FSprite                                 mMIPrizeGemGlow[2];
    
    //FSprite                                 mMIHeaderCell[3];
    
    
    FSprite                                 mMILevelUpDisplayStar;
    FSprite                                 mMILevelUpDisplayStarEmpty;
	FSprite                                 mMILevelUpDisplayStarGlowRing;

    
    
	FSprite                                 mMILevelUpTextWinY[2];
	FSprite                                 mMILevelUpTextWinO[2];
	FSprite                                 mMILevelUpTextWinU[2];
	FSprite                                 mMILevelUpTextWinW[2];
	FSprite                                 mMILevelUpTextWinI[2];
	FSprite                                 mMILevelUpTextWinN[2];
	FSprite                                 mMILevelUpTextWinExc[2];

	FSprite                                 mMILevelUpTextNoMovesN[2];
	FSprite                                 mMILevelUpTextNoMovesO[2];
	FSprite                                 mMILevelUpTextNoMovesM[2];
	FSprite                                 mMILevelUpTextNoMovesV[2];
	FSprite                                 mMILevelUpTextNoMovesE[2];
	FSprite                                 mMILevelUpTextNoMovesS[2];
	FSprite                                 mMILevelUpTextNoMovesL[2];
	FSprite                                 mMILevelUpTextNoMovesF[2];
	FSprite                                 mMILevelUpTextNoMovesT[2];
	FSprite                                 mMILevelUpTextNoMovesDot[2];
    
    //mi_menu_header_medium
    //mi_menu_header_short
    //mi_menu_header_tall
    
    //                                                      //
    //////////////////////////////////////////////////////////
    
    
    //FSprite                                 mEnhancementMenuBack;
    //FSprite                                 mEnhancementMenuSlot;
    //FSprite                                 mEnhancementItem[6][2];
    
    
    

    
    
    
    //FSprite                                 mInterfaceTopBack;
    
    FSprite                                 mInterfaceTopButtonMenu[3];
    
    FSprite                                 mInterfaceTopMovesBox;
    
    
    FSprite                                 mInterfaceTopScoreBarSmall;
    FSprite                                 mInterfaceTopScoreBarLarge;
    
    FSprite                                 mInterfaceTopScoreBarItemSlot;
    
    FSprite                                 mInterfaceTopScoreBarGem[3];
    
    
    FSprite                                 mInterfaceBottomBack;
    
    
    //FSprite                                 mGameMenuBack;
    //FSprite                                 mLevelCompleteMenuBackLose;
    //FSprite                                 mLevelCompleteMenuBackWin;
    
    
    FSprite                                 mTimeOverMenuStar[3];

    
    
    
    FSprite                                 mGameTextStart[4];
    
    
    //FSprite                                 mAstronaut;
    

    FSprite                                 mAdBannerDemo;
    
    
    
    FFont                                   mFontMainDisplayFront;
    FFont                                   mFontMainDisplayMiddle;
    FFont                                   mFontMainDisplayStroke;
    
    FFont                                   mFontScore;
    
    //FFont                                   mFontGameText;
    //FFont                                   mFontGameTextBig;
    
    FFont                                   mFontMovesRemaining;
    //FFont                                   mFontScoreBar;

    
    

    
    
    
    
    FSound                                  mSoundChainSelect;
    FSound                                  mSoundChainDeselect;
    
    FSound                                  mSoundMatchChain;
    FSound                                  mSoundMatchSpecial;
    FSound                                  mSoundMatchStarting;
    
    FSound                                  mSoundTileLanded;
    
    FSound                                  mSoundLevelUp;
    
    FSound                                  mSoundJarCharge;
    FSound                                  mSoundJarBlast;
    
    FSound                                  mSoundJarCollect;
    
    
    
    
    
    FSound                                  mSoundBlasterChargeUp;
    FSound                                  mSoundBlasterTrigger;
    FSound                                  mSoundBlasterEnd;
    
    
    
    FSound                                  mSoundStartAnimationBeep;
    FSound                                  mSoundStartAnimationGo;
    
    FSound                                  mSoundDirtBreak[3];
    
    FSound                                  mSoundRockBreak[2];
    
    FSound                                  mSoundMetalBreak[2];
    
    FSound                                  mSoundRockChink;
    FSound                                  mSoundMetalChink;
    
    FSound                                  mSoundRise[2];
    
    FSound                                  mSoundDiscoverGeneric;
    FSound                                  mSoundDiscoverTreasure;
    FSound                                  mSoundDiscoverStar;
    
    
    
    
    FSound                                  mSoundMenuStarEarn;
    FSound                                  mSoundButtonClick;
    
    FSound                                  mSoundTitleLetterBonk;
    
    
    
    
    
    Transition                              *mTransition;
    FView                                   *mTransitionToView;
    FView                                   *mTransitionFromView;
    
    bool                                    TransitionInProgress(){return (mTransition != 0);}
    void                                    TransitionTo(FView *pToView, FView *pFromView, Transition *pTransition);
    void                                    TransitionSwapViews();
    
    
    int                                     mTestIndex;
    
    
    
    
    
    
    
    
};

extern MainApp *gApp;

#endif



