#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H

class FireLine{
    public:
        FireLine(){}
        FireLine(float x, float y);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
    
    private:
        VAO *object;
        VAO *object_line;
};

#endif //FIRELINE_H