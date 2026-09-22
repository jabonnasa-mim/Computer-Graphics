//scene 3


#ifndef SCENE3_H
#define SCENE3_H

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.1416

//CIRCLE
void scene3_drawCircle(float center_x, float center_y, float radius, int segments)
{
    glBegin(GL_POLYGON);
    glVertex2f(center_x, center_y);

    for (int i = 0; i <= segments; i++)
    {
        float angle = 2 * PI * i / segments;
        glVertex2f(center_x + radius * cos(angle), center_y + radius * sin(angle));
    }

    glEnd();
}

//VARIABLES
bool scene3_isNight = false;

//bottom sky color
float scene3_skyR1 = 0.50f;
float scene3_skyG1 = 0.85f;
float scene3_skyB1 = 1.00f;

//top sky color
float scene3_skyR2 = 0.80f;
float scene3_skyG2 = 0.93f;
float scene3_skyB2 = 1.00f;

//BACKGROUND BUILDING COLOR
float scene3_bgR = 0.55f;
float scene3_bgG = 0.68f;
float scene3_bgB = 0.76f;


//WINDOW COLOR
float scene3_windowR = 0.75f;
float scene3_windowG = 0.90f;
float scene3_windowB = 1.00f;


//CLOUD POSITION
float scene3_cloudX = 0.0f;

//CAR POSITION
float scene3_car1X = -1.20f;
float scene3_car2X = -0.20f;
float scene3_car3X = 1.20f;
float scene3_car4X = 0.20f;
//CAR STOP STATUS
bool scene3_car1Stop = false;
bool scene3_car2Stop = false;
bool scene3_car3Stop = false;
bool scene3_car4Stop = false;


//TRAFFIC LIGHT
// 0 = GREEN
// 1 = RED
// 2 = YELLOW

int scene3_trafficLight = 0; // default green


//HUMAN POSITION
float scene3_h1x = -0.40f;
float scene3_h2x = 0.10f;
float scene3_h3x = 0.50f;

//HUMAN SPEED
float scene3_h1speed = 0.0020f;
float scene3_h2speed = 0.0015f;
float scene3_h3speed = 0.0025f;

//HUMAN DIRECTION
int scene3_h1dir = 0; // 0 = right, 1 = left
int scene3_h2dir = 1;
int scene3_h3dir = 0;
//HUMAN LEG MOVEMENT
float scene3_legAngle = 0.0f;
float scene3_legSpeed = 2.0f;


//CROSSING HUMAN POSITION
float scene3_humanX = -0.82f;
float scene3_humanY = -0.02f;

//CROSSING HUMAN STATUS
bool scene3_humanMoving = false;
int scene3_humanDirection = 0;

//CROSSING HUMAN LEG
float scene3_crossingLegAngle = 0.0f;
float scene3_crossingLegSpeed = 2.0f;


//RAIN
bool scene3_rain = false;

float scene3_rainX[1000];
float scene3_rainY[1000];
float scene3_rainSpeed[1000];

float scene3_rainSpeedMultiplier = 1.0f;


//SNOW
bool scene3_snow = false;

float scene3_snowX[500];
float scene3_snowY[500];
float scene3_snowSpeed[500];
float scene3_snowSway[500];  //left-right movement of snowflakes

float scene3_snowSpeedMultiplier = 1.0f;


//WIND
 bool scene3_wind = false;
 float scene3_windLineX[60];
 float scene3_windLineY[60];
 float scene3_windSway = 0.0f;    // tree leaves left-right rotation

// Seeds rain/snow/wind arrays with randomized starting positions and
// nonzero speeds. Without this, all particles start at (0,0) with
// speed 0 and never move, since the per-particle speed is otherwise
// only reassigned once a particle falls below the bottom of the
// screen -- which never happens if its speed is already 0.
void scene3_initializeWeather()
{
    for (int i = 0; i < 1000; i++)
    {
        scene3_rainX[i] = ((float)rand() / RAND_MAX) * 2.10f - 1.05f;
        scene3_rainY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene3_rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
    }

    for (int i = 0; i < 500; i++)
    {
        scene3_snowX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene3_snowY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene3_snowSpeed[i] = 0.003f + ((float)rand() / RAND_MAX) * 0.006f;
        scene3_snowSway[i] = ((float)rand() / RAND_MAX) * 6.28f;
    }

    for (int i = 0; i < 60; i++)
    {
        scene3_windLineX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene3_windLineY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    }
}

