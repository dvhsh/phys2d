#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <simple2d.h>

#include <stdlib.h>
#include <stdio.h>

// libGenesis
#include "platform.h"
#include "vector.h"

// libEntropy
#include "kinematic.h"

#if PLATFORM == PLATFORM_MACOS_INTEL || PLATFORM == PLATFORM_MACOS_ARM
    #include <mach-o/dyld.h>  // for _NSGetExecutablePath
#endif

#define RES_WIDTH 500
#define RES_HEIGHT 500
#define PIXELS_PER_METER 10
#define STANDARD_GRAVITY 9.80665

static int iFPS = 60;
static GLint gi_gridColor[] = { 0, 255, 0, 255 };
static GLint gi_ballColor[] = { 255, 0, 0, 255 };
static GLint gi_backgroundColor[] = { 0, 0, 0, 255 };

typedef struct 
{
    float x, y;
    int radius, sectors;
    float mass; // in grams
    GLint color[4];
    float velocity;  
    float time; 
} BallActor;

// Global ball state
static BallActor *ball = NULL;

void ApplyGravityToActor(BallActor *actor);

#endif // MAIN_H
