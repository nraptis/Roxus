//
//  OpenGLView.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "OpenGLView.hpp"

GLContextAttrs cContextAttrs = {8, 8, 8, 8, 24, 8, 0};

OpenGLView::OpenGLView() {
    
}

OpenGLView::~OpenGLView() {
    
}

void OpenGLView::SetGLContextAttrs(GLContextAttrs& glContextAttrs) {
    cContextAttrs = glContextAttrs;
}

GLContextAttrs OpenGLView::GetGLContextAttrs() {
    return cContextAttrs;
}
