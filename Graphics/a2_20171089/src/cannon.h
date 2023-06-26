#include "main.h"

#ifndef CANNON_H
#define CANNON_H

class Cannon{
public:
    Cannon() {}
    Cannon(float x, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick(float yaw, float pitch);
    float yaw;
    float pitch;
private:
    VAO *object;
};

#endif //CANNON_H