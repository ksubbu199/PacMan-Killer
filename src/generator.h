#include "main.h"
#ifndef GENERATOR_H
#define GENERATOR_H


class Generator {
public:
    Generator() {}
    VAO* rectangle(float x,float y,float width,float height, color_t color);
    VAO* circle(int angle1, int angle_cover, float radius, color_t color);
};

#endif // GENERATOR_H
