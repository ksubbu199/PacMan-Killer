#include "main.h"

#ifndef GROUND_H
#define GROUND_H

class Ground{
public:
  Ground() {}
  Ground(float x, float y,float base_height, float grass_height, color_t color_base, color_t color_grass);
  void draw(glm::mat4 VP);
  glm::vec3 top_left;
  glm::vec3 position;
private:
  VAO *objectBase;
  VAO *objectGrass;
};




#endif // GROUND_H
