#include "GameManager.h"

GameManager::GameManager()
{
    // NOTE: Level Class Init
    m_GridManager = new GridManager(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_UIManager = new UIManager(this, m_GridManager);

    m_Money = 500;
    m_Score = 0;
    m_StrongholdCount = 3;

    m_GameState = GAME_STATE_TITLE;
    // m_GameState = GAME_STATE_END;
    m_ShouldCloseGame = false;
    m_EnemiesKilled = 0;

    m_PlayButtonColour = WHITE;
    m_ExitButtonColour = WHITE;
    m_RetryButtonColour = WHITE;

    // NOTE: Spawning Enemies
    m_SpawnCounter = 5;
    m_SpawnTimer = 0;

    m_SpawnLines[0] = Line2D{ Vector2{0, 0}, Vector2{SCREEN_WIDTH, 0} };                         // Top Line
    m_SpawnLines[1] = Line2D{ Vector2{0, SCREEN_HEIGHT}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT} }; // Bottom Line

    m_SpawnLines[2] = Line2D{ Vector2{0, 0}, Vector2{0, SCREEN_HEIGHT} };                       // Left Line
    m_SpawnLines[3] = Line2D{ Vector2{SCREEN_WIDTH, 0}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT} }; // Right Line

    m_Towers.clear();
    m_Enemies.clear();
    m_Projectiles.clear();
    m_StrongHolds.clear();
}

GameManager::~GameManager()
{
    delete m_GridManager;
    delete m_UIManager;

    if (!m_Towers.empty())
    {
        for (auto itr = m_Towers.begin(); itr != m_Towers.end(); ++itr)
        {
            delete* itr;
        }

        m_Towers.clear();
    }

    if (!m_Enemies.empty())
    {
        for (auto itr = m_Enemies.begin(); itr != m_Enemies.end(); ++itr)
        {
            delete* itr;
        }

        m_Enemies.clear();
    }

    if (!m_Projectiles.empty())
    {
        for (auto itr = m_Projectiles.begin(); itr != m_Projectiles.end(); ++itr)
        {
            delete* itr;
        }

        m_Projectiles.clear();
    }

    if (!m_StrongHolds.empty())
    {
        for (auto itr = m_StrongHolds.begin(); itr != m_StrongHolds.end(); ++itr)
        {
            delete* itr;
        }

        m_StrongHolds.clear();
    }
}

void GameManager::Update(const float deltaTime)
{
    // NOTE: Update the Game State
    switch (m_GameState)
    {
    case GAME_STATE_TITLE:
        TitleUpdate(deltaTime);
        break;

    case GAME_STATE_MENU:
        MenuUpdate(deltaTime);
        break;

    case GAME_STATE_GAMEPLAY:
        m_UIManager->Update(deltaTime);
        GameplayUpdate(deltaTime);
        break;

    case GAME_STATE_END:
        EndUpdate(deltaTime);
        break;

    default:
        break;
    }
}

void GameManager::Draw()
{
    // NOTE: Update the Game State
    switch (m_GameState)
    {
    case GAME_STATE_TITLE:
        TitleDraw();
        break;

    case GAME_STATE_MENU:
        MenuDraw();
        break;

    case GAME_STATE_GAMEPLAY:
        // NOTE: UI Game Objects
        m_UIManager->Draw();
        GameplayDraw();
        break;

    case GAME_STATE_END:
        EndDraw();
        break;

    default:
        break;
    }
}

void GameManager::UpdateGameObjects(const float deltaTime)
{
    // NOTE: Towers
    if (!m_Towers.empty())
    {
        for (auto& v : m_Towers)
        {
            // NOTE: Update Towers
            v->Update(deltaTime);
        }
    }

    // NOTE: Projectiles
    if (!m_Projectiles.empty())
    {
        for (auto& v : m_Projectiles)
        {
            v->Update(deltaTime);
        }
    }

    // NOTE: Enemies
    if (!m_Enemies.empty())
    {
        for (auto& v : m_Enemies)
        {
            v->Update(deltaTime);
        }
    }

    // NOTE: Enemies
    if (!m_StrongHolds.empty())
    {
        for (auto& v : m_StrongHolds)
        {
            v->Update(deltaTime);
        }
    }
}

