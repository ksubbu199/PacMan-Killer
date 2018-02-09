#include "main.h"
#include "generator.h"

static Generator generator = Generator();

static void helper_draw(glm::mat4 VP,glm::vec3 translation,float rotation, VAO* object ) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (translation);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object);
}
