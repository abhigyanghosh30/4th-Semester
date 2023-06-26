#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(0,0,0);
    this->speed = 0;
    this->yaw = this->pitch = this->roll = 0.0f;
    static GLfloat vertex_buffer_data[3200];
    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i] = 0.5*(cos(2*M_PI*i/100));;
		vertex_buffer_data[18*i+1] = 0.5*(sin(2*M_PI*i/100));;
		vertex_buffer_data[18*i+2] = 0.0f;
		vertex_buffer_data[18*i+3] = 0.5*(cos(2*M_PI*i/100));
		vertex_buffer_data[18*i+4] = 0.5*(sin(2*M_PI*i/100));
		vertex_buffer_data[18*i+5] = 1.0f;
		vertex_buffer_data[18*i+6] = 0.5*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+7] = 0.5*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+8] = 1.0f;

        vertex_buffer_data[18*i+9] = 0.5*(cos(2*M_PI*(i+1)/100));;
		vertex_buffer_data[18*i+10] = 0.5*(sin(2*M_PI*(i+1)/100));;
		vertex_buffer_data[18*i+11] = 1.0f;
		vertex_buffer_data[18*i+12] = 0.5*(cos(2*M_PI*i/100));
		vertex_buffer_data[18*i+13] = 0.5*(sin(2*M_PI*i/100));
		vertex_buffer_data[18*i+14] = 0.0f;
		vertex_buffer_data[18*i+15] = 0.5*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+16] = 0.5*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[18*i+17] = 0.0f;
    }
    for(int i=0;i<100;i++){
        vertex_buffer_data[1800+9*i] = 0.0f;
		vertex_buffer_data[1800+9*i+1] = 0.0f;
		vertex_buffer_data[1800+9*i+2] = 2.0f;
		vertex_buffer_data[1800+9*i+3] = 0.5*(cos(2*M_PI*i/100));
		vertex_buffer_data[1800+9*i+4] = 0.5*(sin(2*M_PI*i/100));
		vertex_buffer_data[1800+9*i+5] = 1.0f;
		vertex_buffer_data[1800+9*i+6] = 0.5*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[1800+9*i+7] = 0.5*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[1800+9*i+8] = 1.0f;
    }
    static GLfloat vertex_buffer_tail[]={
        //Tail
        0.0f,0.5f,0.5f,
        0.0f,0.5f,0.0f,
        0.0f,1.0f,0.0f,
        //Wing right
        0.5f,0.0f,0.0f,
        1.5f,0.0f,0.0f,
        0.5f,0.0f,0.5f,
        //Wing left
        -0.5f,0.0f,0.0f,
        -1.5f,0.0f,0.0f,
        -0.5f,0.0f,0.5f,
    };
    this->object = create3DObject(GL_TRIANGLES, 300*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->tail = create3DObject(GL_TRIANGLES, 3*3,vertex_buffer_tail,COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_roll  = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate_pitch = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_yaw   = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate_roll          = rotate_roll * glm::translate(glm::vec3(this->position.x, this->position.y, this->position.z));
    // rotate_pitch          = rotate_pitch * glm::translate(glm::vec3(this->position.x, this->position.y, this->position.z));
    // rotate_yaw          = rotate_yaw * glm::translate(glm::vec3(this->position.x, this->position.y, this->position.z));
    Matrices.model *= ( translate * rotate_yaw * rotate_pitch *  rotate_roll );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->tail);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x,y,z);
    if(x>=500)
        this->position.x = 500;
    if(z>=500) 
        this->position.z = 500;
    if(x<=-500)
        this->position.x = -500;
    if(z<=-500) 
        this->position.z = -500;
}

void Ball::tick() {
    this->velocity.x = this->speed * sin(this->yaw * M_PI / 180.0f);
    this->velocity.z = this->speed * cos(this->yaw * M_PI / 180.0f);
    this->position += this->velocity;
    if(this->position.x>=500)
        this->position.x=500;
    if(this->position.x<=-500)
        this->position.x=-500;
    if(this->position.z>=500)
        this->position.z=500;
    if(this->position.z<=-500)
        this->position.z=-500;
}

