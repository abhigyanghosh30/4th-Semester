#include "main.h"

#ifndef FUEL_CAN_H
#define FUEL_CAN_H

class FuelCan {
public:
    FuelCan() {}
    FuelCan(float x, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float yaw;
private:
    VAO *object;
};

#endif // FUEL_CAN_H