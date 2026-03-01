#include "SecondaryTower.h"
#include "GameManager.h"

SecondaryTower::SecondaryTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile)
    : BaseTower(gameManager, name, position, size, tile)
{
    // NOTE: Calculate Line Points for this tower
    CalculateLinePoints(4);

    m_SpeedCost = 180;
    m_FireRateCost = 230;
    m_RangeCost = 250;

    m_Price = 400;
}

SecondaryTower::~SecondaryTower()
{
}

void SecondaryTower::Update(const float deltaTime)
{
    // SUPER UPDATE
    BaseTower::Update(deltaTime);

    // CHILD UPDATE
    if (!m_Enemies.empty())
    {
        m_ProjectileCounter += deltaTime;
        if (m_ProjectileCounter > m_FireRate)
        {
            // NOTE: Get the direction to shoot towards
            Vector2 tempDirection = Vector2Normalize(Vector2Subtract((*m_Enemies.begin())->GetPosition(), this->m_Position));

            // NOTE: Secondary Fire Bullet Calculation
            // NOTE: Add projectile to the world
            // NOTE: Shoots a bullet forward and backwards
            m_GameManager->AddProjectile(m_Position, this, 2, tempDirection, m_FireSpeed * 100);
            m_GameManager->AddProjectile(m_Position, this, 2, Vector2{ tempDirection.x * -1.f, tempDirection.y * -1.f }, m_FireSpeed * 100);

            // NOTE: Reset Counter
            m_ProjectileCounter = 0.f;
        }
    }
    else
    {
        m_ProjectileCounter = 0.f;
    }
}

void SecondaryTower::Draw()
{
    // SUPER DRAW
    BaseTower::Draw();
}
