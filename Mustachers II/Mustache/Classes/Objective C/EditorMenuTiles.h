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
    UISegmentedControl                          *segmentCurrentLayer;
    
    UISegmentedControl                          *segmentShowTunnel;
    UISegmentedControl                          *segmentShowFloor;
    UISegmentedControl                          *segmentShowBridge;
    
    UISlider                                    *sliderOpacityTunnel;
    UISlider                                    *sliderOpacityFloor;
    UISlider                                    *sliderOpacityBridge;
    
    UIButton                                    *buttonTile;
    UIButton                                    *buttonBlocker;
    
    UIButton                                    *buttonRampU;
    UIButton                                    *buttonRampD;
    UIButton                                    *buttonRampL;
    UIButton                                    *buttonRampR;
}

@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentCurrentLayer;

@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentShowTunnel;
@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentShowFloor;
@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentShowBridge;

@property (nonatomic, retain) IBOutlet UISlider *sliderOpacityTunnel;
@property (nonatomic, retain) IBOutlet UISlider *sliderOpacityFloor;
@property (nonatomic, retain) IBOutlet UISlider *sliderOpacityBridge;

@property (nonatomic, retain) IBOutlet UIButton *buttonTile;
@property (nonatomic, retain) IBOutlet UIButton *buttonBlocker;

@property (nonatomic, retain) IBOutlet UIButton *buttonRampU;
@property (nonatomic, retain) IBOutlet UIButton *buttonRampD;
@property (nonatomic, retain) IBOutlet UIButton *buttonRampL;
@property (nonatomic, retain) IBOutlet UIButton *buttonRampR;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)updateUI;

- (void)nuke;
- (void)dealloc;

@end