void GameManager::DrawGameObjects()
{
    if (!m_Towers.empty())
    {
        for (auto& v : m_Towers)
        {
            v->Draw();
        }
    }

    if (!m_Projectiles.empty())
    {
        for (auto& v : m_Projectiles)
        {
            v->Draw();
        }
    }

    if (!m_Enemies.empty())
    {
        for (auto& v : m_Enemies)
        {
            v->Draw();
        }
    }

    if (!m_StrongHolds.empty())
    {
        for (auto& v : m_StrongHolds)
        {
            v->Draw();
        }
    }
}

void GameManager::AddPrimaryTower(std::string name, float size, float price)
{
    // TODO: Add JSON Code (all "entities")
    float tempMoney = m_Money;

    if ((tempMoney -= price) >= 0)
    {
        Tile tempTile = m_GridManager->GetCurrentTileSelected();
        tempTile.id = TILE_ID_TOWER;
        m_GridManager->ChangeTileID(TILE_ID_TOWER);

        m_Towers.emplace(new PrimaryTower(
            this,
            name,
            Vector2{
                tempTile.rec.x + (GRIDE_TILE_SIZE / 2) + 1,
                tempTile.rec.y + (GRIDE_TILE_SIZE / 2) + 1 },
                size,
                tempTile));

        m_Money -= price;
    }
}

void GameManager::AddSecondaryTower(std::string name, float size, float price)
{
    // TODO: Add JSON Code (all "entities")
    float tempMoney = m_Money;

    if ((tempMoney -= price) >= 0)
    {
        Tile tempTile = m_GridManager->GetCurrentTileSelected();
        tempTile.id = TILE_ID_TOWER;
        m_GridManager->ChangeTileID(TILE_ID_TOWER);

        m_Towers.emplace(new SecondaryTower(
            this,
            name,
            Vector2{
                tempTile.rec.x + (GRIDE_TILE_SIZE / 2) + 1,
                tempTile.rec.y + (GRIDE_TILE_SIZE / 2) + 1 },
                size,
                tempTile));

        m_Money -= price;
    }
}

void GameManager::AddThirdTower(std::string name, float size, float price)
{
    // TODO: Add JSON Code (all "entities")
    float tempMoney = m_Money;

    if ((tempMoney -= price) >= 0)
    {
        Tile tempTile = m_GridManager->GetCurrentTileSelected();
        tempTile.id = TILE_ID_TOWER;
        m_GridManager->ChangeTileID(TILE_ID_TOWER);

        m_Towers.emplace(new ThirdTower(
            this,
            name,
            Vector2{
                tempTile.rec.x + (GRIDE_TILE_SIZE / 2) + 1,
                tempTile.rec.y + (GRIDE_TILE_SIZE / 2) + 1 },
                size,
                tempTile));

        m_Money -= price;
    }
}

void GameManager::AddEnemy(std::string name, float size)
{
    // TODO: Do not need tile for enemy spawning
    Tile tempTile = m_GridManager->GetCurrentTileSelected();

    m_Enemies.emplace(new PrimaryEnemy(
        this,
        name,
        Vector2{
            tempTile.rec.x + (GRIDE_TILE_SIZE / 2) + 1,
            tempTile.rec.y + (GRIDE_TILE_SIZE / 2) + 1 },
            size));
}

void GameManager::AddEnemy(std::string name, Vector2 position, float size)
{

    m_Enemies.emplace(new PrimaryEnemy(
        this,
        name,
        position,
        size));
}

void GameManager::AddProjectile(Vector2 position, BaseTower* owner, float size, Vector2 direction, float speed, float rotation)
{
    m_Projectiles.emplace(new PrimaryProjectile(
        this,
        owner,
        position,
        size,
        direction,
        speed,
        rotation));
}

