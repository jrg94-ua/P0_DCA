#include <MainGameState.hpp>
#include <iostream>
#include "StateMachine.hpp"
#include "GameOverState.hpp"

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
        jugador.vy = -200.0f;  
    }

}

void MainGameState::update(float deltaTime)
{
    /** @brief Aplica la gravedad y actualiza la posición del jugador. */
    const float gravedad = 200.0f;
    jugador.vy += gravedad * deltaTime;
    jugador.y += jugador.vy * deltaTime;

    /** @brief Controla el temporizador y genera nuevas tuberías periódicamente. */
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnEvery)
    {
        spawnTimer = 0.0f;
        int pipe_y_offset_top = GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2);

        PipePair newPipe;
        newPipe.top = { static_cast<float>(GetScreenWidth()), static_cast<float>(-pipe_y_offset_top), PIPE_W, PIPE_H };
        newPipe.bot = { static_cast<float>(GetScreenWidth()),
                        (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2),
                        PIPE_W, PIPE_H };

        pipes.push_back(newPipe);
    }

    /** @brief Mueve las tuberías activas hacia la izquierda y elimina las que salen de pantalla. */
    for (auto& pipe : pipes)
    {
        pipe.top.x -= PIPE_SPEED * deltaTime;
        pipe.bot.x -= PIPE_SPEED * deltaTime;
    }

    if (!pipes.empty() && pipes.front().top.x + PIPE_W < 0)
        pipes.pop_front();

    /** @brief Actualiza la puntuación cuando el jugador pasa una tubería. */
    for (auto& pipe : pipes)
    {
        if (!pipe.scored && (pipe.top.x + PIPE_W) < jugador.x)
        {
            pipe.scored = true;
            score++;
        }
    }

    /** @brief Define el bounding box del jugador para detectar colisiones. */
    const float radio = 17.0f;
    Rectangle jugadorBox = {
        jugador.x - radio,
        jugador.y - radio,
        radio * 2,
        radio * 2
    };

    /** @brief Detecta colisiones entre el jugador y las tuberías. */
    for (auto& pipe : pipes)
    {
        if (CheckCollisionRecs(jugadorBox, pipe.top) || CheckCollisionRecs(jugadorBox, pipe.bot))
        {
            this->state_machine->add_state(std::make_unique<GameOverState>(score), true);
            return;
        }
    }

    /** @brief Detecta si el jugador sale de los límites de la pantalla. */
    if (jugador.y - radio < 0 || jugador.y + radio > GetScreenHeight())
    {
        this->state_machine->add_state(std::make_unique<GameOverState>(score), true);
        return;
    }
}



void MainGameState::render()
{
    /**
     * @brief Inicia el proceso de dibujado en pantalla.
     */
    BeginDrawing();

    /**
     * @brief Limpia el fondo de la ventana con color blanco.
     */
    ClearBackground(RAYWHITE);

    /**
     * @brief Muestra el texto del título del juego.
     */
    DrawText("Flappy Bird", 50, 100, 20, BLACK);

    /**
     * @brief Dibuja al pájaro como un círculo rojo de radio 17 px.
     */
    DrawCircle(
        static_cast<int>(jugador.x),  
        static_cast<int>(jugador.y),  
        17,                           
        RED                           
    );

    /**
     * @brief Itera sobre todas las tuberías almacenadas en la cola (deque)
     *        y las dibuja en pantalla como rectángulos verdes.
     */
    for (const auto& pipe : pipes)
    {
        /**
         * @brief Dibuja la tubería superior.
         */
        DrawRectangleRec(pipe.top, GREEN);

        /**
         * @brief Dibuja la tubería inferior.
         */
        DrawRectangleRec(pipe.bot, GREEN);
    }

    /** @brief Muestra la puntuación actual del jugador en la esquina superior izquierda. */
    std::string scoreText = "Puntos: " + std::to_string(score);
    DrawText(scoreText.c_str(), 20, 20, 25, BLACK);

    /**
     * @brief Finaliza el proceso de dibujado y actualiza la ventana.
     */
    EndDrawing(); 
}
