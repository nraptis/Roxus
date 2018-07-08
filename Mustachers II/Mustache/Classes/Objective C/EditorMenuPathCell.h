//
//  EditorMenuPathCell.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GamePath.h"
#import "EditorGameArena.h"

@class EditorMenuPath;

@interface EditorMenuPathCell : UIViewController
{
    UISegmentedControl                  *segmentStartZ;
    UISegmentedControl                  *segmentEndZ;
 
    UIButton                            *buttonSelect;
    
    EditorMenuPath                      *menu;
    
    GamePath                            *path;
}

@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentStartZ;
@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentEndZ;

@property (nonatomic, retain) IBOutlet UIButton *buttonSelect;


@property (nonatomic, retain) EditorMenuPath *menu;

@property (nonatomic, assign) GamePath *path;

- (id)initWithPath:(GamePath *)pPath;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;

- (void)nuke;
- (void)dealloc;

@end
