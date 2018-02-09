#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "spikes.h"
#include "pond.h"
#include "player.h"
#include "magnet.h"
#include "trampoline.h"
#include "sevensegment.h"

#include "basic_func.h"

#include <cmath>
#include <unistd.h>
#include <string.h>
#include <sstream>

#define PI 3.14159265
#define clear() printf("\033[H\033[J")

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Sevensegment sevensegment;
int ballCount = 30;
int spikesCount = 2;
float g=0.2;
float t=0;
float regernation_x_limit;
int score=0;
int level=1;
int lives=3;
//Ball d_ball;
Ball* balls;
Ground ground;
Magnet magnet;
//Spikes spikes1, spikes2;
Spikes* spikes;
Pond pond;
Player player;
Trampoline trampoline;
float left_most;
float friction_ground = 0.02;

float friction_air = 0.005;

float top_s, bottom_s, left_s, right_s;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 20);

void debug();
float get_y_limit();
void print_stuff();
void draw_score(glm::mat4 VP);
void draw_lives(glm::mat4 VP);
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

  //  glViewport((GLint) -30, (GLint) -30, 600, 600);
    // Scene render
    if(magnet.isOn)
      magnet.draw(VP);
    ground.draw(VP);
    for(int i = 0; i < spikesCount; i++)
    {
      if(spikes[i].isOn)
        spikes[i].draw(VP);
    }

    pond.draw(VP);
    trampoline.draw(VP);
    for(int i = 0; i < ballCount; i++)
    {
      if(balls[i].isScored) continue;

      balls[i].draw(VP);
    }

    player.draw(VP);

    //sevensegment.draw(VP);
    draw_score(VP);
    draw_lives(VP);
}




void draw_score(glm::mat4 VP)
{
    //std::string s = std::to_string(score);
    //char const *pchar = s.c_str();
    //char* pchar[((sizeof score)+ 2)/3 + 2];
    //sprintf(pchar, "%d", score);
    char pchar[6];
    //itoa(score, pchar,10);
    //char myString[128];
    snprintf(pchar, sizeof(pchar), "%d", score);
    cout<<pchar<<endl;
    int len = strlen(pchar);
    float x=right_s -2, y=bottom_s + 1;
    Sevensegment s = Sevensegment(pchar[0],x,y);
    for(int i=0;i<len;i++)
    {
      s.set_position(x,y);
      s.set_letter(pchar[i]);
      s.draw(VP);
      x+=0.7;
    }
}

void draw_lives(glm::mat4 VP)
{
    //std::string s = std::to_string(score);
    //char const *pchar = s.c_str();
    //char* pchar[((sizeof score)+ 2)/3 + 2];
    //sprintf(pchar, "%d", score);
    char pchar[6];
    //itoa(score, pchar,10);
    //char myString[128];
    snprintf(pchar, sizeof(pchar), "%d", lives);
    cout<<pchar<<endl;
    int len = strlen(pchar);
    float x=left_s +1, y=bottom_s + 1;
    Sevensegment s = Sevensegment(pchar[0],x,y);
    for(int i=0;i<len;i++)
    {
      s.set_position(x,y);
      s.set_letter(pchar[i]);
      s.draw(VP);
      x+=0.7;
    }
}

void fixed_magnet()
{
  if(magnet.isOn)
  {
    if(magnet.isOnLeft)
    {
      magnet.position.x = left_s + 1;
      magnet.position.y = bottom_s + 6;
    }
    else
    {
      magnet.position.x = right_s - 1;
      magnet.position.y = bottom_s + 6;
    }
  }
}

// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
//     // Do something
//     cout<<xoffset<<"\t"<<yoffset<<endl;
// }

void upgrade_spikes(int i)
{
  //sleep(1);
  spikes[0] = Spikes(get_random_integer(1 + i,4 + i), left_s + 1, 1, get_random_integer(5,10),  COLOR_PURE_RED );
  spikes[1] = Spikes(get_random_integer(1 + i,4 + i), right_s - 2, 1, get_random_integer(5,10),  COLOR_PURE_RED );
}

