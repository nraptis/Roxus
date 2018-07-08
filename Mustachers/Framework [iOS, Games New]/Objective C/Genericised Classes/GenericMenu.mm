//
//  GenericMenu.m
//  Chrysler300Reloaded
//
//  Created by Nick Raptis on 1/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GenericMenu.h"

@implementation GenericMenu

@synthesize delegateMenu;

@synthesize lastClickedRect;

@synthesize imageViewMenuBack;

@synthesize buttonMenuAction1;
@synthesize buttonMenuAction2;
@synthesize buttonMenuAction3;
@synthesize buttonMenuAction4;
@synthesize buttonMenuAction5;
@synthesize buttonMenuAction6;
@synthesize buttonMenuAction7;
@synthesize buttonMenuAction8;
@synthesize buttonMenuAction9;
@synthesize buttonMenuAction10;
@synthesize buttonMenuAction11;
@synthesize buttonMenuAction12;
@synthesize buttonMenuAction13;
@synthesize buttonMenuAction14;
@synthesize buttonMenuAction15;
@synthesize buttonMenuAction16;
@synthesize buttonMenuAction17;
@synthesize buttonMenuAction18;
@synthesize buttonMenuAction19;
@synthesize buttonMenuAction20;
@synthesize buttonMenuAction21;
@synthesize buttonMenuAction22;
@synthesize buttonMenuAction23;
@synthesize buttonMenuAction24;
@synthesize buttonMenuAction25;

@synthesize arrayMenuButtons;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)viewDidLoad
{
    
    self.arrayMenuButtons = [[NSMutableArray alloc] init];
    
    if(buttonMenuAction1 )[arrayMenuButtons addObject:buttonMenuAction1 ];
    if(buttonMenuAction2 )[arrayMenuButtons addObject:buttonMenuAction2 ];
    if(buttonMenuAction3 )[arrayMenuButtons addObject:buttonMenuAction3 ];
    if(buttonMenuAction4 )[arrayMenuButtons addObject:buttonMenuAction4 ];
    if(buttonMenuAction5 )[arrayMenuButtons addObject:buttonMenuAction5 ];
    if(buttonMenuAction6 )[arrayMenuButtons addObject:buttonMenuAction6 ];
    if(buttonMenuAction7 )[arrayMenuButtons addObject:buttonMenuAction7 ];
    if(buttonMenuAction8 )[arrayMenuButtons addObject:buttonMenuAction8 ];
    if(buttonMenuAction9 )[arrayMenuButtons addObject:buttonMenuAction9 ];
    if(buttonMenuAction10)[arrayMenuButtons addObject:buttonMenuAction10];
    if(buttonMenuAction11)[arrayMenuButtons addObject:buttonMenuAction11];
    if(buttonMenuAction12)[arrayMenuButtons addObject:buttonMenuAction12];
    if(buttonMenuAction13)[arrayMenuButtons addObject:buttonMenuAction13];
    if(buttonMenuAction14)[arrayMenuButtons addObject:buttonMenuAction14];
    if(buttonMenuAction15)[arrayMenuButtons addObject:buttonMenuAction15];
    if(buttonMenuAction16)[arrayMenuButtons addObject:buttonMenuAction16];
    if(buttonMenuAction17)[arrayMenuButtons addObject:buttonMenuAction17];
    if(buttonMenuAction18)[arrayMenuButtons addObject:buttonMenuAction18];
    if(buttonMenuAction19)[arrayMenuButtons addObject:buttonMenuAction19];
    if(buttonMenuAction20)[arrayMenuButtons addObject:buttonMenuAction20];
    if(buttonMenuAction21)[arrayMenuButtons addObject:buttonMenuAction21];
    if(buttonMenuAction22)[arrayMenuButtons addObject:buttonMenuAction22];
    if(buttonMenuAction23)[arrayMenuButtons addObject:buttonMenuAction23];
    if(buttonMenuAction24)[arrayMenuButtons addObject:buttonMenuAction24];
    if(buttonMenuAction25)[arrayMenuButtons addObject:buttonMenuAction25];
    
    
    
    
    
    for(UIButton *aButton in arrayMenuButtons)
    {
        aButton.backgroundColor = [UIColor clearColor];
    }
    
    
    [super viewDidLoad];
}

- (IBAction)click:(UIButton*)sender
{
    
    lastClickedRect = CGRectMake(sender.frame.origin.x,sender.frame.origin.y,sender.frame.size.width,sender.frame.size.height);
    
    if(arrayMenuButtons)
    {
        
        int aIndex=-1;
        int aCheck=0;
        
        for(UIButton *aButton in arrayMenuButtons)
        {
            if(aButton == sender)
            {
                aIndex=aCheck;
                break;
            }
            else
            {
                aCheck++;
                aIndex++;
            }
        }
        
        if(aIndex != -1)
        {
            [self menuAction:aIndex] ;
        }
        
    }
}

- (void)menuAction:(int)targetAction
{
    NSLog(@"[%@] Performing Action: (%d)", [self class], targetAction);
    
    if(delegateMenu)
    {
        if([delegateMenu respondsToSelector:(@selector(menuAction:fromMenu:))])
        {
            [delegateMenu menuAction:targetAction fromMenu:self];
        }
    }
}

- (void)nuke
{
    if(arrayMenuButtons)
    {
        for(UIButton *aButton in arrayMenuButtons)
        {
            [aButton removeFromSuperview];
        }
        [arrayMenuButtons removeAllObjects];
        self.arrayMenuButtons = nil;
    }
    self.buttonMenuAction1 = nil;
    self.buttonMenuAction2 = nil;
    self.buttonMenuAction3 = nil;
    self.buttonMenuAction4 = nil;
    self.buttonMenuAction5 = nil;
    self.buttonMenuAction6 = nil;
    self.buttonMenuAction7 = nil;
    self.buttonMenuAction8 = nil;
    self.buttonMenuAction9 = nil;
    self.buttonMenuAction10 = nil;
    self.buttonMenuAction11 = nil;
    self.buttonMenuAction12 = nil;
    self.buttonMenuAction13 = nil;
    self.buttonMenuAction14 = nil;
    self.buttonMenuAction15 = nil;
    self.buttonMenuAction16 = nil;
    self.buttonMenuAction17 = nil;
    self.buttonMenuAction18 = nil;
    self.buttonMenuAction19 = nil;
    self.buttonMenuAction20 = nil;
    self.buttonMenuAction21 = nil;
    self.buttonMenuAction22 = nil;
    self.buttonMenuAction23 = nil;
    self.buttonMenuAction24 = nil;
    self.buttonMenuAction25 = nil;
    
    self.delegateMenu=nil;
    
    self.imageViewMenuBack=nil;
}

- (void)dealloc
{
    NSLog(@"[%@ Dealloc!]", [self class]);
    
    
    
    [self nuke];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}

@end





