#ifndef GRID_MANAGER_H
#define GRID_MANAGER_H

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "GridConstants.h"
#include "Tile.h"

class GridManager
{
private:

    // BASE VARIABLE(s)
    int m_ScreenWidth;
    int m_ScreenHeight;

    // GRID VARIABLE(s)
    bool m_drawGrid;
    bool m_isActive;

    std::vector<Tile> m_GridSpaces;

    Tile m_CurrentTileSelected;

public:

    // CLASS FUNCTION(s)
    GridManager(int screenWidth, int screenHeight);
    ~GridManager();

    // BASE FUNCTION(s)
    void Update(const float deltaTime);
    void Draw();

    // GETTER(s)
    Tile GetCurrentTileSelected() { return m_CurrentTileSelected; }
    std::vector<Tile> GetGrid() { return m_GridSpaces; }
    void ChangeTileID(TILE_ID newId) { m_GridSpaces[m_CurrentTileSelected.indexSingle].id = newId; }
    void ChangeTileID(int index, TILE_ID newId) { m_GridSpaces[index].id = newId; }

    // SETTER(s)

};

#endif