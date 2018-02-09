#include "main.h"

#ifndef POND_H
#define POND_H

class Pond{
public:
  Pond() {}
  Pond(float position_x, float position_y, color_t color);
  void draw(glm::mat4 VP);
  glm::vec3 position;
  float radius;
private:
  VAO *object;
};

#endif // POND_H
