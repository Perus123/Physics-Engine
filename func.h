#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <raylib.h>
class circle {
      Vector2 position; 
      float radius,weight;
      public:
      circle(Vector2 start,float rad);
      Vector2 getPosition();
      void changePosition(Vector2 vector);
      int getRadius();
      void changeRadius(float ammount);
};
#endif 
