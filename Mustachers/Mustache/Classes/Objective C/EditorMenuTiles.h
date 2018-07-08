//
//  EditorMenuTiles.h
//  Mustache
//
//  Created by Nick Raptis on 6/21/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EditorMenuTiles : UIViewController
{
    UISegmentedControl                          *segmentTileType;
    
    UIButton                                    *buttonTileCross;
    
    UIButton                                    *buttonTileH;
    UIButton                                    *buttonTileV;
    
    UIButton                                    *buttonTileT_U;
    UIButton                                    *buttonTileT_R;
    UIButton                                    *buttonTileT_D;
    UIButton                                    *buttonTileT_L;
    
    UIButton                                    *buttonTileCorner_UR;
    UIButton                                    *buttonTileCorner_BR;
    UIButton                                    *buttonTileCorner_BL;
    UIButton                                    *buttonTileCorner_UL;
}

@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentTileType;

@property (nonatomic, retain) IBOutlet UIButton *buttonTileCross;

@property (nonatomic, retain) IBOutlet UIButton *buttonTileH;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileV;

@property (nonatomic, retain) IBOutlet UIButton *buttonTileT_U;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileT_R;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileT_D;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileT_L;

@property (nonatomic, retain) IBOutlet UIButton *buttonTileCorner_UR;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileCorner_BR;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileCorner_BL;
@property (nonatomic, retain) IBOutlet UIButton *buttonTileCorner_UL;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)nuke;
- (void)dealloc;

@end
