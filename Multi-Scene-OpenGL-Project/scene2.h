//scene 2

#ifndef SCENE2_H
#define SCENE2_H

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


bool scene2_isNight = false;

// sky colors
float scene2_skyTopR = 0.50f, scene2_skyTopG = 0.80f, scene2_skyTopB = 1.00f;
float scene2_skyBottomR = 0.80f, scene2_skyBottomG = 0.93f, scene2_skyBottomB = 1.00f;

// scene2_cloud color
float scene2_cloudR = 1.0f, scene2_cloudG = 1.0f, scene2_cloudB = 1.0f;

// scene2_rain
bool  scene2_rain = false;
float scene2_rainX[1000];
float scene2_rainY[1000];
float scene2_rainSpeed[1000];
float scene2_rainSpeedMultiplier = 1.0f;

// scene2_snow
bool  scene2_snow = false;
float scene2_snowX[500];
float scene2_snowY[500];
float scene2_snowSpeed[500];
float scene2_snowSpeedMultiplier = 1.0f;

float scene2_cloudMove = 0.0f;
float scene2_car1Move  = 1.3f;
float scene2_car2Move  = 0.0f;
float scene2_car3Move  = -0.5f;
float scene2_car4Move  = 0.7f;

// scene2_pedestrians
float scene2_pedestrianRightMove = 0.0f;
float scene2_pedestrianLeftMove  = 0.0f;

// tscene2_rain movement
float scene2_trainPosition = 0.0f;
float scene2_trainSpeed = 0.005f;

// scene2_wind
bool  scene2_wind = false;
float scene2_windLineX[60];
float scene2_windLineY[60];

// scene2_tree movement scene2_wind
float scene2_treeMove = 0.0f;
float scene2_treeDirection = 0.001f;

// Seeds rain/snow/wind arrays with randomized starting positions and
// nonzero speeds. Without this, all particles start at (0,0) with
// speed 0 and never move, since the per-particle speed is otherwise
// only reassigned once a particle falls below the bottom of the
// screen -- which never happens if its speed is already 0.
void scene2_initializeWeather()
{
    for (int i = 0; i < 1000; i++)
    {
        scene2_rainX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene2_rainY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene2_rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
    }

    for (int i = 0; i < 500; i++)
    {
        scene2_snowX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene2_snowY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene2_snowSpeed[i] = 0.003f + ((float)rand() / RAND_MAX) * 0.006f;
    }

    for (int i = 0; i < 60; i++)
    {
        scene2_windLineX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene2_windLineY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    }
}


void scene2_circle(float centerX, float centerY, float radius)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++)
    {
        float A = i * 2 * 3.1416f / 200;
        float x = centerX + radius * cos(A);
        float y = centerY + radius * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
}


void scene2_road()
{
    // scene2_road
    glColor3f(0.20f, 0.20f, 0.20f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.5f);
        glVertex2f(-1.0f, -0.5f);
    glEnd();

    // b1
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.50f);
        glVertex2f(-0.9f, -0.50f);
        glVertex2f(-0.9f, -0.45f);
        glVertex2f(-1.0f, -0.45f);
    glEnd();


    // w1
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.9f, -0.50f);
        glVertex2f(-0.8f, -0.50f);
        glVertex2f(-0.8f, -0.45f);
        glVertex2f(-0.9f, -0.45f);
    glEnd();


    // b2
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, -0.50f);
        glVertex2f(-0.7f, -0.50f);
        glVertex2f(-0.7f, -0.45f);
        glVertex2f(-0.8f, -0.45f);
    glEnd();


    // w2
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, -0.50f);
        glVertex2f(-0.6f, -0.50f);
        glVertex2f(-0.6f, -0.45f);
        glVertex2f(-0.7f, -0.45f);
    glEnd();


    // b3
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.6f, -0.50f);
        glVertex2f(-0.5f, -0.50f);
        glVertex2f(-0.5f, -0.45f);
        glVertex2f(-0.6f, -0.45f);
    glEnd();


    // w3
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.50f);
        glVertex2f(-0.4f, -0.50f);
        glVertex2f(-0.4f, -0.45f);
        glVertex2f(-0.5f, -0.45f);
    glEnd();


    // b4
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.50f);
        glVertex2f(-0.3f, -0.50f);
        glVertex2f(-0.3f, -0.45f);
        glVertex2f(-0.4f, -0.45f);
    glEnd();


    // w4
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, -0.50f);
        glVertex2f(-0.2f, -0.50f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.3f, -0.45f);
    glEnd();


    // b5
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, -0.50f);
        glVertex2f(-0.1f, -0.50f);
        glVertex2f(-0.1f, -0.45f);
        glVertex2f(-0.2f, -0.45f);
    glEnd();


    // w5
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.50f);
        glVertex2f(0.0f, -0.50f);
        glVertex2f(0.0f, -0.45f);
        glVertex2f(-0.1f, -0.45f);
    glEnd();


    // b6
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, -0.50f);
        glVertex2f(0.1f, -0.50f);
        glVertex2f(0.1f, -0.45f);
        glVertex2f(0.0f, -0.45f);
    glEnd();


    // w6
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.1f, -0.50f);
        glVertex2f(0.2f, -0.50f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.1f, -0.45f);
    glEnd();


    // b7
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, -0.50f);
        glVertex2f(0.3f, -0.50f);
        glVertex2f(0.3f, -0.45f);
        glVertex2f(0.2f, -0.45f);
    glEnd();


    // w7
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.3f, -0.50f);
        glVertex2f(0.4f, -0.50f);
        glVertex2f(0.4f, -0.45f);
        glVertex2f(0.3f, -0.45f);
    glEnd();


    // b8
        glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.4f, -0.50f);
        glVertex2f(0.5f, -0.50f);
        glVertex2f(0.5f, -0.45f);
        glVertex2f(0.4f, -0.45f);
    glEnd();


    // w8
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.5f, -0.50f);
        glVertex2f(0.6f, -0.50f);
        glVertex2f(0.6f, -0.45f);
        glVertex2f(0.5f, -0.45f);
    glEnd();


    // b9
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.6f, -0.50f);
        glVertex2f(0.7f, -0.50f);
        glVertex2f(0.7f, -0.45f);
        glVertex2f(0.6f, -0.45f);
    glEnd();


    // w9
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.7f, -0.50f);
        glVertex2f(0.8f, -0.50f);
        glVertex2f(0.8f, -0.45f);
        glVertex2f(0.7f, -0.45f);
    glEnd();


    // b10
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.8f, -0.50f);
        glVertex2f(0.9f, -0.50f);
        glVertex2f(0.9f, -0.45f);
        glVertex2f(0.8f, -0.45f);
    glEnd();


    // w10
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.9f, -0.50f);
        glVertex2f(1.0f, -0.50f);
        glVertex2f(1.0f, -0.45f);
        glVertex2f(0.9f, -0.45f);
    glEnd();

    // scene2_road dashes = 10
    glColor3f(1.0f, 1.0f, 1.0f);


    // d1
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.75f);
        glVertex2f(-0.9f, -0.75f);
        glVertex2f(-0.9f, -0.72f);
        glVertex2f(-1.0f, -0.72f);
    glEnd();


    // d2
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, -0.75f);
        glVertex2f(-0.7f, -0.75f);
        glVertex2f(-0.7f, -0.72f);
        glVertex2f(-0.8f, -0.72f);
    glEnd();


    // d3
    glBegin(GL_POLYGON);
        glVertex2f(-0.6f, -0.75f);
        glVertex2f(-0.5f, -0.75f);
        glVertex2f(-0.5f, -0.72f);
        glVertex2f(-0.6f, -0.72f);
    glEnd();


    // d4
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.75f);
        glVertex2f(-0.3f, -0.75f);
        glVertex2f(-0.3f, -0.72f);
        glVertex2f(-0.4f, -0.72f);
    glEnd();


    // d5
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, -0.75f);
        glVertex2f(-0.1f, -0.75f);
        glVertex2f(-0.1f, -0.72f);
        glVertex2f(-0.2f, -0.72f);
    glEnd();


    // d6
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, -0.75f);
        glVertex2f(0.1f, -0.75f);
        glVertex2f(0.1f, -0.72f);
        glVertex2f(0.0f, -0.72f);
    glEnd();


    // d7
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, -0.75f);
        glVertex2f(0.3f, -0.75f);
        glVertex2f(0.3f, -0.72f);
        glVertex2f(0.2f, -0.72f);
    glEnd();


    // d8
    glBegin(GL_POLYGON);
        glVertex2f(0.4f, -0.75f);
        glVertex2f(0.5f, -0.75f);
        glVertex2f(0.5f, -0.72f);
        glVertex2f(0.4f, -0.72f);
    glEnd();


    // d9
    glBegin(GL_POLYGON);
        glVertex2f(0.6f, -0.75f);
        glVertex2f(0.7f, -0.75f);
        glVertex2f(0.7f, -0.72f);
        glVertex2f(0.6f, -0.72f);
    glEnd();


    // d10
    glBegin(GL_POLYGON);
        glVertex2f(0.8f, -0.75f);
        glVertex2f(0.9f, -0.75f);
        glVertex2f(0.9f, -0.72f);
        glVertex2f(0.8f, -0.72f);
    glEnd();

}


    // car - 1

