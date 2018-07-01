

////////////////////////////
////    The Process     ////
////                    ////
/*
 
 1.) Turn on the computer.
 2.) Open the project.
 3.) Close the internet browser.
 4.) Build the project.
 5.) Pick something to do.
 6.) Do it, go back to 5.
 
*/
////                    ////
////                    ////
////////////////////////////

////////////////////////////
////  Write Task Here   ////
////                    ////
/*
 
 Dirt breaking works like this. And you've pondered over this for a while.
 
 There are 3 rows in which dirt may break. We keep these 3 rows and 1 lower row on the screen at all times.
 
 If dirt is broken in this area, cool.
 
 If dirt is "broken" below this layer, break the highest nearby dirt (randomly break right / left closest ties) and SHAKE the dirt.
 
 There is a color activated 3 charge item (always available) which breaks the 2 highest dirt tiles.
 
 */
////                    ////
////                    ////
////////////////////////////


#ifndef MAIN_APP_H
#define MAIN_APP_H

#define EDITOR_MODE 1
#undef EDITOR_MODE

#define TEST_MODE 1
//#undef TEST_MODE

#include "FApp.h"
#include "FPointList.h"

extern float gTileWidth;
extern float gTileHeight;

extern float gTileWidth2;
extern float gTileHeight2;

class Game;

class GLApp : public FApp
{
public:

    GLApp();
    virtual ~GLApp();
    
    virtual void                                Load();
    virtual void                                LoadComplete();
    
    void                                        LoadSounds();
    
    virtual void                                Update();
	virtual void                                Draw();
    virtual void                                DrawOver();
    
    virtual void                                SetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetDeviceSize(float pWidth, float pHeight);
    virtual void                                VirtualDeviceSizeDidChange();
    
    //FSprite                                     mBoardEdges;
    //FSprite                                     mBackground[6];
    
    FSprite                                     mDirtTextureFill;
    FSprite                                     mDirtTextureSides;
    //FSprite                                   mDirtTextureTops;
    FSprite                                     mDirtTextureBottoms;
    
    
    FSprite                                     mTileMatchableWhole[8];
    FSprite                                     mTileMatchableFront[8];
    FSprite                                     mTileMatchableFrontSelected[8];
    FSprite                                     mTileMatchableBack[8];
    
    
    FSprite                                     mTileBlock;
    FSprite                                     mTileRock;
    FSprite                                     mTileItem;
    FSprite                                     mTileGem;
    
    
    
    
    
    FSprite                                     mTransitionCenter;
    
    
    
    FSprite                                     mHeroStegoMockup;
    FSprite                                     mHeroStegoBody;
    FSprite                                     mHeroStegoBelly;
    FSprite                                     mHeroStegoHeadNub;
    FSprite                                     mHeroStegoHead;
    FSprite                                     mHeroStegoFootFront[2];
    FSprite                                     mHeroStegoSpike[3];
    FSprite                                     mHeroStegoEyeAngry;
    FSprite                                     mHeroStegoEyeNice;
    FSprite                                     mHeroStegoNostril;
    FSprite                                     mHeroStegoTail;
    FSprite                                     mHeroStegoTailSpike[4];
    FSprite                                     mHeroStegoShadow;
    
    FSprite                                     mTitleTextLetterRow1[7];
    FSprite                                     mTitleTextLetterRow2[12];
    
    FSprite                                     mTitleVolcano[3];
    
    
    FSprite                                     mTitleVolcanoSmoke[5];
    FSprite                                     mTitleVolcanoSmokeShadow[5];
    
    
    
    
    
    
    FSprite                                     mTitleMonolith[3];
    
    FSprite                                     mTitleFloorDirt;
    FSprite                                     mTitleButtonPlay[2];
    
    FSprite                                     mTitleButtonLogIn[2];
    FSprite                                     mTitleButtonStore[2];
    
    FSprite                                     mTitleButtonLeaf[2];

