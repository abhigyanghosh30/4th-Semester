#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet{
    public:
        Magnet(){}
        Magnet(float x, float y);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        bool display;
    private:
        VAO *object;
};

#endif //MAGNET_H