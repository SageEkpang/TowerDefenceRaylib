#include "ThirdTower.h"
#include "GameManager.h"

ThirdTower::ThirdTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile)
    : BaseTower(gameManager, name, position, size, tile)
{
    CalculateLinePoints(5);

    m_SpeedCost = 250;
    m_FireRateCost = 275;
    m_RangeCost = 325;

    m_Price = 800.f;
}

ThirdTower::~ThirdTower()
{
}

void ThirdTower::Update(const float deltaTime)
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

            // NOTE: Third Fire Bullet Calculation
            // NOTE: Add projectile to the world
            // NOTE: Shoots a bullet forward and side ways

            m_GameManager->AddProjectile(m_Position, this, 2, Vector2Rotate(tempDirection, 25.f), m_FireSpeed * 100);
            m_GameManager->AddProjectile(m_Position, this, 2, tempDirection, m_FireSpeed * 100);
            m_GameManager->AddProjectile(m_Position, this, 2, Vector2Rotate(tempDirection, 335.f), m_FireSpeed * 100);

            // NOTE: Reset Counter
            m_ProjectileCounter = 0.f;
        }
    }
    else
    {
        m_ProjectileCounter = 0.f;
    }
}

void ThirdTower::Draw()
{
    // SUPER DRAW
    BaseTower::Draw();
}
