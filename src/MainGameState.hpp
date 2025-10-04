#pragma once
#include <GameState.hpp>
#include <Bird.hpp>
#include <PipePair.hpp>
#include <deque>

class MainGameState : public GameState
{
public:
    MainGameState();
    ~MainGameState() = default;

    void init() override;
    void handleInput() override;
    void update(float deltaTime) override;
    void render() override;

    void pause() {};
    void resume() {};

private:
    char entered_key;
    Bird jugador;
    std::deque<PipePair> pipes;

    float spawnTimer = 0.0f;
    float spawnEvery = 2.0f;

    static constexpr float PIPE_W = 32.0f;
    static constexpr float PIPE_H = 320.0f;
    static constexpr float PIPE_SPEED = 100.0f;
};
