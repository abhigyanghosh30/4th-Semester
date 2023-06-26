#include "barry.h"
#include "main.h"

Barry::Barry(float x, float y) {
    this->position = glm::vec3(x,y,0);
    this->jump = false;
    this->yaccln = -0.01;
    this->xaccln = 0;
    this->countdown = -1;
    static const GLfloat vertex_buffer_data[] = {
        -0.6f,1.0f,0.0f, // triangle 1 : begin
        -0.6f,-1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, // triangle 1 : end
        -0.6f, 1.0f, 0.0f, // triangle 2 : begin
        1.0f,-1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, // triangle 2 : end
        -0.6f,1.0f, 0.0f,
        -1.0f,0.0f, 0.0f,
        -0.6f,0.0f, 0.0f
    };
    static const GLfloat vertex_buffer_data_jet[] = {
        -0.8f, 0.0f, 0.0f,
        -1.0f,-1.0f, 0.0f,
        -0.6f,-1.0f, 0.0f

    };

    this->box = {x,y,2,2};

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->jet = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_jet, COLOR_YELLOW, GL_FILL);
}

void Barry::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, -0.6));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    static const GLfloat vertex_buffer_data[] = {
        -0.6f,1.0f,0.0f, // triangle 1 : begin
        -0.6f,-1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, // triangle 1 : end
        -0.6f, 1.0f, 0.0f, // triangle 2 : begin
        1.0f,-1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, // triangle 2 : end
        -0.6f,1.0f, 0.0f,
        -1.0f,0.0f, 0.0f,
        -0.6f,0.0f, 0.0f
    };
    if(this->countdown > 0)
        this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_SILVER, GL_FILL);
    else
        this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);

    draw3DObject(this->object);
    if(this->jump) {
        draw3DObject(this->jet);
    }
}

void Barry::set_position(float x, float y) {
    this->position = glm::vec3(x,y,0);
    this->box = {x,y,2,2};
    // std::cout<<this->position.x<<std::endl;
}

void Barry::tick() {
    // this->rotation += speed;
    this->yspeed += this->yaccln;
    this->xspeed += this->xaccln;
    this->position.x += this->xspeed;
    this->position.y += this->yspeed;

    if( this->position.y < -2 ) {
        this->position.y=-2;
        this->yspeed = 0;
    }
    if(this->position.y > 10) {
        this->position.y = 10;
        this->yspeed = 0;        
    }
    if(this->position.x > 41) {
        this->position.x = 41;
    }
    if(this->position.x < -41) {
        this->position.x = -41;
    }
    if(this->yspeed <= 0) { 
        this->jump=false;
    }
    if(this->countdown >= 0) {
        this->countdown--;
    }
}