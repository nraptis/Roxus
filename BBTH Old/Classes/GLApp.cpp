#include "GLApp.h"
#include "Game.h"
#include "ToolzResizeScreen.h"

GLApp *gApp = 0;

float gTileWidth = 78.0f;
float gTileHeight = 78.0f;
float gTileWidth2 = (gTileWidth / 2.0f);
float gTileHeight2 = (gTileHeight / 2.0f);

void GLApp::LoadComplete()
{
    //gApp->mViewController.ViewAdd(new MainMenu());
    
    gApp->mViewController.ViewAdd(new Game());
    gGame->Layout(0, 0, gAppWidth, gAppHeight);
    
    //gApp->mViewController.ViewAdd(new MainMenu());
}

GLApp::GLApp()
{
    gApp = this;
    
    
    //gApp->mViewController.SetNaturalSize(640.0f, 768.0f);
    //gApp->mViewController.FitTypeSetWidth();
    //gApp->mViewControllerModal.SetNaturalSize(640.0f, 768.0f);
    //gApp->mViewControllerModal.FitTypeSetWidth();
    
    
    if(gDeviceWidth > 400)
    {
        gApp->mViewControllerTools.ViewAdd(new ToolzResizeScreen());
    }
    
    mEggBorder = new FPointPath();
    mEggBorder->Add(0.000, -29.500);mEggBorder->Add(3.126, -29.021);mEggBorder->Add(6.156, -27.600);mEggBorder->Add(9.000, -25.280);
    mEggBorder->Add(11.570, -22.130);mEggBorder->Add(13.789, -18.248);mEggBorder->Add(15.588, -13.750);mEggBorder->Add(16.914, -8.774);
    mEggBorder->Add(17.727, -3.470);mEggBorder->Add(18.000, 2.000);mEggBorder->Add(17.727, 5.751);mEggBorder->Add(16.914, 9.388);
    mEggBorder->Add(15.588, 12.800);mEggBorder->Add(13.789, 15.884);mEggBorder->Add(11.570, 18.547);mEggBorder->Add(9.000, 20.706);
    mEggBorder->Add(6.156, 22.297);mEggBorder->Add(3.126, 23.272);mEggBorder->Add(0.000, 23.600);mEggBorder->Add(-3.126, 23.272);
    mEggBorder->Add(-6.156, 22.297);mEggBorder->Add(-9.000, 20.706);mEggBorder->Add(-11.570, 18.547);mEggBorder->Add(-13.789, 15.884);
    mEggBorder->Add(-15.588, 12.800);mEggBorder->Add(-16.914, 9.388);mEggBorder->Add(-17.727, 5.751);mEggBorder->Add(-18.000, 2.000);
    mEggBorder->Add(-17.727, -3.470);mEggBorder->Add(-16.914, -8.774);mEggBorder->Add(-15.588, -13.750);mEggBorder->Add(-13.789, -18.248);
    mEggBorder->Add(-11.570, -22.130);mEggBorder->Add(-9.000, -25.280);mEggBorder->Add(-6.156, -27.600);mEggBorder->Add(-3.126, -29.021);
}

GLApp::~GLApp()
{
    
}

void GLApp::SetVirtualFrame(float pX, float pY, float pWidth, float pHeight)
{
    
}

void GLApp::SetDeviceSize(float pWidth, float pHeight)
{
    FApp::SetDeviceSize(pWidth, pHeight);
    
    if(gGame)gGame->Layout(0.0f, 0.0f, gAppWidth, gAppHeight);
}

void GLApp::VirtualDeviceSizeDidChange()
{
    if(gGame)gGame->Layout(0.0f, 0.0f, gAppWidth, gAppHeight);
}

