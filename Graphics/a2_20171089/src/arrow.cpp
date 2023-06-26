#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x,y,z);
    this->yaw = 0;
    this->pitch = 0;
    static GLfloat vertex_buffer_data[] = {
        0.25f,0.0f,0.0f,
        -0.25f,0.0f,0.0f,
        0.0f,0.0f,1.0f,
    };
    this->object = create3DObject(GL_TRIANGLES,3,vertex_buffer_data,COLOR_YELLOW,GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_yaw   = glm::rotate((float) (this->yaw), glm::vec3(0, 1, 0));
    glm::mat4 rotate_pitch   = glm::rotate((float) (this->pitch*M_PI_2), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate *  rotate_yaw * rotate_pitch);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::tick(float yaw, float pitch, float x, float y, float z){
    this->yaw = yaw;
    this->pitch = pitch;
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}