void manage_spikes_position()
{
  if(spikes==NULL) return;
  spikes[0].set_position((glm::vec3){left_s + 1, 1 , 0});
  spikes[1].set_position((glm::vec3){right_s - 2, 1 , 0});
}

void reset_screen() {
    top_s    = screen_center_y + 6 / screen_zoom;
    bottom_s = screen_center_y - 2 / screen_zoom;
    left_s   = screen_center_x - 4 / screen_zoom;
    right_s  = screen_center_x + 4 / screen_zoom;
    if(left_s <= -5) return;
    Matrices.projection = glm::ortho(left_s, right_s, bottom_s, top_s, 0.1f, 500.0f);
    regernation_x_limit =  right_s + 5;
    fixed_magnet();
    if(spikes==NULL) return;
    if(screen_center_x - spikes[1].position.x > 2 || screen_center_x - spikes[0].position.x < -2 )
      manage_spikes_position();

}



bool shall_we_have_slab()
{
  return get_random_integer(0,5)==0;
}


bool is_player_on_trampoline()
{
  if(get_absolute_value(player.position.x - trampoline.position.x) <=trampoline.width &&
     player.position.y == trampoline.position.y + player.radius)
     return true;
  else return false;
}

bool is_player_in_pond()
{
  if(player.position.y -player.radius <= pond.position.y && get_absolute_value(pond.position.x - player.position.x) < pond.radius)  return true;
  else return false;
}

bool is_player_on_ground(){
    if(!is_player_in_pond())
    {
      if(player.position.y-player.radius <= 1.25)
        return true;
      else return false;
    }
    else
    {
      if(get_y_limit()==player.position.y)
        return true;
      else
        return false;
    }
}

void update_level()
{
  if(score / 300 >= level)
  {
    level++;
    upgrade_spikes(level);
  }
}

void p1(double x,double y)
{
  cout<<"("<<x<<","<<y<<")"<<endl;
}
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    static double past_xpos, past_ypos;
    static double curr_xpos=0, curr_ypos=0;
    float speedx=0.25,speedy=0.2;
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:

        if (action == GLFW_PRESS) {
          glfwGetCursorPos(window, &past_xpos, &past_ypos);
          past_xpos /= 600;
          past_ypos /= 600;

        } else if (action == GLFW_RELEASE) {
            // Do something
            glfwGetCursorPos(window, &curr_xpos, &curr_ypos);
            curr_xpos /= 600;
            curr_ypos /= 600;
            p1(past_xpos,past_ypos);
            p1(curr_xpos,curr_ypos);
            p1(curr_xpos - past_xpos, curr_ypos - past_ypos);

            if(curr_xpos - past_xpos < 0) speedx *= -1;
            if(curr_ypos - past_ypos > 0) speedy *= -1;

            if(curr_xpos != past_xpos)
              player.speed.x += speedx;
            if(curr_ypos != past_ypos)
              player.speed.y += speedy;
            //reset_screen();
        }
        break;
    default:
        break;
    }
}


