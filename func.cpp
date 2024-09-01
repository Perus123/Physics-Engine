#include <func.h>

circle::circle(Vector2 start, float rad){
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
    ///If the speed is too slow, there is no point in trying to let friction and restitution getting the objects to be static
    if(abs(velocity.x)+abs(velocity.y)<0.1f){
        velocity.x=0;
        velocity.y=0;
    }
        
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
        Vector2 normalLine=Vector2Normalize(hitLine.lineDirection);
        Vector2 circlePositionWithRespectToLine=Vector2Subtract(getPosition(), hitLine.secondPoint);
        float projectionScalar=Vector2DotProduct(normalLine, circlePositionWithRespectToLine);
        Vector2 lineProjection=Vector2Scale(normalLine, projectionScalar);
        float value = -2 * Vector2DotProduct(hitLine.normal, velocity) * restitution;
        
        if(projectionIsOnLine(hitLine, lineProjection, projectionScalar)) {

        if (distance < 0)
            penetration=Vector2Scale(penetration,-1);
                        
        changeVelocity(Vector2Scale(hitLine.normal, value));
        changePosition(penetration);
        }
}
float circle::getWeight(){
    return weight;
}
void circle::continueMovement(){
    changeVelocity(Vector2Scale(gravity, perFrame));
    changePosition(Vector2Scale(getVelocity(), perFrame*steps::subStepMultiplier));
}
void handleCircleCollision(circle& firstCircle, circle& secondCircle){

    float distance = Vector2Distance(firstCircle.getPosition(), secondCircle.getPosition());
    

    if(distance>=(firstCircle.getRadius()+secondCircle.getRadius()))
        return;
    /// Calculate the line between the two circles
    line firstToSecond(firstCircle.getPosition(), secondCircle.getPosition());
    Vector2 normal = Vector2Normalize(firstToSecond.lineDirection),
            tangent = firstToSecond.normal;  
    float firstVelocityTangent=Vector2DotProduct(firstCircle.getVelocity(), tangent),
          firstVelocityNormal=Vector2DotProduct(firstCircle.getVelocity(), normal),
          secondVelocityTangent=Vector2DotProduct(secondCircle.getVelocity(), tangent),
          secondVelocityNormal=Vector2DotProduct(secondCircle.getVelocity(), normal),
          firstMass=firstCircle.getWeight(),
          secondMass=secondCircle.getWeight();

    ///Calculate new velocities
    float firstVelocityPrime = (firstVelocityNormal * (firstMass - secondMass) + 2 * secondMass * secondVelocityNormal) / (firstMass + secondMass);
    float secondVelocityPrime = (secondVelocityNormal * (secondMass-firstMass) + 2 * firstMass * firstVelocityNormal) / (firstMass + secondMass);
    
    ///The tangential component does not suffer modifications, so we just need to compose the new velocities and assign them.
    Vector2 composedFirstVelocity=Vector2Add(Vector2Scale(normal, firstVelocityPrime),Vector2Scale(tangent,firstVelocityTangent)),
            composedSecondVelocity=Vector2Add(Vector2Scale(normal, secondVelocityPrime),Vector2Scale(tangent,secondVelocityTangent));

    ///Set a new substep if needed, since objects with big weights ragdoll smaller ones
    float m1=calculateSpeed(composedFirstVelocity), m2=calculateSpeed(composedSecondVelocity);
    steps::subStepCounter= std::max(steps::subStepCounter,int (m1/200.0) +1);
    steps::subStepCounter= std::max(steps::subStepCounter,int (m2/200.0) +1);
    steps::subStepMultiplier=1.0/steps::subStepCounter;

    ///Solve Penetration
    float penetration = firstCircle.getRadius()+secondCircle.getRadius()-distance;
    firstCircle.changePosition(Vector2Scale(normal, penetration));
    secondCircle.changePosition(Vector2Scale(normal, -penetration));

    ///Update and continue movement
    firstCircle.setVelocity(composedFirstVelocity);
    secondCircle.setVelocity(composedSecondVelocity); 
    firstCircle.continueMovement();
    secondCircle.continueMovement();

}


line::line(Vector2 a, Vector2 b){
    firstPoint = a;
    secondPoint = b;
    lineVector = Vector2Subtract(a, b);
    lineDirection= lineVector;
    lineVector = {-lineVector.y, lineVector.x};
    normal = Vector2Normalize(lineVector);
}
bool projectionIsOnLine(line Line, Vector2 projection, float projectionScalar){  
    float x=Vector2Length(Line.lineDirection);
    return 0.0<=projectionScalar/x&&projectionScalar/x<=1.0;
}
void calculateSubSteps(float speed){
    steps::subStepCounter=speed/200.0 +1;
    
    steps::subStepMultiplier=1.0/steps::subStepCounter;
}
float calculateSpeed(Vector2 speedComponents){
        return sqrt(speedComponents.x*speedComponents.x+speedComponents.y*speedComponents.y);
}