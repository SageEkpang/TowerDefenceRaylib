#include "ScreenConstants.h"
#include "GameManager.h"
#include <memory>

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defence One Day Game");
    InitAudioDevice();

    // NOTE: Init the GameManager
    std::unique_ptr<GameManager> m_Game = std::make_unique<GameManager>();

    // NOTE: Sound Playing
    Sound m_SoundTrack = LoadSound("Sound/GameTrack.wav");
    float m_TargetFPS = 1;

    while (!WindowShouldClose())
    {
        if (!IsSoundPlaying(m_SoundTrack))
        {
            SetSoundVolume(m_SoundTrack, 0.1f);
            PlaySound(m_SoundTrack);
        }

        // UPDATE
        {
            if (IsKeyPressed(KEY_ONE))
            {
                m_TargetFPS = 1;
            }
            else if (IsKeyPressed(KEY_TWO))
            {
                m_TargetFPS = 3;
            }

            float t_deltaTime = GetFrameTime() * m_TargetFPS;
            m_Game->Update(t_deltaTime);
        }

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);
        {
            m_Game->Draw();

            if (m_TargetFPS == 3)
            {
                // DrawText("FAST", )
            }
        }
        EndDrawing();
    }

    UnloadSound(m_SoundTrack);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
