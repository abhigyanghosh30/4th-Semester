#include "main.h"

#ifndef SHEILD_H
#define SHILD_H

class Sheild {
public:
    Sheild(){}
    Sheild(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t box;
    float yspeed;
    float xspeed;
    bool display;

private:
    VAO *object;
};

#endif // SHIELD_H