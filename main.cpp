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
    solv.objects[0].set_velocity((Vector2){1500.0f,0.0f}, 60);
    SetTargetFPS(60);
    const int substeps=8;
    int time=0;
    while(!WindowShouldClose())
    {   
        solv.runSystem(crc, substeps);
        

        
        
        EndDrawing();
    }

    return 0;
}