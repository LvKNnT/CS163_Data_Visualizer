#include "Button.h"
#include "RenderUtilities.h"
#include "Properties.h"

Button::Button() {}
Button::~Button() {}

void Button::SetRec(Rectangle rec, Color recColor = BLANK, Color hoveringColor = Color{255, 255, 255, 0}) {
    this->useRatio = false;
    this->rec = rec;
    this->recColor = recColor;
    this->hoveringColor = hoveringColor;
}

void Button::SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor = BLANK, Color hoveringColor = Color{255, 255, 255, 0}) {
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

void Button::SetText(std::string text, int fontSize = 0, Color textColor = GRAY, Font font = {}) {
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->font = font;
}

void Button::SetHoveringText(std::string hoveringText, int fontSize = 0, Color textColor = GRAY, Font font = {}) {
    this->hoveringText = hoveringText;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->font = font;
}

void Button::SetSound(Sound sound) {
    this->sound = sound;
}

void Button::SetTexture(std::string name, std::string hoveringName){
    this->texture1 = Properties::textures[name];
    this->texture2 = Properties::textures[hoveringName];
}

void Button::SetHoveringTexture(std::string name) {
    this->hoveringTexture = Properties::textures[name];
}

void Button::Render() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    // Render debug box
    if(state == HOVERING) DrawRectangleRec(rec, hoveringColor);
    else DrawRectangleRec(rec, recColor);

    // Render subBox
    if(useSub && mode) {
        Rectangle subRec = !useRatio ? Rectangle{this->rec.x, this->rec.y, this->rec.width, this->rec.height} 
                                        : Rectangle{GetScreenWidth() * rx + dx - GetScreenWidth() * rw - dw, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
        DrawRectangleRec(subRec, RAYWHITE);
        DrawRectangleLinesEx(subRec, 1.0f, PINK);
    }
    
    // Render texture
    if(texture1.id != 0) {
        if(state == HOVERING && texture2.id != 0) {
            DrawTexturePro(texture2, (Rectangle) {0.0, 0.0, (float) texture2.width, (float) texture2.height}, rec, (Vector2) {0.0, 0.0}, 0.0, WHITE);
        }
        else DrawTexturePro(texture1, (Rectangle) {0.0, 0.0, (float) texture1.width, (float) texture1.height}, rec, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    }
    if(state == HOVERING && hoveringTexture.id != 0) {
        float h = 25.0f;
        Rectangle hoveringTextureRec = Rectangle{GetMousePosition().x, GetMousePosition().y - h, h / hoveringTexture.height * hoveringTexture.width, h};
        DrawTexturePro(hoveringTexture, (Rectangle) {0.0, 0.0, (float) hoveringTextureRec.width, (float) hoveringTextureRec.height}, hoveringTextureRec, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    }

    // Render text
    if(text != "") {
        if(font.texture.id == 0) {
            DrawTextRec(text.c_str(), rec, fontSize, textColor);
        }
        else DrawTextRecEx(font, text.c_str(), rec, fontSize, 2, textColor);
    }
    if(state == HOVERING && hoveringText != "") {
        if(font.texture.id == 0) {
            DrawTextCursor(hoveringText.c_str(), fontSize, textColor);
        }
        else DrawTextCursorEx(font, hoveringText.c_str(), fontSize, 2, textColor);
    }
}

bool Button::Check() {
    UpdateState();
    
    // Render the cursor icon
    if(state != NONE) Properties::SetCursor(4);

    if (state == CLICKED) ClickedSound();
    return state == CLICKED || (useSub && mode);
}

void Button::ClickedSound() {
    if (sound.frameCount != 0) {
        PlaySound(sound);
    }
}

void Button::SetSub() {
    useSub = true;
}

bool Button::State() {
    if(!useSub) return false;
    return mode;
}

void Button::UpdateState() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
    Rectangle subRec = !useRatio ? Rectangle{this->rec.x, this->rec.y, this->rec.width, this->rec.height} 
                                    : Rectangle{GetScreenWidth() * rx + dx - GetScreenWidth() * rw - dw, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (state == HOLDING && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            mode = !mode;
            state = CLICKED;
        } else {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && state == HOVERING) {
                state = HOLDING;
            } else if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOVERING;
            }
        }
    }
    else {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), subRec)) mode = false;
        state = NONE;
    }
}