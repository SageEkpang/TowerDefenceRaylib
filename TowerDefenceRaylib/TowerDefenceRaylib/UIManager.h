#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

#include "LineToLine.h"
#include "ScreenConstants.h"

class GameManager;
class GridManager;
class BaseStronghold;
class BaseTower;

enum PressedType
{
    PRESSED_TYPE_NONE = 0,

    PRESSED_TYPE_PRIMARY_TOWER,
    PRESSED_TYPE_SECONDARY_TOWER,
    PRESSED_TYPE_THIRD_TOWER,

    PRESSED_TYPE_PRIMARY_STRONG_HOLD,
};

// NOTE: Button struct because making a class is long
struct Button
{
    bool buttonPress;
    Rectangle buttonRec;
    Vector2 textPosition;
    std::string text;
    Color colour;
    Color recColour;

    Button() = default;

    Button(Rectangle buttonRec, Vector2 textPosition, std::string text, Color colour)
    {
        this->buttonRec = buttonRec;
        this->textPosition = textPosition;
        this->text = text;
        this->buttonPress = false;
        this->colour = colour;
        this->recColour = BLANK;
    }

    void SetButtonState(bool state)
    {
        this->buttonPress = state;
    }

    bool ButtonHover()
    {
        if (CheckCollisionPointRec(GetMousePosition(), buttonRec))
        {
            this->recColour = WHITE;
            return true;
        }
        else
        {
            this->recColour = BLANK;
            return false;
        }
    }

    bool ButtonToggle()
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonRec))
        {
            if (this->buttonPress == false)
            {
                this->buttonPress = true;
                return this->buttonPress;
            }
            else if (this->buttonPress == true)
            {
                this->buttonPress = false;
                return this->buttonPress;
            }
        }

        return this->buttonPress;
    }

    bool ButtonPressed()
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonRec))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Draw()
    {
        DrawRectangleLinesEx(buttonRec, 1, this->recColour);
        DrawRectangleRec(Rectangle{ buttonRec.x + 1, buttonRec.y + 1, buttonRec.width - 2, buttonRec.height - 2 }, BLACK);
        DrawText(TextFormat("%s", text.c_str()), textPosition.x + buttonRec.x, textPosition.y + buttonRec.y, 20, this->colour);
    }
};

struct PlacerDisplay
{
    bool buttonPress;
    Vector2 position;
    float size;
    Rectangle displayRec;
    Rectangle defaultRec;
    std::vector<LineToLine> pointLines;
    Color colour;
    Color recColour;

    PlacerDisplay() = default;

    PlacerDisplay(Rectangle displayRec, Vector2 position, float size, int points, Color colour)
    {
        this->displayRec = displayRec;
        this->defaultRec = displayRec;
        this->position = position;
        this->size = size;
        this->recColour = BLANK;

        this->buttonPress = false;
        this->colour = colour;

        if (points != -1)
        {
            CalculateLinePoints(points);
        }
    }

    void SetButtonState(bool state)
    {
        this->buttonPress = state;
    }

    bool ButtonHover()
    {
        if (CheckCollisionPointRec(GetMousePosition(), displayRec))
        {
            recColour = WHITE;
            // colour.a = 200;
            return true;
        }
        else
        {
            recColour = BLANK;
            // colour.a = 255;
            return false;
        }
    }

