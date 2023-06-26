#include "ssd.h"
#include "main.h"

SSD::SSD(float place,int num){
    this->position = glm::vec3(place, -10,0);
    this->value=num;
    static GLfloat vertex_buffer_data_1[] = {
        -1.0f,1.0f,0.0f,//A
        -0.8f,0.8f,0.0f,//E
        1.0f,1.0f,0.0f,//B
        -0.8f,0.8f,0.0f,//E
        1.0f,1.0f,0.0f,//B
        0.8f,0.8f,0.0f,//F
    };
    static GLfloat vertex_buffer_data_2[] = {
        1.0f,1.0f,0.0f,//B
        0.8f,0.8f,0.0f,//F
        0.8f,0.2f,0.0f,//S
        1.0f,1.0f,0.0f,//B
        0.8f,0.2f,0.0f,//S
        1.0f,0.0f,0.0f,//U
    };
    static GLfloat vertex_buffer_data_3[] = {
        -0.8f,0.2f,0.0f,//R
        -1.0f,0.0f,0.0f,//P
        -0.8f,-0.2f,0.0f,//Q
        -0.8f,0.2f,0.0f,//R
        -0.8f,-0.2f,0.0f,//Q
        0.8f,-0.2f,0.0f,//T
        -0.8f,0.2f,0.0f,//R
        0.8f,-0.2f,0.0f,//T
        0.8f,0.2f,0.0f,//S
        0.8f,-0.2f,0.0f,//T
        0.8f,0.2f,0.0f,//S
        1.0f,0.0f,0.0f,//U
    };
    static GLfloat vertex_buffer_data_4[] = {
        1.0f,0.0f,0.0f,//U
        0.8f,-0.2f,0.0f,//T
        0.8f,-0.8f,0.0f,//I
        1.0f,0.0f,0.0f,//U
        0.8f,-0.8f,0.0f,//I
        1.0f,-1.0f,0.0f,//D
    };
    static GLfloat vertex_buffer_data_5[] = {
        0.8f,-0.8f,0.0f,//I
        1.0f,-1.0f,0.0f,//D
        -0.8f,-0.8f,0.0f,//L
        1.0f,-1.0f,0.0f,//D
        -0.8f,-0.8f,0.0f,//L
        -1.0f,-1.0f,0.0f,//C
    };
    static GLfloat vertex_buffer_data_6[] = {
        -0.8f,-0.8f,0.0f,//L
        -1.0f,-1.0f,0.0f,//C
        -1.0f,0.0f,0.0f,//P
        -0.8f,-0.8f,0.0f,//L
        -1.0f,0.0f,0.0f,//P
        -0.8f,-0.2f,0.0f,//Q
    };
    static GLfloat vertex_buffer_data_7[] = {
        -1.0f,1.0f,0.0f,//A
        -0.8f,0.8f,0.0f,//E
        -0.8f,0.2f,0.0f,//R
        -0.8f,0.2f,0.0f,//R
        -1.0f,1.0f,0.0f,//A
        -1.0f,0.0f,0.0f,//P
    };

    this->seg_1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_1, COLOR_BLUE,GL_FILL);
    this->seg_2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_BLUE,GL_FILL);
    this->seg_3 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_3, COLOR_BLUE,GL_FILL);
    this->seg_4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_4, COLOR_BLUE,GL_FILL);
    this->seg_5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_5, COLOR_BLUE,GL_FILL);
    this->seg_6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_6, COLOR_BLUE,GL_FILL);
    this->seg_7 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_7, COLOR_BLUE,GL_FILL);
}

void SSD::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    switch (this->value)
    {
        case 1:
            draw3DObject(this->seg_2);
            draw3DObject(this->seg_4);
            break;
        case 2:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_2);
            draw3DObject(this->seg_3);
            draw3DObject(this->seg_5);
            draw3DObject(this->seg_6);
            break;
        case 3:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_2);
            draw3DObject(this->seg_3);
            draw3DObject(this->seg_4);
            draw3DObject(this->seg_5);
            break;
        case 4:
            draw3DObject(this->seg_7);
            draw3DObject(this->seg_3);
            draw3DObject(this->seg_4);
            draw3DObject(this->seg_2);
            break;
        case 6:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_7);
            draw3DObject(this->seg_3);
            draw3DObject(this->seg_4);
            draw3DObject(this->seg_5);
            draw3DObject(this->seg_6);
            break;
        case 5:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_7);
            draw3DObject(this->seg_3);
            draw3DObject(this->seg_4);
            draw3DObject(this->seg_5);
            break;
        case 8:
            draw3DObject(this->seg_6);
        case 9:
            draw3DObject(this->seg_7);
            draw3DObject(this->seg_3);
            draw3DObject(this->seg_5);
        case 7:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_2);
            draw3DObject(this->seg_4);
            break;
        case 0:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_2);
            draw3DObject(this->seg_4);
            draw3DObject(this->seg_5);
            draw3DObject(this->seg_6);
            draw3DObject(this->seg_7);
            break;
        default:
            draw3DObject(this->seg_1);
            draw3DObject(this->seg_2);
            draw3DObject(this->seg_4);
            draw3DObject(this->seg_5);
            draw3DObject(this->seg_6);
            draw3DObject(this->seg_7);
            break;
    }

}
void SSD::set_score(int value) {
    this->value=value;
}