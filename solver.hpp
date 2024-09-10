#pragma once
#ifndef solver_HPP
#define solver_HPP
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
class Solver;
class VerletObject
{
    public: 
       Vector2 position;
       Vector2 last_position;
       Vector2 acceleration;
       float radius;
    VerletObject()=default;
    VerletObject(Vector2 position_, float radius_)
    {
        position=position_;
        last_position=position_;
        radius = radius_;
        acceleration={float(0), float(400)};
    }
    void set_acceleration(Vector2 acceleration_)
    {
        acceleration=acceleration_;
    }
    void accelerate(Vector2 a)
    {
        acceleration=Vector2Add(acceleration, a);
    }
    void set_position(Vector2 position_)
    {
        position=position_;
        last_position=position_;
    }
    void setVelocity(Vector2 v, float dt)
    {
        last_position=Vector2Add(position,(Vector2Scale(v,-dt)));
    }
    void addVelocity(Vector2 v, float dt)
    {
        last_position=Vector2Add(position,(Vector2Scale(v,-dt)));
    }
    

};
class Solver
{   public:
    Solver()=default;
    std::vector<VerletObject> objects;

    void move(VerletObject& obj, float dt)
    {
        Vector2 auxiliary_position=obj.position;
        obj.position=Vector2Add(Vector2Scale(obj.position,2),Vector2Scale(obj.last_position,-1));
        obj.position=Vector2Add(obj.position, Vector2Scale(obj.acceleration, 1.0/(dt*dt)));
        std::cout<<obj.position.x<<" "<<obj.position.y<<" se intampla cv\n";
     
        obj.last_position=auxiliary_position;
    }
    ///void keepBoundary(VerletObject)
    
};

class boundaryCircle:
{
    float x,y,radius;
    boundaryCircle(float x_, float y_, float radius_)
    {
        x=x_;
        y=y_;
        radius=radius_;
    }
}
#endif

