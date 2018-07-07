//
//  GLApp.h
//  OptimizeRX
//
//  Created by Nicholas Raptis on 10/10/15.
//  Copyright © 2015 Nick Raptis. All rights reserved.
//

#ifndef GLApp_hpp
#define GLApp_hpp

#include "FApp.h"
#include "FSprite.h"
#include "FFont.h"
#include "FModelData.h"
#include "FCanvas.hpp"

class CNVWorldContainerContainer;
class TestWorldContainerContainer;
class TestWorldContainer;
class TempView;
class GLApp : public FApp {
public:
    GLApp();
    virtual ~GLApp();

    virtual void                                Update();
    virtual void                                Draw();
    virtual void                                Load();
    virtual void                                LoadComplete();

    void                                        UpdateRot(float pX);

    virtual void                                SetVirtualFrame(float pX, float pY, float pWidth, float pHeight);
    virtual void                                SetDeviceSize(float pWidth, float pHeight);

    bool                                        SegmentSegmentIntersection(FPoint l1p1, FPoint l1p2, FPoint l2p1, FPoint l2p2, FPoint *intersection);
    
    virtual void                                MouseWheel(int pDirection);
    virtual void                                KeyDown(int pKey);
    virtual void                                KeyUp(int pKey);
    
    virtual void                                TouchDown(float pX, float pY, void *pData);
    virtual void                                TouchMove(float pX, float pY, void *pData);
    virtual void                                TouchUp(float pX, float pY, void *pData);
    virtual void                                TouchFlush();
    
    CNVWorldContainerContainer                  *mCanvasContainer;

    FSound                                      mSound;
    
    FPoint                                      mLine1Point1;
    FPoint                                      mLine1Point2;
    
    FPoint                                      mLine2Point1;
    FPoint                                      mLine2Point2;

    FPoint                                      *mSelectedPoint;
    FPoint                                      mSelectedPointStart;
    FPoint                                      mSelectedTouchStart;

    float                                       mFont1ScaleSin;
    float                                       mFont2ScaleSin;
    
    FModelDataIndexed                           mSphere;
    
    FSprite                                     mTestSprite;
    FSprite                                     mBackground;
    FSprite                                     mBackgroundLarge;
    
    FSprite                                     mTessPattern;
    
    FSprite                                     mDarkTile;

    FSprite                                     mWallLeft;
    FSprite                                     mWallRight;

    FSprite                                     mSillyMeme;

    FSprite                                     mTest_800x600_1;
    FSprite                                     mTest_800x600_2;
    FSprite                                     mTest_Small_1;

    FSprite                                     mInterfaceBottom;
    FSprite                                     mInterfaceBottomGray;


    FSpriteSequence                             mSequenceSquare;
    FSpriteSequence                             mParticleStream;

    FSpriteSequence                             mSequencePlasmaBolt;
    FSpriteSequence                             mSequencePlasmaBoltGlow;


    FSpriteSequence                             mSequenceSmokePuff;
    FSpriteSequence                             mSequenceTwinkle;
    FSpriteSequence                             mSequenceSparkBlast;

    
    FSprite                                     mTile1;
    FSprite                                     mTile2;
    FSprite                                     mTile3;
    FSprite                                     mTile4;

    int                                         mSpawnNewWorldTimer;
    
    bool                                        mAnimationSide;
    FCanvasAnimation                            mAnimation;




    FSprite                                     gi_chaos_egg_back_blue_steel;
    FSprite                                     gi_chaos_egg_back_chrome;
    FSprite                                     gi_chaos_egg_back_grey;
    FSprite                                     gi_chaos_egg_back_megabronze;
    FSprite                                     gi_chaos_egg_back_red;
    FSprite                                     gi_chaos_egg_back_tan;
    FSprite                                     gi_chaos_egg_diamond_glow_large;
    FSprite                                     gi_chaos_egg_diamond_glow_small;
    FSprite                                     gi_chaos_egg_diamond_slot;
    FSprite                                     gi_chaos_egg_gem_diamond;
    FSprite                                     gi_chaos_egg_mockup_2;
    FSprite                                     gi_chaos_egg_mockup;
    FSprite                                     gi_chaos_egg_spots_blue_glowing;
    FSprite                                     gi_chaos_egg_spots_blue;
    FSprite                                     gi_chaos_egg_spots_hot_yellow_glowing;
    FSprite                                     gi_chaos_egg_spots_purple_glowing;
    FSprite                                     gi_chaos_egg_spots_red_glowing;
    FSprite                                     gi_chaos_egg_spots_teal_glowing;
    FSprite                                     gi_chaos_egg_spots_white;
    FSprite                                     gi_chaos_egg_spots_yellow_glowing;
    FSprite                                     gi_chaos_egg_stroke_blue;
    FSprite                                     gi_chaos_egg_stroke_glowing;
    FSprite                                     gi_chaos_egg_stroke_white;



    FSprite                                     gi_item_back_bottom_overlay;
    FSprite                                     gi_item_back_inset_active;
    FSprite                                     gi_item_back_inset;
    FSprite                                     gi_item_back;
    FSprite                                     gi_item_charge_count_indicator;
    FSprite                                     gi_item_crystal;
    FSprite                                     gi_item_lock;
    FSprite                                     gi_item_locked_mockup;
    FSprite                                     gi_item_locked;
    FSprite                                     gi_item_mace;
    FSprite                                     gi_item_mockup;
    FSprite                                     gi_item_progress_bar_fill;
    FSprite                                     gi_item_progress_bar;
    FSprite                                     gi_item_stone_back;

    


};

extern GLApp *gApp;

#endif /* GLApp_hpp */
