#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>

/// Physics constants
const float friction = 1;
const float restitution = 1;
const Vector2 gravity = {0.0f, 60.0f};
/// Rendering constans
const float perFrame = 1.0/60;


class circle
{
      Vector2 position;
      Vector2 velocity = {500.0f, 0.0f};
      float radius, weight;

public:
      int subStep;
      circle(Vector2 start, float rad);
      Vector2 getPosition();
      void changePosition(Vector2 vector);
      int getRadius();
      void changeRadius(float ammount);
      Vector2 getVelocity();
      void changeVelocity(Vector2 acceleration);
      void setPosition(Vector2 pos);
      void handleCollision(line hitLine, float distance);
};
class line
{
public:
      Vector2 firstPoint, secondPoint;
      Vector2 lineVector, lineDirection;
      Vector2 normal;
      line(Vector2 a, Vector2 b);
};
void calculateSubSteps(float speed, int& steps, float& multiplier);
#endif
