#include <func.h>

circle::circle(Vector2 start, float rad)
{
    std::cout << "New circle object created at " << start.x << " " << start.y << '\n';
    position.x = start.x;
    position.y = start.y;
    radius = rad;
    weight = radius * radius * 3.14f;
}
Vector2 circle::getPosition()
{
    return position;
}
int circle::getRadius()
{
    return radius;
}
Vector2 circle::getVelocity()
{
    return velocity;
}
void circle::changePosition(Vector2 vector)
{
    position.x += vector.x;
    position.y += vector.y;
}
void circle::changeRadius(float ammount)
{
    radius += ammount;
}
void circle::changeVelocity(Vector2 acceleration)
{

    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    velocity.x *= friction;
    velocity.y *= friction;
}
void circle::setPosition(Vector2 pos)
{
    position.x = pos.x;
    position.y = pos.y;
}

line::line(Vector2 a, Vector2 b)
{
    firstPoint = a;
    secondPoint = b;
    lineVector = Vector2Subtract(a, b);
    lineVector = {-lineVector.y, lineVector.x};
    normal = Vector2Normalize(lineVector);
}
