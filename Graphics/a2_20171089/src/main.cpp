#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "ssd.h"
#include "volcano.h"
#include "bar.h"
#include "bomb.h"
#include "bullet.h"
#include "ring.h"
#include "cannon.h"
#include "cannon_ball.h"
#include "parachute.h"
#include "fuel_can.h"
#include "arrow.h"
#include "indicator.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball plane;
Ground ground;
SSD speed1;
SSD speed2;
Bar alt;
Bar lives_bar;
Bar fuel_bar;
SSD dist0_bar;
SSD dist1_bar;
SSD dist2_bar;
vector <Volcano> volcanoes;
vector <Bomb> bombs;
vector <Ring> rings;
vector <Bullet> bullets;
vector <Cannon> cannons;
vector <CannonBall> cannon_balls;
vector <Parachute> parachutes;
vector <FuelCan> fuel_cans;
Indicator indicator;
Arrow arrow;

int lives;
int fuel = 60;
float screen_zoom = 1.0f, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float eye_x, eye_y, eye_z, horizontal = 90, vertical = 0;
float up_x = 0, up_y = 1, up_z = 0;
float t_x,t_y,t_z;
int camera_view = 4;

Timer t60(1.0 / 60);
Timer t1(1.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    if(camera_view == 0)
    {   
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        eye_x = plane.position.x + 3.0f * cos(horizontal * M_PI / 180.0f);
        eye_y = plane.position.y + 3.0f * cos(vertical * M_PI / 180.0f);
        eye_z = plane.position.z - 3.0f * sin(horizontal * M_PI / 180.0f);
        
        t_x = plane.position.x;
        t_y = plane.position.y; 
        t_z = plane.position.z;

        up_x = 0;
        up_y = 1;
        up_z = 0;
    }
    if(camera_view == 1)
    {
        eye_x = plane.position.x;
        eye_y = plane.position.y+20;
        eye_z = plane.position.z;
        t_x = plane.position.x;
        t_y = plane.position.y;
        t_z = plane.position.z;
        up_x = 0;
        up_y = 0;
        up_z = 1;
    }
    if(camera_view == 2)
    {
        eye_x = plane.position.x - 2.9f * cos( horizontal * M_PI / 180.0f);
        eye_y = plane.position.y;
        eye_z = plane.position.z + 2.9f * sin(horizontal *  M_PI / 180.0f);;
        t_x = plane.position.x - 3.0f * cos( horizontal * M_PI / 180.0f);
        t_y = plane.position.y;
        t_z = plane.position.z + 3.0f * sin(horizontal * M_PI / 180.0f);
        up_x = 0;
        up_y = 1;
        up_z = 0;
    }
    if(camera_view == 3)
    {
        eye_x = eye_y = eye_z = 0;
        t_x = plane.position.x;
        t_y = plane.position.y;
        t_z = plane.position.z;
        up_x = 0;
        up_y = 1;
        up_z = 0;
    }
    if(camera_view == 4)
    {
        eye_x = plane.position.x + 3.0 * cos((plane.yaw + 90) * M_PI / 180.0f );
        eye_y = plane.position.y + 3.0f;
        eye_z = plane.position.z - 3.0 * sin((plane.yaw + 90) * M_PI / 180.0f );
        
        t_x = plane.position.x;
        t_y = plane.position.y; 
        t_z = plane.position.z;

        up_x = 0;
        up_y = 1;
        up_z = 0;
    }

    glm::vec3 eye (eye_x, eye_y, eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (t_x, t_y, t_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);
 
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 VP1 = Matrices.projection *  glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    ground.draw(VP);
    for(vector<Volcano>::iterator volcano = volcanoes.begin();volcano!=volcanoes.end();volcano++) {
        volcano->draw(VP);
    }
    for(vector<Bomb>::iterator bomb = bombs.begin(); bomb != bombs.end();bomb++) {
        bomb->draw(VP);
    }
    for(vector<Ring>::iterator ring = rings.begin(); ring != rings.end() ; ring++) {
        ring->draw(VP);
    }
    for(vector<Bullet>::iterator bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
        bullet->draw(VP);
    }
    for(vector<Cannon>::iterator cannon = cannons.begin(); cannon != cannons.end() ;cannon++)
    {
        cannon->draw(VP);
    }
    for(vector<CannonBall>::iterator cannon_ball = cannon_balls.begin(); cannon_ball != cannon_balls.end() ;cannon_ball++)
    {
        cannon_ball->draw(VP);
    }
    for(vector<Parachute>::iterator parachute = parachutes.begin(); parachute != parachutes.end(); parachute++) {
        parachute->draw(VP);
    }
    for(vector<FuelCan>::iterator fuel_can = fuel_cans.begin(); fuel_can != fuel_cans.end(); fuel_can++) {
        fuel_can->draw(VP);
    }
    arrow.draw(VP);
    // Matrices.view = glm::lookAt( glm::vec3(0,0,-3), glm::vec3(0,0,0),glm::vec3(0,1,0) );
    // Matrices.projection = glm::ortho(-1,1,-1,1);
    // glm::mat4 VP2 = Matrices.projection * Matrices.view;    
    // speed1.draw(VP);
    // speed2.draw(VP);
    alt.draw(VP1);
    lives_bar.draw(VP1);
    fuel_bar.draw(VP1);
    dist0_bar.draw(VP1);
    dist1_bar.draw(VP1);
    dist2_bar.draw(VP1);
    speed1.draw(VP1);
    speed2.draw(VP1);
    indicator.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int a = glfwGetKey(window, GLFW_KEY_A);
    // int c = glfwGetKey(window, GLFW_KEY_C);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    int left_alt = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
    int mouse_left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int mouse_right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (d) {
        plane.yaw -= 1;
        horizontal = plane.yaw + 90;
        vertical = 0;
    }
    if(a){
        plane.yaw += 1;
        horizontal = plane.yaw + 90;
        vertical = 0;
    }
    // if(up) {
    //     horizontal+=1.0f;
    // }
    // if(down) {
    //     horizontal-=1.0f;
    // }
    if(q) {
        plane.roll--;
    }
    if(e) {
        plane.roll++;
    }
    if(up) {
        plane.pitch = plane.pitch <= -30 ? -30 : plane.pitch - 0.2f;
        plane.position.y = plane.position.y >= 30.0f ? 30.0f : plane.position.y + 0.1f;
    }
    else if(down){
        if(plane.pitch <= 0) {
            plane.pitch += 0.2f;
        }
        plane.position.y -= 0.1f;
    }
    
    if(w) {
        plane.speed = plane.speed >= 3.0 ? 3.0 : plane.speed + 0.1;
    }
    else if(s) {
        plane.speed -= plane.speed < 0 ? 0: plane.speed - 0.1;
    }
    if(mouse_right) {
        bombs.push_back(Bomb(plane.position.x,plane.position.y,plane.position.z)); 
    }
    if(mouse_left) {
        // cout<<"Left"<<endl;
        bullets.push_back(Bullet(plane.position.x,plane.position.y,plane.position.z,plane.yaw));
    }
    // if(c) {
    //     camera_view = (camera_view+1)%4;
    // }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if(xpos > 640){
        horizontal += 1.0f;
    }
    if(xpos < 440){
        horizontal -= 1.0f;
    }
    if(ypos > 640){
        vertical += 1.0f;
    }
    if(ypos < 440){
        vertical -= 1.0f;
    }

}

