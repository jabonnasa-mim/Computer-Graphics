#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#include "scene1.h"
#include "scene2.h"
#include "scene3.h"


// which scene is currently shown: 1, 2, or 3
int currentScene = 1;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentScene)
    {
    case 1:
        scene1_display();
        break;
    case 2:
        scene2_display();
        break;
    case 3:
        scene3_display();
        break;
    }

    glFlush();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    // scene switching, works no matter which scene is active
    switch (key)
    {
    case '1':
        currentScene = 1;
        glutPostRedisplay();
        return;
    case '2':
        currentScene = 2;
        glutPostRedisplay();
        return;
    case '3':
        currentScene = 3;
        glutPostRedisplay();
        return;
    case 27: // ESC
        exit(0);
    }

    // otherwise let the active scene handle its own keys
    switch (currentScene)
    {
    case 1:
        scene1_keyboard(key, x, y);
        break;
    case 2:
        scene2_keyboard(key, x, y);
        break;
    case 3:
        scene3_keyboard(key, x, y);
        break;
    }

    glutPostRedisplay();
}


void update(int value)
{
    switch (currentScene)
    {
    case 1:
        scene1_Update();
        break;
    case 2:
        scene2_Update();
        break;
    case 3:
        scene3_Update();
        break;
    }

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}

void mouse(int button, int state, int x, int y)
{
    // only scene2 has a mouse handler defined
    if (currentScene == 2)
    {
        scene2_handleMouse(button, state, x, y);
    }
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics Project");
    scene1_initializeWeather();
    scene2_initializeWeather();
    scene3_initializeWeather();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
