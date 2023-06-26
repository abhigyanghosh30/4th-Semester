#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {

public:
    Ring() {}
    Ring(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bool completed;
private:
    VAO *object;

};

#endif // RING_H