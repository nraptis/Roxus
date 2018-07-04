
#include "MainApp.h"
#include "Game.h"
#include "MainMenu.h"
#include "MapScreen.h"
#include "Board.h"
#include "GameMenu.h"
#include "GameStoreScreen.h"
#include "UMainCanvas.h"
#include "ToolzResizeScreen.h"
#include "GameTweakMenu.h"

MainApp *gApp = 0;


float gTileWidth = 80.0f;
float gTileHeight = 80.0f;

float gTileWidth2 = (gTileWidth / 2.0f);
float gTileHeight2 = (gTileHeight / 2.0f);

MainApp::MainApp()
{
    gApp = this;
    
    mTransition = 0;
    mTransitionToView = 0;
    mTransitionFromView = 0;
    
    
    gApp->mViewController.SetNaturalSize(660.0f, 768.0f);
    gApp->mViewController.FitTypeSetWidth();
    
    gApp->mViewControllerModal.SetNaturalSize(660.0f, 768.0f);
    gApp->mViewControllerModal.FitTypeSetWidth();
    
    mTestIndex = 0;
    
    mPopoverShowing = false;
    mPopoverFade = 0.0f;
    
    gApp->mViewControllerTools.ViewAdd(new ToolzResizeScreen());
    gApp->mViewControllerTools.ViewAdd(new GameTweakMenu());
    
}

MainApp::~MainApp()
{
    
}

void MainApp::Load()
{
    gTextureCache.mAutoMode = false;

    
    
    int aTestIndex = 0;
    
    
    /*
    mSeqTest[aTestIndex++].Load("effect_sparkle_circle_", 0, 67);
    mSeqTest[aTestIndex++].Load("effect_blast_overlay_", 0, 47);
    mSeqTest[aTestIndex++].Load("effect_blast_underlay_", 0, 53);
    mSeqTest[aTestIndex++].Load("effect_blast_jet_1_", 0, 54);
    mSeqTest[aTestIndex++].Load("effect_blast_jet_", 0, 53);
    mSeqTest[aTestIndex++].Load("effect_plasma_burst_", 0, 59);
    mSeqTest[aTestIndex++].Load("effect_blast_color_", 0, 47);
    mSeqTest[aTestIndex++].Load("", 0, 80);
    */
    

    
    LoadMain();
	LoadInterface();
    LoadEffects();
    
#ifndef DISABLE_SOUNDS
    LoadSounds();
#endif
}

void MainApp::LoadComplete()
{
    gApp->mViewController.ViewAdd(new Game(0));
    
    if(gBoard)
    {
        //gBoard->LevelUp();
    }
    //gApp->mViewController.ViewAdd(new MainMenu());
    
}

