#ifndef BASE_PROJECTILE_H
#define BASE_PROJECTILE_H

#include <raylib.h>
#include <raymath.h>
#include <string>

class BaseEnemy;
class BaseTower;
class GameManager;

class BaseProjectile
{
protected:
    GameManager* m_GameManager;

protected:
    // NOTE: Base Variables
    std::string m_Name;
    Vector2 m_Position;
    float m_Size;
    float m_Rotation;
    BaseTower* m_Owner;
    Sound m_HitSound;
    Sound m_EnemyDeath;

    //
    float m_Speed;
    Vector2 m_Direction;

public:
    // NOTE: CLASS FUNCTION(s)
    BaseProjectile(GameManager* gameManager, BaseTower* owner, Vector2 position, float size, Vector2 direction, float speed = 100.f, float rotation = 0.f);
    virtual ~BaseProjectile();

    // NOTE: BASE FUNCTION(s)
    virtual void Update(const float deltaTime);
    virtual void Draw();

    // GETTER(s)

    // SETTER(s)
};

#endif