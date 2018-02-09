#include "ball.h"
#include "main.h"
#include "helper.cpp"


#define PI 3.14159265
using namespace std;
Ball::Ball(float x, float y, float radius, float speed,bool hasSlab, color_t color) {
    this->position = glm::vec3(x, y, 0);

    this->rotation = 0;
    this->radius = radius;
    this->isScored = false;
    this->speed = speed;
    this->object = generator.circle(5,360, radius, color);

    this->hasSlab = hasSlab;
    if(hasSlab)
    {
      const float slabHeight = 0.1;
      const float slabWidth = 0.5;
      this->slab_dimensions.x = slabWidth;
      this->slab_dimensions.y = slabHeight;
      color_t slab_color = (color_t){ 236, 100, 75 };
      this->objectSlab = generator.rectangle(-slabWidth/2,-slabHeight/2,slabWidth, slabHeight,slab_color );
    }

}

void Ball::draw(glm::mat4 VP) {
    helper_draw(VP, this->position, this->rotation, this->object);
    if(this->hasSlab)
    {
      glm::vec3 slab_draw_pos = glm::vec3(this->position.x  -( this->radius + this->slab_dimensions.y/2)*cos(PI/4),this->position.y -(  this->radius + this->slab_dimensions.y/2)*sin(PI/4), 0);
      helper_draw(VP, slab_draw_pos, 135, this->objectSlab );
    }
}


glm::vec3 Ball::get_slab_bottom()
{
  glm::vec3 slab_pos = glm::vec3(-(this->radius)*cos(PI/4), -(this->radius)*sin(PI/4), 0);
  glm::vec3 slab_bottom = glm::vec3(slab_pos.x, slab_pos.y, 0 );

  return glm::vec3(this->position.x + slab_bottom.x, this->position.y + slab_bottom.y, 0);
}

glm::vec3 Ball::get_slab_top()
{
  glm::vec3 slab_pos = glm::vec3(-(this->radius)*cos(PI/4), -(this->radius)*sin(PI/4), 0);
  glm::vec3 slab_top = glm::vec3(slab_pos.x - this->slab_dimensions.x/(2*cos(PI/4)), slab_pos.y + this->slab_dimensions.x/(2*cos(PI/4)), 0 );

  return glm::vec3(this->position.x + slab_top.x, this->position.y + slab_top.y, 0);
}

void Ball::tick() {
  this->position.x += this->speed;
}
