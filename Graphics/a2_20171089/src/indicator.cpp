#include "indicator.h"
#include "main.h"

Indicator::Indicator(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    static GLfloat vertex_buffer_data[1000];
    for(int i =0;i<100;i++){
        vertex_buffer_data[9*i] = 5.0 * cos(2*M_PI*i/100);
        vertex_buffer_data[9*i+1] = 10.0f;
        vertex_buffer_data[9*i+2] = 5.0 * sin(2*M_PI*i/100);
        vertex_buffer_data[9*i+3] = 5.0 * cos(2*M_PI*(i+1)/100);
        vertex_buffer_data[9*i+4] = 10.0f;
        vertex_buffer_data[9*i+5] = 5.0 * sin(2*M_PI*(i+1)/100);
        vertex_buffer_data[9*i+6] = 0.0f;
        vertex_buffer_data[9*i+7] = 0.0f;
        vertex_buffer_data[9*i+8] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Indicator::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Indicator::set_position(float x, float y, float z){
    this->position = glm::vec3(x,y,z);
}