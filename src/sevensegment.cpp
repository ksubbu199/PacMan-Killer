#include "helper.cpp"
#include "sevensegment.h"
#define PI 3.14159265
using namespace std;

Sevensegment::Sevensegment(char letter, float x, float y)
{
  color_t font_color = {229,  0,  0};
  float font_height=0.1, font_width=0.5;
  this->letter = letter;
  this->position.x = x;
  this->position.y = y;
  this->font_height = font_height;
  this->font_width = font_width;
  this->segment = generator.rectangle(-font_width/2, - font_height/2,font_width, font_height, font_color);

}

void Sevensegment::set_position(float x, float y)
{
  this->position.x = x;
  this->position.y = y;
}

void Sevensegment::set_letter(char letter)
{
  this->letter = letter;
}
void Sevensegment::draw(glm::mat4 VP)
{
  bool *code;
  bool seven[7];
  switch(this->letter)
  {
    case '0': seven[0]=0;
              seven[1]=1;
              seven[2]=1;
              seven[3]=1;
              seven[4]=1;
              seven[5]=1;
              seven[6]=1;
              break;
    case '1': seven[0]=0;
              seven[1]=0;
              seven[2]=1;
              seven[3]=0;
              seven[4]=0;
              seven[5]=1;
              seven[6]=0;
              break;


  case '2': seven[0]=1;
            seven[1]=1;
            seven[2]=1;
            seven[3]=0;
            seven[4]=1;
            seven[5]=0;
            seven[6]=1;
            break;
  case '3': seven[0]=1;
            seven[1]=1;
            seven[2]=1;
            seven[3]=0;
            seven[4]=1;
            seven[5]=1;
            seven[6]=0;
            break;


  case '4': seven[0]=1;
            seven[1]=0;
            seven[2]=0;
            seven[3]=1;
            seven[4]=0;
            seven[5]=1;
            seven[6]=0;
            break;
  case '5': seven[0]=1;
            seven[1]=1;
            seven[2]=0;
            seven[3]=1;
            seven[4]=1;
            seven[5]=1;
            seven[6]=0;
            break;



  case '6': seven[0]=1;
            seven[1]=1;
            seven[2]=0;
            seven[3]=1;
            seven[4]=1;
            seven[5]=1;
            seven[6]=1;
            break;
  case '7': seven[0]=0;
            seven[1]=1;
            seven[2]=1;
            seven[3]=0;
            seven[4]=0;
            seven[5]=1;
            seven[6]=0;
            break;

  case '8': seven[0]=1;
            seven[1]=1;
            seven[2]=1;
            seven[3]=1;
            seven[4]=1;
            seven[5]=1;
            seven[6]=1;
            break;
  case '9': seven[0]=1;
            seven[1]=1;
            seven[2]=1;
            seven[3]=1;
            seven[4]=0;
            seven[5]=1;
            seven[6]=0;
            break;
}
  code = seven;
  glm::vec3 pos;
  //cout<<this->letter<<endl;
  for(int i=0;i<7;i++)
  {
    if(code[i]==0) continue;
    switch(i)
    {
      case 0: helper_draw(VP, this->position, 0, this->segment); break;
      case 1:
              //glm::vec3 pos;
              pos.x = this->position.x;
              pos.y = this->position.y +this->font_width;
              helper_draw(VP, pos, 0, this->segment); break;
      case 2:
              //glm::vec3 pos;
              pos.x = this->position.x +this->font_width/2;
              pos.y = this->position.y +this->font_width/2 ;
              helper_draw(VP, pos, 90, this->segment); break;
      case 3:
              //glm::vec3 pos;
              pos.x = this->position.x - this->font_width/2;
              pos.y = this->position.y + this->font_width/2;
              helper_draw(VP, pos, 90, this->segment); break;
      case 4:
              //glm::vec3 pos;
              pos.x = this->position.x ;
              pos.y = this->position.y - this->font_width;
              helper_draw(VP, pos, 0, this->segment); break;

      case 5:
              //glm::vec3 pos;
              pos.x = this->position.x +this->font_width/2;
              pos.y = this->position.y -this->font_width/2;
              helper_draw(VP, pos, -90, this->segment); break;
      case 6:
              //glm::vec3 pos;
              pos.x = this->position.x - this->font_width/2;
              pos.y = this->position.y - this->font_width/2;
              helper_draw(VP, pos, -90, this->segment); break;
    }

  }
}
