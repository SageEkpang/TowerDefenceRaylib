#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <raymath.h>

enum TILE_ID
{
    TILE_ID_NONE,
    TILE_ID_TOWER,
    TILE_ID_ENEMY,
    TILE_ID_STRONG_HOLD
};

struct Tile
{
    Rectangle rec;
    Color colour;
    TILE_ID id;
    int indexX;
    int indexY;
    int indexSingle;

    Tile()
    {
        this->rec = Rectangle{ 0, 0, 0, 0 };
        this->colour = GRAY;
        this->id = TILE_ID_NONE;
        this->indexX = 0;
        this->indexY = 0;
        this->indexSingle = 0;
    }

    Tile(Rectangle rec)
    {
        this->rec = rec;
        this->colour = GRAY;
        this->id = TILE_ID_NONE;
        this->indexX = 0;
        this->indexY = 0;
        this->indexSingle = 0;
    }

    Tile(Rectangle rec, Color colour)
    {
        this->rec = rec;
        this->colour = colour;
        this->id = TILE_ID_NONE;
        this->indexX = 0;
        this->indexY = 0;
        this->indexSingle = 0;
    }

    Tile(Rectangle rec, Color colour, TILE_ID id)
    {
        this->rec = rec;
        this->colour = colour;
        this->id = id;
        this->indexX = 0;
        this->indexY = 0;
        this->indexSingle = 0;
    }

    Tile(Rectangle rec, Color colour, TILE_ID id, int indexX, int indexY, int indexSingle)
    {
        this->rec = rec;
        this->colour = colour;
        this->id = id;
        this->indexX = indexX;
        this->indexY = indexY;
        this->indexSingle = indexSingle;
    }
};

#endif