void scene2_car1()
{
    // car - 1 main Body
   glColor3f(1.0f, 0.45f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.75f, -0.6f);
        glVertex2f(-0.5f, -0.6f);
        glVertex2f(-0.5f, -0.55f);
        glVertex2f(-0.75f, -0.55f);
    glEnd();


    // car - 1 roof
    glColor3f(1.0f, 0.45f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.70f, -0.55f);
        glVertex2f(-0.66f, -0.49f);
        glVertex2f(-0.59f, -0.49f);
        glVertex2f(-0.55f, -0.55f);
    glEnd();


    // car - 1 left scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.685f, -0.545f);
        glVertex2f(-0.655f, -0.50f);
        glVertex2f(-0.63f, -0.50f);
        glVertex2f(-0.63f, -0.545f);
    glEnd();


    // car - 1  right scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.625f, -0.545f);
        glVertex2f(-0.625f, -0.50f);
        glVertex2f(-0.595f, -0.50f);
        glVertex2f(-0.565f, -0.545f);
    glEnd();


    // car - 1 left wheel

    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(-0.69f, -0.63f, 0.030f);

    // car 1 - left wheel center

    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(-0.69f, -0.63f, 0.012f);


    // car 1 - right wheel

    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(-0.57f, -0.63f, 0.030f);

    // car - 1 right wheel center
    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(-0.57f, -0.63f, 0.012f);

}

    // Car 2
    void scene2_car2()
    {

    // Main Body
    glColor3f(0.55f, 0.80f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(0.35f, -0.91f);
        glVertex2f(0.6f, -0.91f);
        glVertex2f(0.6f, -0.83f);
        glVertex2f(0.35f, -0.83f);
    glEnd();


    // Roof
    glColor3f(0.55f, 0.80f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(0.40f, -0.83f);
        glVertex2f(0.44f, -0.77f);
        glVertex2f(0.51f, -0.77f);
        glVertex2f(0.55f, -0.83f);
    glEnd();


    // Left scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.415f, -0.825f);
        glVertex2f(0.445f, -0.78f);
        glVertex2f(0.47f, -0.78f);
        glVertex2f(0.47f, -0.825f);
    glEnd();


    // Right scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.475f, -0.825f);
        glVertex2f(0.475f, -0.78f);
        glVertex2f(0.505f, -0.78f);
        glVertex2f(0.535f, -0.825f);
    glEnd();


    // Left wheel
    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(0.41f, -0.91f, 0.030f);


    // Right wheel

    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(0.53f, -0.91f, 0.030f);


    // left wheel center

    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(0.41f, -0.91f, 0.012f);


    // right wheel center

    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(0.53f, -0.91f, 0.012f);
}

    // Car 3

void scene2_car3()
{
    // car - 3 main Body
    glColor3f(0.15f, 0.35f, 0.85f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.75f, -0.6f);
        glVertex2f(-0.5f, -0.6f);
        glVertex2f(-0.5f, -0.55f);
        glVertex2f(-0.75f, -0.55f);
    glEnd();


    // car - 3 roof
    glColor3f(0.45f, 0.60f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.70f, -0.55f);
        glVertex2f(-0.66f, -0.49f);
        glVertex2f(-0.59f, -0.49f);
        glVertex2f(-0.55f, -0.55f);
    glEnd();


    // car - 3 left scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.685f, -0.545f);
        glVertex2f(-0.655f, -0.50f);
        glVertex2f(-0.63f, -0.50f);
        glVertex2f(-0.63f, -0.545f);
    glEnd();


    // car - 3  right scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.625f, -0.545f);
        glVertex2f(-0.625f, -0.50f);
        glVertex2f(-0.595f, -0.50f);
        glVertex2f(-0.565f, -0.545f);
    glEnd();


    // car - 3 left wheel

    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(-0.69f, -0.63f, 0.030f);

    // car 3 - left wheel center

    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(-0.69f, -0.63f, 0.012f);


    // car 3 - right wheel

    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(-0.57f, -0.63f, 0.030f);

    // car - 3 right wheel center
    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(-0.57f, -0.63f, 0.012f);

}

// Car 4
void scene2_car4()
{
    // Main Body
    glColor3f(0.95f, 0.60f, 0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(0.35f, -0.91f);
        glVertex2f(0.6f, -0.91f);
        glVertex2f(0.6f, -0.83f);
        glVertex2f(0.35f, -0.83f);
    glEnd();


    // Roof
    glColor3f(0.95f, 0.60f, 0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(0.40f, -0.83f);
        glVertex2f(0.44f, -0.77f);
        glVertex2f(0.51f, -0.77f);
        glVertex2f(0.55f, -0.83f);
    glEnd();


    // Left scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.415f, -0.825f);
        glVertex2f(0.445f, -0.78f);
        glVertex2f(0.47f, -0.78f);
        glVertex2f(0.47f, -0.825f);
    glEnd();


    // Right scene2_window
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.475f, -0.825f);
        glVertex2f(0.475f, -0.78f);
        glVertex2f(0.505f, -0.78f);
        glVertex2f(0.535f, -0.825f);
    glEnd();


    // Left wheel
    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(0.41f, -0.91f, 0.030f);


    // Right wheel
    glColor3f(0.08f, 0.08f, 0.08f);
    scene2_circle(0.53f, -0.91f, 0.030f);


    // left wheel center
    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(0.41f, -0.91f, 0.012f);


    // right wheel center
    glColor3f(0.35f, 0.35f, 0.35f);
    scene2_circle(0.53f, -0.91f, 0.012f);
}



void scene2_building()
{
    // scene2_building 1
    glColor3f(0.48f,0.47f,0.48f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, 0.15f);
        glVertex2f(-0.833f, 0.15f);
        glVertex2f(-0.833f, 0.75f);
        glVertex2f(-1.0f, 0.75f);
    glEnd();

    glColor3f(0.31f,0.30f,0.29f);

    // 1 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(-0.965f, 0.220f);
        glVertex2f(-0.930f, 0.220f);
        glVertex2f(-0.930f, 0.275f);
        glVertex2f(-0.965f, 0.275f);
    glEnd();

    // 1 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(-0.965f, 0.320f);
        glVertex2f(-0.930f, 0.320f);
        glVertex2f(-0.930f, 0.375f);
        glVertex2f(-0.965f, 0.375f);
    glEnd();

    // 1 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(-0.965f, 0.420f);
        glVertex2f(-0.930f, 0.420f);
        glVertex2f(-0.930f, 0.475f);
        glVertex2f(-0.965f, 0.475f);
    glEnd();

    // 1 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(-0.965f, 0.520f);
        glVertex2f(-0.930f, 0.520f);
        glVertex2f(-0.930f, 0.575f);
        glVertex2f(-0.965f, 0.575f);
    glEnd();

    // 1 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(-0.965f, 0.620f);
        glVertex2f(-0.930f, 0.620f);
        glVertex2f(-0.930f, 0.675f);
        glVertex2f(-0.965f, 0.675f);
    glEnd();

    // 1 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(-0.907f, 0.220f);
        glVertex2f(-0.872f, 0.220f);
        glVertex2f(-0.872f, 0.275f);
        glVertex2f(-0.907f, 0.275f);
    glEnd();

    // 1 scene2_window 7
    glBegin(GL_POLYGON);
        glVertex2f(-0.907f, 0.320f);
        glVertex2f(-0.872f, 0.320f);
        glVertex2f(-0.872f, 0.375f);
        glVertex2f(-0.907f, 0.375f);
    glEnd();

    // 1 scene2_window 8
    glBegin(GL_POLYGON);
        glVertex2f(-0.907f, 0.420f);
        glVertex2f(-0.872f, 0.420f);
        glVertex2f(-0.872f, 0.475f);
        glVertex2f(-0.907f, 0.475f);
    glEnd();

    // 1 scene2_window 9
    glBegin(GL_POLYGON);
        glVertex2f(-0.907f, 0.520f);
        glVertex2f(-0.872f, 0.520f);
        glVertex2f(-0.872f, 0.575f);
        glVertex2f(-0.907f, 0.575f);
    glEnd();

    // 1 scene2_window 10
    glBegin(GL_POLYGON);
        glVertex2f(-0.907f, 0.620f);
        glVertex2f(-0.872f, 0.620f);
        glVertex2f(-0.872f, 0.675f);
        glVertex2f(-0.907f, 0.675f);
    glEnd();



    // scene2_building 2

    glColor3f(0.55f,0.55f,0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.833f, 0.15f);
        glVertex2f(-0.668f, 0.15f);
        glVertex2f(-0.668f, 0.52f);
        glVertex2f(-0.833f, 0.52f);
    glEnd();

    glColor3f(0.40f,0.40f,0.40f);

    // 2 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(-0.800f, 0.220f);
        glVertex2f(-0.765f, 0.220f);
        glVertex2f(-0.765f, 0.275f);
        glVertex2f(-0.800f, 0.275f);
    glEnd();

    // 2 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(-0.800f, 0.320f);
        glVertex2f(-0.765f, 0.320f);
        glVertex2f(-0.765f, 0.375f);
        glVertex2f(-0.800f, 0.375f);
    glEnd();

    // 2 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(-0.800f, 0.420f);
        glVertex2f(-0.765f, 0.420f);
        glVertex2f(-0.765f, 0.475f);
        glVertex2f(-0.800f, 0.475f);
    glEnd();

    // 2 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(-0.742f, 0.220f);
        glVertex2f(-0.707f, 0.220f);
        glVertex2f(-0.707f, 0.275f);
        glVertex2f(-0.742f, 0.275f);
    glEnd();

    // 2 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(-0.742f, 0.320f);
        glVertex2f(-0.707f, 0.320f);
        glVertex2f(-0.707f, 0.375f);
        glVertex2f(-0.742f, 0.375f);
    glEnd();

    // 2 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(-0.742f, 0.420f);
        glVertex2f(-0.707f, 0.420f);
        glVertex2f(-0.707f, 0.475f);
        glVertex2f(-0.742f, 0.475f);
    glEnd();



    // scene2_building 3

    glColor3f(0.85f,0.68f,0.52f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.550f, 0.15f);
        glVertex2f(-0.347f, 0.15f);
        glVertex2f(-0.347f, 0.63f);
        glVertex2f(-0.550f, 0.63f);
    glEnd();

    glColor3f(0.49f,0.34f,0.26f);

    // 3 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(-0.525f, 0.220f);
        glVertex2f(-0.497f, 0.220f);
        glVertex2f(-0.497f, 0.262f);
        glVertex2f(-0.525f, 0.262f);
    glEnd();

    // 3 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(-0.525f, 0.285f);
        glVertex2f(-0.497f, 0.285f);
        glVertex2f(-0.497f, 0.327f);
        glVertex2f(-0.525f, 0.327f);
    glEnd();

    // 3 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(-0.525f, 0.350f);
        glVertex2f(-0.497f, 0.350f);
        glVertex2f(-0.497f, 0.392f);
        glVertex2f(-0.525f, 0.392f);
    glEnd();

    // 3 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(-0.525f, 0.415f);
        glVertex2f(-0.497f, 0.415f);
        glVertex2f(-0.497f, 0.457f);
        glVertex2f(-0.525f, 0.457f);
    glEnd();

    // 3 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(-0.525f, 0.480f);
        glVertex2f(-0.497f, 0.480f);
        glVertex2f(-0.497f, 0.522f);
        glVertex2f(-0.525f, 0.522f);
    glEnd();

    // 3 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(-0.525f, 0.545f);
        glVertex2f(-0.497f, 0.545f);
        glVertex2f(-0.497f, 0.587f);
        glVertex2f(-0.525f, 0.587f);
    glEnd();

    // 3 scene2_window 7
    glBegin(GL_POLYGON);
        glVertex2f(-0.480f, 0.220f);
        glVertex2f(-0.452f, 0.220f);
        glVertex2f(-0.452f, 0.262f);
        glVertex2f(-0.480f, 0.262f);
    glEnd();

    // 3 scene2_window 8
    glBegin(GL_POLYGON);
        glVertex2f(-0.480f, 0.285f);
        glVertex2f(-0.452f, 0.285f);
        glVertex2f(-0.452f, 0.327f);
        glVertex2f(-0.480f, 0.327f);
    glEnd();

    // 3 scene2_window 9
    glBegin(GL_POLYGON);
        glVertex2f(-0.480f, 0.350f);
        glVertex2f(-0.452f, 0.350f);
        glVertex2f(-0.452f, 0.392f);
        glVertex2f(-0.480f, 0.392f);
    glEnd();

    // 3 scene2_window 10
    glBegin(GL_POLYGON);
        glVertex2f(-0.480f, 0.415f);
        glVertex2f(-0.452f, 0.415f);
        glVertex2f(-0.452f, 0.457f);
        glVertex2f(-0.480f, 0.457f);
    glEnd();

    // 3 scene2_window 11
    glBegin(GL_POLYGON);
        glVertex2f(-0.480f, 0.480f);
        glVertex2f(-0.452f, 0.480f);
        glVertex2f(-0.452f, 0.522f);
        glVertex2f(-0.480f, 0.522f);
    glEnd();

    // 3 scene2_window 12
    glBegin(GL_POLYGON);
        glVertex2f(-0.480f, 0.545f);
        glVertex2f(-0.452f, 0.545f);
        glVertex2f(-0.452f, 0.587f);
        glVertex2f(-0.480f, 0.587f);
    glEnd();

    // 3 scene2_window 13
    glBegin(GL_POLYGON);
        glVertex2f(-0.435f, 0.220f);
        glVertex2f(-0.407f, 0.220f);
        glVertex2f(-0.407f, 0.262f);
        glVertex2f(-0.435f, 0.262f);
    glEnd();

    // 3 scene2_window 14
    glBegin(GL_POLYGON);
        glVertex2f(-0.435f, 0.285f);
        glVertex2f(-0.407f, 0.285f);
        glVertex2f(-0.407f, 0.327f);
        glVertex2f(-0.435f, 0.327f);
    glEnd();

    // 3 scene2_window 15
    glBegin(GL_POLYGON);
        glVertex2f(-0.435f, 0.350f);
        glVertex2f(-0.407f, 0.350f);
        glVertex2f(-0.407f, 0.392f);
        glVertex2f(-0.435f, 0.392f);
    glEnd();

    // 3 scene2_window 16
    glBegin(GL_POLYGON);
        glVertex2f(-0.435f, 0.415f);
        glVertex2f(-0.407f, 0.415f);
        glVertex2f(-0.407f, 0.457f);
        glVertex2f(-0.435f, 0.457f);
    glEnd();

    // 3 scene2_window 17
    glBegin(GL_POLYGON);
        glVertex2f(-0.435f, 0.480f);
        glVertex2f(-0.407f, 0.480f);
        glVertex2f(-0.407f, 0.522f);
        glVertex2f(-0.435f, 0.522f);
    glEnd();

    // 3 scene2_window 18
    glBegin(GL_POLYGON);
        glVertex2f(-0.435f, 0.545f);
        glVertex2f(-0.407f, 0.545f);
        glVertex2f(-0.407f, 0.587f);
        glVertex2f(-0.435f, 0.587f);
    glEnd();



    // scene2_building 4

    glColor3f(0.40f,0.43f,0.58f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.259f, 0.15f);
        glVertex2f(-0.089f, 0.15f);
        glVertex2f(-0.089f, 0.51f);
        glVertex2f(-0.259f, 0.51f);
    glEnd();

    glColor3f(0.26f,0.28f,0.38f);

    // 4 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(-0.238f, 0.170f);
        glVertex2f(-0.218f, 0.170f);
        glVertex2f(-0.218f, 0.490f);
        glVertex2f(-0.238f, 0.490f);
    glEnd();

    // 4 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(-0.200f, 0.170f);
        glVertex2f(-0.180f, 0.170f);
        glVertex2f(-0.180f, 0.490f);
        glVertex2f(-0.200f, 0.490f);
    glEnd();

    // 4 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(-0.162f, 0.170f);
        glVertex2f(-0.142f, 0.170f);
        glVertex2f(-0.142f, 0.490f);
        glVertex2f(-0.162f, 0.490f);
    glEnd();

    // 4 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(-0.124f, 0.170f);
        glVertex2f(-0.104f, 0.170f);
        glVertex2f(-0.104f, 0.490f);
        glVertex2f(-0.124f, 0.490f);
    glEnd();



    // scene2_building 5

    glColor3f(0.125f,0.463f,0.553f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.078f, 0.15f);
        glVertex2f(0.158f, 0.15f);
        glVertex2f(0.158f, 0.63f);
        glVertex2f(-0.078f, 0.63f);
    glEnd();

    glColor3f(0.41f,0.75f,0.82f);

    // 5 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(-0.060f, 0.200f);
        glVertex2f(0.140f, 0.200f);
        glVertex2f(0.140f, 0.238f);
        glVertex2f(-0.060f, 0.238f);
    glEnd();

    // 5 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(-0.060f, 0.275f);
        glVertex2f(0.140f, 0.275f);
        glVertex2f(0.140f, 0.313f);
        glVertex2f(-0.060f, 0.313f);
    glEnd();

    // 5 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(-0.060f, 0.350f);
        glVertex2f(0.140f, 0.350f);
        glVertex2f(0.140f, 0.388f);
        glVertex2f(-0.060f, 0.388f);
    glEnd();

    // 5 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(-0.060f, 0.425f);
        glVertex2f(0.140f, 0.425f);
        glVertex2f(0.140f, 0.463f);
        glVertex2f(-0.060f, 0.463f);
    glEnd();

    // 5 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(-0.060f, 0.500f);
        glVertex2f(0.140f, 0.500f);
        glVertex2f(0.140f, 0.538f);
        glVertex2f(-0.060f, 0.538f);
    glEnd();

    // 5 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(-0.060f, 0.575f);
        glVertex2f(0.140f, 0.575f);
        glVertex2f(0.140f, 0.613f);
        glVertex2f(-0.060f, 0.613f);
    glEnd();



    // scene2_building 6
    glColor3f(0.47f,0.38f,0.45f);
    glBegin(GL_POLYGON);
        glVertex2f(0.237f, 0.15f);
        glVertex2f(0.391f, 0.15f);
        glVertex2f(0.391f, 0.52f);
        glVertex2f(0.237f, 0.52f);
    glEnd();

    glColor3f(0.33f,0.27f,0.31f);

    // 6 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(0.250f, 0.200f);
        glVertex2f(0.276f, 0.200f);
        glVertex2f(0.276f, 0.255f);
        glVertex2f(0.250f, 0.255f);
    glEnd();

    // 6 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(0.250f, 0.300f);
        glVertex2f(0.276f, 0.300f);
        glVertex2f(0.276f, 0.355f);
        glVertex2f(0.250f, 0.355f);
    glEnd();

    // 6 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(0.250f, 0.400f);
        glVertex2f(0.276f, 0.400f);
        glVertex2f(0.276f, 0.455f);
        glVertex2f(0.250f, 0.455f);
    glEnd();

    // 6 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(0.298f, 0.200f);
        glVertex2f(0.324f, 0.200f);
        glVertex2f(0.324f, 0.255f);
        glVertex2f(0.298f, 0.255f);
    glEnd();

    // 6 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(0.298f, 0.300f);
        glVertex2f(0.324f, 0.300f);
        glVertex2f(0.324f, 0.355f);
        glVertex2f(0.298f, 0.355f);
    glEnd();

    // 6 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(0.298f, 0.400f);
        glVertex2f(0.324f, 0.400f);
        glVertex2f(0.324f, 0.455f);
        glVertex2f(0.298f, 0.455f);
    glEnd();

    // 6 scene2_window 7
    glBegin(GL_POLYGON);
        glVertex2f(0.346f, 0.200f);
        glVertex2f(0.372f, 0.200f);
        glVertex2f(0.372f, 0.255f);
        glVertex2f(0.346f, 0.255f);
    glEnd();

    // 6 scene2_window 8
    glBegin(GL_POLYGON);
        glVertex2f(0.346f, 0.300f);
        glVertex2f(0.372f, 0.300f);
        glVertex2f(0.372f, 0.355f);
        glVertex2f(0.346f, 0.355f);
    glEnd();

    // 6 scene2_window 9
    glBegin(GL_POLYGON);
        glVertex2f(0.346f, 0.400f);
        glVertex2f(0.372f, 0.400f);
        glVertex2f(0.372f, 0.455f);
        glVertex2f(0.346f, 0.455f);
    glEnd();

    // scene2_building 7

    glColor3f(0.88f,0.675f,0.235f);
    glBegin(GL_POLYGON);
        glVertex2f(0.564f, 0.15f);
        glVertex2f(0.742f, 0.15f);
        glVertex2f(0.742f, 0.60f);
        glVertex2f(0.564f, 0.60f);
    glEnd();


    glColor3f(0.58f,0.467f,0.235f);

    // 7 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(0.588f, 0.200f);
        glVertex2f(0.614f, 0.200f);
        glVertex2f(0.614f, 0.250f);
        glVertex2f(0.588f, 0.250f);
    glEnd();

    // 7 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(0.588f, 0.270f);
        glVertex2f(0.614f, 0.270f);
        glVertex2f(0.614f, 0.320f);
        glVertex2f(0.588f, 0.320f);
    glEnd();

    // 7 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(0.588f, 0.340f);
        glVertex2f(0.614f, 0.340f);
        glVertex2f(0.614f, 0.390f);
        glVertex2f(0.588f, 0.390f);
    glEnd();

    // 7 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(0.588f, 0.410f);
        glVertex2f(0.614f, 0.410f);
        glVertex2f(0.614f, 0.460f);
        glVertex2f(0.588f, 0.460f);
    glEnd();

    // 7 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(0.588f, 0.480f);
        glVertex2f(0.614f, 0.480f);
        glVertex2f(0.614f, 0.530f);
        glVertex2f(0.588f, 0.530f);
    glEnd();

    // 7 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(0.636f, 0.200f);
        glVertex2f(0.662f, 0.200f);
        glVertex2f(0.662f, 0.250f);
        glVertex2f(0.636f, 0.250f);
    glEnd();

    // 7 scene2_window 7
    glBegin(GL_POLYGON);
        glVertex2f(0.636f, 0.270f);
        glVertex2f(0.662f, 0.270f);
        glVertex2f(0.662f, 0.320f);
        glVertex2f(0.636f, 0.320f);
    glEnd();

    // 7 scene2_window 8
    glBegin(GL_POLYGON);
        glVertex2f(0.636f, 0.340f);
        glVertex2f(0.662f, 0.340f);
        glVertex2f(0.662f, 0.390f);
        glVertex2f(0.636f, 0.390f);
    glEnd();

    // 7 scene2_window 9
    glBegin(GL_POLYGON);
        glVertex2f(0.636f, 0.410f);
        glVertex2f(0.662f, 0.410f);
        glVertex2f(0.662f, 0.460f);
        glVertex2f(0.636f, 0.460f);
    glEnd();

    // 7 scene2_window 10
    glBegin(GL_POLYGON);
        glVertex2f(0.636f, 0.480f);
        glVertex2f(0.662f, 0.480f);
        glVertex2f(0.662f, 0.530f);
        glVertex2f(0.636f, 0.530f);
    glEnd();

    // 7 scene2_window 11
    glBegin(GL_POLYGON);
        glVertex2f(0.684f, 0.200f);
        glVertex2f(0.710f, 0.200f);
        glVertex2f(0.710f, 0.250f);
        glVertex2f(0.684f, 0.250f);
    glEnd();

    // 7 scene2_window 12
    glBegin(GL_POLYGON);
        glVertex2f(0.684f, 0.270f);
        glVertex2f(0.710f, 0.270f);
        glVertex2f(0.710f, 0.320f);
        glVertex2f(0.684f, 0.320f);
    glEnd();

    // 7 scene2_window 13
    glBegin(GL_POLYGON);
        glVertex2f(0.684f, 0.340f);
        glVertex2f(0.710f, 0.340f);
        glVertex2f(0.710f, 0.390f);
        glVertex2f(0.684f, 0.390f);
    glEnd();

    // 7 scene2_window 14
    glBegin(GL_POLYGON);
        glVertex2f(0.684f, 0.410f);
        glVertex2f(0.710f, 0.410f);
        glVertex2f(0.710f, 0.460f);
        glVertex2f(0.684f, 0.460f);
    glEnd();

    // 7 scene2_window 15
    glBegin(GL_POLYGON);
        glVertex2f(0.684f, 0.480f);
        glVertex2f(0.710f, 0.480f);
        glVertex2f(0.710f, 0.530f);
        glVertex2f(0.684f, 0.530f);
    glEnd();



    // scene2_building 8

    glColor3f(0.627f,0.322f,0.259f);
    glBegin(GL_POLYGON);
        glVertex2f(0.827f, 0.15f);
        glVertex2f(1.00f, 0.15f);
        glVertex2f(1.00f, 0.66f);
        glVertex2f(0.827f, 0.66f);
    glEnd();

    glColor3f(0.43f,0.23f,0.18f);

    // 8 scene2_window 1
    glBegin(GL_POLYGON);
        glVertex2f(0.850f, 0.190f);
        glVertex2f(0.878f, 0.190f);
        glVertex2f(0.878f, 0.245f);
        glVertex2f(0.850f, 0.245f);
    glEnd();

    // 8 scene2_window 2
    glBegin(GL_POLYGON);
        glVertex2f(0.850f, 0.280f);
        glVertex2f(0.878f, 0.280f);
        glVertex2f(0.878f, 0.335f);
        glVertex2f(0.850f, 0.335f);
    glEnd();

    // 8 scene2_window 3
    glBegin(GL_POLYGON);
        glVertex2f(0.850f, 0.370f);
        glVertex2f(0.878f, 0.370f);
        glVertex2f(0.878f, 0.425f);
        glVertex2f(0.850f, 0.425f);
    glEnd();

    // 8 scene2_window 4
    glBegin(GL_POLYGON);
        glVertex2f(0.850f, 0.460f);
        glVertex2f(0.878f, 0.460f);
        glVertex2f(0.878f, 0.515f);
        glVertex2f(0.850f, 0.515f);
    glEnd();

    // 8 scene2_window 5
    glBegin(GL_POLYGON);
        glVertex2f(0.850f, 0.550f);
        glVertex2f(0.878f, 0.550f);
        glVertex2f(0.878f, 0.605f);
        glVertex2f(0.850f, 0.605f);
    glEnd();

    // 8 scene2_window 6
    glBegin(GL_POLYGON);
        glVertex2f(0.888f, 0.190f);
        glVertex2f(0.916f, 0.190f);
        glVertex2f(0.916f, 0.245f);
        glVertex2f(0.888f, 0.245f);
    glEnd();

    // 8 scene2_window 7
    glBegin(GL_POLYGON);
        glVertex2f(0.888f, 0.280f);
        glVertex2f(0.916f, 0.280f);
        glVertex2f(0.916f, 0.335f);
        glVertex2f(0.888f, 0.335f);
    glEnd();

    // 8 scene2_window 8
    glBegin(GL_POLYGON);
        glVertex2f(0.888f, 0.370f);
        glVertex2f(0.916f, 0.370f);
        glVertex2f(0.916f, 0.425f);
        glVertex2f(0.888f, 0.425f);
    glEnd();

    // 8 scene2_window 9
    glBegin(GL_POLYGON);
        glVertex2f(0.888f, 0.460f);
        glVertex2f(0.916f, 0.460f);
        glVertex2f(0.916f, 0.515f);
        glVertex2f(0.888f, 0.515f);
    glEnd();

    // 8 scene2_window 10
    glBegin(GL_POLYGON);
        glVertex2f(0.888f, 0.550f);
        glVertex2f(0.916f, 0.550f);
        glVertex2f(0.916f, 0.605f);
        glVertex2f(0.888f, 0.605f);
    glEnd();

    // 8 scene2_window 11
    glBegin(GL_POLYGON);
        glVertex2f(0.926f, 0.190f);
        glVertex2f(0.954f, 0.190f);
        glVertex2f(0.954f, 0.245f);
        glVertex2f(0.926f, 0.245f);
    glEnd();

    // 8 scene2_window 12
    glBegin(GL_POLYGON);
        glVertex2f(0.926f, 0.280f);
        glVertex2f(0.954f, 0.280f);
        glVertex2f(0.954f, 0.335f);
        glVertex2f(0.926f, 0.335f);
    glEnd();

    // 8 scene2_window 13
    glBegin(GL_POLYGON);
        glVertex2f(0.926f, 0.370f);
        glVertex2f(0.954f, 0.370f);
        glVertex2f(0.954f, 0.425f);
        glVertex2f(0.926f, 0.425f);
    glEnd();

    // 8 scene2_window 14
    glBegin(GL_POLYGON);
        glVertex2f(0.926f, 0.460f);
        glVertex2f(0.954f, 0.460f);
        glVertex2f(0.954f, 0.515f);
        glVertex2f(0.926f, 0.515f);
    glEnd();

    // 8 scene2_window 15
    glBegin(GL_POLYGON);
        glVertex2f(0.926f, 0.550f);
        glVertex2f(0.954f, 0.550f);
        glVertex2f(0.954f, 0.605f);
        glVertex2f(0.926f, 0.605f);
    glEnd();

    // 8 scene2_window 16
    glBegin(GL_POLYGON);
        glVertex2f(0.964f, 0.190f);
        glVertex2f(0.992f, 0.190f);
        glVertex2f(0.992f, 0.245f);
        glVertex2f(0.964f, 0.245f);
    glEnd();

    // 8 scene2_window 17
    glBegin(GL_POLYGON);
        glVertex2f(0.964f, 0.280f);
        glVertex2f(0.992f, 0.280f);
        glVertex2f(0.992f, 0.335f);
        glVertex2f(0.964f, 0.335f);
    glEnd();

    // 8 scene2_window 18
    glBegin(GL_POLYGON);
        glVertex2f(0.964f, 0.370f);
        glVertex2f(0.992f, 0.370f);
        glVertex2f(0.992f, 0.425f);
        glVertex2f(0.964f, 0.425f);
    glEnd();

    // 8 scene2_window 19
    glBegin(GL_POLYGON);
        glVertex2f(0.964f, 0.460f);
        glVertex2f(0.992f, 0.460f);
        glVertex2f(0.992f, 0.515f);
        glVertex2f(0.964f, 0.515f);
    glEnd();

    // 8 scene2_window 20
    glBegin(GL_POLYGON);
        glVertex2f(0.964f, 0.550f);
        glVertex2f(0.992f, 0.550f);
        glVertex2f(0.992f, 0.605f);
        glVertex2f(0.964f, 0.605f);
    glEnd();
}


void scene2_ground()
{
    glColor3f(0.42f, 0.42f, 0.45f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, 0.15f);
        glVertex2f(1.0f, 0.15f);
        glVertex2f(1.0f, -0.35f);
        glVertex2f(-1.0f, -0.35f);
    glEnd();
}


// scene2_tree
void scene2_treeCircle(float cx, float cy)
{
     scene2_circle(cx, cy, 0.025f);
}

void scene2_tree()
{
            // scene2_tree - 1
            glColor3f(0.6f, 0.3f, 0.1f);
            glBegin(GL_POLYGON);
                glVertex2f(-0.625f,0.15f);
                glVertex2f(-0.615f,0.15f);
                glVertex2f(-0.615f,0.28f);
                glVertex2f(-0.625f,0.28f);
            glEnd();

              // bottom circles
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.65f,0.27f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.64f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.61f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.59f,0.27f);


              //mid circles
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(-0.64f,0.31f);
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(-0.6f,0.31f);

              //top circle
              glColor3f(0.18f, 0.55f, 0.24f);
              scene2_treeCircle(-0.62f,0.34f);

            // scene2_tree - 2
            glColor3f(0.6f, 0.3f, 0.1f);
            glBegin(GL_POLYGON);
                glVertex2f(-0.3175f,0.15f);
                glVertex2f(-0.3075f,0.15f);
                glVertex2f(-0.3075f,0.28f);
                glVertex2f(-0.3175f,0.28f);
            glEnd();

            // bottom circles
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.3425f,0.27f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.3325f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.3025f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(-0.2825f,0.27f);


              //mid circles
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(-0.3325f,0.31f);
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(-0.2925f,0.31f);

              //top circle
              glColor3f(0.18f, 0.55f, 0.24f);
              scene2_treeCircle(-0.3125f,0.34f);

            // scene2_tree - 3
            glColor3f(0.6f, 0.3f, 0.1f);
            glBegin(GL_POLYGON);
                glVertex2f(0.190f,0.15f);
                glVertex2f(0.200f,0.15f);
                glVertex2f(0.200f,0.28f);
                glVertex2f(0.190f,0.28f);
            glEnd();

            // bottom circles
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.165f,0.27f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.175f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.205f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.225f,0.27f);


              //mid circles
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(0.175f,0.31f);
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(0.215f,0.31f);

              //top circle
              glColor3f(0.18f, 0.55f, 0.24f);
              scene2_treeCircle(0.195f,0.34f);

            // scene2_tree - 4
            glColor3f(0.6f, 0.3f, 0.1f);
            glBegin(GL_POLYGON);
                glVertex2f(0.475f,0.15f);
                glVertex2f(0.485f,0.15f);
                glVertex2f(0.485f,0.28f);
                glVertex2f(0.475f,0.28f);
            glEnd();

            // bottom circles
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.450f,0.27f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.460f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.490f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.510f,0.27f);


              //mid circles
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(0.460f,0.31f);
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(0.500f,0.31f);

              //top circle
              glColor3f(0.18f, 0.55f, 0.24f);
              scene2_treeCircle(0.480f,0.34f);

            // scene2_tree - 5
            glColor3f(0.6f, 0.3f, 0.1f);
            glBegin(GL_POLYGON);
                glVertex2f(0.775f,0.15f);
                glVertex2f(0.785f,0.15f);
                glVertex2f(0.785f,0.28f);
                glVertex2f(0.775f,0.28f);
            glEnd();

            // bottom circles
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.750f,0.27f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.760f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.790f,0.28f);
              glColor3f(0.13f, 0.45f, 0.20f);
              scene2_treeCircle(0.810f,0.27f);


              //mid circles
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(0.760f,0.31f);
              glColor3f(0.16f, 0.50f, 0.22f);
              scene2_treeCircle(0.800f,0.31f);

              //top circle
              glColor3f(0.18f, 0.55f, 0.24f);
              scene2_treeCircle(0.780f,0.34f);
}



