#ifndef BASE_STRONG_HOLD_H
#define BASE_STRONG_HOLD_H

#include <raylib.h>
#include <raymath.h>
#include <string>

#include "Tile.h"

class GameManager;
class GridManager;

class BaseStronghold
{
private:
    GameManager* m_GameManager;
    GridManager* m_GridManager;

protected: // NOTE: Cost Variables
    unsigned int m_HealthCost;
    unsigned int m_ShieldCost;
    unsigned int m_ShieldRadiusCost;

protected:
    // NOTE: Base Variables
    std::string m_Name;
    Vector2 m_Position;
    float m_Size;
    float m_Rotation;

    // NOTE: Stronghold Variables
    bool m_IsActive;
    float m_Health;

    float m_Price;

    float m_Shield;
    Vector2 m_ShieldPosition;
    float m_ShieldSize;

    float m_HitBox;
    Tile m_StrongholdTile;

public:
    // CLASS FUNCTION(s)
    BaseStronghold(GameManager* gameManager, GridManager* gridManager, std::string name, Vector2 position, float size, float hitBox, float health, float shield, Vector2 shieldPosition, float shieldSize, Tile tile);
    virtual ~BaseStronghold();

    // BASE FUNCTION(s)
    virtual void Update(const float deltaTime);
    virtual void Draw();

    // GETTER(s)

    inline std::string GetName() { return m_Name; }
    inline Vector2 GetPosition() { return m_Position; }
    inline float GetSize() { return m_Size; }
    inline float GetRotation() { return m_Rotation; }

    // COST GETTER(s)
    inline unsigned int GetHealthCost() { return m_HealthCost; }
    inline unsigned int GetShieldCost() { return m_ShieldCost; }
    inline unsigned int GetShieldRadiusCost() { return m_ShieldRadiusCost; }

    inline float GetHealth() { return this->m_Health; }
    inline float GetShield() { return this->m_Shield; }
    inline float GetShieldSize() { return this->m_ShieldSize; }
    inline Tile GetStrongholdTile() { return this->m_StrongholdTile; }

    // SETTER(s)
    inline void SetName(std::string name) { this->m_Name = name; }
    inline void SetPosition(Vector2 position) { this->m_Position = position; }
    inline void SetSize(float size) { this->m_Size = size; }
    inline void SetRotation(float rotation) { this->m_Rotation = rotation; }

    // COST SETTER(s)
    inline void SetHealthCost(unsigned int healthCost) { m_HealthCost = healthCost; }
    inline void SetShieldCost(unsigned int shieldCost) { m_ShieldCost = shieldCost; }
    inline void SetShieldRadiusCost(unsigned int shieldRadiusCost) { m_ShieldRadiusCost = shieldRadiusCost; }

    inline void SetHealth(float health) { this->m_Health = health; }
    inline void AddHealth(float health) { this->m_Health += health; }

    inline void TakeHealthDamage(float damage)
    {
        if (this->m_Health <= 0)
        {
            this->m_Health = 0;
        }
        else
        {
            this->m_Health -= damage;
        }
    }

    inline void SetShield(float shield) { this->m_Shield = shield; }
    inline void AddShield(float shield) { this->m_Shield += shield; }
    inline void AddShieldSize(float size) { this->m_ShieldSize += size; }
    inline void SetShieldSize(float shieldSize) { this->m_ShieldSize = shieldSize; }

    inline void TakeShieldDamage(float damage)
    {
        if (this->m_Shield <= 0)
        {
            this->m_Shield = 0;
        }
        else
        {
            this->m_Shield -= damage;
        }
    }
};

#endif