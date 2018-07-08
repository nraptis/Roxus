//
//  InfiniteLooper.h
//  FiatReloaded
//
//  Created by Nick Raptis on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//



@interface InfiniteLooper : UIViewController <UIGestureRecognizerDelegate>
{
	UIView							*scrollContent;
	
	NSMutableArray					*tileArray;
	int								tileCount;
	
	int								tileWidth;
	int								tileHeight;
	
	int								gridWidth;
	int								gridHeight;
	
	int								offsetIndexX;
	int								offsetIndexY;
    
    BOOL                            horizontalScrollEnabled;
    BOOL                            verticalScrollEnabled;
	
	UIPanGestureRecognizer			*recognizerPan;
	
	float							scrollOffsetX;
	float							scrollOffsetY;
	
	bool							dragMode;
	
	float							touchStartOffsetX;
	float							touchStartOffsetY;
	
	float							touchStartFingerX;
	float							touchStartFingerY;
	
	float							velocityDirX;
	float							velocityDirY;
	float							velocityMagnitude;
}

@property (nonatomic, retain) UIPanGestureRecognizer *recognizerPan;
@property (nonatomic, retain) NSMutableArray *tileArray;
@property (nonatomic, retain) UIView *scrollContent;

@property (nonatomic, assign) float	scrollOffsetX;
@property (nonatomic, assign) float scrollOffsetY;

@property (nonatomic, assign) BOOL horizontalScrollEnabled;
@property (nonatomic, assign) BOOL verticalScrollEnabled;

- (void)globalUpdate;
- (void)update;

- (void)didPan:(UIPanGestureRecognizer*)recognizer;

- (void)bumpTilesLeft;
- (void)bumpTilesRight;

- (CGPoint)fixOffset:(CGPoint)targetPoint;
- (void)addTile:(UIViewController*)targetTile;

- (void)goVertical:(NSArray*)targetArray;

- (void)shiftWithX:(float)targetX withY:(float)targetY;

- (void)updatePositions;
- (void)doneWithTiles;

@end





