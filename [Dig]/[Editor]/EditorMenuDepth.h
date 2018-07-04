//
//  EditorMenuDepth.h
//  BoneDig
//
//  Created by Nick Raptis on 11/26/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EditorMenuDepth : UIViewController
{
    UISegmentedControl                      *segmentStarDepth;
}

@property (nonatomic, strong) IBOutlet UISegmentedControl *segmentStarDepth;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)nuke;
- (void)dealloc;

@end
