#include <func.h>

circle::circle(Vector2 start, float rad)
{
    std::cout << "New circle object created at " << start.x << " " << start.y << '\n';
    position.x = start.x;
    position.y = start.y;
    radius = rad;
    weight = radius * radius * 3.14f;
    subStep=0;
}
Vector2 circle::getPosition() { return position;}
int circle::getRadius() { return radius;}
Vector2 circle::getVelocity() { return velocity;}

void circle::changePosition(Vector2 vector){
    position.x += vector.x;
    position.y += vector.y;
}
void circle::changeRadius(float ammount){
    radius += ammount;
}
void circle::changeVelocity(Vector2 acceleration){

    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    velocity.x *= friction;
    velocity.y *= friction;
}
void circle::setPosition(Vector2 pos){
    position.x = pos.x;
    position.y = pos.y;
}
void circle::setVelocity(Vector2 veloc){
    velocity=veloc;
}
void circle::handleCollision(line hitLine, float distance){

        Vector2 penetration = Vector2Scale(hitLine.normal, radius - abs(distance));
        float value = -2 * Vector2DotProduct(hitLine.normal, velocity) * restitution;
        if (distance < 0)
            penetration=Vector2Scale(penetration,-1);
                        
        changeVelocity(Vector2Scale(hitLine.normal, value));
        changePosition(penetration);
}
float circle::getWeight()
{
    return weight;
}
void handleCircleCollision(circle& firstCircle, circle& secondCircle){

    float distance = Vector2Distance(firstCircle.getPosition(), secondCircle.getPosition());
    if(distance>firstCircle.getRadius()+secondCircle.getRadius())
        return;
    /// Calculate the line between the two circles
    line firstToSecond(firstCircle.getPosition(), secondCircle.getPosition());
    /// The normal I calculate in the Line constructor is actually the normal of the tangent
    Vector2 normal = Vector2Normalize(firstToSecond.lineDirection),
            tangent = firstToSecond.normal;  ///Need to rename the Line class because of this
    float firstVelocityTangent=Vector2DotProduct(firstCircle.getVelocity(), tangent),
          firstVelocityNormal=Vector2DotProduct(firstCircle.getVelocity(), normal),
          secondVelocityTangent=Vector2DotProduct(secondCircle.getVelocity(), tangent),
          secondVelocityNormal=Vector2DotProduct(secondCircle.getVelocity(), normal);
    float firstVelocityPrime=secondVelocityNormal;
    float secondVelocityPrime=firstVelocityNormal;
   
    /// As we know, the tangential component does not suffer modifications, so we just need to compose the new velocities and assign them.
    Vector2 composedFirstVelocity=Vector2Add(Vector2Scale(normal, firstVelocityPrime),Vector2Scale(tangent,firstVelocityTangent)),
            composedSecondVelocity=Vector2Add(Vector2Scale(normal, secondVelocityPrime),Vector2Scale(tangent,secondVelocityTangent));
    /// To add tommorow: redefine Line, penetration, mass
    firstCircle.setVelocity(composedFirstVelocity);
    secondCircle.setVelocity(composedSecondVelocity);
    
    

}

void circle::continueMovement(float stepMultiplier){
    changeVelocity(Vector2Scale(gravity, perFrame));
    changePosition(Vector2Scale(getVelocity(), perFrame*stepMultiplier));
}

line::line(Vector2 a, Vector2 b)
{
    firstPoint = a;
    secondPoint = b;
    lineVector = Vector2Subtract(a, b);
    lineDirection= lineVector;
    lineVector = {-lineVector.y, lineVector.x};
    normal = Vector2Normalize(lineVector);
}

void calculateSubSteps(float speed, int& steps, float& multiplier)
{
    steps=speed/300+1;
    multiplier=1.0/steps;
}