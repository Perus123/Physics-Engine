#include <iostream>
#include <raylib.h>
#include <func.h>

using namespace std;

int main () {

    circle c(100,100,5);
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    

    return 0;
}