    FSprite                                     mTitleButtonTextPlay[4];
    
    FSprite                                     mTitleButtonTextStore[4];
    FSprite                                     mTitleButtonTextLogIn[5];
    
    
    FSprite                                     mTitleButtonStoreGem;
    

    
    
    FSprite                                     mTitleRock[4];
    FSprite                                     mTitleRockGrass[4][2];
    

    
    
    FSprite                                     mTitleSpewer;
    FSprite                                     mTitleSpewerShadow;
    
    
    FSprite                                 mTitleSun;
    
    
    FSprite                                 mTitleBackgroundSky;
    
    FSprite                                 mTitleCloud[3];
    
    
    FSprite                                 mGIItemBack;
    
    FSprite                                 mGIItemBackLocked;
    
    FSprite                                 mGIItemBackFrameBottom;
    
    
    
    FSprite                                 mGIItemProgressBar;
    FSprite                                 mGIItemProgressBarFill;
    
    FSprite                                 mGIItemLock;
    
    FSprite                                 mGIItemChargeCountIndicator;
    
    FSprite                                 mGIItemCrystal;
    FSprite                                 mGIItemMace;
    FSprite                                 mGIItemItemHammer;
    
    //FSprite                                     mGIPaperMenuBack;
    //FSprite                                     mGIPaperMenuCloseButton;
    
    FSprite                                     mGITutorialArrow;
    
    FSprite                                     mTutorialRexMockup;
    
    FSprite                                     mTutorialRexBackground;
    FSprite                                     mTutorialRexCircle;
    
    FSprite                                     mTutorialRexBody;
    
    FSprite                                     mTutorialRexJawLower;
    FSprite                                     mTutorialRexHeadBack;
    
    FSprite                                     mTutorialRexTooth[4];
    FSprite                                     mTutorialRexEye;
    FSprite                                     mTutorialRexEyePupil;
    
    FSprite                                     mTutorialRexNoseSegment;
    FSprite                                     mTutorialRexNose;
    
    FSprite                                     mTutorialRexNostrilBack;
    FSprite                                     mTutorialRexNostrilFront;
    
    //                                                      //
    //////////////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
    /////////////////          M.I.             //////////////
    //                                                      //
    //                                                      //
    
    
    //FSprite                                     mMIButtonPlayConnected;
    //FSprite                                     mMIButtonPlayAsGuest;

    
    FSprite                                 mMIDialogBackSmall;
    FSprite                                 mMIDialogBackMedium;
    FSprite                                 mMIDialogBackLarge;
    FSprite                                 mMIDialogBackScroll;
    
    FSprite                                 mMIDialogSlabBrown;
    FSprite                                 mMIDialogSlabOutOfMoves;
    
    FSprite                                 mMIDialogHeader;
    
    
    
    FSprite                                 mMIButtonBackLargeRetry;
    //FSprite                                 mMIButtonBackLargeRetryMockup;
    
    FSprite                                 mMIButtonBackLarge[4];
    FSprite                                 mMIButtonBackMedium[2];
    FSprite                                 mMIButtonBackSmall[2];
    
    FSprite                                 mMIButtonRetryCrystals;
    FSprite                                 mMIButtonRetry;
    
    FSprite                                 mMIButtonEndGame;
    FSprite                                 mMIButtonMainMenu;
    FSprite                                 mMIButtonOptions;
    FSprite                                 mMIButtonShop;

    FSprite                                 mMIButtonCancel;
    FSprite                                 mMIButtonOkay;
    
    FSprite                                 mMIButtonFacebook;
    FSprite                                 mMIButtonReplay;
    
    FSprite                                 mMIPrizeChestClosed;
    FSprite                                 mMIPrizeChestOpen;
    
    FSprite                                 mMILevelUpStar[2];
    
    //                                                      //
    //////////////////////////////////////////////////////////
    
    
    //FSprite                                 mEnhancementMenuBack;
    //FSprite                                 mEnhancementMenuSlot;
    //FSprite                                 mEnhancementItem[6][2];
    
    
    

