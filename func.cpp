#include <func.h>
#include <iostream>

circle::circle(float xstart, float ystart,float rad)
      {
          std::cout<<"New circle object created at "<<xstart<<" "<<ystart<<'\n';
          x=xstart;
          y=ystart;
          radius=rad;
          weight=radius*radius*3.14f;
      }



