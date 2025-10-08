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
    /** @brief Carga sprites de pájaro y tubería. */
    birdSprite = LoadTexture("assets/yellowbird-midflap.png");
    pipeSprite = LoadTexture("assets/pipe-green.png");

    /** @brief Posición inicial y dimensiones del jugador. */
    jugador.x = 200.0f;
    jugador.y = 200.0f;
    jugador.width  = static_cast<float>(birdSprite.width);
    jugador.height = static_cast<float>(birdSprite.height);

    /** @brief Dimensiones de las tuberías según sprite. */
    PIPE_W = static_cast<float>(pipeSprite.width);
    PIPE_H = static_cast<float>(pipeSprite.height);

    /** @brief Separación vertical entre tuberías. */
    PIPE_GAP = jugador.height * 4.5f;
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

    /** @brief Define el bounding box del jugador según el tamaño del sprite. */
    Rectangle jugadorBox = {
        jugador.x,
        jugador.y,
        jugador.width,
        jugador.height
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
    if (jugador.y < 0 || jugador.y + jugador.height > GetScreenHeight())
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
     * @brief Muestra el título del juego.
     */
    DrawText("Flappy Bird", 50, 100, 20, BLACK);

    /**
     * @brief Dibuja el sprite del jugador (pájaro).
     */
    DrawTexture(
        birdSprite,
        static_cast<int>(jugador.x),
        static_cast<int>(jugador.y),
        WHITE
    );

    /**
     * @brief Dibuja las tuberías (superior e inferior) como sprites.
     *        La superior se rota 180 grados para apuntar hacia abajo.
     */
    for (const auto& pipe : pipes)
    {
        // Tubería superior (rotada)
        DrawTextureEx(
            pipeSprite,
            { pipe.top.x + PIPE_W, pipe.top.y + PIPE_H },
            180.0f,  // rotación
            1.0f,    // escala
            WHITE
        );

        // Tubería inferior (normal)
        DrawTextureEx(
            pipeSprite,
            { pipe.bot.x, pipe.bot.y },
            0.0f,   // sin rotación
            1.0f,   // escala
            WHITE
        );
    }

    /** 
     * @brief Muestra la puntuación actual del jugador en la esquina superior izquierda.
     */
    std::string scoreText = "Puntos: " + std::to_string(score);
    DrawText(scoreText.c_str(), 20, 20, 25, BLACK);

    /**
     * @brief Finaliza el proceso de dibujado y actualiza la ventana.
     */
    EndDrawing();
}
