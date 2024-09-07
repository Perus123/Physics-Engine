#include <solver.hpp>
#include <iostream>
const int screenHeight=900;
const int screenWidth=1600;

VerletObject cir({100.0, 100.0}, 10);
int main()
{
    InitWindow(screenWidth, screenHeight, "hey");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {   

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleGradient(cir.position.x, cir.position.y, cir.radius, BLUE, WHITE);
        EndDrawing();
    }

    return 0;
}