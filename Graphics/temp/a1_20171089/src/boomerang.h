#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H

class Boomerang {
public:
    Boomerang(){}
    Boomerang(float x, float y);
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

#endif // BOOMERANG_H