//SKY
void scene3_drawSky()
{
    glBegin(GL_QUADS);

    glColor3f(scene3_skyR1, scene3_skyG1, scene3_skyB1);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);

    glColor3f(scene3_skyR2, scene3_skyG2, scene3_skyB2);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);

    glEnd();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[BACKGROUND CITY]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawBackgroundCity()
{
    glColor3f(scene3_bgR, scene3_bgG, scene3_bgB);


    // LEFT
    glBegin(GL_QUADS);

    glVertex2f(-1.00f, 0.00f);
    glVertex2f(-0.60f, 0.00f);
    glVertex2f(-0.60f, 0.40f);
    glVertex2f(-1.00f, 0.40f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-0.90f, 0.00f);
    glVertex2f(-0.70f, 0.00f);
    glVertex2f(-0.70f, 0.52f);
    glVertex2f(-0.90f, 0.52f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-0.85f, 0.00f);
    glVertex2f(-0.80f, 0.00f);
    glVertex2f(-0.80f, 0.56f);
    glVertex2f(-0.85f, 0.56f);

    glEnd();


    // LEFT MIDDLE
    glBegin(GL_QUADS);

    glVertex2f(-0.50f, 0.00f);
    glVertex2f(-0.20f, 0.00f);
    glVertex2f(-0.20f, 0.60f);
    glVertex2f(-0.50f, 0.60f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-0.45f, 0.00f);
    glVertex2f(-0.25f, 0.00f);
    glVertex2f(-0.25f, 0.65f);
    glVertex2f(-0.45f, 0.65f);

    glEnd();


    //MIDDLE
    glBegin(GL_QUADS);

    glVertex2f(-0.15f, 0.00f);
    glVertex2f(0.05f, 0.00f);
    glVertex2f(0.05f, 0.60f);
    glVertex2f(-0.15f, 0.60f);

    glEnd();


    //RIGHT MIDDLE
    glBegin(GL_QUADS);

    glVertex2f(0.10f, 0.00f);
    glVertex2f(0.30f, 0.00f);
    glVertex2f(0.30f, 0.55f);
    glVertex2f(0.10f, 0.55f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(0.15f, 0.00f);
    glVertex2f(0.25f, 0.00f);
    glVertex2f(0.25f, 0.65f);
    glVertex2f(0.15f, 0.65f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(0.17f, 0.00f);
    glVertex2f(0.23f, 0.00f);
    glVertex2f(0.23f, 0.68f);
    glVertex2f(0.17f, 0.68f);

    glEnd();


    //RIGHT
    glBegin(GL_QUADS);

    glVertex2f(0.35f, 0.00f);
    glVertex2f(0.65f, 0.00f);
    glVertex2f(0.65f, 0.50f);
    glVertex2f(0.35f, 0.50f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(0.70f, 0.00f);
    glVertex2f(1.00f, 0.00f);
    glVertex2f(1.00f, 0.40f);
    glVertex2f(0.70f, 0.40f);

    glEnd();
}



//SUN / MOON

void scene3_drawSunMoon()
{
    if (!scene3_isNight)
    {
        // SUN
        glColor3f(1.0f, 0.92f, 0.15f);
        scene3_drawCircle(-0.75f, 0.80f, 0.055f, 36);

        glColor3f(1.0f, 0.98f, 0.65f);
        scene3_drawCircle(-0.76f, 0.81f, 0.022f, 18);
    }

    else
    {
        //MOON
        glColor3f(0.97f, 0.97f, 0.84f);
        scene3_drawCircle(-0.75f, 0.80f, 0.055f, 30);

        glColor3f(0.10f, 0.10f, 0.22f);
        scene3_drawCircle(-0.73f, 0.82f, 0.044f, 30);


        //STARS
        glPointSize(3.0f);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_POINTS);

        glVertex2f(-0.90f, 0.88f);
        glVertex2f(-0.65f, 0.92f);
        glVertex2f(-0.45f, 0.82f);
        glVertex2f(-0.25f, 0.91f);
        glVertex2f(-0.05f, 0.78f);
        glVertex2f(0.15f, 0.90f);
        glVertex2f(0.35f, 0.82f);
        glVertex2f(0.55f, 0.94f);
        glVertex2f(0.75f, 0.86f);
        glVertex2f(0.90f, 0.96f);

        glEnd();

        glPointSize(1.0f);
    }
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% [CLOUD] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawCloud(float x, float y, float scale)
{
    glPushMatrix();

    glTranslatef(x + scene3_cloudX, y, 0.0f);
    glScalef(scale, scale, 1.0f);


    if (scene3_isNight)
        glColor3f(0.22f, 0.22f, 0.32f);

    else
        glColor3f(0.98f, 0.98f, 1.00f);


    scene3_drawCircle(0.00f, 0.00f, 0.05f, 22);
    scene3_drawCircle(0.045f, 0.016f, 0.065f, 22);
    scene3_drawCircle(0.095f, 0.004f, 0.055f, 22);
    scene3_drawCircle(0.070f, -0.014f, 0.036f, 22);
    scene3_drawCircle(-0.025f, -0.009f, 0.034f, 22);


    glPopMatrix();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% [BUILDINGS] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawBuildings()
{
    //YELLOW HOUSE
    glColor3f(1.0f, 0.80f, 0.30f);

    glBegin(GL_QUADS);

    glVertex2f(-0.95f, 0.00f);
    glVertex2f(-0.65f, 0.00f);
    glVertex2f(-0.65f, 0.25f);
    glVertex2f(-0.95f, 0.25f);

    glEnd();


    //YELLOW HOUSE ROOF
    glColor3f(0.61f, 0.25f, 0.04f);

    glBegin(GL_TRIANGLES);

    glVertex2f(-0.98f, 0.25f);
    glVertex2f(-0.62f, 0.25f);
    glVertex2f(-0.81f, 0.38f);

    glEnd();


    //DOOR
    glColor3f(0.61f, 0.25f, 0.04f);

    glBegin(GL_QUADS);

    glVertex2f(-0.92f, 0.00f);
    glVertex2f(-0.84f, 0.00f);
    glVertex2f(-0.84f, 0.15f);
    glVertex2f(-0.92f, 0.15f);

    glEnd();


    //WINDOW
    glColor3f(scene3_windowR, scene3_windowG, scene3_windowB);

    glBegin(GL_QUADS);

    glVertex2f(-0.78f, 0.06f);
    glVertex2f(-0.68f, 0.06f);
    glVertex2f(-0.68f, 0.16f);
    glVertex2f(-0.78f, 0.16f);

    glEnd();



    //BLUE BUILDING
    glColor3f(0.239f, 0.353f, 0.502f);

    glBegin(GL_QUADS);

    glVertex2f(-0.60f, 0.00f);
    glVertex2f(-0.30f, 0.00f);
    glVertex2f(-0.30f, 0.45f);
    glVertex2f(-0.60f, 0.45f);

    glEnd();


    //WINDOWS
    glColor3f(scene3_windowR, scene3_windowG, scene3_windowB);

    glBegin(GL_QUADS);

    glVertex2f(-0.55f, 0.35f);
    glVertex2f(-0.50f, 0.35f);
    glVertex2f(-0.50f, 0.40f);
    glVertex2f(-0.55f, 0.40f);

    glVertex2f(-0.40f, 0.35f);
    glVertex2f(-0.35f, 0.35f);
    glVertex2f(-0.35f, 0.40f);
    glVertex2f(-0.40f, 0.40f);

    glVertex2f(-0.55f, 0.20f);
    glVertex2f(-0.50f, 0.20f);
    glVertex2f(-0.50f, 0.25f);
    glVertex2f(-0.55f, 0.25f);

    glVertex2f(-0.40f, 0.20f);
    glVertex2f(-0.35f, 0.20f);
    glVertex2f(-0.35f, 0.25f);
    glVertex2f(-0.40f, 0.25f);

    glEnd();


    //DOOR
    glColor3f(0.588f, 0.435f, 0.200f);

    glBegin(GL_QUADS);

    glVertex2f(-0.47f, 0.00f);
    glVertex2f(-0.42f, 0.00f);
    glVertex2f(-0.42f, 0.10f);
    glVertex2f(-0.47f, 0.10f);

    glEnd();



    //RED HOUSE
    glColor3f(0.906f, 0.365f, 0.337f);

    glBegin(GL_QUADS);

    glVertex2f(-0.20f, 0.00f);
    glVertex2f(0.10f, 0.00f);
    glVertex2f(0.10f, 0.40f);
    glVertex2f(-0.20f, 0.40f);

    glEnd();


    //RED HOUSE ROOF
    glColor3f(0.906f, 0.365f, 0.337f);

    glBegin(GL_TRIANGLES);

    glVertex2f(-0.23f, 0.40f);
    glVertex2f(0.13f, 0.40f);
    glVertex2f(-0.05f, 0.52f);

    glEnd();


    //WINDOWS
    glColor3f(scene3_windowR, scene3_windowG, scene3_windowB);

    glBegin(GL_QUADS);

    glVertex2f(-0.15f, 0.30f);
    glVertex2f(-0.10f, 0.30f);
    glVertex2f(-0.10f, 0.35f);
    glVertex2f(-0.15f, 0.35f);

    glVertex2f(0.00f, 0.30f);
    glVertex2f(0.05f, 0.30f);
    glVertex2f(0.05f, 0.35f);
    glVertex2f(0.00f, 0.35f);

    glVertex2f(-0.15f, 0.20f);
    glVertex2f(-0.10f, 0.20f);
    glVertex2f(-0.10f, 0.25f);
    glVertex2f(-0.15f, 0.25f);

    glVertex2f(0.00f, 0.20f);
    glVertex2f(0.05f, 0.20f);
    glVertex2f(0.05f, 0.25f);
    glVertex2f(0.00f, 0.25f);

    glEnd();


    // DOOR
    glColor3f(0.42f, 0.22f, 0.12f);

    glBegin(GL_QUADS);

    glVertex2f(-0.075f, 0.00f);
    glVertex2f(-0.025f, 0.00f);
    glVertex2f(-0.025f, 0.12f);
    glVertex2f(-0.075f, 0.12f);

    glEnd();



    // HOSPITAL
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(0.20f, 0.00f);
    glVertex2f(0.50f, 0.00f);
    glVertex2f(0.50f, 0.45f);
    glVertex2f(0.20f, 0.45f);

    glEnd();


    //WINDOWS
    glColor3f(scene3_windowR, scene3_windowG, scene3_windowB);

    glBegin(GL_QUADS);

    glVertex2f(0.25f, 0.30f);
    glVertex2f(0.30f, 0.30f);
    glVertex2f(0.30f, 0.35f);
    glVertex2f(0.25f, 0.35f);

    glVertex2f(0.40f, 0.30f);
    glVertex2f(0.45f, 0.30f);
    glVertex2f(0.45f, 0.35f);
    glVertex2f(0.40f, 0.35f);

    glVertex2f(0.25f, 0.20f);
    glVertex2f(0.30f, 0.20f);
    glVertex2f(0.30f, 0.25f);
    glVertex2f(0.25f, 0.25f);

    glVertex2f(0.40f, 0.20f);
    glVertex2f(0.45f, 0.20f);
    glVertex2f(0.45f, 0.25f);
    glVertex2f(0.40f, 0.25f);

    glEnd();


    //DOOR
    glColor3f(0.25f, 0.45f, 0.65f);

    glBegin(GL_QUADS);

    glVertex2f(0.325f, 0.00f);
    glVertex2f(0.385f, 0.00f);
    glVertex2f(0.385f, 0.14f);
    glVertex2f(0.325f, 0.14f);

    glEnd();


    //RED CROSS
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

    glVertex2f(0.32f, 0.35f);
    glVertex2f(0.37f, 0.35f);
    glVertex2f(0.37f, 0.38f);
    glVertex2f(0.32f, 0.38f);

    glVertex2f(0.335f, 0.33f);
    glVertex2f(0.355f, 0.33f);
    glVertex2f(0.355f, 0.40f);
    glVertex2f(0.335f, 0.40f);

    glEnd();



    //RIGHT BUILDING
    glColor3f(0.70f, 0.55f, 0.45f);

    glBegin(GL_QUADS);

    glVertex2f(0.80f, 0.00f);
    glVertex2f(0.98f, 0.00f);
    glVertex2f(0.98f, 0.27f);
    glVertex2f(0.80f, 0.27f);

    glEnd();


    //WINDOWS
    glColor3f(scene3_windowR, scene3_windowG, scene3_windowB);

    glBegin(GL_QUADS);

    glVertex2f(0.82f, 0.15f);
    glVertex2f(0.865f, 0.15f);
    glVertex2f(0.865f, 0.205f);
    glVertex2f(0.82f, 0.205f);

    glVertex2f(0.91f, 0.15f);
    glVertex2f(0.955f, 0.15f);
    glVertex2f(0.955f, 0.205f);
    glVertex2f(0.91f, 0.205f);

    glEnd();


    //DOOR
    glColor3f(0.40f, 0.23f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(0.865f, 0.00f);
    glVertex2f(0.915f, 0.00f);
    glVertex2f(0.915f, 0.11f);
    glVertex2f(0.865f, 0.11f);

    glEnd();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[GRASS]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawGrass()
{
    glColor3f(0.20f, 0.60f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(-1.00f, 0.00f);
    glVertex2f(1.00f, 0.00f);
    glVertex2f(1.00f, 0.018f);
    glVertex2f(-1.00f, 0.018f);

    glEnd();
}

// TREE
void scene3_drawTree()
{
    //TREE BODY
    glColor3f(0.45f, 0.22f, 0.05f);

    glBegin(GL_QUADS);

    glVertex2f(0.635f, 0.00f);
    glVertex2f(0.665f, 0.00f);
    glVertex2f(0.665f, 0.18f);
    glVertex2f(0.635f, 0.18f);

    glEnd();


    //TREE LEAVES
    glPushMatrix();

    glTranslatef(0.65f, 0.15f, 0.0f);
    glRotatef(scene3_windSway, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.65f, -0.15f, 0.0f);


    // BOTTOM
    glColor3f(0.13f, 0.55f, 0.07f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0.52f, 0.12f);
    glVertex2f(0.78f, 0.12f);
    glVertex2f(0.65f, 0.34f);

    glEnd();


    //MIDDLE
    glColor3f(0.18f, 0.65f, 0.09f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0.55f, 0.23f);
    glVertex2f(0.75f, 0.23f);
    glVertex2f(0.65f, 0.42f);

    glEnd();


    //TOP
    glColor3f(0.22f, 0.72f, 0.10f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0.585f, 0.33f);
    glVertex2f(0.715f, 0.33f);
    glVertex2f(0.65f, 0.49f);

    glEnd();


    glPopMatrix();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% [ROAD]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawRoad()
{
    //GROUND
    glColor3f(0.65f, 0.64f, 0.57f);

    glBegin(GL_QUADS);

    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);

    glEnd();


    //ROAD
    glColor3f(0.063f, 0.071f, 0.071f);

    glBegin(GL_QUADS);

    glVertex2f(-1.0f, -0.20f);
    glVertex2f(1.0f, -0.20f);
    glVertex2f(1.0f, -0.70f);
    glVertex2f(-1.0f, -0.70f);

    glEnd();


    //ROAD DIVIDER
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.60f, -0.45f);
    glVertex2f(-0.40f, -0.45f);
    glVertex2f(-0.40f, -0.40f);
    glVertex2f(-0.60f, -0.40f);

    glVertex2f(-0.30f, -0.45f);
    glVertex2f(-0.10f, -0.45f);
    glVertex2f(-0.10f, -0.40f);
    glVertex2f(-0.30f, -0.40f);

    glVertex2f(0.00f, -0.45f);
    glVertex2f(0.20f, -0.45f);
    glVertex2f(0.20f, -0.40f);
    glVertex2f(0.00f, -0.40f);

    glVertex2f(0.30f, -0.45f);
    glVertex2f(0.50f, -0.45f);
    glVertex2f(0.50f, -0.40f);
    glVertex2f(0.30f, -0.40f);

    glVertex2f(0.60f, -0.45f);
    glVertex2f(0.80f, -0.45f);
    glVertex2f(0.80f, -0.40f);
    glVertex2f(0.60f, -0.40f);

    glEnd();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[ZEBRA]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawZebra()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.95f, -0.25f);
    glVertex2f(-0.65f, -0.25f);
    glVertex2f(-0.65f, -0.30f);
    glVertex2f(-0.95f, -0.30f);

    glVertex2f(-0.95f, -0.35f);
    glVertex2f(-0.65f, -0.35f);
    glVertex2f(-0.65f, -0.40f);
    glVertex2f(-0.95f, -0.40f);

    glVertex2f(-0.95f, -0.45f);
    glVertex2f(-0.65f, -0.45f);
    glVertex2f(-0.65f, -0.50f);
    glVertex2f(-0.95f, -0.50f);

    glVertex2f(-0.95f, -0.55f);
    glVertex2f(-0.65f, -0.55f);
    glVertex2f(-0.65f, -0.60f);
    glVertex2f(-0.95f, -0.60f);

    glVertex2f(-0.95f, -0.65f);
    glVertex2f(-0.65f, -0.65f);
    glVertex2f(-0.65f, -0.70f);
    glVertex2f(-0.95f, -0.70f);

    glEnd();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[TRAFFIC LIGHT]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawTrafficLight()
{
    //POLE
    glColor3f(0.30f, 0.30f, 0.30f);

    glBegin(GL_QUADS);

    glVertex2f(-0.625f, -0.20f);
    glVertex2f(-0.610f, -0.20f);
    glVertex2f(-0.610f, 0.02f);
    glVertex2f(-0.625f, 0.02f);

    glEnd();


    //BOX
    glColor3f(0.15f, 0.15f, 0.15f);

    glBegin(GL_QUADS);

    glVertex2f(-0.645f, 0.00f);
    glVertex2f(-0.590f, 0.00f);
    glVertex2f(-0.590f, 0.18f);
    glVertex2f(-0.645f, 0.18f);

    glEnd();


    //RED
    if (scene3_trafficLight == 1)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.25f, 0.0f, 0.0f);

    scene3_drawCircle(-0.6175f, 0.155f, 0.018f, 40);

    //YELLOW
    if (scene3_trafficLight == 2)
        glColor3f(1.0f, 0.85f, 0.0f);
    else
        glColor3f(0.25f, 0.21f, 0.0f);

    scene3_drawCircle(-0.6175f, 0.09f, 0.018f, 40);

    // GREEN
    if (scene3_trafficLight == 0)
        glColor3f(0.0f, 1.0f, 0.20f);
    else
        glColor3f(0.0f, 0.25f, 0.05f);

    scene3_drawCircle(-0.6175f, 0.025f, 0.018f, 40);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[ HUMAN 1 BLUE SHIRT]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_human()
{
    glPushMatrix();


    //HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene3_drawCircle(0.0f, 0.09f, 0.018f, 50);


    //NECK
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.007f, 0.074f);
    glVertex2f(0.007f, 0.074f);
    glVertex2f(0.007f, 0.054f);
    glVertex2f(-0.007f, 0.054f);

    glEnd();


    //HAIR
    glBegin(GL_POLYGON);

    glColor3f(0.05f, 0.05f, 0.05f);

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();


    //SHIRT
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.55f, 0.75f);

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();


    //LEFT ARM
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();


    // RIGHT ARM
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();


    //LEFT LEG
    glPushMatrix();

    glTranslatef(-0.010f, -0.015f, 0.0f);
    glRotatef(scene3_legAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);

    glColor3f(0.10f, 0.10f, 0.10f);

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    glPopMatrix();


    //RIGHT LEG
    glPushMatrix();

    glTranslatef(0.010f, -0.015f, 0.0f);
    glRotatef(-scene3_legAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);

    glColor3f(0.10f, 0.10f, 0.10f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();


    glPopMatrix();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[HUMAN 2]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_human2()
{
    glPushMatrix();


    //HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene3_drawCircle(0.0f, 0.09f, 0.018f, 50);


    //NECK
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);

    glEnd();


    //HAIR
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.05f, 0.05f);

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();


    //SHIRT
    glBegin(GL_POLYGON);

    glColor3f(0.60f, 0.30f, 0.70f);

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();


    //ARMS
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();


    //LEFT LEG
    glPushMatrix();

    glTranslatef(-0.010f, -0.015f, 0.0f);
    glRotatef(scene3_legAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.60f, 0.60f);

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    glPopMatrix();


    //RIGHT LEG
    glPushMatrix();

    glTranslatef(0.010f, -0.015f, 0.0f);
    glRotatef(-scene3_legAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.60f, 0.60f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();


    glPopMatrix();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[HUMAN 3]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_human3()
{
    glPushMatrix();


    //HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene3_drawCircle(0.0f, 0.09f, 0.018f, 50);


    //NECK
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);

    glEnd();


    //HAIR
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.05f, 1.0f);

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();


    //SHIRT
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.55f, 0.75f);

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();


    //ARMS
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();


    //LEFT LEG
    glPushMatrix();

    glTranslatef(-0.010f, -0.015f, 0.0f);
    glRotatef(scene3_legAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);

    glColor3f(0.10f, 0.10f, 0.10f);

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    glPopMatrix();


    //RIGHT LEG
    glPushMatrix();

    glTranslatef(0.010f, -0.015f, 0.0f);
    glRotatef(-scene3_legAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);

    glColor3f(0.10f, 0.10f, 0.10f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();


    glPopMatrix();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[CROSSING HUMAN]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_crossingHuman()
{
    glPushMatrix();


    //HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene3_drawCircle(0.0f, 0.09f, 0.018f, 50);


    //NECK
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.007f, 0.074f);
    glVertex2f(0.007f, 0.074f);
    glVertex2f(0.007f, 0.054f);
    glVertex2f(-0.007f, 0.054f);

    glEnd();


    //HAIR
    glBegin(GL_POLYGON);

    glColor3f(0.05f, 0.05f, 0.05f);

    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);

    glEnd();


    //SHIRT
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.55f, 0.75f);

    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);

    glEnd();


    //ARMS
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.82f, 0.68f);

    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);

    glEnd();


    //LEFT LEG
    glPushMatrix();

    glTranslatef(-0.010f, -0.015f, 0.0f);

    if (scene3_humanMoving)
        glRotatef(scene3_crossingLegAngle, 0.0f, 0.0f, 1.0f);

    glTranslatef(0.010f, 0.015f, 0.0f);


    glBegin(GL_POLYGON);

    glColor3f(0.10f, 0.10f, 0.10f);

    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);

    glEnd();

    glPopMatrix();


    //RIGHT LEG
    glPushMatrix();

    glTranslatef(0.010f, -0.015f, 0.0f);

    if (scene3_humanMoving)
        glRotatef(-scene3_crossingLegAngle, 0.0f, 0.0f, 1.0f);

    glTranslatef(-0.010f, 0.015f, 0.0f);


    glBegin(GL_POLYGON);

    glColor3f(0.10f, 0.10f, 0.10f);

    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 0.0f);

    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);

    glEnd();

    glPopMatrix();


    glPopMatrix();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[RED CAR]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_car1()
{
    // BODY
    glColor3f(0.90f, 0.10f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(-0.14f, -0.05f);
    glVertex2f(0.14f, -0.05f);
    glVertex2f(0.14f, 0.07f);
    glVertex2f(-0.14f, 0.07f);

    glEnd();


    // ROOF
    glColor3f(0.75f, 0.05f, 0.05f);

    glBegin(GL_POLYGON);

    glVertex2f(-0.08f, 0.07f);
    glVertex2f(0.08f, 0.07f);
    glVertex2f(0.04f, 0.16f);
    glVertex2f(-0.04f, 0.16f);

    glEnd();


    // WINDOWS
    glColor3f(0.55f, 0.80f, 0.95f);

    glBegin(GL_QUADS);

    glVertex2f(-0.055f, 0.08f);
    glVertex2f(-0.005f, 0.08f);
    glVertex2f(-0.005f, 0.14f);
    glVertex2f(-0.035f, 0.14f);

    glVertex2f(0.010f, 0.08f);
    glVertex2f(0.060f, 0.08f);
    glVertex2f(0.035f, 0.14f);
    glVertex2f(0.010f, 0.14f);

    glEnd();


    // WHEELS
    glColor3f(0.0f, 0.0f, 0.0f);

    scene3_drawCircle(-0.09f, -0.055f, 0.030f, 40);
    scene3_drawCircle(0.09f, -0.055f, 0.030f, 40);
}

// BLUE CAR
void scene3_car2()
{
    //BODY
    glColor3f(0.05f, 0.35f, 0.90f);

    glBegin(GL_QUADS);

    glVertex2f(-0.16f, -0.05f);
    glVertex2f(0.16f, -0.05f);
    glVertex2f(0.16f, 0.07f);
    glVertex2f(-0.16f, 0.07f);

    glEnd();


    //ROOF
    glColor3f(0.03f, 0.25f, 0.75f);

    glBegin(GL_POLYGON);

    glVertex2f(-0.09f, 0.07f);
    glVertex2f(0.10f, 0.07f);
    glVertex2f(0.05f, 0.17f);
    glVertex2f(-0.045f, 0.17f);

    glEnd();


    //WINDOWS
    glColor3f(0.65f, 0.85f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.065f, 0.085f);
    glVertex2f(-0.010f, 0.085f);
    glVertex2f(-0.010f, 0.145f);
    glVertex2f(-0.040f, 0.145f);

    glVertex2f(0.005f, 0.085f);
    glVertex2f(0.075f, 0.085f);
    glVertex2f(0.045f, 0.145f);
    glVertex2f(0.005f, 0.145f);

    glEnd();


    //WHEELS
    glColor3f(0.0f, 0.0f, 0.0f);

    scene3_drawCircle(-0.10f, -0.055f, 0.030f, 40);
    scene3_drawCircle(0.10f, -0.055f, 0.030f, 40);
}

// YELLOW CAR

void scene3_car3()
{
    //BODY
    glColor3f(1.0f, 0.70f, 0.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.14f, -0.05f);
    glVertex2f(0.14f, -0.05f);
    glVertex2f(0.14f, 0.07f);
    glVertex2f(-0.14f, 0.07f);

    glEnd();


    //ROOF
    glColor3f(0.90f, 0.55f, 0.0f);

    glBegin(GL_POLYGON);

    glVertex2f(-0.09f, 0.07f);
    glVertex2f(0.07f, 0.07f);
    glVertex2f(0.035f, 0.16f);
    glVertex2f(-0.055f, 0.16f);

    glEnd();


    // WINDOWS
    glColor3f(0.60f, 0.85f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.065f, 0.085f);
    glVertex2f(-0.010f, 0.085f);
    glVertex2f(-0.010f, 0.14f);
    glVertex2f(-0.045f, 0.14f);

    glVertex2f(0.005f, 0.085f);
    glVertex2f(0.055f, 0.085f);
    glVertex2f(0.030f, 0.14f);
    glVertex2f(0.005f, 0.14f);

    glEnd();


    //WHEELS
    glColor3f(0.0f, 0.0f, 0.0f);

    scene3_drawCircle(-0.09f, -0.055f, 0.030f, 40);
    scene3_drawCircle(0.09f, -0.055f, 0.030f, 40);
}


// GREEN CAR

void scene3_car4()
{
    //BODY
    glColor3f(0.10f, 0.65f, 0.30f);

    glBegin(GL_QUADS);

    glVertex2f(-0.18f, -0.05f);
    glVertex2f(0.18f, -0.05f);
    glVertex2f(0.18f, 0.12f);
    glVertex2f(-0.18f, 0.12f);

    glEnd();


    //ROOF
    glColor3f(0.08f, 0.55f, 0.25f);

    glBegin(GL_POLYGON);

    glVertex2f(-0.13f, 0.12f);
    glVertex2f(0.07f, 0.12f);
    glVertex2f(0.02f, 0.20f);
    glVertex2f(-0.08f, 0.20f);

    glEnd();


    //WINDOWS
    glColor3f(0.65f, 0.85f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.095f, 0.13f);
    glVertex2f(-0.035f, 0.13f);
    glVertex2f(-0.035f, 0.185f);
    glVertex2f(-0.070f, 0.185f);

    glVertex2f(-0.020f, 0.13f);
    glVertex2f(0.045f, 0.13f);
    glVertex2f(0.015f, 0.185f);
    glVertex2f(-0.020f, 0.185f);

    glEnd();


    //WHEELS
    glColor3f(0.0f, 0.0f, 0.0f);

    scene3_drawCircle(-0.11f, -0.055f, 0.032f, 40);
    scene3_drawCircle(0.11f, -0.055f, 0.032f, 40);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[WIND]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawWind()
{
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);

    for (int i = 0; i < 60; i++)
    {
        glVertex2f(scene3_windLineX[i], scene3_windLineY[i]);
        glVertex2f(scene3_windLineX[i] + 0.05f, scene3_windLineY[i] + 0.03f);
    }

    glEnd();

   glLineWidth(1.0f);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%[RAIN]%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_drawRain()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    for (int i = 0; i < 1000; i++)
    {
        if (i % 3 == 0)
            glColor3f(0.80f, 0.80f, 1.00f);

        else if (i % 3 == 1)
            glColor3f(0.60f, 0.60f, 1.00f);

        else
            glColor3f(0.40f, 0.40f, 0.90f);


        glVertex2f(scene3_rainX[i], scene3_rainY[i]);
        glVertex2f(scene3_rainX[i] - 0.015f, scene3_rainY[i] - 0.06f);
    }

    glEnd();

    //glLineWidth(1.0f);
}


// SNOW

void scene3_drawSnow()
{
    for (int tier = 0; tier < 3; tier++)
    {
        float size;
        float shade;


        if (tier == 0)
        {
            size = 5.0f;
            shade = 1.00f;
        }

        else if (tier == 1)
        {
            size = 3.5f;
            shade = 0.85f;
        }

        else
        {
            size = 2.0f;
            shade = 0.65f;
        }


        glPointSize(size);
        glColor3f(shade, shade, shade);

        glBegin(GL_POINTS);

        for (int i = 0; i < 500; i++)
        {
            if (i % 3 == tier)
            {
                glVertex2f(scene3_snowX[i], scene3_snowY[i]);
            }
        }

        glEnd();
    }

    glPointSize(1.0f);
}

// DISPLAY
void scene3_display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    scene3_drawSky();

    scene3_drawBackgroundCity();

    scene3_drawSunMoon();


    //CLOUD
    scene3_drawCloud(-0.30f, 0.77f, 1.00f);
    scene3_drawCloud(0.30f, 0.83f, 0.80f);
    scene3_drawCloud(0.72f, 0.73f, 0.70f);


    scene3_drawBuildings();

    scene3_drawGrass();

    scene3_drawTree();

    scene3_drawRoad();

    scene3_drawZebra();


    //CROSSING HUMAN
    glPushMatrix();

    glTranslatef(scene3_humanX, scene3_humanY, 0.0f);

    scene3_crossingHuman();

    glPopMatrix();


    //HUMAN 1
    glPushMatrix();

    glTranslatef(scene3_h1x, -0.02f, 0.0f);

    scene3_human();

    glPopMatrix();


    //HUMAN 2
    glPushMatrix();

    glTranslatef(scene3_h2x, -0.05f, 0.0f);

    scene3_human2();

    glPopMatrix();


    //HUMAN 3
    glPushMatrix();

    glTranslatef(scene3_h3x, -0.01f, 0.0f);

    scene3_human3();

    glPopMatrix();


    scene3_drawTrafficLight();


    //RED CAR
    glPushMatrix();

    glTranslatef(scene3_car1X, -0.30f, 0.0f);

    scene3_car1();

    glPopMatrix();


    // BLUE CAR
    glPushMatrix();

    glTranslatef(scene3_car2X, -0.30f, 0.0f);

    scene3_car2();

    glPopMatrix();


    //YELLOW CAR
    glPushMatrix();

    glTranslatef(scene3_car3X, -0.58f, 0.0f);

    scene3_car3();

    glPopMatrix();


    // GREEN CAR
    glPushMatrix();

    glTranslatef(scene3_car4X, -0.58f, 0.0f);

    scene3_car4();

    glPopMatrix();


    if (scene3_rain)
    {
        scene3_drawRain();
    }


    if (scene3_wind)
    {
        scene3_drawWind();
    }


    if (scene3_snow)
    {
        scene3_drawSnow();
    }


    //glutSwapBuffers();
}

