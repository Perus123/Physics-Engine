#include <solver.hpp>
#include <iostream>
const int screenHeight=900;
const int screenWidth=1600;

VerletObject cir({700.0, 500.0}, 20),cir2({900,500.0},20);
Solver solv;
boundaryCircle crc ({800,450}, 400);
Vector2 middle={screenWidth/2, screenHeight/2};

int main()
{   
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "hey");
    solv.objects.push_back(cir);
    solv.objects.push_back(cir2);
    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {   
        solv.move(solv.objects[0],60);
        solv.move(solv.objects[1], 60);
        solv.keepBoundary(solv.objects[0],crc);
        solv.keepBoundary(solv.objects[1],crc);
        solv.solveCollision(solv.objects[0], solv.objects[1]);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircleSector(middle,400.0f,0,360,128,BLACK);
        DrawCircle(solv.objects[0].position.x, solv.objects[0].position.y, 20, YELLOW);
        DrawCircle(solv.objects[1].position.x, solv.objects[1].position.y, 20, YELLOW);
        
        EndDrawing();
    }

    return 0;
}