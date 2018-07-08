//
//  ImageViewController.h
//  Wrangler
//
//  Created by Nick Raptis on 8/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ImageViewController : UIViewController
{
    UIImageView                 *imageView;
    NSString                    *imagePath;
}

@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) NSString *imagePath;

- (void)nuke;

- (id)initWithImagePath:(NSString *)targetImagePath;
- (id)initWithImage:(UIImage *)targetImage;

- (void)loadImage:(NSString*)targetImagePath;

@end
