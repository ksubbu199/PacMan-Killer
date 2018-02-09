#include "main.h"
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H


class Sevensegment {
public:
    Sevensegment(){};
    Sevensegment(char letter, float x, float y);
    char letter;
    bool* code;
    VAO * segment;
    float font_width, font_height;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_letter(char letter);
    void set_position(float x, float y);
};

#endif // SEVENSEGMENT_H
