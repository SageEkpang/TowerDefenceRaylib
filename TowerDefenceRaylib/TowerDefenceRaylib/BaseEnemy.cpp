#include "BaseEnemy.h"
#include "GameManager.h"
#include "BaseStronghold.h"

BaseEnemy::BaseEnemy(GameManager* gameManager, std::string name, Vector2 position, float size)
{
    m_GameManager = gameManager;

    // NOTE: Base Variables
    m_Name = name;
    m_Position = position;
    m_Size = size;
    m_Rotation = 0;
    m_DetectionCircle = 10.f;
    m_HitCircle = 8.f;

    m_Health = 100.f;
    m_MaxHealth = 100.f;

    m_Damage = 10.f;
    m_PointsGiven = 5.f;
    m_Speed = 20.f;

    // NOTE: Enemy Variables
    m_IsActive = false;
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Update(const float deltaTime)
{
    // NOTE: Move Enemy
    m_Position = Vector2Add(
        m_Position,
        Vector2{
            m_TargetDirection.x * m_Speed * deltaTime,
            m_TargetDirection.y * m_Speed * deltaTime });

    for (auto& v : m_PointDestination)
    {
        v.lineStart = Vector2Add(
            v.lineStart,
            Vector2{
                m_TargetDirection.x * m_Speed * deltaTime,
                m_TargetDirection.y * m_Speed * deltaTime });

        v.lineEnd = Vector2Add(
            v.lineEnd,
            Vector2{
                m_TargetDirection.x * m_Speed * deltaTime,
                m_TargetDirection.y * m_Speed * deltaTime });
    }
}

void BaseEnemy::Draw()
{
    // NOTE: Draw Enemy Lines
    DrawCircleV(m_Position, 2, RED);
    // DrawCircleLines(m_Position.x, m_Position.y, m_HitCircle, PURPLE);

    for (auto& v : m_PointDestination)
    {
        DrawLineV(v.lineStart, v.lineEnd, RED);
    }
}

void BaseEnemy::CalculateLinePoints(int points)
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
                Vector2Add(Vector2Multiply(t_endVec, Vector2{ m_Size, m_Size }), m_Position)));

        // NOTE: Add a part of the angle from this
        Angle += ResultAngle;
    }
}
