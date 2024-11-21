#include "component.h"

static S2D_Text* CreateTextObject(const char* text, int size) {
    const char* fontPath = GetResourcePath("fonts/JetBrainsMono-Regular.ttf");
    
    S2D_Text* textObj = S2D_CreateText(fontPath, text, size);
    if (textObj == NULL) {
        printf("Error - Failed to create text object\n");
        return NULL;
    }
    
    return textObj;
}

void TextComponent(
    S2D_Window *window, 
    const char *text, 
    Vector2 position, 
    Vector4 color,
    int size
) {
    const char* fontPath = GetResourcePath("fonts/JetBrainsMono-Regular.ttf");
    
    // Try to create text object
    S2D_Text *txt = S2D_CreateText(fontPath, text, size);
    if (!txt) {
        printf("Failed to create text object for: '%s'\n", text);
        return;
    }

    // Set position
    txt->x = position.x;
    txt->y = position.y;

    // Set color (normalize from 0-255 to 0-1)
    txt->color.r = color.x / 255.0f;
    txt->color.g = color.y / 255.0f;
    txt->color.b = color.z / 255.0f;
    txt->color.a = color.w / 255.0f;

    // Draw the text
    S2D_DrawText(txt);

    // Free the text object
    S2D_FreeText(txt);
}