void GameManager::AddPrimaryStronghold(std::string name, float size, float hitBox, float health, float shield, float shieldSize)
{
    // NOTE: Check if there are still strongholds to place down, if not, return the function
    if (m_StrongholdCount <= 0)
    {
        return;
    }

    Tile tempTile = m_GridManager->GetCurrentTileSelected();
    tempTile.id = TILE_ID_STRONG_HOLD;
    m_GridManager->ChangeTileID(TILE_ID_STRONG_HOLD);

    m_StrongHolds.emplace(new PrimaryStronghold(
        this,
        m_GridManager,
        name,
        Vector2{
            (tempTile.rec.x + (GRIDE_TILE_SIZE / 2) + 1) - (size / 2),
            (tempTile.rec.y + (GRIDE_TILE_SIZE / 2) + 1) - (size / 2) },
            size,
            hitBox,
            health,
            shield,
            Vector2{
                (tempTile.rec.x + (GRIDE_TILE_SIZE / 2) + 1),
                (tempTile.rec.y + (GRIDE_TILE_SIZE / 2) + 1) },
                shieldSize,
                tempTile));

    RemoveStrongholdCount(1);
}

void GameManager::DeleteEnemies()
{
    // NOTE: Skip if empty
    if (m_DeleteListEnemies.empty())
    {
        m_DeleteListEnemies.clear();
        return;
    }

    // NOTE: Remove enemy from tower radius list
    for (auto& t : m_Towers)
    {
        if (!t->GetEnemyList().empty())
        {
            for (size_t i = 0; i < m_DeleteListEnemies.size(); ++i)
            {
                if (t->GetEnemyList().count(m_DeleteListEnemies[i]) != 0)
                {
                    t->RemoveEnemyFromList(m_DeleteListEnemies[i]);
                }
            }
        }
    }

    // NOTE: Loop through the enemies and erase
    for (size_t i = 0; i < m_DeleteListEnemies.size(); ++i)
    {
        m_Enemies.erase(m_DeleteListEnemies[i]);
    }

    m_DeleteListEnemies.clear();
}

void GameManager::DeleteTowers()
{
    if (m_DeleteListTowers.empty())
    {
        m_DeleteListTowers.clear();
        return;
    }

    // NOTE: Loop through the towers and erase
    for (size_t i = 0; i < m_DeleteListTowers.size(); ++i)
    {
        m_Towers.erase(m_DeleteListTowers[i]);
    }

    m_DeleteListTowers.clear();
}

void GameManager::DeleteProjectiles()
{
    if (m_DeleteListProjectiles.empty())
    {
        m_DeleteListProjectiles.clear();
        return;
    }

    // NOTE: Loop through the projectile and erase
    for (size_t i = 0; i < m_DeleteListProjectiles.size(); ++i)
    {
        m_Projectiles.erase(m_DeleteListProjectiles[i]);
    }

    m_DeleteListProjectiles.clear();
}

void GameManager::DeleteStrongHolds()
{
    if (m_DeleteListStrongHolds.empty())
    {
        m_DeleteListStrongHolds.clear();
        return;
    }

    // NOTE: Loop through the towers and erase
    for (size_t i = 0; i < m_DeleteListStrongHolds.size(); ++i)
    {
        m_StrongHolds.erase(m_DeleteListStrongHolds[i]);
    }

    m_DeleteListStrongHolds.clear();
}

void GameManager::TitleUpdate(const float deltaTime)
{
    // NOTE: switch to Main Menu Page
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        m_GameState = GAME_STATE_MENU;
    }
}

void GameManager::TitleDraw()
{
    // NOTE:
    DrawText("3-Bit Tower Defence", (SCREEN_WIDTH / 2) - 160, (SCREEN_HEIGHT / 2) - 40, 30, WHITE);
    DrawText("Click to Start", (SCREEN_WIDTH / 2) - 70, (SCREEN_HEIGHT / 2), 20, GRAY);
    DrawRectangleLines(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, WHITE);
}

void GameManager::MenuUpdate(const float deltaTime)
{
    // NOTE: Play Button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{
                                                       (SCREEN_WIDTH / 2) - 40,
                                                       (SCREEN_HEIGHT / 2) - 40,
                                                       65,
                                                       30 }))
    {
        m_PlayButtonColour = GRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            m_GameState = GAME_STATE_GAMEPLAY;
        }
    }
    else
    {
        m_PlayButtonColour = WHITE;
    }

    // NOTE: Exit Button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{
                                                       (SCREEN_WIDTH / 2) - 40,
                                                       (SCREEN_HEIGHT / 2),
                                                       60,
                                                       30 }))
    {
        m_ExitButtonColour = GRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            delete this;
            m_ShouldCloseGame = true;
            CloseWindow();
            exit(0);
        }
    }
    else
    {
        m_ExitButtonColour = WHITE;
    }
}

