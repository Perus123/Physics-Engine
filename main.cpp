#include <func.h>

int main()
{
    /// Animation and display constants and variables
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    char *message = {"Lets get this bread"};
    /// When velocity gets too big, there is a need for sub stepping
    int subStepCounter=1;
    float subStepMultiplier=1.0;
    /// Objects initialization

    std::vector<circle> circleArray;
    std::vector<line> lineArray;
    Vector2 initCircle = {100.f, 500.0f};
    circle c(initCircle, 20);
    initCircle = {1060.0f, 490.0f};
    circle c2(initCircle, 20);
    circleArray.push_back(c);
    circleArray.push_back(c2);

    /// Creating a square
    line l((Vector2){0, 0}, (Vector2){1600, 0}),
        l2((Vector2){1600, 0}, (Vector2){1600, 900}),
        l3((Vector2){0, 900}, (Vector2){0, 0}),
        l4((Vector2){1600, 900}, (Vector2){0, 900});
    lineArray.push_back(l);
    lineArray.push_back(l2);
    lineArray.push_back(l3);
    lineArray.push_back(l4);

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        float speedMaximum=0;
        
        for (int k = 0; k < subStepCounter; k++)
        {
            for (int i = 0; i < circleArray.size(); i++) /// All circles
            {
                for (int j = 0; j < lineArray.size(); j++) /// All lines 
                {
                    /// Circle to line vector, for calculating distance
                    Vector2 circleToLine = Vector2Subtract(circleArray[i].getPosition(), lineArray[j].firstPoint);
                    float distance = Vector2DotProduct(circleToLine, lineArray[j].normal);

                    if (abs(distance) <= circleArray[i].getRadius()) {
                        circleArray[i].handleCollision(lineArray[j], distance);
                        circleArray[i].continueMovement(subStepMultiplier);
                    }
                    else {
                        circleArray[i].continueMovement(subStepMultiplier);
                    }
                }

                for(int j=0; j<circleArray.size(); j++)
                {
                    if(j!=i){
                        handleCircleCollision(circleArray[i], circleArray[j]);
                    }
                }

                if(speedMaximum<abs(circleArray[i].getVelocity().x)||speedMaximum<abs(circleArray[i].getVelocity().y)) /// Find max speed
                    speedMaximum=__max(abs(circleArray[i].getVelocity().x),abs(circleArray[i].getVelocity().y));
                
            } 
        }  
        
        calculateSubSteps(speedMaximum, subStepCounter, subStepMultiplier); /// Update sub steps after every iteration
        BeginDrawing(); /// Start draw
        ClearBackground(BLACK);
        DrawText(message, 390, 400, 50, LIGHTGRAY);
       
        for (int i = 0; i < circleArray.size(); i++)
        {
            Vector2 position = circleArray[i].getPosition();
            DrawCircle(position.x, position.y, circleArray[i].getRadius(), MAROON);
        }
        for (int j = 0; j < lineArray.size(); j++)
        {
            Vector2 start, finish;
            start = lineArray[j].firstPoint;
            finish = lineArray[j].secondPoint;
            DrawLine(start.x, start.y, finish.x, finish.y, BLUE);
        }
        EndDrawing(); /// Stop draw
      

    }
    CloseWindow();

    return 0;
}