#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@protocol PagedViewScrollerDelegate <NSObject>

- (UIViewController*)viewForIndex:(int)targetIndex;

@end


@interface PagedViewScroller : UIViewController <UIScrollViewDelegate>
{
    
    UIScrollView *scrollView;
    NSMutableArray *viewControllers;
    
    UIImage *imageChevronRight;
    UIImage *imageChevronLeft;
    
    id <PagedViewScrollerDelegate>delegate;
    
    int pageCount;
    int currentPage;
    int page;
}

@property (nonatomic, retain) id delegate;

@property (nonatomic, retain) UIImage *imageChevronRight;
@property (nonatomic, retain) UIImage *imageChevronLeft;

@property (nonatomic, retain) UIScrollView *scrollView;
@property (nonatomic, retain) NSMutableArray *viewControllers;

@property (nonatomic, assign) int pageCount;
@property (nonatomic, assign) int page;

- (IBAction)changePage:(id)sender;
- (void)loadScrollViewWithPage:(int)targetPage;
- (void)scrollViewDidScroll:(UIScrollView *)sender;
- (void)jumpToPage:(int)targetPage;
- (UIViewController*)viewForPage:(int)targetPage;

@end



