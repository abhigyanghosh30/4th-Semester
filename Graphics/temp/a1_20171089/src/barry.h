#include "main.h"

#ifndef BARRY_H 
#define BARRY_H

class Barry{
public:
    Barry() {}
    Barry(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed;
    double yspeed;
    double xaccln;
    double yaccln;
    bounding_box_t box;
    bool jump; 
    int countdown;

private:
    VAO *object;
    VAO *jet;
};

#endif // BARRY_H