#include "UIManager.h"
#include "BaseTower.h"
#include "GameManager.h"
#include "GridManager.h"

UIManager::UIManager(GameManager* gameManager, GridManager* gridManager)
{
    m_GameManager = gameManager;
    m_GridManager = gridManager;

    // m_ButtonSelected = false;
    m_PressedType = PRESSED_TYPE_NONE;
    m_StoredPressedType = PRESSED_TYPE_NONE;

    m_ShowUI = false;
    m_HoverButton = false;
    m_TargetTower = nullptr;
    m_TargetStronghold = nullptr;
    m_ToggleOn = false;

    // NOTE: Displayers
    m_PrimaryTowerDisplay = new PlacerDisplay(
        Rectangle{ 10, SCREEN_HEIGHT - 60, 50, 50 },
        Vector2{ 25, 25 },
        15,
        3,
        WHITE);

    m_SecondaryTowerDisplay = new PlacerDisplay(
        Rectangle{ 70, SCREEN_HEIGHT - 60, 50, 50 },
        Vector2{ 25, 25 },
        15,
        4,
        WHITE);

    m_ThirdTowerDisplay = new PlacerDisplay(
        Rectangle{ 130, SCREEN_HEIGHT - 60, 50, 50 },
        Vector2{ 25, 25 },
        15,
        5,
        WHITE);

    m_PrimaryStronghold = new PlacerDisplay(
        Rectangle{ SCREEN_HEIGHT - 60, SCREEN_HEIGHT - 60, 50, 50 },
        Vector2{ 17, 17 },
        15,
        -1,
        WHITE);

    // NOTE: Upgrade Buttons
    // NOTE: Tower Buttons
    m_TowerSpeedButton = new Button(
        Rectangle{ SCREEN_WIDTH - 130, 30, 100, 40 },
        Vector2{ 18, 10 },
        "Speed",
        WHITE);

    m_TowerFireRateButton = new Button(
        Rectangle{ SCREEN_WIDTH - 140, 100, 120, 40 },
        Vector2{ 10, 10 },
        "Fire Rate",
        WHITE);

    m_TowerRadiusButton = new Button(
        Rectangle{ SCREEN_WIDTH - 130, 170, 100, 40 },
        Vector2{ 18, 10 },
        "Range",
        WHITE);

    m_TowerSellButton = new Button(
        Rectangle{ SCREEN_WIDTH - 130, 240, 100, 40 },
        Vector2{ 30, 12 },
        "Sell",
        WHITE);

    // NOTE: Strong Hold
    m_StrongHoldHealthButton = new Button(
        Rectangle{ SCREEN_WIDTH - 130, 30, 100, 40 },
        Vector2{ 10, 13 },
        "Health",
        WHITE);

    m_StrongHoldShieldButton = new Button(
        Rectangle{ SCREEN_WIDTH - 140, 100, 120, 40 },
        Vector2{ 10, 13 },
        "Shield",
        WHITE);

    m_StrongHoldShieldSizeButton = new Button(
        Rectangle{ SCREEN_WIDTH - 145, 170, 130, 40 },
        Vector2{ 10, 13 },
        "Shield Size",
        WHITE);

    // NOTE: Closing Button
    m_CloseGridButton = new Button(
        Rectangle{ SCREEN_WIDTH - (SCREEN_WIDTH / 2) - 60, SCREEN_HEIGHT - 50, 120, 40 },
        Vector2{ 8, 12 },
        "Close Grid",
        WHITE);

    m_MenuCloseButton = new Button(
        Rectangle{ 10, 100, 100, 40 },
        Vector2{ 25, 12 },
        "Close",
        WHITE);
}

UIManager::~UIManager()
{
    // NOTE: Tower Variables
    delete m_TowerSpeedButton;
    delete m_TowerFireRateButton;
    delete m_TowerRadiusButton;
    delete m_TowerSellButton;

    delete m_PrimaryTowerDisplay;
    delete m_SecondaryTowerDisplay;
    delete m_ThirdTowerDisplay;

    // NOTE: Strong Hold Variables
    delete m_StrongHoldHealthButton;
    delete m_StrongHoldShieldButton;
    delete m_StrongHoldShieldSizeButton;

    delete m_PrimaryStronghold;

    // NOTE: General
    delete m_CloseGridButton;
    delete m_MenuCloseButton;
}