void MainApp::LoadMain()
{
    mWallLoopLeft[0].Load("wall_loop_left_1");
    mWallLoopLeft[1].Load("wall_loop_left_1");
    mWallLoopLeft[2].Load("wall_loop_left_1");
    
    mWallLoopRight[0].Load("wall_loop_right_1");
    mWallLoopRight[1].Load("wall_loop_right_1");
    mWallLoopRight[2].Load("wall_loop_right_1");
    
    mBackgroundFill.Load("background_loop");
    
    mDirtTextureFill.Load("dirt_fill_uvw");
    mDirtTextureSides.Load("dirt_sides_uvw");
    
    mDirtTextureBottoms.Load("dirt_corners_uvw");
    
    gImageBundler.StartBundle("bundle_tiles_1");
    for(int i=0;i<7;i++)
    {
        FString aPath = FString("tile_whole_") + FString((i + 1)) + FString("");
        mTileEggWhole[i].Load(aPath.c());
        
        aPath = FString("tile_front_") + FString((i + 1)) + FString("");
        mTileEggFront[i].Load(aPath.c());
        
        aPath = FString("tile_front_selected_") + FString((i + 1)) + FString("");
        mTileEggFrontSelected[i].Load(aPath.c());
        
        aPath = FString("tile_back_") + FString((i + 1)) + FString("");
        mTileEggBack[i].Load(aPath.c());
    }
    
    mGameTileRock.Load("tile_rock");
    mGameTileRockBuried.Load("tile_rock_buried");
    
    mGameTileRockCracked[0].Load("tile_rock_cracked_1");
    mGameTileRockCracked[1].Load("tile_rock_cracked_2");
    
    for(int i=0;i<9;i++)
    {
        FString aPath = FString("tile_metal_") + FString(i);
        mGameTileMetal[i].Load(aPath);
        
        for(int n=0;n<2;n++)
        {
            FString aPathBuried = aPath + FString("_buried_") + FString(n);
            mGameTileMetalBuried[i][n].Load(aPathBuried);
        }
    }
    
    
    
    mGameTileLevelStar.Load("level_star");
    
    mGameTileLevelStarBuried[0].Load("level_star_buried_1");
    mGameTileLevelStarBuried[1].Load("level_star_buried_2");
    mGameTileLevelStarBuried[2].Load("level_star_buried_3");
    
    mGameTilePowerupGenericBuried.Load("powerup_bomb_buried");
    mGameTilePowerupBack.Load("powerup_back");
    mGameTilePowerupGeneric.Load("powerup_time_extend_clock_back");
    
    mGameTileBone.Load("game_tile_bone");
    
    for(int i=0;i<3;i++)
    {
        FString aPathBase = FString("game_tile_treasure_") + FString((i + 1));
        mGameTileTreasureLarge[i].Load(aPathBase.c());
        
        aPathBase += FString("_buried_");
        
        for(int n=0;n<4;n++)
        {
            FString aPath = aPathBase + FString((n + 1));
            
            mGameTileTreasureBuried[i][n].Load(aPath.c());
            
            //mGameTileTreasureBuried[i][n].Load("tile_metal_buried");
        
        }
        //aPath = FString("gem_large_") + FString((i + 1));
        
    }
    
    mGameTileTreasureRandomSmall.Load("editor_button_treasure_random_small");
    mGameTileTreasureRandomLarge.Load("editor_button_treasure_random_large");
    
    mGameTilePowerupRandomSmall.Load("editor_button_powerup_random_small");
    mGameTilePowerupRandomLarge.Load("editor_button_powerup_random_large");
    
    mTileDefaultBuriedMask.Load("tile_default_buried_mask");
    
    
    
    
    gImageBundler.StartBundle("main_menu_1");
    
    mTransitionCenter.Load("transition_footprint");
    
    //mSexyButt.Load("example_image");
    //mSexyButtBlurred.Load("example_image_blurry");
    
    mTitleBackgroundSky.Load("title_sky");
    
    mTitleCloud[0].Load("mm_cloud_1_1");
    mTitleCloud[1].Load("mm_cloud_1_2");
    mTitleCloud[2].Load("mm_cloud_1_3");
    
    
    //mTitleCloud[0].Load("mm_cloud_2_1");
    //mTitleCloud[1].Load("mm_cloud_2_2");
    //mTitleCloud[2].Load("mm_cloud_2_3");
    
    
    mTitleVolcano[0].Load("title_volcano_1");
    mTitleVolcano[1].Load("title_volcano_2");
    mTitleVolcano[2].Load("title_volcano_3");
    
    
    mTitleVolcanoSmoke[0].Load("title_smoke_plume_1");
    mTitleVolcanoSmoke[1].Load("title_smoke_plume_2");
    mTitleVolcanoSmoke[2].Load("title_smoke_plume_3");
    
    //mTitleVolcanoSmokeShadow[0].Load("title_volcano_smoke_shadow_1");
    //mTitleVolcanoSmokeShadow[1].Load("title_volcano_smoke_shadow_2");
    //mTitleVolcanoSmokeShadow[2].Load("title_volcano_smoke_shadow_3");
    
    //.png
    //.png
    //.png
    //.png
    
    
    
    mTitleMonolith[0].Load("title_background_monolith_1");
    mTitleMonolith[1].Load("title_background_monolith_2");
    mTitleMonolith[2].Load("title_background_monolith_3");
    
    
    
    
    
    mTitleRock[0].Load("title_rock_1");
    mTitleRock[1].Load("title_rock_2");
    
    mTitleRockGrass[0][0].Load("title_rock_1_grass_1");
    mTitleRockGrass[0][1].Load("title_rock_1_grass_2");
    
    mTitleRockGrass[1][0].Load("title_rock_2_grass_1");
    mTitleRockGrass[1][1].Load("title_rock_2_grass_2");
    
    
    
    
    
    mTitleSpewer.Load("title_spewer");
    mTitleSpewerShadow.Load("title_spewer_shadow");
    
    
    //title_bottom_mockup
    //title_effect_spiral_small
    //title_effect_spiral
    
    
    
    
    
    
    
    
    
    
    mTitleSun.Load("title_sun");
    mTitleSunMiddle.Load("title_sun_middle");
    mTitleSunSpokes.Load("title_sun_spokes");
    
    
    
    
    
    
    
    
    mTitleStego.Load("title_stego_mockup");
    
    
    mTitleFloorDirt.Load("title_bottom_dirt");
    mTitleFloorMockup.Load("title_bottom_mockup");
    
    
    
    
    
    
    
    
    
    
    mTitleButtonPlay[0].Load("mm_button_play_stroke");
    //mTitleButtonPlay[0].Load("mm_button_play");
    mTitleButtonPlay[1].Load("mm_button_play_shadow");
    
    mTitleButtonLogIn[0].Load("mm_button_login_stroke");
    //mTitleButtonLogIn[0].Load("mm_button_login");
    mTitleButtonLogIn[1].Load("mm_button_login_shadow");
    
    mTitleButtonStore[0].Load("mm_button_store_stroke");
    //mTitleButtonStore[0].Load("mm_button_store");
    mTitleButtonStore[1].Load("mm_button_store_shadow");

    
    
    
    mTitleButtonLeaf[0].Load("mm_button_leaf");
    mTitleButtonLeaf[1].Load("mm_button_leaf_shadow");
    
    
    
    //mTitleRock[0].Load("mm_decor_rock_1");
    //mTitleRock[1].Load("mm_decor_rock_2");
    //mTitleRock[2].Load("mm_decor_rock_3");
    
    //mTitleRockCrystal[0][0].Load("mm_decor_rock_1_crystal_1");
    //mTitleRockCrystal[0][1].Load("mm_decor_rock_1_crystal_2");
    
    //mTitleRockCrystal[1][0].Load("mm_rock_2_crystal_1");
    //mTitleRockCrystal[2][0].Load("mm_rock_3_crystal_1");
    
    
    
    
    
    
    
    mTitleButtonTextPlay[0].Load("mm_button_letter_play_p");
    mTitleButtonTextPlay[1].Load("mm_button_letter_play_l");
    mTitleButtonTextPlay[2].Load("mm_button_letter_play_a");
    mTitleButtonTextPlay[3].Load("mm_button_letter_play_y");
    
    mTitleButtonTextStore[0].Load("mm_button_letter_store_s");
    mTitleButtonTextStore[1].Load("mm_button_letter_store_h");
    mTitleButtonTextStore[2].Load("mm_button_letter_store_o");
    mTitleButtonTextStore[3].Load("mm_button_letter_store_p");
    
    mTitleButtonTextLogIn[0].Load("mm_button_letter_login_l");
    mTitleButtonTextLogIn[1].Load("mm_button_letter_login_o");
    mTitleButtonTextLogIn[2].Load("mm_button_letter_login_g");
    mTitleButtonTextLogIn[3].Load("mm_button_letter_login_hyphen");
    mTitleButtonTextLogIn[4].Load("mm_button_letter_login_n");
    
    mTitleButtonStoreGem.Load("mm_button_store_gem");
    
    
    
    mTitleTextLetterRow1[0].Load("title_text_big_b");
    mTitleTextLetterRow1[1].Load("title_text_big_i");
    mTitleTextLetterRow1[2].Load("title_text_big_g");
    mTitleTextLetterRow1[3].Load("title_text_bone_b");
    mTitleTextLetterRow1[4].Load("title_text_bone_o");
    mTitleTextLetterRow1[5].Load("title_text_bone_n");
    mTitleTextLetterRow1[6].Load("title_text_bone_e");
    mTitleTextLetterRow2[0].Load("title_text_treasure_t");
    mTitleTextLetterRow2[1].Load("title_text_treasure_r1");
    mTitleTextLetterRow2[2].Load("title_text_treasure_e1");
    mTitleTextLetterRow2[3].Load("title_text_treasure_a");
    mTitleTextLetterRow2[4].Load("title_text_treasure_s");
    mTitleTextLetterRow2[5].Load("title_text_treasure_u");
    mTitleTextLetterRow2[6].Load("title_text_treasure_r2");
    mTitleTextLetterRow2[7].Load("title_text_treasure_e2");
    mTitleTextLetterRow2[8].Load("title_text_hunt_h");
    mTitleTextLetterRow2[9].Load("title_text_hunt_u");
    mTitleTextLetterRow2[10].Load("title_text_hunt_n");
    mTitleTextLetterRow2[11].Load("title_text_hunt_t");
    
    //gImageBundler.EndBundle();
}

