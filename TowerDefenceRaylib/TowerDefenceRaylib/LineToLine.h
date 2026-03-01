#ifndef LINE_TO_LINE_H
#define LINE_TO_LINE_H

#include "raylib.h"
struct LineToLine
{
    Vector2 lineStart;
    Vector2 lineEnd;

    LineToLine(Vector2 lineStart, Vector2 lineEnd)
    {
        this->lineStart = lineStart;
        this->lineEnd = lineEnd;
    }
};

#endif