// Sky

void scene2_skyGradient()
{
    glBegin(GL_QUADS);
        glColor3f(scene2_skyBottomR, scene2_skyBottomG, scene2_skyBottomB);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);

        glColor3f(scene2_skyTopR, scene2_skyTopG, scene2_skyTopB);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();
}

void scene2_drawDayToNight()
{
    if (!scene2_isNight)
    {
        // Sun
        glColor3f(1.0f, 0.82f, 0.20f);
        scene2_circle(0.80f, 0.90f, 0.06f);

        glColor3f(1.0f, 0.93f, 0.55f);
        scene2_circle(0.80f, 0.90f, 0.035f);
    }
    else
    {
        // Moon
        glColor3f(0.97f, 0.97f, 0.84f);
        scene2_circle(0.80f, 0.90f, 0.055f);

        glColor3f(0.10f, 0.10f, 0.22f);
        scene2_circle(0.82f, 0.92f, 0.044f);

        // Stars
        glPointSize(3.0f);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_POINTS);

            glVertex2f(-0.90f, 0.88f);
            glVertex2f(-0.65f, 0.92f);
            glVertex2f(-0.45f, 0.82f);
            glVertex2f(-0.25f, 0.91f);
            glVertex2f(-0.05f, 0.78f);
            glVertex2f( 0.15f, 0.90f);
            glVertex2f( 0.35f, 0.82f);
            glVertex2f( 0.55f, 0.94f);
            glVertex2f( 0.75f, 0.86f);
            glVertex2f( 0.90f, 0.96f);

            glVertex2f(-0.82f, 0.68f);
            glVertex2f(-0.55f, 0.72f);
            glVertex2f(-0.35f, 0.62f);
            glVertex2f(-0.10f, 0.70f);
            glVertex2f( 0.10f, 0.60f);
            glVertex2f( 0.30f, 0.70f);
            glVertex2f( 0.50f, 0.64f);
            glVertex2f( 0.70f, 0.74f);
            glVertex2f( 0.88f, 0.62f);

            glVertex2f(-0.95f, 0.52f);
            glVertex2f(-0.72f, 0.58f);
            glVertex2f(-0.48f, 0.50f);
            glVertex2f(-0.20f, 0.55f);
            glVertex2f( 0.05f, 0.48f);
            glVertex2f( 0.25f, 0.55f);
            glVertex2f( 0.48f, 0.50f);
            glVertex2f( 0.68f, 0.56f);
            glVertex2f( 0.92f, 0.48f);

        glEnd();

    }
}

