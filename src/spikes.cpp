#include "spikes.h"
#include "main.h"

using namespace std;

Spikes::Spikes(int count, float position_x, float position_y, int time_limit, color_t color){
  VAO **obj = (VAO **)malloc(count * sizeof(VAO*));
  this->spike_count = count;
  this->position = glm::vec3(position_x, position_y, 0);
  this->spawn_position = glm::vec3(position_x, position_y, 0);
  this->isOn = false;
  this->movingRight = true;
  this->time_limit = time_limit;
  this->timer = 0;
  float width = 0.25;
  float height = 0.25;
  float current_pos_x = 0;
  float current_pos_y = 0;
  for(int i = 0 ; i < count; i++)
  {
    GLfloat vertex_buffer_data[] = {
        current_pos_x,          current_pos_y, 0, // vertex 1
        current_pos_x + width,  current_pos_y, 0, // vertex 2
        current_pos_x + width/2,current_pos_y + height,        0, // vertex 3
    };
    current_pos_x += width;
    obj[i] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
  }

  this->bounding_box = (bounding_box_t) { position_x, position_y, count*width, height };
  this->object = obj;
  this->width= count*width;
  this->height = height;
}


void Spikes::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i = 0; i < this->spike_count ; i++)
    {
      draw3DObject(this->object[i]);
    }
}

bounding_box_t Spikes::get_bounding_box() {
  return (bounding_box_t){this->position.x, this->position.y, this->width, this->height };
}

void Spikes::set_position(glm::vec3 position){
  this->position = position;
  this->spawn_position = position;
}
