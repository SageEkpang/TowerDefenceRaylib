#include "BaseTower.h"
#include "GameManager.h"

BaseTower::BaseTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile)
{
    // NOTE:
    m_GameManager = gameManager;

    // NOTE: Base Variables
    m_Name = name;
    m_Position = position;
    m_Size = size;
    m_Rotation = 0;
    m_TowerTile = tile;

    m_ProjectileDamage = 50.f;

    // NOTE: Tower Variables
    m_IsActive = false;

    m_Points = 3;

    m_Direction = Vector2{ 0, -1 };
    m_FireSpeed = 1;
    m_FireRate = 1;

    m_RotationSpeed = 1;
    m_RotationEase = 1; // NOTE: Lerping Value thing

    m_ShowRange = false;
    m_Range = 30;

    m_UpgradeLevel = 1;
    m_MaxUpgrade = 2;
    m_Colour = WHITE;

    m_ProjectileCounter = 0.f;
}

BaseTower::~BaseTower()
{
    // NOTE: Base Variables
    m_Name = "NONE";
    m_Position = Vector2{ 0, 0 };
    m_Size = 1;
    m_Rotation = 0;

    // NOTE: Tower Variables
    m_IsActive = false;

    m_Points = 3;

    m_Direction = Vector2{ 0, -1 };
    m_FireSpeed = 1;
    m_FireRate = 1;

    m_RotationSpeed = 1;
    m_RotationEase = 1; // NOTE: Lerping Value thing

    m_Range = 1;

    m_UpgradeLevel = 1;
    m_MaxUpgrade = 2;
    m_Colour = WHITE;
}

void BaseTower::Construct()
{
    // NOTE: Base Variables
    m_Name = "NONE";
    m_Position = Vector2{ 0, 0 };
    m_Size = 1;
    m_Rotation = 0;

    m_ProjectileDamage = 10.f;

    // NOTE: Tower Variables
    m_IsActive = false;

    m_Points = 3;

    m_Direction = Vector2{ 0, -1 };
    m_FireSpeed = 1;
    m_FireRate = 1;

    m_RotationSpeed = 1;
    m_RotationEase = 1; // NOTE: Lerping Value thing

    m_Range = 1;

    m_UpgradeLevel = 1;
    m_MaxUpgrade = 2;
    m_Colour = WHITE;
}

void BaseTower::Update(const float deltaTime)
{
    // NOTE: Insert Projectile into List
    EnteredRadius();
}

void BaseTower::Draw()
{
    if (m_ShowRange == true)
    {
        // NOTE: Radius Name
        DrawCircleLines(m_Position.x, m_Position.y, m_Range, WHITE);
    }

    // NOTE: Draw Turret Lines
    for (auto& v : m_PointDestination)
    {
        DrawLineV(v.lineStart, v.lineEnd, m_Colour);
    }
}

void BaseTower::CalculateLinePoints(int points)
{
    int ResultAngle = 360 / points;
    int Angle = 0;

    m_PointDestination.clear();

    // NOTE: Point Array Calculation
    for (int i = 0; i < points; ++i)
    {
        float t_startDegree = Angle;
        float t_endDegree = Angle + ResultAngle;

        Vector2 t_startVec = Vector2Rotate(Vector2{ 0, -1 }, t_startDegree);
        Vector2 t_endVec = Vector2Rotate(Vector2{ 0, -1 }, t_endDegree);

        // NOTE: Push point to array
        m_PointDestination.push_back(
            LineToLine(
                Vector2Add(Vector2Multiply(t_startVec, Vector2{ m_Size, m_Size }), m_Position),
                Vector2Add(Vector2Multiply(t_endVec, Vector2{ m_Size, m_Size }), m_Position)
            )
        );

        // NOTE: Add a part of the angle from this
        Angle += ResultAngle;
    }
}

void BaseTower::EnteredRadius()
{
    if (!m_GameManager->GetEnemies().empty())
    {
        for (auto& enemy : m_GameManager->GetEnemies())
        {
            // NOTE: Check if the enemy is colliding and it is not in the set
            if (
                CheckCollisionCircles(this->m_Position, this->m_Range, enemy->GetPosition(), enemy->GetDetectionCircle()) == true &&
                m_Enemies.count(enemy) == 0)
            {
                m_Enemies.emplace(enemy);
            }
            // NOTE: If the enemy is not colliding and is in the list, remove it from the list
            else if (
                CheckCollisionCircles(this->m_Position, this->m_Range, enemy->GetPosition(), enemy->GetDetectionCircle()) == false &&
                m_Enemies.count(enemy) != 0)
            {
                m_Enemies.erase(enemy);
            }
        }
    }
}