void scene2_cloudCircle(float cx, float cy, float radius)
{
    scene2_circle(cx, cy, radius);
}

void scene2_sky()
{
    scene2_skyGradient();
    scene2_drawDayToNight();

    glPushMatrix();
    glTranslatef(scene2_cloudMove, 0.0f, 0.0f);

    glColor3f(scene2_cloudR, scene2_cloudG, scene2_cloudB);
    // scene2_cloud - 1
    scene2_cloudCircle(-1.00f, 0.820f, 0.035f);
    scene2_cloudCircle(-0.95f, 0.840f, 0.045f);
    scene2_cloudCircle(-0.90f, 0.820f, 0.035f);


    // scene2_cloud - 2
    scene2_cloudCircle(-0.80f, 0.920f, 0.035f);
    scene2_cloudCircle(-0.75f, 0.940f, 0.045f);
    scene2_cloudCircle(-0.70f, 0.920f, 0.035f);


    // scene2_cloud - 3
    scene2_cloudCircle(-0.20f, 0.950f, 0.035f);
    scene2_cloudCircle(-0.15f, 0.970f, 0.045f);
    scene2_cloudCircle(-0.10f, 0.950f, 0.035f);


    // scene2_cloud - 4
    scene2_cloudCircle(0.10f, 0.840f, 0.035f);
    scene2_cloudCircle(0.15f, 0.860f, 0.045f);
    scene2_cloudCircle(0.20f, 0.840f, 0.035f);


    // scene2_cloud - 5
    scene2_cloudCircle(0.40f, 0.930f, 0.035f);
    scene2_cloudCircle(0.45f, 0.950f, 0.045f);
    scene2_cloudCircle(0.50f, 0.930f, 0.035f);


    // scene2_cloud - 6
    scene2_cloudCircle(0.65f, 0.760f, 0.035f);
    scene2_cloudCircle(0.70f, 0.780f, 0.045f);
    scene2_cloudCircle(0.75f, 0.760f, 0.035f);


    glPopMatrix();
}

