#include "main.h"
#include <cmath>
#include "generator.h"
#define PI 3.14159265
using namespace std;

VAO* Generator::circle(int angle1, int angle_cover, float radius, color_t color)
{
  const float angle = angle1;
  int count = angle_cover/angle;
  GLfloat g_vertex_buffer_data[1000];
  int size = 0;
  float curx,cury;

  while(count > 0)
  {
    g_vertex_buffer_data[size++]=0.0f;
    g_vertex_buffer_data[size++]=0.0f;
    g_vertex_buffer_data[size++]=0.0f;

    if(size < 4)
    {
      g_vertex_buffer_data[size++]=radius;
      g_vertex_buffer_data[size++]=0.0f;
      g_vertex_buffer_data[size++]=0.0f;

      curx=radius;
      cury=0.0f;
    }
    else
    {
      curx=g_vertex_buffer_data[size-6];
      cury=g_vertex_buffer_data[size-5];

      g_vertex_buffer_data[size++]=curx;
      g_vertex_buffer_data[size++]=cury;
      g_vertex_buffer_data[size++]=0.0f;
    }

    g_vertex_buffer_data[size++]=curx*cos(angle*PI/180)-cury*sin(angle*PI/180);
    g_vertex_buffer_data[size++]=curx*sin(angle*PI/180)+cury*cos(angle*PI/180);
    g_vertex_buffer_data[size++]=0.0f;

    count--;
  }

  return create3DObject(GL_TRIANGLES, size/3, g_vertex_buffer_data, color, GL_FILL);
}


VAO* Generator::rectangle(float x,float y,float width,float height, color_t color)
{
  const GLfloat vertex_buffer_data[] = {
        x, y, 0, // vertex 1
        x, y + height, 0, // vertex 2
        x + width, y + height, 0, // vertex 3

        x + width, y + height, 0, // vertex 3
        x + width, y, 0, // vertex 4
        x, y, 0 // vertex 1
  };

  return create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}