void tick_elements() {
    plane.tick();
    plane.velocity.x = plane.speed * sin(plane.yaw*M_PI / 180.0f);
    plane.velocity.z = plane.speed * cos(plane.yaw*M_PI / 180.0f);

    // speed1.set_position(plane.position.x+2,plane.position.y+2,plane.position.z+3);
    // speed2.set_position(plane.position.x,plane.position.y+2,plane.position.z+3);
    // alt.set_position(plane.position.x,plane.position.y-4, plane.position.z);
    // alt.yaw = plane.yaw;
    // speed1.set_score(mag_speed%10);
    // speed2.set_score((mag_speed/10)%10);
    alt.set_score(plane.position.y+10);
    lives_bar.set_score(30-lives);
    fuel_bar.set_score(fuel);
    dist0_bar.set_score(int(glm::length(plane.position - rings.begin()->position))%10);
    dist1_bar.set_score(int(glm::length(plane.position - rings.begin()->position)/10)%10);
    dist2_bar.set_score(int(glm::length(plane.position - rings.begin()->position)/100)%10);
    speed1.set_score(int(plane.speed * 10) % 10);
    speed2.set_score(int(plane.speed) % 10);
    for(vector<Bomb>::iterator bomb=bombs.begin();bomb!=bombs.end();bomb++) {
        bomb->tick();
        if(bomb->position.y<-10){
            bombs.erase(bomb);
            bomb--;
        }
    }
    for(vector<Bullet>::iterator bullet = bullets.begin(); bullet!=bullets.end(); bullet++) {
        bullet->tick();
        if(bullet->position.y<-10){
            bullets.erase(bullet);
            bullet--;
        }
    }
    for(vector<Cannon>::iterator cannon = cannons.begin();cannon!=cannons.end();cannon++){
        glm::vec3 direction = cannon->position - plane.position; 
        cannon->tick(direction.z<0?atan(direction.x/direction.z):M_PI+atan(direction.x/direction.z), atan((plane.position.y + 10) / ((direction.x)*(direction.x)+(direction.z)*(direction.z))));
        if(glm::length(direction)<50){
            cannon_balls.push_back(CannonBall(cannon->position.x, cannon->position.z, cannon->yaw));
        }
    }
    for(vector<CannonBall>::iterator cannon_ball = cannon_balls.begin(); cannon_ball!=cannon_balls.end(); cannon_ball++) {
        cannon_ball->tick();
        if(cannon_ball->position.y<-10){
            cannon_balls.erase(cannon_ball);
            cannon_ball--;
        }
    }
    for(vector<Parachute>::iterator parachute=parachutes.begin();parachute!=parachutes.end();parachute++){
        parachute->tick();
        if(parachute->position.y<-10){
            parachutes.erase(parachute);
            parachute--;
        }
    }
    for(vector<FuelCan>::iterator fuel_can=fuel_cans.begin();fuel_can!=fuel_cans.end();fuel_can++){
        fuel_can->tick();
        if(fuel_can->position.y<-10){
            fuel_cans.erase(fuel_can);
            fuel_can--;
        }
    }

    glm::vec3 direction = cannons.begin()->position - plane.position;
    // cout<<arrow.yaw<<endl;
    // cout<<plane.position.x<<","<<plane.position.y<<","<<plane.position.z<<endl;
    // cout<<rings.begin()->position.x<<","<<rings.begin()->position.y<<","<<rings.begin()->position.z<<endl;
    
    if(direction.z<0){
        arrow.tick(M_PI+atan(direction.x/direction.z),-atan(direction.y/sqrt((direction.x)*(direction.x)+(direction.z)*(direction.z))),plane.position.x,plane.position.y+2, plane.position.z);
    }
    else{
        arrow.tick(atan(direction.x/direction.z), -atan(direction.y/sqrt((direction.x)*(direction.x)+(direction.z)*(direction.z))),plane.position.x,plane.position.y+2, plane.position.z);
    }
    if(camera_view == 2){
        arrow.position.x = plane.position.x - 6.0f * cos( horizontal * M_PI / 180.0f);
        arrow.position.y = plane.position.y - 0.5f;
        arrow.position.z = plane.position.z + 6.0f * sin( horizontal * M_PI / 180.0f);
    }
    indicator.set_position(cannons.begin()->position.x,cannons.begin()->position.y + 3,cannons.begin()->position.z);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Ball(0, 0, 0);
    arrow = Arrow(0, 2, 0);
    ground = Ground(0,-10.0f,0);
    // speed1 = SSD(0,0);
    // speed2 = SSD(2,0);
    alt = Bar(-3,-3,0,10,COLOR_LAVAYELLOW);
    lives_bar = Bar(-3,-2,0,30,COLOR_BLUE);
    fuel_bar = Bar(-3,-2.5,0,30,COLOR_YELLOW);
    dist0_bar = SSD(1,0);
    dist1_bar = SSD(0.5,0);
    dist2_bar = SSD(0,0);
    speed1 = SSD(-1,0);
    speed2 = SSD(-1.5,0);
    for(int i=0;i<50;i++) {
        volcanoes.push_back(Volcano(rand()%1000-500,rand()%500-250));
    }
    rings.push_back(Ring(0,10,0));
    for(int i=0;i<30;i++) {
        float ring_x = rand()%1000-500;
        float ring_y = rand()%20;
        float ring_z = rand()%500-250;
        rings.push_back(Ring(ring_x,ring_y,ring_z));
        cannons.push_back(Cannon(ring_x+20.0f,ring_z+20.0f));
        cannons.push_back(Cannon(ring_x-20.0f,ring_z+20.0f));
        cannons.push_back(Cannon(ring_x+20.0f,ring_z-20.0f));
        cannons.push_back(Cannon(ring_x-20.0f,ring_z-20.0f));
    }

    indicator = Indicator(rings.begin()->position.x,rings.begin()->position.y + 3,rings.begin()->position.z);

    // for(int i=0;i<15;i++) {
    //     cannons.push_back(Cannon(rand()%1000-500,rand()%500-250));
    // }
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
    srand(time(0));
    int width  = 1080;
    int height = 1080;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            check_collisions();
            spawn_elements();
            tick_input(window);
        }
        if(plane.position.y <= -10 || fuel<=0 ){
            quit(window);
            return 0;
        }
        if(lives>=30){
            quit(window);
            return 0;
        }
        if(t1.processTick()){
            fuel-=0.01;
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // if(camera_view == 0)
    Matrices.projection = glm::perspective(float(M_PI_2 * screen_zoom), 1.0f, 0.1f, 500.0f);
    // if(camera_view == 1)
    //     Matrices.projection = glm::ortho(left,right,bottom,top,0.1f,100.0f);

}

