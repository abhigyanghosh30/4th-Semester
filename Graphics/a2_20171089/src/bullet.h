#include "main.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float z, float yaw);
    glm::vec3 position;
    glm::vec3 speed;
    void draw(glm::mat4 VP);
    void tick();
    float yaw;
private:
    VAO *object;
};

#endif // BULLET_H