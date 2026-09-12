#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "raylib.h"
#include <string>

class Textbox {
public:
    Textbox();
    ~Textbox();

    // Process input
    void SetRec(Rectangle rec, Color recColor, Color hoveringColor);
    void SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor, Color hoveringColor);
    void SetFont(int fontSize, Color textColor, Font font);
    void SetText(std::string text);

    bool Check();
    bool State();
    int to_num();
    void Render();
    void Input();
    std::string Get();

private:
    enum BUTTON_STATE {
        NONE,
        HOVERING,
        HOLDING,
        CLICKED
    };
    BUTTON_STATE state;
    bool mode = true;
    
    // Input figure
    Rectangle rec;
    bool useRatio = false;
    float rx, dx, ry, dy;
    float rw, dw, rh, dh;
    Color recColor = BLANK;
    Color hoveringColor = Color{0, 0, 0, 255};

    // Input properties
    std::string text = "";
    int maxLength = 3;
    int fontSize = 0;
    Color textColor = GRAY;
    Font font = {};
    Sound sound = {};

    void ClickedSound();
    void UpdateState();
};

#endif //TEXTBOX_H