    FSprite                                 mGIScoreBar[3];
    FSprite                                 mGIScoreBarItem[6];
    

    
    
    //FSprite                                 mInterfaceTopBack;
    //FSprite                                 mInterfaceTopButtonMenu[3];
    //FSprite                                 mInterfaceTopMovesBox;
    
    //FSprite                                 mInterfaceTopScoreBarSmall;
    //FSprite                                 mInterfaceTopScoreBarLarge;
    
    //FSprite                                 mInterfaceTopScoreBarItemSlot;
    //FSprite                                 mInterfaceTopScoreBarGem[3];
    
    
    FSprite                                 mInterfaceBottomBack;

    FSprite                                 mAdBannerDemo;

    
    
    
    
    
    
    
    
    //====================================================================================================
    //====================================================================================================
    //=========================  EFFECTS  ================================================================
    //====================================================================================================
    //====================================================================================================
    
    //New fucking EFFECTS!!
    FSprite                                     mEffectSpecialOrbiter;
    FSprite                                     mEffectSpecialOrbiterHalo;
    FSprite                                     mEffectSpecialOrbiterHaloNaked;
    
    
    
    //mm_background_mountains_back.png
    //mm_background_mountains_front.png
    //mm_background_sky.png
    //mm_bottom_mockup.png
    //mm_bottom_sand.png
    
    
    
    //FSprite                                 mStarEarnText[4];
    //FSprite                                 mStarEarnTextGlow[4];
    
    
    
    
    
    //FSpriteSequence                         mSequenceEffectSmoke;
    //FSpriteSequence                         mSequenceEffectBurst;
    
    //FSpriteSequence                         mSequenceExplosion;
    
    FSpriteSequence                         mSequenceRockCrumble[2];
    
    
    FSpriteSequence                         mSequenceSparkleBlast;
    
    
    FSpriteSequence                         mSequenceParticleStream;
    
    
    //FSpriteSequence                         mSequenceSparkleSphereStart;
    //FSpriteSequence                         mSequenceSparkleSphereLoop;
    //FSpriteSequence                         mSequenceSparkleSphereStop;
    
    
    
    
    //effect_blast_overlay_
    
    
    FSpriteSequence                         mSequenceBlast;
    
    FSpriteSequence                         mSequenceLaserLoop;
    
    //FSpriteSequence                         mSequenceBubbleRing;

    
    
    FSpriteSequence                         mSequenceGlowBall;
    
    //FSpriteSequence                         mSequenceEffectLightSmokePlume;
    FSpriteSequence                         mSequenceEffectBolt;
    FSpriteSequence                         mSequenceEffectBoltGlow;
    
    
    FSpriteSequence                         mSequenceBurst;
    
    FSpriteSequence                         mSequenceEffectTileBurn[2];
    //FSpriteSequence                         mSequenceEffectHilightSquareWhite;
    
    FSpriteSequence                         mSequenceEffectSpiralLoop[2];
    
    FSpriteSequence                         mSequenceTwinkleSphere;
    
    FSpriteSequence                         mSequenceCoinSpin[5];
    
    
    
    FSpriteSequence                         mSequenceOrangeSmoke;
    
    
    FSprite                                 mEffectMagicBubble;
    FSprite                                 mEffectMagicBubbleSmall;
    
    FSprite                                 mEffectMagicSphere;
    FSprite                                 mEffectMagicSphereSmall;
    
    FSprite                                 mEffectSmokePuff;
    
    
    
    //FSpriteSequence                         mSequenceEffectBlastJet1;
    //FSpriteSequence                         mSequenceEffectBlastJet2;
    //FSpriteSequence                         mSequenceEffectBlastColor;
    
    
    
    
    
