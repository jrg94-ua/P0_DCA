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

}

void MainGameState::handleInput()
{

}

void MainGameState::update(float deltaTime)
{

}

void MainGameState::render()
{
    
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Flappy Bird",50 ,100 , 20,BLACK );

    EndDrawing(); 

}