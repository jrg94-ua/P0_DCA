#pragma once
#include <GameState.hpp>
#include <Bird.hpp>
#include <PipePair.hpp>
#include <deque>

extern "C" {
    #include <raylib.h>
}

class MainGameState : public GameState
{
public:
    MainGameState();
    ~MainGameState() override = default;

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
    /**
    * @brief Textura del pájaro.
    */
    Texture2D birdSprite;
    /**
     * @brief Textura de las tuberías.
     */
    Texture2D pipeSprite;

    float spawnTimer = 0.0f;
    float spawnEvery = 2.0f;

    float PIPE_W = 0.0f;       
    float PIPE_H = 0.0f;       
    float PIPE_SPEED = 120.0f; 
    float PIPE_GAP = 0.0f;     
    
    int score = 0; //puntuacion
};