void UIManager::Update(const float deltaTime)
{
    // NOTE: Button Hover
    CheckButtonsHovered();
    CheckButtonsToggled();

    if (m_TargetTower != nullptr)
    {
        // NOTE: Change Tower Speed
        if (m_TowerSpeedButton->ButtonPressed() == true)
        {
            unsigned int tempCost = m_GameManager->GetMoney() - m_TargetTower->GetSpeedCost();

            if (tempCost > 0)
            {
                m_TargetTower->SetFireSpeed(m_TargetTower->GetFireSpeed() + 5);
                m_GameManager->RemoveMoney(m_TargetTower->GetSpeedCost());
                m_GameManager->AddScore(150);
            }
        }

        // NOTE: Change Fire Rate
        if (m_TowerFireRateButton->ButtonPressed() == true)
        {
            float tempCost = m_GameManager->GetMoney() - m_TargetTower->GetFireRateCost();

            if (tempCost > 0)
            {
                if (m_TargetTower->GetFireRate() <= 0.1f)
                {
                    m_TargetTower->SetFireRate(0.1f);
                }
                else
                {
                    m_TargetTower->SetFireRate(m_TargetTower->GetFireRate() - 0.01f);

                    if (m_TargetTower->GetFireRate() <= 0.1f)
                    {
                        m_TargetTower->SetFireRate(0.1f);
                    }
                }

                m_GameManager->AddScore(190);
                m_GameManager->RemoveMoney(m_TargetTower->GetFireRateCost());
            }
        }

        // NOTE: Increase Tower Radius
        if (m_TowerRadiusButton->ButtonPressed() == true)
        {
            float tempCost = m_GameManager->GetMoney() - m_TargetTower->GetRangeCost();

            if (tempCost > 0)
            {
                if (m_TargetTower->GetRange() < 80)
                {
                    m_GameManager->AddScore(220);
                    m_TargetTower->SetRange(m_TargetTower->GetRange() + 5);
                    m_GameManager->RemoveMoney(m_TargetTower->GetRangeCost());
                }
            }
        }

        // NOTE: Sell the Tower
        if (m_TowerSellButton->ButtonPressed() == true)
        {
            m_GameManager->AddMoney(m_TargetTower->GetPrice() - (m_TargetTower->GetPrice() * 0.25));
            m_GameManager->DeleteTower(m_TargetTower);
            m_GridManager->ChangeTileID(m_TargetTower->GetTowerTile().indexSingle, TILE_ID_NONE);
            m_TargetTower = nullptr;
            m_ShowUI = false;
        }
    }

    if (m_TargetStronghold != nullptr)
    {
        // NOTE: Strong Hold Health
        if (m_StrongHoldHealthButton->ButtonPressed() == true)
        {
            float tempCost = m_GameManager->GetMoney() - m_TargetStronghold->GetHealthCost();

            if (tempCost > 0)
            {
                if (m_TargetStronghold->GetHealth() < 100.f)
                {
                    m_GameManager->AddScore(150);
                    m_TargetStronghold->AddHealth(10);
                    m_GameManager->RemoveMoney(m_TargetStronghold->GetHealthCost());
                }
            }
        }

        // NOTE: Strong Hold Shield Button
        if (m_StrongHoldShieldButton->ButtonPressed() == true)
        {
            float tempCost = m_GameManager->GetMoney() - m_TargetStronghold->GetShieldCost();

            if (tempCost > 0)
            {
                if (m_TargetStronghold->GetShield() < 100.f)
                {
                    m_GameManager->AddScore(170);
                    m_TargetStronghold->AddShield(10);
                    m_GameManager->RemoveMoney(m_TargetStronghold->GetShieldCost());
                }
            }
        }

        // NOTE: Strong Hold Shield Size Button
        if (m_StrongHoldShieldSizeButton->ButtonPressed() == true)
        {
            float tempCost = m_GameManager->GetMoney() - m_TargetStronghold->GetShieldRadiusCost();

            if (tempCost > 0)
            {
                if (m_TargetStronghold->GetShieldSize() < 40.f)
                {
                    m_GameManager->AddScore(200);
                    m_TargetStronghold->AddShieldSize(5);
                    m_GameManager->RemoveMoney(m_TargetStronghold->GetShieldRadiusCost());
                }
            }
        }
    }
}

