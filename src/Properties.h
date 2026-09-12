#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <filesystem>
#include "raylib.h"
#include <bits/stdc++.h> // gg mr beast

namespace Properties { // Game properties
    // Window variables
    extern bool isFullscreen;

    // visual assets
    extern std::map<std::string, Texture> textures;
    extern int mouseMode;
    
    // sound assets
    extern std::map<std::string, Sound> sounds;
    extern std::map<std::string, Music> musics;
    extern bool isMusicsMute, isSoundsMute;
    extern float musicsVolume, soundsVolume;

    // text assets
    extern std::map<std::string, Font> fonts;
    extern int fontSizes[];

    // file paths
    extern std::string filePath;
    const std::string ASSETS_PATH = "../assets";
    const std::string SOUNDS_PATH = ASSETS_PATH + "/sounds"; // Sounds effects
    const std::string MUSIC_PATH = ASSETS_PATH + "/musics"; // Background musics
    const std::string TEXTURE_PATH = ASSETS_PATH + "/textures"; // titles element
    const std::string FONTS_PATH = ASSETS_PATH + "/fonts";
    const std::string SAVEFILES_PATH = "../savefiles";

    // Windows Settings
    extern void ToggleScreen();

    // Load all assets
    extern void LoadSounds();
    extern void LoadMusics();
    extern void LoadTextures();
    extern void LoadFonts();
    extern void Unload();

    // Settings
    extern void SetSoundsVolume(float volume);
    extern void MuteSounds();
    extern void SetMusicsVolume(float volume);
    extern void MuteMusics();

    extern void ResetCursor();
    extern void SetCursor(int mode);
    extern void RenderCursor();
}

#endif // PROPERTIES_H