void check_collisions() { 
    for(vector<Volcano>::iterator volcano = volcanoes.begin();volcano!=volcanoes.end();volcano++) {
        if(plane.position.y < 10  && sqrt((plane.position.x - volcano->position.x)*(plane.position.x - volcano->position.x)+(plane.position.z - volcano->position.z)*(plane.position.z - volcano->position.z))<8){
            // cout<<"Quit "<<lives++<<endl;
            lives++;
            // quit(window);
        }
    }
    for(vector<Ring>::iterator ring = rings.begin();ring!=rings.end();ring++)
    {
        if(sqrt((plane.position.y - ring->position.y)*(plane.position.y - ring->position.y)+(plane.position.x - ring->position.x)*(plane.position.x - ring->position.x)+(plane.position.z - ring->position.z)*(plane.position.z - ring->position.z)) < 8) {
            lives--;
            fuel+=5;
            rings.erase(ring);
            ring--;
        }
    }
    for(vector<Cannon>::iterator cannon = cannons.begin();cannon != cannons.end();cannon++){
        for(vector<Bomb>::iterator bomb=bombs.begin();bomb!=bombs.end();bomb++){
            if(glm::length(cannon->position - bomb->position)<3){
                bombs.erase(bomb);
                bomb--;
                cannons.erase(cannon);
                cannon--;
            }
        }
    }
    for(vector<Cannon>::iterator cannon = cannons.begin();cannon!=cannons.end();cannon++){
        for(vector<Bullet>::iterator bullet = bullets.begin();bullet!=bullets.end();bullet++){
            if(glm::length(cannon->position - bullet->position)<3){
                bullets.erase(bullet);
                bullet--;
                cannons.erase(cannon);
                cannon--;
            }
        }
    }


    for(vector<Parachute>::iterator parachute=parachutes.begin(); parachute != parachutes.end(); parachute++) {
        for(vector<Bullet>::iterator bullet = bullets.begin();bullet!=bullets.end();bullet++) {
            if(glm::length(bullet->position-parachute->position)<2) {
                bullets.erase(bullet);
                bullet--;
                parachutes.erase(parachute);
                parachute--;
                lives--;
            }
        }
        if(glm::length(parachute->position-plane.position)<2){
            parachutes.erase(parachute);
            parachute--;
            lives++;
        }
    }
    for(vector<FuelCan>::iterator fuel_can=fuel_cans.begin(); fuel_can != fuel_cans.end(); fuel_can++) {
        if(glm::length(fuel_can->position-plane.position)<2){
            fuel_cans.erase(fuel_can);
            fuel_can--;
            fuel+=5;
        }
    }
    for(vector<CannonBall>::iterator cannon_ball = cannon_balls.begin(); cannon_ball != cannon_balls.end(); cannon_ball++) {
        if(glm::length(cannon_ball->position - plane.position)<1) {
            cannon_balls.erase(cannon_ball);
            cannon_ball--;
            lives++;
        }
    }
}

void spawn_elements(){
    if(rand()%10000 < 2250) {
        parachutes.push_back(Parachute(rand()%1000-500,rand()%500-250));
    }
    if(rand()%10000 < 7250) {
        fuel_cans.push_back(FuelCan(rand()%1000-500,rand()%500-250));
    }

}