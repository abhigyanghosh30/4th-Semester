#include "main.h"

#ifndef INDICATOR_H
#define INDICATOR_H

class Indicator{

public: 
    Indicator(){}
    Indicator(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);

private:
    VAO *object;

};

#endif //INDICATOR_H