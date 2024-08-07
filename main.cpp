#include <func.h>

int main()
{
    /// Animation and display constants
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    char *message = {"Lets get this bread"};
    /// Objects initialization
    std::vector<circle> circleArray;
    std::vector<line> lineArray;

    Vector2 initCircle = {100.f, 100.0f};
    circle c(initCircle, 20);
    initCircle = {130.0f, 100.0f};
    circle c2(initCircle, 20);
    circleArray.push_back(c);
    circleArray.push_back(c2);

    line l((Vector2){0, 600}, (Vector2){1600, 650}),
        l2((Vector2){1600, 650}, (Vector2){800, 0}),
        l3((Vector2){800, 0},(Vector2){0, 600});
    lineArray.push_back(l);
    lineArray.push_back(l2);
    lineArray.push_back(l3);
    

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {

        for (int i = 0; i < circleArray.size(); i++)
        {

            for (int j = 0; j < lineArray.size(); j++)
            {
                Vector2 cValues = circleArray[i].getPosition();
                Vector2 circleToLine = Vector2Subtract(circleArray[i].getPosition(), lineArray[j].firstPoint);
                float dis = Vector2DotProduct(circleToLine, lineArray[j].normal);
                if (abs(dis) <= circleArray[i].getRadius())
                {
                    Vector2 penetration = Vector2Scale(lineArray[j].normal, circleArray[i].getRadius() - abs(dis));
                    float value = -2 * Vector2DotProduct(lineArray[j].normal, circleArray[i].getVelocity()) * restitution;
                    circleArray[i].changeVelocity(Vector2Scale(lineArray[j].normal, value));
                    circleArray[i].changePosition(penetration);
                    circleArray[i].changePosition(circleArray[i].getVelocity());
                    std::cout << dis << '\n';
                }
                else if (cValues.y < screenHeight - circleArray[i].getRadius() && cValues.x < screenWidth)
                {
                    circleArray[i].changeVelocity(Vector2Scale(gravity, 0.01f));
                    circleArray[i].changePosition(circleArray[i].getVelocity());
                }

                else if (cValues.x > screenWidth)
                {
                    /// Vector2 finalPosition=c.getPosition();
                    /// std::cout<<finalPosition.x<<" "<<finalPosition.y<<" ";
                    circleArray[i].setPosition({0.0f, (float)600 - circleArray[i].getRadius()});
                }
            }
        }

        BeginDrawing(); /// start draw
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
            DrawLine(start.x , start.y, finish.x, finish.y, BLUE);
        }
        EndDrawing(); /// stop draw
    }
    CloseWindow();

    return 0;
}