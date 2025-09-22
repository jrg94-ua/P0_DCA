#include <MainGameState.hpp>
#include <iostream>

extern "C" {
    #include <raylib.h>
}

MainGameState::MainGameState()
{

}

void MainGameState::init()
{
    jugador.x =  200.0f;
    jugador.y = 200.0f;

}

void MainGameState::handleInput()
{
    /**
        @brief si se presiona el espacio la velocidad vertical del jugador sube(hacia arriba) en 300.0f
    */    

    if (IsKeyPressed(KEY_SPACE))
    {
        jugador.vy = -300.0f;  
    }

}

void MainGameState::update(float deltaTime)
{
    /**
        @brief Creamos una variable de gravedad e inicializamos a 300
    */

    const float gravedad = 300.0f;

    /**
        @brief ajustamos la nueva velocidad del jugador con el deltaTime
    */
    jugador.vy += gravedad * deltaTime;
    /**
        @brief La nueva posicion del jugador 
    */
    jugador.y += jugador.vy * deltaTime;
    /**
        @brief Volvemos a reinstaurar la vel a 0
    */
    jugador.vy = 0.0f;

}

void MainGameState::render()
{
    
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Flappy Bird",50 ,100 , 20,BLACK );

    EndDrawing(); 

}