void MainApp::LoadInterface()
{
    gImageBundler.StartBundle("interface_1");
    
    mGIButtonPause.Load("gi_button_pause");
    
    for(int i=0;i<3;i++)
    {
        FString aPath;
        
        aPath = FString("gi_star_bar_back_s") + FString((i + 1));
        mGIStarBarBack[i].Load(aPath.c());
        
        aPath = FString("gi_star_bar_back_shadow_s") + FString((i + 1));
        mGIStarBarShadow[i].Load(aPath.c());
        
        aPath = FString("gi_star_bar_earned_s") + FString((i + 1));
        mGIStarBarComplete[i].Load(aPath.c());
    }
    
    
    
    
    mGIItemBack.Load("gi_item_back");
    mGIItemBackInactive.Load("gi_item_back_empty");
    
    
    
    mGIMovesBox.Load("game_interface_moves_block");
    
    mGIScoreBarBack.Load("gi_score_bar_back");
    mGIScoreBarShadow.Load("gi_score_bar_back_shadow");
    mGIScoreBarMockup.Load("gi_score_bar_back_mockup");
    
    mGIProgressBarBack.Load("gi_progress_bar_back");
    mGIProgressBarShadow.Load("gi_progress_bar_back_shadow");
    mGIProgressBarFill.Load("gi_progress_bar_fill_blue");
    mGIProgressBarMockup.Load("gi_progress_bar_back_mockup");
    
    
    
    //mGIChargerFront.Load("gi_charge_gem_fill");
    //mGIChargerFrontFill.Load("gi_charge_gem_fill_bright");
    
    mGIPaperMenuBack.Load("gi_paper_menu_back");
    mGIPaperMenuCloseButton.Load("gi_paper_menu_button_close");
    
    
    
    mGITutorialArrow.Load("gi_tutorial_arrow");
    
    mGIAccessoryBone[0].Load("menu_bone_1");
    mGIAccessoryBone[1].Load("menu_bone_2");
    
    
    
    mMIButtonPlayConnected.Load("mi_button_play");
    mMIButtonPlayAsGuest.Load("main_menu_button_play");
    
    
    mTimeOverMenuStar[0].Load("time_over_star_1");
    mTimeOverMenuStar[1].Load("time_over_star_2");
    mTimeOverMenuStar[2].Load("time_over_star_3");
    
    mInterfaceTopMovesBox.Load("game_interface_moves_block");
    
    
    
    
    
    gImageBundler.StartBundle("menu_interface_buttons");
    
    mMIBigButton[0].Load("mi_button_large_back");
    mMIBigButtonShadow[0].Load("mi_button_large_shadow");
    
    
    mMIBigButton[1].Load("mi_button_large_blue");
    mMIBigButtonShadow[1].Load("mi_button_large_blue_shadow");
    
    
    mMIBigButton[2].Load("mi_button_large_green");
    mMIBigButtonShadow[2].Load("mi_button_large_green_shadow");
    
    
    
    mMIBigButtonTextOkay.Load("mi_button_text_okay");
    mMIBigButtonTextCancel.Load("mi_button_text_cancel");
    mMIBigButtonTextDone.Load("mi_button_text_done");
    mMIBigButtonTextGotIt.Load("mi_button_text_got_it");
    mMIBigButtonTextOptions.Load("mi_button_text_options");
    mMIBigButtonTextQuit.Load("mi_button_text_quit");
    mMIBigButtonTextResume.Load("mi_button_text_resume");
    mMIBigButtonTextRetry.Load("mi_button_text_retry");
    mMIBigButtonTextStore.Load("mi_button_text_store");
    mMIBigButtonTextYes.Load("mi_button_text_yes");
    
    //
    
    mMILevelUpDisplayStar.Load("level_up_star");
    mMILevelUpDisplayStarEmpty.Load("level_up_star_empty");
    mMILevelUpDisplayStarGlowRing.Load("gi_tutorial_arrow");
    
	mMILevelUpTextWinY[0].Load("level_complete_text_you_win_y");
	mMILevelUpTextWinO[0].Load("level_complete_text_you_win_o");
	mMILevelUpTextWinU[0].Load("level_complete_text_you_win_u");
	mMILevelUpTextWinW[0].Load("level_complete_text_you_win_w");
	mMILevelUpTextWinI[0].Load("level_complete_text_you_win_i");
	mMILevelUpTextWinN[0].Load("level_complete_text_you_win_n");
	mMILevelUpTextWinExc[0].Load("level_complete_text_you_win_exc");
	mMILevelUpTextWinY[1].Load("level_complete_text_front_you_win_y");
	mMILevelUpTextWinO[1].Load("level_complete_text_front_you_win_o");
	mMILevelUpTextWinU[1].Load("level_complete_text_front_you_win_u");
	mMILevelUpTextWinW[1].Load("level_complete_text_front_you_win_w");
	mMILevelUpTextWinI[1].Load("level_complete_text_front_you_win_i");
	mMILevelUpTextWinN[1].Load("level_complete_text_front_you_win_n");
	mMILevelUpTextWinExc[1].Load("level_complete_text_front_you_win_exc");
    mMILevelUpTextNoMovesN[0].Load("level_complete_text_no_moves_n");
    mMILevelUpTextNoMovesO[0].Load("level_complete_text_no_moves_o");
    mMILevelUpTextNoMovesM[0].Load("level_complete_text_no_moves_m");
    mMILevelUpTextNoMovesV[0].Load("level_complete_text_no_moves_v");
    mMILevelUpTextNoMovesE[0].Load("level_complete_text_no_moves_e");
    mMILevelUpTextNoMovesS[0].Load("level_complete_text_no_moves_s");
    mMILevelUpTextNoMovesL[0].Load("level_complete_text_no_moves_l");
    mMILevelUpTextNoMovesF[0].Load("level_complete_text_no_moves_f");
    mMILevelUpTextNoMovesT[0].Load("level_complete_text_no_moves_t");
    mMILevelUpTextNoMovesDot[0].Load("level_complete_text_no_moves_period");
    mMILevelUpTextNoMovesN[1].Load("level_complete_text_front_no_moves_n");
    mMILevelUpTextNoMovesO[1].Load("level_complete_text_front_no_moves_o");
    mMILevelUpTextNoMovesM[1].Load("level_complete_text_front_no_moves_m");
    mMILevelUpTextNoMovesV[1].Load("level_complete_text_front_no_moves_v");
    mMILevelUpTextNoMovesE[1].Load("level_complete_text_front_no_moves_e");
    mMILevelUpTextNoMovesS[1].Load("level_complete_text_front_no_moves_s");
    mMILevelUpTextNoMovesL[1].Load("level_complete_text_front_no_moves_l");
    mMILevelUpTextNoMovesF[1].Load("level_complete_text_front_no_moves_f");
    mMILevelUpTextNoMovesT[1].Load("level_complete_text_front_no_moves_t");
    mMILevelUpTextNoMovesDot[1].Load("level_complete_text_front_no_moves_period");
    
    gImageBundler.StartBundle("interface_assorted_fixins");
    

    
    mInterfaceTopScoreBarSmall.Load("game_interface_score_bar_small");
    mInterfaceTopScoreBarLarge.Load("game_interface_score_bar_large");
    
    mInterfaceTopScoreBarItemSlot.Load("game_interface_score_bar_item_slot");
    
    mInterfaceTopScoreBarGem[0].Load("game_interface_score_bar_item_gem_1");
    mInterfaceTopScoreBarGem[1].Load("game_interface_score_bar_item_gem_2");
    mInterfaceTopScoreBarGem[2].Load("game_interface_score_bar_item_gem_3");
    
    mInterfaceBottomBack.Load("game_interface_bottom_back_colored");
    
    mInterfaceTopButtonMenu[0].Load("game_interface_button_pause");
    mInterfaceTopButtonMenu[2].Load("game_interface_button_pause_down");
    
    
    
    
    
    gImageBundler.StartBundle("interface_buttons_n_junk");
    
    
    mGameTextStart[0].Load("game_text_start_3");
    mGameTextStart[1].Load("game_text_start_2");
    mGameTextStart[2].Load("game_text_start_1");
    mGameTextStart[3].Load("game_text_start_go");
    
    //mStarEarnText[0].Load("text_star_earn_1");
    //mStarEarnTextGlow[0].Load("text_star_earn_1_glow");
    
    //mStarEarnText[1].Load("text_star_earn_2");
    //mStarEarnTextGlow[1].Load("text_star_earn_2_glow");
    
    //mStarEarnText[2].Load("text_star_earn_3");
    //mStarEarnTextGlow[2].Load("text_star_earn_3_glow");
    
    //mStarEarnText[3].Load("text_star_earn_dash");
    //mStarEarnTextGlow[3].Load("text_star_earn_dash_glow");

    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
    /////////////////          M.I.             //////////////
    //                                                      //
    //                                                      //
    
    mAdBannerDemo.Load("demo_ad_banner");
    
    
    
    
    
    
    
    
    
    mMIDialogBackSmall.Load("dialog_box_back_small");
    mMIDialogBackLarge.Load("dialog_box_back_large");
    
    
    
    
    mMIPrizeChestClosed.Load("prize_chest_closed");
    mMIPrizeChestOpen.Load("prize_chest_open");
    
    
    mMIPrizeGem[0].Load("prize_gem1");
    mMIPrizeGemGlow[0].Load("prize_gem1_glow");
    

    
    //                                                      //
    //////////////////////////////////////////////////////////
    
    
    

    
    
    
    
    
    
    
    
    
    mGIRockHammerBack.Load("gi_rock_hammer");
    mGIThunderboneBack.Load("game_tile_bone");
    
    
    mTutorialRexMockup.Load("tut_rex_mockup");
    mTutorialRexBackground.Load("tut_rex_background_circle");
    mTutorialRexCircle.Load("tut_rex_stone_ring");
    
    mTutorialRexBody.Load("tut_rex_part_body");
    
    mTutorialRexJawLower.Load("tut_rex_part_lower_jaw");
    mTutorialRexHeadBack.Load("tut_rex_part_back_of_head");
    
    mTutorialRexTooth[0].Load("tut_rex_part_tooth_1");
    mTutorialRexTooth[1].Load("tut_rex_part_tooth_2");
    mTutorialRexTooth[2].Load("tut_rex_part_tooth_3");
    mTutorialRexTooth[3].Load("tut_rex_part_tooth_4");
    
    
    mTutorialRexEye.Load("tut_rex_part_eye");
    mTutorialRexEyePupil.Load("tut_rex_part_pupil");
    
    mTutorialRexNoseSegment.Load("tut_rex_part_nose_segment");
    mTutorialRexNose.Load("tut_rex_part_nose");
    
    mTutorialRexNostrilBack.Load("tut_rex_part_back_nostril");
    mTutorialRexNostrilFront.Load("tut_rex_part_nostril_front");
    
    
    
    
    
    mHeroStegoShadow.Load("title_stego_shadow");
    
    mHeroStegoMockup.Load("title_stego_nice_mockup");
    
    mHeroStegoBody.Load("hero_stego_body");
    mHeroStegoBelly.Load("hero_stego_belly");
    
    mHeroStegoHeadNub.Load("hero_stego_head_nub");
    
    mHeroStegoHead.Load("hero_stego_head");
    
    
    
    mHeroStegoFootFront[0].Load("hero_stego_foot_front_left");
    mHeroStegoFootFront[1].Load("hero_stego_foot_front_right");
    
    mHeroStegoSpike[0].Load("hero_stego_spike_1");
    mHeroStegoSpike[1].Load("hero_stego_spike_2");
    mHeroStegoSpike[2].Load("hero_stego_spike_3");
    
    mHeroStegoEye.Load("hero_stego_head_eye");
    mHeroStegoNostril.Load("hero_stego_nostril");
    
    
    mHeroStegoTail.Load("hero_stego_tail");
    
    mHeroStegoTailSpike[0].Load("hero_stego_tail_spike_1");
    mHeroStegoTailSpike[1].Load("hero_stego_tail_spike_2");
    mHeroStegoTailSpike[2].Load("hero_stego_tail_spike_3");
    mHeroStegoTailSpike[3].Load("hero_stego_tail_spike_4");
    
    
    
    
    
    
    
    
    
    
    gImageBundler.StartBundle("font_bundle_set");
    
    mFontScore.Load ("font_score_", "0123456789$,");
    //mFontGameText.Load("font_game_", "!$+.0123456789");
    //mFontGameTextBig.Load("font_game_big_", "$!acfkstx0123456789");
    
    mFontMovesRemaining.Load("font_move_count_", "0123456789");
    
    //mFontMovesRemaining.mPointSize = 30.0f;
    //mFontScoreBar.Load("font_score_bar_", "0123456789,");
    
    mFontMainDisplayFront.Load("font_main_", "$+.-0123456789");
    mFontMainDisplayMiddle.Load("font_main_middle_", "!$+.0123456789");
    mFontMainDisplayStroke.Load("font_main_stroke_", "!$+.0123456789");
    
    //mFontMainDisplayFront.mScale = 0.5f;
    //mFontMainDisplayMiddle.mScale = 0.5f;
    //mFontMainDisplayStroke.mScale = 0.5f;
    
    
    
    //mFontMainDisplayFront.PrintLoaded();
    //mFontMainDisplayMiddle.PrintLoaded();
    //mFontMainDisplayStroke.PrintLoaded();
    
    
    //gImageBundler.EndBundle();
    
    //mFontMainDisplayFront.ExpandAll(-4.0f);
    
    
    
    
    
    
    
    //gImageBundler.EndBundle();
}

