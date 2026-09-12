#include "Properties.h"

// using namespace Properties;

namespace Properties {
    // Window variables
    bool isFullscreen = false;

    // visual assets
    std::map<std::string, Texture> textures;
    int mouseMode = 0;
    
    // sound assets
    std::map<std::string, Sound> sounds;
    std::map<std::string, Music> musics;
    bool isMusicsMute, isSoundsMute;
    float musicsVolume, soundsVolume;

    // text assets
    std::map<std::string, Font> fonts;
    int fontSizes[] = {15, 45, 60, 80};

    // file paths
    std::string filePath = "";

    // Windows settings
    void ToggleScreen() {
        if (!isFullscreen) { // Toggle to fullscreen borderless mode
            isFullscreen = true;
            SetWindowState(FLAG_WINDOW_UNDECORATED);
            SetWindowPosition(0, 0);
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        }
        else { // Toggle to fixed resolution
            isFullscreen = false;
            ClearWindowState(FLAG_WINDOW_UNDECORATED);
            int monitor = GetCurrentMonitor();
            int x = GetMonitorWidth(monitor) / 2 - 1280 / 2;
            int y = GetMonitorHeight(monitor) / 2 - 800 / 2;
            SetWindowPosition(x, y);
            SetWindowSize(1280, 800);
        }
    }

    // Load all assets
    void LoadSounds() {
        for (const auto & entry : std::filesystem::directory_iterator(SOUNDS_PATH)) {
            // Load sound.
            Sound sound = LoadSound(entry.path().string().c_str());

            // Add sound to map of sounds.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            sounds[fileNameWithoutExtension] = sound;

            // Free sound data.
            // UnloadSound(sound);
        }

        // Initial values
        isSoundsMute = false;
        soundsVolume = 1.0f;
    }

    void LoadMusics() {
        // default value is 4096
        // testing value is 131072
        SetAudioStreamBufferSizeDefault(4096); 

        for (const auto & entry : std::filesystem::directory_iterator(MUSIC_PATH)) {
            // Load sound.
            Music music = LoadMusicStream(entry.path().string().c_str());

            // Add sound to map of sounds.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            musics[fileNameWithoutExtension] = music;

            // Free sound data.
            // UnloadSound(sound);
        }

        // Initial values
        isMusicsMute = false;
        musicsVolume = 1.0f;
    }

    void LoadTextures() {
        for (const auto & entry : std::filesystem::directory_iterator(TEXTURE_PATH)) {
            // Load and resize image.
            Image image = LoadImage(entry.path().string().c_str());
            Texture texture = LoadTextureFromImage(image);

            // Add texture to map of textures.
            std::string fileName = entry.path().filename().string();
            size_t dotIndex = fileName.find('.');

            std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex);
            textures[fileNameWithoutExtension] = texture;

            // Free image data.
            UnloadImage(image);
        }
    }

    void LoadFonts() {
        for (const auto & entry : std::filesystem::directory_iterator(FONTS_PATH)) {
            for(const auto & fontSize : fontSizes) {
                // Load font.
                Font font = LoadFontEx(entry.path().string().c_str(), fontSize, 0, 0);

                // Add font to map of fonts.
                std::string fileName = entry.path().filename().string();
                size_t dotIndex = fileName.find('.');

                std::string fileNameWithoutExtension = entry.path().filename().string().substr(0, dotIndex) + "_" + std::to_string(fontSize);
                fonts[fileNameWithoutExtension] = font;
                
                // Free font data.
                // UnloadFont(font);
            }
        }
    }

    void Unload() {
        for(auto& texture : textures) {
            UnloadTexture(texture.second);
        }
        
        for(auto& music : musics) {
            UnloadMusicStream(music.second);
        }
        
        for(auto& sound : sounds) {
            UnloadSound(sound.second);
        }
        
        for(auto& font : fonts) {
            UnloadFont(font.second);
        }
    }

    // Settings
    void SetSoundsVolume(float volume) {
        soundsVolume = volume;
        if(!isSoundsMute) {
            for(auto v : sounds) {
                SetSoundVolume(v.second, volume);
            }
        }
    }

    void MuteSounds() {
        if(!isSoundsMute) {
            isSoundsMute = true;
            for(auto v : sounds) {
                SetSoundVolume(v.second, 0.0f);
            }
        }
        else {
            isSoundsMute = false;
            for(auto v : sounds) {
                SetSoundVolume(v.second, soundsVolume);
            }
        }
    }

    void SetMusicsVolume(float volume) {
        musicsVolume = volume;
        if(!isMusicsMute) {
            for(auto v : musics) {
                SetMusicVolume(v.second, volume);
            }
        }
    }

    void MuteMusics() {
        if(!isMusicsMute) {
            isMusicsMute = true;
            for(auto v : musics) {
                SetMusicVolume(v.second, 0.0f);
            }
        }
        else {
            isMusicsMute = false;
            for(auto v : musics) {
                SetMusicVolume(v.second, musicsVolume);
            }
        }
    }

    void ResetCursor() {
        mouseMode = 0;
    }

    void SetCursor(int mode) {
        if(mode != 0) mouseMode = mode;
    }

    void RenderCursor() {
        SetMouseCursor(mouseMode);
    }
}