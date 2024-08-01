#include <func.h>

int main () {
    ///Animation and display constants
    const int screenWidth=1600;
    const int screenHeight=900;
    
    ///Objects initialization
    Vector2 initCircle= {100.f, 100.0f};
    circle c(initCircle,20);
    line l((Vector2){0,600},(Vector2){1600,650});
    std::cout<<l.normal.x<<" "<<l.normal.y<<'\n';
  
    char *message={"Lets get this bread"};
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    SetTargetFPS(60);
    while(WindowShouldClose()==false){

        
        Vector2 cValues=c.getPosition();
        int cRadius=c.getRadius();
        Vector2 circleToLine=Vector2Subtract(c.getPosition(),l.firstPoint); 
        float dis = Vector2DotProduct(circleToLine,l.normal);   
         if(abs(dis)<=c.getRadius())
        {
            Vector2 penetration = Vector2Scale(l.normal , c.getRadius() - abs(dis));
            c.changePosition(penetration);
            float value=-2*Vector2DotProduct(l.normal, c.getVelocity())*restitution;
            c.changeVelocity(Vector2Scale(l.normal,value)); 
            std::cout<<dis<<'\n';
        }
         if(cValues.y<screenHeight-c.getRadius()&&cValues.x<screenWidth)
        {    
             c.changeVelocity(Vector2Scale(gravity, 0.01f));
             c.changePosition(c.getVelocity());
        }
       
        else 
        {
          /// Vector2 finalPosition=c.getPosition();
          /// std::cout<<finalPosition.x<<" "<<finalPosition.y<<" ";
          c.setPosition({0.0f, (float)600-c.getRadius()});
          
        }
       
        
        BeginDrawing();  ///start draw
        ClearBackground(BLACK);
        DrawText(message, 390, 400, 50, LIGHTGRAY);
        DrawLine(0,600,1600,650, BLUE);
        DrawCircle(cValues.x, cValues.y, cRadius, MAROON);
        EndDrawing(); ///stop draw
    }
    CloseWindow();
    

    return 0;
}