    //FSprite                                 mEffectParticleHot[4];
    //FSprite                                 mEffectParticleHotSmall[4];
    //FSprite                                 mEffectParticleCool[4];
    //FSprite                                 mEffectParticleCoolSmall[4];
    //FSprite                                 mEffectSparkleAdditive[8][8];
    
    FSprite                                 mEffectSparkleAdditive[8][4];
    
    FSprite                                 mEffectParticleWarm[4];
    FSprite                                 mEffectParticleWarmSmall[4];
    FSprite                                 mEffectParticleCool[4];
    FSprite                                 mEffectParticleCoolSmall[4];
    
    
    
    
    
    
    FSprite                                 mEffectParticleShooterStar;
    FSprite                                 mEffectParticleShooterStarSmall;
    
    FSprite                                 mEffectParticleShooterTetra;
    FSprite                                 mEffectParticleShooterTetraSmall;
    
    
    
    
    
    //FSprite                                 mEffectTwinkleYellow[8];
    //FSprite                                 mEffectTwinkleYellowLarge[8];
    
    //FSprite                                 mEffectTwinkleWhiteLarge[2];
    //FSprite                                 mEffectTwinkleWhite[2];
    
    
    //PrizeChestDialog.h
    
    //FSprite                                 mEffectTwinkle[2];
    //FSprite                                 mEffectTwinkleLarge[2];
    //FSprite                                 mEffectTwinkleAdditivePinwheel[2];
    //FSprite                                 mEffectTwinkleAdditive[3];
    //FSprite                                 mEffectTwinkleAdditiveLarge[3];
    
    //FSprite                                 mEffectTwinkleWhiteHard[2];
    FSprite                                 mEffectTwinkleWhite[2];
    FSprite                                 mEffectTwinkleWhiteSmall[2];
    
    
    FSprite                                 mEffectTwinkleAdditiveWhite;
    FSprite                                 mEffectTwinkleAdditiveWhiteSmall;
    
    //FSprite                                 mEffectTwinkleAdditiveYellow;
    //FSprite                                 mEffectTwinkleAdditiveYellowSmall;
    
    //FSprite                                 mEffectTwinkleAdditiveGreen;
    //FSprite                                 mEffectTwinkleAdditiveGreenSmall;
    

    
    FSprite                                 mEffectGlowHaloLargeAdditive[3];
    FSprite                                 mEffectGlowHaloSmallAdditive[3];

    
    
    
    //FSprite                                 mEffectLightRay[6];
    //FSprite                                 mEffectLightRayWide[6];
    
    
    
    FSprite                                 mEffectLaserBurnSmall;
    FSprite                                 mEffectLaserBurn;
    
    //FSprite                                 mEffectLightFlareSmall;
    //FSprite                                 mEffectLightFlare;
    
    
    //FSprite                                 mEffectHaloSmall[2];
    //FSprite                                 mEffectHaloMedium[3];
    //FSprite                                 mEffectHaloLarge[2];
    
    
    
    
    
    //FSprite                                 mEffectDebrisCoin;
    
    //FSprite                                 mEffectLightSmearBlue;
    //FSprite                                 mEffectLightSmearBlueBubbles;
    
    
    
    //FSprite                                     mEffectBeamAdditive;
    //FSprite                                     mEffectBeamColor;
    
    //FSprite                                     mEffectBoomHalo;
    
    //PrizeChestDialog.h
    
    
    
    //====================================================================================================
    //====================================================================================================
    //====================================================================================================
    
    
    
    
    
    FFont                                   mFontDialogHeader;
    
    FFont                                   mFontScoreLarge;
    FFont                                   mFontScoreSmall;
    
    //FFont                                   mFontGameText;
    //FFont                                   mFontGameTextBig;
    FFont                                   mFontMovesRemaining;
    
    FFont                                   mFontItem;
    
    FFont                                   mFontGameBubblesLarge;
    FFont                                   mFontGameBubblesSmall;
    
    

    
    
    
    
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
    
    FPointPath                              *mEggBorder;
    
};

extern GLApp *gApp;

#endif



