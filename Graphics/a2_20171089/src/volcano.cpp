#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float z) {
    this->position = glm::vec3(x, -10, z);
    static GLfloat vertex_buffer_data[1800];
    for(int i=0;i<100;i++) {
        vertex_buffer_data[18*i] = 10 * cos(2*M_PI*i/100);
        vertex_buffer_data[18*i+1] = 0.0f;
        vertex_buffer_data[18*i+2] = 10 * sin(2*M_PI*i/100);
        
        vertex_buffer_data[18*i+3] = 10 * cos(2*M_PI*(i+1)/100);
        vertex_buffer_data[18*i+4] = 0.0f;
        vertex_buffer_data[18*i+5] = 10 * sin(2*M_PI*(i+1)/100);
        
        vertex_buffer_data[18*i+6] = 5 * cos(2*M_PI*i/100);
        vertex_buffer_data[18*i+7] = 10.0f;
        vertex_buffer_data[18*i+8] = 5 * sin(2*M_PI*i/100);
        
        vertex_buffer_data[18*i+9] = 5 * cos(2*M_PI*i/100);
        vertex_buffer_data[18*i+10] = 10.0f;
        vertex_buffer_data[18*i+11] = 5 * sin(2*M_PI*i/100);
        
        vertex_buffer_data[18*i+12] = 5 * cos(2*M_PI*(i+1)/100);
        vertex_buffer_data[18*i+13] = 10.0f;
        vertex_buffer_data[18*i+14] = 5 * sin(2*M_PI*(i+1)/100);
        
        vertex_buffer_data[18*i+15] = 10 * cos(2*M_PI*(i+1)/100);
        vertex_buffer_data[18*i+16] = 0.0f;
        vertex_buffer_data[18*i+17] = 10 * sin(2*M_PI*(i+1)/100);

    }
    static GLfloat vertex_buffer_lava[900];
    for(int i=0;i<100;i++) {
        vertex_buffer_lava[9*i] = 5 * cos(2*M_PI*i/100);
        vertex_buffer_lava[9*i+1] = 10.0f;
        vertex_buffer_lava[9*i+2] = 5 * sin(2*M_PI*i/100);
        vertex_buffer_lava[9*i+3] = 5 * cos(2*M_PI*(i+1)/100);
        vertex_buffer_lava[9*i+4] = 10.0f;
        vertex_buffer_lava[9*i+5] = 5 * sin(2*M_PI*(i+1)/100);
        vertex_buffer_lava[9*i+6] = 0.0f;
        vertex_buffer_lava[9*i+7] = 10.0f;
        vertex_buffer_lava[9*i+8] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data,COLOR_BLACK,GL_FILL);
    this->lava = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_lava,COLOR_LAVAYELLOW,GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->lava);
}