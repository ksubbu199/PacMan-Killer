#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

class Trampoline{
public:
  Trampoline() {}
  Trampoline(float position_x, float position_y, float height, float radius, color_t color);
  void draw(glm::mat4 VP);
  float width,height;
  glm::vec3 position;
private:
  VAO *objectStandLeft;
  VAO *objectStandRight;
  VAO *objectTrampoline;
};

#endif // TRAMPOLINE_H
