#ifndef BASE_TOWER_H
#define BASE_TOWER_H

#include "raylib.h"
#include "raymath.h"
#include <string>
#include <vector>
#include <set>
#include <math.h>

#include "LineToLine.h"
#include "Tile.h"

class GameManager;
class BaseEnemy;

class BaseTower
{
protected:
    GameManager* m_GameManager;

protected: // NOTE: Cost Variables
    unsigned int m_SpeedCost;
    unsigned int m_FireRateCost;
    unsigned int m_RangeCost;

protected:
    // NOTE: Base Variables
    std::string m_Name;
    Vector2 m_Position;
    float m_Size;
    float m_Rotation;

    // NOTE: Tower Variables
    bool m_IsActive;
    Tile m_TowerTile;

    float m_Price;

    int m_Points;
    float m_ProjectileDamage;

    Vector2 m_Direction;
    float m_FireSpeed;
    float m_FireRate;

    float m_RotationSpeed;
    float m_RotationEase; // Lerping value thing

    float m_Range;
    bool m_ShowRange;

    int m_UpgradeLevel;
    int m_MaxUpgrade; // IMPORTANT_NOTE: Not to be used yet

    Color m_Colour;

    // NOTE: Projectiles
    float m_ProjectileCounter;

    // NOTE: Other Variables
    std::set<BaseEnemy*> m_Enemies;

    // NOTE: Points
    std::vector<LineToLine> m_PointDestination;

public:
    // CLASS FUNCTION(s)
    BaseTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile);
    virtual ~BaseTower();

    // CONSTRUCT(s) (1)
    virtual void Construct();

    // BASE FUNCTION(s)
    virtual void Update(const float deltaTime);
    virtual void Draw();

    // HELPER FUNCTION(s)
    void EnteredRadius();
    void CalculateLinePoints(int points);

    // GETTER(s)

    // BASE GETTER(s)
    inline std::string GetName() { return m_Name; }
    inline Vector2 GetPosition() { return m_Position; }
    inline float GetSize() { return m_Size; }
    inline float GetRotation() { return m_Rotation; }

    // COST GETTER(s)
    inline unsigned int GetSpeedCost() { return m_SpeedCost; }
    inline unsigned int GetFireRateCost() { return m_FireRateCost; }
    inline unsigned int GetRangeCost() { return m_RangeCost; }

    // TOWER GETTER(s)
    inline bool GetActive() { return m_IsActive; }
    inline int GetPoints() { return m_Points; }
    inline Vector2 GetDirection() { return m_Direction; }
    inline float GetProjectileDamage() { return m_ProjectileDamage; }
    inline float GetFireSpeed() { return m_FireSpeed; }
    inline float GetFireRate() { return m_FireRate; }
    inline float GetRotationSpeed() { return m_RotationSpeed; }
    inline float GetRange() { return m_Range; }
    inline float GetMaxUpgrade() { return m_MaxUpgrade; }
    inline Color GetColour() { return m_Colour; }
    inline int GetPrice() { return m_Price; }
    inline bool GetShowRange() { return m_ShowRange; }
    inline Tile GetTowerTile() { return m_TowerTile; }

    inline std::set<BaseEnemy*> GetEnemyList() { return m_Enemies; }

    // SETTER(s)

    // BASE SETTER(s)
    inline void SetName(std::string name) { this->m_Name = name; }
    inline void SetPosition(Vector2 position) { this->m_Position = position; }
    inline void SetSize(float size) { this->m_Size = size; }
    inline void SetRotation(float rotation) { this->m_Rotation = rotation; }

    // COST SETTER(s)
    inline void SetSpeedCost(unsigned int speedCost) { m_SpeedCost = speedCost; }
    inline void SetFireRateCost(unsigned int fireRateCost) { m_FireRateCost = fireRateCost; }
    inline void SetRangeCost(unsigned int rangeCost) { m_RangeCost = rangeCost; }

    // TOWER SETTER(s)
    inline void SetActive(bool active) { this->m_IsActive = active; }
    inline void SetPoints(int points) { this->m_Points = points; }
    inline void SetDirection(Vector2 direction) { this->m_Direction = direction; }
    inline void SetProjectileDamage(float projectileDamage) { this->m_ProjectileDamage = projectileDamage; }
    inline void SetFireSpeed(float fireSpeed) { this->m_FireSpeed = fireSpeed; }
    inline void SetFireRate(float fireRate) { this->m_FireRate = fireRate; }
    inline void SetRotationSpeed(float rotationSpeed) { this->m_RotationSpeed = rotationSpeed; }
    inline void SetRange(float range) { this->m_Range = range; }
    inline void SetMaxUpgrade(int maxUpgrade) { this->m_MaxUpgrade = maxUpgrade; }
    inline void SetColour(Color colour) { this->m_Colour = colour; }
    inline void SetPrice(int price) { this->m_Price = price; }
    inline void SetShowRange(bool show) { this->m_ShowRange = show; }
    inline void SetTowerTile(Tile tile) { this->m_TowerTile = tile; }

    inline void RemoveEnemyFromList(BaseEnemy* enemy) { m_Enemies.erase(enemy); }

    //
};

#endif