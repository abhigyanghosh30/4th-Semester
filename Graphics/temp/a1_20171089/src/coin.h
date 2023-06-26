#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin{
    public:
        Coin(){}
        Coin(float x, float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        bounding_box_t box;
        bool display;
        int score;
        
    private:
        VAO *object;
};

#endif //COIN_H