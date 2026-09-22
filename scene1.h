//scene - 1


#ifndef SCENE1_H
#define SCENE1_H
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

void scene1_drawCircle(float center_x, float center_y, float radius, int segments)
{
    glBegin(GL_POLYGON);
    glVertex2f(center_x, center_y);
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2 * 3.1416 * i / segments;
        glVertex2f(center_x + radius * (float)cos(angle), center_y + radius * (float)sin(angle));
    }
    glEnd();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (VARIABLES)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
float scene1_wheelAngle = 0.0f;

float scene1_swingAngle = 0.0f;
float scene1_swingSpeed = 0.5f;

float scene1_parkh1x = -0.5f;
float scene1_parkh1y = -0.2f;
float scene1_legAngle1 = 0.0f;
float scene1_legSpeed1 = 2.0f;


float scene1_parkh2x = 0.0f;
float scene1_parkh2y = -0.4f;
float scene1_legAngle2 = 0.0f;
float scene1_legSpeed2 = 2.0f;


float scene1_parkh3x = 0.5f;
float scene1_parkh3y = -0.1f;
float scene1_legAngle3 = 0.0f;
float scene1_legSpeed3 = 2.0f;


float scene1_parkh1speedX = 0.002f;
float scene1_parkh1speedY = 0.001f;

float scene1_parkh2speedX = -0.0015f;
float scene1_parkh2speedY = 0.002f;

float scene1_parkh3speedX = 0.001f;
float scene1_parkh3speedY = -0.002f;

float scene1_sd_skyR1 = 0.50f, scene1_sd_skyG1 = 0.85f, scene1_sd_skyB1 = 1.00f; // top
float scene1_sd_skyR2 = 0.80f, scene1_sd_skyG2 = 0.93f, scene1_sd_skyB2 = 1.00f; // bottom
bool  scene1_sd_isNight = false;
float scene1_sd_cloudX = 0.0f;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (WIND DRAW)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
float scene1_windLineX[60];
float scene1_windLineY[60];
bool scene1_wind = false;
float scene1_windPhase = 0.0f;
float scene1_windSway = 0.0f;

