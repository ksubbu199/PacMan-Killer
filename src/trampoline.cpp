#include "trampoline.h"
#include "main.h"
#include "helper.cpp"

#define PI 3.14159265

using namespace std;

Trampoline::Trampoline(float position_x, float position_y, float height, float radius, color_t color){

  this->position = glm::vec3(position_x, position_y, 0);
  float stand_width=0.1;
  this->height = height;
  this->width = 2*(stand_width + radius);

  this->objectStandLeft = generator.rectangle(-radius -stand_width, -height, stand_width, height, color);
  this->objectStandRight = generator.rectangle(radius, -height, stand_width, height, color);
  this->objectTrampoline = generator.circle(5, 180, radius, color);
}


void Trampoline::draw(glm::mat4 VP) {
    helper_draw(VP, this->position, 0, this->objectStandLeft);
    helper_draw(VP, this->position, 0, this->objectStandRight);
    helper_draw(VP, this->position, -180, this->objectTrampoline);
}