void MainApp::LoadEffects()
{
    
    //effect_blast_overlay_00.png
    //effect_blast_overlay_47.png
    
    mSequenceBlast1.Load("effect_blast_underlay_", 0, 53);
    mSequenceBlast2.Load("effect_blast_overlay_", 0, 47);
    
    
    // //effect_blast_overlay_00.png
    // //effect_blast_underlay_00
    // //effect_blast_underlay_53
    
    //mEffectBeamAdditive.Load("effect_quad_beam_additive");
    //mEffectBeamColor.Load("effect_quad_beam_color");
    
    
    
    
    gImageBundler.StartBundle("particle_swarm");
    
    //mEffectParticleTetra[0].Load("effect_particle_tetra");
    //mEffectParticleTetra[1].Load("effect_particle_tetra_large");
    
    mEffectParticleStar[0].Load("effect_particle_star_24");
    mEffectParticleStar[1].Load("effect_particle_star_32");
    mEffectParticleStar[2].Load("effect_particle_star_40");
    mEffectParticleStar[3].Load("effect_particle_star_64");
    mEffectParticleStar[4].Load("effect_particle_star_80");
    mEffectParticleStar[5].Load("effect_particle_star_128");
    
    
    for(int i=0;i<4;i++)
    {
        FString aBasePath = FString("effect_flare_") + FString(i + 1);
        
        mEffectParticleFlare[0][i].Load(aBasePath + FString(""));
        mEffectParticleFlareLarge[0][i].Load(aBasePath + FString("_large"));
        
        mEffectParticleFlare[1][i].Load(aBasePath + FString("_streaks"));
        mEffectParticleFlareLarge[1][i].Load(aBasePath + FString("_streaks_large"));
    }
    
    for(int aColorIndex=0;aColorIndex<8;aColorIndex++)
    {
        FString aColorName;
        
        if(aColorIndex == 0)aColorName = "red";
        if(aColorIndex == 2)aColorName = "green";
        if(aColorIndex == 1)aColorName = "blue";
        if(aColorIndex == 3)aColorName = "orange";
        if(aColorIndex == 4)aColorName = "purple";
        if(aColorIndex == 5)aColorName = "teal";
        if(aColorIndex == 6)aColorName = "yellow";
        if(aColorIndex == 7)aColorName = "white";
        
        
        FString aBasePath = FString("effect_sparkle_additive_cluster_") + aColorName + FString("_0");
        
        //FString aBasePathPastel = FString("effect_add_sparkle_pastel_") + aColorName + FString("_");
        
        
        for(int i=0;i<7;i++)
        {
            mEffectSparkleAdditive[aColorIndex][i].LoadN(aBasePath.c(), i);
        }
    }
    
    for(int i=0;i<4;i++)
    {
        mEffectParticleHot[i].LoadN("effect_hot_particle_", i + 1);
        //mEffectParticleHotSmall[i].LoadN("effect_hot_particle_small_", i + 1);
        
        mEffectParticleCool[i].LoadN("effect_cool_particle_", i + 1);
        //mEffectParticleCoolSmall[i].LoadN("effect_cool_particlesmall_", i + 1);
    }
    
    
    
    mEffectTwinkle[0].Load("effect_twinkle_small_1");
    mEffectTwinkle[1].Load("effect_twinkle_small_2");
    
    mEffectTwinkleLarge[0].Load("effect_twinkle_big_1");
    mEffectTwinkleLarge[1].Load("effect_twinkle_big_2");
    
    mEffectTwinkleAdditive[0].Load("effect_twinkle_additive_yellow");
    mEffectTwinkleAdditive[1].Load("effect_twinkle_additive_teal");
    mEffectTwinkleAdditive[2].Load("effect_twinkle_additive_green");
    
    mEffectTwinkleAdditiveLarge[0].Load("effect_twinkle_additive_yellow_large");
    mEffectTwinkleAdditiveLarge[1].Load("effect_twinkle_additive_teal_large");
    mEffectTwinkleAdditiveLarge[2].Load("effect_twinkle_additive_green_large");
    
    mEffectTwinkleAdditivePinwheel[0].Load("effect_twinkle_additive_pinwheel_orange");
    mEffectTwinkleAdditivePinwheel[1].Load("effect_twinkle_additive_pinwheel_blue");
    
    for(int i=0;i<8;i++)
    {
        mEffectTwinkleYellow[i].Load(FString("effect_twinkle_yellow_small_0") + FString(i));
        mEffectTwinkleYellowLarge[i].Load(FString("effect_twinkle_yellow_large_0") + FString(i));
    }
    
    mEffectSpecialOrbiter.Load("effect_tile_orb");
    mEffectSpecialOrbiterHalo.Load("effect_tile_orb_spinner");
    mEffectSpecialOrbiterHaloNaked.Load("effect_tile_orb_spinner_naked");

    mEffectHaloLarge[0].Load("effect_halo_large_1");
    
    mEffectHaloMedium[0].Load("effect_halo_medium_1");
    mEffectHaloMedium[1].Load("effect_halo_medium_2");
    mEffectHaloMedium[2].Load("effect_halo_medium_3");
    
    //mEffectHaloSmall[0].Load("effect_halo_small_1");
    //mEffectHaloSmall[1].Load("effect_halo_small_2");
    
    
    
    
    
    
    
    
    gImageBundler.StartBundle("effects_halos");
    
    mEffectHaloLarge[1].Load("effect_halo_large_2");
    
    //mEffectLightTwirl.Load("effect_light_twirl_small");
    //mEffectLightSpokes.Load("effect_light_spokes");
    
    mEffectLightSpinnerLarge[0].Load("effect_spinner_large_1");
    mEffectLightSpinnerLarge[1].Load("effect_spinner_large_2");
    mEffectLightSpinnerLarge[2].Load("effect_spinner_large_3");
    
    
    mEffectLightSpinner[0].Load("effect_spinner_small_1");
    mEffectLightSpinner[1].Load("effect_spinner_small_2");
    mEffectLightSpinner[2].Load("effect_spinner_small_3");
    
    //mEffectLightSmearBlue.Load("effect_side_smear_blue");
    //mEffectLightSmearBlueBubbles.Load("effect_side_smear_blue_bubbly");
    
    mEffectLaserNode[0].Load("effect_laser_node_1");
    mEffectLaserNode[1].Load("effect_laser_node_2");
    
    mEffectLaserNodeLarge[0].Load("effect_laser_node_large_1");
    mEffectLaserNodeLarge[1].Load("effect_laser_node_large_2");
    
    
    
    
    for(int i=0;i<6;i++)
    {
        //mEffectLightRay[i].LoadN("effect_ray_", i + 1);
        //mEffectLightRayWide[i].LoadN("effect_ray_wide_", i + 1);
        
    }
    
    
    //gImageBundler.StartBundle("effect_spiral");
    //mSequenceEffectSpiralLoop.Load("effect_spiral_loop_", 0, 15);
    
    //gImageBundler.StartBundle("effect_spiral_wide");
    //mSequenceEffectSpiralLoopWide.Load("effect_spiral_loop_wide_", 0, 15);
    
    
    
    gImageBundler.StartBundle("effect_glow_ball");
    
    mSequenceSparkleSphereStart.Load("sparkle_loop_start_", 0, 29);
    mSequenceSparkleSphereLoop.Load("sparkle_loop_", 0, 15);
    mSequenceSparkleSphereStop.Load("sparkle_loop_start_", 0, 29);
    
    
    //mSequenceSparkleSphereStop.Load("sparkle_loop_end_", 0, 22);
    mSequenceGlowBall.Load("effect_glow_ball_", 0, 15);
    
    
    
    
    //mSequenceSparkleYellow.Load("effect_sparkle_circle_", 0, 67);
    //effect_sparkle_circle_000.png
    //effect_sparkle_circle_067.png
    
    
    int aInset = gImageBundler.mInset;
    gImageBundler.mInset = 6;
    gImageBundler.StartBundle("effect_laser_stream");
    mSequenceLaserLoop.Load("particle_stream_", 0, 29);
    gImageBundler.mInset = aInset;
    
    
    
    
    gImageBundler.StartBundle("effect_coin_spins");
    
    mSequenceCoinSpin[0].Load("effect_coin_spin_1_", 0, 15);
    mSequenceCoinSpin[1].Load("effect_coin_spin_2_", 0, 15);
    mSequenceCoinSpin[2].Load("effect_coin_spin_3_", 0, 15);
    mSequenceCoinSpin[3].Load("effect_coin_spin_4_", 0, 15);
    mSequenceCoinSpin[4].Load("effect_coin_spin_5_", 0, 15);
    

    
    
    mSequenceEffectEnegyBoom.Load("effect_energy_boom_", 0, 29);
    mSequenceEffectJetBlast.Load("effect_jet_blast_", 0, 50);
    mSequenceEffectSmallBurnLoop.Load("effect_small_burn_loop_", 0, 15);
    //mSequenceEffectZipFlare.Load("effect_zip_flare_", 0, 23);
    
    
    //mSequenceEffectBlastJet1.Load("effect_blast_jet_1_", 0, 47);
    //mSequenceEffectBlastJet2.Load("effect_blast_jet_2_", 0, 54);
    //mSequenceEffectBlastColor.Load("effect_blast_color_", 0, 47);
    
    
    
    gImageBundler.StartBundle("effect_twinkle_sphere");
    mSequenceTwinkleSphere.Load("effect_twinkle_accent_loop_", 0, 29);
    
    
    
    //gImageBundler.StartBundle("effect_smoke_plume");
    //mSequenceEffectSmoke.Load("effect_smoke_plume_", 0, 50);
    
    //gImageBundler.StartBundle("effect_teal_bust");
    //mSequenceEffectBurst.Load("effect_blueburst_", 0, 30);
    
    
    //gImageBundler.StartBundle("bubble_ring_0");
    //mSequenceBubbleRing.Load("effect_bubble_ring_", 0, 22);
    
    //gImageBundler.StartBundle("bubble_ring_1");
    //mSequenceBubbleRing.Load("effect_bubble_ring_", 23, 37);
    
    //gImageBundler.StartBundle("bubble_ring_2");
    //mSequenceBubbleRing.Load("effect_bubble_ring_", 38, 57);
    
    
    
    //gImageBundler.StartBundle("smoke_plume");
    //mSequenceEffectLightSmokePlume.Load("effect_light_smoke_plume_", 0, 23);
    
    
    gImageBundler.StartBundle("highlight_square");
    mSequenceEffectHilight1.Load("effect_hilight_square_", 0, 11);
    
    
    //gImageBundler.StartBundle("highlight_square_white");
    //mSequenceEffectHilightSquareWhite.Load("effect_hilight_square_white_", 0, 11);
    
    
    gImageBundler.StartBundle("effect_tile_highlight");
    mSequenceEffectHilight2.Load("effect_tile_highlight_", 0, 24);
    
    
    
    gImageBundler.StartBundle("energy_bolts");
    
    mSequenceEffectBolt.Load("plasma_bolt_", 0, 23);
    //mSequenceEffectBoltGlow.Load("plasma_bolt_glow_", 0, 23);
    
    gImageBundler.StartBundle("particles_tail");
    mSequenceParticleStream.Load("particle_tail_", 0, 23);
    
    gImageBundler.StartBundle("burst");
    mSequenceBurst.Load("burst_", 0, 26);
    
 
    
    
    
    
    bool HOLD_AUTO_BUNDLE = gImageBundler.mAutoBundle;
    gImageBundler.mAutoBundle = false;
    
    
    gImageBundler.StartBundle("dirt_crumble_1");
    mSequenceRockCrumble[0].Load("dirt_crumble_1_");
    
    gImageBundler.StartBundle("dirt_crumble_2");
    mSequenceRockCrumble[1].Load("dirt_crumble_2_");
    
    
    
    
    gImageBundler.StartBundle("explosion_1");
    mSequenceExplosion.Load("exp2_", 0, 35);
    
    gImageBundler.StartBundle("explosion_2");
    mSequenceExplosion.Load("exp2_", 36, 53);
    
    //gImageBundler.StartBundle("rock_spins");
    
    //1_00.png
    //rock_debris_gray_spin_1_23.png
    
    /*
     for(int i=0;i<9;i++)
     {
     
     FString aPathGrey = FString("rock_debris_gray_spin_") + FString((i + 1)) + FString("_");
     FString aPathRed = FString("rock_debris_red_spin_") + FString((i + 1)) + FString("_");
     
     mSequenceRockSpinGrey[i].Load(aPathGrey.c(), 0, 23);
     mSequenceRockSpinRed[i].Load(aPathRed.c(), 0, 23);
     }
     */
    
    //gImageBundler.EndBundle();
    gImageBundler.mAutoBundle = HOLD_AUTO_BUNDLE;
    
    
    
#ifdef SETUP_MODE
    
    
    AddTestSprite(mEffectHaloSmall[0]);
    AddTestSprite(mEffectHaloSmall[1]);
    
    AddTestSprite(&(mEffectTwinkleYellowLarge[0]));
    AddTestSprite(&(mEffectTwinkleYellowLarge[1]));
    
    
    AddTestSprite(&(mEffectLightSpinnerLarge[0]));
    AddTestSprite(&(mEffectLightSpinner[1]));
    AddTestSprite(&(mEffectLightSpinnerLarge[2]));
    
    
    AddTestSprite(mEffectLightSpokes);
    
    
    AddTestSprite(mEffectLightSmearBlueBubbles);
    
    
    
    
    
    AddTestSprite(mEffectLaserNode[0]);
    AddTestSprite(mEffectLaserNode[1]);
    
    AddTestSprite(mEffectLaserNodeLarge[0]);
    AddTestSprite(mEffectLaserNodeLarge[1]);
    
    
    AddTestSprite(mEffectTwinkleYellowLarge[1]);
    
    
    AddTestSprite(mEffectTwinkleYellowLarge[0]);
    
    AddTestSprite(mEffectTwinkleYellowLarge[2]);
    
    AddTestSprite(mEffectTwinkleYellowLarge[3]);
                  
    
    
    AddTestSprite(mEffectParticleFlare[0][0]);
    
    AddTestSprite(mEffectParticleFlareLarge[1][0]);
    
    AddTestSprite(mEffectParticleFlare[2][1]);
    
    AddTestSprite(mEffectParticleFlareLarge[0][1]);
    
    
    

    
    AddTestSprite(mEffectTwinkleAdditivePinwheel[0]);
    AddTestSprite(mEffectTwinkleAdditivePinwheel[1]);
    
    AddTestSprite(mEffectTwinkleAdditiveLarge[0]);
    AddTestSprite(mEffectTwinkleAdditiveLarge[1]);
    AddTestSprite(mEffectTwinkleAdditiveLarge[2]);
    
    AddTestSprite(mEffectTwinkleAdditive[0]);
    AddTestSprite(mEffectTwinkleAdditive[1]);
    AddTestSprite(mEffectTwinkleAdditive[2]);
    
    
    //AddTestSprite(mEffectHaloSmall[1]);
    //AddTestSprite(mEffectHaloSmall[0]);
    
    //AddTestSprite(mEffectHaloMedium[2]);
    //AddTestSprite(mEffectHaloMedium[1]);
    //AddTestSprite(mEffectHaloMedium[0]);
    
    AddTestSprite(mEffectLightSpinner[2]);
    AddTestSprite(mEffectLightSpinner[1]);
    AddTestSprite(mEffectLightSpinner[0]);
    
    AddTestSprite(mEffectLightSpinnerLarge[2]);
    AddTestSprite(mEffectLightSpinnerLarge[1]);
    AddTestSprite(mEffectLightSpinnerLarge[0]);
    
    for(int i=0;i<8;i++)
    {
        gSpriteSequenceList.Remove(&(mEffectSparkleAdditive[i]));
    }
    
    gSpriteSequenceList.Remove(&(mEffectParticleHot));//.Load("effect_hot_particle_", 1, 4);
    gSpriteSequenceList.Remove(&(mEffectParticleHotSmall));//.Load("effect_hot_particle_small_", 1, 4);
    
    gSpriteSequenceList.Remove(&(mEffectParticleCool));//.Load("effect_cool_particle_", 1, 4);
    gSpriteSequenceList.Remove(&(mEffectParticleCoolSmall));//.Load("effect_cool_particlesmall_", 1, 4);
    
#endif
    
    
}



