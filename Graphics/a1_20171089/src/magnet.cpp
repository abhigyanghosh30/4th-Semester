#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x,y,0);
	static GLfloat vertex_buffer_data[]={
        -1.0f,1.0f,0.0f,//A
        -0.8f,1.0f,0.0f,//E
        -1.0f,-0.8f,0.0f,//K

        -0.8f,1.0f,0.0f,//E
        -1.0f,-0.8f,0.0f,//K
        -0.8f,-1.0f,0.0f,//L

        -0.8f,-1.0f,0.0f,//L
        -0.8f,-0.6f,0.0f,//F
        -0.6f,-0.8f,0.0f,//G

        -0.8f,-1.0f,0.0f,//L
        -0.6f,-0.8f,0.0f,//G
        0.6f,-0.8f,0.0f,//H

        -0.8f,-1.0f,0.0f,//L
        0.6f,-0.8f,0.0f,//H
        0.8f,-1.0f,0.0f,//M

        0.6f,-0.8f,0.0f,//H
        0.8f,-1.0f,0.0f,//M
        0.8f,-0.6f,0.0f,//I

        0.8f,-1.0f,0.0f,//M
        1.0f,-0.8f,0.0f,//N
        0.8f,1.0f,0.0f,//J

        1.0f,-0.8f,0.0f,//N
        0.8f,1.0f,0.0f,//J
        1.0f,1.0f,0.0f,//D

    };   
    this->object = create3DObject(GL_TRIANGLES,8*3, vertex_buffer_data, COLOR_RED,GL_FILL);
    this->display = false;
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x,y,0);
    if(x >= 43) {
        this->position.x = 42.5;
    }
    if(x <= -43) {
        this->position.x = -42.5;
    }
    if(x <= -42 || x >= 42){
        this->display = false;
    }
    // std::cout<<this->position.x<<std::endl;
}