#include <func.h>

int main () {

    const Vector2 gravity= {0.0f, 9.8f};
    Vector2 initCerc= {100.f, 100.0f};
    circle c(initCerc,20);
    const int screenWidth=1600;
    const int screenHeight=900;
    char *message={"Lets get this bread"};
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    SetTargetFPS(60);
    while(WindowShouldClose()==false){

        
        Vector2 cValues=c.getPosition();
        int cRadius=c.getRadius();
        
        if(cValues.y<screenHeight-c.getRadius())
        {    
             c.changeVelocity((Vector2){gravity.x/60,gravity.y/60});
             c.changePosition(c.getVelocity());
        }
           
        else
        {
          /// Vector2 finalPosition=c.getPosition();
          /// std::cout<<finalPosition.x<<" "<<finalPosition.y<<" ";
           c.changePosition((Vector2){0.0f,0.0f-screenHeight});
           message={"bread acquired"};
        }
        std::cout<<cValues.x<<" "<<cValues.y<<"\n";
        BeginDrawing();  ///start draw
        ClearBackground(BLACK);
        DrawText(message, 390, 400, 50, LIGHTGRAY);
        
        DrawCircle(cValues.x, cValues.y, cRadius, MAROON);
        EndDrawing(); ///stop draw
    }
    CloseWindow();
    

    return 0;
}