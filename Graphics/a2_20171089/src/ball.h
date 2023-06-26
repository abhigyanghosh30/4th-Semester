#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 velocity;
    float speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float yaw;
    float pitch;
    float roll;
private:
    VAO *object;
    VAO *tail;
};

#endif // BALL_H
