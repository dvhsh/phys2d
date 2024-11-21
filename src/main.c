#include "main.h"
#include "scene.h"
#include "component.h"

static S2D_Window *window = NULL;

void spawnBall(S2D_Window *window) 
{
    if (ball == NULL) {
        ball = (BallActor*)malloc(sizeof(BallActor));
        ball->x = RES_WIDTH / 2;
        ball->y = RES_HEIGHT / 2;
        ball->radius = 10;
        ball->sectors = 100;
        ball->mass = 100.0f;
        ball->velocity = 0;
        ball->time = 0;
        memcpy(ball->color, gi_ballColor, sizeof(GLint) * 4);
    }
}

void update() 
{
    if (ball != NULL) {
        // Update time and calculate new position
        ball->time += 1.0f / iFPS;
        ball->velocity = STANDARD_GRAVITY * ball->time * PIXELS_PER_METER;
        
        // Update position
        ball->y += ball->velocity / iFPS;
        
        // Reset ball if it hits the ground
        if (ball->y >= RES_HEIGHT - ball->radius) {
            ball->y = RES_HEIGHT+ball->y;  // Reset to ceiling
            ball->time = 0;            // Reset time
            ball->velocity = 0;        // Reset velocity
        }
    }
}

void render(S2D_Window *window) 
{
    Vector2 res = { RES_WIDTH, RES_HEIGHT };
    DrawGrid(res, PIXELS_PER_METER, COLOR_GREEN);

    Vector2 pos = {10, 10};
    TextComponent(window, "phys2d", pos, COLOR_MAGENTA, 64);
}

int main() 
{
    if (!PlatformInit()) {
        printf("Failed to initialize platform-specific features\n");
        return -1;
    }

    printf("Running on: %s\n", GetPlatformName());

    if (!InitializeResources()) {
        printf("Failed to initialize resources\n");
        return -1;
    }

    if (TTF_Init() < 0) {
        printf("SDL_TTF could not initialize! Error: %s\n", TTF_GetError());
        return -1;
    }

    S2D_Diagnostics(true);

    window = S2D_CreateWindow(
        "phys2d",
        RES_WIDTH,
        RES_HEIGHT,
        update,
        render,
        S2D_RESIZABLE
    );

    if (!window) {
        printf("Failed to create window\n");
        CleanupResources();
        return -1;
    }

    window->fps_cap = iFPS;
    window->background.r = gi_backgroundColor[0];
    window->background.g = gi_backgroundColor[1];
    window->background.b = gi_backgroundColor[2];
    window->background.a = gi_backgroundColor[3];

    S2D_Show(window);
    
    CleanupResources();
    S2D_FreeWindow(window);
    return 0;
}
