#include "main.h"
#include "scene.h"

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

void ApplyGravityToActor(BallActor *actor) 
{
   
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
    
    // Draw ball
    if (ball != NULL) {
        S2D_DrawCircle(
            ball->x,
            ball->y,
            ball->radius,
            ball->sectors,
            ball->color[0], ball->color[1], ball->color[2], ball->color[3]
        );
    }
}

int main() 
{
    if (!PlatformInit()) {
        printf("Failed to initialize platform-specific features\n");
        return -1;
    }

    printf("Running on: %s\n", GetPlatformName());

    S2D_Window *window = S2D_CreateWindow(
        "phys2d",
        RES_WIDTH,
        RES_HEIGHT,
        update,
        render,
        S2D_RESIZABLE
    );

    if (!window) {
        return 1;
    }

    window->fps_cap = iFPS;
    window->background.r = gi_backgroundColor[0];
    window->background.g = gi_backgroundColor[1];
    window->background.b = gi_backgroundColor[2];
    window->background.a = gi_backgroundColor[3];

    // Create initial ball
    spawnBall(window);

    S2D_Show(window);
    
    // Cleanup
    if (ball != NULL) {
        free(ball);
        ball = NULL;
    }
    S2D_FreeWindow(window);
    return 0;
}