// scene2_rain
void scene2_drawRain()
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    for (int i = 0; i < 1000; i++)
    {
        if (i % 3 == 0)
        {
            glColor3f(0.8f, 0.8f, 1.0f);
        }
        else if (i % 3 == 1)
        {
            glColor3f(0.6f, 0.6f, 1.0f);
        }
        else
        {
            glColor3f(0.4f, 0.4f, 0.9f);
        }

        glVertex2f(scene2_rainX[i], scene2_rainY[i]);
        glVertex2f(scene2_rainX[i] - 0.015f, scene2_rainY[i] - 0.06f);
    }

    glEnd();
}

// scene2_snow
void scene2_drawSnow()
{
    for (int s = 0; s < 3; s++)
    {
        float scene2_snowSize;
        float shade;

        if (s == 0)
        {
            scene2_snowSize = 5.0f;
            shade = 1.00f;
        }
        else if (s == 1)
        {
            scene2_snowSize = 3.5f;
            shade = 0.85f;
        }
        else
        {
            scene2_snowSize = 2.0f;
            shade = 0.65f;
        }

        glPointSize(scene2_snowSize);
        glColor3f(shade, shade, shade);

        glBegin(GL_POINTS);
        for (int i = 0; i < 500; i++)
        {
            if (i % 3 == s)
            {
                glVertex2f(scene2_snowX[i], scene2_snowY[i]);
            }
        }
        glEnd();
    }
}

