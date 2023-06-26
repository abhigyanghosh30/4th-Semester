#include "main.h"
#include "timer.h"
#include "floor.h"
#include "coin.h"
#include "barry.h"
#include "fireline.h"
#include "firebeam.h"
#include "water.h"
#include "magnet.h"
#include "boomerang.h"
#include "sheild.h"
#include "circle.h"
#include "ssd.h"

#include <GL/glut.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

vector <Floor> floors;
Barry barry;
Boomerang boomerang;
vector <Coin> coins;
vector <FireLine> firelines;
vector <FireBeam> firebeams;
vector <Water> balloons;
Magnet magnet;
Sheild sheild;
Circle circle;
SSD score_1;
SSD score_2;
SSD score_3;
SSD lives_display;

int score=0,life = 4;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0, 0, 200);
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    barry.draw(VP);
    if(circle.display)
        circle.draw(VP);
    if(boomerang.display)
        boomerang.draw(VP);
    for(vector<Floor>::iterator f=floors.begin(); f != floors.end(); ++f ) {
        f->draw(VP);
    }
    for(vector<Coin>::iterator c=coins.begin(); c!= coins.end(); ++c ) {
        if(c->display)
            c->draw(VP);
    }
    for(vector<Water>::iterator wb=balloons.begin(); wb!=balloons.end(); ++wb) {
        wb->draw(VP);
    }
    for(vector<FireLine>::iterator f=firelines.begin(); f!=firelines.end(); ++f ) {
        f->draw(VP);
    }
    for(vector<FireBeam>::iterator fb=firebeams.begin(); fb!=firebeams.end(); ++fb ) {
        fb->draw(VP);
    }
    if(magnet.display)
        magnet.draw(VP);
    if(sheild.display)
        sheild.draw(VP);

    // Score display
    score_1.draw(VP);
    score_2.draw(VP);
    score_3.draw(VP);
    lives_display.draw(VP);
}


void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if(space)
        balloons.push_back(Water(barry.position.x+1,barry.position.y+1));
    if(up)
        jump();
    if(left)
        barry_move_left();
    if(right)
        barry_move_right();
    
}

void tick_elements() {    
    float dist = sqrt((barry.position.x-circle.position.x)*(barry.position.x-circle.position.x)+(barry.position.y-circle.position.y)*(barry.position.y-circle.position.y));
    float theta = barry.position.x>circle.position.x?atan(barry.position.y/(barry.position.x-circle.position.x)):M_PI-atan(barry.position.y/(circle.position.x-barry.position.x)); 
    if(dist >= 9 && dist <= 10 && theta > 0) {
        // cout<<barry.position.y<<endl;
        barry.yaccln = 0.0f;
        barry.xaccln = 0.0f;
        barry.xspeed = 0.0f;
        barry.yspeed = 0.0f;
        barry.countdown = 300;
        // cout<<theta<<endl;
        if(barry.position.x>circle.position.x){
            // barry.tick();
            barry.set_position(circle.position.x+9.2*cos(theta-0.01),9.2*sin(theta-0.01));
        }
        else{
            // barry.yspeed=0.1f;
            // barry.tick();
            barry.set_position(circle.position.x+9.2*cos(theta-0.01),9.2*sin(theta-0.01));
            // barry.set_position(barry.position.x+0.1f,barry.position.y+0.1f);
        }
        return;
    }
    barry.yaccln = -0.01f;
    barry.xspeed = 0;
    for(vector<Coin>::iterator coin=coins.begin(); coin!=coins.end(); ++coin) {
            if(coin->display && detect_collision(coin->box,{barry.position.x,barry.position.y,2,2})) {
                coin->display=false;
                score += coin->score;
            }
    }
    for(vector<FireLine>::iterator fl = firelines.begin(); fl!=firelines.end(); ++fl) {
        if(detect_burn(fl->position.x,fl->position.y,fl->rotation) && barry.countdown <=0) {
            firelines.erase(fl);
            fl--;
            life--;
        }
    }

    for(vector<FireBeam>::iterator fb = firebeams.begin();fb!=firebeams.end(); ++fb) {
        if(detect_burn(fb->position.x,fb->position.y,fb->rotation) && barry.countdown <=0) {
            firebeams.erase(fb);
            fb--;
            life--;
        }
    }

    for(vector<Water>::iterator wb=balloons.begin(); wb!=balloons.end(); ++wb) {
        if(wb->position.y<=0) {
            balloons.erase(wb);
            wb--;
        }

        for(vector<FireBeam>::iterator fb=firebeams.begin(); fb!=firebeams.end(); ++fb) {
            if(detect_douse(fb->position.x, fb->position.y, fb->rotation, wb->position.x, wb->position.y)){
                firebeams.erase(fb);
                fb--;
                balloons.erase(wb);
                wb--;
            }
        }
        for(vector<FireLine>::iterator fl=firelines.begin(); fl!=firelines.end(); ++fl) {
            if(detect_douse(fl->position.x, fl->position.y, fl->rotation, wb->position.x, wb->position.y)){
                firelines.erase(fl);
                fl--;
                balloons.erase(wb);
                wb--;
            }
        }
        wb->tick();
    }
    if(magnet.position.x <= -42){
        magnet.display = false;
        magnet.position.x=-41;
    }
    barry.tick();
    boomerang.tick();
    if(detect_collision({barry.position.x,barry.position.y,2,2},boomerang.box) && barry.countdown<=0) {
        life--;
        cout<<"BOOMERANGED"<<endl;

        boomerang.display = false;
    }
    sheild.tick();
    if(sheild.display && detect_collision(barry.box,sheild.box)) {
        sheild.display=false;
        barry.countdown=300;
    }

    if(magnet.display) {
        barry.position.x += (magnet.position.x-barry.position.x)/50; 
        barry.position.y += (magnet.position.y-barry.position.y)/50; 
    }
    move_right();
    // camera_rotation_angle += 1;
}

