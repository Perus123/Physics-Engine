#pragma once
#ifndef solver_HPP
#define solver_HPP
#include <raylib.h>
#include <raymath.h>
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
        acceleration={float(0), float(0)};
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
        last_position=Vector2Add(position,(Vector2Scale(v,-dt)))
    }
    

};

#endif

