#include "main.h"

#ifndef SPIKES_H
#define SPIKES_H

class Spikes{
public:
  Spikes() {}
  glm::vec3 position,spawn_position;
  bounding_box_t bounding_box;
  Spikes(int count, float position_x, float position_y, int time_limit, color_t color);
  void set_position(glm::vec3 position);
  void draw(glm::mat4 VP);
  bool movingRight;
  int spike_count;
  bool isOn;
  int time_limit;
  float timer;
  float width;
  float height;
  bounding_box_t get_bounding_box();
private:
  VAO **object;
};




#endif // SPIKES_H
