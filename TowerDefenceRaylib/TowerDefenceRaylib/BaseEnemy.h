#ifndef BASE_ENEMY_H
#define BASE_ENEMY_H

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>
#include <math.h>

#include "LineToLine.h"

class GameManager;

class BaseEnemy
{
protected:
    GameManager* m_GameManager;

protected:
    // NOTE: Base Variables
    std::string m_Name;
    Vector2 m_Position;
    float m_Size;
    float m_Rotation;

    // NOTE: Enemy Variables
    bool m_IsActive;
    float m_DetectionCircle;
    float m_HitCircle;

    float m_Health;
    float m_MaxHealth;
    float m_Damage;
    float m_PointsGiven;
    float m_Speed;

    Vector2 m_TargetDirection;

    // NOTE: Points
    std::vector<LineToLine> m_PointDestination;

public:
    // CLASS FUNCTION(s)
    BaseEnemy(GameManager* gameManager, std::string name, Vector2 position, float size);
    virtual ~BaseEnemy();

    // BASE FUNCTION()
    virtual void Update(const float deltaTime);
    virtual void Draw();

    // HELPER FUCNTION(s)
    void CalculateLinePoints(int points);

    // GETTER(s)

    // BASE GETTER(s)
    inline std::string GetName() { return m_Name; }
    inline Vector2 GetPosition() { return m_Position; }
    inline float GetSize() { return m_Size; }
    inline float GetRotation() { return m_Rotation; }

    // ENEMY GETTER(s)
    inline bool GetActive() { return m_IsActive; }
    inline float GetHealth() { return m_Health; }
    inline float GetMaxHealth() { return m_MaxHealth; }
    inline float GetDamage() { return m_Damage; }
    inline float GetSpeed() { return m_Speed; }
    inline float GetDetectionCircle() { return m_DetectionCircle; }
    inline float GetHitCircle() { return m_HitCircle; }

    // SETTER(s)

    // BASE SETTER(s)
    inline void SetName(std::string name) { this->m_Name = name; }
    inline void SetPosition(Vector2 position) { this->m_Position = position; }
    inline void SetSize(float size) { this->m_Size = size; }
    inline void SetRotation(float rotation) { this->m_Rotation = rotation; }

    // ENEMY SETTER(s)
    inline void SetActive(bool active) { this->m_IsActive = active; }
    inline void SetHealth(float health) { this->m_Health = health; }

    inline void SetMaxHealth(float maxHealth) { this->m_MaxHealth = maxHealth; }

    inline void SetDamage(float damage) { this->m_Damage = damage; }
    inline void TakeDamage(float damage) { this->m_Health -= m_Health > 0 ? damage : 0; }

    inline void SetSpeed(float speed) { this->m_Speed = speed; }

    inline void SetDetectionCircle(float radius) { this->m_DetectionCircle = radius; }
    inline void SetHitCircle(float radius) { this->m_HitCircle = radius; }

    //
};

#endif