// scene2_wind
void scene2_drawWind()
{
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (int i = 0; i < 60; i++)
    {
        glVertex2f(scene2_windLineX[i], scene2_windLineY[i]);
        glVertex2f(scene2_windLineX[i] - 0.05f, scene2_windLineY[i] + 0.03f);
    }
    glEnd();
}


// scene2_tree Bush
void scene2_treeBush()
{
            // scene2_tree bush - 1
            glColor3f(0.55f, 0.30f, 0.10f);
            glBegin(GL_POLYGON);
                glVertex2f(-0.975f, -0.42f);
                glVertex2f(-0.925f, -0.42f);
                glVertex2f(-0.918f, -0.385f);
                glVertex2f(-0.982f, -0.385f);
            glEnd();

            glColor3f(0.25f, 0.55f, 0.20f);
            scene2_circle(-0.97f, -0.365f, 0.028f);

            glColor3f(0.20f, 0.50f, 0.18f);
            scene2_circle(-0.93f, -0.365f, 0.028f);

            glColor3f(0.30f, 0.60f, 0.22f);
            scene2_circle(-0.95f, -0.345f, 0.030f);

            // scene2_tree bush - 2
            glColor3f(0.55f, 0.30f, 0.10f);
            glBegin(GL_POLYGON);
                glVertex2f(0.875f, -0.42f);
                glVertex2f(0.925f, -0.42f);
                glVertex2f(0.932f, -0.385f);
                glVertex2f(0.868f, -0.385f);
            glEnd();

            glColor3f(0.25f, 0.55f, 0.20f);
            scene2_circle(0.88f, -0.365f, 0.028f);

            glColor3f(0.20f, 0.50f, 0.18f);
            scene2_circle(0.92f, -0.365f, 0.028f);

            glColor3f(0.30f, 0.60f, 0.22f);
            scene2_circle(0.90f, -0.345f, 0.030f);
}


// scene2_pedestrian

void scene2_pedestrian1()
{
    // scene2_pedestrian 1
    glPushMatrix();
    glTranslatef(scene2_pedestrianRightMove, 0.0f, 0.0f);

    // legs
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.716f, -0.35f);
        glVertex2f(-0.702f, -0.35f);
        glVertex2f(-0.702f, -0.44f);
        glVertex2f(-0.716f, -0.44f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.698f, -0.35f);
        glVertex2f(-0.684f, -0.35f);
        glVertex2f(-0.684f, -0.44f);
        glVertex2f(-0.698f, -0.44f);
    glEnd();

    // body
    glColor3f(0.20f, 0.60f, 0.35f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.722f, -0.35f);
        glVertex2f(-0.678f, -0.35f);
        glVertex2f(-0.678f, -0.27f);
        glVertex2f(-0.722f, -0.27f);
    glEnd();

    // head
    glColor3f(0.94f, 0.78f, 0.65f);
    scene2_circle(-0.70f, -0.24f, 0.024f);

    // hair
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.724f, -0.24f);
        glVertex2f(-0.676f, -0.24f);
        glVertex2f(-0.678f, -0.218f);
        glVertex2f(-0.722f, -0.218f);
    glEnd();

    glPopMatrix();

}

void scene2_pedestrian2()
{
    // scene2_pedestrian 2
    glPushMatrix();
    glTranslatef(scene2_pedestrianLeftMove, 0.0f, 0.0f);

    // legs
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.316f, -0.35f);
        glVertex2f(-0.302f, -0.35f);
        glVertex2f(-0.302f, -0.44f);
        glVertex2f(-0.316f, -0.44f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.298f, -0.35f);
        glVertex2f(-0.284f, -0.35f);
        glVertex2f(-0.284f, -0.44f);
        glVertex2f(-0.298f, -0.44f);
    glEnd();

    // body
    glColor3f(0.30f, 0.40f, 0.85f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.322f, -0.35f);
        glVertex2f(-0.278f, -0.35f);
        glVertex2f(-0.278f, -0.27f);
        glVertex2f(-0.322f, -0.27f);
    glEnd();

    // head
    glColor3f(0.94f, 0.78f, 0.65f);
    scene2_circle(-0.30f, -0.24f, 0.024f);

    // hair
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(-0.324f, -0.24f);
        glVertex2f(-0.276f, -0.24f);
        glVertex2f(-0.278f, -0.218f);
        glVertex2f(-0.322f, -0.218f);
    glEnd();

    glPopMatrix();

}

void scene2_pedestrian3()
{
    // scene2_pedestrian 3
    glPushMatrix();
    glTranslatef(scene2_pedestrianRightMove, 0.0f, 0.0f);

    // legs
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0.084f, -0.35f);
        glVertex2f(0.098f, -0.35f);
        glVertex2f(0.098f, -0.44f);
        glVertex2f(0.084f, -0.44f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.102f, -0.35f);
        glVertex2f(0.116f, -0.35f);
        glVertex2f(0.116f, -0.44f);
        glVertex2f(0.102f, -0.44f);
    glEnd();

    // body
    glColor3f(0.95f, 0.55f, 0.15f);

    glBegin(GL_POLYGON);
        glVertex2f(0.078f, -0.35f);
        glVertex2f(0.122f, -0.35f);
        glVertex2f(0.122f, -0.27f);
        glVertex2f(0.078f, -0.27f);
    glEnd();

    // head
    glColor3f(0.94f, 0.78f, 0.65f);
    scene2_circle(0.10f, -0.24f, 0.024f);

    // hair
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0.076f, -0.24f);
        glVertex2f(0.124f, -0.24f);
        glVertex2f(0.122f, -0.218f);
        glVertex2f(0.078f, -0.218f);
    glEnd();

    glPopMatrix();
}
void scene2_pedestrian4()
{
    // scene2_pedestrian 4
    glPushMatrix();
    glTranslatef(scene2_pedestrianLeftMove, 0.0f, 0.0f);

    // legs
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0.484f, -0.35f);
        glVertex2f(0.498f, -0.35f);
        glVertex2f(0.498f, -0.44f);
        glVertex2f(0.484f, -0.44f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.502f, -0.35f);
        glVertex2f(0.516f, -0.35f);
        glVertex2f(0.516f, -0.44f);
        glVertex2f(0.502f, -0.44f);
    glEnd();

    // body
    glColor3f(0.60f, 0.25f, 0.75f);

    glBegin(GL_POLYGON);
        glVertex2f(0.478f, -0.35f);
        glVertex2f(0.522f, -0.35f);
        glVertex2f(0.522f, -0.27f);
        glVertex2f(0.478f, -0.27f);
    glEnd();

    // head
    glColor3f(0.94f, 0.78f, 0.65f);
    scene2_circle(0.50f, -0.24f, 0.024f);

    // hair
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0.476f, -0.24f);
        glVertex2f(0.524f, -0.24f);
        glVertex2f(0.522f, -0.218f);
        glVertex2f(0.478f, -0.218f);
    glEnd();

    glPopMatrix();
}

