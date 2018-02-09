#include "ground.h"
#include "helper.cpp"
#include "main.h"

using namespace std;

Ground::Ground(float x, float y, float base_height, float grass_height, color_t color_base, color_t color_grass){
  float width = INT_MAX;
  this->position.x = x;
  this->position.y = y;

  this->objectBase = generator.rectangle(0, 0, width, base_height, color_base);
  this->objectGrass = generator.rectangle(0, base_height - grass_height/2, width, grass_height, color_grass);
}


void Ground::draw(glm::mat4 VP) {
    helper_draw(VP, this->position, 0, this->objectBase);
    helper_draw(VP, this->position, 0, this->objectGrass);
}