// KEYBOARD
void scene3_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // DAY / NIGHT
        case 'v':

            scene3_isNight = !scene3_isNight;

            if (scene3_isNight)
            {
                scene3_skyR1 = 0.02f;
                scene3_skyG1 = 0.02f;
                scene3_skyB1 = 0.08f;

                scene3_skyR2 = 0.05f;
                scene3_skyG2 = 0.05f;
                scene3_skyB2 = 0.12f;

                scene3_bgR = 0.08f;
                scene3_bgG = 0.10f;
                scene3_bgB = 0.16f;

                scene3_windowR = 1.00f;
                scene3_windowG = 0.85f;
                scene3_windowB = 0.25f;
            }
            else
            {
                scene3_skyR1 = 0.50f;
                scene3_skyG1 = 0.85f;
                scene3_skyB1 = 1.00f;

                scene3_skyR2 = 0.80f;
                scene3_skyG2 = 0.93f;
                scene3_skyB2 = 1.00f;

                scene3_bgR = 0.55f;
                scene3_bgG = 0.68f;
                scene3_bgB = 0.76f;

                scene3_windowR = 0.75f;
                scene3_windowG = 0.90f;
                scene3_windowB = 1.00f;
            }

            break;


        // TRAFFIC GREEN
        case 'k':

            scene3_trafficLight = 0;

            break;


        // TRAFFIC RED
        case 'r':

            scene3_trafficLight = 1;

            break;


        // TRAFFIC YELLOW
        case 'y':

            scene3_trafficLight = 2;

            break;


        // HUMAN CROSS
        case 'p':

            if (scene3_trafficLight == 1 && scene3_humanMoving == false)
            {
                scene3_humanMoving = true;
                scene3_crossingLegAngle = 0.0f;
            }

            break;


        // CAR STOP
        case 'M':

            scene3_car1Stop = true;

            break;

        case 'N':

            scene3_car2Stop = true;

            break;

        case 'B':

            scene3_car3Stop = true;

            break;

        case 'V':

            scene3_car4Stop = true;

            break;


        // CAR START
        case 'C':

            scene3_car1Stop = false;

            break;

        case 'X':

            scene3_car2Stop = false;

            break;

        case 'Z':

            scene3_car3Stop = false;

            break;

        case 'A':

            scene3_car4Stop = false;

            break;


        // RAIN START
        case 'f':

            scene3_rain = true;

            break;


        // RAIN STOP
        case 'c':

            scene3_rain = false;

            break;


        // RAIN SPEED UP
        case 'w':

            scene3_rainSpeedMultiplier += 0.2f;

            break;


        // RAIN SPEED DOWN
        case 's':

            if (scene3_rainSpeedMultiplier > 0.2f)
            {
                scene3_rainSpeedMultiplier -= 0.2f;
            }

            break;


        // SNOW START
        case 'n':

            scene3_snow = true;

            break;


        // SNOW STOP
        case 'b':

            scene3_snow = false;

            break;


        // SNOW SPEED UP
        case 'e':

            scene3_snowSpeedMultiplier += 0.2f;

            break;


        // SNOW SPEED DOWN
        case 'd':

            scene3_snowSpeedMultiplier -= 0.2f;

            if (scene3_snowSpeedMultiplier < 0.1f)
            {
                scene3_snowSpeedMultiplier = 0.1f;
            }

            break;


        // WIND START
        case 'g':

            scene3_wind = true;

            break;


        // WIND STOP
        case 'h':

            scene3_wind = false;

            break;
    }


    //glutPostRedisplay();
}

