#include "GameOverState.hpp"
#include "MainGameState.hpp"
#include <memory>

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

    const char* text = "GAME OVER";
    int textWidth = MeasureText(text, 40);
    int x = (GetScreenWidth() - textWidth) / 2;
    int y = GetScreenHeight() / 2 - 20;

    DrawText(text, x, y, 40, RED);

    /** @brief Muestra la puntuación final en el centro de la pantalla. */
    std::string scoreText = "Puntuacion: " + std::to_string(score);
    int scoreWidth = MeasureText(scoreText.c_str(), 25);
    DrawText(scoreText.c_str(), (GetScreenWidth() - scoreWidth) / 2, y + 60, 25, DARKGRAY);

    DrawText("Pulsa ESPACIO para reiniciar", 30, y + 80, 20, DARKGRAY);


    EndDrawing();
}