#include "GameOverState.hpp"
#include "MainGameState.hpp"
#include <memory>
#include <string>

extern "C" {
    #include <raylib.h>
}

void GameOverState::init() {}

void GameOverState::handleInput()
{
    /** @brief Si se presiona ESPACIO, iniciamos una nueva partida. */
    if (IsKeyPressed(KEY_SPACE))
    {
        this->state_machine->add_state(std::make_unique<MainGameState>(), true);
    }
}

void GameOverState::update(float deltaTime) {}

void GameOverState::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    /** @brief Texto principal del estado Game Over. */
    const char* titleText = "GAME OVER";
    int titleFontSize = 32;
    int titleWidth = MeasureText(titleText, titleFontSize);
    int titleX = (GetScreenWidth() - titleWidth) / 2;
    int titleY = GetScreenHeight() / 2 - 80;

    DrawText(titleText, titleX, titleY, titleFontSize, RED);

    /** @brief Texto de puntuación centrado debajo del título. */
    std::string scoreText = "Puntuacion: " + std::to_string(score);
    int scoreFontSize = 20;
    int scoreWidth = MeasureText(scoreText.c_str(), scoreFontSize);
    int scoreX = (GetScreenWidth() - scoreWidth) / 2;
    int scoreY = titleY + 50;

    DrawText(scoreText.c_str(), scoreX, scoreY, scoreFontSize, DARKGRAY);

    /** @brief Texto de instrucciones centrado más abajo. */
    const char* infoText = "Pulsa ESPACIO para reiniciar";
    int infoFontSize = 16;
    int infoWidth = MeasureText(infoText, infoFontSize);
    int infoX = (GetScreenWidth() - infoWidth) / 2;
    int infoY = scoreY + 40;

    DrawText(infoText, infoX, infoY, infoFontSize, GRAY);

    EndDrawing();
}

