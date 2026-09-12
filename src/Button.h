#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

class Button {
public:
    Button();
    ~Button();

    // Process input
    void SetRec(Rectangle rec, Color recColor, Color hoveringColor);
    void SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor, Color hoveringColor);
    void SetText(std::string text, int fontSize, Color textColor, Font font);
    void SetHoveringText(std::string hoveringText, int fontSize, Color textColor, Font font);
    void SetSound(Sound sound);
    void SetTexture(std::string name, std::string hoveringName);
    void SetHoveringTexture(std::string name);
    void SetSub();

    void Render();
    bool Check();
    bool State();

private:
    enum BUTTON_STATE {
        NONE,
        HOVERING,
        HOLDING,
        CLICKED
    };
    BUTTON_STATE state;
    
    // Input figure
    Rectangle rec;
    bool useRatio = false;
    float rx, dx, ry, dy;
    float rw, dw, rh, dh;
    Color recColor = BLANK;
    Color hoveringColor = Color{255, 255, 255, 0};
    
    // Input sub figure
    bool useSub = false;
    bool mode;

    // Input properties
    std::string text = "";
    std::string hoveringText = "";
    int fontSize = 0;
    Color textColor = GRAY;
    Font font = {};
    Sound sound = {};
    Texture texture1 = {};
    Texture texture2 = {};
    Texture hoveringTexture = {};

    void ClickedSound();
    void UpdateState();
};

#endif //BUTTON_H
