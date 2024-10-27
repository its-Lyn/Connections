#include <raylib.h>

#include <stdlib.h>
#include <stdio.h>

// C is a crazy language
//                  - Eve

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Connections");
    SetTargetFPS(60);

    // Initialise
    const char* message = "Hello, World!";
    while (!WindowShouldClose()) {
        // Update
        
        // Calculate message position
        Font font = GetFontDefault();
        int font_size = 20;

        Vector2 measurements = MeasureTextEx(font, message, font_size, 1);
        Vector2 position = (Vector2) {
            (GetScreenWidth() - measurements.x) / 2, 
            (GetScreenHeight() - measurements.y) / 2
        };

        BeginDrawing();
            // Draw
            ClearBackground(RAYWHITE);

            DrawTextEx(font, message, position, font_size, 1, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}