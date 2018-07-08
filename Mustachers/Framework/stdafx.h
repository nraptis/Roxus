#pragma once

#define IPHONE

#include "Include.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Math.h"
#include "Randomizer.h"
#include "FString.h"
#include "Math.h"
#include "FPoint.h"
#include "Shapes.h"
#include "Graphics.h"
#include "Canvas.h"
#include "Button.h"
#include "Color.h"
#include "Object.h"
#include "Particle.h"
#include "Rectangle.h"
#include "Oscillator.h"
#include "Buffer.h"
#include "Sound.h"
#include "Achievement.h"
#include "OCInlets.h"

#import "glues_project.h"

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#define MAX_PATH (1024)

#define trace printf

/*

#define min(a,b) \
({ typeof (a) _a = (a); \
typeof (b) _b = (b); \
_a < _b ? _a : _b; })
 
#define max(a,b) \
({ typeof (a) _a = (a); \
typeof (b) _b = (b); \
_a > _b ? _a : _b; })
 
*/


#define O_BINARY 0

class Application;

extern Application *gApp;

extern Randomizer gRand;

extern FString gSandbox;

extern FString gDocuments;

extern float mGlobalTranslateX, mGlobalTranslateY;