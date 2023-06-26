#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y){
    this->position = glm::vec3(42, 10, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.5f,0.5f,0.0f, // triangle 1 : begin
        -0.5f,-0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, // triangle 1 : end
        0.5f, 0.5f, 0.0f, // triangle 2 : begin
        0.5f,-0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f, // triangle 2 : end
    };
    this->xspeed = -0.9;
    this->yspeed = 0;
    this->display = true;
    this->box = {42,10,1,1};
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BROWN, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->box = {x,y,1,1};
    
}

void Boomerang::tick(){
    this->yspeed -= 0.001;
    this->xspeed += 0.009;
    this->position.x += this->xspeed;
    this->position.y += this->yspeed;
    this->box = {this->position.x,this->position.y,1,1};
    // std::cout<<this->position.x<<std::endl;
    if(this->position.y <= -4){
        this->display = false;
        this->position.y=-4;
    }
    if(this->position.x >= 42){
        this->display = false;
        this->position.x = 41;
    }

}