void tick_input(GLFWwindow *window) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    int up  = glfwGetKey(window, GLFW_KEY_SPACE);
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);

    int zoom = glfwGetKey(window, GLFW_KEY_Z);
    int zoomout = glfwGetKey(window, GLFW_KEY_C);
    int panleft = glfwGetKey(window, GLFW_KEY_LEFT);
    int panright = glfwGetKey(window, GLFW_KEY_RIGHT);

    int panup = glfwGetKey(window, GLFW_KEY_UP);
    int pandown = glfwGetKey(window, GLFW_KEY_DOWN);

    if(panleft)
    {
      screen_center_x -= 0.1;
      reset_screen();
    }

    if(panright)
    {
      screen_center_x += 0.1;
      reset_screen();
    }
    if(panup)
    {
      screen_center_y += 0.1;
      reset_screen();
    }

    if(pandown)
    {
      screen_center_y -= 0.1;
      reset_screen();
    }

    if(zoomout)
    {
      if(screen_zoom > 0.1)
      {
        screen_zoom -= 0.1;
        reset_screen();
      }
    }
    if(zoom)
    {
      screen_zoom += 0.1;
      reset_screen();
    }

    int x = glfwGetKey(window, GLFW_KEY_X);

    if(x) debug();

    float up_speed = 0.15;
    float side_speed = 0.03;
    if(is_player_on_trampoline())
    {
      up_speed = 0.5;
    }
    if(is_player_in_pond())
    {
      up_speed = 0.2;
      side_speed = 0.015;
      //cout<<"in pond"<<endl;
    }
    else
    {
      //cout<<"on ground"<<endl;
    }

    if(left){
      //player.moveLeft(side_speed);
      player.updateSpeedX(-side_speed);
    }

    if(right){
      player.updateSpeedX(side_speed);
    }

    if(up&&(is_player_on_ground() || is_player_on_trampoline())){
      //cout<<"up_speed:"<<up_speed<<endl;
      player.updateSpeedY(up_speed);
    }

}

void toggle_spike(int i)
{

  float timer = spikes[i].timer;

  float timer_limit = spikes[i].time_limit;
  //cout<<"spike "<<i<<"  "<<timer<<endl;
  timer += 1.0/20.0;
  spikes[i].timer = timer;
  //cout<<timer<<endl;
  if(timer > timer_limit)
  {
    if(spikes[i].isOn)
    {
      spikes[i].isOn = false;
      timer_limit = spikes[i].time_limit;
    }
    else
    {
      spikes[i].isOn= true;
      timer_limit = spikes[i].time_limit;
    }
    spikes[i].timer = 0;
  }
}

void move_spike(int i)
{
  if(spikes[i].isOn)
  {
    if(spikes[i].movingRight)
        spikes[i].position.x += 0.01;
    else
      spikes[i].position.x -= 0.01;
    if(get_absolute_value(spikes[i].spawn_position.x - spikes[i].position.x) >= 0.5)
    {
      if(spikes[i].movingRight)
        spikes[i].movingRight =  false;
      else
        spikes[i].movingRight = true;
    }
  }

}

void random_spikes()
{
  for(int i=0;i< spikesCount; i++)
  {
    toggle_spike(i);
    move_spike(i);
  }
}

void toggle_magnet()
{
  static float timer=0;
  static float timer_limit = 15;
  timer += 1.0/20.0;
  //cout<<timer<<endl;
  if(timer > timer_limit)
  {
    if(magnet.isOn)
    {
      magnet.isOn = false;
      timer_limit = 10;
    }
    else
    {
      if(magnet.isOnLeft) magnet.isOnLeft=false;
      else magnet.isOnLeft=true;
      magnet.isOn= true;
      timer_limit = 15;
    }
    timer = 0;
  }
}

void manange_magnet()
{
  if(magnet.isOn)
  {
    if(!is_player_on_ground() && !is_player_on_trampoline() && player.position.y >= 1 - player.radius)
    {
      if(magnet.isOnLeft)
        player.speed.x -= 0.01;
      else
        player.speed.x += 0.01;
    }
  }
}

bool are_two_balls_collided(Player ball1, Ball ball2)
{
  float distance = pow(ball1.position.x - ball2.position.x, 2) + pow(ball1.position.y - ball2.position.y, 2) ;
  if(distance >= pow(ball1.radius + ball2.radius,2) ) return false;
  else return true;
}

void update_score(int value)
{
  score += value;
}


void regenerate_ball(int i)
{
    balls[i]=Ball(getRandomBetween(left_s -4, right_s), getRandomBetween(1.7,5), getRandomBetween(0.05,0.3), getRandomBetween(0.02, 0.1), shall_we_have_slab(), COLOR_YELLOW);
    //balls[i]=Ball(4,3,0.5,0,shall_we_have_slab(),COLOR_YELLOW);
}


void reflect_ball(int i)
{
  if(player.speed.y >=0)
    player.updateSpeedY(0.05);
  else
    player.updateSpeedY(0.5);
}