void scene2_pedestrian5()
{

    // scene2_pedestrian 5
    glPushMatrix();
    glTranslatef(scene2_pedestrianRightMove, 0.0f, 0.0f);

    // legs
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0.834f, -0.35f);
        glVertex2f(0.848f, -0.35f);
        glVertex2f(0.848f, -0.44f);
        glVertex2f(0.834f, -0.44f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.852f, -0.35f);
        glVertex2f(0.866f, -0.35f);
        glVertex2f(0.866f, -0.44f);
        glVertex2f(0.852f, -0.44f);
    glEnd();

    // body
    glColor3f(0.85f, 0.20f, 0.30f);

    glBegin(GL_POLYGON);
        glVertex2f(0.828f, -0.35f);
        glVertex2f(0.872f, -0.35f);
        glVertex2f(0.872f, -0.27f);
        glVertex2f(0.828f, -0.27f);
    glEnd();

    // head
    glColor3f(0.94f, 0.78f, 0.65f);
    scene2_circle(0.85f, -0.24f, 0.024f);

    // hair
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(0.826f, -0.24f);
        glVertex2f(0.874f, -0.24f);
        glVertex2f(0.872f, -0.218f);
        glVertex2f(0.828f, -0.218f);
    glEnd();

    glPopMatrix();
}


// Side walk
void scene2_sideWalk()
{
    glColor3f(0.70f, 0.68f, 0.65f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.50f);
        glVertex2f(1.0f, -0.50f);
        glVertex2f(1.0f, -0.30f);
        glVertex2f(-1.0f, -0.30f);
    glEnd();
}

// Sscene2_treet Lamp
void scene2_lampLight(float cx, float cy)
{
    if (scene2_isNight)
        {
            glColor3f(1.0f, 1.0f, 0.0f);
        }
    else
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
    scene2_circle(cx, cy, 0.015f);

}

void scene2_treetLamp()
{
    // left lamp
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.9f, -0.3f);
        glVertex2f(-0.89f, -0.3f);
        glVertex2f(-0.89f, 0.07f);
        glVertex2f(-0.9f, 0.07f);
    glEnd();

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.89f, 0.07f);
        glVertex2f(-0.8f, 0.07f);
        glVertex2f(-0.8f, 0.06f);
        glVertex2f(-0.89f, 0.06f);
    glEnd();

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.81f, 0.07f);
        glVertex2f(-0.8f, 0.07f);
        glVertex2f(-0.8f, 0.03f);
        glVertex2f(-0.81f, 0.03f);
    glEnd();

    scene2_lampLight(-0.804f,0.0f);

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.83f, 0.01f);
        glVertex2f(-0.78f, 0.01f);
        glVertex2f(-0.78f, 0.03f);
        glVertex2f(-0.83f, 0.03f);
    glEnd();

    // right lamp
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.9f, -0.3f);
        glVertex2f(0.89f, -0.3f);
        glVertex2f(0.89f, 0.07f);
        glVertex2f(0.9f, 0.07f);
    glEnd();

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.89f, 0.07f);
        glVertex2f(0.8f, 0.07f);
        glVertex2f(0.8f, 0.06f);
        glVertex2f(0.89f, 0.06f);
    glEnd();

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.81f, 0.07f);
        glVertex2f(0.8f, 0.07f);
        glVertex2f(0.8f, 0.03f);
        glVertex2f(0.81f, 0.03f);
    glEnd();

    scene2_lampLight(0.804f,0.0f);

    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(0.83f, 0.01f);
        glVertex2f(0.78f, 0.01f);
        glVertex2f(0.78f, 0.03f);
        glVertex2f(0.83f, 0.03f);
    glEnd();

}

// Tscene2_rain
void scene2_trainWheel(float cx, float cy)
{
    glColor3f(0.05f, 0.05f, 0.05f);
    scene2_circle(cx, cy, 0.025);

    glColor3f(0.80f, 0.80f, 0.80f);
    scene2_circle(cx, cy, 0.015f);
}
void scene2_trainLine()
{
    // tscene2_rain line
    glColor3f(0.0f, 0.0f, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f,-0.3f);
        glVertex2f(1.0f,-0.3f);
        glVertex2f(1.0f,-0.29f);
        glVertex2f(-1.0f,-0.29f);
    glEnd();
}
void scene2_train()
{
    // cabin - 1
    glColor3f(0.10f, 0.10f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f,-0.24f);
        glVertex2f(-0.45f,-0.24f);
        glVertex2f(-0.45f,-0.05f);
        glVertex2f(-0.8f,-0.05f);
    glEnd();

    // red boarder
    glColor3f(1.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f,-0.22f);
        glVertex2f(-0.45f,-0.22f);
        glVertex2f(-0.45f,-0.21f);
        glVertex2f(-0.8f,-0.21);
    glEnd();

    // c1 : wheel - 1
    glColor3f(1.0f, 0.0, 0.0f);
    scene2_trainWheel(-0.745f,-0.265f);
    scene2_trainWheel(-0.682f,-0.265f);
    scene2_trainWheel(-0.565f,-0.265f);
    scene2_trainWheel(-0.5f,-0.265f);

    // c1 : w1
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.76f,-0.16f);
        glVertex2f(-0.72f,-0.16f);
        glVertex2f(-0.72f,-0.1f);
        glVertex2f(-0.76f,-0.1);
    glEnd();

    //c1 : w2
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f,-0.16f);
        glVertex2f(-0.66f,-0.16f);
        glVertex2f(-0.66f,-0.1f);
        glVertex2f(-0.7f,-0.1f);
    glEnd();

     //c1 : w3
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.64f,-0.16f);
        glVertex2f(-0.6f,-0.16f);
        glVertex2f(-0.6f,-0.1f);
        glVertex2f(-0.64f,-0.1f);
    glEnd();

     //c1 : w4
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.58f,-0.16f);
        glVertex2f(-0.54f,-0.16f);
        glVertex2f(-0.54f,-0.1f);
        glVertex2f(-0.58f,-0.1f);
    glEnd();


     //c1 : w5
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.52f,-0.16f);
        glVertex2f(-0.48f,-0.16f);
        glVertex2f(-0.48f,-0.1f);
        glVertex2f(-0.52f,-0.1f);
    glEnd();


    // connector - 1
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f,-0.2f);
        glVertex2f(-0.4f,-0.2f);
        glVertex2f(-0.4f,-0.1f);
        glVertex2f(-0.45f,-0.1f);
    glEnd();



    // cabin - 2
    glColor3f(0.10f, 0.10f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f,-0.24f);
        glVertex2f(-0.05f,-0.24f);
        glVertex2f(-0.05f,-0.05f);
        glVertex2f(-0.4f,-0.05f);
    glEnd();

    // red boarder
    glColor3f(1.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f,-0.22f);
        glVertex2f(-0.05f,-0.22f);
        glVertex2f(-0.05f,-0.21f);
        glVertex2f(-0.4f,-0.21);
    glEnd();

    // c1 : wheel - 1
    glColor3f(1.0f, 0.0, 0.0f);
    scene2_trainWheel(-0.35f,-0.265f);
    scene2_trainWheel(-0.29f,-0.265f);
    scene2_trainWheel(-0.16f,-0.265f);
    scene2_trainWheel(-0.1f,-0.265f);


    //c1 : w1
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.36f,-0.16f);
        glVertex2f(-0.32f,-0.16f);
        glVertex2f(-0.32f,-0.1f);
        glVertex2f(-0.36f,-0.1f);
    glEnd();

     //c1 : w2
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f,-0.16f);
        glVertex2f(-0.26f,-0.16f);
        glVertex2f(-0.26f,-0.1f);
        glVertex2f(-0.3f,-0.1f);
    glEnd();

     //c1 : w3
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.24f,-0.16f);
        glVertex2f(-0.2f,-0.16f);
        glVertex2f(-0.2f,-0.1f);
        glVertex2f(-0.24f,-0.1f);
    glEnd();


     //c1 : w4
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f,-0.16f);
        glVertex2f(-0.14f,-0.16f);
        glVertex2f(-0.14f,-0.1f);
        glVertex2f(-0.18f,-0.1f);
    glEnd();


    // c1 : w5
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.12f,-0.16f);
        glVertex2f(-0.08f,-0.16f);
        glVertex2f(-0.08f,-0.1f);
        glVertex2f(-0.12f,-0.1f);
    glEnd();


    // connector - 2
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f,-0.2f);
        glVertex2f(-0.0f,-0.2f);
        glVertex2f(-0.0f,-0.1f);
        glVertex2f(-0.05f,-0.1f);
    glEnd();


    // cabin - 3
    glColor3f(0.10f, 0.10f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.0f,-0.24f);
        glVertex2f(0.35f,-0.24f);
        glVertex2f(0.35f,-0.05f);
        glVertex2f(-0.0f,-0.05f);
    glEnd();

    // red boarder
    glColor3f(1.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.0f,-0.22f);
        glVertex2f(0.35f,-0.22f);
        glVertex2f(0.35f,-0.21f);
        glVertex2f(-0.0f,-0.21);
    glEnd();

    // c1 : wheel - 1
    glColor3f(1.0f, 0.0, 0.0f);
    scene2_trainWheel(0.065f,-0.265f);
    scene2_trainWheel(0.125f,-0.265f);
    scene2_trainWheel(0.23f,-0.265f);
    scene2_trainWheel(0.295f,-0.265f);


    //c1 : w1
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.04f,-0.16f);
        glVertex2f(0.08f,-0.16f);
        glVertex2f(0.08f,-0.1f);
        glVertex2f(0.04f,-0.1f);
    glEnd();

     //c1 : w2
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.1f,-0.16f);
        glVertex2f(0.14f,-0.16f);
        glVertex2f(0.14f,-0.1f);
        glVertex2f(0.1f,-0.1f);
    glEnd();

     //c1 : w3
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.16f,-0.16f);
        glVertex2f(0.2f,-0.16f);
        glVertex2f(0.2f,-0.1f);
        glVertex2f(0.16f,-0.1f);
    glEnd();


     //c1 : w4
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.22f,-0.16f);
        glVertex2f(0.26f,-0.16f);
        glVertex2f(0.26f,-0.1f);
        glVertex2f(0.22f,-0.1f);
    glEnd();


    // c1 : w5
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.28f,-0.16f);
        glVertex2f(0.32f,-0.16f);
        glVertex2f(0.32f,-0.1f);
        glVertex2f(0.28f,-0.1f);
    glEnd();


    // connector - 3
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.35f,-0.2f);
        glVertex2f(0.4f,-0.2f);
        glVertex2f(0.4f,-0.1f);
        glVertex2f(0.35f,-0.1f);
    glEnd();


    // cabin - 4
    glColor3f(0.10f, 0.10f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.4f,-0.24f);
        glVertex2f(0.8,-0.24f);
        glVertex2f(0.8,-0.16f);
        glVertex2f(0.7f,-0.05f);
        glVertex2f(0.4f,-0.05f);
    glEnd();

    // red boarder
    glColor3f(1.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.4f,-0.22f);
        glVertex2f(0.8f,-0.22f);
        glVertex2f(0.8f,-0.21f);
        glVertex2f(0.4f,-0.21);
    glEnd();

    // c1 : wheel - 1
    glColor3f(1.0f, 0.0, 0.0f);
    scene2_trainWheel(0.46f,-0.265f);
    scene2_trainWheel(0.52f,-0.265f);
    scene2_trainWheel(0.67f,-0.265f);
    scene2_trainWheel(0.73f,-0.265f);


    //c4 : door
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.44f,-0.21f);
        glVertex2f(0.48f,-0.21f);
        glVertex2f(0.48f,-0.08f);
        glVertex2f(0.44f,-0.08f);
    glEnd();

     //c1 : w1
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.5f,-0.16f);
        glVertex2f(0.54f,-0.16f);
        glVertex2f(0.54f,-0.1f);
        glVertex2f(0.5f,-0.1f);
    glEnd();

     //c1 : w2
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.56f,-0.16f);
        glVertex2f(0.6f,-0.16f);
        glVertex2f(0.6f,-0.1f);
        glVertex2f(0.56f,-0.1f);
    glEnd();


     //c1 : w3
    glColor3f(0.0f, 0.0, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.62f,-0.16f);
        glVertex2f(0.66f,-0.16f);
        glVertex2f(0.66f,-0.1f);
        glVertex2f(0.62f,-0.1f);
    glEnd();


}

