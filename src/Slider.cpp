#include "Slider.h"
#include "RenderUtilities.h"
#include "Properties.h"
#include <algorithm>

Slider::Slider() {}
Slider::~Slider() {
    UnloadSound(sound); 
}

void Slider::SetRec(Rectangle rec, Color recColor = BLANK, Color progressColor = Color{255, 109, 194, 255}, Color hoveringColor = Color{255, 255, 255, 100}) {
    this->useRatio = false;
    this->rec = rec;
    this->recColor = recColor;
    this->hoveringColor = hoveringColor;
    this->progressColor = progressColor;
}

void Slider::SetRatio(float rx, float dx, float ry, float dy, float rw, float dw, float rh, float dh, Color recColor = BLANK, Color progressColor = Color{255, 109, 194, 255}, Color hoveringColor = Color{255, 255, 255, 100}) {
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
    this->progressColor = progressColor;
    this->hoveringColor = hoveringColor;
}

void Slider::SetSound(Sound sound) {
    this->sound = sound;
}

void Slider::SetTexture(std::string name1, std::string name2){
    this->texture1 = Properties::textures[name1];
    this->texture2 = Properties::textures[name2];
}

void Slider::SetProgressRatio(float progress) {
    this->progress = progress;
}

void Slider::Render() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
    
    if(texture1.id != 0) {
        Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
        Rectangle progressRec = !useRatio ? Rectangle{this->rec.x + this->rec.width * this->progress - this->rec.height / 2, this->rec.y,
                                                        this->rec.height, this->rec.height} : 
                                            Rectangle{GetScreenWidth() * rx + dx + (GetScreenWidth() * rw + dw) * this->progress - (GetScreenHeight() * rh + dh) / 2, GetScreenHeight() * ry + dy,
                                                        GetScreenHeight() * rh + dh, GetScreenHeight() * rh + dh};

        DrawTexturePro(texture1, (Rectangle) {0.0, 0.0, (float) texture1.width, (float) texture1.height}, rec, (Vector2) {0.0, 0.0}, 0.0, WHITE); 
        DrawTexturePro(texture2, (Rectangle) {0.0, 0.0, (float) texture2.width, (float) texture2.height}, progressRec, (Vector2) {0.0, 0.0}, 0.0, WHITE);
    }
    else {
        Rectangle progressRec = !useRatio ? Rectangle{this->rec.x, this->rec.y, this->rec.width * this->progress, this->rec.height} : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, (GetScreenWidth() * rw + dw) * this->progress, GetScreenHeight() * rh + dh};
        Rectangle subRec = !useRatio ? Rectangle{this->rec.x - sub, this->rec.y - sub, this->rec.width + 2 * sub, this->rec.height + 2 * sub} 
                                        : Rectangle{GetScreenWidth() * rx + dx - sub, GetScreenHeight() * ry + dy - sub, GetScreenWidth() * rw + dw + 2 * sub, GetScreenHeight() * rh + dh + 2 * sub};
        if(state != NONE) DrawRectangleRec(subRec, hoveringColor);
        DrawRectangleRec(rec, recColor);
        DrawRectangleRec(progressRec, progressColor);
    }
}

bool Slider::Check() {
    UpdateState();
    
    // Render the cursor icon
    if(state != NONE) Properties::SetCursor(4);

    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};
    if(state == HOLDING) {
        float progress = float(GetMousePosition().x - rec.x) / rec.width;
        this->progress = std::min(std::max(progress, 0.0f), 1.0f);
    }
    if (state == CLICKED) {
        ClickedSound();
    }
    return state == CLICKED || state == HOLDING;
}

float Slider::Get() {
    return this->progress;
}

void Slider::ClickedSound() {
    if (sound.frameCount != 0) {
        PlaySound(sound);
    }
}

void Slider::UpdateState() {
    Rectangle rec = !useRatio ? this->rec : Rectangle{GetScreenWidth() * rx + dx, GetScreenHeight() * ry + dy, GetScreenWidth() * rw + dw, GetScreenHeight() * rh + dh};

    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        if (state == HOLDING && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            state = CLICKED;
        } else {
            if (state == HOVERING && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOLDING;
            } else if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOVERING;
            }
        }
    } else {
        if (state == HOLDING && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            state = CLICKED;
        } else {
            if (state == HOLDING && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                state = HOLDING;
            } else {
                state = NONE;
            }
        }
    }
}