#include "PrimaryStronghold.h"

PrimaryStronghold::PrimaryStronghold(GameManager* gameManager, GridManager* gridManager, std::string name, Vector2 position, float size, float hitBox, float health, float shield, Vector2 shieldPosition, float shieldSize, Tile tile)
    : BaseStronghold(gameManager, gridManager, name, position, size, hitBox, health, shield, shieldPosition, shieldSize, tile)
{
    m_HealthCost = 250;
    m_ShieldCost = 350;
    m_ShieldRadiusCost = 300;
}

PrimaryStronghold::~PrimaryStronghold()
{
}

void PrimaryStronghold::Update(const float deltaTime)
{
    // SUPER UPDATE
    BaseStronghold::Update(deltaTime);
}

void PrimaryStronghold::Draw()
{
    // SUPER DRAW
    BaseStronghold::Draw();
}