void GameManager::MenuDraw()
{
    DrawText("3-Bit Tower Defence", (SCREEN_WIDTH / 2) - 160, (SCREEN_HEIGHT / 2) - 80, 30, WHITE);

    DrawText("Play", (SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2) - 40, 30, m_PlayButtonColour);
    DrawRectangleLines((SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2) - 40, 65, 30, BLANK);

    DrawText("Exit", (SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2), 30, m_ExitButtonColour);
    DrawRectangleLines((SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2), 60, 30, BLANK);

    DrawRectangleLines(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, WHITE);
}

void GameManager::GameplayUpdate(const float deltaTime)
{
    // NOTE: Level Updates
    m_GridManager->Update(deltaTime);

    // NOTE: Give another stronghold back once 50 enemies have been killed
    if (m_EnemiesKilled >= 150u)
    {
        ++m_StrongholdCount;
        float tempSpawnCount = m_SpawnCounter;
        m_SpawnCounter = tempSpawnCount - 1 == 0 ? m_SpawnCounter : --m_SpawnCounter;
        m_EnemiesKilled = 0;
    }

    // NOTE: Place Turret Down (Each if for each tower)
    if (
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        m_GridManager->GetGrid()[m_GridManager->GetCurrentTileSelected().indexSingle].id == TILE_ID_NONE &&
        m_UIManager->GetHoverButton() == false)
    {
        switch (m_UIManager->GetPressedType())
        {
            // NOTE: Tower(s)
        case PRESSED_TYPE_PRIMARY_TOWER:
            AddPrimaryTower("PrimaryTower", 10, 100);
            break;
        case PRESSED_TYPE_SECONDARY_TOWER:
            AddSecondaryTower("SecondaryTower", 10, 250);
            break;
        case PRESSED_TYPE_THIRD_TOWER:
            AddThirdTower("ThirdTower", 10, 500);
            break;

            // NOTE: Strong Hold(s)
        case PRESSED_TYPE_PRIMARY_STRONG_HOLD:
            AddPrimaryStronghold("PrimaryStronghold", 10, 10, 100.f, 100.f, 20.f);
            break;

        case PRESSED_TYPE_NONE:
            break;
        default:
            break;
        }
    }

    if (m_StrongHolds.size() >= 1)
    {
        // NOTE: Spawning Enemies
        m_SpawnTimer += deltaTime;
        if (m_SpawnTimer >= m_SpawnCounter)
        {
            Vector2 tempPosition;

            int t_randomLine = GetRandomValue(0, 3);
            Line2D t_chosenLine = m_SpawnLines[t_randomLine];

            float lineStart = GetRandomValue(t_chosenLine.startLine.x, t_chosenLine.endLine.x);
            float lineEnd = GetRandomValue(t_chosenLine.startLine.y, t_chosenLine.endLine.y);

            tempPosition = Vector2{ lineStart, lineEnd };

            AddEnemy("PrimaryEnemy", tempPosition, 10);
            m_SpawnTimer = 0;
        }
    }

    // NOTE: Place Enemy
    // if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) &&
    //     m_GridManager->GetGrid()[m_GridManager->GetCurrentTileSelected().indexSingle].id == TILE_ID_NONE)
    // {
    //     AddEnemy("PrimaryEnemy", 10);
    // }

    // NOTE: Does this for each tower (Need an if for each tower type)
    for (auto& t : m_Towers)
    {
        if (
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), t->GetPosition(), t->GetSize()) &&
            m_UIManager->GetPressedType() == PRESSED_TYPE_NONE)
        {
            // NOTE: Quick check to turn the switch turrets radius off
            if (m_UIManager->GetTargetTower() != nullptr)
            {
                m_UIManager->GetTargetTower()->SetShowRange(false);
            }

            m_UIManager->SetTargetStronghold(nullptr);
            m_UIManager->SetTargetTower(t);
            t->SetShowRange(true);
            m_UIManager->SetShowUI(true);
            break;
        }
    }

    for (auto& s : m_StrongHolds)
    {
        if (
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), s->GetPosition(), s->GetSize()) &&
            m_UIManager->GetPressedType() == PRESSED_TYPE_NONE)
        {
            // NOTE: Quick check to turn the switch turrets radius off
            if (m_UIManager->GetTargetTower() != nullptr)
            {
                m_UIManager->GetTargetTower()->SetShowRange(false);
            }

            m_UIManager->SetTargetTower(nullptr);
            m_UIManager->SetTargetStronghold(s);
            m_UIManager->SetShowUI(true);
            break;
        }
    }

    // NOTE: Exits out the close for each tower
    if (m_UIManager->GetCloseButton()->ButtonPressed() == true && m_UIManager->GetShowUI() == true)
    {
        if (m_UIManager->GetTargetTower() != nullptr)
        {
            m_UIManager->GetTargetTower()->SetShowRange(false);
        }

        m_UIManager->SetShowUI(false);
        m_UIManager->GetCloseButton()->SetButtonState(false);
    }

    // NOTE: Update Game Objects
    UpdateGameObjects(deltaTime);

    // NOTE: Deleting Code (Deletes Projectile as well)
    DeleteTowers();
    DeleteProjectiles();
    DeleteEnemies();
    DeleteStrongHolds();

    // NOTE: End Game Condition
    if (m_StrongholdCount == 0 && m_StrongHolds.size() == 0)
    {
        m_GameState = GAME_STATE_END;
    }
}

