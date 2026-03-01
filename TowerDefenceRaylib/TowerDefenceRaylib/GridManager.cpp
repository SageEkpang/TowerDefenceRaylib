#include "GridManager.h"

GridManager::GridManager(int screenWidth, int screenHeight)
{
    m_ScreenHeight = screenHeight;
    m_ScreenWidth = screenWidth;

    m_drawGrid = true;
    m_isActive = true;

    int Counter = -1;

    // NOTE: Draw Grid for 
    for (int i = 0; i < m_ScreenWidth / GRIDE_TILE_SIZE; ++i)
    {
        for (int j = 0; j < m_ScreenHeight / GRIDE_TILE_SIZE; ++j)
        {
            Rectangle rec = {
                (float)i * GRIDE_TILE_SIZE,
                (float)j * GRIDE_TILE_SIZE,
                GRIDE_TILE_SIZE,
                GRIDE_TILE_SIZE
            };

            ++Counter;
            m_GridSpaces.push_back(Tile(rec, GRAY, TILE_ID_NONE, (int)i, (int)j, Counter));
        }
    }
}

GridManager::~GridManager()
{
    m_GridSpaces.clear();
}

void GridManager::Update(const float deltaTime)
{
    // NOTE: Check if the grid is active
    if (m_isActive == false) { return; }

    // NOTE: Highlight Grid Space
    for (auto& v : m_GridSpaces)
    {
        // NOTE: Get the 
        if (CheckCollisionPointRec(GetMousePosition(), v.rec))
        {
            m_CurrentTileSelected = v;
            v.colour = GREEN;
            // break;
        }
        else
        {
            v.colour = Color{ 255, 255, 255, 10 };
        }
    }
}

void GridManager::Draw()
{
    if (m_drawGrid == false) { return; }

    for (auto& v : m_GridSpaces)
    {
        DrawRectangleLinesEx(v.rec, 1, v.colour);
    }
}


