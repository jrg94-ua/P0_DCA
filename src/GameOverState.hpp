#pragma once
#include "GameState.hpp"
#include "StateMachine.hpp"

extern "C" {
    #include <raylib.h>
}

/**
 * @brief Estado del juego mostrado cuando el jugador pierde.
 */
class GameOverState : public GameState
{
public:
    /** @brief Constructor que recibe la puntuación final del jugador. */
    explicit GameOverState(int finalScore) : score(finalScore) {}

    ~GameOverState() override = default;

    void init() override;
    void handleInput() override;
    void update(float deltaTime) override;
    void render() override;

    void pause() override {};
    void resume() override {};

private:
    int score = 0; //< @brief Puntuación final del jugador
};
