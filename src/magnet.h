#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    bool isOn;
    float speed;
    bool isOnLeft;
    void jump();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void rotate(float degree);
    bounding_box_t bounding_box();
private:
    VAO *bigCircle;
    VAO *smallCircle;
    VAO *upRect;
    VAO *downRect;
};

#endif // MAGNET_H
