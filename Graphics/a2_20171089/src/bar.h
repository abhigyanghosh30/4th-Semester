#include "main.h"

#ifndef BAR_H
#define BAR_H

class Bar {
public:
    Bar() {}
    Bar(float x, float y, float z,float value, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_score(float score);
    void set_position(float x, float y, float z);
    float yaw;
    color_t colour;
private:
    VAO *object;
};

#endif // BAR_H