void MainApp::LoadSounds()
{
    
    
    mSoundBlasterChargeUp.Load("charge_up_laser_flanger");
    
    mSoundBlasterTrigger.Load("burn_stinger");
    mSoundBlasterEnd.Load("massive_blast_impact_laser");
    
    
    //mSoundChainSelect.Load("select_blip", 4);
    //mSoundChainSelect.Load("pop_5", 4);
    mSoundChainSelect.Load("match", 4);
    
    mSoundChainDeselect.Load("deselect_3", 2);
    
    
    mSoundMatchChain.Load("bubble_pop", 4);
    mSoundMatchSpecial.Load("pop_4", 2);
    
    mSoundMatchStarting.Load("fireball_land", 2);
    
    
    mSoundTileLanded.Load("tile_landed", 4);
    
    mSoundLevelUp.Load("good_job_chime_2");
    
    
    mSoundJarCharge.Load("impact_with_sheen");
    mSoundJarBlast.Load("drill");
    mSoundJarCollect.Load("twinkle");
    
    
    mSoundDiscoverGeneric.Load("rock_thud_2");
    mSoundDiscoverTreasure.Load("xylophone");
    mSoundDiscoverStar.Load("good_job_chime_1");
    
    //mSoundTimeWarning.Load("time_running_out");
    //mSoundTimeOver.Load("sparkle_1", 3);
    //mSoundTimeTick.Load("time_tick", 2);
    //mSoundTimeTock.Load("time_tock", 2);
    
    //mSoundLevelEgg.Load("egg_discovered");
    
    //mSoundPowerupBomb.Load("powerup_bomb", 2);
    //mSoundPowerupQuad.Load("powerup_quad", 2);
    //mSoundPowerupShuffle.Load("powerup_shuffle", 2);
    //mSoundPowerupTimeExtension.Load("powerup_time_extension");
    //mSoundPowerupFireball.Load("fireball_spawn", 2);
    
    //mSoundFireballLand.Load("fireball_land", 2);
    
    mSoundStartAnimationBeep.Load("countdown_beep", 2);
    mSoundStartAnimationGo.Load("countdown_go");
    
    //mSoundRockCrack[0].Load("rock_crack_1", 2);
    //mSoundRockCrack[1].Load("rock_crack_2", 2);
    //mSoundRockCrack[2].Load("rock_crack_3", 2);
    //mSoundRockCrack[3].Load("rock_crack_4", 2);
    
    mSoundDirtBreak[0].Load("dirt_break_1", 2);
    mSoundDirtBreak[1].Load("dirt_break_2", 2);
    mSoundDirtBreak[2].Load("dirt_break_3", 2);
    
    
    mSoundRockBreak[0].Load("rock_break_1", 2);
    mSoundRockBreak[1].Load("rock_break_2", 2);
    
    
    
    mSoundMetalBreak[0].Load("pop_3", 2);
    mSoundMetalBreak[1].Load("pop_2", 2);
    
    
    mSoundRockChink.Load("rock_chink");
    mSoundMetalChink.Load("metal_chink");
    
    
    mSoundRise[0].Load("rock_rise_1");
    mSoundRise[1].Load("rock_rise_2");
    
    mSoundTitleLetterBonk.Load("pop_1", 5);
    
    mSoundMenuStarEarn.Load("menu_star_earn", 3);
    mSoundButtonClick.Load("clank_1", 2);
}




