#include <func.h>

int main()
{
    /// Animation and display constants
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Physics simulator - Gravity");
    char *message = {"Lets get this bread"};
    /// Objects initialization
    std::vector<circle> circles;
    std::vector<line> lines;
    Vector2 initCircle = {100.f, 100.0f};

    circle c(initCircle, 20);
    initCircle = {130.0f, 100.0f};
    circle c2(initCircle, 20);
    circles.push_back(c);
    circles.push_back(c2);
    line l((Vector2){0, 600}, (Vector2){1600, 650}),
         l2((Vector2){1600,650},(Vector2){800,0}),
         l3((Vector2){800,0},(Vector2){0,600});
    lines.push_back(l);
    lines.push_back(l2);
    lines.push_back(l3);
    std::cout << l.normal.x << " " << l.normal.y << '\n';

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {

        for (int i = 0; i < circles.size(); i++)
        {
            Vector2 cValues = circles[i].getPosition();
            Vector2 circleToLine = Vector2Subtract(circles[i].getPosition(), l.firstPoint);
            float dis = Vector2DotProduct(circleToLine, l.normal);
            if (abs(dis) <= circles[i].getRadius())
            {
                Vector2 penetration = Vector2Scale(l.normal, circles[i].getRadius() - abs(dis));

                float value = -2 * Vector2DotProduct(l.normal, circles[i].getVelocity()) * restitution;
                circles[i].changeVelocity(Vector2Scale(l.normal, value));
                circles[i].changePosition(penetration);
                circles[i].changePosition(circles[i].getVelocity());
                std::cout << dis << '\n';
            }
            else if (cValues.y < screenHeight - circles[i].getRadius() && cValues.x < screenWidth)
            {
                circles[i].changeVelocity(Vector2Scale(gravity, 0.01f));
                circles[i].changePosition(circles[i].getVelocity());
            }

            else if (cValues.x > screenWidth)
            {
                /// Vector2 finalPosition=c.getPosition();
                /// std::cout<<finalPosition.x<<" "<<finalPosition.y<<" ";
                circles[i].setPosition({0.0f, (float)600 - circles[i].getRadius()});
            }
        }

        BeginDrawing(); /// start draw
        ClearBackground(BLACK);
        DrawText(message, 390, 400, 50, LIGHTGRAY);
        DrawLine(0, 600, 1600, 650, BLUE);
        for (int i = 0; i < circles.size(); i++)
        {
            Vector2 position = circles[i].getPosition();
            DrawCircle(position.x, position.y, circles[i].getRadius(), MAROON);
        }
        EndDrawing(); /// stop draw
    }
    CloseWindow();

    return 0;
}