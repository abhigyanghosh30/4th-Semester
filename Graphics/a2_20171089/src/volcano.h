#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano {
public:
    Volcano() {}
    Volcano(float x, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);

private:
    VAO *object;
    VAO *lava;
};

#endif // VOLCANO_H