void UIManager::Draw()
{
    // NOTE: Draw the Primary Tower Cost
    DrawText("100", 20, SCREEN_HEIGHT - 80, 20, WHITE);
    m_PrimaryTowerDisplay->Draw();

    DrawText("250", 80, SCREEN_HEIGHT - 80, 20, WHITE);
    m_SecondaryTowerDisplay->Draw();

    DrawText("500", 140, SCREEN_HEIGHT - 80, 20, WHITE);
    m_ThirdTowerDisplay->Draw();

    DrawText(TextFormat("%d", m_GameManager->GetStrongholdCount()), SCREEN_WIDTH - 40, SCREEN_HEIGHT - 80, 20, WHITE);
    m_PrimaryStronghold->DrawAlt();

    // NOTE: Draw the Money for the Player
    DrawText(TextFormat("Money: %.0f", m_GameManager->GetMoney()), (SCREEN_WIDTH / 2.f) - 40, 0, 20, WHITE);

    // NOTE: Draw UI
    if (m_ShowUI == true)
    {
        if (m_TargetTower != nullptr)
        {
            // NOTE: Draw Tower Information
            DrawText("Stats: ", 10, 10, 20, WHITE);
            DrawText(TextFormat("Shot Speed: %.1f", m_TargetTower->GetFireSpeed()), 10, 30, 20, WHITE);
            DrawText(TextFormat("Fire Rate: %.1f", m_TargetTower->GetFireRate()), 10, 50, 20, WHITE);
            DrawText(TextFormat("Range: %.1f", m_TargetTower->GetRange()), 10, 70, 20, WHITE);

            DrawText(TextFormat("Cost: %d", m_TargetTower->GetSpeedCost()), SCREEN_WIDTH - 120, 10, 20, WHITE);
            DrawText(TextFormat("Cost: %d", m_TargetTower->GetFireRateCost()), SCREEN_WIDTH - 120, 80, 20, WHITE);
            DrawText(TextFormat("Cost: %d", m_TargetTower->GetRangeCost()), SCREEN_WIDTH - 120, 150, 20, WHITE);

            m_TowerSpeedButton->Draw();
            m_TowerFireRateButton->Draw();
            m_TowerRadiusButton->Draw();
            m_TowerSellButton->Draw();
        }

        if (m_TargetStronghold != nullptr)
        {
            DrawText("Stats: ", 10, 10, 20, WHITE);
            DrawText(TextFormat("Health: %.1f", m_TargetStronghold->GetHealth()), 10, 30, 20, WHITE);
            DrawText(TextFormat("Shield: %.1f", m_TargetStronghold->GetShield()), 10, 50, 20, WHITE);
            DrawText(TextFormat("Shield Size: %.1f", m_TargetStronghold->GetShieldSize()), 10, 70, 20, WHITE);

            DrawText(TextFormat("Cost: %d", m_TargetStronghold->GetHealthCost()), SCREEN_WIDTH - 120, 10, 20, WHITE);
            DrawText(TextFormat("Cost: %d", m_TargetStronghold->GetShieldCost()), SCREEN_WIDTH - 120, 80, 20, WHITE);
            DrawText(TextFormat("Cost: %d", m_TargetStronghold->GetShieldRadiusCost()), SCREEN_WIDTH - 120, 150, 20, WHITE);

            m_StrongHoldHealthButton->Draw();
            m_StrongHoldShieldButton->Draw();
            m_StrongHoldShieldSizeButton->Draw();
        }

        m_MenuCloseButton->Draw();
    }

    // NOTE: Show Grid Button
    if (m_ToggleOn == true)
    {
        m_CloseGridButton->Draw();
    }
}

void UIManager::CheckButtonsHovered()
{
    // NOTE: Buttons Hovered Effect
    // NOTE: Need to do this with all buttons

    if (
        m_PrimaryTowerDisplay->ButtonHover() ||
        m_SecondaryTowerDisplay->ButtonHover() ||
        m_ThirdTowerDisplay->ButtonHover() ||
        m_PrimaryStronghold->ButtonHover() ||

        m_MenuCloseButton->ButtonHover() ||
        m_CloseGridButton->ButtonHover())
    {
        m_HoverButton = true;
    }
    else
    {
        m_HoverButton = false;
    }

    // NOTE: Check if there are Turrets or Strongholds Activated, if not then default to the hover about
    // NOTE: If they are active, check these ifs as well
    if (m_TargetTower != nullptr)
    {
        if (m_TowerSpeedButton->ButtonHover() ||
            m_TowerFireRateButton->ButtonHover() ||
            m_TowerRadiusButton->ButtonHover() ||
            m_TowerSellButton->ButtonHover())
        {
            m_HoverButton = true;
        }
        else
        {
            m_HoverButton = false;
        }
    }
    else if (m_TargetStronghold != nullptr)
    {
        if (m_StrongHoldHealthButton->ButtonHover() ||
            m_StrongHoldShieldButton->ButtonHover() ||
            m_StrongHoldShieldSizeButton->ButtonHover())
        {
            m_HoverButton = true;
        }
        else
        {
            m_HoverButton = false;
        }
    }
}

void UIManager::CheckButtonsToggled()
{
    // NOTE: Button Pressed
    if (m_PrimaryStronghold->ButtonPressed())
    {
        m_PressedType = PRESSED_TYPE_PRIMARY_STRONG_HOLD;
        m_ToggleOn = true;
    }

    if (m_PrimaryTowerDisplay->ButtonPressed())
    {
        m_PressedType = PRESSED_TYPE_PRIMARY_TOWER;
        m_ToggleOn = true;
    }
    if (m_SecondaryTowerDisplay->ButtonPressed())
    {
        m_PressedType = PRESSED_TYPE_SECONDARY_TOWER;
        m_ToggleOn = true;
    }
    if (m_ThirdTowerDisplay->ButtonPressed())
    {
        m_PressedType = PRESSED_TYPE_THIRD_TOWER;
        m_ToggleOn = true;
    }

    // NOTE: Reset press type to none
    if (m_CloseGridButton->ButtonPressed())
    {
        m_PressedType = PRESSED_TYPE_NONE;
        m_ToggleOn = false;
    }
}
