#include <func.h>

int main () {
    ///Animation and display constants
    const int screenWidth=1600;
    const int screenHeight=900;
    
    ///Objects initialization
    Vector2 initCircle= {100.f, 100.0f};
    circle c(initCircle,20);
    line l((Vector2){0,450},(Vector2){800,900});
    std::cout<<l.normal.x<<" "<<l.normal.y<<'\n';
    c.changeVelocity({0.0f, 25.0f});
    char *message={"Lets get this bread"};
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    SetTargetFPS(60);
    while(WindowShouldClose()==false){

        
        Vector2 cValues=c.getPosition();
        int cRadius=c.getRadius();

        if(cValues.y<screenHeight-c.getRadius())
        {    
             c.changeVelocity((Vector2){0.0f,0.0f});
             c.changePosition(c.getVelocity());
        }
           
        else 
        {
          /// Vector2 finalPosition=c.getPosition();
          /// std::cout<<finalPosition.x<<" "<<finalPosition.y<<" ";
          c.changePosition({0.0f, (float)-screenHeight});
          
        }
        
        BeginDrawing();  ///start draw
        ClearBackground(BLACK);
        DrawText(message, 390, 400, 50, LIGHTGRAY);
        DrawLine(0,450,800,900, BLUE);
        DrawCircle(cValues.x, cValues.y, cRadius, MAROON);
        EndDrawing(); ///stop draw
    }
    CloseWindow();
    

    return 0;
}