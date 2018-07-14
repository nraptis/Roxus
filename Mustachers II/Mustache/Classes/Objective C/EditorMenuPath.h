//
//  EditorMenuPath.h
//  Mustache
//
//  Created by Nick Raptis on 6/22/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EditorMenuPath : UIViewController {
    UIButton                        *buttonAdd;
    UIButton                        *buttonRemove;
    
    UISegmentedControl              *segmentPoint;
    
    NSMutableArray                  *arrayCells;
    UIScrollView                    *scrollViewCells;
}

@property (nonatomic, retain) IBOutlet UIButton *buttonAdd;
@property (nonatomic, retain) IBOutlet UIButton *buttonRemove;

@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentPoint;

@property (nonatomic, retain) NSMutableArray *arrayCells;
@property (nonatomic, retain) UIScrollView *scrollViewCells;

- (IBAction)click:(UIButton*)sender;
- (IBAction)toggle:(UISegmentedControl*)sender;

- (void)updateUI;
- (void)updateSelectedCell;

- (void)nuke;
- (void)dealloc;

@end
