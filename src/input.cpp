#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
// void mouseButton(GLFWwindow *window, int button, int action, int mods) {
//       //cout<<button<<"\t"<<action<<"\t"<<mods<<endl;
//     static double past_xpos, past_ypos;
//     static double curr_xpos=0, curr_ypos=0;
//
//     switch (button) {
//     case GLFW_MOUSE_BUTTON_LEFT:
//
//         if (action == GLFW_PRESS) {
//           glfwGetCursorPos(window, &past_xpos, &past_ypos);
//           past_xpos /= 600;
//           past_ypos /= 600;
//
//         } else if (action == GLFW_RELEASE) {
//             // Do something
//             glfwGetCursorPos(window, &curr_xpos, &curr_ypos);
//             curr_xpos /= 600;
//             curr_ypos /= 600;
//
//             player.speed.x += (curr_xpos - past_xpos);
//             player.speed.y += (curr_ypos - past_ypos);
//             //reset_screen();
//         }
//         break;
//     // case GLFW_MOUSE_BUTTON_RIGHT:
//     // if (action == GLFW_RELEASE) {
//     // rectangle_rot_dir *= -1;
//     // }
//     // break;
//     default:
//         break;
//     }
// }

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    //if(yoffset)
    //{
      //if(screen_zoom > yoffset/10 )
      if(screen_zoom > 0.1)reset_screen();
      {
        screen_zoom += yoffset/10;
        reset_screen();
      }

    //}
}