void scene2_display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    scene2_sky();
    scene2_building();

    glPushMatrix();
    glTranslatef(scene2_treeMove, 0.0f, 0.0f);
    scene2_tree();
    glPopMatrix();

    scene2_ground();

    scene2_trainLine();

    glPushMatrix();
    glTranslatef(scene2_trainPosition, 0.0f, 0.0f);
    scene2_train();
    glPopMatrix();

    scene2_sideWalk();
    scene2_treetLamp();

    scene2_treeBush();

    scene2_pedestrian1();
    scene2_pedestrian2();
    scene2_pedestrian3();
    scene2_pedestrian4();
    scene2_pedestrian5();

    scene2_road();

    glPushMatrix();
    glTranslatef(scene2_car1Move, 0.0f, 0.0f);
    scene2_car1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scene2_car2Move, 0.0f, 0.0f);
    scene2_car2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scene2_car3Move, 0.0f, 0.0f);
    scene2_car3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scene2_car4Move, 0.0f, 0.0f);
    scene2_car4();
    glPopMatrix();

    if (scene2_rain)
    {
        scene2_drawRain();
    }

    if (scene2_snow)
    {
        scene2_drawSnow();
    }

    if (scene2_wind)
    {
        scene2_drawWind();
    }

    //glutSwapBuffers();
}

void scene2_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'v':
        scene2_isNight = !scene2_isNight;
        if (scene2_isNight)
        {
            scene2_skyTopR = 0.02f;
            scene2_skyTopG = 0.02f;
            scene2_skyTopB = 0.08f;

            scene2_skyBottomR = 0.05f;
            scene2_skyBottomG = 0.05f;
            scene2_skyBottomB = 0.12f;

            scene2_cloudR = 0.30f;
            scene2_cloudG = 0.30f;
            scene2_cloudB = 0.32f;
        }

        else
        {
            scene2_skyTopR = 0.50f;
            scene2_skyTopG = 0.80f;
            scene2_skyTopB = 1.00f;

            scene2_skyBottomR = 0.80f;
            scene2_skyBottomG = 0.93f;
            scene2_skyBottomB = 1.00f;

            scene2_cloudR = 1.0f;
            scene2_cloudG = 1.0f;
            scene2_cloudB = 1.0f;
        }
        break;

    case 'f':  // start & stop scene2_rain
        scene2_rain = !scene2_rain;
        break;

    case 'w':  // scene2_rain speed up
        scene2_rainSpeedMultiplier += 0.2f;
        break;

    case 's':  // scene2_rain speed down
        scene2_rainSpeedMultiplier -= 0.2f;
        break;

    case 'n':  // start & stop scene2_snow
        scene2_snow = !scene2_snow;
        break;

    case 'e': // scene2_snow speed up
        scene2_snowSpeedMultiplier += 0.2f;
        break;

    case 'd': // scene2_snow speed down
        scene2_snowSpeedMultiplier -= 0.2f;
        break;

    case 'g': // start & stop scene2_wind
        scene2_wind = !scene2_wind;
        break;

    case 'a': // stop tscene2_rain
        scene2_trainSpeed = 0.0f;
        break;

    case 't': // tscene2_rain default speed
        scene2_trainSpeed = 0.005f;
        break;



    }
    //glutPostRedisplay();
}

void scene2_handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        scene2_trainSpeed += 0.005f;
    }
    if (button == GLUT_RIGHT_BUTTON)
    {
        scene2_trainSpeed -= 0.005f;
    }
    //glutPostRedisplay();
}

void scene2_Update()
{
    // scene2_cloud
    scene2_cloudMove += 0.0003f;
    if(scene2_cloudMove > 0.6f)
    {
        scene2_cloudMove = -0.6f;
    }

    // scene2_wind movement
    if (scene2_wind)
    {
        // move scene2_wind left to right
        for (int i = 0; i < 60; i++)
        {
            scene2_windLineX[i] += 0.01f;

            if (scene2_windLineX[i] > 1.0f)
            {
                scene2_windLineX[i] = -1.0f;
            }
        }

        // move scene2_tree left and right
        scene2_treeMove += scene2_treeDirection;

        if (scene2_treeMove > 0.02f || scene2_treeMove < -0.02f)
        {
            scene2_treeDirection = -scene2_treeDirection;
        }
    }
    else
    {
        scene2_treeMove = 0.0f;
    }

    // tscene2_rain movement
    if(scene2_trainPosition > 1.0f)
    {
        scene2_trainPosition = -1.0f;
    }
    scene2_trainPosition += scene2_trainSpeed;

    scene2_car1Move -= 0.01f;
    if(scene2_car1Move < -1.3f)
    {
        scene2_car1Move = 1.3f;
    }

    scene2_car2Move += 0.012f;
    if(scene2_car2Move > 1.3f)
    {
        scene2_car2Move = -1.3f;
    }

    scene2_car3Move -= 0.01f;
    if(scene2_car3Move < -1.3f)
    {
        scene2_car3Move = 1.3f;
    }

    scene2_car4Move += 0.012f;
    if(scene2_car4Move > 1.3f)
    {
        scene2_car4Move = -1.3f;
    }

    // scene2_pedestrians moving right
    scene2_pedestrianRightMove += 0.003f;
    if(scene2_pedestrianRightMove > 1.8f)
    {
        scene2_pedestrianRightMove = -1.8f;
    }

    // scene2_pedestrians moving left
    scene2_pedestrianLeftMove -= 0.003f;
    if(scene2_pedestrianLeftMove < -1.8f)
    {
        scene2_pedestrianLeftMove = 1.8f;
    }

    if (scene2_rain)
    {
        for (int i = 0; i < 1000; i++)
        {
            scene2_rainY[i] -= scene2_rainSpeed[i] * scene2_rainSpeedMultiplier;

            if (scene2_rainY[i] < -1.0f)
            {
                scene2_rainY[i] = 1.0f;
                scene2_rainX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

                scene2_rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
            }
        }
    }

    if (scene2_snow)
    {
        for (int i = 0; i < 500; i++)
        {
            scene2_snowY[i] -= scene2_snowSpeed[i] * scene2_snowSpeedMultiplier;

            if (scene2_snowY[i] < -1.0f)
            {
                scene2_snowY[i] = 1.0f;
                scene2_snowX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

                scene2_snowSpeed[i] = 0.003f + ((float)rand() / RAND_MAX) * 0.006f;
            }
        }
    }


}


#endif
