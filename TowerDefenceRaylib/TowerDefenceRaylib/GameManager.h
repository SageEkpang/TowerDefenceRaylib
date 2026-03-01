#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// NOTE:  SCREEN CLASSES
#include "ScreenConstants.h"
#include "UIManager.h"

// NOTE: LEVEL CLASSES
#include "GridManager.h"

// NOTE: CLASSES
// NOTE: TOWERS
#include "PrimaryTower.h"
#include "SecondaryTower.h"
#include "ThirdTower.h"

// NOTE: PROJECTILE
#include "PrimaryProjectile.h"

// NOTE: ENEMY
#include "PrimaryEnemy.h"

// NOTE: STRONGHOLD
#include "PrimaryStronghold.h"

// NOTE: Base Includes
#include <vector>
#include <set>
#include <iostream>

enum TowerType
{
    TOWER_TYPE_PRIMARY = 1,
    TOWER_TYPE_SECONDARY,
    TOWER_TYPE_THIRD
};

enum GameState
{
    GAME_STATE_TITLE,
    GAME_STATE_MENU,
    GAME_STATE_GAMEPLAY,
    GAME_STATE_END
};

struct Line2D
{
    Vector2 startLine;
    Vector2 endLine;
};

class GameManager
{
private:
    bool m_ShouldStartGame;
    bool m_ShouldCloseGame;

private:
    GameState m_GameState;

private:
    float m_Money;
    float m_Score;
    unsigned int m_StrongholdCount;

    // NOTE: Enemy Spawning

    Line2D m_SpawnLines[4];
    float m_SpawnTimer;
    float m_SpawnCounter;
    // float m
    unsigned int m_EnemiesKilled;

private:
    // NOTE: Misc
    Color m_PlayButtonColour;
    Color m_ExitButtonColour;
    Color m_RetryButtonColour;

    // NOTE: Level Variables
    GridManager* m_GridManager;
    UIManager* m_UIManager;

    // NOTE: Tower Variables
    TowerType m_TowerType;
    std::set<BaseTower*> m_Towers;
    std::set<BaseEnemy*> m_Enemies;
    std::set<BaseProjectile*> m_Projectiles;
    std::set<BaseStronghold*> m_StrongHolds;

    std::vector<BaseTower*> m_DeleteListTowers;
    std::vector<BaseEnemy*> m_DeleteListEnemies;
    std::vector<BaseProjectile*> m_DeleteListProjectiles;
    std::vector<BaseStronghold*> m_DeleteListStrongHolds;

private:
    // GAME HELPER FUNCTION(s)
    void TitleUpdate(const float deltaTime);
    void TitleDraw();

    void MenuUpdate(const float deltaTime);
    void MenuDraw();

    void GameplayUpdate(const float deltaTime);
    void GameplayDraw();

    void EndUpdate(const float deltaTime);
    void EndDraw();

    void ResetGame();

    inline bool CloseGame() { return m_ShouldCloseGame; }

private:
    // HELPER FUNCTION(s)
    void DeleteEnemies();
    void DeleteTowers();
    void DeleteProjectiles();
    void DeleteStrongHolds();

public:
    // CLASS FUNCTION(s)
    GameManager();
    ~GameManager();

    // BASE FUNCTION(s)

    void Update(const float deltaTime);
    void Draw();

    // HELPER FUNCTION(s)
    void UpdateGameObjects(const float deltaTime);
    void DrawGameObjects();

    // GETTER(s)

    // GAMEPLAY FUNCTION(s)

    // BASIC FUNCTION(s)
    inline float GetMoney() { return m_Money; }
    inline float GetScore() { return m_Score; }
    inline int GetStrongholdCount() { return m_StrongholdCount; }
    std::set<BaseTower*> GetTowers() { return m_Towers; }
    std::set<BaseEnemy*> GetEnemies() { return m_Enemies; }
    std::set<BaseProjectile*> GetProject() { return m_Projectiles; }
    std::set<BaseStronghold*> GetStrongHolds() { return m_StrongHolds; }

    // SETTER(s)

    // GAMEPLAY FUNCTION(s)

    // BASIC FUNCTION(s)
    inline void AddMoney(float addFunds) { m_Money += addFunds; }
    inline void RemoveMoney(float removeFunds)
    {
        unsigned int tempMoney = m_Money;

        if ((tempMoney -= removeFunds) > 0)
        {
            m_Money -= removeFunds;
        }
    }

    inline void AddStrongholdCount(unsigned int addStrongholdCount) { m_StrongholdCount += addStrongholdCount; }
    inline void RemoveStrongholdCount(unsigned int removeStrongholdCount) { m_StrongholdCount -= removeStrongholdCount; }

    inline void AddScore(float addScore) { m_Score += addScore; }

    void AddPrimaryTower(std::string name, float size, float price);
    void AddSecondaryTower(std::string name, float size, float price);
    void AddThirdTower(std::string name, float size, float price);
    void AddEnemy(std::string name, float size);
    void AddEnemy(std::string name, Vector2 position, float size);
    void AddProjectile(Vector2 position, BaseTower* owner, float size, Vector2 direction, float speed = 300.f, float rotation = 0.f);
    void AddPrimaryStronghold(std::string name, float size, float hitBox, float health = 100.f, float shield = 100.f, float shieldSize = 10.f);

    inline void DeleteTower(BaseTower* tower) { m_DeleteListTowers.push_back(tower); }
    inline void DeleteProjectile(BaseProjectile* projectile) { m_DeleteListProjectiles.push_back(projectile); }
    inline void DeleteEnemy(BaseEnemy* enemy)
    {
        ++m_EnemiesKilled;
        m_Score += 10;
        m_DeleteListEnemies.push_back(enemy);
    }
    inline void DeleteStronghold(BaseStronghold* stronghold) { m_DeleteListStrongHolds.push_back(stronghold); }
};

#endif