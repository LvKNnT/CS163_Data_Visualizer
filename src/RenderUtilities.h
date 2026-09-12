/*
This file provides basic utilities as an extension to the raylib library.
*/

#ifndef RENDER_UTILITIES_H
#define RENDER_UTILITIES_H

#include "raylib.h"
#include "raymath.h"

// Draws the text centered at a position (posX, posY) without custom font
inline void DrawTextCen(const char *text, int posX, int posY, int fontSize, Color color) {
    int textWidth =  MeasureText(text, fontSize);;
    int textX = posX - textWidth / 2;
    int textY = posY - fontSize / 2;  // The font size represents the height of the text
    DrawText(text, textX, textY, fontSize, color);
}

// Draws the text centered at a position (posX, posY) with custom font
inline void DrawTextCenEx(Font font, const char *text, float posX, float posY, int fontSize, int spacing, Color color) {
    Vector2 pos = MeasureTextEx(font, text, fontSize, spacing);
    pos.x = posX - pos.x / 2;
    pos.y = posY - pos.y / 2;  // The font size represents the height of the text
    DrawTextEx(font, text, pos, fontSize, spacing, color);
}

// Draws the text centered in the rectangle without custom fonts
inline void DrawTextRec(const char *text, Rectangle rec, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int textX = rec.x + (rec.width - textWidth) / 2;
    int textY = rec.y + (rec.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, color);
}

// Draws the text centered in the rectangle with custom fonts
inline void DrawTextRecEx(Font font, const char *text, Rectangle rec, int fontSize,int spacing, Color color) {
    Vector2 pos = MeasureTextEx(font, text, fontSize, spacing);
    pos.x = rec.x + (rec.width - pos.x) / 2;
    pos.y = rec.y + (rec.height - pos.y) / 2;
    DrawTextEx(font, text, pos, fontSize, spacing, color);
}

// Draws the text at up right the cursor without custom fonts
inline void DrawTextCursor(const char *text, int fontSize, Color color) {
    DrawRectangle(GetMousePosition().x, GetMousePosition().y - fontSize - 10, MeasureText(text, fontSize) + 10, fontSize + 10, {0, 0, 0, 100});
    int textX = GetMousePosition().x + 5;
    int textY = GetMousePosition().y - fontSize - 5;  // The font size represents the height of the text
    DrawText(text, textX, textY, fontSize, color);
}

// Draws the text at up right the cursor without custom fonts
inline void DrawTextCursorEx(Font font, const char *text, int fontSize, int spacing, Color color) {
    Vector2 pos = MeasureTextEx(font, text, fontSize, spacing);
    DrawRectangle(GetMousePosition().x, GetMousePosition().y - pos.y - 10, pos.x + 10, pos.y + 10, {0, 0, 0, 150});
    pos.x = GetMousePosition().x + 5;
    pos.y = GetMousePosition().y - pos.y - 5;  // The font size represents the height of the text
    DrawTextEx(font, text, pos, fontSize, spacing, color);
}

#endif //RENDER_UTILITIES_H