    bool ButtonToggle()
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), displayRec))
        {
            if (this->buttonPress == false)
            {
                this->buttonPress = true;
                return this->buttonPress;
            }
            else if (this->buttonPress == true)
            {
                this->buttonPress = false;
                return this->buttonPress;
            }
        }

        return this->buttonPress;
    }

    bool ButtonPressed()
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), displayRec))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Draw()
    {
        DrawRectangleLinesEx(displayRec, 1, recColour);
        DrawRectangleRec(Rectangle{ displayRec.x + 1, displayRec.y + 1, displayRec.width - 2, displayRec.height - 2 }, BLACK);
        for (auto& v : pointLines)
        {
            DrawLineV(v.lineStart, v.lineEnd, this->colour);
        }
    }

    void DrawAlt()
    {
        DrawRectangleRec(displayRec, recColour);
        DrawRectangleRec(Rectangle{ displayRec.x + 1, displayRec.y + 1, displayRec.width - 2, displayRec.height - 2 }, BLACK);
        DrawRectangleV(Vector2{ position.x + displayRec.x, position.y + displayRec.y }, { size, size }, this->colour);
    }

    void CalculateLinePoints(int points)
    {
        int ResultAngle = 360 / points;
        int Angle = 0;

        pointLines.clear();

        // NOTE: Point Array Calculation
        for (int i = 0; i < points; ++i)
        {
            float t_startDegree = Angle;
            float t_endDegree = Angle + ResultAngle;

            Vector2 t_startVec = Vector2Rotate(Vector2{ 0, -1 }, t_startDegree);
            Vector2 t_endVec = Vector2Rotate(Vector2{ 0, -1 }, t_endDegree);

            // NOTE: Push point to array
            pointLines.push_back(
                LineToLine(
                    Vector2Add(Vector2Multiply(t_startVec, Vector2{ size, size }), Vector2Add(position, Vector2{ displayRec.x, displayRec.y })),
                    Vector2Add(Vector2Multiply(t_endVec, Vector2{ size, size }), Vector2Add(position, Vector2{ displayRec.x, displayRec.y }))));

            // NOTE: Add a part of the angle from this
            Angle += ResultAngle;
        }
    }
};

class UIManager
{
private:
    GameManager* m_GameManager;
    GridManager* m_GridManager;

private:
    bool m_ShowUI;
    bool m_HoverButton;

    PressedType m_PressedType;
    PressedType m_StoredPressedType;
    bool m_ToggleOn;

    // NOTE: Upgrade UI (Tower)
    BaseTower* m_TargetTower;

    Button* m_TowerSpeedButton;
    Button* m_TowerFireRateButton;
    Button* m_TowerRadiusButton;
    Button* m_TowerSellButton;

    PlacerDisplay* m_PrimaryTowerDisplay;
    PlacerDisplay* m_SecondaryTowerDisplay;
    PlacerDisplay* m_ThirdTowerDisplay;

    // NOTE: Upgrade UI (Stronghold)
    BaseStronghold* m_TargetStronghold;

    Button* m_StrongHoldHealthButton;
    Button* m_StrongHoldShieldButton;
    Button* m_StrongHoldShieldSizeButton;

    PlacerDisplay* m_PrimaryStronghold;

    // NOTE: General Button
    Button* m_MenuCloseButton;
    Button* m_CloseGridButton;

private:
    void CheckButtonsHovered();
    void CheckButtonsToggled();

public:
    // CLASS FUNCTION(s)
    UIManager(GameManager* gameManager, GridManager* gridManager);
    virtual ~UIManager();

    // BASE FUNCTION(s)
    virtual void Update(const float deltaTime);
    virtual void Draw();

    // GETTER(s)
    inline BaseTower* GetTargetTower() { return m_TargetTower; }

    inline bool GetShowUI() { return m_ShowUI; }
    inline Button* GetSpeedButton() { return m_TowerSpeedButton; }
    inline Button* GetFireRateButton() { return m_TowerFireRateButton; }
    inline Button* GetRadiusButton() { return m_TowerRadiusButton; }
    inline Button* GetSellButton() { return m_TowerSellButton; }
    inline Button* GetCloseButton() { return m_MenuCloseButton; }
    inline Button* GetCloseGridButton() { return m_CloseGridButton; }

    inline PlacerDisplay* GetPrimaryTowerDisplay() { return m_PrimaryTowerDisplay; }
    inline PlacerDisplay* GetSecondaryTowerDisplay() { return m_SecondaryTowerDisplay; }
    inline PlacerDisplay* GetThirdTowerDisplay() { return m_ThirdTowerDisplay; }

    inline PressedType GetPressedType() { return m_PressedType; }
    inline bool GetHoverButton() { return m_HoverButton; }

    inline bool GetToggleOn() { return m_ToggleOn; }

    // SETTER(s)

    inline void SetTargetTower(BaseTower* tower) { this->m_TargetTower = tower; }
    inline void SetTargetStronghold(BaseStronghold* strongHold) { this->m_TargetStronghold = strongHold; }
    inline void SetShowUI(bool showUI) { this->m_ShowUI = showUI; }
};

#endif