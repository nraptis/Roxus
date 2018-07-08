//
//  DefaultBannerView.m
//  Template
//
//  Created by Nick Raptis on 11/1/10.
//  Copyright 2010 Raptisoft LLC. All rights reserved.
//

#import "DefaultBannerView.h"
#import "GLApp.h"
#import "Root.h"
#import "OCInlets.h"


@implementation DefaultBannerView

- (id)initWithFrame:(CGRect)frame
{
    if ((self = [super initWithFrame:frame]))
	{
        UIImage *aImage;// = [UIImage imageNamed:@"ad_default.png"];
        if(gIsIpad)
        {
            aImage = [UIImage imageNamed:@"ad_default_ipad.png"];
        }
        else
        {
            aImage = [UIImage imageNamed:@"ad_default.png"];
        }
		buttonBanner=[[UIButton alloc] initWithFrame:CGRectMake(0,0,self.frame.size.width,self.frame.size.height)];
		[buttonBanner setBackgroundImage:aImage forState:UIControlStateNormal];
		[buttonBanner addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
		[self addSubview:buttonBanner];
    }
    return self;
}

- (void) click:(UIButton*)sender
{
    //OpenURL((const char*)"itms://itunes.com/apps/sunshine-games");
    //OpenURL((const char*)"https://itunes.apple.com/us/artist/froggy-studios/id389062016");
    OpenURL((const char*)"itms-apps://itunes.com/apps/froggystudios");
}


@end