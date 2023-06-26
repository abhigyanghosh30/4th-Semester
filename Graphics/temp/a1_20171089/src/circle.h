#include "main.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
public:
    Circle() {}
    Circle(float x);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x);
    bool display;

private:
    VAO *object;
};

#endif // CIRCLE_H