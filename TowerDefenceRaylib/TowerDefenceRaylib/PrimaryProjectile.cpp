#include "PrimaryProjectile.h"

PrimaryProjectile::PrimaryProjectile(GameManager* gameManager, BaseTower* owner, Vector2 position, float size, Vector2 direction, float speed, float rotation)
    : BaseProjectile(gameManager, owner, position, size, direction, speed, rotation)
{
}

PrimaryProjectile::~PrimaryProjectile()
{
}

void PrimaryProjectile::Update(const float deltaTime)
{
    // SUPER UPDATE
    BaseProjectile::Update(deltaTime);
}

void PrimaryProjectile::Draw()
{
    // SUPER DRAW
    BaseProjectile::Draw();
}
