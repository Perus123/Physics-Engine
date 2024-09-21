#pragma once
#ifndef solver_HPP
#define solver_HPP
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
class Solver;
class boundaryCircle;
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
struct boundaryCircle
{   
    float radius;
    Vector2 position;
    boundaryCircle(Vector2 position_,float radius_)
    {
        position=position_;
        radius=radius_;
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
        obj.last_position=auxiliary_position;
    }
    void keepBoundary(VerletObject& obj, boundaryCircle container)
    {
        float distance = Vector2Distance(obj.position, container.position);
        if(distance>=container.radius-obj.radius-0.5f)
        {   
            Vector2 direction= Vector2Subtract(obj.position, container.position);
            direction = Vector2Normalize(direction);
            Vector2 correction_vector=Vector2Scale(direction, container.radius-obj.radius);
            ///obj.last_position=obj.position;
            obj.position=Vector2Add(container.position,correction_vector);
        }
        
    }
    void solveCollision(VerletObject& obj1, VerletObject& obj2)
    {
        float distance = Vector2Distance(obj1.position, obj2.position);
        if(distance>=obj1.radius+obj2.radius)
            return;
        Vector2 direction = Vector2Subtract(obj1.position, obj2.position);
        direction=Vector2Normalize(direction);
        Vector2 correction_vector=Vector2Scale(direction, abs(distance-obj1.radius-obj2.radius));
        obj1.position=Vector2Add(obj1.position, correction_vector);
        obj2.position=Vector2Subtract(obj2.position, correction_vector);

    }
    
};


#endif