// UPDATE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void scene3_Update() //(int value)
{
    //RED CAR
    if (scene3_car1Stop == false)
    {
        if (scene3_trafficLight == 0)
            scene3_car1X += 0.008f;

        else if (scene3_trafficLight == 2)
            scene3_car1X += 0.003f;

        else
        {
            if (scene3_car1X < -1.12f)
            {
                scene3_car1X += 0.008f;

                if (scene3_car1X > -1.12f)
                    scene3_car1X = -1.12f;
            }

            else if (scene3_car1X > -1.12f)
                scene3_car1X += 0.008f;
        }
    }


    //BLUE CAR
    if (scene3_car2Stop == false)
    {
        if (scene3_trafficLight == 0)
            scene3_car2X += 0.006f;

        else if (scene3_trafficLight == 2)
            scene3_car2X += 0.0025f;

        else
        {
            if (scene3_car2X < -1.47f)
            {
                scene3_car2X += 0.006f;

                if (scene3_car2X > -1.47f)
                    scene3_car2X = -1.47f;
            }

            else if (scene3_car2X > -1.47f)
                scene3_car2X += 0.006f;
        }
    }


    //YELLOW CAR
    if (scene3_car3Stop == false)
    {
        if (scene3_trafficLight == 0)
            scene3_car3X -= 0.007f;

        else if (scene3_trafficLight == 2)
            scene3_car3X -= 0.003f;

        else
        {
            if (scene3_car3X > -0.47f)
            {
                scene3_car3X -= 0.007f;

                if (scene3_car3X < -0.47f)
                    scene3_car3X = -0.47f;
            }

            else if (scene3_car3X < -0.47f)
                scene3_car3X -= 0.007f;
        }
    }


    //GREEN CAR
    if (scene3_car4Stop == false)
    {
        if (scene3_trafficLight == 0)
            scene3_car4X -= 0.005f;

        else if (scene3_trafficLight == 2)
            scene3_car4X -= 0.002f;

        else
        {
            if (scene3_car4X > -0.05f)
            {
                scene3_car4X -= 0.005f;

                if (scene3_car4X < -0.05f)
                    scene3_car4X = -0.05f;
            }

            else if (scene3_car4X < -0.05f)
                scene3_car4X -= 0.005f;
        }
    }


    //CAR RESET
    if (scene3_car1X > 1.30f)
        scene3_car1X = -1.30f;

    if (scene3_car2X > 1.30f)
        scene3_car2X = -1.65f;

    if (scene3_car3X < -1.30f)
        scene3_car3X = 1.30f;

    if (scene3_car4X < -1.30f)
        scene3_car4X = 1.30f;


    //CROSSING HUMAN
    if (scene3_humanMoving)
    {
        scene3_crossingLegAngle += scene3_crossingLegSpeed;


        if (scene3_crossingLegAngle > 25.0f || scene3_crossingLegAngle < -25.0f)
        {
            scene3_crossingLegSpeed = -scene3_crossingLegSpeed;
        }


        //TOP TO BOTTOM
        if (scene3_humanDirection == 0)
        {
            scene3_humanY -= 0.008f;


            if (scene3_humanY <= -0.75f)
            {
                scene3_humanY = -0.75f;

                scene3_humanMoving = false;

                scene3_humanDirection = 1;

                scene3_crossingLegAngle = 0.0f;
            }
        }


        //BOTTOM TO TOP
        else
        {
            scene3_humanY += 0.008f;


            if (scene3_humanY >= -0.02f)
            {
                scene3_humanY = -0.02f;

                scene3_humanMoving = false;

                scene3_humanDirection = 0;

                scene3_crossingLegAngle = 0.0f;
            }
        }
    }


    //NORMAL HUMANS
    if (scene3_h1dir == 0)
        scene3_h1x += scene3_h1speed;
    else
        scene3_h1x -= scene3_h1speed;


    if (scene3_h2dir == 0)
        scene3_h2x += scene3_h2speed;
    else
        scene3_h2x -= scene3_h2speed;


    if (scene3_h3dir == 0)
        scene3_h3x += scene3_h3speed;
    else
        scene3_h3x -= scene3_h3speed;


    if (scene3_h1x > 1.20f)
        scene3_h1x = -1.20f;

    if (scene3_h1x < -1.20f)
        scene3_h1x = 1.20f;


    if (scene3_h2x > 1.20f)
        scene3_h2x = -1.20f;

    if (scene3_h2x < -1.20f)
        scene3_h2x = 1.20f;


    if (scene3_h3x > 1.20f)
        scene3_h3x = -1.20f;

    if (scene3_h3x < -1.20f)
        scene3_h3x = 1.20f;


    //HUMAN LEG
    scene3_legAngle += scene3_legSpeed;


    if (scene3_legAngle > 25.0f || scene3_legAngle < -25.0f)
    {
        scene3_legSpeed = -scene3_legSpeed;
    }


    // CLOUD
    scene3_cloudX += 0.0003f;


    if (scene3_cloudX > 0.60f)
    {
        scene3_cloudX = -0.60f;
    }


  // WIND
   if (scene3_wind)
  {
    scene3_windSway += 0.1f;

    if (scene3_windSway > 2.0f)
        scene3_windSway = -2.0f;

    for (int i = 0; i < 60; i++)
    {
        scene3_windLineX[i] += 0.01f;

        if (scene3_windLineX[i] > 1.0f)
            scene3_windLineX[i] = -1.0f;
    }
  }
 else
  {
    scene3_windSway = 0.0f;
  }
    //RAIN
    if (scene3_rain)
    {
        for (int i = 0; i < 1000; i++)
        {
            scene3_rainY[i] -= scene3_rainSpeed[i] * scene3_rainSpeedMultiplier;

            scene3_rainX[i] -= 0.002f;


            if (scene3_rainX[i] < -1.05f)
            {
                scene3_rainX[i] = 1.05f;
            }


            if (scene3_rainY[i] < -1.0f)
            {
                scene3_rainY[i] = 1.0f;

                scene3_rainX[i] = ((float)rand() / RAND_MAX) * 2.10f - 1.05f;

                scene3_rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
            }
        }
    }


    //SNOW
    if (scene3_snow)
    {
        for (int i = 0; i < 500; i++)
        {
            scene3_snowY[i] -= scene3_snowSpeed[i] * scene3_snowSpeedMultiplier;

            scene3_snowSway[i] += 0.02f;

            scene3_snowX[i] += sin(scene3_snowSway[i]) * 0.0008f;


            if (scene3_snowY[i] < -1.0f)
            {
                scene3_snowY[i] = 1.0f;

                scene3_snowX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

                scene3_snowSpeed[i] = 0.003f + ((float)rand() / RAND_MAX) * 0.006f;
            }
        }
    }
}

#endif

