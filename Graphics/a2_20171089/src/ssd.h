#include "main.h"

#ifndef SSD_H
#define SSD_H

class SSD {
public:
    SSD(){}
    SSD(float place,int num);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_score(int value);
    int value;
    
private:
    VAO *seg_1;
    VAO *seg_2;
    VAO *seg_3;
    VAO *seg_4;
    VAO *seg_5;
    VAO *seg_6;
    VAO *seg_7;
};

#endif //SSD_H 