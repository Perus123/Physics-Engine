#include <func.h>

int main()
{
    /// Animation and display constants and variables
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    char *message = {"Lets get this bread"};
    /// When velocity gets too big, there is a need for sub stepping
    steps::subStepMultiplier=1.0;
    steps::subStepCounter=1;
    /// Objects initialization

    std::vector<circle> circleArray;
    std::vector<line> lineArray;
    Vector2 initCircle = {100.f, 100.0f};
    circle c(initCircle, 20);
    
    circleArray.push_back(c);
 

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
    int fpscounter=0;
    while (WindowShouldClose() == false)
    {
       
         float speedMaximum=0;
         fpscounter++;
        for (int k = 0; k < steps::subStepCounter*2; k++)
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
                    }
                    circleArray[i].continueMovement();
                    
                }

                for(int j=0; j<circleArray.size(); j++)
                {
                    if(j!=i){
                        handleCircleCollision(circleArray[i], circleArray[j]);
                    }
                   /* for (int it = 0; it < lineArray.size(); it++){
                    Vector2 circleToLine = Vector2Subtract(circleArray[j].getPosition(), lineArray[it].firstPoint);
                    float distance = Vector2DotProduct(circleToLine, lineArray[it].normal);

                    if (abs(distance) <= circleArray[j].getRadius()) {
                        circleArray[j].handleCollision(lineArray[it], distance);
                    }
                    Vector2 circleToLine2 = Vector2Subtract(circleArray[i].getPosition(), lineArray[it].firstPoint);
                    float distance1 = Vector2DotProduct(circleToLine2, lineArray[it].normal);

                    if (abs(distance1) <= circleArray[i].getRadius()) {
                        circleArray[i].handleCollision(lineArray[it], distance1);
                    }
                    }*/

                }
                    /// Find max speed  
                if(speedMaximum<calculateSpeed(circleArray[i].getVelocity()))  
                        speedMaximum=calculateSpeed(circleArray[i].getVelocity());
                    
                
            } 
        }  
        if(fpscounter%5==0){
            circle  cc(initCircle, 20);
            circleArray.push_back(cc);
        }
        std::cout<<steps::subStepCounter<<'\n';
        calculateSubSteps(speedMaximum);
       
        
         /// Update sub steps after every iteration
        
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