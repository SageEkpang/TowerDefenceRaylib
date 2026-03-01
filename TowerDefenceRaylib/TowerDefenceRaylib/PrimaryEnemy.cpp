#include "PrimaryEnemy.h"
#include "GameManager.h"
#include "BaseStronghold.h"

PrimaryEnemy::PrimaryEnemy(GameManager* gameManager, std::string name, Vector2 position, float size)
    : BaseEnemy(gameManager, name, position, size)
{
    CalculateLinePoints(4);
    m_PointsGiven = 20;

    // NOTE: Find Closest Stronghold
    if (!gameManager->GetStrongHolds().empty())
    {
        // NOTE: Work out the initial distance from the current enemy to the nearest strong hold
        auto itr = (*gameManager->GetStrongHolds().begin());

        // NOTE: Iterate through all of them and find the shortest distance
        // NOTE: Set thet target location to whatever the shortest location is

        // NOTE: Set the target direction to the first strong hold
        if (gameManager->GetStrongHolds().size() == 1)
        {
            m_TargetDirection = Vector2Normalize(Vector2Subtract(itr->GetPosition(), this->m_Position));
        }
        else if (gameManager->GetStrongHolds().size() > 1)
        {
            // NOTE: Find the closest one and target that
            float t_tempMag = Vector2Length(Vector2Subtract(itr->GetPosition(), this->m_Position));
            m_TargetDirection = Vector2Normalize(Vector2Subtract(itr->GetPosition(), this->m_Position));

            for (auto& s : m_GameManager->GetStrongHolds())
            {
                float t_tempLength = Vector2Length(Vector2Subtract(s->GetPosition(), this->m_Position));

                if (t_tempMag > t_tempLength)
                {
                    t_tempMag = t_tempLength;
                    m_TargetDirection = Vector2Normalize(Vector2Subtract(s->GetPosition(), this->m_Position));
                }
            }
        }
    }
}

PrimaryEnemy::~PrimaryEnemy()
{
}

void PrimaryEnemy::Update(const float deltaTime)
{
    // SUPER UPDATE
    BaseEnemy::Update(deltaTime);

    // CHILD UPDATE
}

void PrimaryEnemy::Draw()
{
    // SUPER DRAW
    BaseEnemy::Draw();

    // CHILD DRAW
}