void scene1_drawWind()
{
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    for (int i = 0; i < 60; i++)
    {
        glVertex2f(scene1_windLineX[i], scene1_windLineY[i]);
        glVertex2f(scene1_windLineX[i] - 0.05f,
                   scene1_windLineY[i] + 0.03f);
    }

    glEnd();

    glLineWidth(1.0f);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (RAIN DRAW)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
bool scene1_rain = false;
float scene1_rainX[1000];
float scene1_rainY[1000];
float scene1_rainSpeed[1000];
float scene1_rainSpeedMultiplier = 1.0f;
void scene1_drawRain()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    for (int i = 0; i < 1000; i++)
    {
        //brightness
        if (i % 3 == 0)
            glColor3f(0.8f, 0.8f, 1.0f);
        else if (i % 3 == 1)
            glColor3f(0.6f, 0.6f, 1.0f);
        else
            glColor3f(0.4f, 0.4f, 0.9f);

        //slanted rain
        glVertex2f(scene1_rainX[i], scene1_rainY[i]);
        glVertex2f(scene1_rainX[i] - 0.015f, scene1_rainY[i] - 0.06f);
    }

    glEnd();

    //glLineWidth(1.0f);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (SNOW DRAW)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
bool scene1_snow = false;
float scene1_snowX[500];
float scene1_snowY[500];
float scene1_snowSpeed[500];
float scene1_snowSway[500];
float scene1_snowSpeedMultiplier = 1.0f;

void scene1_drawSnow()
{
    glPointSize(4.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    for (int i = 0; i < 500; i++)
    {
        glVertex2f(scene1_snowX[i], scene1_snowY[i]);
    }

    glEnd();

    glPointSize(1.0f);
}

// Seeds rain/snow/wind arrays with randomized starting positions and
// nonzero speeds. Without this, all particles start at (0,0) with
// speed 0 and never move, since the per-particle speed is otherwise
// only reassigned once a particle falls below the bottom of the
// screen -- which never happens if its speed is already 0.
void scene1_initializeWeather()
{
    for (int i = 0; i < 1000; i++)
    {
        scene1_rainX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene1_rainY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene1_rainSpeed[i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
    }

    for (int i = 0; i < 500; i++)
    {
        scene1_snowX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene1_snowY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene1_snowSpeed[i] = 0.003f + ((float)rand() / RAND_MAX) * 0.006f;
        scene1_snowSway[i] = ((float)rand() / RAND_MAX) * 6.28f;
    }

    for (int i = 0; i < 60; i++)
    {
        scene1_windLineX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        scene1_windLineY[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (CABIN DRAW)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
void scene1_cabin(float x, float y, float r)
{
    //upper white half
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (int i = 0; i <= 50; i++)
    {
        float angle = 3.1416 * i / 50.0f;
        glVertex2f(
            x + cos(angle) * r,
            y + sin(angle) * r
        );
    }
    glEnd();
    //lower RED half
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (int i = 50; i <= 100; i++)
    {
        float angle = 3.1416 * i / 50.0f;
        glVertex2f(
            x + cos(angle) * r,
            y + sin(angle) * r
        );
    }
    glEnd();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (FIELD)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
void scene1_greenField()
{
	glBegin(GL_QUADS);
    glColor3f(0.2, 0.8, 0.2);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 0.4);
    glVertex2f(-1.0, 0.4);
    glEnd();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (SKY)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
void scene1_parksky()
{
    glBegin(GL_QUADS);
    glColor3f(scene1_sd_skyR1, scene1_sd_skyG1, scene1_sd_skyB1);
    glVertex2f(-1.0f, 0.4f);
    glVertex2f(1.0f, 0.4f);
    glColor3f(scene1_sd_skyR2, scene1_sd_skyG2, scene1_sd_skyB2);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (GOL TREE)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  (scene1)
void scene1_tree() {
    //tree body
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.22, 0.05);
    glVertex2f(0.70f, -0.5f);
    glVertex2f(0.67f, -0.5f);
    glVertex2f(0.67f, -0.3f);
    glVertex2f(0.70f, -0.3f);
    glEnd();

    //grass
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.55f, 0.0f);
    // grass 1
    glVertex2f(0.65f, -0.50f);
    glVertex2f(0.66f, -0.45f);
    glVertex2f(0.67f, -0.50f);
    // grass 2
    glVertex2f(0.665f, -0.50f);
    glVertex2f(0.675f, -0.44f);
    glVertex2f(0.685f, -0.50f);
    // grass 3
    glVertex2f(0.68f, -0.50f);
    glVertex2f(0.69f, -0.46f);
    glVertex2f(0.70f, -0.50f);
    // grass 4
    glVertex2f(0.695f, -0.50f);
    glVertex2f(0.705f, -0.45f);
    glVertex2f(0.715f, -0.50f);
    glEnd();

    // stone 1
    glColor3f(0.6f, 0.6f, 0.6f);
    scene1_drawCircle(0.655f, -0.515f, 0.012f, 100);
    // stone 2
    glColor3f(0.7f, 0.7f, 0.7f);
    scene1_drawCircle(0.685f, -0.525f, 0.010f, 100);
    // stone 3
    glColor3f(0.5f, 0.5f, 0.5f);
    scene1_drawCircle(0.715f, -0.515f, 0.013f, 100);
    // stone 4
    glColor3f(0.75f, 0.75f, 0.75f);
    scene1_drawCircle(0.70f, -0.54f, 0.009f, 100);

    //tree leaves
    glPushMatrix();

    glTranslatef(0.0f, 0.15f, 0.0f);
    glRotatef(scene1_windSway, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -0.15f, 0.0f);

    glColor3f(0.65f, 0.8f, 0.2f);
    scene1_drawCircle(0.685f, -0.25f, 0.1f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    scene1_drawCircle(0.65f, -0.15f, 0.09f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    scene1_drawCircle(0.72f, -0.15f, 0.09f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    scene1_drawCircle(0.75f, -0.31f, 0.07f, 100);
    glColor3f(0.65f, 0.8f, 0.2f);
    scene1_drawCircle(0.61f, -0.31f, 0.07f, 100);

    // white flower
    glColor3f(1.0f, 1.0f, 1.0f);
    scene1_drawCircle(0.67f, -0.18f, 0.012f, 100);
    scene1_drawCircle(0.69f, -0.18f, 0.012f, 100);
    scene1_drawCircle(0.68f, -0.16f, 0.012f, 100);
    scene1_drawCircle(0.68f, -0.20f, 0.012f, 100);
    glColor3f(1.0f, 0.8f, 0.0f);
    scene1_drawCircle(0.68f, -0.18f, 0.010f, 100);

    // pink flower
    glColor3f(1.0f, 0.4f, 0.7f);
    scene1_drawCircle(0.72f, -0.20f, 0.012f, 100);
    scene1_drawCircle(0.74f, -0.20f, 0.012f, 100);
    scene1_drawCircle(0.73f, -0.18f, 0.012f, 100);
    scene1_drawCircle(0.73f, -0.22f, 0.012f, 100);
    glColor3f(1.0f, 1.0f, 0.0f);
    scene1_drawCircle(0.73f, -0.20f, 0.010f, 100);

    // red flower
    glColor3f(1.0f, 0.0f, 0.0f);
    scene1_drawCircle(0.65f, -0.28f, 0.011f, 100);
    scene1_drawCircle(0.67f, -0.28f, 0.011f, 100);
    scene1_drawCircle(0.66f, -0.26f, 0.011f, 100);
    scene1_drawCircle(0.66f, -0.30f, 0.011f, 100);
    glColor3f(1.0f, 1.0f, 0.0f);
    scene1_drawCircle(0.66f, -0.28f, 0.009f, 100);

    // small flower
    glColor3f(0.8f, 0.5f, 1.0f);
    scene1_drawCircle(0.71f, -0.11f, 0.010f, 100);
    scene1_drawCircle(0.725f, -0.11f, 0.010f, 100);
    scene1_drawCircle(0.717f, -0.095f, 0.010f, 100);
    scene1_drawCircle(0.717f, -0.125f, 0.010f, 100);
    glColor3f(1.0f, 1.0f, 0.0f);
    scene1_drawCircle(0.717f, -0.11f, 0.008f, 100);

    glPopMatrix();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (JHAR GACH)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void scene1_tree2() {
    //tree body
    glBegin(GL_QUADS);
    glColor3f(0.65, 0.40, 0.20);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.47f, -0.5f);
    glVertex2f(-0.47f, -0.3f);
    glVertex2f(-0.5f, -0.3f);
    glEnd();
    //tree leaves
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.55f, 0.15f);
    glVertex2f(-0.535f, -0.3f);
    glVertex2f(-0.535f, -0.1f);
    glVertex2f(-0.505f, 0.0f);
    glVertex2f(-0.465f, 0.0f);
    glVertex2f(-0.435f, -0.1f);
    glVertex2f(-0.435f, -0.3f);
    glEnd();
    glColor3f(0.2f, 0.55f, 0.15f);
    scene1_drawCircle(-0.435f, -0.3f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.28f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.26f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.24f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.22f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.20f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.18f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.16f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.14f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.12f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.10f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.30f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.28f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.26f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.24f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.22f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.20f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.18f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.16f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.14f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.12f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.10f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.525f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.515f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.505f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.495f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.485f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.475f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.465f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.455f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.445f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.308f, 0.01f, 100);
    scene1_drawCircle(-0.535f, -0.10f, 0.01f, 100);
    scene1_drawCircle(-0.530f, -0.08f, 0.01f, 100);
    scene1_drawCircle(-0.525f, -0.06f, 0.01f, 100);
    scene1_drawCircle(-0.520f, -0.04f, 0.01f, 100);
    scene1_drawCircle(-0.515f, -0.02f, 0.01f, 100);
    scene1_drawCircle(-0.505f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.505f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.495f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.485f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.475f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.465f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.465f, 0.00f, 0.01f, 100);
    scene1_drawCircle(-0.460f, -0.02f, 0.01f, 100);
    scene1_drawCircle(-0.455f, -0.04f, 0.01f, 100);
    scene1_drawCircle(-0.450f, -0.06f, 0.01f, 100);
    scene1_drawCircle(-0.445f, -0.08f, 0.01f, 100);
    scene1_drawCircle(-0.435f, -0.10f, 0.01f, 100);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (TRIBHUJ GACH)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_tree3() {
    //tree body
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.22, 0.05);
    glVertex2f(-0.27f, -0.5f);
    glVertex2f(-0.27f, -0.3f);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(-0.3f, -0.5f);
    glEnd();
    //tree leaves
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.6f, 0.15f);
    glVertex2f(-0.23f, -0.3f);
    glVertex2f(-0.285f, -0.15f);
    glVertex2f(-0.34f, -0.3f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.6f, 0.15f);
    glVertex2f(-0.23f, -0.20f);
    glColor3f(0.65f, 0.8f, 0.2f);
    glVertex2f(-0.285f, -0.05f);
    glColor3f(0.65f, 0.8f, 0.2f);
    glVertex2f(-0.34f, -0.20f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.65f, 0.8f, 0.2f);
    glVertex2f(-0.23f, -0.10f);
    glColor3f(1.0f, 0.8f, 0.2f);
    glVertex2f(-0.285f, 0.05f);
    glColor3f(1.0f, 0.8f, 0.2f);
    glVertex2f(-0.34f, -0.10f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    // grass 1
    glVertex2f(-0.33f, -0.50f);
    glVertex2f(-0.325f, -0.46f);
    glVertex2f(-0.32f, -0.50f);
    // grass 2
    glVertex2f(-0.315f, -0.50f);
    glVertex2f(-0.31f, -0.45f);
    glVertex2f(-0.305f, -0.50f);
    // grass 3
    glVertex2f(-0.30f, -0.50f);
    glVertex2f(-0.295f, -0.46f);
    glVertex2f(-0.29f, -0.50f);
    // grass 4
    glVertex2f(-0.285f, -0.50f);
    glVertex2f(-0.28f, -0.44f);
    glVertex2f(-0.275f, -0.50f);
    // grass 5
    glVertex2f(-0.27f, -0.50f);
    glVertex2f(-0.265f, -0.46f);
    glVertex2f(-0.26f, -0.50f);
    // grass 6
    glVertex2f(-0.255f, -0.50f);
    glVertex2f(-0.25f, -0.45f);
    glVertex2f(-0.245f, -0.50f);
    glEnd();
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (FULS)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_flower() {
    // white flower
    glColor3f(1.0f, 1.0f, 1.0f);
    scene1_drawCircle(0.47f, -0.18f, 0.012f, 100);
    scene1_drawCircle(0.49f, -0.18f, 0.012f, 100);
    scene1_drawCircle(0.48f, -0.16f, 0.012f, 100);
    scene1_drawCircle(0.48f, -0.20f, 0.012f, 100);
    glColor3f(1.0f, 0.8f, 0.0f);
    scene1_drawCircle(0.48f, -0.18f, 0.010f, 100);
}
void scene1_flower2() {
    // pink flower
    glColor3f(1.0f, 0.4f, 0.7f);
    scene1_drawCircle(0.52f, -0.20f, 0.012f, 100);
    scene1_drawCircle(0.54f, -0.20f, 0.012f, 100);
    scene1_drawCircle(0.53f, -0.18f, 0.012f, 100);
    scene1_drawCircle(0.53f, -0.22f, 0.012f, 100);
    glColor3f(1.0f, 1.0f, 0.0f);
    scene1_drawCircle(0.53f, -0.20f, 0.010f, 100);
}
void scene1_flower3() {
    // red flower
    glColor3f(1.0f, 0.0f, 0.0f);
    scene1_drawCircle(0.45f, -0.28f, 0.011f, 100);
    scene1_drawCircle(0.47f, -0.28f, 0.011f, 100);
    scene1_drawCircle(0.46f, -0.26f, 0.011f, 100);
    scene1_drawCircle(0.46f, -0.30f, 0.011f, 100);
    glColor3f(1.0f, 1.0f, 0.0f);
    scene1_drawCircle(0.46f, -0.28f, 0.009f, 100);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (RASTA)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_pathway()
{
    // curved pathway
    glColor3f(0.75f, 0.65f, 0.45f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -1.00f);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.55f, -0.70f);
    glVertex2f(-0.35f, -0.55f);
    glVertex2f(-0.10f, -0.40f);
    glVertex2f(0.10f, -0.35f);
    glVertex2f(0.25f, -0.38f);
    glVertex2f(0.40f, -0.48f);
    glVertex2f(0.55f, -0.62f);
    glVertex2f(0.75f, -0.82f);
    glVertex2f(0.90f, -1.00f);
    glVertex2f(0.72f, -1.00f);
    glVertex2f(0.58f, -0.85f);
    glVertex2f(0.42f, -0.70f);
    glVertex2f(0.28f, -0.60f);
    glVertex2f(0.12f, -0.52f);
    glVertex2f(-0.05f, -0.50f);
    glVertex2f(-0.22f, -0.58f);
    glVertex2f(-0.40f, -0.72f);
    glVertex2f(-0.58f, -0.86f);
    glVertex2f(-0.72f, -1.00f);
    glEnd();
    // pathway border
    glLineWidth(3.0f);
    glColor3f(0.55f, 0.40f, 0.20f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.90f, -1.00f);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.55f, -0.70f);
    glVertex2f(-0.35f, -0.55f);
    glVertex2f(-0.10f, -0.40f);
    glVertex2f(0.10f, -0.35f);
    glVertex2f(0.25f, -0.38f);
    glVertex2f(0.40f, -0.48f);
    glVertex2f(0.55f, -0.62f);
    glVertex2f(0.75f, -0.82f);
    glVertex2f(0.90f, -1.00f);
    glVertex2f(0.72f, -1.00f);
    glVertex2f(0.58f, -0.85f);
    glVertex2f(0.42f, -0.70f);
    glVertex2f(0.28f, -0.60f);
    glVertex2f(0.12f, -0.52f);
    glVertex2f(-0.05f, -0.50f);
    glVertex2f(-0.22f, -0.58f);
    glVertex2f(-0.40f, -0.72f);
    glVertex2f(-0.58f, -0.86f);
    glVertex2f(-0.72f, -1.00f);
    glEnd();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (BENCHS)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_bench() {
    glBegin(GL_QUADS);
    glColor3f(0.82f, 0.60f, 0.35f);
    glVertex2f(-0.95f, -0.65f);
    glVertex2f(-0.80f, -0.55f);
    glVertex2f(-0.785f, -0.66f);
    glVertex2f(-0.935f, -0.76f);  //upper
    glEnd();
    //upper bench design
    glBegin(GL_LINES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.9425f, -0.72f);
    glVertex2f(-0.79f, -0.62f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.9485f, -0.69f);
    glVertex2f(-0.795f, -0.59f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.85f, -0.77f);
    glVertex2f(-0.7f, -0.67f);
    glVertex2f(-0.785f, -0.66f);
    glVertex2f(-0.935f, -0.76f); //lower
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.82f, 0.60f, 0.35f);
    glVertex2f(-0.935f, -0.76f);
    glVertex2f(-0.935f, -0.77f);
    glVertex2f(-0.85f, -0.78f);
    glVertex2f(-0.85f, -0.77f); //lower border
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.82f, 0.60f, 0.35f);
    glVertex2f(-0.85f, -0.78f);
    glVertex2f(-0.85f, -0.77f);
    glVertex2f(-0.7f, -0.67f);
    glVertex2f(-0.7f, -0.68f); //lower border
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.925f, -0.77f);
    glVertex2f(-0.925f, -0.80f);
    glVertex2f(-0.915f, -0.805f);
    glVertex2f(-0.915f, -0.77f); //left leg
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.84f, -0.77f);
    glVertex2f(-0.84f, -0.825f);
    glVertex2f(-0.85f, -0.820f);
    glVertex2f(-0.85f, -0.78f); //right leg
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(-0.70f, -0.68f);
    glVertex2f(-0.70f, -0.735f);
    glVertex2f(-0.71f, -0.73f);
    glVertex2f(-0.7115f, -0.69f); //upper right leg
    glEnd();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (NAGORDOLA)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_nagordola() {
    //middle circle
    glColor3f(0.3f, 0.3f, 0.3f);
    scene1_drawCircle(0.55f, -0.10f, 0.05f, 100);
    // left stand
    glBegin(GL_TRIANGLES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(0.45f, -0.50f);
    glVertex2f(0.50f, -0.50f);
    glVertex2f(0.55f, -0.10f);
    glEnd();
    // right stand
    glBegin(GL_TRIANGLES);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(0.60f, -0.50f);
    glVertex2f(0.65f, -0.50f);
    glVertex2f(0.55f, -0.10f);
    glEnd();
    // bottom base
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(0.40f, -0.50f);
    glVertex2f(0.70f, -0.50f);
    glVertex2f(0.70f, -0.52f);
    glVertex2f(0.40f, -0.52f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.55f, -0.10f, 0.0f);
    glRotatef(scene1_wheelAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.55f, 0.10f, 0.0f);
    //main circle
    float scene1_centerX = 0.55f;
    float scene1_centerY = -0.10f;
    float scene1_outerRadius = 0.30f;
    float scene1_innerRadius = 0.24f;
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0f, 0.45f, 0.55f);
    for (int i = 0; i <= 100; i++)
    {
        float scene1_angle = 2 * 3.1416 * i / 100;
        glVertex2f(
            scene1_centerX + cos(scene1_angle) * scene1_outerRadius,
            scene1_centerY + sin(scene1_angle) * scene1_outerRadius  // outer circle point
        );
        glVertex2f(
            scene1_centerX + cos(scene1_angle) * scene1_innerRadius,
            scene1_centerY + sin(scene1_angle) * scene1_innerRadius  // inner circle point
        );
    }
    glEnd();
    //2 circle connections
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.25f, 0.25f);
    // top
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.55f, 0.14f);
    // bottom
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.55f, -0.34f);
    // left
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.31f, -0.10f);
    // right
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.79f, -0.10f);
    // top-left
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.38f, 0.07f);
    // top-right
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.72f, 0.07f);
    // bottom-left
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.38f, -0.27f);
    // bottom-right
    glVertex2f(0.55f, -0.10f);
    glVertex2f(0.72f, -0.27f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    scene1_drawCircle(0.55f, -0.10f, 0.02f, 100); //middile circle design
    // cabin design
    scene1_cabin(0.55f, 0.20f, 0.04f);     // top
    scene1_cabin(0.55f, -0.40f, 0.04f);    // bottom
    scene1_cabin(0.25f, -0.10f, 0.04f);    // left
    scene1_cabin(0.85f, -0.10f, 0.04f);    // right
    scene1_cabin(0.34f, 0.11f, 0.04f);    // top-left
    scene1_cabin(0.76f, 0.11f, 0.04f);    // top-right
    scene1_cabin(0.34f, -0.31f, 0.04f);    // bottom-left
    scene1_cabin(0.76f, -0.31f, 0.04f);    // bottom-right
    glPopMatrix();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (DOLNA)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_swing()
{
    // SWING FRAME
    glColor3f(0.33f, 0.22f, 0.05f);

    // Left support
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, -0.40f);
    glVertex2f(-0.19f, -0.40f);
    glVertex2f(-0.08f, 0.05f);
    glVertex2f(-0.11f, 0.05f);
    glEnd();

    // Right support
    glBegin(GL_QUADS);
    glVertex2f(0.19f, -0.40f);
    glVertex2f(0.22f, -0.40f);
    glVertex2f(0.11f, 0.05f);
    glVertex2f(0.08f, 0.05f);
    glEnd();

    // Top bar
    glBegin(GL_QUADS);
    glVertex2f(-0.12f, 0.05f);
    glVertex2f(0.12f, 0.05f);
    glVertex2f(0.12f, 0.08f);
    glVertex2f(-0.12f, 0.08f);
    glEnd();


    // SWING
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glRotatef(scene1_swingAngle, 0.0f, 0.0f, 1.0f);

    // Left rope
    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glVertex2f(-0.07f, 0.0f);
    glVertex2f(-0.07f, -0.30f);
    glEnd();

    // Right rope
    glBegin(GL_LINES);
    glVertex2f(0.07f, 0.0f);
    glVertex2f(0.07f, -0.30f);
    glEnd();

    // Seat
    glColor3f(0.75f, 0.35f, 0.08f);

    glBegin(GL_QUADS);
    glVertex2f(-0.09f, -0.32f);
    glVertex2f(0.09f, -0.32f);
    glVertex2f(0.09f, -0.28f);
    glVertex2f(-0.09f, -0.28f);
    glEnd();

    //KID
    glPushMatrix();
    glTranslatef(0.0f, -0.22f, 0.0f);
    glScalef(0.75f, 0.75f, 1.0f);

    // HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene1_drawCircle(0.0f, 0.09f, 0.018f, 50);

    // NECK
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);
    glEnd();

    // HAIR
    glBegin(GL_POLYGON);
    glColor3f(.87f, 0.05f, 0.22f);
    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);
    glEnd();

    // BODY / SHIRT
    glBegin(GL_POLYGON);
    glColor3f(0.78f, 0.05f, 0.0f);
    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);
    glEnd();

   // LEFT ARM
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(-0.028f, 0.055f);
    glVertex2f(-0.085f, 0.100f);
    glVertex2f(-0.093f, 0.088f);
    glVertex2f(-0.028f, 0.038f);
    glEnd();

    // RIGHT ARM
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(0.028f, 0.055f);
    glVertex2f(0.085f, 0.100f);
    glVertex2f(0.093f, 0.088f);
    glVertex2f(0.028f, 0.038f);
    glEnd();

    // LEFT HAND
    glColor3f(1.0f, 0.82f, 0.68f);
    scene1_drawCircle(-0.090f, 0.094f, 0.010f, 30);

    // RIGHT HAND
    glColor3f(1.0f, 0.82f, 0.68f);
    scene1_drawCircle(0.090f, 0.094f, 0.010f, 30);

    // LEFT LEG
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);
    glEnd();

    // RIGHT LEG
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);
    glEnd();

    // LEFT SHOE
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);
    glEnd();

    // RIGHT SHOE
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);
    glEnd();

    glPopMatrix();
    glPopMatrix();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (FENCH)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_Fence() {
    glBegin(GL_QUADS);
    glColor3f(0.60f, 0.35f, 0.15f);
    // upper bar
    glVertex2f(-0.40f, -0.05f);
    glVertex2f(0.40f, -0.05f);
    glVertex2f(0.40f, -0.03f);
    glVertex2f(-0.40f, -0.03f);
    // lower bar
    glVertex2f(-0.40f, -0.11f);
    glVertex2f(0.40f, -0.11f);
    glVertex2f(0.40f, -0.09f);
    glVertex2f(-0.40f, -0.09f);
    glEnd();
    glColor3f(0.50f, 0.25f, 0.08f);
    for (float scene1_x = -0.40f; scene1_x <= 0.40f; scene1_x += 0.06f)
    {
        glBegin(GL_POLYGON);
        glVertex2f(scene1_x, -0.15f);
        glVertex2f(scene1_x + 0.02f, -0.15f);
        glVertex2f(scene1_x + 0.02f, 0.00f);
        glVertex2f(scene1_x + 0.01f, 0.03f);
        glVertex2f(scene1_x, 0.00f);
        glEnd();
    }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (MANUS)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_manus()
{
    glPushMatrix();
    //glTranslatef(x, y, 0.0f);
    // HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene1_drawCircle(0.0f, 0.09f, 0.018f, 50);

    // NECK
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);
    glEnd();

    // HAIR
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.05f, 0.95f);
    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);
    glEnd();

    // BODY
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.05f, 0.95f);
    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);
    glEnd();

    // LEFT ARM
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

    // LEFT LEG SHOE
    glPushMatrix();
    glTranslatef(-0.010f, -0.015f, 0.0f);
    glRotatef(scene1_legAngle1, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.018f, -0.015f);
    glVertex2f(-0.002f, -0.015f);
    glVertex2f(-0.004f, -0.085f);
    glVertex2f(-0.020f, -0.085f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(-0.024f, -0.085f);
    glVertex2f(-0.002f, -0.085f);
    glVertex2f(-0.002f, -0.092f);
    glVertex2f(-0.024f, -0.092f);
    glEnd();
    glPopMatrix();

    // RIGHT LEG SHOE
    glPushMatrix();
    glTranslatef(0.010f, -0.015f, 0.0f);
    glRotatef(-scene1_legAngle1, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.002f, -0.015f);
    glVertex2f(0.018f, -0.015f);
    glVertex2f(0.020f, -0.085f);
    glVertex2f(0.004f, -0.085f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(0.002f, -0.085f);
    glVertex2f(0.024f, -0.085f);
    glVertex2f(0.024f, -0.092f);
    glVertex2f(0.002f, -0.092f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (MANUS 2)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_manus2()
{
    glPushMatrix();
    //glTranslatef(x, y, 0.0f);
    // HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene1_drawCircle(0.0f, 0.09f, 0.018f, 50);

    // NECK
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);
    glEnd();

    // HAIR
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.05f, 0.05f);
    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);
    glEnd();

    // BODY / SHIRT
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.55f, 0.0f);
    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);
    glEnd();

    // LEFT ARM
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(-0.028f, 0.050f);
    glVertex2f(-0.040f, 0.040f);
    glVertex2f(-0.036f, -0.010f);
    glVertex2f(-0.022f, 0.000f);
    glEnd();

    //  RIGHT ARM
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(0.028f, 0.050f);
    glVertex2f(0.040f, 0.040f);
    glVertex2f(0.036f, -0.010f);
    glVertex2f(0.022f, 0.000f);
    glEnd();

    // LEFT LEG SHOE
    glPushMatrix();
    glTranslatef(-0.010f, -0.015f, 0.0f);
    glRotatef(scene1_legAngle2, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f);
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

    // RIGHT LEG SHOE
    glPushMatrix();
    glTranslatef(0.010f, -0.015f, 0.0f);
    glRotatef(-scene1_legAngle2, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f);
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (MANUS 3)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_manus3()
{
    glPushMatrix();
    //glTranslatef(x, y, 0.0f);
    // HEAD
    glColor3f(1.0f, 0.82f, 0.68f);
    scene1_drawCircle(0.0f, 0.09f, 0.018f, 50);

    //  NECK
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.82f, 0.68f);
    glVertex2f(-0.006f, 0.072f);
    glVertex2f(0.006f, 0.072f);
    glVertex2f(0.006f, 0.055f);
    glVertex2f(-0.006f, 0.055f);
    glEnd();

    //  HAIR
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.05f, 1.0f);
    glVertex2f(-0.018f, 0.102f);
    glVertex2f(-0.010f, 0.115f);
    glVertex2f(0.010f, 0.115f);
    glVertex2f(0.018f, 0.102f);
    glVertex2f(0.014f, 0.085f);
    glVertex2f(-0.014f, 0.085f);
    glEnd();

    // BODY / SHIRT
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.3f, 0.7f);
    glVertex2f(-0.028f, 0.060f);
    glVertex2f(0.028f, 0.060f);
    glVertex2f(0.022f, -0.015f);
    glVertex2f(-0.022f, -0.015f);
    glEnd();

    //  LEFT ARM
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

    // LEFT LEG SHOE
    glPushMatrix();
    glTranslatef(-0.010f, -0.015f, 0.0f);
    glRotatef(scene1_legAngle3, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f);
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

    // RIGHT LEG SHOE
    glPushMatrix();
    glTranslatef(0.010f, -0.015f, 0.0f);
    glRotatef(-scene1_legAngle3, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.010f, 0.015f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.6f);
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (SUN/MOON)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Sun / Moon
void scene1_sd_drawCelestial() {
    if (!scene1_sd_isNight) {
// SIMPLE SUN

glColor3f(1.0f, 0.92f, 0.15f);
scene1_drawCircle(-0.75f, 0.80f, 0.055f, 36);

glColor3f(1.0f, 0.98f, 0.65f);
scene1_drawCircle(-0.76f, 0.81f, 0.022f, 18);
    }
    else {
        // Moon
        glColor3f(0.97f, 0.97f, 0.84f);
        scene1_drawCircle(-0.75f, 0.80f, 0.055f, 30);
        glColor3f(0.10f, 0.10f, 0.22f);
        scene1_drawCircle(-0.73f, 0.82f, 0.044f, 30);
        // Stars
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

    glVertex2f(-0.82f, 0.68f);
    glVertex2f(-0.55f, 0.72f);
    glVertex2f(-0.35f, 0.62f);
    glVertex2f(-0.10f, 0.70f);
    glVertex2f(0.10f, 0.60f);
    glVertex2f(0.30f, 0.70f);
    glVertex2f(0.50f, 0.64f);
    glVertex2f(0.70f, 0.74f);
    glVertex2f(0.88f, 0.62f);

    glVertex2f(-0.95f, 0.52f);
    glVertex2f(-0.72f, 0.58f);
    glVertex2f(-0.48f, 0.50f);
    glVertex2f(-0.20f, 0.55f);
    glVertex2f(0.05f, 0.48f);
    glVertex2f(0.25f, 0.55f);
    glVertex2f(0.48f, 0.50f);
    glVertex2f(0.68f, 0.56f);
    glVertex2f(0.92f, 0.48f);

    glEnd();

    glPointSize(1.0f);}

    }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (CLOUD)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_sd_drawCloud(float bx, float by, float sc) {
    glPushMatrix();
    glTranslatef(bx + scene1_sd_cloudX, by, 0);
    glScalef(sc, sc, 1.0f);

    float scene1_cr, scene1_cg, scene1_cb;

    if (scene1_sd_isNight) {
        scene1_cr = 0.22f;
        scene1_cg = 0.22f;
        scene1_cb = 0.32f;
    }
    else {
        scene1_cr = 0.98f;
        scene1_cg = 0.98f;
        scene1_cb = 1.00f;
    }

    // Set cloud color
    glColor3f(scene1_cr, scene1_cg, scene1_cb);

    // Cloud circles
    scene1_drawCircle(0.0f,  0.0f,   0.05f, 22);
    scene1_drawCircle(0.045f, 0.016f, 0.065f, 22);
    scene1_drawCircle(0.095f, 0.004f, 0.055f, 22);
    scene1_drawCircle(0.07f, -0.014f, 0.036f, 22);
    scene1_drawCircle(-0.025f, -0.009f, 0.034f, 22);

    glPopMatrix();

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (DISPLAY)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_display()
{
    glClearColor(0.75f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    scene1_parksky();

    scene1_sd_drawCelestial();

    scene1_sd_drawCloud(-0.30f, 0.72f, 1.00f);
    scene1_sd_drawCloud(0.30f, 0.78f, 0.80f);
    scene1_sd_drawCloud(0.72f, 0.68f, 0.70f);

    scene1_greenField();
    scene1_pathway();

	//fence
    glPushMatrix();
    glTranslatef(-0.6f, 0.5f, 0.0f);
    scene1_Fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    scene1_Fence();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.6f, 0.5f, 0.0f);
    scene1_Fence();
    glPopMatrix();

    //flower more
    glPushMatrix();
    glTranslatef(-0.90f, -0.20f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.70f, -0.25f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.50f, -0.22f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.30f, -0.27f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.10f, -0.23f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.10f, -0.28f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.30f, -0.24f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.50f, -0.26f, 0.0f);
    scene1_flower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.70f, -0.22f, 0.0f);
    scene1_flower();
    glPopMatrix();


    //flower2 more
    glPushMatrix();
    glTranslatef(-0.90f, 0.45f, 0.0f);
    scene1_flower2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.95f, -0.50f, 0.0f);
    scene1_flower2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.40f, -0.47f, 0.0f);
    scene1_flower2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.20f, -0.52f, 0.0f);
    scene1_flower2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.00f, -0.48f, 0.0f);
    scene1_flower2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.20f, -0.53f, 0.0f);
    scene1_flower2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.40f, -0.49f, 0.0f);
    scene1_flower2();
    glPopMatrix();


    //flower3 more
    glPushMatrix();
    glTranslatef(0.35f, -0.19f, 0.0f);
    scene1_flower3();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.55f, -0.23f, 0.0f);
    scene1_flower3();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.75f, -0.18f, 0.0f);
    scene1_flower3();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.85f, -0.18f, 0.0f);
    scene1_flower3();
    glPopMatrix();


    //manus
    glPushMatrix();
    glTranslatef(scene1_parkh1x, scene1_parkh1y, 0.0f);
    scene1_manus();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(scene1_parkh2x, scene1_parkh2y, 0.0f);
    scene1_manus2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(scene1_parkh3x, scene1_parkh3y, 0.0f);
    scene1_manus3();
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    scene1_bench();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.05f, 0.55f, 0.0f);
    scene1_bench();
    glPopMatrix();


    // SWING
    glPushMatrix();
    glTranslatef(-0.70f, 0.35f, 0.0f);
    scene1_swing();
    glPopMatrix();


    //tree3
    glPushMatrix();
    glTranslatef(0.45f, 0.48f, 0.0f);
    scene1_tree3();
    glPopMatrix();


    //tree more
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    scene1_tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.65f, -0.35f, 0.0f);
    scene1_tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.32f, 0.10f, 0.0f);
    scene1_tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.995f, 0.6f, 0.0f);
    scene1_tree();
    glPopMatrix();

    //tree2 more
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    scene1_tree2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.35f, 0.18f, 0.0f);
    scene1_tree2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.30f, 0.2f, 0.0f);
    scene1_tree2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.55f, -0.12f, 0.0f);
    scene1_tree2();
    glPopMatrix();

    //tree3 more
    glPushMatrix();
    glTranslatef(-0.30f, -0.20f, 0.0f);
    scene1_tree3();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.15f, 0.5f, 0.0f);
    scene1_nagordola();
    glPopMatrix();

    if (scene1_rain)
    {
        scene1_drawRain();
    }

    if (scene1_wind)
{
    scene1_drawWind();
}

