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
    const int substeps=8;
    int time=0;
    while(!WindowShouldClose())
    {   
        solv.runSystem(crc, substeps);
        if(time&&time%60==0)
            solv.objects.push_back(cir);
        time++;

        
        
        EndDrawing();
    }

    return 0;
}