#import "PagedViewScroller.h"
#import "Root.h"

@implementation PagedViewScroller

@synthesize delegate;

@synthesize scrollView, viewControllers;

@synthesize imageChevronRight;
@synthesize imageChevronLeft;

@synthesize pageCount;
@synthesize page;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    page=0;
    pageCount=0;
    
    self.scrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    VCHAX(self);
    
    return self;
}

- (void)dealloc
{
    
    NSLog(@"Paged View Controllahaha!!! Deallocating");
    
    for(UIViewController *aView in viewControllers)
    {
        if((NSNull *)aView == [NSNull null])
        {
            
        }
        else
        {
            [aView.view removeFromSuperview];
        }
    }
    
    self.delegate=nil;
    
    self.viewControllers=nil;
    
    self.imageChevronRight=nil;
    self.imageChevronLeft=nil;
    
    self.viewControllers=nil;
    self.scrollView=nil;
}

- (void)setPageCount:(int)targetPageCount
{
    pageCount = targetPageCount;
    
    NSMutableArray *controllers = [[NSMutableArray alloc] init];
    for(unsigned i=0;i<pageCount;i++)
    {
		[controllers addObject:[NSNull null]];
    }
    self.viewControllers = controllers;
    
    // a page is the width of the scroll view
    self.scrollView.pagingEnabled = YES;
    self.scrollView.contentSize = CGSizeMake(scrollView.frame.size.width * pageCount, scrollView.frame.size.height);
    self.scrollView.showsHorizontalScrollIndicator = NO;
    self.scrollView.showsVerticalScrollIndicator = NO;
    self.scrollView.scrollsToTop = NO;
    self.scrollView.delegate = self;
    
    [self.view addSubview:self.scrollView];
    
    [self loadScrollViewWithPage:0];
    [self loadScrollViewWithPage:1];
}

- (UIViewController*)viewForPage:(int)targetPage
{
    return [delegate viewForIndex:targetPage];
}

- (void)jumpToPage:(int)targetPage
{
    page = targetPage;
    
    // Switch the indicator when more than 50% of the previous/next page is visible
    CGFloat pageWidth = scrollView.frame.size.width;
    
    int aNewPage = floor((scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    if(aNewPage != page)
    {
        page = aNewPage;
    }
    
    // load the visible page and the page on either side of it (to avoid flashes when the user starts scrolling)
    [self loadScrollViewWithPage:page - 1];
    [self loadScrollViewWithPage:page];
    [self loadScrollViewWithPage:page + 1];
}

- (void)loadScrollViewWithPage:(int)targetPage
{
    if(targetPage < 0)return;
    if(targetPage >= pageCount)return;
    
    UIViewController *controller = [viewControllers objectAtIndex:targetPage];
    if((NSNull *)controller == [NSNull null])
    {
        controller = [self viewForPage:page];
        
        if(controller != nil)
        {
            [viewControllers replaceObjectAtIndex:targetPage withObject:controller];
            
            CGRect frame = self.scrollView.frame;
            frame.origin.x = frame.size.width * targetPage;
            frame.origin.y = 0;
            controller.view.frame = frame;
            [self.scrollView addSubview:controller.view];
            
            if(pageCount > 1)
            {
                if((imageChevronRight != nil) && (targetPage < (pageCount - 1)))
                {
                    UIImageView *aImageView = [[UIImageView alloc] initWithImage: imageChevronRight];
                    
                    if(aImageView)
                    {
                        float aWidth = aImageView.frame.size.width;
                        float aHeight = aImageView.frame.size.height;
                        aImageView.frame = CGRectMake(gAppWidth - aWidth - 10, gAppHeight2 - (aHeight / 2.0f), aWidth, aHeight);
                        
                        [controller.view addSubview:aImageView];
                    }
                    
                }
                if(imageChevronLeft && (page > 0))
                {
                    UIImageView *aImageView = [[UIImageView alloc] initWithImage: imageChevronLeft];
                    
                    if(aImageView)
                    {
                        float aWidth = aImageView.frame.size.width;
                        float aHeight = aImageView.frame.size.height;
                        aImageView.frame = CGRectMake(10, gAppHeight2 - (aHeight / 2.0f), aWidth, aHeight);
                        
                        [controller.view addSubview:aImageView];
                    }
                }
            }
        }
    }
}

- (void)scrollViewDidScroll:(UIScrollView *)sender
{
    // Switch the indicator when more than 50% of the previous/next page is visible
    CGFloat pageWidth = scrollView.frame.size.width;
    
    int aNewPage = floor((scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    if(aNewPage != page)
    {
        page = aNewPage;
    }
    
    // load the visible page and the page on either side of it (to avoid flashes when the user starts scrolling)
    [self loadScrollViewWithPage:page - 1];
    [self loadScrollViewWithPage:page];
    [self loadScrollViewWithPage:page + 1];
    
    // A possible optimization would be to unload the views+controllers which are no longer visible
}

// At the begin of scroll dragging, reset the boolean used when scrolls originate from the UIPageControl
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    
}

// At the end of scroll animation, reset the boolean used when scrolls originate from the UIPageControl
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    
}

- (IBAction)changePage:(id)sender
{
    // load the visible page and the page on either side of it (to avoid flashes when the user starts scrolling)
    [self loadScrollViewWithPage:page - 1];
    [self loadScrollViewWithPage:page];
    [self loadScrollViewWithPage:page + 1];
    
	// update the scroll view to the appropriate page
    CGRect frame = scrollView.frame;
    frame.origin.x = frame.size.width * page;
    frame.origin.y = 0;
    
    //[scrollView scrollRectToVisible:frame animated:YES];
	// Set the boolean used when scrolls originate from the UIPageControl. See scrollViewDidScroll: above.
    //pageControlUsed = YES;
}

@end







