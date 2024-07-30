#include <func.h>

using namespace std;

int main () {

    const Vector2 gravity= {0.0f, 9.8f};
    const int screenWidth = 800;
    const int screenHeight = 450;
    Vector2 initCerc= {100.f, 100.0f};
    circle c(initCerc,5);
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    SetTargetFPS(60);
    while(WindowShouldClose()==false){


        Vector2 cValues=c.getPosition();
        int cRadius=c.getRadius();
        if(cValues.y<450)
            c.changePosition(gravity);
        else
            c.changePosition((Vector2){50.0f, -450.f});
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Lets get this bread", 190, 200, 20, LIGHTGRAY);
        
        DrawCircle(cValues.x, cValues.y, cRadius, MAROON);
        EndDrawing();
    }
    CloseWindow();
    

    return 0;
}