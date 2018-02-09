#include "player.h"
#include "main.h"

#define PI 3.14159265
using namespace std;


Player::Player(float position_x, float position_y){

	const float angle = 3;
	this->rotation = 0;
	float curx,cury;
	float radius=0.25;
	this->radius = radius;
  color_t colors[6]={COLOR_PURE_RED, COLOR_ORANGE, COLOR_YELLOW,  COLOR_CYAN, COLOR_PURPLE, COLOR_DARK_GREEN};
  this->position = glm::vec3(position_x, position_y + radius, 0);
	this->speed = glm::vec3(0, 0, 0);
	const int color_c = 6;
	this->color_count = color_c;
	VAO **obj = (VAO **)malloc(color_c * sizeof(VAO*));

	float last_vertex_x, last_vertex_y;
  for(int c=0;c<color_c;c++)
  {
		int count=360/(angle*color_c);
    GLfloat g_vertex_buffer_data[10000/color_c];
		//cout<<c<<"\n";
		//GLfloat *g_vertex_buffer_data=(GLfloat*) malloc(10000*sizeof(GLfloat));
		int size=0;
  	while(count>0)
  	{
  		//int size= (sizeof(g_vertex_buffer_data)/sizeof(*g_vertex_buffer_data))/3;

  		g_vertex_buffer_data[size++]=0.0f;
  		g_vertex_buffer_data[size++]=0.0f;
  		g_vertex_buffer_data[size++]=0.0f;

  		if(size<4&&c==0)
  		{
				//cout<<"c:"<<c<<"\t size:"<<size<<"\n";
  			g_vertex_buffer_data[size++]=radius;
  			g_vertex_buffer_data[size++]=0.0f;
  			g_vertex_buffer_data[size++]=0.0f;

  			curx=radius;
  			cury=0.0f;
  		}
			else if(size<4 && c!=0)
			{
				//cout<<"new first c:"<<c<<"\t size:"<<size<<"\n";
				curx= last_vertex_x;
				cury= last_vertex_y;
				//cout<<"curx:"<<curx<<"\tcury:"<<cury<<"\n";
				g_vertex_buffer_data[size++]=curx;
  			g_vertex_buffer_data[size++]=cury;
  			g_vertex_buffer_data[size++]=0.0f;
			}
  		else
  		{
  			curx=g_vertex_buffer_data[size-6];
  			cury=g_vertex_buffer_data[size-5];

  			//printf("size:%d \t new vertex for (%f, %f)\n",size,curx,cury);
  			g_vertex_buffer_data[size++]=curx;
  			g_vertex_buffer_data[size++]=cury;
  			g_vertex_buffer_data[size++]=0.0f;
  		}

  		//printf("size:%d \t new vertex for (%f, %f)",size,curx,cury);
  		//printf("is : (%f, %f)\n",curx*cos(angle*PI/180)-cury*sin(angle*PI/180),curx*sin(angle*PI/180)+cury*cos(angle*PI/180));
  		g_vertex_buffer_data[size++]=curx*cos(angle*PI/180)-cury*sin(angle*PI/180);
  		g_vertex_buffer_data[size++]=curx*sin(angle*PI/180)+cury*cos(angle*PI/180);
  		g_vertex_buffer_data[size++]=0.0f;

  		count--;
  	}

		// for(int i=0;i<size;i++)
		// {
		// 	if(i%3==0) printf("\n");
		// 	printf("%d,%f\t",i,g_vertex_buffer_data[i]);
		// 	//cout<<g_vertex_buffer_data[i];
		// }
		//cout<<"\n\n"<<size-3<<":"<<g_vertex_buffer_data[size-3]<<"\t"<<size-2<<":"<<g_vertex_buffer_data[size-2]<<"\n";
		last_vertex_x=g_vertex_buffer_data[size-3];
		last_vertex_y=g_vertex_buffer_data[size-2];

    obj[c] = create3DObject(GL_TRIANGLES, size/3, g_vertex_buffer_data, colors[c], GL_FILL);

  }

	this->object = obj;
}


void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		for(int i = 0; i < this->color_count ; i++)
    {
			//cout<<"print :"<<i<<"\n";
      draw3DObject(this->object[i]);
    }
}

void Player::updateSpeedX(float x)
{
	this->speed.x += x;
}

void Player::updateSpeedY(float y)
{
	this->speed.y += y;
}

void Player::resetSpeedY()
{
	this->speed.y = 0;
}

float get_absolute_value_o(float a)
{
  if(a<0) return -a;
  else return a;
}


void Player::tick(float friction, float y_limit_bottom)
{
	this->position.x += this->speed.x;

	//cout<<"limit:"<<y_limit_bottom<<endl;
	//cout<<"pos\tx:"<<this->position.x<<"\t"<<"y:"<<this->position.y<<endl;
	//cout<<"added:"<<this->position.y + this->speed.y<<endl;
	if((float)(this->position.y + this->speed.y ) <= y_limit_bottom )
	{
		//cout<<"limited"<<endl;
		if(this->speed.y < - 0.1)
			this->speed.y = -this->speed.y/3;
		this->position.y = y_limit_bottom;

	}
	else this->position.y += this->speed.y;
  //
	// if(this->position.y <= 1.25)
	// {
	// 	this->position.y = 1.25;
	// 	//if(this->speed.y < 0) this->speed.y = -0.1*this->speed.y;
	// 	//else
	// 	this->speed.y = 0;
	// }

	this->rotation -= 10*this->speed.x;

	//cout<<get_absolute_value_o(this->speed.x) - friction<<endl;
	// if(get_absolute_value_o(this->speed.x) - friction > 0)
	// 	this->speed.x -= friction;

	if(this->speed.x > 0)
	{
		if(this->speed.x - friction < 0) this->speed.x =0;
		else	this->speed.x -= friction;
	}
	else
	{
		if(this->speed.x + friction > 0) this->speed.x =0;
		else	this->speed.x += friction;
	}

	//cout<<this->speed.x<<"\t"<<this->speed.y<<endl;

}

void Player::moveLeft(float value){
	this->speed.x = -value;
	this->position.x -= value;
	this->rotation += 10*value;
}


void Player::moveRight(float value){
	this->speed.x = value;
	this->position.x += value;
	this->rotation -= 10*value;
}

void Player::jump(float value){
	this->speed.y = value;
	this->position.y += value;
}

void Player::gravity(float value, float limit){
	if(this->position.y + this->radius < limit) return;
	this->position.y -= value;
}
