#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <raylib.h>

class circle {
      Vector2 position; 
      Vector2 velocity={0.0f, 0.0f};
      float radius,weight;
      public:
      circle(Vector2 start,float rad);
      Vector2 getPosition();
      void changePosition(Vector2 vector);
      int getRadius();
      void changeRadius(float ammount);
      Vector2 getVelocity();
      void changeVelocity(Vector2 acceleration);
      
};
#endif 
