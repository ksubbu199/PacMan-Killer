#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float radius, float speed, bool hasSlab, color_t color);
    glm::vec3 position,slab_dimensions;
    float rotation;
    float radius;
    bool isScored;
    float speed;
    void draw(glm::mat4 VP);
    bool hasSlab;
    glm::vec3 get_slab_top();
    glm::vec3 get_slab_bottom();
    void tick();
private:
    VAO *object;
    VAO *objectSlab;
};

#endif // BALL_H