if (scene1_snow)
{
    scene1_drawSnow();
}


}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (KEYS)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_keyboard(unsigned char scene1_key, int scene1_x, int scene1_y) {

    switch (scene1_key) {
    case 'v':
        scene1_sd_isNight = !scene1_sd_isNight;
        if (scene1_sd_isNight) {
            scene1_sd_skyR1 = 0.02f;
            scene1_sd_skyG1 = 0.02f;
            scene1_sd_skyB1 = 0.08f;
            scene1_sd_skyR2 = 0.05f;
            scene1_sd_skyG2 = 0.05f;
            scene1_sd_skyB2 = 0.12f;
        }
        else {
            scene1_sd_skyR1 = 0.50f;
            scene1_sd_skyG1 = 0.85f;
            scene1_sd_skyB1 = 1.00f;
            scene1_sd_skyR2 = 0.80f;
            scene1_sd_skyG2 = 0.93f;
            scene1_sd_skyB2 = 1.00f;
        }
        break;

    case 'f':   // start & stop rain
        scene1_rain = !scene1_rain;
        break;

    case 'w':
        scene1_rainSpeedMultiplier += 0.2f;
        break;

    case 's':
        if (scene1_rainSpeedMultiplier > 0.2f)
            scene1_rainSpeedMultiplier -= 0.2f;
        break;

    case 'n': // snow start & stop
        scene1_snow = !scene1_snow;
        break;

    case 'e':
        scene1_snowSpeedMultiplier += 0.2f;
        break;

    case 'd':
        scene1_snowSpeedMultiplier -= 0.2f;
        if (scene1_snowSpeedMultiplier < 0.1f)
            scene1_snowSpeedMultiplier = 0.1f; // avoid negative speed
        break;

    case 'g':
        scene1_wind = !scene1_wind;
        break;
    }

    //glutPostRedisplay();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (UPDATE)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void scene1_Update()//(int scene1_value)
{
    scene1_wheelAngle += 1.0f;
    scene1_swingAngle += scene1_swingSpeed;

if (scene1_swingAngle > 15.0f || scene1_swingAngle < -15.0f)
{
    scene1_swingSpeed = -scene1_swingSpeed;
}

    // cloud
    scene1_sd_cloudX += 0.0003f;
    if (scene1_sd_cloudX > 0.6f)
        scene1_sd_cloudX = -0.6f;

    scene1_parkh1x += scene1_parkh1speedX;
    scene1_parkh1y += scene1_parkh1speedY;
    if (scene1_parkh1x > 0.9f || scene1_parkh1x < -0.6f)
    {
        scene1_parkh1speedX = -scene1_parkh1speedX;
    }
    if (scene1_parkh1y > 0.3f || scene1_parkh1y < -0.9f)
    {
        scene1_parkh1speedY = -scene1_parkh1speedY;
    }


    if (rand() % 200 == 0)
    {
        scene1_parkh1speedX = ((rand() % 5) - 2) * 0.001f;
        scene1_parkh1speedY = ((rand() % 5) - 2) * 0.001f;
    }

    scene1_legAngle1 += scene1_legSpeed1;
    if (scene1_legAngle1 > 25.0f || scene1_legAngle1 < -25.0f)
    {
        scene1_legSpeed1 = -scene1_legSpeed1;
    }


    scene1_parkh2x += scene1_parkh2speedX;
    scene1_parkh2y += scene1_parkh2speedY;
    if (scene1_parkh2x > 0.9f || scene1_parkh2x < -0.6f)
    {
        scene1_parkh2speedX = -scene1_parkh2speedX;
    }

    if (scene1_parkh2y > 0.3f || scene1_parkh2y < -0.9f)
    {
        scene1_parkh2speedY = -scene1_parkh2speedY;
    }


    if (rand() % 200 == 0)
    {
        scene1_parkh2speedX = ((rand() % 5) - 2) * 0.001f;
        scene1_parkh2speedY = ((rand() % 5) - 2) * 0.001f;
    }
    scene1_legAngle2 += scene1_legSpeed2;
    if (scene1_legAngle2 > 25.0f || scene1_legAngle2 < -25.0f)
    {
        scene1_legSpeed2 = -scene1_legSpeed2;
    }


    scene1_parkh3x += scene1_parkh3speedX;
    scene1_parkh3y += scene1_parkh3speedY;

    if (scene1_parkh3x > 0.9f || scene1_parkh3x < -0.6f)
    {
        scene1_parkh3speedX = -scene1_parkh3speedX;
    }

    if (scene1_parkh3y > 0.3f || scene1_parkh3y < -0.9f)
    {
        scene1_parkh3speedY = -scene1_parkh3speedY;
    }


    if (rand() % 200 == 0)
    {
        scene1_parkh3speedX = ((rand() % 5) - 2) * 0.001f;
        scene1_parkh3speedY = ((rand() % 5) - 2) * 0.001f;
    }
    scene1_legAngle3 += scene1_legSpeed3;
    if (scene1_legAngle3 > 25.0f || scene1_legAngle3 < -25.0f)
    {
        scene1_legSpeed3 = -scene1_legSpeed3;
    }

if (scene1_snow)
{
    for (int scene1_i = 0; scene1_i < 500; scene1_i++)
    {
        scene1_snowY[scene1_i] -= scene1_snowSpeed[scene1_i] * scene1_snowSpeedMultiplier;
        scene1_snowSway[scene1_i] += 0.02f; //sway phase
        //scene1_snowX[scene1_i] += sin(scene1_snowSway[scene1_i]) * 0.0008f; //left/right drift

        if (scene1_snowY[scene1_i] < -1.0f)
        {
            scene1_snowY[scene1_i] = 1.0f;
            scene1_snowX[scene1_i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
            scene1_snowSpeed[scene1_i] = 0.003f + ((float)rand() / RAND_MAX) * 0.006f;
        }
    }
}

if (scene1_wind)
{
    scene1_windPhase += 0.05f;

    // Tree sway
    scene1_windSway = sinf(scene1_windPhase) * 1.0f;

    // Move wind lines in one direction
    for (int scene1_i = 0; scene1_i < 60; scene1_i++)
    {
        scene1_windLineX[scene1_i] += 0.012f;

        if (scene1_windLineX[scene1_i] > 1.0f)
            scene1_windLineX[scene1_i] = -1.0f;
    }
}
else
{
    // Slowly return tree to normal position
    scene1_windSway *= 0.92f;
}

    if (scene1_rain)
    {
        for (int scene1_i = 0; scene1_i < 1000; scene1_i++)
        {
            scene1_rainY[scene1_i] -= scene1_rainSpeed[scene1_i] * scene1_rainSpeedMultiplier;
            scene1_rainX[scene1_i] -= 0.002f; // wind effect

            // reset rain drop
            if (scene1_rainY[scene1_i] < -1.0f)
            {
                scene1_rainY[scene1_i] = 1.0f;
                scene1_rainX[scene1_i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

                scene1_rainSpeed[scene1_i] = 0.01f + ((float)rand() / RAND_MAX) * 0.03f;
            }
        }
    }


}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  (DISPLAY)  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



#endif
