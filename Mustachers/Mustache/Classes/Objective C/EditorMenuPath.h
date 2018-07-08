//
//  EditorMenuPath.h
//  Mustache
//
//  Created by Nick Raptis on 6/22/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EditorMenuPath : UIViewController
{
    UISegmentedControl              *segmentPathMode;
}

@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentPathMode;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)nuke;
- (void)dealloc;

@end
