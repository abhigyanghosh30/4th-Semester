#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    static const GLfloat vertex_buffer_data[] = {
        0.0f,0.0f,0.5f,//D
        0.5f,0.0f,0.0f,//E
        0.0f,0.5f,0.0f,//C  

        0.0f,0.0f,0.5f,//D
        0.5f,0.0f,0.0f,//E
        0.0f,-0.5f,0.0f,//B

        0.0f,0.0f,0.5f,//D
        0.0f,-0.5f,0.0f,//B
        -1.0f,0.0f,0.0f,//A
   
        0.0f,0.0f,0.5f,//D
        -1.0f,0.0f,0.0f,//A
        0.0f,0.5f,0.0f,//C  
    };
    this->object = create3DObject(GL_TRIANGLES,4*3,vertex_buffer_data,COLOR_RED,GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::tick(){
    this->position.y -= 0.5f;
}