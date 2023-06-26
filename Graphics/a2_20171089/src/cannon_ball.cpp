#include "cannon_ball.h"
#include "main.h"

CannonBall::CannonBall(float x, float z, float yaw) {
    this->position = glm::vec3(x,-10,z);
    this->yaw = yaw;
    this->speed = glm::vec3(0,3,0);
    static GLfloat vertex_buffer_data[3200];
    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i] = 0.25*(cos(2*M_PI*i/100));;
		vertex_buffer_data[18*i+1] = 0.25*(sin(2*M_PI*i/100));;
		vertex_buffer_data[18*i+2] = 0.0f;
		vertex_buffer_data[18*i+3] = 0.25*(cos(2*M_PI*i/100));
		vertex_buffer_data[18*i+4] = 0.25*(sin(2*M_PI*i/100));
		vertex_buffer_data[18*i+5] = 0.5f;
		vertex_buffer_data[18*i+6] = 0.25*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+7] = 0.25*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+8] = 0.5f;

        vertex_buffer_data[18*i+9] = 0.25*(cos(2*M_PI*(i+1)/100));;
		vertex_buffer_data[18*i+10] = 0.25*(sin(2*M_PI*(i+1)/100));;
		vertex_buffer_data[18*i+11] = 0.5f;
		vertex_buffer_data[18*i+12] = 0.25*(cos(2*M_PI*i/100));
		vertex_buffer_data[18*i+13] = 0.25*(sin(2*M_PI*i/100));
		vertex_buffer_data[18*i+14] = 0.0f;
		vertex_buffer_data[18*i+15] = 0.25*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+16] = 0.25*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+17] = 0.0f;
    }
    for(int i=0;i<100;i++){
        vertex_buffer_data[1800+9*i] = 0.0f;
		vertex_buffer_data[1800+9*i+1] = 0.0f;
		vertex_buffer_data[1800+9*i+2] = 1.0f;
		vertex_buffer_data[1800+9*i+3] = 0.25*(cos(2*M_PI*i/100));
		vertex_buffer_data[1800+9*i+4] = 0.25*(sin(2*M_PI*i/100));
		vertex_buffer_data[1800+9*i+5] = 0.5f;
		vertex_buffer_data[1800+9*i+6] = 0.25*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[1800+9*i+7] = 0.25*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[1800+9*i+8] = 0.5f;
    }
    this->object = create3DObject(GL_TRIANGLES,300*3,vertex_buffer_data,COLOR_GREEN,GL_FILL);
}

void CannonBall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_yaw   = glm::rotate((float) (this->yaw), glm::vec3(0, 1, 0));
    Matrices.model *= (translate *  rotate_yaw );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void CannonBall::tick() {
    this->speed.y -= 0.08;
    this->speed.x = 1.0f * sin(this->yaw);
    this->speed.z = 1.0f * cos(this->yaw);

    this->position += this->speed;
	// std::cout<<this->position.x<<","<<this->position.y<<","<<this->position.z<<std::endl;
}