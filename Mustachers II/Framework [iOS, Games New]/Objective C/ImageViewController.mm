//
//  ImageViewController.m
//  Wrangler
//
//  Created by Nick Raptis on 8/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ImageViewController.h"
#import "Root.h"

@implementation ImageViewController

@synthesize imageView;
@synthesize imagePath;


- (id)initWithImagePath:(NSString *)targetImagePath
{
    UIImage *aImage = nil;
    
    if(targetImagePath)
    {
        aImage = [gRoot loadImage:targetImagePath];
    }
    return [self initWithImage:aImage];
}

- (id)initWithImage:(UIImage *)targetImage
{
    
    self = [self initWithNibName:nil bundle:nil];
    
    float aWidth = 255;
    float aHeight = 255;
    
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    
    if(targetImage)
    {
        aWidth = targetImage.size.width;
        aHeight = targetImage.size.height;
    }
    
    if(self.view == nil)
    {
        NSLog(@"Whoops? No IVC Nib?");
        self.view = [[UIView alloc] initWithFrame:CGRectMake(0,0,aWidth,aHeight)];
        self.view.backgroundColor = [UIColor clearColor];
    }
    
    if(imageView == nil)
    {
        NSLog(@"Whoops?!?!?! IMAGE VIEW IS NULL TOO?!?!?!");
        
        self.imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0,0,aWidth,aHeight)];
        imageView.backgroundColor = [UIColor clearColor];
        [self.view addSubview:imageView];
        [self.view sendSubviewToBack:imageView];
    }
    
    self.view.frame = CGRectMake(0,0,aWidth,aHeight);
    imageView.frame = CGRectMake(0,0,aWidth,aHeight);
    
    
    imageView.image = targetImage;
    return self;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    return self;
}

- (void)dealloc
{
    
    NSLog(@"Dealloc[%@]", imagePath);
    
    [self nuke];
    
}

- (void)nuke
{
    self.imageView = nil;
    self.imagePath = nil;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    [self.view setUserInteractionEnabled:NO];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	return YES;
}

- (void)loadImage:(NSString*)targetImagePath
{
    
    VCHAX(self);
    
    FString aName;
    FString aString;
    UIImage *aImage;
    
    
    aName = FString([targetImagePath UTF8String]);
    aName.RemovePath(true);
    aString = aName;
    aString += "_cropped";
    imagePath = [[NSString alloc] initWithFormat:@"%s", aString.c()];
    aImage = [gRoot loadImage:imagePath];
    if(aImage)
    {
        NSLog(@"Image Size [%f, %f]", aImage.size.width, aImage.size.height);
        
        self.view.frame = CGRectMake(0,0,gAppWidth,gAppHeight);
        imageView.frame = CGRectMake(0,0,aImage.size.width, aImage.size.height);
        //[gRoot cropImage:[NSString stringWithUTF8String:(const char*)aName.c()] withImageView:imageView];
        
        imageView.image=aImage;
    }
    else
    {
        imagePath = nil;
        
        aString = aName;
        
        imagePath = [[NSString alloc] initWithFormat:@"%s.png", aString.c()];
        
        aImage = [gRoot loadImage:imagePath];
        
        if(!imagePath)
        {
            imagePath = [[NSString alloc] initWithFormat:@"%s.jpg", aString.c()];
            aImage = [gRoot loadImage:imagePath];
        }
        
        NSLog(@"Fucking Image: [%f, %f]", aImage.size.width, aImage.size.height);
        
        if(aImage)
        {
            self.view.frame = CGRectMake(0,0,aImage.size.width, aImage.size.height);
            imageView.frame = CGRectMake(0,0,aImage.size.width, aImage.size.height);
            imageView.image=aImage;
        }
        else
        {
            imageView.image=nil;
        }
    }
    
    [imageView setUserInteractionEnabled:NO];
}

@end