void MainApp::Update()
{
    if(mTransition)
    {
        if(mTransition->mKill == 0)
        {
            mTransition->Update();
        }
        else
        {
            mTransition->mKill--;
            if(mTransition->mKill <= 0)
            {
                delete mTransition;
                mTransition = 0;
            }
        }
    }
    
    
    
    
    mPopoverShowing = false;
    mPopoverFade = 0.0f;
    
    int aModalViewCount = gApp->mViewController.ModalViewCount();
    
    if(gApp->mViewController.AnimationExists())
    {
        mPopoverFade = gApp->mViewController.AnimationPercent();
        
        if(gApp->mViewController.AnimationInExists())
        {
            if(aModalViewCount > 1)mPopoverFade = 1.0f;
        }
        else
        {
            if(aModalViewCount <= 1)mPopoverFade = (1.0f - mPopoverFade);
        }
    }
    else
    {
        if(aModalViewCount > 0)
        {
            mPopoverShowing = true;
            mPopoverFade = 1.0f;
        }
    }
}

void MainApp::Draw()
{
    FApp::Draw();
}

void MainApp::DrawOver()
{
    if(mTransition)
    {
        if(mTransition->mKill == 0)
        {
            mTransition->Draw();
        }
    }    
}



void MainApp::MouseDown(float pX, float pY)
{
    
}

