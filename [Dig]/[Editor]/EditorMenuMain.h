//
//  EditorMenuMain.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EditorMenuMain : UIViewController
{
    
    UIButton                    *buttonFill;
    UIButton                    *buttonClear;
    UIButton                    *buttonTrim;
    
    
    UITextField                 *textFieldStarDepth1;
    UITextField                 *textFieldStarSpacing;
    
    UIButton                    *buttonGenerateStars;
    
    
    UIButton                    *buttonSave;
    UIButton                    *buttonLoad;
}

@property (nonatomic, strong) IBOutlet UIButton *buttonFill;
@property (nonatomic, strong) IBOutlet UIButton *buttonClear;
@property (nonatomic, strong) IBOutlet UIButton *buttonTrim;

@property (nonatomic, strong) IBOutlet UITextField *textFieldStarDepth1;
@property (nonatomic, strong) IBOutlet UITextField *textFieldStarSpacing;

@property (nonatomic, strong) IBOutlet UIButton *buttonGenerateStars;

@property (nonatomic, strong) IBOutlet UIButton *buttonSave;
@property (nonatomic, strong) IBOutlet UIButton *buttonLoad;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;
- (IBAction)slide:(UISlider*)sender;

- (void)nuke;
- (void)dealloc;

@end
