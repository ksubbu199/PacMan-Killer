#include "pond.h"
#include "main.h"
#include "helper.cpp"

#define PI 3.14159265
using namespace std;


Pond::Pond(float position_x, float position_y, color_t color){

	const float angle = 1;
	int count=180/angle;
	GLfloat g_vertex_buffer_data[10000];
	int size=0;
	float curx,cury;

  this->position = glm::vec3(position_x, position_y, 0);
	this->radius = 1;

	this->object = generator.circle(5, 180, this->radius, color);
}


void Pond::draw(glm::mat4 VP) {
		helper_draw(VP, this->position, -180, this->object);
}