void MainApp::MouseUp(float pX, float pY)
{
    
}

void MainApp::MouseMove(float pX, float pY)
{
    
}

bool MainApp::IsPaused()
{
    bool aReturn = false;
    
    if(gApp->mViewController.ModalViewExists())aReturn = true;
    
    //if(mPopoverContainer != 0)aReturn = true;
    
    
    //TODO:
    //if(mPopoverViews.mCount > 0)aReturn = true;
    
    return aReturn;
}

void MainApp::TransitionTo(FView *pToView, FView *pFromView, Transition *pTransition)
{
    mTransitionToView = pToView;
    mTransitionFromView = pFromView;
    
    FView *aRoot = &(gApp->mViewController.mRoot);
    
    if(pFromView == 0)
    {
        EnumListReverse(FView, aView, gApp->mViewController.mRoot.mSubviews)
        {
            if((aView->GetContainer()->mKill == 0) && (pFromView ==0))
            {
                mTransitionFromView = aView;
            }
        }
    }
    
    if(pTransition == 0)
    {
        pTransition = new Transition();
    }
    
    mTransition = pTransition;
}

void MainApp::TransitionSwapViews()
{
    Log("TransitionSwapViews(%s => %s)\n", mTransitionToView->mName.c(), mTransitionFromView->mName.c());
    
    if(mTransitionToView)
    {
        gApp->mViewController.ViewAdd(mTransitionToView);
    }
    
    if(mTransitionFromView)
    {
        mTransitionFromView->Kill();
    }
    
    if(true)
    {
        gApp->mViewController.KillAllModalViews();
    }
    
    mTransitionToView = 0;
    mTransitionFromView = 0;
}

