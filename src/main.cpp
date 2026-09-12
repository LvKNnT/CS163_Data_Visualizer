#include "raylib.h"
#include "Properties.h"
#include "Scene.h"
#include <bits/stdc++.h>

int main() {
    // Init game window
    InitWindow(1280, 800, "CS_163_Data_Visualizer");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(0);
    
    // Load assets
    Properties::LoadSounds();
    Properties::LoadMusics();
    Properties::LoadTextures();
    Properties::LoadFonts();
    
    // Inits
    srand(time(0));
    scene.Init();
    
    // Main game loop
    while (!WindowShouldClose()) {
        Properties::ResetCursor();
        if(IsKeyPressed(KEY_SPACE)) {
            Properties::ToggleScreen();
        }
        BeginDrawing(); {
            ClearBackground(RAYWHITE);
            scene.Run();
            Properties::RenderCursor();
        }
        EndDrawing();
    }
    
    // Unload assets
    Properties::Unload();
    
    // Deinit game window
    CloseWindow();
    CloseAudioDevice();
    return 0;
}