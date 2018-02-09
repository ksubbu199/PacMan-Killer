#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
  Player() {}
  Player(float position_x, float position_y);
  void draw(glm::mat4 VP);
  glm::vec3 position;
  glm::vec3 speed;
  int color_count;
  void updateSpeedX(float x);
  void updateSpeedY(float y);
  void resetSpeedY();
  void tick(float friction, float y_limit_bottom);
  void moveLeft(float value);
  void moveRight(float value);
  void jump(float value);
  void gravity(float value, float limit);
  float rotation;
  float radius;
private:
  VAO **object;
};

#endif // POND_H
