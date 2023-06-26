#include "bar.h"
#include "main.h"

Bar::Bar(float x, float y, float z, float score, color_t color){
    this->position=glm::vec3(x,y,z);
    GLfloat vertex_buffer_data[] = {
        -2.0f,0.2f,0.0f,
        -2.0,-0.2f,0.0f,
        score/100,0.2f,0.0f,

        score/100,0.2f,0.0f,
        score/100,-0.2f,0.0f,
        -2.0f,-0.2f,0.0f,
    };
    this->yaw = 0;
    this->colour = color;
    this->object = create3DObject(GL_TRIANGLES,2*3,vertex_buffer_data,color,GL_FILL);
}

void Bar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 rotate_yaw = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate_yaw);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bar::set_score(float score){
    GLfloat vertex_buffer_data[] = {
        -1.0f,0.2f,0.0f,
        -1.0,-0.2f,0.0f,
        score/10,0.2f,0.0f,

        score/10,0.2f,0.0f,
        score/10,-0.2f,0.0f,
        -1.0f,-0.2f,0.0f,
    };
    // std::cout<<score<<std::endl;
    this->object = create3DObject(GL_TRIANGLES,2*3,vertex_buffer_data,this->colour,GL_FILL);
}

void Bar::set_position(float x, float y, float z) {
    this->position = glm::vec3(x,y,z);
}