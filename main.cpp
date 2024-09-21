#include <solver.hpp>
#include <iostream>
const int screenHeight=900;
const int screenWidth=1600;

VerletObject cir({700.0, 500.0}, 20);
Solver solv;
boundaryCircle crc ({800,450}, 400);
Vector2 middle={screenWidth/2, screenHeight/2};

int main()
{   
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "hey");
    solv.objects.push_back(cir);
    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {   
        solv.move(solv.objects[0],60);
        solv.keepBoundary(solv.objects[0],crc);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircleSector(middle,400.0f,0,360,128,BLACK);
        DrawCircle(solv.objects[0].position.x, solv.objects[0].position.y, 20, YELLOW);
        
        EndDrawing();
    }

    return 0;
}