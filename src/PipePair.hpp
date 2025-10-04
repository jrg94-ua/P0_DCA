
#pragma once
extern "C" {
    #include <raylib.h>
}
/**
    *@struct PipePair
    *@brief Representa los tubos del juego
*/

struct PipePair {

    /**
     * @brief tubo superior 
     */
    Rectangle top;   
    /**
     * @brief tubo inferior 
     */
     Rectangle bot;
    /**
     * @brief Puntuacion
     */
    bool scored=false;
};