void MainApp::PopupGameMenu()
{
    if(gApp->mViewController.AnimationExists())
    {
        
    }
    else
    {
        //KLUDGE:
        //TODO:
        //return;
        
        PopupAnimateTopOut();
        GameMenu *aMenu = new GameMenu();
        gApp->mViewController.ModalViewAddTop(aMenu);
        aMenu->SetTransformX(-(gAppWidth2 * 1.2f));
        aMenu->SetTransformRotation(-18.0f);
        aMenu->SetTransformScaleX(1.06f);
        aMenu->SetTransformScaleY(0.97f);
        aMenu->AnimateIn();
    }
}

void MainApp::PopupOptionsMenu()
{
    
    
}

void MainApp::PopupStoreMenu()
{
    if(gApp->mViewController.AnimationExists())
    {
        Log("PopupGameMenu() ... AnimationExists() == TRUE, Bail!\n");
    }
    else
    {
        PopupAnimateTopOut();
        GameStoreScreen *aMenu = new GameStoreScreen();
        gApp->mViewController.ModalViewAddTop(aMenu);
        aMenu->SetTransformX(-(gAppWidth2 * 1.2f));
        aMenu->SetTransformRotation(-18.0f);
        aMenu->SetTransformScaleX(1.06f);
        aMenu->SetTransformScaleY(0.94f);
        aMenu->AnimateIn();
    }
}

void MainApp::ClosePopup()
{
    FView *aTopPopover = gApp->mViewController.GetTopModalView();
    
    if(aTopPopover)
    {
        aTopPopover->AnimationSetX(-gAppWidth);
        aTopPopover->AnimationSetRotation(-18.0f);
        aTopPopover->AnimationSetScaleX(1.06f);
        aTopPopover->AnimationSetScaleY(0.94f);
        aTopPopover->AnimateOut(true);
    }
    
    aTopPopover = gApp->mViewController.GetTopModalView(true);
    
    if(aTopPopover)
    {
        aTopPopover->AnimateIn();
    }
}

void MainApp::PopupAnimateTopOut()
{
    FView *aTopPopover = gApp->mViewController.GetTopModalView(false);
    if(aTopPopover)
    {
        //aTopPopover->AnimationSetX(gAppWidth + (gAppWidth2 * 1.2f));
        aTopPopover->AnimationSetX(gAppWidth);
        aTopPopover->AnimationSetRotation(18.0f);
        aTopPopover->AnimationSetScaleX(1.06f);
        aTopPopover->AnimationSetScaleY(0.94f);
        aTopPopover->AnimateOut(false);
    }
}

void MainApp::PopupAnimateInTop()
{
    
}

void MainApp::PopupAnimateInSecond()
{
    
}

