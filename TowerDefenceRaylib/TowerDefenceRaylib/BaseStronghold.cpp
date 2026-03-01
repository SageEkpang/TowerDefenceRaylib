#include "BaseStronghold.h"
#include "GameManager.h"

BaseStronghold::BaseStronghold(GameManager* gameManager, GridManager* gridManager, std::string name, Vector2 position, float size, float hitBox, float health, float shield, Vector2 shieldPosition, float shieldSize, Tile tile)
{
    m_GameManager = gameManager;
    m_GridManager = gridManager;

    this->m_Name = name;
    this->m_Position = position;
    this->m_Size = size;
    this->m_HitBox = hitBox;
    this->m_Health = health;
    this->m_Shield = shield;
    this->m_ShieldPosition = shieldPosition;
    this->m_ShieldSize = shieldSize;
    this->m_StrongholdTile = tile;
}

BaseStronghold::~BaseStronghold()
{

}

void BaseStronghold::Update(const float deltaTime)
{
    // NOTE: Take Damage from the enemies hitting the Stronghold
    if (!m_GameManager->GetEnemies().empty())
    {
        for (auto& w : m_GameManager->GetEnemies())
        {
            if (this->m_Shield > 0)
            {
                if (CheckCollisionCircles(m_ShieldPosition, m_ShieldSize, w->GetPosition(), w->GetHitCircle()))
                {
                    this->TakeShieldDamage(w->GetDamage());
                    m_GameManager->DeleteEnemy(w);
                    continue;
                }
            }
            else
            {
                if (CheckCollisionCircles(m_Position, m_Size, w->GetPosition(), w->GetHitCircle()))
                {
                    // NOTE: Delete the enemy and projectile
                    this->TakeHealthDamage(w->GetDamage());
                    m_GameManager->DeleteEnemy(w);
                    continue;
                }
            }
        }
    }

    // NOTE: Delete the tower if the reaches 0
    if (m_Health <= 0.f)
    {
        m_GridManager->ChangeTileID(this->m_StrongholdTile.indexSingle, TILE_ID_NONE);
        m_GameManager->DeleteStronghold(this);
    }
}

void BaseStronghold::Draw()
{
    // TODO: Draw the text needed for the health here

    if (m_Shield > 0)
    {
        DrawCircleLines(m_ShieldPosition.x, m_ShieldPosition.y, m_ShieldSize, GREEN);
    }

    DrawRectangleV(m_Position, Vector2{ m_Size, m_Size }, WHITE);

    // DrawText(TextFormat("%f", m_Shield), m_Position.x, m_Position.y, 20, GREEN);
    // DrawText(TextFormat("%f", m_Health), m_Position.x, m_Position.y, 20, WHITE);
}
