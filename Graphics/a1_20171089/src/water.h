#include "main.h"

#ifndef WATER_H
#define WATER_H

class Water{
    public:
        Water(float x, float y);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void tick();
        float yspeed;
        float xspeed;
    
    private:
        VAO *object;
};

#endif //WATER_H