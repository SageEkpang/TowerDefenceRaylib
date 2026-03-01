#include "PrimaryTower.h"
#include "GameManager.h"

PrimaryTower::PrimaryTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile)
    : BaseTower(gameManager, name, position, size, tile)
{
    // NOTE: Calculate Line Points for this Tower
    CalculateLinePoints(3);

    m_SpeedCost = 160;
    m_FireRateCost = 200;
    m_RangeCost = 230;

    m_Price = 200.f;
}

PrimaryTower::~PrimaryTower()
{
}

void PrimaryTower::Update(const float deltaTime)
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

            // NOTE: Primary Fire Bullet Calculation
            // NOTE: Add projectile to the world
            // NOTE: Shoots a bullet forward
            m_GameManager->AddProjectile(m_Position, this, 2, tempDirection, m_FireSpeed * 100);

            // NOTE: Reset Counter
            m_ProjectileCounter = 0.f;
        }
    }
    else
    {
        m_ProjectileCounter = 0.f;
    }
}

void PrimaryTower::Draw()
{
    // SUPER DRAW
    BaseTower::Draw();
}
