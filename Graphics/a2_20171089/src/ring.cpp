#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->completed = false;
    static GLfloat vertex_buffer_data[1800];
    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i] = 10.0f*(cos(2 * M_PI*i/100));
        vertex_buffer_data[18*i+1] = 10.0f*(sin(2 * M_PI*i/100));
        vertex_buffer_data[18*i+2] = 0.0f;
        vertex_buffer_data[18*i+3] = 9.0f*(cos(2 * M_PI*i/100));
        vertex_buffer_data[18*i+4] = 9.0f*(sin(2 * M_PI*i/100));
        vertex_buffer_data[18*i+5] = 0.0f;
        vertex_buffer_data[18*i+6] = 10.0f*(cos(2 * M_PI*(i+1)/100));
        vertex_buffer_data[18*i+7] = 10.0f*(sin(2 * M_PI*(i+1)/100));
        vertex_buffer_data[18*i+8] = 0.0f;
        vertex_buffer_data[18*i+9] = 9.0f*(cos(2 * M_PI*i/100));
        vertex_buffer_data[18*i+10] = 9.0f*(sin(2 * M_PI*i/100));
        vertex_buffer_data[18*i+11] = 0.0f;
        vertex_buffer_data[18*i+12] = 9.0f*(cos(2 * M_PI*(i+1)/100));
        vertex_buffer_data[18*i+13] = 9.0f*(sin(2 * M_PI*(i+1)/100));
        vertex_buffer_data[18*i+14] = 0.0f;
        vertex_buffer_data[18*i+15] = 10.0f*(cos(2 * M_PI*(i+1)/100));
        vertex_buffer_data[18*i+16] = 10.0f*(sin(2 * M_PI*(i+1)/100));
        vertex_buffer_data[18*i+17] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data, COLOR_GREEN,GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}