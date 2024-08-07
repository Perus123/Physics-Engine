#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>

/// Physics constants
const float friction = 1;
const float restitution = 0.8;
const Vector2 gravity = {0.0f, 5.0f};
class circle
{
      Vector2 position;
      Vector2 velocity = {0.0f, 0.0f};
      float radius, weight;

public:
      circle(Vector2 start, float rad);
      Vector2 getPosition();
      void changePosition(Vector2 vector);
      int getRadius();
      void changeRadius(float ammount);
      Vector2 getVelocity();
      void changeVelocity(Vector2 acceleration);
      void setPosition(Vector2 pos);
};
class line
{
public:
      Vector2 firstPoint, secondPoint;
      Vector2 lineVector;
      Vector2 normal;
      line(Vector2 a, Vector2 b);
};

#endif