void GLApp::Load()
{
    gImageBundler.mAutoBundle = false;
    //gImageBundler.mAutoBundle = true;
    
    
    /*
    
    //FString aAllowedCharsAlphaNumeric = FString::GetCharsAlphanumeric();
    //FFont::BitmapDataBatch("bmfont_arial_bold_256.fnt", "bmfont_arial_bold_256_st1.png", "CALB_140_", "VVALB_140_", 0, 140, 0, aBlock);

    
    
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
    
    */
    
    
    //mBackground[0].Load("background_1");
    //mBackground[1].Load("background_2");
    //mBackground[2].Load("background_3");
    
    //mBoardEdges.Load("board_edges");
    
    
    mDirtTextureFill.Load("dirt_fill_uvw");
    mDirtTextureSides.Load("dirt_sides_uvw");
    
    mDirtTextureBottoms.Load("dirt_corners_uvw");
    
    
    
    
    //mSequenceBlast.Load("effect_blast_overlay_", 0, 23);
    
    
    
    FString aAllowedCharsScores = "0123456789,.+-\\/?!$";
    
    //aAllowedCharsScores = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890+-=.,()[]!/\\{}_*&%$?";
    
    mFontScoreSmall.LoadNew("kern_bnk_216b.kern_data.fon", "font_score_216b_", (const char *)(aAllowedCharsScores.c()));
    mFontScoreLarge.LoadNew("kern_bnk_248b.kern_data.fon", "font_score_248b_", (const char *)(aAllowedCharsScores.c()));
    mFontItem.Load("font_item_charge_", "0123456789:.+");
    
    aAllowedCharsScores = "0123456789,.+-\\/?!$[]";
    
    mFontGameBubblesLarge.LoadNew("kern_bnk_248b.kern_data.fon", "font_hotbnk_248b_", (const char *)(aAllowedCharsScores.c()));
    mFontGameBubblesSmall.LoadNew("kern_bnk_216b.kern_data.fon", "font_hotbnk_216b_", (const char *)(aAllowedCharsScores.c()));
    
    mFontMovesRemaining.Load("font_move_count_", "0123456789");
    mFontDialogHeader.Load("font_dialog_header_", "l0123456789");
    
    
    
    gImageBundler.StartBundle("BNDL_game_tiles");
    
    for(int i=0;i<7;i++)
    {
        FString aPath = FString("tile_whole_") + FString((i + 1)) + FString("");
        mTileMatchableWhole[i].Load(aPath.c());
        
        aPath = FString("tile_front_") + FString((i + 1)) + FString("");
        mTileMatchableFront[i].Load(aPath.c());
        
        aPath = FString("tile_front_selected_") + FString((i + 1)) + FString("");
        mTileMatchableFrontSelected[i].Load(aPath.c());
        
        aPath = FString("tile_back_") + FString((i + 1)) + FString("");
        mTileMatchableBack[i].Load(aPath.c());
    }
    
    //
    mTileBlock.Load("powerup_back");
    mTileRock.Load("tile_rock_cracked_1");
    mTileItem.Load("tile_wood");
    mTileGem.Load("game_tile_treasure_3");
    
    
    
    mGIScoreBar[0].Load("mi_interface_bar_amber");
    mGIScoreBar[1].Load("mi_interface_bar_dark_red");
    mGIScoreBar[2].Load("mi_interface_bar_blue");
    
    mGIScoreBarItem[0].Load("mi_interface_object_crystal");
    mGIScoreBarItem[1].Load("mi_interface_object_gold");
    mGIScoreBarItem[2].Load("mi_interface_object_ruby");
    mGIScoreBarItem[3].Load("mi_interface_object_leg");
    mGIScoreBarItem[4].Load("mi_interface_object_circle");

    
    
    gImageBundler.StartBundle("BNDL_title_scenery_1");
    
    //return;
    
    mTitleBackgroundSky.Load("title_sky");
    
    mTitleMonolith[0].Load("title_background_monolith_1");
    mTitleMonolith[1].Load("title_background_monolith_2");
    mTitleMonolith[2].Load("title_background_monolith_3");
    
    mTitleVolcano[0].Load("title_volcano_1");
    mTitleVolcano[1].Load("title_volcano_2");
    mTitleVolcano[2].Load("title_volcano_3");
    
    mTitleVolcanoSmoke[0].Load("title_smoke_plume_1");
    mTitleVolcanoSmoke[1].Load("title_smoke_plume_2");
    mTitleVolcanoSmoke[2].Load("title_smoke_plume_3");
    
    mTitleRock[0].Load("title_rock_1");
    mTitleRock[1].Load("title_rock_2");
    
    mTitleRockGrass[0][0].Load("title_rock_1_grass_1");
    mTitleRockGrass[0][1].Load("title_rock_1_grass_2");
    
    mTitleRockGrass[1][0].Load("title_rock_2_grass_1");
    mTitleRockGrass[1][1].Load("title_rock_2_grass_2");
    
    
    mTitleSpewer.Load("title_spewer");
    mTitleSpewerShadow.Load("title_spewer_shadow");
    

    
    
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_character_stego");
    
    gImageBundler.mSeamlessBorders = true;
    
    //HeroStegoMockup.Load("hero_stego_mockup");
    mHeroStegoShadow.Load("title_stego_shadow");
    mHeroStegoBody.Load("hero_stego_body");
    mHeroStegoBelly.Load("hero_stego_belly");
    mHeroStegoHeadNub.Load("hero_stego_head_nub");
    mHeroStegoHead.Load("hero_stego_head");
    mHeroStegoFootFront[0].Load("hero_stego_foot_front_left");
    mHeroStegoFootFront[1].Load("hero_stego_foot_front_right");
    mHeroStegoSpike[0].Load("hero_stego_spike_1");
    mHeroStegoSpike[1].Load("hero_stego_spike_2");
    mHeroStegoSpike[2].Load("hero_stego_spike_3");
    mHeroStegoEyeNice.Load("hero_stego_head_eye_nice");
    mHeroStegoEyeAngry.Load("hero_stego_head_eye_angry");
    mHeroStegoNostril.Load("hero_stego_nostril");
    mHeroStegoTail.Load("hero_stego_tail");
    mHeroStegoTailSpike[0].Load("hero_stego_tail_spike_1");
    mHeroStegoTailSpike[1].Load("hero_stego_tail_spike_2");
    mHeroStegoTailSpike[2].Load("hero_stego_tail_spike_3");
    mHeroStegoTailSpike[3].Load("hero_stego_tail_spike_4");
    
    gImageBundler.EndBundle();
    gImageBundler.mSeamlessBorders = false;
    
    
    gImageBundler.StartBundle("BNDL_interface_assortment_1");
    
    
    
    
    
    //mTutorialRexMockup.Load("tut_rex_mockup");
    
    
    
    //gImageBundler.EndBundle();
    
    
    mMIButtonRetryCrystals.Load("mi_button_retry_crystals");
    mMIButtonRetry.Load("mi_button_retry");
    
    mMIButtonEndGame.Load("mi_button_end_game");
    mMIButtonMainMenu.Load("mi_button_main_menu");
    mMIButtonOptions.Load("mi_button_options");
    mMIButtonShop.Load("mi_button_shop");
    
    
    

    
    
    
    mGIItemBack.Load("gi_item_back");
    //mGIItemBackMockup.Load("gi_item_mockup");
    
    mGIItemBackLocked.Load("gi_item_locked");
    //mGIItemBackLockedMockup.Load("gi_item_locked_mockup");
    
    mGIItemBackFrameBottom.Load("gi_item_back_bottom_overlay");
    
    
    mGIItemProgressBar.Load("gi_item_progress_bar");
    mGIItemProgressBarFill.Load("gi_item_progress_bar_fill");
    //mGIProgressBarFillOdd.Load("gi_item_progress_bar_fill_odd");
    
    
    mGIItemLock.Load("gi_item_lock");
    
    mGIItemChargeCountIndicator.Load("gi_item_charge_count_indicator");
    
    mGIItemCrystal.Load("gi_item_crystal");
    mGIItemMace.Load("gi_item_mace");
    mGIItemItemHammer.Load("gi_item_rock_hammer");
    
    
    

    mGITutorialArrow.Load("gi_tutorial_arrow");
    
    
    
    mTutorialRexBackground.Load("tut_rex_background_circle");
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
    
    gImageBundler.StartBundle("BNDL_random_goodies");
    
    mTransitionCenter.Load("transition_footprint");
    mTitleFloorDirt.Load("title_bottom_dirt");
    mInterfaceBottomBack.Load("game_interface_bottom_back_colored");
    mAdBannerDemo.Load("demo_ad_banner");
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    
    
    
    
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_effect_spark_blast");
    gImageBundler.mInset = 0;
    
    
    mSequenceSparkleBlast.Load("effect_sparkblast_", 0, 28);
    
    
    
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_effect_spirals");
    mSequenceEffectSpiralLoop[0].Load("effect_spiral_loop_", 0, 15);
    mSequenceEffectSpiralLoop[1].Load("effect_spiral_loop_wide_", 0, 15);
    
    
    
    
    gImageBundler.StartBundle("BNDL_effect_light_square");
    mTitleSun.Load("title_sun");
    mSequenceEffectTileBurn[1].Load("effect_tile_highlight_", 0, 24);
    mSequenceEffectTileBurn[0].Load("effect_hilight_square_", 0, 11);
    
    
    //gImageBundler.StartBundle("BNDL_highlight_square_white");
    //mSequenceEffectHilightSquareWhite.Load("effect_hilight_square_white_", 0, 11);
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_effect_burst");
    
    //mSequenceEffectBolt.Load("plasma_bolt_", 0, 23);
    //mSequenceEffectBoltGlow.Load("plasma_bolt_glow_", 0, 23);
    //gImageBundler.StartBundle("BNDL_effect_burst");
    mSequenceBurst.Load("burst_", 0, 26);
    
    gImageBundler.mInset = 4;
    mTutorialRexCircle.Load("tut_rex_stone_ring");
    gImageBundler.mInset = 0;
    
    
    
    
    
    
    
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++  AUTO-BUNDLED  ++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //=======================++++++++++++++++++++++++++++===================
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    
    
    
    bool HOLD_AUTO_BUNDLE = gImageBundler.mAutoBundle;
    //gImageBundler.mAutoBundle = false;
    
    
    gImageBundler.StartBundle("BNDL_interface_dialogs_1");
    mMIDialogBackLarge.Load("mi_dialog_box_large_back");
    mMIDialogBackSmall.Load("mi_dialog_box_small_back");
    mMIButtonBackLargeRetry.Load("mi_button_large_back_retry");
    mMIButtonBackLarge[0].Load("mi_button_large_back_red");
    mMIButtonBackLarge[1].Load("mi_button_large_back_teal");
    mMIDialogSlabBrown.Load("mi_dialog_slab_brown");
    mMIDialogHeader.Load("mi_dialog_box_header");
    
    //mFontItem.Load("font_item_charge_", "0123456789:.+");
    
    
    //mFontGameBubblesLarge.LoadNew("kern_bnk_248b.kern_data.fon", "font_hotbnk_248b_", (const char *)(aAllowedCharsScores.c()));
    //mFontGameBubblesSmall.LoadNew("kern_bnk_216b.kern_data.fon", "font_hotbnk_216b_", (const char *)(aAllowedCharsScores.c()));
    
    
    
    
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_interface_dialogs_2");
    mMIDialogBackScroll.Load("mi_dialog_box_scroll");
    mMIDialogBackMedium.Load("mi_dialog_box_medium_back");
    mMIDialogSlabOutOfMoves.Load("mi_dialog_slab_oom");
    mMIButtonBackLarge[2].Load("mi_button_large_back_orange");
    mMIButtonBackLarge[3].Load("mi_button_large_back_purple");
    
    //mFontDialogHeader.Load("font_dialog_header_", "l");
    
    
    
    
    
   
    
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_interface_dialogs_3");
    mMIPrizeChestClosed.Load("prize_chest_closed");
    mMIPrizeChestOpen.Load("prize_chest_open");
    mTitleButtonPlay[0].Load("mm_button_play_stroke");
    mTitleButtonPlay[1].Load("mm_button_play_shadow");
    mTitleButtonLogIn[0].Load("mm_button_login_stroke");
    mTitleButtonLogIn[1].Load("mm_button_login_shadow");
    mTitleButtonStore[0].Load("mm_button_store_stroke");
    mTitleButtonStore[1].Load("mm_button_store_shadow");
    mTitleButtonLeaf[0].Load("mm_button_leaf");
    mTitleButtonLeaf[1].Load("mm_button_leaf_shadow");
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
    mMILevelUpStar[0].Load("mi_level_up_star_unearned");
    mMILevelUpStar[1].Load("mi_level_up_star_earned");
    mMIButtonBackMedium[0].Load("mi_button_medium_back_green");
    mMIButtonBackMedium[1].Load("mi_button_medium_back_red");
    mMIButtonBackSmall[0].Load("mi_button_small_back_orange");
    mMIButtonBackSmall[1].Load("mi_button_small_back_teal");

    
    mMIButtonCancel.Load("mi_button_cancel");
    mMIButtonOkay.Load("mi_button_okay");
    mMIButtonFacebook.Load("mi_button_facebook");
    mMIButtonReplay.Load("mi_button_replay");
    
    
    
    gImageBundler.StartBundle("BNDL_dirt_crumble_1");
    mSequenceRockCrumble[0].Load("dirt_crumble_1_");
    
    gImageBundler.StartBundle("BNDL_dirt_crumble_2");
    mSequenceRockCrumble[1].Load("dirt_crumble_3_");
    
    
    //gImageBundler.StartBundle("BNDL_explosion_1");
    //mSequenceExplosion.Load("exp2_", 0, 35);
    
    //gImageBundler.StartBundle("BNDL_explosion_2");
    //mSequenceExplosion.Load("exp2_", 36, 53);
    
    int aInset = gImageBundler.mInset;
    gImageBundler.mInset = 6;
    gImageBundler.StartBundle("BNDL_effect_stream_loop");
    mSequenceLaserLoop.Load("particle_stream_", 0, 29);
    gImageBundler.mInset = aInset;
    mSequenceParticleStream.Load("particle_tail_", 0, 23);
    
    
    gImageBundler.mInset = 0;
    gImageBundler.StartBundle("BNDL_effect_sparkle_city");
    mSequenceTwinkleSphere.Load("effect_twinkle_accent_loop_", 0, 29);
    mSequenceEffectBolt.Load("plasma_bolt_", 0, 23);
    mSequenceCoinSpin[0].Load("effect_coin_spin_1_", 0, 15);
    mSequenceCoinSpin[1].Load("effect_coin_spin_2_", 0, 15);
    mSequenceCoinSpin[2].Load("effect_coin_spin_3_", 0, 15);
    mSequenceCoinSpin[3].Load("effect_coin_spin_4_", 0, 15);
    mSequenceCoinSpin[4].Load("effect_coin_spin_5_", 0, 15);
    
    
    
    
    
    gImageBundler.StartBundle("BNDL_effect_cluster_1");
    mEffectParticleShooterStar.Load("effect_particle_star_large");
    mEffectParticleShooterStarSmall.Load("effect_particle_star_small");
    
    mEffectParticleShooterTetra.Load("effect_particle_tetra_large");
    mEffectParticleShooterTetraSmall.Load("effect_particle_tetra_small");
    
    mEffectTwinkleWhite[0].Load("effect_twinkle_white_big_1");
    mEffectTwinkleWhite[1].Load("effect_twinkle_white_big_2");
    
    mEffectTwinkleWhiteSmall[0].Load("effect_twinkle_white_small_1");
    mEffectTwinkleWhiteSmall[1].Load("effect_twinkle_white_small_2");
    
    
    mEffectTwinkleAdditiveWhite.Load("effect_twinkle_additive_white_large");
    mEffectTwinkleAdditiveWhiteSmall.Load("effect_twinkle_additive_white_small");
    
    mEffectMagicBubble.Load("effect_magic_bubble");
    mEffectMagicBubbleSmall.Load("effect_magic_bubble_small");
    
    mEffectMagicSphere.Load("effect_magic_sphere");
    mEffectMagicSphereSmall.Load("effect_magic_sphere_small");
    
    mEffectSmokePuff.Load("effect_cloud_poof");
    
    mEffectLaserBurnSmall.Load("effect_laser_burn_small");
    mEffectLaserBurn.Load("effect_laser_burn");
    
    mEffectSpecialOrbiter.Load("effect_tile_orb");
    mEffectSpecialOrbiterHalo.Load("effect_tile_orb_spinner");
    mEffectSpecialOrbiterHaloNaked.Load("effect_tile_orb_spinner_naked");
    
    mEffectGlowHaloLargeAdditive[0].Load("effect_glow_large_1");
    mEffectGlowHaloLargeAdditive[1].Load("effect_glow_large_2");
    mEffectGlowHaloLargeAdditive[2].Load("effect_glow_large_3");
    
    mEffectGlowHaloSmallAdditive[0].Load("effect_glow_small_1");
    mEffectGlowHaloSmallAdditive[1].Load("effect_glow_small_2");
    mEffectGlowHaloSmallAdditive[2].Load("effect_glow_small_3");
    
    
    
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
        for(int i=0;i<4;i++)mEffectSparkleAdditive[aColorIndex][i].LoadN(aBasePath.c(), i);
    }
    
    for(int i=0;i<4;i++)
    {
        mEffectParticleWarm[i].LoadN("effect_hot_particle_", i + 1);
        mEffectParticleWarmSmall[i].LoadN("effect_hot_particle_small_", i + 1);
        mEffectParticleCool[i].LoadN("effect_cool_particle_", i + 1);
        mEffectParticleCoolSmall[i].LoadN("effect_cool_particlesmall_", i + 1);
    }
    
    mSequenceOrangeSmoke.Load("BNDL_smoke_puff_b_fast", 0, 30);
    
    
    gImageBundler.EndBundle();
    
    //gImageBundler.StartBundle("hamma");
    //gImageBundler.mAutoBundle = HOLD_AUTO_BUNDLE;

    
    
    
    
    
    mFontItem.ApplyScrunch(4.0f);
    
    mFontGameBubblesLarge.ApplyScale(0.25f);
    mFontGameBubblesSmall.ApplyScale(0.25f);
    
    mFontGameBubblesLarge.ApplyExpand(12.0f);
    mFontGameBubblesSmall.ApplyExpand(9.0f);
    mFontGameBubblesLarge.ApplyOffsetX(-30.0f);
    mFontGameBubblesSmall.ApplyOffsetX(-24.0f);
    
    
    mFontScoreLarge.ApplyScale(0.25f);
    mFontScoreSmall.ApplyScale(0.25f);
    mFontScoreLarge.ApplyExpand(12.0f);
    mFontScoreSmall.ApplyExpand(9.0f);
    
    
#ifndef DISABLE_SOUNDS
    LoadSounds();
#endif
}

void GLApp::LoadSounds()
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

void GLApp::Update()
{
    
}

void GLApp::Draw()
{
    
    Graphics::Clear(0.15f, 0.15f, 0.15f, 0.15f);
    
    Graphics::SetColor();
    
}

void GLApp::DrawOver()
{
    
}