void manage_points(int i)
{
  reflect_ball(i);
  balls[i].isScored = true;
  regenerate_ball(i);
  update_score(10);
}

void detect_waste_balls()
{
  for(int i=0;i<ballCount;i++)
  {
    if(balls[i].position.x > regernation_x_limit)
      regenerate_ball(i);
  }
}

void detect_collision_with_ball(){

  for(int i = 0;i < ballCount; i++)
  {
      if(balls[i].isScored) continue;

      if(are_two_balls_collided(player, balls[i]))
      {
        manage_points(i);
      }
  }

}


void debug()
{
  screen_center_x += (player.position.x - screen_center_x);
  reset_screen();
}

bool is_collided_with_spike(int i)
{
  bounding_box_t bb = spikes[i].get_bounding_box();
  float distance_x = get_absolute_value(bb.x + bb.width/2 - player.position.x);

  bool x_overlapped = distance_x <= (bb.width/2 + player.radius);

  if(x_overlapped)
  {
    if(get_absolute_value(bb.y + bb.width/2 - player.position.y)<=bb.width/2+player.radius) return true;
    else return false;
  }
  else return false;

}

void manage_stripes_collide()
{
  lives--;
  if(!lives){
    clear();
    print_stuff();
    exit(EXIT_SUCCESS);
  }
  update_score(-5);
  player.position.x = 0;
  player.position.y = top_s;
  player.speed.y = 0.1;
  draw();
}

void spike_collision(){

  for(int i=0; i < spikesCount; i++)
  {
      if(!spikes[i].isOn) continue;

      if(is_collided_with_spike(i))
      {
        manage_stripes_collide();
      }
  }
}


float get_y_limit()
{
  if(is_player_in_pond())
  {
    float x_p_sqr = pow(player.position.x-pond.position.x,2);
    float r_sqr = pow(pond.radius - player.radius,2);
    float y_sqr = r_sqr - x_p_sqr;
    if(y_sqr<0)
    {
      return 1.25;
    }
    return pond.position.y - sqrt(get_absolute_value(y_sqr));
  }

  if(get_absolute_value(player.position.x-trampoline.position.x) <=  trampoline.width/2 + player.radius &&
     player.position.y >= trampoline.position.y + player.radius )
  {
    return 1 + trampoline.height + player.radius;
  }

  else return 1.25;
}

void detect_trampoline_collision()
{
  if(get_absolute_value(player.position.x - trampoline.position.x) <= trampoline.width/2  + player.radius &&
     player.position.y < trampoline.position.y + player.radius
      )
  {
    if(player.position.x < trampoline.position.x)
      player.position.x = trampoline.position.x - trampoline.width/2 - player.radius;
    else
      player.position.x = trampoline.position.x + trampoline.width/2 + player.radius;
    player.speed.x *= -1;
  }
}

void x_left_limit()
{
  if(player.position.x - player.radius <= -4)
  {
    player.position.x = -4 + player.radius;
    player.speed.x = get_absolute_value(player.speed.x);
  }
}

bool check_slab_hit(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float R)
{

  float LAB = sqrt(pow(Bx-Ax,2)+pow(By-Ay,2));

  float Dx = (Bx-Ax)/LAB;
  float Dy = (By-Ay)/LAB;
  float dt;

  float t = Dx*(Cx-Ax) + Dy*(Cy-Ay);

  float Ex = t*Dx+Ax;
  float Ey = t*Dy+Ay;

  float LEC = sqrt(pow(Ex-Cx,2)+pow(Ey-Cy,2));

  if( LEC < R )
  {
      dt = sqrt( pow(R,2) - pow(LEC,2));
      if((t-dt <0 && t+dt <0) || (t-dt >1 && t+dt >1))
       return false;
  }
  else if( LEC == R )
    return true;
  else
    return false;
}

