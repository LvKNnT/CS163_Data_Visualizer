#include "Textbox.h"
#include "RenderUtilities.h"
#include "Properties.h"
#include "raylib.h"

Textbox::Textbox() {}
Textbox::~Textbox() {}

void Textbox::SetRec(Rectangle rec, Color recColor = BLANK, Color hoveringColor = Color{255, 255, 255, 0}) {
    this->useRatio = false;
    this->rec = rec;
    this->recColor = recColor;
    this->hoveringColor = hoveringColor;
}

void Textbox::SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor = BLANK, Color hoveringColor = Color{255, 255, 255, 0}) {
    this->useRatio = true;
    this->rx = rx;
    this->dx = dx;
    this->ry = ry;
    this->dy = dy;
    this->rw = rw;
    this->dw = dw;
    this->rh = rh;
    this->dh = dh;
    this->recColor = recColor;
    this->hoveringColor = hoveringColor;
}

void Textbox::SetFont(int fontSize = 0, Color textColor = GRAY, Font font = {}) {
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->font = font;
}

void Textbox::SetText(std::string text) {
    this->text = text;
}

void Textbox::Render() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    // Render debug box
    if(state == HOVERING) DrawRectangleRec(rec, hoveringColor);
    else DrawRectangleRec(rec, recColor);

    // Render text
    if(text != "") {
        if(font.texture.id == 0) {
            DrawTextRec(text.c_str(), rec, fontSize, textColor);
        }
        else {
            // DrawTextRecEx(font, text.c_str(), rec, fontSize, 2, textColor);

            // DrawText left
            Vector2 pos = MeasureTextEx(font, text.c_str(), fontSize, 2);
            pos.x = rec.x + (rec.height - pos.y) / 2;
            pos.y = rec.y + (rec.height - pos.y) / 2;
            DrawTextEx(font, text.c_str(), pos, fontSize, 2, textColor);
        }
    }
}

void Textbox::Input() {
    int key = GetCharPressed();
    while(key > 0) {
        if(32 <= key && key <= 125 && text.length() < maxLength) {
            text += (char) key;
        } 
        key = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
        text.pop_back();
    }
}

std::string Textbox::Get() {
    return this->text;
}

bool Textbox::State() {
    if(text.empty()) return false;
    for(const auto& ch : text) if(ch < '0' || ch > '9') return false;
    return true;
}

bool Textbox::Check() {
    UpdateState();

    // Render the cursor icon
    if(state != NONE) Properties::SetCursor(4);

    if (state == CLICKED) ClickedSound();
    return mode;
}

void Textbox::ClickedSound() {
    if (sound.frameCount != 0) {
        PlaySound(sound);
    }
}

void Textbox::UpdateState() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (state == HOLDING && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            state = CLICKED;
            mode = true;
        } else {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOLDING;
            } else if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOVERING;
            }
        }
    }
    else {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) mode = false;
        state = NONE;
    }
}