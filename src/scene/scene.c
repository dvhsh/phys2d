#include "scene.h"

void DrawGrid(Vector2 res, int gridSize, Vector4 color)
{
    const int CELL_WIDTH = res.x / gridSize;
    const int CELL_HEIGHT = res.y / gridSize;
    
    // Draw vertical lines
    for (int x = 0; x <= gridSize; x++) 
    {
        int xPos = x * CELL_WIDTH;
        S2D_DrawLine(
            xPos, 0, 
            xPos, res.y,
            1.0,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w
        );
    }
    
    // Draw horizontal lines
    for (int y = 0; y <= gridSize; y++) 
    {
        int yPos = y * CELL_HEIGHT;
        S2D_DrawLine(
            0, yPos,
            res.x, yPos,
            1.0,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w,
            color.x, color.y, color.z, color.w
        );
    }
}