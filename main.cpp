#include <solver.hpp>
#include <iostream>
const int screenHeight=900;
const int screenWidth=1600;

VerletObject cir({700.0, 500.0}, 20);
Solver solv;
boundaryCircle crc ({800,450}, 400);

int main()
{
    InitWindow(screenWidth, screenHeight, "hey");
    solv.objects.push_back(cir);
    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {   
        solv.move(solv.objects[0],60);
        solv.keepBoundary(solv.objects[0],crc);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(screenWidth/2, screenHeight/2, 400, BLACK);
        std::cout<<solv.objects[0].position.x<<" "<<solv.objects[0].position.y<<'\n';
        DrawCircle(solv.objects[0].position.x, solv.objects[0].position.y, 20, WHITE);
        
        EndDrawing();
    }

    return 0;
}