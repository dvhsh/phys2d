#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "main.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>

// Resource initialization
bool InitializeResources(void);
void CleanupResources(void);
char* GetResourcePath(const char* resourcePath);

// Text components
void TextComponent(
    S2D_Window *window, 
    const char *text, 
    Vector2 position, 
    Vector4 color, 
    int size
);

void TextComponent_Centered(
    S2D_Window *window,
    const char *text,
    Vector4 bounds,
    Vector4 color,
    int size
);

void ButtonComponent(
    S2D_Window *window, 
    const char *text, 
    bool *clicked, 
    Vector4 res, 
    Vector4 color, 
    Vector4 hoverColor
);

void SliderComponent(
    S2D_Window *window, 
    float *value, 
    Vector2 position, 
    Vector2 size, 
    Vector4 color, 
    Vector4 hoverColor
);

// Component state structures
typedef struct {
    bool isHovered;
    bool isPressed;
    Vector2 lastMousePos;
} ComponentState;

typedef struct {
    Vector4 normalColor;
    Vector4 hoverColor;
    Vector4 pressedColor;
    int fontSize;
    float cornerRadius;
    float borderWidth;
} ComponentStyle;

ComponentState CreateComponentState(void);
ComponentStyle CreateDefaultStyle(void);
bool IsPointInRect(Vector2 point, Vector4 rect);

#endif // COMPONENT_H