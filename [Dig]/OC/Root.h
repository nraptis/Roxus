//
//  Root.h
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

//#import "app_global.h"

#import "RootBase.h"


#ifdef ANIMATION_MODE
#import "SABuildMenu.h"
#endif


#ifdef EDITOR_MODE

#import "EditorBoard.h"
#import "EditorMenu.h"

#endif

@interface Root : RootBase
{
    
#ifdef EDITOR_MODE
    EditorMenu                      *editorMenu;
#endif
    
#ifdef ANIMATION_MODE
    SABuildMenu                     *buildMenu;
#endif
    
    //CABuilderMenu                   *caBuilder;
}

#ifdef EDITOR_MODE
@property (nonatomic, strong) EditorMenu *editorMenu;
#endif

#ifdef ANIMATION_MODE
@property (nonatomic, strong) SABuildMenu *buildMenu;
#endif

//@property (nonatomic, strong) CABuilderMenu *caBuilder;

- (void)go;
- (void)begin;

@end

extern Root *gRoot;