void GameManager::GameplayDraw()
{
    if (m_UIManager->GetToggleOn() == true)
    {
        m_GridManager->Draw();
    }

    DrawGameObjects();
}

void GameManager::EndUpdate(const float deltaTime)
{
    // NOTE: Play Button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{
                                                       (SCREEN_WIDTH / 2) - 55,
                                                       (SCREEN_HEIGHT / 2) - 40,
                                                       90,
                                                       30 }))
    {
        m_RetryButtonColour = GRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            ResetGame();
        }
    }
    else
    {
        m_RetryButtonColour = WHITE;
    }

    // NOTE: Exit Button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{
                                                       (SCREEN_WIDTH / 2) - 40,
                                                       (SCREEN_HEIGHT / 2),
                                                       60,
                                                       30 }))
    {
        m_ExitButtonColour = GRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            delete this;
            CloseWindow();
            exit(0);
        }
    }
    else
    {
        m_ExitButtonColour = WHITE;
    }
}

void GameManager::EndDraw()
{
    DrawText(TextFormat("Score: %.2f", 0.f), (SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 100, 50, WHITE);
    DrawText("Retry", (SCREEN_WIDTH / 2) - 55, (SCREEN_HEIGHT / 2) - 40, 30, m_RetryButtonColour);
    DrawRectangleLines((SCREEN_WIDTH / 2) - 55, (SCREEN_HEIGHT / 2) - 40, 90, 30, BLANK);

    DrawText("Exit", (SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2), 30, m_ExitButtonColour);
    DrawRectangleLines((SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2), 60, 30, BLANK);

    DrawRectangleLines(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, WHITE);
}

void GameManager::ResetGame()
{
    // NOTE: Level Class Init
    m_GridManager = new GridManager(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_UIManager = new UIManager(this, m_GridManager);

    m_Money = 400;
    m_Score = 0;
    m_StrongholdCount = 3;
    m_EnemiesKilled = 0;

    m_RetryButtonColour = WHITE;

    if (!m_Towers.empty())
    {
        for (auto itr = m_Towers.begin(); itr != m_Towers.end(); ++itr)
        {
            delete* itr;
        }

        m_Towers.clear();
    }

    if (!m_Enemies.empty())
    {
        for (auto itr = m_Enemies.begin(); itr != m_Enemies.end(); ++itr)
        {
            delete* itr;
        }

        m_Enemies.clear();
    }

    if (!m_Projectiles.empty())
    {
        for (auto itr = m_Projectiles.begin(); itr != m_Projectiles.end(); ++itr)
        {
            delete* itr;
        }

        m_Projectiles.clear();
    }

    if (!m_StrongHolds.empty())
    {
        for (auto itr = m_StrongHolds.begin(); itr != m_StrongHolds.end(); ++itr)
        {
            delete* itr;
        }

        m_StrongHolds.clear();
    }

    m_GameState = GAME_STATE_GAMEPLAY;
}
