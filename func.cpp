#include <func.h>

circle::circle(Vector2 start,float rad)
      {
          std::cout<<"New circle object created at "<<start.x<<" "<<start.y<<'\n';
          position.x=start.x;
          position.y=start.y;
          radius=rad;
          weight=radius*radius*3.14f;
      }
Vector2 circle::getPosition()
{
    return position;
}
int circle::getRadius()
{
    return radius;
}
void circle::changePosition(Vector2 vector)
{
    position.x+=vector.x;
    position.y+=vector.y;
}
void circle::changeRadius(float ammount)
{
    radius+=ammount;
}



