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
    /** @brief Renderiza la pantalla de Game Over. */
    BeginDrawing();
    ClearBackground(RAYWHITE);

    const char* text = "GAME OVER";
    int textWidth = MeasureText(text, 40);
    int x = (GetScreenWidth() - textWidth) / 2;
    int y = GetScreenHeight() / 2 - 20;

    DrawText(text, x, y, 40, RED);
    DrawText("Pulsa ESPACIO para reiniciar", 30, y + 80, 20, DARKGRAY);

    EndDrawing();
}
