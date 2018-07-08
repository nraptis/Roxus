//
//  InfiniteLooper.m
//  FiatReloaded
//
//  Created by Nick Raptis on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "InfiniteLooper.h"
#import "ImageViewController.h"
#import "Root.h"

@implementation InfiniteLooper

@synthesize tileArray;

@synthesize scrollOffsetX;
@synthesize scrollOffsetY;
@synthesize scrollContent;

@synthesize horizontalScrollEnabled;
@synthesize verticalScrollEnabled;

@synthesize recognizerPan;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    horizontalScrollEnabled = NO;
    verticalScrollEnabled = NO;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
	
	tileWidth=0;
	tileHeight=0;
	
	gridWidth=0;
	gridHeight=0;
	
	scrollOffsetX=0;
	scrollOffsetY=0;
    
	dragMode=false;
	
	//touchStartOffsetX=0;
	//touchStartOffsetY=0;
	
	//touchStartFingerX=0;
	//touchStartFingerY=0;
	
	velocityDirX=0;
	velocityDirY=0;
	velocityMagnitude=0;
	
	scrollContent = [[UIView alloc] initWithFrame:CGRectMake(0,0,512,1280)];
    
	[self.view addSubview:scrollContent];
	
	recognizerPan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(didPan:)];
	recognizerPan.delegate = self;
	[self.view addGestureRecognizer:recognizerPan];
	
    return self;
}

- (void)viewDidUnload
{
    NSLog(@"Infinite Looper - View Did Unload");
    
    [super viewDidUnload];
    
    [gRoot removeGlobalUpdate:self];
}

- (void)viewDidLoad
{
    NSLog(@"Infinite Looper - View Did Load");
    
	[super viewDidLoad];
    
    [gRoot addGlobalUpdate:self];
}

- (void)doneWithTiles
{
	scrollContent.frame = CGRectMake(-tileWidth, -tileHeight, gridWidth*(tileWidth + 1), gridHeight*(tileHeight + 2));
    
    //if(verticalScrollEnabled)scrollOffsetX -= tileWidth;
    //if(horizontalScrollEnabled)scrollOffsetY -= tileHeight;
    
	[self updatePositions];
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
    velocityMagnitude = 0;
    dragMode = NO;
    
	return YES;
}

- (void)addTile:(UIViewController*)targetTile
{
	if(targetTile.view.frame.size.width > tileWidth)
	{
		tileWidth = targetTile.view.frame.size.width;
	}
	if(targetTile.view.frame.size.height > tileHeight)
	{
		tileHeight = targetTile.view.frame.size.height;
	}
    
    /*
	if(targetTile.gridX + 1 > gridWidth)
	{
		gridWidth = targetTile.gridX + 1;
	}
	if(targetTile.gridY + 1 > gridHeight)
	{
		gridHeight = targetTile.gridY + 1;
	}
    */
    
	[scrollContent addSubview:targetTile.view];
	if(tileArray==nil)tileArray = [[NSMutableArray alloc] init];
	[tileArray addObject:targetTile];
    
}

- (void)shiftWithX:(float)targetX withY:(float)targetY
{
    if(horizontalScrollEnabled)scrollOffsetX += targetX;
    if(verticalScrollEnabled)scrollOffsetY += targetY;
	[self updatePositions];
}

