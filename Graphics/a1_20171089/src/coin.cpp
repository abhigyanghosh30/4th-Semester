#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y){
    this->position = glm::vec3(x,y,0);
    static GLfloat vertex_buffer_data[900];
    for(int i=0;i<100;i++)
	{
		vertex_buffer_data[9*i] = 0.0f;
		vertex_buffer_data[9*i+1] = 0.0f;
		vertex_buffer_data[9*i+2] = 0.0f;
		vertex_buffer_data[9*i+3] = 1*(cos(2*M_PI*i/100));
		vertex_buffer_data[9*i+4] = 1*(sin(2*M_PI*i/100));
		vertex_buffer_data[9*i+5] = 0.0f;
		vertex_buffer_data[9*i+6] = 1*(cos(2*M_PI*(i+1)/100));
		vertex_buffer_data[9*i+7] = 1*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[9*i+8] = 0.0f;

	}
    this->box = {x,y,2,2};
    this->display = true;
    this->score = (rand()%2)+1;
    if(score==1)
        this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    else
        this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x,y,0);
    this->box = {x,y,2,2};
}