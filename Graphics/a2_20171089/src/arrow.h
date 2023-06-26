#include "main.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow{

public: 
    Arrow(){}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick(float yaw, float pitch, float x, float y, float z);
    bool completed;
    float yaw;
    float pitch;

private:
    VAO *object;

};

#endif // ARROW_H