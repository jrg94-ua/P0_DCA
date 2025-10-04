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
        @brief Ajustamos la nueva velocidad del jugador con el deltaTime
    */
    jugador.vy += gravedad * deltaTime;

    /**
        @brief Calculamos la nueva posición del jugador 
    */
    jugador.y += jugador.vy * deltaTime;

   

    /**
        @brief Actualizamos el temporizador de aparición de tuberías
    */
    spawnTimer += deltaTime;

    /**
        @brief Cada spawnEvery ciclos, generamos un nuevo par de tuberías
    */
    if (spawnTimer >= spawnEvery)
    {
        spawnTimer = 0.0f;

        /**
            @brief Calculamos un valor aleatorio para el desplazamiento de la tubería superior.
            El valor mínimo será la mitad de la altura de la tubería y el máximo la mitad
            de la altura de la pantalla.
        */
        int pipe_y_offset_top = GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2);

        /**
            @brief Creamos una nueva estructura PipePair con dos rectángulos:
                   uno para la tubería superior y otro para la inferior.
        */
        PipePair newPipe;

        /**
            @brief Definimos las coordenadas de la tubería superior.
                   Ambas comienzan en x = ancho de la pantalla.
        */
        newPipe.top = {
            static_cast<float>(GetScreenWidth()),  // posición x
            -pipe_y_offset_top,                    // posición y negativa según offset
            PIPE_W,                                // anchura
            PIPE_H                                 // altura
        };

        /**
            @brief Definimos las coordenadas de la tubería inferior.
                   Su posición en y se calcula según el desplazamiento de la superior.
        */
        newPipe.bot = {
            static_cast<float>(GetScreenWidth()),  // misma posición x
            (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H / 2, GetScreenHeight() / 2),
            PIPE_W,
            PIPE_H
        };

        /**
            @brief Insertamos el nuevo par de tuberías en la cola (deque)
        */
        pipes.push_back(newPipe);
    }

    /**
        @brief Movemos las tuberías hacia la izquierda a la misma velocidad.
               La distancia recorrida depende de deltaTime.
    */
    for (auto& pipe : pipes)
    {
        pipe.top.x -= PIPE_SPEED * deltaTime;
        pipe.bot.x -= PIPE_SPEED * deltaTime;
    }

    /**
        @brief Si la tubería frontal sale completamente de la pantalla,
               la eliminamos de la cola para liberar memoria.
    */
    if (!pipes.empty() && pipes.front().top.x + PIPE_W < 0)
    {
        pipes.pop_front();
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
        static_cast<int>(jugador.x),  // Se hace el cast a int porque lo hemos definido antes como float
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

    /**
     * @brief Finaliza el proceso de dibujado y actualiza la ventana.
     */
    EndDrawing(); 
}
