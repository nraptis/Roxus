//
//  TestMenuContent.h
//  GoldDigger
//
//  Created by Nick Raptis on 6/9/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TestMenuContent : UIViewController
{
    UISlider                        *sliderPanX;
    UISlider                        *sliderPanY;
    
    UISlider                        *sliderZoom;
    
    UISlider                        *sliderRotaion;
    
    UILabel                         *labelPan;
    UILabel                         *labelZoom;
    
    UIButton                        *buttonResetPan;
    UIButton                        *buttonResetZoom;
    
}

@property (nonatomic, retain) IBOutlet UISlider *sliderPanX;
@property (nonatomic, retain) IBOutlet UISlider *sliderPanY;

@property (nonatomic, retain) IBOutlet UISlider *sliderZoom;

@property (nonatomic, retain) IBOutlet UISlider *sliderRotaion;


@property (nonatomic, retain) IBOutlet UILabel *labelPan;
@property (nonatomic, retain) IBOutlet UILabel *labelZoom;

@property (nonatomic, retain) IBOutlet UIButton *buttonResetPan;
@property (nonatomic, retain) IBOutlet UIButton *buttonResetZoom;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)globalUpdate;

- (void)nuke;
- (void)dealloc;

@end
