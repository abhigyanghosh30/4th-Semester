#include "fireline.h"
#include "main.h"

FireLine::FireLine(float x, float y) {
    this->position = glm::vec3(x,y,0);
    this->rotation =  (rand() % 360) ;
	static GLfloat vertex_buffer_data[2000];
    for(int i=0;i<100;i++)
	{
		vertex_buffer_data[9*i]   = -1.0f;
		vertex_buffer_data[9*i+1] = 0.0f;
		vertex_buffer_data[9*i+2] = 0.0f;
		vertex_buffer_data[9*i+3] = 0.1f*(cos(2*M_PI*i/100))-1.0f;
		vertex_buffer_data[9*i+4] = 0.1f*(sin(2*M_PI*i/100));
		vertex_buffer_data[9*i+5] = 0.0f;
		vertex_buffer_data[9*i+6] = 0.1f*(cos(2*M_PI*(i+1)/100))-1.0f;
		vertex_buffer_data[9*i+7] = 0.1f*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[9*i+8] = 0.0f;
	}
    for(int i=100;i<200;i++)
	{
		vertex_buffer_data[9*i]   = 1.0f;
		vertex_buffer_data[9*i+1] = 0.0f;
		vertex_buffer_data[9*i+2] = 0.0f;
		vertex_buffer_data[9*i+3] = 0.1f*(cos(2*M_PI*i/100))+1.0f;
		vertex_buffer_data[9*i+4] = 0.1f*(sin(2*M_PI*i/100));
		vertex_buffer_data[9*i+5] = 0.0f;
		vertex_buffer_data[9*i+6] = 0.1f*(cos(2*M_PI*(i+1)/100))+1.0f;
		vertex_buffer_data[9*i+7] = 0.1f*(sin(2*M_PI*(i+1)/100));
		vertex_buffer_data[9*i+8] = 0.0f;
	}
    
	static GLfloat vertex_buffer_data_line[] = {
		-1.0f, 0.1f, 0.0f,
		1.0f, 0.1f, 0.0f,
		1.0f, -0.1f, 0.0f,
		1.0f, -0.1f, 0.0f,
		-1.0f, 0.1f, 0.0f,
		-1.0f,-0.1f, 0.0f
	};

    this->object = create3DObject(GL_TRIANGLES,200*3, vertex_buffer_data, COLOR_BLACK,GL_FILL);
	this->object_line = create3DObject(GL_TRIANGLES,3*2, vertex_buffer_data_line, COLOR_YELLOW,GL_FILL);
}
void FireLine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_line);
    draw3DObject(this->object);

}

void FireLine::set_position(float x, float y) {
    this->position = glm::vec3(x,y,0);
}