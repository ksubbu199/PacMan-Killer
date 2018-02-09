#include "magnet.h"
#include "main.h"
#include "helper.cpp"

using namespace std;

Magnet::Magnet(float x, float y, color_t color){

  this->position = glm::vec3(x, y, 0);
  this->isOnLeft = true;
  this->rotation = 0;

  this->isOn = false;

  float r1 = 0.6;
  float r2 = 0.3;
  float r_diff = r1 - r2;
  float width= 0.7;
  float height=r_diff;
  this->bigCircle = generator.circle(5,180,r1,color);
  this->smallCircle = generator.circle(5,180,r2,(color_t){0,0,0});

  this->downRect = generator.rectangle(-width/2,-r1,width, height,color);
  this->upRect = generator.rectangle(-width/2,r2,width, height, color);

}


void Magnet::draw(glm::mat4 VP) {

    helper_draw(VP, this->position, 0, this->upRect);
    helper_draw(VP, this->position, 0, this->downRect);

    if(this->isOnLeft)
    {
      glm::vec3 draw_pos = glm::vec3(this->position.x - 0.35, this->position.y, 0);
      helper_draw(VP, draw_pos, 90, bigCircle);
      helper_draw(VP, draw_pos, 90, smallCircle);
    }
    else
    {
      glm::vec3 draw_pos = glm::vec3(this->position.x + 0.35, this->position.y, 0);
      helper_draw(VP, draw_pos, -90, bigCircle);
      helper_draw(VP, draw_pos, -90, smallCircle);
    }
}
