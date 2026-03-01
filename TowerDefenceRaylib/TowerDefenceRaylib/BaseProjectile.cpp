#include "BaseProjectile.h"
#include "GameManager.h"

BaseProjectile::BaseProjectile(GameManager* gameManager, BaseTower* owner, Vector2 position, float size, Vector2 direction, float speed, float rotation)
{
    m_GameManager = gameManager;
    m_Owner = owner;
    m_Position = position;
    m_Size = size;
    m_Direction = direction;
    m_Speed = speed;
    m_Rotation = rotation;
    m_HitSound = LoadSound("Sound/BulletHit.wav");
    m_EnemyDeath = LoadSound("Sound/DeathSound.wav");
}

BaseProjectile::~BaseProjectile()
{
    UnloadSound(m_HitSound);
    UnloadSound(m_EnemyDeath);
}

void BaseProjectile::Update(const float deltaTime)
{
    // NOTE: Move Projectile
    m_Position = Vector2Add(
        m_Position,
        Vector2{
            m_Direction.x * m_Speed * deltaTime,
            m_Direction.y * m_Speed * deltaTime });

    // NOTE: Check if its outside of bounds
    if (m_Position.x < 0 ||
        m_Position.y < 0 ||
        m_Position.x > SCREEN_WIDTH ||
        m_Position.y > SCREEN_HEIGHT)
    {
        m_GameManager->DeleteProjectile(this);
        return;
    }

    // NOTE: Check enemy collision
    if (!m_GameManager->GetEnemies().empty())
    {
        for (auto& w : m_GameManager->GetEnemies())
        {
            if (CheckCollisionCircles(m_Position, m_Size, w->GetPosition(), w->GetHitCircle()))
            {
                // NOTE: Take Damage and see if the enemy needs to be destroyed
                w->TakeDamage(m_Owner->GetProjectileDamage());

                // NOTE: Destroy enemy if the health is at 0
                if (w->GetHealth() <= 0)
                {
                    SetSoundVolume(m_EnemyDeath, 0.1f);
                    PlaySound(m_EnemyDeath);

                    m_GameManager->AddMoney(75);
                    m_GameManager->AddScore(50);
                    m_GameManager->DeleteEnemy(w);
                }

                // NOTE: Delete Projectile on Hit
                SetSoundVolume(m_HitSound, 0.3f);
                PlaySound(m_HitSound);
                m_GameManager->DeleteProjectile(this);
            }
        }
    }
}

void BaseProjectile::Draw()
{
    DrawCircleV(m_Position, m_Size, WHITE);
}
