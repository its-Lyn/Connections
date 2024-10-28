#include <raylib.h>

#include <stdlib.h>
#include <stdio.h>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

#define FPS 0 // 0 means uncapped

// C is a crazy language
//                  - Eve

const char* message = "Hello, World!";

void loop() {
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

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Connections");

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(loop, FPS, 1);
#else
    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        loop();
    }
#endif

    CloseWindow();

    return 0;
}
