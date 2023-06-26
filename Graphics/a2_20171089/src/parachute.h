#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float yaw;
private:
    VAO *object;
};

#endif // PARACHUTE_H