void spawn_objects() {
    // srand(time(NULL));

    float spawn_coin = rand()%10000;
    // cout<< spawn_coin << endl;
    if( spawn_coin > 9800 ) {
        coins.push_back(Coin(42,rand()%10));
        return;
    }
    float spawn_fire_beam = rand()%10000;
    if( spawn_fire_beam > 9980 ) {
        firebeams.push_back(FireBeam(42,rand()%10));
    }

    float spawn_fire_line = rand()%1000;
    if( spawn_fire_line > 990 ) {
        firelines.push_back(FireLine(42,rand()%10));
        return;
    }

    float spawn_magnet = rand()%1000;
    if(!magnet.display && spawn_magnet > 997 && !circle.display ) {
        magnet.set_position(42,0) ;
        magnet.display = true;
        return;
    }
    float spawn_circle = rand()%1000;
    if(!circle.display && spawn_circle > 997 && !magnet.display) {
        circle.set_position(42) ;
        circle.display = true;
        return;
    }

    float spawn_sheild = rand()%1000;
    if(!sheild.display && spawn_sheild > 995) {
        sheild.set_position(42,rand()%10);
        sheild.display = true;
        sheild.xspeed = -0.9;
        return;
    }

    float spawn_boomerang = rand()%1000;
    if(!boomerang.display && spawn_boomerang> 995) {
        boomerang.set_position(42,20) ;
        boomerang.display = true;
        boomerang.xspeed = -1;
        boomerang.yspeed = 0;
        return;
    }


}

void jump(){
    barry.yspeed+=0.1;
    barry.jump = true;
}

void barry_move_left(){
    barry.set_position(barry.position.x-0.2,barry.position.y);
    if(barry.position.x - screen_center_x <= -40) {
        screen_center_x -= 0.2f;
        reset_screen();
    }
}
void barry_move_right(){
    barry.set_position(barry.position.x+0.2,barry.position.y);
    if(barry.position.x - screen_center_x >=40) {
        screen_center_x += 0.2f;
        reset_screen();
    }
    
}

void move_right(){
    for(vector<Coin>::iterator c=coins.begin(); c!= coins.end(); ++c){
        c->set_position(c->position.x-0.1f,c->position.y);
        if(c->position.x < -40) {
            coins.erase(c);
            c--;
        }
    }

    for(vector<FireLine>::iterator fl=firelines.begin(); fl!=firelines.end(); ++fl) {
        fl->set_position(fl->position.x-0.1f,fl->position.y);
        if(fl->position.x < -40) {
            firelines.erase(fl);
            fl--;
        }
    }
    for(vector<FireBeam>::iterator fb=firebeams.begin(); fb!=firebeams.end(); ++fb) {
        fb->set_position(fb->position.x-0.1f,fb->position.y);
        if(detect_burn(fb->position.x,fb->position.y,fb->rotation)){
            firebeams.erase(fb);
            fb--;
            life--;
        }
        if(fb->position.x < -40) {
            firebeams.erase(fb);
            fb--;
        }
        fb->tick();
    }
    magnet.set_position(magnet.position.x-0.1f,magnet.position.y);
    sheild.set_position(sheild.position.x-0.1f,sheild.position.y);
    circle.set_position(circle.position.x-0.1f);
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    barry = Barry(0.0f,2.0f);
    for(int i=-40;i<=40;i+=1){
        Floor new_floor = Floor(float(i),-3.5f,COLOR_BLACK);
        floors.push_back(new_floor);
    }
    coins.push_back(Coin(3,3));
    firelines.push_back(FireLine(0.0f,0.0f));
    magnet = Magnet(42,0);
    magnet.display = false;
    sheild = Sheild(42,0);
    sheild.display = false;
    boomerang = Boomerang(42,10);
    circle = Circle(5);
    score_1 = SSD(4,score%10);
    score_2 = SSD(1,(score/10)%10);
    score_3 = SSD(-2,(score/100)%10);
    lives_display = SSD(-10,life);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    // srand(time(NULL));
    int width  = 1080;
    int height = 1080;

    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window) && life>0 ) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            spawn_objects();
            update_score();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    // cout << score << endl;
    quit(window);
}

void update_score(){
    score_1.set_score(score%10);
    score_2.set_score((score/10)%10);
    score_3.set_score((score/100)%10);
    lives_display.set_score(life);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_burn(float x, float y, float t) {
    float x1= barry.position.x;
    float y1= barry.position.y;
    double dist = sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
    // double min_dist = 1 + cos(t);
    return (dist < 1.414);
}

bool detect_douse(float x, float y, float t, float a, float b){
    float x1 = x + 0.5 * cos(t);
    float y1 = y + 0.5 * sin(t);
    float x2 = x - 0.5 * cos(t);
    float y2 = y - 0.5 * sin(t);
    return (sqrt((x1-a)*(x1-a)+(y1-b)*(y1-b))+sqrt((x2-a)*(x2-a)+(y2-b)*(y2-b)) < 1.3);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