- (void)updatePositions
{
	int aShiftX = 0;
	int aShiftY = 0;
	
	if((tileWidth > 0) && (horizontalScrollEnabled == YES))
	{
		while(scrollOffsetX < 0)
		{
			touchStartOffsetX += tileWidth;
			scrollOffsetX += tileWidth;
			aShiftX --;
		}
		while(scrollOffsetX > tileWidth)
		{
			touchStartOffsetX -= tileWidth;
			scrollOffsetX -= tileWidth;
			aShiftX ++;
		}
	}
    
    if((tileHeight > 0) && (verticalScrollEnabled == YES))
	{
		while(scrollOffsetY < 0)
		{
			touchStartOffsetY += tileHeight;
			scrollOffsetY += tileHeight;
			aShiftY --;
		}
		while(scrollOffsetY > tileHeight)
		{
			touchStartOffsetY -= tileHeight;
			scrollOffsetY -= tileHeight;
			aShiftY ++;
		}
	}
    
    if(aShiftX != 0)
    {
        offsetIndexX += aShiftX;
        if(gridWidth > 0)
        {
            while(offsetIndexX < 0)offsetIndexX+=gridWidth;
            while(offsetIndexX >= gridWidth)offsetIndexX-=gridWidth;
        }
    }
    
    if(aShiftY != 0)
    {
        offsetIndexY += aShiftY;
        if(gridHeight > 0)
        {
            while(offsetIndexY < 0)offsetIndexY += gridHeight;
            while(offsetIndexY >= gridHeight)offsetIndexY -= gridHeight;
        }
    }
    
//	if(aShiftX != 0 || aShiftY != 0)
//	{
//		
//		offsetIndexY += aShiftY;
//		
//		while(offsetIndexY < 0)offsetIndexY+=gridHeight;
//		while(offsetIndexY >= gridHeight)offsetIndexY-=gridHeight;
//	}
    
    scrollContent.frame = CGRectMake((horizontalScrollEnabled ? (-tileWidth) : (0))
                                     + scrollOffsetX,
                                     
                                     (verticalScrollEnabled ? (-tileHeight) : (0))
                                     
                                     + scrollOffsetY,
                                     
									 self.view.frame.size.width + tileWidth,
									 self.view.frame.size.height + tileHeight);
    
    
    
    int aGridX = 0;
    int aGridY = 0;
    
	for(UIViewController *aTile in tileArray)
	{
        
        aTile.view.frame = CGRectMake(((offsetIndexX + aGridX) % gridWidth) * tileWidth,
                                      ((offsetIndexY + aGridY) % gridHeight) * tileHeight,
                                      tileWidth,
                                      tileHeight);
        
        
        //[aTile.view setBackgroundColor:[UIColor colorWithRed:0.66f green:0.55f blue:0.33f alpha:0.65f]];
        //float aCenter = aTile.view.frame.origin.y + (aTile.view.frame.size.height / 2.0f);
        //float aPercent = aCenter / (self.view.frame.size.height * 0.5f);
        //NSLog(@"Stats: [Center = %f] [Percent = %f]", aCenter, aPercent);
        //[aTile.view setTransform:CGAffineTransformMakeScale(aPercent, aPercent)];
        
        
        aGridX++;
        
        if(aGridX >= gridWidth)
        {
            aGridX = 0;
            aGridY++;
        }
	}
    
    
	
    
    
}

- (void)goVertical:(NSArray*)targetArray
{
    
    horizontalScrollEnabled = NO;
    verticalScrollEnabled = YES;
    
    for(NSString *aString in targetArray)
    {
        ImageViewController *aImage = [[ImageViewController alloc] initWithNibName:nil bundle:nil];
        [aImage loadImage:aString];
        [self addTile:aImage];
    }
    
    gridWidth = 1;
    gridHeight = ([targetArray count] - 1);
    
    [self doneWithTiles];
    
}

- (void)globalUpdate
{
    [self update];
}

- (void)update
{
    
	if(velocityMagnitude > 0 && dragMode == false)
	{
		
		velocityMagnitude *= 0.95f;
		velocityMagnitude -= 25.0f;
        
		if(velocityMagnitude < 0)
        {
            velocityMagnitude = 0;
        }
		
		[self shiftWithX:velocityDirX * velocityMagnitude * 0.01f withY:velocityDirY * velocityMagnitude * 0.01f];
	}
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	dragMode=false;
}

- (void)didPan:(UIPanGestureRecognizer*)recognizer
{
	dragMode=true;
    
	CGPoint aTranslation = [recognizerPan translationInView:self.view];
    
	[self shiftWithX:aTranslation.x withY:aTranslation.y];
	
	[recognizerPan setTranslation:CGPointMake(0, 0) inView:self.view];
	
	if(recognizerPan.state == UIGestureRecognizerStateEnded)
	{
		CGPoint aVelocity = [recognizerPan velocityInView:self.view];
		
		velocityDirX=aVelocity.x;
		velocityDirY=aVelocity.y;
		
		velocityMagnitude = velocityDirX * velocityDirX + velocityDirY * velocityDirY;
		
		if(velocityMagnitude > 1.0f)
		{
			velocityMagnitude = sqrtf(velocityMagnitude);
            
			velocityDirX /= velocityMagnitude;
			velocityDirY /= velocityMagnitude;
		}
		else
		{
			velocityMagnitude=0;
			velocityDirX=0;
			velocityDirY=0;
		}
        
        if(velocityMagnitude > 20000.0f)velocityMagnitude = 20000.0f;
        
		dragMode = false;
	}
}




- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}


- (void)didReceiveMemoryWarning
{
	
}

- (void)dealloc
{
    [self.view removeGestureRecognizer:recognizerPan];
    
    recognizerPan.delegate=nil;
    
    self.recognizerPan=nil;
    
    self.scrollContent=nil;
    
    self.tileArray=nil;
}

@end
