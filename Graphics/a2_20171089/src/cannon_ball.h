#include "main.h"

#ifndef CANNON_BALL_H
#define CANNON_BALL_H

class CannonBall {
public:
    CannonBall(){}
    CannonBall(float x, float z, float yaw);
    glm::vec3 position;
    glm::vec3 speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float yaw; 
private:
    VAO *object;
};

#endif // CANNON_BALL_H