#include "circle.h"
#include "main.h"

Circle::Circle(float x){
    this->position = glm::vec3(x,0,0);
    this->display = true;
    static GLfloat vertex_buffer_data[1800];
    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i] = 10.0f*(cos(M_PI*i/100));
        vertex_buffer_data[18*i+1] = 10.0f*(sin(M_PI*i/100));
        vertex_buffer_data[18*i+2] = 0.0f;
        vertex_buffer_data[18*i+3] = 9.0f*(cos(M_PI*i/100));
        vertex_buffer_data[18*i+4] = 9.0f*(sin(M_PI*i/100));
        vertex_buffer_data[18*i+5] = 0.0f;
        vertex_buffer_data[18*i+6] = 10.0f*(cos(M_PI*(i+1)/100));
        vertex_buffer_data[18*i+7] = 10.0f*(sin(M_PI*(i+1)/100));
        vertex_buffer_data[18*i+8] = 0.0f;
        vertex_buffer_data[18*i+9] = 9.0f*(cos(M_PI*i/100));
        vertex_buffer_data[18*i+10] = 9.0f*(sin(M_PI*i/100));
        vertex_buffer_data[18*i+11] = 0.0f;
        vertex_buffer_data[18*i+12] = 9.0f*(cos(M_PI*(i+1)/100));
        vertex_buffer_data[18*i+13] = 9.0f*(sin(M_PI*(i+1)/100));
        vertex_buffer_data[18*i+14] = 0.0f;
        vertex_buffer_data[18*i+15] = 10.0f*(cos(M_PI*(i+1)/100));
        vertex_buffer_data[18*i+16] = 10.0f*(sin(M_PI*(i+1)/100));
        vertex_buffer_data[18*i+17] = 0.0f;
    } 

    this->object = create3DObject(GL_TRIANGLES, 600, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Circle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Circle::set_position(float x){
    if(x>48) {
        this->position.x = 47;
        this->display=false;
    }
    else if(x<-48){
        this->position.x = -47;
        this->display = false;
    }
    else {
        this->position.x = x;
    }
}