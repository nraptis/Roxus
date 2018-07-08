//
//  GenericSlider.h
//  JiggleARC
//
//  Created by Nick Raptis on 1/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GenericSlider;

@protocol GenericSliderDelegate <NSObject>

- (void)didSlide:(float)percent withSlider:(GenericSlider*)sender;

@end


@interface GenericSlider : UIViewController
{
    UIImageView                                 *imageViewThumb;
    UIImageView                                 *imageViewBackground;
    
    UIView                                      *viewBounds;
    
    id <GenericSliderDelegate>                  delegateSlider;
    
    UIImageView                                 *selectedImage;
    float                                       selectedImageStartX;
    float                                       touchStartX;
    
    float                                       selectedImageStartY;
    float                                       touchStartY;
    
    BOOL                                        isVertical;
    
    float                                       internalPercent;
    
    float                                       percent;
    
    BOOL                                        isDragging;
}

@property (nonatomic, retain) id delegateSlider;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewThumb;

@property (nonatomic, retain) IBOutlet UIImageView *imageViewBackground;

@property (nonatomic, retain) IBOutlet UIView *viewBounds;

@property (nonatomic, assign) BOOL isVertical;

@property (nonatomic, assign) float percent;

- (void)touchImage:(UIImageView *)targetImageView withX:(float)targetX withY:(float)targetY;
- (void)correctOverlap;

- (void)setPercent:(float)targetPercent withNotification:(BOOL)targetNotify;

- (void)internalUpdate:(id)sender;

- (void)nuke;

@end

