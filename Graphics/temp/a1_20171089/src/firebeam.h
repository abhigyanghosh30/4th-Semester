#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H

class FireBeam{
    public:
        FireBeam(){}
        FireBeam(float x, float y);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void tick();
        float yspeed;
    
    private:
        VAO *object;
        VAO *object_line;
};

#endif //FIREBEAM_H