#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>

/// Physics constants
const float friction = 0.999;
const float restitution = 0.9;
const Vector2 gravity = {0.0f, 60.0f};
/// Rendering constants
const float perFrame = 1.0/60;


class line
{
public:
      Vector2 firstPoint, secondPoint;
      Vector2 lineVector, lineDirection;
      Vector2 normal;
      line(Vector2 a, Vector2 b);
};
class circle
{
      Vector2 position;
      Vector2 velocity = {500.0f, 0.0f};
      float radius, weight;

public:
      int subStep;
      circle(Vector2 start, float rad);

      Vector2 getPosition();
      Vector2 getVelocity();
      int getRadius();
      float getWeight();

      void changeRadius(float ammount);
      void changePosition(Vector2 vector);
      void changeVelocity(Vector2 acceleration);

      void setPosition(Vector2 pos);
      void setVelocity(Vector2 veloc);

      void handleCollision(line hitLine, float distance);
      void continueMovement(float stepMultiplier);
      
};
bool projectionIsOnLine(line Line, Vector2 projection, float projectionScalar);
void handleCircleCollision(circle& firstCircle, circle& secondCircle);
void calculateSubSteps(float speed, int& steps, float& multiplier);
#endif