void tick_balls()
{
  for(int i=0;i<ballCount; i++)
  {
    balls[i].tick();
    if(balls[i].isScored) continue;
    if(check_slab_hit(balls[i].get_slab_top().x,  balls[i].get_slab_top().y,  balls[i].get_slab_bottom().x, balls[i].get_slab_bottom().y, player.position.x, player.position.y, player.radius))
    {
        player.speed.x = -(player.speed.x*cos(PI/4) + player.speed.y*sin(PI/4));
        player.speed.y = -(player.speed.x*cos(PI/4) + player.speed.y*sin(PI/4));
    }
  }
}

void print_line(const char *line)
{
  int len=strlen(line);
  cout<<"#";

  for(int i=0;i<(58-len)/2 -1;i++)
  cout<<" ";

  for(int i=0;i<len;i++)
    cout<<line[i];

  for(int i=0;i<(58-len)/2 -1;i++)
    cout<<" ";

  if(len%2==1) cout<<" ";
  cout<<"#"<<endl;
}

void print_stuff()
{
  const char *border = "########################################################";
  const char *title = "PacMan - Killer ";
  const char *author = "Author: ksubbu199@gmail.com ";
  const char *score_disp;
  stringstream ss;
  ss<<" Score:"<<score<<"    Lives:"<<lives<<"   Level:"<<level;
  const std::string tmp = ss.str();
  score_disp = tmp.c_str();

  print_line(border);
  print_line(title);
  print_line(author);
  print_line(border);
  print_line(score_disp);
  print_line(border);

}

void update_title()
{
  const char *score_disp;
  stringstream ss;
  ss<<" Score:"<<score<<"    Lives:"<<lives<<"   Level:"<<level;
  const std::string tmp = ss.str();
  score_disp = tmp.c_str();
  glfwSetWindowTitle(window, score_disp);
}

void player_centric()
{
  if(player.position.x - 4 / screen_zoom < left_most) return;

  if(get_absolute_value(player.position.x - screen_center_x) >= 0 )
  {
    screen_center_x = player.position.x;
    reset_screen();
  }
}

void move_player()
{
  if(!is_player_on_ground())
  {
    player.updateSpeedY(-0.02);
    player.tick(friction_air, get_y_limit());
  }
  else
  {
    player.tick(friction_ground, get_y_limit());
  }
}

void tick_elements() {
    print_stuff();
    update_title();
    toggle_magnet();
    reset_screen();
    manange_magnet();
    random_spikes();
    update_level();
    player_centric();
    move_player();
    x_left_limit();
    detect_collision_with_ball();
    spike_collision();
    tick_balls();
    detect_trampoline_collision();
    detect_waste_balls();
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    reset_screen();
    left_most = left_s;
    magnet = Magnet(-3,4,COLOR_RED);
    balls       = (Ball *) malloc(ballCount*sizeof(Ball));
    spikes      = (Spikes *) malloc(spikesCount*sizeof(Spikes));
    //d_ball = Ball(0,0,0.01,0,COLOR_GREEN);
    for(int i = 0; i < ballCount; i++)
    {
      balls[i] = Ball(getRandomBetween(left_s -4,right_s), getRandomBetween(1.7,5), getRandomBetween(0.05,0.3), getRandomBetween(0.02, 0.1), shall_we_have_slab(), COLOR_YELLOW);
      //balls[i]= Ball(4,5,0.5,0, shall_we_have_slab(), COLOR_YELLOW);
    }

    ground      = Ground(-4,bottom_s, 2.75, 0.5, COLOR_GREY, COLOR_GREEN);
    sevensegment = Sevensegment('0', 0, 0);

    spikes[0] = Spikes(get_random_integer(1,5), left_s + 1, 1, get_random_integer(5,10),  COLOR_PURE_RED );
    spikes[1] = Spikes(get_random_integer(1,5), right_s - 2, 1, get_random_integer(5,10),  COLOR_PURE_RED );


    pond        = Pond(0,1,COLOR_BLUE);
    player      = Player(-2, 1);
    trampoline  = Trampoline(3.5, 1+0.5, 0.5, 0.5, COLOR_RED);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    //glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);draw();

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            clear();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            draw();
            tick_input(window);
            tick_elements();


        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}
