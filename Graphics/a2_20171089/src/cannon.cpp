#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float z) {
    this->position = glm::vec3(x,-9,z);
    this->yaw = 1.7;
    this->pitch = 1.7;
    static GLfloat vertex_buffer_data[3200];
    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i] = 2.5*(cos(2*M_PI*i/100));;
		vertex_buffer_data[18*i+1] = 2.5*(sin(2*M_PI*i/100));;
		vertex_buffer_data[18*i+2] = 0.0f;
		vertex_buffer_data[18*i+3] = 2.5*(cos(2*M_PI*i/100));
		vertex_buffer_data[18*i+4] = 2.5*(sin(2*M_PI*i/100));
		vertex_buffer_data[18*i+5] = 10.0f;
		vertex_buffer_data[18*i+6] = 2.5*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+7] = 2.5*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+8] = 10.0f;

        vertex_buffer_data[18*i+9] = 2.5*(cos(2*M_PI*(i+1)/100));;
		vertex_buffer_data[18*i+10] = 2.5*(sin(2*M_PI*(i+1)/100));;
		vertex_buffer_data[18*i+11] = 10.0f;
		vertex_buffer_data[18*i+12] = 2.5*(cos(2*M_PI*i/100));
		vertex_buffer_data[18*i+13] = 2.5*(sin(2*M_PI*i/100));
		vertex_buffer_data[18*i+14] = 0.0f;
		vertex_buffer_data[18*i+15] = 2.5*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+16] = 2.5*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+17] = 0.0f;
    }
    for(int i=0;i<100;i++){
        vertex_buffer_data[1800+9*i] = 0.0f;
		vertex_buffer_data[1800+9*i+1] = 0.0f;
		vertex_buffer_data[1800+9*i+2] = 1.0f;
		vertex_buffer_data[1800+9*i+3] = 2.5*(cos(2*M_PI*i/100));
		vertex_buffer_data[1800+9*i+4] = 2.5*(sin(2*M_PI*i/100));
		vertex_buffer_data[1800+9*i+5] = 0.5f;
		vertex_buffer_data[1800+9*i+6] = 2.5*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[1800+9*i+7] = 2.5*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[1800+9*i+8] = 0.5f;
    }
    this->object = create3DObject(GL_TRIANGLES,300*3,vertex_buffer_data,COLOR_GREEN,GL_FILL);

    // static GLfloat vertex_buffer_data[] = {
    //     3.0f,0.0f,0.0f,
    //     -3.0f,0.0f,0.0f,
    //     0.0f,0.0f,20.0f,
    // };
    // this->object = create3DObject(GL_TRIANGLES,3,vertex_buffer_data,COLOR_RED,GL_FILL);

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_yaw   = glm::rotate((float) (this->yaw), glm::vec3(0, 1, 0));
    glm::mat4 rotate_pitch   = glm::rotate((float) (this->pitch), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate *  rotate_yaw * rotate_pitch);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::tick(float yaw, float pitch){
    this->yaw = yaw;
    this->pitch = pitch;   
}